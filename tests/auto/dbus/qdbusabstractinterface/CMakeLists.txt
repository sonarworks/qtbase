# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qdbusabstractinterface.pro.

add_subdirectory(qpinger)

# special case begin
qt_internal_add_test(tst_qdbusabstractinterface
    SOURCES
        interface.cpp
        tst_qdbusabstractinterface.cpp
    LIBRARIES
        Qt::Core
        Qt::DBus
)

qt_internal_extend_target(tst_qdbusabstractinterface
    DBUS_INTERFACE_SOURCES
        org.qtproject.QtDBus.Pinger.xml
    DBUS_INTERFACE_BASENAME
        pinger_interface
    DBUS_INTERFACE_FLAGS
        -i interface.h
)

# special case end
