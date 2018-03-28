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

#ifndef LIBNITROSHARE_SETTINGSREGISTRY_H
#define LIBNITROSHARE_SETTINGSREGISTRY_H

#include <QList>
#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QVariant>

#include <nitroshare/config.h>

class Category;
class Setting;

class NITROSHARE_EXPORT SettingsRegistryPrivate;

/**
 * @brief Registry for application settings
 *
 * By using a central registry for settings, it becomes possible for plugins to
 * provide an interface for manipulating settings.
 */
class NITROSHARE_EXPORT SettingsRegistry : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Create a new settings registry
     * @param settings pointer to QSettings
     * @param parent QObject
     */
    explicit SettingsRegistry(QSettings *settings, QObject *parent = nullptr);

    /**
     * @brief Retrieve a list of all categories
     */
    QList<Category*> categories() const;

    /**
     * @brief Retrieve a list of all settings
     */
    QList<Setting*> settings() const;

    /**
     * @brief Attempt to find a category by name
     * @param name unique category name
     * @return pointer to Category or nullptr
     */
    Category *findCategory(const QString &name) const;

    /**
     * @brief Add a category to the registry
     * @param category pointer to Category
     */
    void addCategory(Category *category);

    /**
     * @brief Remove a category from the registry
     * @param category pointer to Category
     */
    void removeCategory(Category *category);

    /**
     * @brief Attempt to find a setting by name
     * @param name setting name
     * @return pointer to Setting or nullptr
     */
    Setting *findSetting(const QString &name) const;

    /**
     * @brief Add a setting to the registry
     * @param setting pointer to Setting
     */
    void addSetting(Setting *setting);

    /**
     * @brief Remove a setting from the registry
     * @param setting pointer to Setting
     */
    void removeSetting(Setting *setting);

    /**
     * @brief Retrieve the value for a setting
     * @param name setting name
     */
    QVariant value(const QString &name) const;

    /**
     * @brief Set the value for a setting
     * @param name setting name
     * @param value new value for the setting
     */
    void setValue(const QString &name, const QVariant &value);

    /**
     * @brief Begin modifying a group of settings
     */
    void begin();

    /**
     * @brief End modifying a group of settings
     */
    void end();

Q_SIGNALS:

    /**
     * @brief Indicate that a category has been added
     * @param category pointer to Category
     */
    void categoryAdded(Category *category);

    /**
     * @brief Indicate that a category has been removed
     * @param category pointer to Category
     */
    void categoryRemoved(Category *category);

    /**
     * @brief Indicate that a setting has been added
     * @param setting pointer to Setting
     */
    void settingAdded(Setting *setting);

    /**
     * @brief Indicate that a setting has been removed
     * @param setting pointer to Setting
     */
    void settingRemoved(Setting *setting);

    /**
     * @brief Indicate that settings have changed value
     * @param names list of settings with new values
     */
    void settingsChanged(const QStringList &names);

private:

    SettingsRegistryPrivate *const d;
};

#endif // LIBNITROSHARE_SETTINGSREGISTRY_H
