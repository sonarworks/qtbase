// Copyright (C) 2022 The Qt Company Ltd.
// Copyright (C) 2016 Kurt Pattyn <pattyn.kurt@gmail.com>.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

/*!
    \class QSslServer

    \ingroup network
    \ingroup ssl
    \inmodule QtNetwork
    \since 6.4

    \brief Implements an encrypted, secure TCP server over TLS.

    Class to use in place of QTcpServer to implement TCP server using
    Transport Layer Security (TLS).

    To configure the secure handshake settings, use the applicable setter
    functions on a QSslConfiguration object, and then use it as a argument
    to the setSslConfiguration() function. All following incoming
    connections handled will use these settings.

    To start listening to incoming connections use the listen() function
    inherited from QTcpServer. Other settings can be configured by using the
    setter functions inherited from the QTcpServer class.

    Connect to the signals of this class to respond to the incoming connection
    attempts. They are the same as the signals on QSslSocket, but also
    passes a pointer to the socket in question.

    When responding to the pendingConnectionAvailable() signal, use the
    nextPendingConnection() function to fetch the next incoming connection and
    take it out of the pending connection queue. The QSslSocket is a child of
    the QSslServer and will be deleted when the QSslServer is deleted. It is
    still a good a good idea to destroy the object explicitly when you are done
    with it, to avoid wasting memory.

    \sa QTcpServer, QSslConfiguration, QSslSocket
*/

/*!
    \fn void QSslServer::peerVerifyError(QSslSocket *socket, const QSslError &error)

    QSslServer can emit this signal several times during the SSL handshake,
    before encryption has been established, to indicate that an error has
    occurred while establishing the identity of the peer. The \a error is
    usually an indication that \a socket is unable to securely identify the
    peer.

    This signal provides you with an early indication when something's wrong.
    By connecting to this signal, you can manually choose to tear down the
    connection from inside the connected slot before the handshake has
    completed. If no action is taken, QSslServer will proceed to emitting
    sslErrors().

    \sa sslErrors()
*/

/*!
    \fn void QSslServer::sslErrors(QSslSocket *socket, const QList<QSslError> &errors);

    QSslServer emits this signal after the SSL handshake to indicate that one
    or more errors have occurred while establishing the identity of the
    peer. The errors are usually an indication that \a socket is unable to
    securely identify the peer. Unless any action is taken, the connection
    will be dropped after this signal has been emitted.

    If you want to continue connecting despite the errors that have occurred,
    you must call QSslSocket::ignoreSslErrors() from inside a slot connected to
    this signal. If you need to access the error list at a later point, you
    can call sslHandshakeErrors().

    \a errors contains one or more errors that prevent QSslSocket from
    verifying the identity of the peer.

    \note You cannot use Qt::QueuedConnection when connecting to this signal,
    or calling QSslSocket::ignoreSslErrors() will have no effect.

    \sa peerVerifyError()
*/

/*!
    \fn void QSslServer::errorOccurred(QSslSocket *socket, QAbstractSocket::SocketError socketError)

    This signal is emitted after an error occurred during handshake. The
    \a socketError parameter describes the type of error that occurred.

    The \a socket is automatically deleted after this signal is emitted if the
    socket handshake has not reached encrypted state. But if the \a socket is
    successfully encrypted, it is inserted into the QSslServer's pending
    connections queue. When the user has called
    QTcpServer::nextPendingConnection() it is the user's responsibility to
    destroy the \a socket or the \a socket will not be destroyed until the
    QSslServer object is destroyed. If an error occurs on a \a socket after
    it has been inserted into the pending connections queue, this signal
    will not be emitted, and the \a socket will not be removed or destroyed.

    \note You cannot use Qt::QueuedConnection when connecting to this signal,
    or the \a socket will have been already destroyed when the signal is
    handled.

    \sa QSslSocket::error(), errorString()
*/

/*!
    \fn void QSslServer::preSharedKeyAuthenticationRequired(QSslSocket *socket,
   QSslPreSharedKeyAuthenticator *authenticator)

    QSslServer emits this signal when \a socket negotiates a PSK ciphersuite,
    and therefore PSK authentication is then required.

    When using PSK, the server must supply a valid identity and a valid pre
    shared key, in order for the SSL handshake to continue.
    Applications can provide this information in a slot connected to this
    signal, by filling in the passed \a authenticator object according to their
    needs.

    \note Ignoring this signal, or failing to provide the required credentials,
    will cause the handshake to fail, and therefore the connection to be aborted.

    \note The \a authenticator object is owned by the \a socket and must not be
    deleted by the application.

    \sa QSslPreSharedKeyAuthenticator
*/

/*!
    \fn void QSslServer::alertSent(QSslSocket *socket, QSsl::AlertLevel level, QSsl::AlertType type,
   const QString &description)

    QSslServer emits this signal if an alert message was sent from \a socket
    to a peer. \a level describes if it was a warning or a fatal error.
    \a type gives the code of the alert message. When a textual description
    of the alert message is available, it is supplied in \a description.

    \note This signal is mostly informational and can be used for debugging
    purposes, normally it does not require any actions from the application.
    \note Not all backends support this functionality.

    \sa alertReceived(), QSsl::AlertLevel, QSsl::AlertType
*/

/*!
    \fn void QSslServer::alertReceived(QSslSocket *socket, QSsl::AlertLevel level, QSsl::AlertType
   type, const QString &description)

    QSslServer emits this signal if an alert message was received by the
    \a socket from a peer. \a level tells if the alert was fatal or it was a
    warning. \a type is the code explaining why the alert was sent.
    When a textual description of the alert message is available, it is
    supplied in \a description.

    \note The signal is mostly for informational and debugging purposes and does not
    require any handling in the application. If the alert was fatal, underlying
    backend will handle it and close the connection.
    \note Not all backends support this functionality.

    \sa alertSent(), QSsl::AlertLevel, QSsl::AlertType
*/

/*!
    \fn void QSslServer::handshakeInterruptedOnError(QSslSocket *socket, const QSslError &error)

    QSslServer emits this signal if a certificate verification error was found
    by \a socket and if early error reporting was enabled in QSslConfiguration.
    An application is expected to inspect the \a error and decide if it wants
    to continue the handshake, or abort it and send an alert message to the
    peer. The signal-slot connection must be direct.

    \sa QSslSocket::continueInterruptedHandshake(), sslErrors(),
   QSslConfiguration::setHandshakeMustInterruptOnError()
*/

#include "qsslserver.h"
#include "qsslserver_p.h"

#include <QtNetwork/QSslSocket>
#include <QtNetwork/QSslCipher>

QT_BEGIN_NAMESPACE

/*!
    \internal
*/
QSslServerPrivate::QSslServerPrivate() :
    sslConfiguration(QSslConfiguration::defaultConfiguration())
{
}

/*!
    Constructs a new QSslServer with the given \a parent.
*/
QSslServer::QSslServer(QObject *parent) :
    QTcpServer(QAbstractSocket::TcpSocket, *new QSslServerPrivate, parent)
{
}

/*!
    Destroys the QSslServer.

    All open connections are closed.
*/
QSslServer::~QSslServer()
{
}

/*!
    Sets the \a sslConfiguration to use for all following incoming connections.

    This must be called before listen() to ensure that the desired
    configuration was in use during all handshakes.

    \sa QSslSocket::setSslConfiguration()
*/
void QSslServer::setSslConfiguration(const QSslConfiguration &sslConfiguration)
{
    Q_D(QSslServer);
    d->sslConfiguration = sslConfiguration;
}

/*!
    Returns the current ssl configuration.
*/
QSslConfiguration QSslServer::sslConfiguration() const
{
    const Q_D(QSslServer);
    return d->sslConfiguration;
}

/*!
    Called when a new connection is established.

    Converts \a socket to a QSslSocket.

    \reimp
*/
void QSslServer::incomingConnection(qintptr socket)
{
    QSslSocket *pSslSocket = new QSslSocket(this);

    pSslSocket->setSslConfiguration(sslConfiguration());

    if (Q_LIKELY(pSslSocket->setSocketDescriptor(socket))) {
        connect(pSslSocket, &QSslSocket::peerVerifyError,
                [this, pSslSocket](const QSslError &error) {
                    Q_EMIT peerVerifyError(pSslSocket, error);
                });
        connect(pSslSocket, &QSslSocket::sslErrors,
                [this, pSslSocket](const QList<QSslError> &errors) {
                    Q_EMIT sslErrors(pSslSocket, errors);
                });
        connect(pSslSocket, &QAbstractSocket::errorOccurred,
                [this, pSslSocket](QAbstractSocket::SocketError error) {
                    Q_EMIT errorOccurred(pSslSocket, error);
                    if (!pSslSocket->isEncrypted())
                        pSslSocket->deleteLater();
                });
        connect(pSslSocket, &QSslSocket::encrypted, [this, pSslSocket]() {
            pSslSocket->disconnect();
            addPendingConnection(pSslSocket);
        });
        connect(pSslSocket, &QSslSocket::preSharedKeyAuthenticationRequired,
                [this, pSslSocket](QSslPreSharedKeyAuthenticator *authenticator) {
                    Q_EMIT preSharedKeyAuthenticationRequired(pSslSocket, authenticator);
                });
        connect(pSslSocket, &QSslSocket::alertSent,
                [this, pSslSocket](QSsl::AlertLevel level, QSsl::AlertType type,
                                   const QString &description) {
                    Q_EMIT alertSent(pSslSocket, level, type, description);
                });
        connect(pSslSocket, &QSslSocket::alertReceived,
                [this, pSslSocket](QSsl::AlertLevel level, QSsl::AlertType type,
                                   const QString &description) {
                    Q_EMIT alertReceived(pSslSocket, level, type, description);
                });
        connect(pSslSocket, &QSslSocket::handshakeInterruptedOnError,
                [this, pSslSocket](const QSslError &error) {
                    Q_EMIT handshakeInterruptedOnError(pSslSocket, error);
                });

        Q_EMIT startedEncryptionHandshake(pSslSocket);

        pSslSocket->startServerEncryption();
    }
}

QT_END_NAMESPACE
