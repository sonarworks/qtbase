# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qstringconverter.pro.

#####################################################################
## tst_qstringconverter Test:
#####################################################################

qt_internal_add_test(tst_qstringconverter
    SOURCES
        tst_qstringconverter.cpp
    TESTDATA ${test_data}
    LIBRARIES
        Qt::CorePrivate # for access to Qt's feature system
)


qt_internal_add_resource(tst_qstringconverter  "compressedtexture_bc1"
    PREFIX
        "/"
    FILES
        "euc_kr.txt"
)
