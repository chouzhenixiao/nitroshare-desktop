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

#include <QPixmap>

#include <nitroshare/application.h>

#include "conclusionpage.h"
#include "devicepage.h"
#include "discoverypage.h"
#include "intropage.h"
#include "wizard.h"

Wizard::Wizard(Application *application)
    : mApplication(application)
{
    setPixmap(QWizard::LogoPixmap, QPixmap(":/wizard/logo.png"));
    setWizardStyle(QWizard::ModernStyle);
    setWindowTitle(tr("Setup Wizard"));

    // Adjust the wizard to a reasonable size
    resize(540, 400);

    addPage(new IntroPage);
    addPage(new DevicePage(application->deviceName()));
    addPage(new DiscoveryPage);
    addPage(new ConclusionPage);
}

void Wizard::accept()
{
    // TODO

    QWizard::accept();
}
