project(NonogrammSolver)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(QT_FILES
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    mainwindow.qrc
    table.h
    table.cpp
)

set(SOURCE_FILES
    main.cpp
    ${QT_FILES}
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    levelChangeDialog/levelchangedialog.h
    levelChangeDialog/levelchangedialog.cpp
    levelChangeDialog/levelchangedialog.ui
    levelsManager/levelsDirectory.h
    levelsManager/levelsDirectory.cpp
    levelsManager/colorstore.h
    levelsManager/colorstore.cpp
    levelsManager/levelLoader.h
    levelsManager/levelLoader.cpp
    levelsManager/levelManager.h levelsManager/levelManager.cpp

)

add_subdirectory(core)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib)
