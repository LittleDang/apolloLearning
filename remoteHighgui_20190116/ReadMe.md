### 20190116
1. 今天主要学习了如何使用外部库（类似像CMake调用本机安装了opencv），顺便用这个办法写了一套遥控器的控制UI,基本参考本文件就好了。基本上bazel资料相对比较少，不过官网有比较完整的资料，基本学习bazel只能够一边参考文档，一边看项目，一边模仿写项目[官网速递](https://docs.bazel.build/versions/master/bazel-overview.html)
2. 同时移植到了apollo里面，apollo里面的自己写了workspace和build那一块，自己只需要写一写自己文件的BUILD，不需要构建opencv的build，比较坑的是一开始的写法是
```
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "remote",
    srcs = ["src/remote.cpp"],
    hdrs = ["src/remote.h"],
)
cc_binary(
	name="remoteControl_gui",
	srcs=["src/main.cpp"],
	deps=[":remote",
	"@opencv2//:highgui",
	"@opencv2//:imgproc",
	"@opencv2//:core",
	"@opencv2//:video"],
)

cpplint()
```
但是程序编译没有任何问题，运行也可以运行一半，但是涉及到了ui的部分全部崩溃。

后来参考了apollo本身的写法，改了一下就可以运行了= =
```
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "remote",
    srcs = ["src/remote.cpp"],
    hdrs = ["src/remote.h"],
)
cc_binary(
	name="remoteControl_gui",
	srcs=["src/main.cpp"],
	linkopts = ["-lopencv_core -lopencv_imgproc -lopencv_highgui"],
	deps=[":remote"],
)

cpplint()
```
3. 顺便记录一下今天比较坑的几个问题
* opencv的cv::waitKey()的返回值要记得&255，猜测返回值是int，但是本身只赋值了后8个bit位，前面的24个bit看运气分配。
```c
int key=cv::waitKey(30)&255;
```
* -l，-L等都是GCC的一些编译参数，-l链接库，-L是指定库在哪里,[博客链接](https://blog.csdn.net/biqioso/article/details/80531835)
