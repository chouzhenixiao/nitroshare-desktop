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

#include <nitroshare/action.h>
#include <nitroshare/actionregistry.h>
#include <nitroshare/application.h>
#include <nitroshare/logger.h>
#include <nitroshare/message.h>

#include "actionregistry_p.h"

const QString MessageTag = "actionregistry";

ActionRegistryPrivate::ActionRegistryPrivate(QObject *parent, Application *application)
    : QObject(parent),
      application(application)
{
}

ActionRegistry::ActionRegistry(Application *application, QObject *parent)
    : QObject(parent),
      d(new ActionRegistryPrivate(this, application))
{
}

void ActionRegistry::add(Action *action)
{
    // Ensure that the action does not already exist
    if (find(action->name())) {
        d->application->logger()->log(new Message(
            Message::Warning,
            MessageTag,
            QString("action \"%1\" already registered").arg(action->name())
        ));
        return;
    }

    d->actions.append(action);
    emit actionAdded(action);
}

void ActionRegistry::remove(Action *action)
{
    d->actions.removeOne(action);
    emit actionRemoved(action);
}

Action *ActionRegistry::find(const QString &name) const
{
    foreach (Action *action, d->actions) {
        if (action->name() == name) {
            return action;
        }
    }
    return nullptr;
}

QList<Action*> ActionRegistry::actions() const
{
    return d->actions;
}
