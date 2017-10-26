set(COVER_SRCS
	Config.cpp
	Cover.cpp
	main.cpp)
add_executable(Cover ${COVER_SRCS})
target_link_libraries(Cover ${LIBS})
