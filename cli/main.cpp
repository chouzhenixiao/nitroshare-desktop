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

#include <iostream>

#include <QCommandLineParser>
#include <QCoreApplication>

#include <nitroshare/apiutil.h>
#include <nitroshare/application.h>
#include <nitroshare/logger.h>
#include <nitroshare/message.h>
#include <nitroshare/signalnotifier.h>
#include <nitroshare/stderrwriter.h>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("NitroShare");
    app.setOrganizationName("NitroShare");

    // Ensure another instance isn't already running
    if (ApiUtil::isRunning()) {
        QString errorMessage = QObject::tr(
            "NitroShare is already running. This instance will now terminate."
        );
        std::cerr << errorMessage.toUtf8().constData() << std::endl;
        return 1;
    }

    QCommandLineParser parser;

    // Create the application
    Application application;

    // Quit when a Unix signal is received
    SignalNotifier signalNotifier;
    QObject::connect(&signalNotifier, &SignalNotifier::signal, &app, &QCoreApplication::quit);

    // Log all messages to stderr by default
    StderrWriter stderrWriter;
    QObject::connect(application.logger(), &Logger::messageLogged, &stderrWriter, &StderrWriter::writeMessage);

    // Add the CLI arguments
    application.addCliOptions(&parser);
    parser.addHelpOption();
    parser.addVersionOption();

    // Process the CLI arguments
    parser.process(app);
    application.processCliOptions(&parser);

    return app.exec();
}
