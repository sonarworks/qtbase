# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from clipboard.pro.

#####################################################################
## clipboard Binary:
#####################################################################

qt_internal_add_manual_test(clipboard
    GUI
    SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)
# Resources:
set(data_resource_files
    "data/qticon64.png"
)

qt_internal_add_resource(clipboard "data"
    PREFIX
        "/"
    FILES
        ${data_resource_files}
)

## Scopes:
#####################################################################

qt_internal_extend_target(clipboard CONDITION (QT_MAJOR_VERSION GREATER 4)
    LIBRARIES
        Qt::Widgets
)

#### Keys ignored in scope 3:.:.:clipboard.pro:QNX:
# target.path = "/tmp/$${TARGET}/bin"

#### Keys ignored in scope 5:.:.:clipboard.pro:UNIX AND NOT ANDROID:
# target.path = "/opt/$${TARGET}/bin"

#### Keys ignored in scope 6:.:.:clipboard.pro:NOT target.path_ISEMPTY:
# INSTALLS = "target"
