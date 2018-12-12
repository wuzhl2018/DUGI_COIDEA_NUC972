# DUGI_COIDEA_NUC972

#### 项目介绍
酷客开发板专用嵌入式Linux系统，集成了SSH/Telnet/Lighttpd/Python/Qt4/Qt5等功能，持续不断更新中！


#### 软件架构

- 0.GCCKIT， 编译器目录，  包含armgcc编译器无需配置PATH环境变量；
- 1.SYSKIT， 系统层目录，  包含u-boot、kernel源码和自动编译脚本；
- 2.MIDKIT， 中间件目录，  包含依赖库源码和自动编译脚本；
- 3.GUIKIT， 图像层目录，  包含Qt4/Qt5/uGFB/LittleVG等图形引擎；
- 4.APPKIT， 应用层目录，  包含各种应用程序示例；
- 8.FSKIT，  文件系统目录，包含根文件系统和自动构建脚本；
- 9.IMGBINS，二进制目录，  包含所有编译的映像文件。
 
中间还有的5~7编号留作后续扩展使用！！！

#### 安装教程

- 1. 使用git clone 下载源码：
git clone https://gitee.com/CCMYLOVE/DUGI_COIDEA_NUC972.git

#### 使用说明

- 1.进入DUGI_COIDEA_NUC97X/1.SYSKIT/a.boot目录，执行以下命令编译u-boot：

```
(master)$ ./001.build_boot.sh defconfig
(master)$ ./001.build_boot.sh build
```


- 2.进入DUGI_COIDEA_NUC97X/1.SYSKIT/b.kernel目录，执行以下命令编译kernel：

```
(master)$ ./001.build_kernel.sh defconfig
(master)$ ./001.build_kernel.sh build
```


- 3.进入DUGI_COIDEA_NUC97X/2.MIDKIT目录，分别执行编译脚本，也可以执行统一脚本：
`./000.build_midkit.sh`

- 4.进入DUGI_COIDEA_NUC97X/8.FSKIT目录，执行以下命令收集中间件：
`./002.install_midkit_to_rootfs.sh build`

- 5.进入DUGI_COIDEA_NUC97X/8.FSKIT目录，执行以下命令构建文件系统：
`./001.build_rootfs.sh  build`

- 6.进入DUGI_COIDEA_NUC97X/9.IMGBINS目录，可以看到所有的映像文件，使用烧写工具烧写即可。

理解命名规则：

- 1.uE220S000.spl.bin
1表示第1个烧写文件；u表示uBoot类型；      E表示执行地址，220表示2后面两个0; S表示存储地址；000表示不关注；
 
- 2.dE000S150.uboot.bin
 2表示第2个烧写文件；d表示Data类型；       E表示执行地址，000表示不关注;     S表示存储地址；150表示1后面五个0；
 
- 3.eE000S840.env.bin
 3表示第3个烧写文件；e表示Environment类型；E表示执行地址，000表示不关注;     S表示存储地址；840表示8后面四个0；
 
- 4.dE000S250.kernel.bin
 4表示第4个烧写文件；d表示Data类型；       E表示执行地址，000表示不关注;     S表示存储地址；250表示2后面五个0；
 
- 5.dE000S260.rootfs.bin
 5表示第5个烧写文件；d表示Data类型；       E表示执行地址，000表示不关注;     S表示存储地址；260表示2后面六个0；


#### 开发板购买地址
https://item.taobao.com/item.htm?spm=a230r.1.14.52.72f53ce7czs7mu&id=558199223440&ns=1&abbucket=8#detail&qq-pf-to=pcqq.temporaryc2c


#### 码云特技

1. 使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2. 码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3. 你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4. [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5. 码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6. 码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)