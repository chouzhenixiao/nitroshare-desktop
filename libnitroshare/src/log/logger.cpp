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

#include <nitroshare/logger.h>
#include <nitroshare/message.h>

#include "logger_p.h"

LoggerPrivate::LoggerPrivate(QObject *parent)
    : QObject(parent)
{
}

LoggerPrivate::~LoggerPrivate()
{
    qDeleteAll(messages);
}

Logger::Logger(QObject *parent)
    : QObject(parent),
      d(new LoggerPrivate(this))
{
}

QList<Message*> Logger::messages() const
{
    return d->messages;
}

void Logger::log(Message *message)
{
    d->messages.append(message);
    emit messageLogged(message);

    // TODO: make this into a setting?

    // Prevent too many messages from accumulating
    if (d->messages.count() > 100) {
        delete d->messages.takeFirst();
    }
}
