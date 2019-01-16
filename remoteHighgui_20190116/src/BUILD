cc_library(
    name = "remote",
    srcs = ["remote.cpp"],
    hdrs = ["remote.h"],
)
cc_binary(
	name="main",
	srcs=["main.cpp"],
	deps=[":remote",
	"@opencv//:opencv"],
)
