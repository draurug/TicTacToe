cmake_minimum_required(VERSION 3.5)

project(TicTacToe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSTANDALONE_TEST)
set(PROJECT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Server-Lessons/EasyTcpServerClient)
add_subdirectory(Server-Lessons/EasyTcpServerClient)


if (APPLE)
    set(CMAKE_PREFIX_PATH "~/Qt/6.4.0/macos")

    add_definitions(-DBOOST_ASIO_HAS_STD_INVOKE_RESULT)
#    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
#    set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")

    # for -lcrypto (I do not know who uses it!)
#    link_directories(/usr/local/opt/openssl/lib)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Boost)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Boost 1.70 REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        Scene.h
        Scene.cpp
        Model.h
        Model.cpp
        Settings.cpp
        Settings.h
        Logic.h
        Logic.cpp
        SettingsDialog.h
        SettingsDialog.cpp
        SettingsDialog.ui

        WaitingInvitationResponseDialog.h
        WaitingInvitationResponseDialog.cpp
        WaitingInvitationResponseDialog.ui

        InviteDialog.h
        InviteDialog.cpp
        InviteDialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TicTacToe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(TicTacToe SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TicTacToe
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TicTacToe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TicTacToe)
endif()
set_target_properties(TicTacToe PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set(PROJECT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCES_DIR})

include(GNUInstallDirs)
install(TARGETS TicTacToe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(TicTacToe PRIVATE ${Boost_INCLUDE_DIRS})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TicTacToe)
endif()

