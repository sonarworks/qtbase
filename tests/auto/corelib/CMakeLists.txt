# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from corelib.pro.

add_subdirectory(kernel)
if(NOT UIKIT)
    add_subdirectory(animation)
    add_subdirectory(global)
    add_subdirectory(io)
    add_subdirectory(itemmodels)
    add_subdirectory(mimetypes)
    add_subdirectory(plugin)
    add_subdirectory(serialization)
    add_subdirectory(text)
    add_subdirectory(thread)
    add_subdirectory(time)
    add_subdirectory(tools)
endif()
add_subdirectory(platform)
