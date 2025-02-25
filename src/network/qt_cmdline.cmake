# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

qt_commandline_option(libproxy TYPE boolean)
qt_commandline_option(openssl TYPE optionalString VALUES no yes linked runtime)
qt_commandline_option(openssl-linked TYPE void NAME openssl VALUE linked)
qt_commandline_option(openssl-runtime TYPE void NAME openssl VALUE runtime)
qt_commandline_option(dtls TYPE boolean)
qt_commandline_option(ocsp TYPE boolean)
qt_commandline_option(sctp TYPE boolean)
qt_commandline_option(securetransport TYPE boolean)
qt_commandline_option(schannel TYPE boolean)
qt_commandline_option(ssl TYPE boolean)
qt_commandline_option(system-proxies TYPE boolean)
qt_commandline_option(publicsuffix TYPE optionalString VALUES system qt no all)
