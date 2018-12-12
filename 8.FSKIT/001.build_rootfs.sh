#!/bin/bash

source ~/.colorc

export TOPDIR=$PWD
export TOPOUT=${TOPDIR}/output

export YAFFS2_DIN_FILE=${TOPDIR}/src/rootfs
export YAFFS2_OUT_NAME=5.dE000S260.rootfs.bin
export YAFFS2_OUT_FILE=${TOPOUT}/${YAFFS2_OUT_NAME}
export YAFFS2_OUT_COPY=${TOPDIR}/../9.IMGBINS

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
	pinfo "Input: $0 build"
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
		else
			perro "Invalid param : $1"
			show_help
			exit 1
		fi
	fi
}

build()
{
	if [ -f ${YAFFS2_OUT_FILE} ]; then
		rm -rf ${YAFFS2_OUT_FILE}
	fi

	if [ ! -d ${YAFFS2_DIN_FILE} ]; then
		perro "No YAFFS2 DIN DIR : ${YAFFS2_DIN_FILE}"
		exit 1
	fi

	if [ ! -d ${TOPOUT} ]; then
		pwarn "Create TOPOUT : ${TOPOUT}"
		mkdir -p ${TOPOUT}
	fi

	cd ${YAFFS2_DIN_FILE}
	sudo chown -R root:root ./*
	cd - > /dev/null

	mkyaffs2 --inband-tags -p 2048 ${YAFFS2_DIN_FILE} ${YAFFS2_OUT_FILE}

	ls -lh ${YAFFS2_OUT_FILE}

	if [ ! -d $YAFFS2_OUT_COPY ]; then
		pwarn "Create new copy directory"
		sudo mkdir -p ${YAFFS2_OUT_COPY}
		sudo chmod 777 ${YAFFS2_OUT_COPY}
	fi
	cp ${YAFFS2_OUT_FILE} ${YAFFS2_OUT_COPY}

	cd ${YAFFS2_DIN_FILE}
	sudo chown -R $(whoami):$(whoami) ./*
	cd - > /dev/null
}
check_option $1
