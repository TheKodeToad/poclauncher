// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *      Copyright 2013-2021 MultiMC Contributors
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QIcon>
#include <QObject>

#include "AboutDialog.h"
#include "Application.h"
#include "BuildConfig.h"
#include "ui_AboutDialog.h"
#include "util/Markdown.h"

using namespace Qt::Literals;

static QString getLink(QString link, QString name)
{
    return u"&lt;<a href='%1'>%2</a>&gt;"_s.arg(link).arg(name);
}

static QString getWebsite(QString link)
{
    return getLink(link, QObject::tr("Website"));
}

static QString getGitHub(QString username)
{
    return getLink(u"https://github.com/"_s + username, u"GitHub"_s);
}

static QString getCreditsHtml()
{
    QFile dataFile(u":/docs/credits.html"_s);
    dataFile.open(QIODevice::ReadOnly);

    QString fileContent = QString::fromUtf8(dataFile.readAll());

    return fileContent.arg(QObject::tr("%1 Developers").arg(BuildConfig::LAUNCHER_DISPLAYNAME), QObject::tr("MultiMC Developers"),
                           QObject::tr("With special thanks to"));
}

static QString getLicenseHtml()
{
    QFile dataFile(u":/docs/COPYING.md"_s);
    dataFile.open(QIODevice::ReadOnly);

    QByteArray fileContent = dataFile.readAll();
    QString output = utf8MarkdownToHTML(fileContent);
    return output;
}

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);

    setWindowTitle(tr("About %1").arg(BuildConfig::LAUNCHER_DISPLAYNAME));

    QString chtml = getCreditsHtml();
    m_ui->creditsText->setHtml(chtml);

    QString lhtml = getLicenseHtml();
    m_ui->licenseText->setHtml(lhtml);

    m_ui->urlLabel->setOpenExternalLinks(true);

    m_ui->icon->setPixmap(QApplication::windowIcon().pixmap(64));
    m_ui->title->setText(BuildConfig::LAUNCHER_DISPLAYNAME);

    m_ui->versionLabel->setText(BuildConfig::VERSION_STRING);

    if (!BuildConfig::BUILD_PLATFORM.isEmpty())
        m_ui->platformLabel->setText(tr("Platform") + u": "_s + BuildConfig::BUILD_PLATFORM);
    else
        m_ui->platformLabel->setVisible(false);

    if (!BuildConfig::GIT_COMMIT.isEmpty())
        m_ui->commitLabel->setText(tr("Commit: %1").arg(BuildConfig::GIT_COMMIT));
    else
        m_ui->commitLabel->setVisible(false);

    if (!BuildConfig::BUILD_DATE.isEmpty())
        m_ui->buildDateLabel->setText(tr("Build date: %1").arg(BuildConfig::BUILD_DATE));
    else
        m_ui->buildDateLabel->setVisible(false);

    if (!BuildConfig::VERSION_CHANNEL.isEmpty())
        m_ui->channelLabel->setText(tr("Channel") + u": "_s + BuildConfig::VERSION_CHANNEL);
    else
        m_ui->channelLabel->setVisible(false);

    static const QLatin1String URL_TEXT = "<html><head/><body><p><a href=\"%1\">%1</a></p></body></html>"_L1;
    m_ui->urlLabel->setText(URL_TEXT.arg(BuildConfig::SOURCE_CODE_URL));

    m_ui->copyLabel->setText(BuildConfig::LAUNCHER_COPYRIGHT);

    connect(m_ui->closeButton, &QPushButton::clicked, this, &AboutDialog::close);

    connect(m_ui->aboutQt, &QPushButton::clicked, &QApplication::aboutQt);
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
