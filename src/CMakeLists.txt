project(mainApp)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCE_FILES
	main.cpp
        mainwindow.h
	mainwindow.cpp
	mainwindow.ui
	mainwindow.qrc
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
)

add_subdirectory(core)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE CoreLib)
