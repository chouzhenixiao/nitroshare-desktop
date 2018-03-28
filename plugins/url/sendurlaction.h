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

#ifndef SENDURLACTION_H
#define SENDURLACTION_H

#include <nitroshare/action.h>

class Application;

/**
 * @brief Send a URL to a peer
 *
 * The action expects three parameters:
 *
 * - "device"     (QString) - UUID of the device to send the URL to
 * - "enumerator" (QString) - name of enumerator that created the device
 * - "url"        (QString) - URL to send to the device
 *
 * The return value will be true if a transfer was prepared for the device and
 * false otherwise.
 */
class SendUrlAction : public Action
{
    Q_OBJECT

public:

    explicit SendUrlAction(Application *application);

    virtual QString name() const;

public slots:

    virtual QVariant invoke(const QVariantMap &params = QVariantMap());

private:

    Application *mApplication;
};

#endif // SENDURLACTION_H
