# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from db2.pro.

#####################################################################
## QDB2DriverPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QDB2DriverPlugin
    OUTPUT_NAME qsqldb2
    PLUGIN_TYPE sqldrivers
    SOURCES
        main.cpp
        qsql_db2.cpp qsql_db2_p.h
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        DB2::DB2
        Qt::Core
        Qt::CorePrivate
        Qt::SqlPrivate
)

#### Keys ignored in scope 1:.:.:db2.pro:<TRUE>:
# OTHER_FILES = "db2.json"

## Scopes:
#####################################################################

qt_internal_extend_target(QDB2DriverPlugin CONDITION (TEST_architecture_arch STREQUAL "x86_64")
    DEFINES
        ODBC64
)

qt_internal_force_macos_intel_arch(QDB2DriverPlugin)
