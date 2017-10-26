set(NORMALIZER_SRCS
	Config.cpp
	Normalizer.cpp
	main.cpp)
add_executable(Normalizer ${NORMALIZER_SRCS})
target_link_libraries(Normalizer ${LIBS})
