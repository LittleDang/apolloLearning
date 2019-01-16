licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# This assumes you have opencv pre-installed in your system.
cc_library(
    name = "opencv",
    defines = ["OPENCV_NO_PRECOMPILE"],
    includes = ["."],
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lopencv_core",
        "-lopencv_imgproc",
        "-lopencv_highgui",
    ],
)
