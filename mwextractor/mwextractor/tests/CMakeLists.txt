
find_package(Boost COMPONENTS unit_test_framework)
link_directories(${Boost_LIBRARY_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

# ADD_DEFINITIONS(-DBOOST_TEST_MAIN)
# ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

set(TEST_MEASURES_SRCS
	#Jaccard.cpp
	main.cpp)

add_executable(TestMeasures ${TEST_MEASURES_SRCS})
target_link_libraries(TestMeasures ${LIBS})