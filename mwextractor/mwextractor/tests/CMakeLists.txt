
find_package(Boost COMPONENTS program_options system)
link_directories(${Boost_LIBRARY_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

MESSAGE("Hello from the inside :)")

set(TEST_MEASURES_SRCS
	#Jaccard.cpp
	main.cpp)
add_executable(TestMeasures ${TEST_MEASURES_SRCS})
target_link_libraries(TestMeasures ${LIBS})
target_link_libraries(TestMeasures ${LIBS})