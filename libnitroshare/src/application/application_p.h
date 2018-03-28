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

#ifndef LIBNITROSHARE_APPLICATION_P_H
#define LIBNITROSHARE_APPLICATION_P_H

#include <QSettings>

#include <nitroshare/actionregistry.h>
#include <nitroshare/application.h>
#include <nitroshare/category.h>
#include <nitroshare/devicemodel.h>
#include <nitroshare/handlerregistry.h>
#include <nitroshare/logger.h>
#include <nitroshare/pluginmodel.h>
#include <nitroshare/setting.h>
#include <nitroshare/settingsregistry.h>
#include <nitroshare/transfermodel.h>
#include <nitroshare/transportserverregistry.h>

class ApplicationPrivate : public QObject
{
    Q_OBJECT

public:

    ApplicationPrivate(Application *application, QSettings *existingSettings);
    virtual ~ApplicationPrivate();

    QString defaultPluginDirectory() const;

    Application *const q;

    Category deviceCategory;
    Setting deviceUuid;
    Setting deviceName;

    Category pluginCategory;
    Setting pluginDirectories;
    Setting pluginBlacklist;

    QSettings *settings;

    ActionRegistry actionRegistry;
    DeviceModel deviceModel;
    HandlerRegistry handlerRegistry;
    Logger logger;
    PluginModel pluginModel;
    SettingsRegistry settingsRegistry;
    TransferModel transferModel;
    TransportServerRegistry transportServerRegistry;

    bool uiEnabled;
};

#endif // LIBNITROSHARE_APPLICATION_P_H
