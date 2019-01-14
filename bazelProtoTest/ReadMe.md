### 写在前面，决定在未来十来天的学习apollo的日子中，写写日记
### 2019/1/14
### 这个文件是如何在C++中使用bazel+protobuf
* [官网语法](https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary "官网语法")
* [protobuf语法](https://blog.csdn.net/boshuzhang/article/details/52816662 "protobuf语法")
* [bazel（不包括protobuf）官网教程]( https://docs.bazel.build/versions/master/tutorial/cpp.html "bazel（不包括protobuf）官网教程")

记得安装protobuf [教程](https://www.cnblogs.com/luoxn28/p/5303517.html "教程")
然后再下载[protobuf-3.6.1.2.zip](https://github.com/protocolbuffers/protobuf/releases/tag/v3.6.1.2 "protobuf-3.6.1.2.zip")
记得workspace中要添加
```
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
```
这句代码是在输出错误中复制的，找了很多教程都没有提到这个，没加这个之前怎么都编译不过，加了之后就正常了

再编写程序的时候好像可以直接默认protobuf已经将脚本转变为了.h文件和.cc文件了，直接#include可以使用，虽然是之后执行编译操作才生产的，但是并不会报错
，只是在想不就没有索引了吗。。大概只能从别的地方查语法，毕竟都是照一个模板生成的，只是ide无法智能提示，有点烦。

我自己编译会在当前路径下产生一堆附加文件，这个文件夹除了main和workspace外，其他都是自己生成的，可以在生成的文件夹中找到对应的protobuf生成的.h和.cc
以及各种所需要的奇奇怪怪的东西。

本来这一切都是为了apollo所准备的，经过一天的心灵上的冲击，骂了n遍bazel和protobuf后，最后终于跑起来了自己的例子，但是我在apollo中并没有找到我要找
的东西。
包括

* 找到很多的proto文件，但是没有找到其生成的.h和.cc
* 文件中有很多的proto文件，但是只看到了很少的一部分有调用对应的pb.h

以上的东西坑了我一天
