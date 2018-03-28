/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef LANTRANSPORT_H
#define LANTRANSPORT_H

#include "config.h"

#include <QHostAddress>
#include <QTcpSocket>

#ifdef ENABLE_TLS
#  include <QSslConfiguration>
#  include <QSslSocket>
#endif

#include <nitroshare/transport.h>

class Packet;

/**
 * @brief Local network transport
 *
 * This class facilitates transfers between devices on a local network. This
 * consists of simple TCP connections.
 */
class LanTransport : public Transport
{
    Q_OBJECT

public:

    LanTransport(
        const QHostAddress &address
      , quint16 port
#ifdef ENABLE_TLS
      , const QSslConfiguration &sslConf
#endif
    );

    LanTransport(
        qintptr socketDescriptor
#ifdef ENABLE_TLS
      , const QSslConfiguration &sslConf
#endif
    );

    virtual void sendPacket(Packet *packet);
    virtual void close();

private slots:

    void onConnected();
    void onReadyRead();
    void onBytesWritten();
    void onError();

#ifdef ENABLE_TLS
    void onEncrypted();
    void onSslErrors();
#endif

private:

    LanTransport(
#ifdef ENABLE_TLS
        const QSslConfiguration &sslConf
#endif
    );

    QTcpSocket *mSocket;
#ifdef ENABLE_TLS
    QSslSocket *mSslSocket;
#endif

    QByteArray mBuffer;
    qint32 mBufferSize;
};

#endif // LANTRANSPORT_H
