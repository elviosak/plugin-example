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

#include "exampleplugin.h"
#include "exampleconfiguration.h"

#include <QIcon>
#include <QMessageBox>
#include <QTimer>

#define QSL(text) QStringLiteral(text)

ExamplePlugin::ExamplePlugin(const ILXQtPanelPluginStartupInfo& startupInfo)
    : QObject()
    , ILXQtPanelPlugin(startupInfo)
{
    mWidget = new QToolButton;
    mWidget->setAutoRaise(true);
    mWidget->setMinimumWidth(1);
    mWidget->setMinimumHeight(1);

    QTimer::singleShot(0, [this] {
        this->settingsChanged();
    });
    connect(mWidget, &QToolButton::clicked, this, [this] {
        QMessageBox::aboutQt(mWidget);
    });
}

ExamplePlugin::~ExamplePlugin() = default;

void ExamplePlugin::settingsChanged()
{
    mShowIcon = settings()->value(QSL("showIcon"), true).toBool();
    mIcon = settings()->value(QSL("icon"), QSL("plugins")).toString();
    mShowText = settings()->value(QSL("showText"), true).toBool();
    mText = settings()->value(QSL("text"), QSL("About")).toString();

    mWidget->setIcon(QIcon::fromTheme(mIcon));
    mWidget->setText(mText);
    if (!mShowIcon && !mShowText) {
        mWidget->hide();
    } else {
        mWidget->show();
        if (mShowIcon && mShowText) {
            mWidget->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
        } else if (mShowIcon) {
            mWidget->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        } else if (mShowText) {
            mWidget->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextOnly);
        }
    }
    mWidget->update();
}

void ExamplePlugin::realign()
{
    mWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QDialog* ExamplePlugin::configureDialog()
{
    return new ExampleConfiguration(settings());
}
