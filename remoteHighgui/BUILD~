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