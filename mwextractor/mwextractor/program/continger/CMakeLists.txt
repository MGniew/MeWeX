set(CONTINGER_SRCS
        Config.cpp
        Continger.cpp
        main.cpp)
add_executable(Continger ${CONTINGER_SRCS})
target_link_libraries(Continger ${LIBS})
