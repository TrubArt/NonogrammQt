project(NonogrammSolver)

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
    levelChangeDlg/levelchangedialog.h
    levelChangeDlg/levelchangedialog.cpp
    levelChangeDlg/levelchangedialog.ui
    levelsDirectory/levelsDirectory.h
    levelsDirectory/levelsDirectory.cpp
)

add_subdirectory(core)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib)
