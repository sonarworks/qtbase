# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

if(QT_FEATURE_wizard)
    qt_internal_add_example(classwizard)
    qt_internal_add_example(trivialwizard)
endif()
qt_internal_add_example(extension)
qt_internal_add_example(findfiles)
qt_internal_add_example(standarddialogs)
qt_internal_add_example(tabdialog)
if(QT_FEATURE_wizard AND TARGET Qt::PrintSupport)
    qt_internal_add_example(licensewizard)
endif()
