# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0


# The module finds its dependencies
find_package(Qt6 6.0.0
             COMPONENTS Core
    OPTIONAL_COMPONENTS DoesNotExist
)

if (NOT Qt6_FOUND)
    message(SEND_ERROR "Qt6 umbrella package not found!")
endif()

if (NOT Qt6Core_FOUND)
    message(SEND_ERROR "Qt6Core package not found!")
endif()

if (Qt6DoesNotExist_FOUND)
    message(SEND_ERROR "Non-existent package found!")
endif()
