# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

qt_internal_add_manual_test(geometryshader
    GUI
    SOURCES
        geometryshader.cpp
    LIBRARIES
        Qt::Gui
        Qt::GuiPrivate
)

set(geometryshader_resource_files
    "test.vert.qsb"
    "test.geom.qsb"
    "test.frag.qsb"
)

qt_internal_add_resource(geometryshader "geometryshader"
    PREFIX
        "/"
    FILES
        ${geometryshader_resource_files}
)
