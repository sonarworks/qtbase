# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

cmake_minimum_required(VERSION 3.16)
project(setmarkdown LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

qt_add_executable(setmarkdown
    main.cpp
)

target_link_libraries(setmarkdown PUBLIC
    Qt::Core
    Qt::Gui
)
if(DEFINED ENV{LIB_FUZZING_ENGINE})
    target_link_libraries(setmarkdown PRIVATE
        $ENV{LIB_FUZZING_ENGINE}
    )
else()
    target_link_libraries(setmarkdown PRIVATE
        -fsanitize=fuzzer
    )
endif()

qt_import_plugins(setmarkdown
    INCLUDE Qt::QMinimalIntegrationPlugin
)
