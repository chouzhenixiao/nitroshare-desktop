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

#ifndef TRANSFERPROXYMODEL_H
#define TRANSFERPROXYMODEL_H

#include <nitroshare/proxymodel.h>

class TransferProxyModel : public ProxyModel
{
    Q_OBJECT

public:

    enum {
        DeviceColumn,
        ProgressColumn,
        SpeedColumn,
        TimeRemainingColumn,
        StatusColumn,
        ColumnCount
    };

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &proxyIndex, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:

    QString formatSpeed(qint64 speed) const;
    QString formatTimeRemaining(qint64 speed, qint64 bytesRemaining) const;
};

#endif // TRANSFERPROXYMODEL_H
