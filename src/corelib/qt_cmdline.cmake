# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

qt_commandline_option(doubleconversion TYPE enum VALUES no qt system)
qt_commandline_option(eventfd TYPE boolean)
qt_commandline_option(glib TYPE boolean)
qt_commandline_option(icu TYPE boolean)
qt_commandline_option(inotify TYPE boolean)
qt_commandline_option(journald TYPE boolean)
qt_commandline_option(libb2 TYPE enum VALUES no qt system)
qt_commandline_option(mimetype-database TYPE boolean)
qt_commandline_option(pcre TYPE enum VALUES no qt system)
qt_commandline_option(posix-ipc TYPE boolean NAME ipc_posix)
qt_commandline_option(pps TYPE boolean NAME qqnx_pps)
qt_commandline_option(slog2 TYPE boolean)
qt_commandline_option(syslog TYPE boolean)
qt_commandline_option(trace TYPE optionalString VALUES etw lttng no yes)
