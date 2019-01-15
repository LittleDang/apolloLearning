proto_library(
	name="test_lib",
	srcs=[
	"test.proto",
	],
)
cc_proto_library(
	name="test",
	deps=[
	":test_lib",
	],
)
cc_binary(
	name="main",
	srcs=["main.cc"],
	deps=[":test"],

)
