set(REDUCTOR_SRCS
	Config.cpp
	Reductor.cpp
	main.cpp)
add_executable(Reductor ${REDUCTOR_SRCS})
target_link_libraries(Reductor ${LIBS})
