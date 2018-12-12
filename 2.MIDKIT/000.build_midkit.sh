#!/bin/bash
#Author: weike
#MyQQID: 2362317758

export TOPDIR=$PWD
export BUILD_DATE=$(date +%Y%m%d_%H%M%S)

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

#-----------------------------------------------------------------------


src_backup()
{
	if [ -d ${TOPDIR}/src_${BUILD_DATE} ]; then
		rm -rf ${TOPDIR}/src_${BUILD_DATE} 
	fi
	if [ -d ${TOPDIR}/src ]; then
		mv ${TOPDIR}/src ${TOPDIR}/src_${BUILD_DATE}
	fi
	mkdir -p ${TOPDIR}/src
	pwarn "src backup: src_${BUILD_DATE} [OK]"
}

src_recover()
{
	if [ -d ${TOPDIR}/src ]; then
		rm -rf ${TOPDIR}/src 
	fi

	if [ -d ${TOPDIR}/src_${BUILD_DATE} ]; then
		mv  ${TOPDIR}/src_${BUILD_DATE} ${TOPDIR}/src 
	fi
	pwarn "src recovered [OK]"
}

sub_defconfig()
{
	./$1 defconfig
	if [ $? -eq 0 ]; then
		pdone "defconfig $1 [OK]"
	else
		perro "defconfig $1 [ERROR]"
		src_recover
		exit 1
	fi
}

sub_build()
{
	./$1 build
	if [ $? -eq 0 ]; then
		pdone "build $1 [OK]"
	else
		perro "build $1 [ERROR]"
		src_recover
		exit 1
	fi
}

sub_build 001.build_busybox.sh
sub_build 002.build_e2fsprogs.sh
sub_build 003.build_lzo.sh
sub_build 004.build_zlib.sh
sub_build 005.build_mtdutils.sh
sub_build 006.build_i2ctools.sh
sub_build 007.build_pcre.sh
sub_build 008.build_lighttpd.sh
sub_build 009.build_wirelesstools.sh
sub_build 010.build_netperf.sh
sub_build 011.build_pythonX86.sh
sub_build 012.build_pythonARM.sh
sub_build 013.build_alsautils.sh
sub_build 014.build_rzsz.sh
sub_build 015.build_dropbear.sh
sub_build 016.build_vsftpd.sh
sub_build 017.build_db.sh
sub_build 018.build_iproute2.sh
sub_build 019.build_vsftpd.sh
sub_build 020.build_lighttpd.sh
sub_build 021.build_tslib.sh
pdone "build midkit [OK]"
