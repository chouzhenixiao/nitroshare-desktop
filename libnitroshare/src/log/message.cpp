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

#include <QMap>

#include <nitroshare/message.h>

#include "message_p.h"

QMap<Message::Type, QString> TypeMap = {
    { Message::Debug, "d" },
    { Message::Info, "i" },
    { Message::Warning, "w" },
    { Message::Error, "e" }
};

MessagePrivate::MessagePrivate(QObject *parent, Message::Type type, const QString &tag, const QString &body)
    : QObject(parent),
      dateTime(QDateTime::currentDateTime()),
      type(type),
      tag(tag),
      body(body)
{
}

Message::Message(Type type, const QString &tag, const QString &body)
    : d(new MessagePrivate(this, type, tag, body))
{
}

QDateTime Message::dateTime() const
{
    return d->dateTime;
}

Message::Type Message::type() const
{
    return d->type;
}

QString Message::tag() const
{
    return d->tag;
}

QString Message::body() const
{
    return d->body;
}

QString Message::toString() const
{
    return QString("%1 [%2:%3] %4")
        .arg(d->dateTime.toString(Qt::ISODate))
        .arg(TypeMap.value(d->type))
        .arg(d->tag)
        .arg(d->body);
}
