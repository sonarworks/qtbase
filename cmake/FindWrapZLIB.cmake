# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

include(QtFindWrapHelper NO_POLICY_SCOPE)

qt_find_package_system_or_bundled(wrap_zlib
    FRIENDLY_PACKAGE_NAME "ZLIB"
    WRAP_PACKAGE_TARGET "WrapZLIB::WrapZLIB"
    WRAP_PACKAGE_FOUND_VAR_NAME "WrapZLIB_FOUND"
    BUNDLED_PACKAGE_NAME "BundledZLIB"
    BUNDLED_PACKAGE_TARGET "BundledZLIB"
    SYSTEM_PACKAGE_NAME "WrapSystemZLIB"
    SYSTEM_PACKAGE_TARGET "WrapSystemZLIB::WrapSystemZLIB"
)
