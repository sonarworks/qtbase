# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

qt_commandline_option(mysql_config TYPE string)
qt_commandline_option(psql_config TYPE string)
qt_commandline_option(sqlite TYPE enum NAME system-sqlite MAPPING qt no system yes)
qt_commandline_option(sql-db2 TYPE boolean)
qt_commandline_option(sql-ibase TYPE boolean)
qt_commandline_option(sql-mysql TYPE boolean)
qt_commandline_option(sql-oci TYPE boolean)
qt_commandline_option(sql-odbc TYPE boolean)
qt_commandline_option(sql-psql TYPE boolean)
qt_commandline_option(sql-sqlite TYPE boolean)
qt_commandline_option(plugin-sql-db2 TYPE void NAME sql-db2)
qt_commandline_option(plugin-sql-ibase TYPE void NAME sql-ibase)
qt_commandline_option(plugin-sql-mysql TYPE void NAME sql-mysql)
qt_commandline_option(plugin-sql-oci TYPE void NAME sql-oci)
qt_commandline_option(plugin-sql-odbc TYPE void NAME sql-odbc)
qt_commandline_option(plugin-sql-psql TYPE void NAME sql-psql)
qt_commandline_option(plugin-sql-sqlite TYPE void NAME sql-sqlite)
