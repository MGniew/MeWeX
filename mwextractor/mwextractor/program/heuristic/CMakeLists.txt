set(HEURISTIC_SRC
        Config.cpp
        Heuristic.cpp
        main.cpp)
add_executable(Heuristic ${HEURISTIC_SRC})
target_link_libraries(Heuristic ${LIBS})
