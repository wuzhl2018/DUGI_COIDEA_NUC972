#!/bin/bash
#Author: weike
#MyQQID: 2362317758

export TOPDIR=$PWD

export MODPKG_ROOT=${TOPDIR}/pkg
export MODSRC_ROOT=${TOPDIR}/src

export MODNAME=rootfs

export MODPKG_NAME=rootfs.tar.gz
export MODSRC_NAME=rootfs

export MODPKG_PATH=${MODPKG_ROOT}/${MODPKG_NAME}
export MODSRC_PATH=${MODSRC_ROOT}/${MODSRC_NAME}

export MDKIT_PATH=${TOPDIR}/../2.MIDKIT/output

export CONFIG_ETC_PATH=${TOPDIR}/pkg/etc
export CONFIG_VAR_PATH=${TOPDIR}/pkg/var

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
check_source()
{
	if [ ! -d ${MODSRC_PATH} ]; then
		pwarn "No ${MODSRC_PATH} found, try extract new source!"
		if [ -f ${MODPKG_PATH} ]; then
			cd ${MODPKG_ROOT}
			if [ "${MODPKG_NAME##*.}"x = "gz"x ]; then
				sudo tar xzf ${MODPKG_PATH} -C ${MODSRC_ROOT}
				if [ $? -eq 0 ]; then
					pdone "Extract .gz  package: ${MODPKG_NAME} OK!"
				else
					perro "Extract .gz  package: ${MODPKG_NAME} Failed!"
					cd -> /dev/null
					exit 1
				fi
			elif [ "${MODPKG_NAME##*.}"x = "bz2"x ]; then
				sudo tar xjf ${MODPKG_PATH} -C ${MODSRC_ROOT}
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
	cp ./${MODPKG_NAME} ${MODPKG_PATH}
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
	if [ ! -d ${MDKIT_PATH} ]; then
		perro "No MDKIT_PATH: ${MDKIT_PATH}"
		exit 1
	fi

	#copy midkit things
	if [ -e ${MDKIT_PATH}/bin ]; then
		pwarn "Copy /bin [START]"
		mkdir -p ${MODSRC_PATH}/bin > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/bin/*    	${MODSRC_PATH}/bin/
		pdone "Copy /bin [DONE]"
	fi

	if [ -e ${MDKIT_PATH}/sbin ]; then
		pwarn "Copy /sbin [START]"
		mkdir -p ${MODSRC_PATH}/sbin > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/sbin/*    	${MODSRC_PATH}/sbin/
		pdone "Copy /sbin [DONE]"
	fi


	if [ -e ${MDKIT_PATH}/lib ]; then
		pwarn "Copy /lib [START]"
		mkdir -p ${MODSRC_PATH}/lib > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/lib/*.so* 	${MODSRC_PATH}/lib/
		pdone "Copy /lib [DONE]"
	fi


	if [ -e ${MDKIT_PATH}/usr/bin ]; then
		pwarn "Copy /usr/bin [START]"
		mkdir -p ${MODSRC_PATH}/usr/bin > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/usr/bin/* 	${MODSRC_PATH}/usr/bin/
		pdone "Copy /usr/bin [DONE]"
	fi


	if [ -e ${MDKIT_PATH}/usr/sbin ]; then
		pwarn "Copy /usr/sbin [START]"
		mkdir -p ${MODSRC_PATH}/usr/sbin > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/usr/sbin/* ${MODSRC_PATH}/usr/sbin/
		pdone "Copy /usr/sbin [DONE]"
	fi

	if [ -e ${MDKIT_PATH}/usr/lib ]; then
		pwarn "Copy /usr/lib [START]"
		mkdir -p ${MODSRC_PATH}/usr/lib > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/usr/lib/*.so* ${MODSRC_PATH}/usr/lib/
		pdone "Copy /usr/lib [DONE]"
	fi

	#if we need python, do below:
	if [ ! -e ${MODSRC_PATH}/usr/lib/python2.7 ]; then
		pwarn "Copy /usr/lib/python2.7 [START]"
		mkdir -p ${MODSRC_PATH}/usr/lib > /dev/null 2>&1
		cp -rf ${MDKIT_PATH}/usr/lib/python2.7 ${MODSRC_PATH}/usr/lib/
		pwarn "Copy /usr/lib/python2.7 [DONE]"
	fi

	#if we need ftp, do below:
	if [ -e ${CONFIG_ETC_PATH}/vsftpd.conf ]; then
		cp -rf ${CONFIG_ETC_PATH}/vsftpd.conf ${MODSRC_PATH}/etc/
	fi
	if [ ! -e ${MODSRC_PATH}/usr/share/empty ]; then
		mkdir -p ${MODSRC_PATH}/usr/share/empty
	fi
	if [ ! -e ${MODSRC_PATH}/var/log ]; then
		mkdir -p ${MODSRC_PATH}/var/log
		cd ${MODSRC_PATH}/var/log
		touch vsftpd.log
		cd - > /dev/null
	fi

	#if ne need lighttpd, do below
	if [ ! -e ${MODSRC_PATH}/var/www ]; then
		mkdir -p ${MODSRC_PATH}/var/www
	fi
	cp -rf ${CONFIG_VAR_PATH}/www/* ${MODSRC_PATH}/var/www/

	if [ ! -e ${MODSRC_PATH}/etc/lighttpd ]; then
		cp -rf ${CONFIG_ETC_PATH}/lighttpd ${MODSRC_PATH}/etc/
	fi
	if [ ! -e ${MODSRC_PATH}/etc/init.d/lighttpd ]; then
		cp -rf ${CONFIG_ETC_PATH}/init.d/lighttpd ${MODSRC_PATH}/etc/init.d/
	fi

	pdone "Build $MODNAME OK!"
}

if [ "x$1" = "xbuild" ]; then
	check_source
	build_module
elif [ "x$1" = "xpack" ]; then
	pack_module
else
	pinfo "Input: $0 pack    pack  rootfs to pkg"
	pinfo "Input: $0 build   build rootfs"
fi
