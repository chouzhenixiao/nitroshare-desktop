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

#include <nitroshare/application.h>
#include <nitroshare/bundle.h>
#include <nitroshare/device.h>
#include <nitroshare/devicemodel.h>
#include <nitroshare/transfer.h>
#include <nitroshare/transfermodel.h>

#include "sendurlaction.h"
#include "url.h"

SendUrlAction::SendUrlAction(Application *application)
    : mApplication(application)
{
}

QString SendUrlAction::name() const
{
    return "sendurl";
}

QVariant SendUrlAction::invoke(const QVariantMap &params)
{
    // Attempt to find the device
    Device *device = mApplication->deviceModel()->findDevice(
        params.value("device").toString(),
        params.value("enumerator").toString()
    );
    if (!device) {
        return false;
    }

    // Create the bundle
    Bundle *bundle = new Bundle;
    bundle->add(new Url(params.value("url").toString()));

    // Create the transfer
    mApplication->transferModel()->add(
        new Transfer(mApplication, device, bundle)
    );

    return true;
}
