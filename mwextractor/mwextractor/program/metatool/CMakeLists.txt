set(META_TOOL_SRCS
	Module.cpp
	MatrixTupleStorageManager.cpp
	Config.cpp
	MetaTool.cpp
	main.cpp)
add_executable(MetaTool ${META_TOOL_SRCS})
target_link_libraries(MetaTool ${LIBS})
