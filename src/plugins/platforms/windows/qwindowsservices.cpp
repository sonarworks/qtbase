// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#define QT_NO_URL_CAST_FROM_STRING
#include "qwindowsservices.h"
#include <QtCore/qt_windows.h>

#include <QtCore/qurl.h>
#include <QtCore/qdebug.h>
#include <QtCore/qdir.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qthread.h>

#include <QtCore/private/qwinregistry_p.h>

#include <shlobj.h>
#include <intshcut.h>

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

enum { debug = 0 };

class QWindowsShellExecuteThread : public QThread
{
public:
    explicit QWindowsShellExecuteThread(const wchar_t *path) : m_path(path) { }

    void run() override
    {
        if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) {
            m_result = ShellExecute(nullptr, nullptr, m_path, nullptr, nullptr, SW_SHOWNORMAL);
            CoUninitialize();
        }
    }

    HINSTANCE result() const { return m_result; }

private:
    HINSTANCE m_result = nullptr;
    const wchar_t *m_path;
};

static inline bool shellExecute(const QUrl &url)
{
    const QString nativeFilePath = url.isLocalFile() && !url.hasFragment() && !url.hasQuery()
        ? QDir::toNativeSeparators(url.toLocalFile())
        : url.toString(QUrl::FullyEncoded);


    // Run ShellExecute() in a thread since it may spin the event loop.
    // Prevent it from interfering with processing of posted events (QTBUG-85676).
    QWindowsShellExecuteThread thread(reinterpret_cast<const wchar_t *>(nativeFilePath.utf16()));
    thread.start();
    thread.wait();

    const auto result = reinterpret_cast<quintptr>(thread.result());

    // ShellExecute returns a value greater than 32 if successful
    if (result <= 32) {
        qWarning("ShellExecute '%ls' failed (error %zu).", qUtf16Printable(url.toString()), result);
        return false;
    }
    return true;
}

// Retrieve the commandline for the default mail client. It contains a
// placeholder %1 for the URL. The default key used below is the
// command line for the mailto: shell command.
static inline QString mailCommand()
{
    enum { BufferSize = sizeof(wchar_t) * MAX_PATH };

    const wchar_t mailUserKey[] = L"Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\mailto\\UserChoice";

    // Check if user has set preference, otherwise use default.
    QString keyName = QWinRegistryKey(HKEY_CURRENT_USER, mailUserKey)
                      .stringValue( L"Progid");
    const auto mailto = keyName.isEmpty() ? "mailto"_L1 : QLatin1StringView();
    keyName += mailto + "\\Shell\\Open\\Command"_L1;
    if (debug)
        qDebug() << __FUNCTION__ << "keyName=" << keyName;
    const QString command = QWinRegistryKey(HKEY_CLASSES_ROOT, keyName).stringValue(L"");
    // QTBUG-57816: As of Windows 10, if there is no mail client installed, an entry like
    // "rundll32.exe .. url.dll,MailToProtocolHandler %l" is returned. Launching it
    // silently fails or brings up a broken dialog after a long time, so exclude it and
    // fall back to ShellExecute() which brings up the URL association dialog.
    if (command.isEmpty() || command.contains(u",MailToProtocolHandler"))
        return QString();
    wchar_t expandedCommand[MAX_PATH] = {0};
    return ExpandEnvironmentStrings(reinterpret_cast<const wchar_t *>(command.utf16()),
                                    expandedCommand, MAX_PATH)
        ? QString::fromWCharArray(expandedCommand) : command;
}

static inline bool launchMail(const QUrl &url)
{
    QString command = mailCommand();
    if (command.isEmpty()) {
        qWarning("Cannot launch '%ls': There is no mail program installed.", qUtf16Printable(url.toString()));
        return false;
    }
    //Make sure the path for the process is in quotes
    const QChar doubleQuote = u'"';
    if (!command.startsWith(doubleQuote)) {
        const int exeIndex = command.indexOf(QStringLiteral(".exe "), 0, Qt::CaseInsensitive);
        if (exeIndex != -1) {
            command.insert(exeIndex + 4, doubleQuote);
            command.prepend(doubleQuote);
        }
    }
    // Pass the url as the parameter. Should use QProcess::startDetached(),
    // but that cannot handle a Windows command line [yet].
    command.replace("%1"_L1, url.toString(QUrl::FullyEncoded));
    if (debug)
        qDebug() << __FUNCTION__ << "Launching" << command;
    //start the process
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    if (!CreateProcess(nullptr, reinterpret_cast<wchar_t *>(const_cast<ushort *>(command.utf16())),
                       nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        qErrnoWarning("Unable to launch '%ls'", qUtf16Printable(command));
        return false;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}

bool QWindowsServices::openUrl(const QUrl &url)
{
    const QString scheme = url.scheme();
    if (scheme == u"mailto" && launchMail(url))
        return true;
    return shellExecute(url);
}

bool QWindowsServices::openDocument(const QUrl &url)
{
    return shellExecute(url);
}

QT_END_NAMESPACE
