# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qgraphicssceneindex.pro.

if(NOT QT_FEATURE_private_tests)
    return()
endif()

#####################################################################
## tst_qgraphicssceneindex Test:
#####################################################################

qt_internal_add_test(tst_qgraphicssceneindex
    SOURCES
        tst_qgraphicssceneindex.cpp
    LIBRARIES
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        Qt::Widgets
        Qt::WidgetsPrivate
)

#### Keys ignored in scope 1:.:.:qgraphicssceneindex.pro:<TRUE>:
# _REQUIREMENTS = "qtConfig(private_tests)"
