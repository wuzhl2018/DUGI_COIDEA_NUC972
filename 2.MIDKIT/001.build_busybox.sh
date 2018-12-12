#!/bin/bash
#Author: weike
#MyQQID: 2362317758

export TOPDIR=$PWD

export MODPKG_ROOT=${TOPDIR}/pkg
export MODSRC_ROOT=${TOPDIR}/src

export MODNAME=busybox

export MODPKG_NAME=busybox-1.23.2.tar.gz
export MODSRC_NAME=busybox-1.23.2

export MODPKG_PATH=${MODPKG_ROOT}/${MODPKG_NAME}
export MODSRC_PATH=${MODSRC_ROOT}/${MODSRC_NAME}
export MODOUT_PATH=$TOPDIR/output

export GCC_PATH_DEFAULT=$TOPDIR/../0.GCCKIT/armgcc
export GCC_TYPE_DEFAULT=arm-linux

export MODCFG_DEF_PATH=${MODSRC_PATH}/configs/dugi_static_defconfig
export MODCFG_PLT_INFO="-mfloat-abi=soft"
#export MODCFG_PLT_INFO="-mfloat-abi=hard"

#-----------------------------------------------------------------------
perro()
{
    echo -e "\033[47;41mERROR: $*\033[0m"
}

pwarn()
{
    echo -e "\033[47;43mWARN: $*\033[0m"
}

pinfo()
{
    echo -e "\033[47;44mINFO: $*\033[0m"
}

pdone()
{
    echo -e "\033[47;42mINFO: $*\033[0m"
}

change_line()
{
	#$1: file path
	#$2:  KeyString, example: line is: ABC=1 KeyString is: ABC
	#$3:  ReplaceString, 
	#$4:  if $4 = 1 ABC=1 wille change to ABC="1"
	if [ $# -ne 4 ]; then
		perro "change_line: param error!"
		exit 1
	fi
	
	if [ ! -f $1 ]; then
		perro "change_line: no file : $1 found!"
		exit 1
	fi

	if [ -z "$2" ]; then
		perro "change_line: no key string found!"
		exit 1
	fi

	if [ -z "$3" ]; then
		perro "change_line: no replace string found!"
		exit 1
	fi

	local line_number=$(grep -n "^$2" $1 | cut -d: -f 1)
	if [ -z  "$line_number" ]; then
		perro "change_line: $2 not found in : $2"
		exit 1
	fi
	if [ $4 -eq 1 ]; then
		sed -i "${line_number}c $2=\"$3\"" $1
	    [ $? -ne 0 ] && perro "change_line: $1 : change $2 as $3 failed!" && exit 1
		#pdone "change_line: $1 : change $2 as $3 OK!"
	else
		sed -i "${line_number}c $2=$3" $1
	    [ $? -ne 0 ] && perro "change_line: $1 : change $2 as $3 failed!" && exit 1
		#pdone "change_line: $1 : change $2 as $3 OK!"
	fi
	return 0
}

#-----------------------------------------------------------------------

check_compiler()
{
	$GCC_TYPE-gcc -v > /dev/null  2>&1
	if [ $? -eq 0 ]; then
		pinfo "check global gcc type : $GCC_TYPE"
	else
		pinfo "check local gcc type : $GCC_PATH"
		if [ -d $GCC_PATH ]; then
			pdone "check local gcc valid OK!"
			export PATH=$GCC_PATH/bin:$PATH
			$GCC_TYPE-gcc -v > /dev/null  2>&1
			if [ $? -eq 0 ]; then
				pdone "test local gcc valid OK!"
			else
				perro "test local gcc valid Failed!"
			exit 1
			fi
		else
			perro "check local gcc valid Failed!"
			exit 1
		fi
	fi
}

check_env()
{
	if [ -z "$GCC_TYPE" ]; then
		pwarn "No compile env configured!"
		pwarn "Set default compile env"
		export GCC_PATH=$GCC_PATH_DEFAULT
		export GCC_TYPE=$GCC_TYPE_DEFAULT
		export HOST=$GCC_TYPE
		export TARGET=$GCC_TYPE
		export CC="${HOST}-gcc"
		export CXX="${HOST}-g++"
		export OBJC="${CC}"
		export LD="${HOST}-ld"
		export ARCH=arm
		export CROSS_COMPILE=${HOST}-
		pinfo "--------default compile env------"
		pinfo "ARCH : $ARCH"
		pinfo "HOST : $HOST"
		pinfo "GCC_TYPE : $GCC_TYPE"
		pinfo "GCC_PATH : $GCC_PATH"
		pinfo "CROSS_COMPILE: $CROSS_COMPILE"
		pinfo "---------------------------------"
		check_compiler
	else
		pwarn "Get compile env configured!"
		pinfo "--------current compile env------"
		pinfo "ARCH : $ARCH"
		pinfo "HOST : $HOST"
		pinfo "GCC_TYPE : $GCC_TYPE"
		pinfo "GCC_PATH : $GCC_PATH"
		pinfo "CROSS_COMPILE: $CROSS_COMPILE"
		pinfo "---------------------------------"
	fi
}

#-----------------------------------------------------------------------
defconfig_module()
{ 
	if [ -f $MODCFG_DEF_PATH ]; then
		cp $MODCFG_DEF_PATH ${MODSRC_PATH}/.config
		pinfo "Copy ${MODCFG_DEF_PATH} as busybox .config"
	else
		pwarn "No busybox cfg file found, use default"
	fi
	change_line $MODSRC_PATH/.config CONFIG_CROSS_COMPILER_PREFIX $GCC_TYPE- 1
	[ $? -ne 0 ] && perro "config cross compile failed" && dir_ret && exit 1
	pdone "config cross compile finish!"

	change_line $MODSRC_PATH/.config CONFIG_PREFIX $MODOUT_PATH 1
	[ $? -ne 0 ] && perro "config prefix failed" && dir_ret && exit 1
	pdone "config prefix finish!"

	change_line $MODSRC_PATH/.config CONFIG_EXTRA_CFLAGS "$MODCFG_PLT_INFO" 1
	[ $? -ne 0 ] && perro "config cpu type failed" && dir_ret && exit 1
	pdone "config cpu type finish!"
}
check_source()
{
	if [ ! -d ${MODSRC_PATH} ]; then
		pwarn "No ${MODSRC_PATH} found, try extract new source!"
		if [ -f ${MODPKG_PATH} ]; then
			cd ${MODPKG_ROOT}
			if [ "${MODPKG_NAME##*.}"x = "gz"x ]; then
				tar xzf ${MODPKG_PATH} -C ${MODSRC_ROOT}
				if [ $? -eq 0 ]; then
					pdone "Extract .gz  package: ${MODPKG_NAME} OK!"
				else
					perro "Extract .gz  package: ${MODPKG_NAME} Failed!"
					cd -> /dev/null
					exit 1
				fi
			elif [ "${MODPKG_NAME##*.}"x = "bz2"x ]; then
				tar xjf ${MODPKG_PATH} -C ${MODSRC_ROOT}
				if [ $? -eq 0 ]; then
					pdone "Extract .bz2  package: ${MODPKG_NAME} OK!"
				else
					perro "Extract .bz2  package: ${MODPKG_NAME} Failed!"
					cd -> /dev/null
					exit 1
				fi
			else
				perro "Unknown tar file type!"
				cd -> /dev/null
				exit 1
			fi
			cd -> /dev/null
		else
			perro "No package: ${MODPKG_NAME} found!"
			exit 1
		fi
	else
		pdone "Check source OK!"
	fi
}

pack_module()
{
	if [ ! -d  ${MODSRC_PATH} ]; then
		perro "No MODSRC_PATH: ${MODSRC_PATH}"
		exit 1
	fi
	cd ${MODSRC_ROOT}
	sudo tar czvf  ./${MODPKG_NAME} ${MODSRC_NAME}
	if [ $? -eq 0 ];then
		pdone "Tar source OK!"
	else
		perro "Tar source Failed!"
		exit 1
	fi
	cp -rf ./${MODPKG_NAME} ${MODPKG_PATH}
	sudo chmod 777 ${MODPKG_PATH}
	sudo chown -R $(whoami):$(whoami) ${MODPKG_PATH}
	if [ $? -eq 0 ];then
		pdone "Pack source OK!"
		cd - > /dev/null
	else
		perro "Pack source Failed!"
		cd - > /dev/null
		exit 1
	fi
}

build_module()
{
#	if [ -d ${MODOUT_PATH} ]; then
#		rm -rf ${MODOUT_PATH}
#		echo "Remove old prefix_busybox [OK]"
#	fi

	(cd ${MODSRC_PATH} && make )
    [ $? -ne 0 ] && perro "Compile busybox Failed" && exit 1
	pdone "Compile busybox OK!"


	(cd ${MODSRC_PATH} && make install)
    [ $? -ne 0 ] && perro "Install busybox Failed" && exit 1
	pdone "Install busybox OK!"
	pinfo "prefix dir: ${MODOUT_PATH}"
}
menuconfig_module()
{
	if [ ! -f $MODSRC_PATH/.config ]; then
		perro "No .config found in $MODSRC_PATH"
		exit 1
	fi
	(cd ${MODSRC_PATH} && make menuconfig)
    [ $? -ne 0 ] && perro "Config busybox Failed" && exit 1
	pdone "Config busybox OK!"
}

clean_module()
{
	(cd ${MODSRC_PATH} && make clean && make distclean)
    [ $? -ne 0 ] && perro "Clear busybox Failed" && exit 1
	pdone "Clear busybox OK!"
}

if [ "x$1" = "xdefconfig" ]; then
	check_env
	check_source
	defconfig_module
elif [ "x$1" = "xbuild" ]; then
	check_env
	check_source
	build_module
elif [ "x$1" = "xmenuconfig" ]; then
	check_env
	check_source
	menuconfig_module
elif [ "x$1" = "xclean" ]; then
	check_env
	clean_module
elif [ "x$1" = "xpack" ]; then
	pack_module
else
	pinfo "Input: $0 defconfig    Config busybox"
	pinfo "Input: $0 build        Compile busybox"
	pinfo "Input: $0 menuconfig   Menuconfig busybox"
	pinfo "Input: $0 clean        Clear busybox"
	pinfo "Input: $0 pack         Pack source to pkg"
fi
