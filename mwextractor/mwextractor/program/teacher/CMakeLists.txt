set(TEACHER_SRCS
	Config.cpp
	Teacher.cpp
	main.cpp)
add_executable(Teacher ${TEACHER_SRCS})
target_link_libraries(Teacher ${LIBS})
