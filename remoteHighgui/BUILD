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
