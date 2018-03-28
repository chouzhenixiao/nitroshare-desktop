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

#include <nitroshare/bundle.h>
#include <nitroshare/item.h>

#include "bundle_p.h"

BundlePrivate::BundlePrivate(QObject *parent)
    : QObject(parent),
      totalSize(0)
{
}

BundlePrivate::~BundlePrivate()
{
    qDeleteAll(items);
}

Bundle::Bundle(QObject *parent)
    : QAbstractListModel(parent),
      d(new BundlePrivate(this))
{
}

void Bundle::add(Item *item)
{
    d->items.append(item);
    d->totalSize += item->size();
}

qint64 Bundle::totalSize() const
{
    return d->totalSize;
}

int Bundle::rowCount(const QModelIndex &) const
{
    return d->items.count();
}

QVariant Bundle::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
            index.row() >= d->items.count() || role != Qt::UserRole) {
        return QVariant();
    }
    return QVariant::fromValue(d->items.at(index.row()));
}
