# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from qimagereader.pro.

#####################################################################
## tst_bench_qimagereader Binary:
#####################################################################

qt_internal_add_benchmark(tst_bench_qimagereader
    SOURCES
        tst_qimagereader.cpp
    LIBRARIES
        Qt::Gui
        Qt::Test
)

#### Keys ignored in scope 1:.:.:qimagereader.pro:<TRUE>:
# QT_FOR_CONFIG = "gui-private"
# TEMPLATE = "app"
# TESTDATA = "images/*"

## Scopes:
#####################################################################

qt_internal_extend_target(tst_bench_qimagereader CONDITION QT_FEATURE_gif
    DEFINES
        QTEST_HAVE_GIF
)

qt_internal_extend_target(tst_bench_qimagereader CONDITION QT_FEATURE_jpeg
    DEFINES
        QTEST_HAVE_JPEG
)
