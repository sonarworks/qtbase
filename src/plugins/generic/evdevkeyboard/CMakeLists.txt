# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from evdevkeyboard.pro.

#####################################################################
## QEvdevKeyboardPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QEvdevKeyboardPlugin
    OUTPUT_NAME qevdevkeyboardplugin
    PLUGIN_TYPE generic
    DEFAULT_IF FALSE
    SOURCES
        main.cpp
    LIBRARIES
        Qt::Core
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        Qt::InputSupportPrivate
)

#### Keys ignored in scope 1:.:.:evdevkeyboard.pro:<TRUE>:
# OTHER_FILES = "evdevkeyboard.json"
# PLUGIN_EXTENDS = "-"
