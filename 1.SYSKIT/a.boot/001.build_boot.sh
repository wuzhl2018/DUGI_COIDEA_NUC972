#!/bin/bash

source ~/.colorc

export BOOT_TOPDIR=$PWD
export GCC_PATH_DEFAULT=$PWD/../../0.GCCKIT/armgcc
export GCC_TYPE_DEFAULT=arm-linux

export MODULE_SRC_NAME=uboot

export MODULE_SRC_DIR=$BOOT_TOPDIR/$MODULE_SRC_NAME
export MODULE_OUT_DIR=$BOOT_TOPDIR/output
export MODULE_DEF_CFG=nuc970_config
export MODULE_CPY_DIR=/mnt/hgfs/D/1.CDNUC972/

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
			$GCC_TYPE-gcc -v > /dev/null 2>&1
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
	pinfo "Input: $0 build        to build cur boot"
	pinfo "Input: $0 menuconfig   to menuconfig cur boot"
	pinfo "Input: $0 defconfig    to defconfig boot"
	pinfo "Input: $0 clean        to clean boot"
	pinfo "Input: $0 pack         to pack boot as .tar.gz"
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

#-----------------------------------------------------------------------

function pack()
{
	if [ -d $MODULE_SRC_DIR ]; then
		pinfo "Start pack $MODULE_SRC_NAME as $MODULE_SRC_NAME.tar.gz"
		tar czf $MODULE_SRC_NAME.tar.gz $MODULE_SRC_NAME
		[ $? -ne 0 ] && perro "--------------------------" && exit 1
	    pdone "--------------------------"
	else
		perro "No MODULE_SRC_DIR: $MODULE_SRC_DIR found!"
		exit 1
	fi
}

function clean()
{
	check_env
	dir_in
    make mrproper
	[ $? -ne 0 ] && perro "make mrproper failed" && dir_ret && exit 1
    make distclean
	[ $? -ne 0 ] && perro "make distclean failed" && dir_ret && exit 1
	dir_ret
	if [ -d $MODULE_OUT_DIR ]; then
		rm -rf $MODULE_OUT_DIR
	fi
    pdone "--------------------------"
}

function menuconfig()
{
	check_env
	dir_in
    pinfo "Boot menuconfig start"
	make O=$MODULE_OUT_DIR menuconfig
	[ $? -ne 0 ] && perro "--------------------------" && dir_ret && exit 1
	dir_ret
    pdone "--------------------------"
}

function defconfig()
{
	check_env
	if [ ! -d $MODULE_OUT_DIR ]; then
		mkdir -p $MODULE_OUT_DIR
	fi
	dir_in
    pinfo "Boot defconfig refer to: $MODULE_DEF_CFG"
    make O=$MODULE_OUT_DIR $MODULE_DEF_CFG
	[ $? -ne 0 ] && perro "--------------------------" && dir_ret && exit 1
	dir_ret
    pdone "--------------------------"
}

function build()
{
	check_env
	dir_in
    make O=$MODULE_OUT_DIR all
	[ $? -ne 0 ] && perro "--------------------------" && dir_ret && exit 1
    pinfo "Boot build done, output dir: $MODULE_OUT_DIR"
	dir_ret
    pdone "--------------------------"

	if [ ! -d $MODULE_CPY_DIR ]; then
		pwarn "Create new copy directory"
		sudo mkdir -p ${MODULE_CPY_DIR}
		sudo chmod 777 ${MODULE_CPY_DIR}
	fi
	cp $MODULE_OUT_DIR/nand_spl/u-boot-spl.bin    ${MODULE_CPY_DIR}/1.uE220S000.spl.bin
	cp $MODULE_OUT_DIR/u-boot.bin                 ${MODULE_CPY_DIR}/2.dE000S150.uboot.bin
}

check_option $1
