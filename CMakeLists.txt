cmake_minimum_required(VERSION 3.19)
project(Connect4 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Svg SvgWidgets)

qt_standard_project_setup()

qt_add_executable(Connect4
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    BaseScreen.h
    BaseScreen.cpp
    StartScreen.h
    StartScreen.cpp
    ConfigScreen.h
    ConfigScreen.cpp
    GameScreen.h
    GameScreen.cpp
    BoardWidget.h
    BoardWidget.cpp
    Color.h
    BoardConfig.h
)

qt_add_resources(Connect4 "resources"
    PREFIX "/"
    FILES assets/logo.svg
)

target_link_libraries(Connect4
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Svg
        Qt::SvgWidgets
)

install(TARGETS Connect4
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Connect4
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
