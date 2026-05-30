cmake_minimum_required(VERSION 3.20)
project(team14_game VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)

find_package(OpenGL REQUIRED)

set(IMGUI_DIR      ${CMAKE_SOURCE_DIR}/src/imgui)
set(IMGUI_SFML_DIR ${CMAKE_SOURCE_DIR}/src/imgui-sfml)

file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE ASSETS "assets/*")

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${ASSETS}

    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    ${IMGUI_SFML_DIR}/imgui-SFML.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    ${IMGUI_DIR}
    ${IMGUI_SFML_DIR}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
    ${OPENGL_LIBRARIES}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)