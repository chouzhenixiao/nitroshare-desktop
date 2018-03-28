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

#ifndef FILE_H
#define FILE_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QVariantMap>

#include <nitroshare/item.h>

/**
 * @brief Item for reading and writing files in the local filesystem
 */
class File : public Item
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ readOnly)
    Q_PROPERTY(bool executable READ executable)
    Q_PROPERTY(qint64 created READ created)
    Q_PROPERTY(qint64 lastRead READ lastRead)
    Q_PROPERTY(qint64 lastModified READ lastModified)

    // Properties provided for legacy support
    Q_PROPERTY(qint64 last_read READ last_read)
    Q_PROPERTY(qint64 last_modified READ last_modified)

public:

    File(const QString &root, const QVariantMap &properties);
    File(const QDir &root, const QFileInfo &info, int blockSize);

    bool readOnly() const;
    bool executable() const;
    qint64 created() const;
    qint64 lastRead() const;
    qint64 lastModified() const;

    qint64 last_read() const;
    qint64 last_modified() const;

    // Reimplemented virtual methods
    virtual QString type() const;
    virtual QString name() const;
    virtual qint64 size() const;

    virtual bool open(OpenMode openMode);
    virtual QByteArray read();
    virtual void write(const QByteArray &data);
    virtual void close();

private:

    QFile mFile;
    int mBlockSize;

    QString mRelativeFilename;

    qint64 mSize;
    bool mReadOnly;
    bool mExecutable;

    qint64 mCreated;
    qint64 mLastRead;
    qint64 mLastModified;
};

#endif // FILE_H
