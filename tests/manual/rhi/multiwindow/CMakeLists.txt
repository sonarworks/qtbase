# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from multiwindow.pro.

#####################################################################
## multiwindow Binary:
#####################################################################

qt_internal_add_manual_test(multiwindow
    GUI
    SOURCES
        multiwindow.cpp
    LIBRARIES
        Qt::Gui
        Qt::GuiPrivate
        Qt::Widgets
)

# Resources:
set_source_files_properties("../shared/color.frag.qsb"
    PROPERTIES QT_RESOURCE_ALIAS "color.frag.qsb"
)
set_source_files_properties("../shared/color.vert.qsb"
    PROPERTIES QT_RESOURCE_ALIAS "color.vert.qsb"
)
set(multiwindow_resource_files
    "../shared/color.frag.qsb"
    "../shared/color.vert.qsb"
)

qt_internal_add_resource(multiwindow "multiwindow"
    PREFIX
        "/"
    FILES
        ${multiwindow_resource_files}
)


#### Keys ignored in scope 1:.:.:multiwindow.pro:<TRUE>:
# TEMPLATE = "app"
