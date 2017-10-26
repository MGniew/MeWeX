set(INDEXER_SRCS
        Config.cpp
        Indexer.cpp
        main.cpp)
add_executable(Indexer ${INDEXER_SRCS})
target_link_libraries(Indexer ${LIBS})
