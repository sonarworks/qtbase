# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

# Generated from access.pro.

add_subdirectory(qnetworkdiskcache)
add_subdirectory(qnetworkcookiejar)
add_subdirectory(qnetworkaccessmanager)
add_subdirectory(qnetworkcookie)
add_subdirectory(qnetworkrequest)
add_subdirectory(qnetworkreply)
add_subdirectory(qnetworkcachemetadata)
add_subdirectory(qabstractnetworkcache)
if(QT_FEATURE_private_tests)
    add_subdirectory(qhttpheaderparser)
    add_subdirectory(qhttpnetworkconnection)
    add_subdirectory(qhttpnetworkreply)
    add_subdirectory(hpack)
    add_subdirectory(http2)
    add_subdirectory(hsts)
    add_subdirectory(qdecompresshelper)
endif()
