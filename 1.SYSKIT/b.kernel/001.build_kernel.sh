#!/bin/bash

source ~/.colorc

export KERNEL_TOPDIR=$PWD
export GCC_PATH_DEFAULT=$PWD/../../0.GCCKIT/armgcc
export GCC_TYPE_DEFAULT=arm-linux

export MODULE_SRC_NAME=kernel
export MODULE_SRC_DIR=$KERNEL_TOPDIR/$MODULE_SRC_NAME
export MODULE_OUT_DIR=$KERNEL_TOPDIR/output
export MODULE_DEF_CFG=nuc972_coidea_defconfig
export MODULE_MOD_INS=$KERNEL_TOPDIR/install
export MODULE_CPY_DIR=${KERNEL_TOPDIR}/../../9.IMGBINS

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
	#Kernel with uImage need mkimage
	mkimage -V >/dev/null  2>&1
	if [ ! $? = 0 ]; then
		pwarn "No \"mkimage\" found, auto install..."
		sudo apt-get install u-boot-tools
		if [ $? = 0 ];then
			pdone 	"Install \"mkimage\" finish!"
		else
			perro "Install \"mkimage\" failed!"
			exit 1
		fi
	fi
}

dir_in()
{
	if [ -d  $MODULE_SRC_DIR ]; then
		pinfo "Now cd \$MODULE_SRC_DIR: $MODULE_SRC_DIR"
		cd $MODULE_SRC_DIR
	else
		perro "\$MODULE_SRC_DIR: $MODULE_SRC_DIR not found!"
		exit 1
	fi
}

dir_ret()
{
	pinfo "Exit $PWD"
	cd - > /dev/null
}

show_help()
{
	pinfo "Input: $0 build        to build cur kernel"
	pinfo "Input: $0 menuconfig   to menuconfig cur kernel"
	pinfo "Input: $0 defconfig    to defconfig kernel"
	pinfo "Input: $0 modules      to build and install modules"
	pinfo "Input: $0 clean        to clean kernel"
	pinfo "Input: $0 pack         to pack   kernel as .tar.gz"
}

check_option()
{	
	if [ -z "$1" ]; then
		perro "No extra param!"
		show_help
		exit 1
	else
		if [ "x$1" = "xbuild" ]; then
			$1
		elif [ "x$1" = "xmenuconfig" ]; then
			$1
		elif [ "x$1" = "xdefconfig" ]; then
			$1
		elif [ "x$1" = "xmodules" ]; then
			$1
		elif [ "x$1" = "xclean" ]; then
			$1
		elif [ "x$1" = "xpack" ]; then
			$1
		else
			perro "Invalid param : $1"
			show_help
			exit 1
		fi
	fi
}

check_lzop()
{
	lzop -V >/dev/null  2>&1
	if [ ! $? = 0 ]; then
		pwarn "No \"lzop\" found, auto install..."
		sudo apt-get install lzop
		if [ $? = 0 ];then
			pdone 	"Install \"lzop\" finish!"
		else
			perro "Install \"lzop\" failed!"
			exit 1
		fi
	fi
}

pack()
{
	if [ -d $MODULE_SRC_DIR ]; then
		pinfo "Start pack $MODULE_SRC_NAME as $MODULE_SRC_NAME.tar.gz"
		tar czf $MODULE_SRC_NAME.tar.gz $MODULE_SRC_NAME
		[ $? -ne 0 ] && perro "Pack kernel [ERROR]" && exit 1
	    pdone "Pack kernel [OK]"
	else
		perro "No MODULE_SRC_DIR: $MODULE_SRC_DIR found!"
		exit 1
	fi
}

clean()
{
	if [ ! -d $MODULE_OUT_DIR ]; then
		pdone "kernel allready clean!"
		exit 1
	fi
	check_env
	dir_in
    make O=$MODULE_OUT_DIR distclean
	[ $? -ne 0 ] && perro "--------------------------" && dir_ret && exit 1
    rm -rf $MODULE_OUT_DIR
	dir_ret
    pdone "--------------------------"
}

menuconfig()
{
	check_env
	dir_in
    pinfo "Kernel menuconfig start"
	make O=$MODULE_OUT_DIR menuconfig
	[ $? -ne 0 ] && perro "Menuconfig kernel [ERROR]" && dir_ret && exit 1
	dir_ret
    pdone "Menuconfig kernel [OK]"
}

defconfig()
{
	check_env
	if [ ! -d $MODULE_OUT_DIR ]; then
		mkdir -p $MODULE_OUT_DIR
	fi
	dir_in
    pinfo "Kernel defconfig refer to: $MODULE_DEF_CFG"
	if [ ! -d $MODULE_OUT_DIR/Makefile ]; then
		cp $MODULE_SRC_DIR/Makefile $MODULE_OUT_DIR/Makefile
	fi
    make O=$MODULE_OUT_DIR $MODULE_DEF_CFG
	[ $? -ne 0 ] && perro "Defconfig kernel [ERROR]" && dir_ret && exit 1
	dir_ret
	pdone "Defconfig kernel [OK]"
}

build()
{
	check_env
	check_lzop

	if [ ! -d $MODULE_OUT_DIR ]; then
		mkdir -p $MODULE_OUT_DIR
	fi

	dir_in

    make  O=$MODULE_OUT_DIR all -j4
	[ $? -ne 0 ] && perro "Build kernel [ERROR]" && dir_ret && exit 1
    pinfo "Build kernel [OK] output dir: $MODULE_OUT_DIR"

    make  O=$MODULE_OUT_DIR uImage -j4
	[ $? -ne 0 ] && perro "Build kernel uImage [ERROR]" && dir_ret && exit 1
    pinfo "Build kernel uImage [OK] output dir: $MODULE_OUT_DIR"

	dir_ret

	if [ ! -d $MODULE_CPY_DIR ]; then
		pwarn "Create new copy directory"
		sudo mkdir -p ${MODULE_CPY_DIR}
		sudo chmod 777 ${MODULE_CPY_DIR}
	fi
	cp $MODULE_OUT_DIR/arch/arm/boot/uImage $MODULE_CPY_DIR/4.dE000S250.kernel.bin
}
modules()
{
	check_env
	check_lzop

	if [ ! -d $MODULE_MOD_INS ]; then
		mkdir -p $MODULE_MOD_INS
	fi

	dir_in

    make  O=$MODULE_OUT_DIR modules
	[ $? -ne 0 ] && perro "Build kernel modules [ERROR]" && dir_ret && exit 1
    pinfo "Build kernel modules [OK] output dir: $MODULE_OUT_DIR"

    make  O=$MODULE_OUT_DIR modules_install INSTALL_MOD_PATH=${MODULE_MOD_INS}
	[ $? -ne 0 ] && perro "Install kernel modules [ERROR]" && dir_ret && exit 1
    pinfo "Intall kernel modules [OK] output dir: $MODULE_OUT_DIR"
	dir_ret
}

check_option $1
