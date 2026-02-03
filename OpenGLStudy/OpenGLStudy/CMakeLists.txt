# OpenGLStudy target
cmake_minimum_required(VERSION 3.15)

# 源文件列表（根据实际文件调整）
set(OPENGLSTUDY_SOURCES
    main.cpp
    DrawTriangle.cpp
    DrawRect.cpp
    DrawWindow.cpp
    Shader.cpp
)

# glad 库（仓库内提供的 Source/src/glad.c 与头文件）
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/Source/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/Source/include")

# 可执行目标
add_executable(OpenGLStudy ${OPENGLSTUDY_SOURCES})

# 包含仓库内头文件路径
target_include_directories(OpenGLStudy PRIVATE
    "${CMAKE_SOURCE_DIR}/Source/include"
    "${CMAKE_CURRENT_SOURCE_DIR}" # 若需要访问本目录头文件
)

# 链接 glad
target_link_libraries(OpenGLStudy PRIVATE glad)

# 查找 GLFW（优先用 pkg-config，再 fallback 到 find_package）
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(GLFW_PKG REQUIRED glfw3)
    target_include_directories(OpenGLStudy PRIVATE ${GLFW_PKG_INCLUDE_DIRS})
    target_link_libraries(OpenGLStudy PRIVATE ${GLFW_PKG_LIBRARIES})
else()
    find_package(glfw3 3.3 REQUIRED)
    target_link_libraries(OpenGLStudy PRIVATE glfw)
endif()

# 查找 OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    target_include_directories(OpenGLStudy PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(OpenGLStudy PRIVATE ${OPENGL_LIBRARIES})
elseif(APPLE)
    # macOS 下备用链接
    target_link_libraries(OpenGLStudy PRIVATE "-framework OpenGL")
endif()

# 在 macOS/Xcode 下可能需要额外框架（通常由 glfw 提供），可根据需要取消注释：
# if(APPLE)
#     target_link_libraries(OpenGLStudy PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation")
# endif()

# 设置可执行文件输出目录（方便找到运行目录）
set_target_properties(OpenGLStudy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 把 ShaderFile 目录拷贝到可执行文件目录，保证运行时可以按相对路径加载着色器
add_custom_command(TARGET OpenGLStudy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/OpenGLStudy/ShaderFile"
    "$<TARGET_FILE_DIR:OpenGLStudy>/ShaderFile"
)