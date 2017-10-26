set(MINER_SRCS
	Config.cpp
	Miner.cpp
	main.cpp)
add_executable(Miner ${MINER_SRCS})
target_link_libraries(Miner ${LIBS})
