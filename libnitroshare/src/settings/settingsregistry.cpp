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

#include <nitroshare/category.h>
#include <nitroshare/setting.h>
#include <nitroshare/settingsregistry.h>

#include "settingsregistry_p.h"

SettingsRegistryPrivate::SettingsRegistryPrivate(QObject *parent, QSettings *settings)
    : QObject(parent),
      settings(settings),
      isInGroup(false)
{
}

SettingsRegistry::SettingsRegistry(QSettings *settings, QObject *parent)
    : QObject(parent),
      d(new SettingsRegistryPrivate(this, settings))
{
}

QList<Category*> SettingsRegistry::categories() const
{
    return d->categoryList;
}

QList<Setting*> SettingsRegistry::settings() const
{
    return d->settingsList;
}

Category *SettingsRegistry::findCategory(const QString &name) const
{
    foreach (Category *category, d->categoryList) {
        if (category->name() == name) {
            return category;
        }
    }
    return nullptr;
}

void SettingsRegistry::addCategory(Category *category)
{
    d->categoryList.append(category);
    emit categoryAdded(category);
}

void SettingsRegistry::removeCategory(Category *category)
{
    d->categoryList.removeOne(category);
    emit categoryRemoved(category);
}

Setting *SettingsRegistry::findSetting(const QString &name) const
{
    foreach (Setting *setting, d->settingsList) {
        if (setting->name() == name) {
            return setting;
        }
    }
    return nullptr;
}

void SettingsRegistry::addSetting(Setting *setting)
{
    d->settingsList.append(setting);
    emit settingAdded(setting);
}

void SettingsRegistry::removeSetting(Setting *setting)
{
    d->settingsList.removeOne(setting);
    emit settingRemoved(setting);
}

QVariant SettingsRegistry::value(const QString &name) const
{
    Setting *setting = findSetting(name);
    if (setting) {
        if (d->settings->contains(name)) {
            return d->settings->value(name);
        } else {
            d->settings->setValue(name, setting->defaultValue());
            return setting->defaultValue();
        }
    } else {
        return QVariant();
    }
}

void SettingsRegistry::setValue(const QString &name, const QVariant &value)
{
    if (d->settings->contains(name) && d->settings->value(name) == value) {
        return;
    }
    d->settings->setValue(name, value);
    if (d->isInGroup) {
        d->groupNames.insert(name);
    } else {
        emit settingsChanged({ name });
    }
}

void SettingsRegistry::begin()
{
    d->isInGroup = true;
}

void SettingsRegistry::end()
{
    emit settingsChanged(d->groupNames.toList());
    d->isInGroup = false;
    d->groupNames.clear();
}
