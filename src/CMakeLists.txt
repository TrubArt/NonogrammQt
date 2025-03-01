project(mainApp)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(QT_FILES
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    mainwindow.qrc
    colorstore.h
    colorstore.cpp
    table.h
    table.cpp
)

set(SOURCE_FILES
    main.cpp
    ${QT_FILES}
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
)

add_subdirectory(core)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib)
