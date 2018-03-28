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

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "devicepage.h"

DevicePage::DevicePage(const QString &deviceName)
{
    setTitle(tr("Device Setup"));
    setSubTitle(tr("Configure settings for this device"));

    QLabel *descriptionLabel = new QLabel(tr(
        "In order to identify your device to others on the network, please "
        "choose a unique name. The default name is shown as a suggestion."
    ));
    descriptionLabel->setWordWrap(true);

    QLabel *deviceNameLabel = new QLabel(tr("Device name:"));

    QLineEdit *deviceNameLineEdit = new QLineEdit;
    deviceNameLineEdit->setText(deviceName);
    registerField("deviceName", deviceNameLineEdit);

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(descriptionLabel);
    vboxLayout->addWidget(deviceNameLabel);
    vboxLayout->addWidget(deviceNameLineEdit);
    setLayout(vboxLayout);
}
