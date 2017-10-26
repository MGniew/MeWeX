set(WEB_TOOL_SRCS
        Config.cpp
        WebTool.cpp
        main.cpp)
add_executable(WebTool ${WEB_TOOL_SRCS})
target_link_libraries(WebTool ${LIBS})