set(FEATURE_MAKER_SRCS
	Config.cpp
	FeatureMaker.cpp
	main.cpp)
add_executable(FeatureMaker ${FEATURE_MAKER_SRCS})
target_link_libraries(FeatureMaker ${LIBS})
