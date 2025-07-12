cmake_minimum_required(VERSION 3.16)

project(3DViewner VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置自动生成的文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置Qt自动生成的moc、uic、rcc文件的输出目录
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt包
find_package(Qt6 COMPONENTS Core Gui Widgets 3DCore 3DRender 3DExtras 3DInput 3DLogic REQUIRED)

# 设置源文件
set(SOURCES
    main.cpp
    AppWindow.cpp
    Entity.cpp
    EntityPrivate.cpp
    KeyNode.cpp
    Logger.cpp
    MeshEntity.cpp
    MeshEntityPrivate.cpp
    PointLightEntity.cpp
    PointLightEntityPrivate.cpp
    Qt3DView.cpp
    TransformEntity.cpp
    TransformEntityPrivate.cpp
    WASDControllerPrivate.cpp
    WASDRotateController.cpp
    WASDTranslateController.cpp
)

# 设置头文件
set(HEADERS
    AppWindow.h
    Entity.h
    EntityPrivate.h
    KeyNode.h
    Logger.h
    MeshEntity.h
    MeshEntityPrivate.h
    PointLightEntity.h
    PointLightEntityPrivate.h
    Qt3DView.h
    TransformEntity.h
    TransformEntityPrivate.h
    WASDControllerPrivate.h
    WASDRotateController.h
    WASDTranslateController.h
)

# 添加可执行文件
add_executable(3DViewner
    ${SOURCES}
    ${HEADERS}
)

# 设置包含目录
target_include_directories(3DViewner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接Qt库
target_link_libraries(3DViewner PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DExtras
    Qt6::3DInput
    Qt6::3DLogic
)

# Windows特定设置
if(WIN32)
    # 设置Windows应用程序属性
    set_target_properties(3DViewner PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# 安装规则
if(WIN32)
    install(TARGETS 3DViewner DESTINATION .)
else()
    install(TARGETS 3DViewner DESTINATION bin)
endif() 
