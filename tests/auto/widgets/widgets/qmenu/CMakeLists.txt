# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qmenu.pro.

#####################################################################
## tst_qmenu Test:
#####################################################################

qt_internal_add_test(tst_qmenu
    SOURCES
        tst_qmenu.cpp
    LIBRARIES
        Qt::Gui
        Qt::GuiPrivate
        Qt::TestPrivate
        Qt::Widgets
)

## Scopes:
#####################################################################

qt_internal_extend_target(tst_qmenu CONDITION MACOS
    SOURCES
        tst_qmenu_mac.mm
    LIBRARIES
        objc
)

qt_internal_extend_target(tst_qmenu CONDITION NOT MACOS
    DEFINES
        QTEST_QPA_MOUSE_HANDLING
)
