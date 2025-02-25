# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0


set(java_sources
    jar/src/org/qtproject/qt/android/networkinformation/QtAndroidNetworkInformation.java
)

qt_internal_add_jar(Qt${QtBase_VERSION_MAJOR}AndroidNetworkInformationBackend
    INCLUDE_JARS ${QT_ANDROID_JAR}
    SOURCES ${java_sources}
    OUTPUT_DIR "${QT_BUILD_DIR}/jar"
)

install_jar(Qt${QtBase_VERSION_MAJOR}AndroidNetworkInformationBackend
    DESTINATION jar
    COMPONENT Devel
)

qt_internal_add_plugin(QAndroidNetworkInformationPlugin
    OUTPUT_NAME qandroidnetworkinformation
    CLASS_NAME QAndroidNetworkInformationBackendFactory
    PLUGIN_TYPE networkinformation
    DEFAULT_IF ANDROID
    SOURCES
        qandroidnetworkinformationbackend.cpp
        wrapper/androidconnectivitymanager.cpp wrapper/androidconnectivitymanager.h
    LIBRARIES
        Qt::NetworkPrivate
    DEFINES
        QT_USE_QSTRINGBUILDER
)

set_property(
    TARGET
        QAndroidNetworkInformationPlugin
    APPEND PROPERTY QT_ANDROID_BUNDLED_JAR_DEPENDENCIES
        jar/Qt${QtBase_VERSION_MAJOR}AndroidNetworkInformationBackend.jar
)

set_property(
    TARGET
        QAndroidNetworkInformationPlugin
    APPEND PROPERTY QT_ANDROID_PERMISSIONS
        android.permission.ACCESS_NETWORK_STATE
)
