cmake_minimum_required(VERSION 3.16)
project(113789742_pa1)
set(CMAKE_CXX_STANDARD 17)

# packages to find

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# all sources

set(GLAD
        include/glad/glad.h
        include/KHR/khrplatform.h
        src/glad/glad.c
        )

set(GLOBAL
        include/global/Context.h
        include/global/Utils.h
        src/global/Context.cpp
        src/global/Utils.cpp
        )

set(SHADER
        include/shader/Shader.h
        )

set(SHAPE
        include/shape/Circle.h
        include/shape/CubicCurve.h
        include/shape/Ellipse.h
        include/shape/LineSegment.h
        include/shape/Shape.h
        src/shape/Circle.cpp
        src/shape/CubicCurve.cpp
        src/shape/Ellipse.cpp
        src/shape/LineSegment.cpp
        src/shape/Shape.cpp
        )

set(ALL_INCLUDE_DIRS
        ${GLEW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${OPENGL_EGL_INCLUDE_DIRS}
        include
        )

set(ALL_SOURCE_FILES
        ${GLAD}
        ${GLOBAL}
        ${SHADER}
        ${SHAPE}
        src/main.cpp
        )

set(ALL_LIBRARIES
        dl
        GLEW::GLEW
        glfw
        OpenGL::GL
        OpenGL::OpenGL
        OpenGL::GLU
        OpenGL::GLX
        OpenGL::EGL
        pthread
        )

# all definitions and options

set(ALL_COMPILE_DEFS
        # -DDEBUG_LINE_SEGMENT
        )

set(ALL_COMPILE_OPTS

        )

# executable target(s)

add_executable(pa1 ${ALL_SOURCE_FILES})
target_compile_definitions(pa1 PUBLIC ${ALL_COMPILE_DEFS})
target_compile_options(pa1 PUBLIC ${ALL_COMPILE_OPTS})
target_include_directories(pa1 PUBLIC ${ALL_INCLUDE_DIRS})
target_link_libraries(pa1 ${ALL_LIBRARIES})

