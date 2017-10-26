set(TUPLES_BUILDER_SRCS
	Config.cpp
	TuplesBuilder.cpp
	main.cpp)
add_executable(TuplesBuilder ${TUPLES_BUILDER_SRCS})
target_link_libraries(TuplesBuilder ${LIBS})
