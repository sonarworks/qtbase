// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qgtk3theme.h"
#include "qgtk3dialoghelpers.h"
#include "qgtk3menu.h"
#include <QVariant>
#include <QtCore/qregularexpression.h>
#include <QGuiApplication>

#undef signals
#include <gtk/gtk.h>

#if QT_CONFIG(xcb_xlib)
#include <X11/Xlib.h>
#endif

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

const char *QGtk3Theme::name = "gtk3";

template <typename T>
static T gtkSetting(const gchar *propertyName)
{
    GtkSettings *settings = gtk_settings_get_default();
    T value;
    g_object_get(settings, propertyName, &value, NULL);
    return value;
}

static QString gtkSetting(const gchar *propertyName)
{
    gchararray value = gtkSetting<gchararray>(propertyName);
    QString str = QString::fromUtf8(value);
    g_free(value);
    return str;
}

void gtkMessageHandler(const gchar *log_domain,
                       GLogLevelFlags log_level,
                       const gchar *message,
                       gpointer unused_data) {
    /* Silence false-positive Gtk warnings (we are using Xlib to set
     * the WM_TRANSIENT_FOR hint).
     */
    if (g_strcmp0(message, "GtkDialog mapped without a transient parent. "
                           "This is discouraged.") != 0) {
        /* For other messages, call the default handler. */
        g_log_default_handler(log_domain, log_level, message, unused_data);
    }
}

QGtk3Theme::QGtk3Theme()
{
    // Ensure gtk uses the same windowing system, but let it
    // fallback in case GDK_BACKEND environment variable
    // filters the preferred one out
    if (QGuiApplication::platformName().startsWith("wayland"_L1))
        gdk_set_allowed_backends("wayland,x11");
    else if (QGuiApplication::platformName() == "xcb"_L1)
        gdk_set_allowed_backends("x11,wayland");

#if QT_CONFIG(xcb_xlib)
    // gtk_init will reset the Xlib error handler, and that causes
    // Qt applications to quit on X errors. Therefore, we need to manually restore it.
    int (*oldErrorHandler)(Display *, XErrorEvent *) = XSetErrorHandler(nullptr);
#endif

    gtk_init(nullptr, nullptr);

#if QT_CONFIG(xcb_xlib)
    XSetErrorHandler(oldErrorHandler);
#endif

    /* Initialize some types here so that Gtk+ does not crash when reading
     * the treemodel for GtkFontChooser.
     */
    g_type_ensure(PANGO_TYPE_FONT_FAMILY);
    g_type_ensure(PANGO_TYPE_FONT_FACE);

    /* Use our custom log handler. */
    g_log_set_handler("Gtk", G_LOG_LEVEL_MESSAGE, gtkMessageHandler, nullptr);
}

static inline QVariant gtkGetLongPressTime()
{
    const char *gtk_long_press_time = "gtk-long-press-time";
    static bool found = g_object_class_find_property(G_OBJECT_GET_CLASS(gtk_settings_get_default()), gtk_long_press_time);
    if (!found)
        return QVariant();
    return QVariant(gtkSetting<guint>(gtk_long_press_time));  // Since 3.14, apparently we support >= 3.6
}

QVariant QGtk3Theme::themeHint(QPlatformTheme::ThemeHint hint) const
{
    switch (hint) {
    case QPlatformTheme::CursorFlashTime:
        return QVariant(gtkSetting<gint>("gtk-cursor-blink-time"));
    case QPlatformTheme::MouseDoubleClickDistance:
        return QVariant(gtkSetting<gint>("gtk-double-click-distance"));
    case QPlatformTheme::MouseDoubleClickInterval:
        return QVariant(gtkSetting<gint>("gtk-double-click-time"));
    case QPlatformTheme::MousePressAndHoldInterval: {
        QVariant v = gtkGetLongPressTime();
        if (!v.isValid())
            v = QGnomeTheme::themeHint(hint);
        return v;
    }
    case QPlatformTheme::PasswordMaskDelay:
        return QVariant(gtkSetting<guint>("gtk-entry-password-hint-timeout"));
    case QPlatformTheme::StartDragDistance:
        return QVariant(gtkSetting<gint>("gtk-dnd-drag-threshold"));
    case QPlatformTheme::SystemIconThemeName:
        return QVariant(gtkSetting("gtk-icon-theme-name"));
    case QPlatformTheme::SystemIconFallbackThemeName:
        return QVariant(gtkSetting("gtk-fallback-icon-theme"));
    case QPlatformTheme::PreselectFirstFileInDirectory:
        return true;
    default:
        return QGnomeTheme::themeHint(hint);
    }
}

QString QGtk3Theme::gtkFontName() const
{
    QString cfgFontName = gtkSetting("gtk-font-name");
    if (!cfgFontName.isEmpty())
        return cfgFontName;
    return QGnomeTheme::gtkFontName();
}

QPlatformTheme::Appearance QGtk3Theme::appearance() const
{
    /*
        https://docs.gtk.org/gtk3/running.html

        It's possible to set a theme variant after the theme name when using GTK_THEME:

            GTK_THEME=Adwaita:dark

        Some themes also have "-dark" as part of their name.

        We test this environment variable first because the documentation says
        it's mainly used for easy debugging, so it should be possible to use it
        to override any other settings.
    */
    QString themeName = qEnvironmentVariable("GTK_THEME");
    const QRegularExpression darkRegex(QStringLiteral("[:-]dark"), QRegularExpression::CaseInsensitiveOption);
    if (!themeName.isEmpty())
        return darkRegex.match(themeName).hasMatch() ? Appearance::Dark : Appearance::Light;

    /*
        https://docs.gtk.org/gtk3/property.Settings.gtk-application-prefer-dark-theme.html

        This setting controls which theme is used when the theme specified by
        gtk-theme-name provides both light and dark variants. We can save a
        regex check by testing this property first.
    */
    const auto preferDark = gtkSetting<bool>("gtk-application-prefer-dark-theme");
    if (preferDark)
        return Appearance::Dark;

    /*
        https://docs.gtk.org/gtk3/property.Settings.gtk-theme-name.html
    */
    themeName = gtkSetting("gtk-theme-name");
    if (!themeName.isEmpty())
        return darkRegex.match(themeName).hasMatch() ? Appearance::Dark : Appearance::Light;

    return Appearance::Unknown;
}

bool QGtk3Theme::usePlatformNativeDialog(DialogType type) const
{
    switch (type) {
    case ColorDialog:
        return true;
    case FileDialog:
        return useNativeFileDialog();
    case FontDialog:
        return true;
    default:
        return false;
    }
}

QPlatformDialogHelper *QGtk3Theme::createPlatformDialogHelper(DialogType type) const
{
    switch (type) {
    case ColorDialog:
        return new QGtk3ColorDialogHelper;
    case FileDialog:
        if (!useNativeFileDialog())
            return nullptr;
        return new QGtk3FileDialogHelper;
    case FontDialog:
        return new QGtk3FontDialogHelper;
    default:
        return nullptr;
    }
}

QPlatformMenu* QGtk3Theme::createPlatformMenu() const
{
    return new QGtk3Menu;
}

QPlatformMenuItem* QGtk3Theme::createPlatformMenuItem() const
{
    return new QGtk3MenuItem;
}

bool QGtk3Theme::useNativeFileDialog()
{
    /* Require GTK3 >= 3.15.5 to avoid running into this bug:
     * https://bugzilla.gnome.org/show_bug.cgi?id=725164
     *
     * While this bug only occurs when using widget-based file dialogs
     * (native GTK3 dialogs are fine) we have to disable platform file
     * dialogs entirely since we can't avoid creation of a platform
     * dialog helper.
     */
    return gtk_check_version(3, 15, 5) == nullptr;
}

QT_END_NAMESPACE
