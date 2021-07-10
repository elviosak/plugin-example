/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2021 LXQt team
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "exampleconfiguration.h"
#include "ui_exampleconfiguration.h"

#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QDebug>
#include <QTimer>

ExampleConfiguration::ExampleConfiguration(PluginSettings &settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExampleConfiguration)
    , mSettings(settings)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName(QStringLiteral("ExampleConfigurationWindow"));
    ui->setupUi(this);
    loadSettings();

    connect(ui->buttons, &QDialogButtonBox::clicked, this, &ExampleConfiguration::dialogButtonsAction);

    connect(ui->iconCB, &QCheckBox::toggled, this, [this] (bool checked) {
        this->settings().setValue(QStringLiteral("showIcon"), checked);
    });
    connect(ui->iconLE, &QLineEdit::textChanged, this, [this] (QString text) {
        this->settings().setValue(QStringLiteral("icon"), text);
    });
    connect(ui->textCB, &QCheckBox::toggled, this, [this] (bool checked) {
        this->settings().setValue(QStringLiteral("showText"), checked);
    });
    connect(ui->textLE, &QLineEdit::textChanged, this, [this] (QString text) {
        this->settings().setValue(QStringLiteral("text"), text);
    });
}

void ExampleConfiguration::loadSettings() const
{
    auto showIcon = settings().value(QStringLiteral("showIcon"), true).toBool();
    auto icon = settings().value(QStringLiteral("icon"), QStringLiteral("face-cool")).toString();
    auto showText = settings().value(QStringLiteral("showText"), true).toBool();
    auto text = settings().value(QStringLiteral("text"), QStringLiteral("About")).toString();
    ui->iconCB->setChecked(showIcon);
    ui->iconLE->setText(icon);
    ui->textCB->setChecked(showText);
    ui->textLE->setText(text);
}

PluginSettings& ExampleConfiguration::settings() const
{
    return mSettings;
}

void ExampleConfiguration::dialogButtonsAction(QAbstractButton *btn)
{
    QDialogButtonBox *box = qobject_cast<QDialogButtonBox*>(btn->parent());

    if (box && box->buttonRole(btn) == QDialogButtonBox::ResetRole)
    {
        mSettings.loadFromCache();
        loadSettings();
    }
    else
    {
        close();
    }
}
