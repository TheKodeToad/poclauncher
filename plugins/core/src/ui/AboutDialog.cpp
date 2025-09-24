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

#include "./AboutDialog.h"
#include "common/BuildConfig.h"
#include "common/Markdown.h"
#include "ui_AboutDialog.h"

using namespace Qt::Literals;

namespace {
QString getLink(QString link, QString name)
{
    return u"&lt;<a href='%1'>%2</a>&gt;"_s.arg(link).arg(name);
}

QString getWebsite(QString link)
{
    return getLink(link, QObject::tr("Website"));
}

QString getGitHub(QString username)
{
    return getLink(u"https://github.com/"_s + username, u"GitHub"_s);
}

// Credits
// This is a hack, but I can't think of a better way to do this easily without screwing with QTextDocument...
QString getCreditsHtml()
{
    QString output;
    QTextStream stream(&output);
#if QT_VERSION <= QT_VERSION_CHECK(6, 0, 0)
    stream.setCodec(QTextCodec::codecForName(u"UTF-8"_s));
#endif
    stream << "<center>\n";

    //: %1 is the name of the launcher, determined at build time, e.g. "Prism Launcher Developers"
    stream << "<h3>" << QObject::tr("%1 Developers", "About Credits").arg(BuildConfig::LAUNCHER_DISPLAYNAME) << "</h3>\n";
    stream << u"<p>Sefa Eyeoglu (Scrumplex) %1</p>\n"_s.arg(getWebsite(u"https://scrumplex.net"_s));
    stream << u"<p>d-513 %1</p>\n"_s.arg(getGitHub(u"d-513"_s));
    stream << u"<p>txtsd %1</p>\n"_s.arg(getWebsite(u"https://ihavea.quest"_s));
    stream << u"<p>timoreo %1</p>\n"_s.arg(getGitHub(u"timoreo22"_s));
    stream << u"<p>ZekeZ %1</p>\n"_s.arg(getGitHub(u"ZekeZDev"_s));
    stream << u"<p>cozyGalvinism %1</p>\n"_s.arg(getGitHub(u"cozyGalvinism"_s));
    stream << u"<p>DioEgizio %1</p>\n"_s.arg(getGitHub(u"DioEgizio"_s));
    stream << u"<p>flowln %1</p>\n"_s.arg(getGitHub(u"flowln"_s));
    stream << u"<p>ViRb3 %1</p>\n"_s.arg(getGitHub(u"ViRb3"_s));
    stream << u"<p>Rachel Powers (Ryex) %1</p>\n"_s.arg(getGitHub(u"Ryex"_s));
    stream << u"<p>TayouVR %1</p>\n"_s.arg(getGitHub(u"TayouVR"_s));
    stream << u"<p>TheKodeToad %1</p>\n"_s.arg(getGitHub(u"TheKodeToad"_s));
    stream << u"<p>getchoo %1</p>\n"_s.arg(getGitHub(u"getchoo"_s));
    stream << u"<p>Alexandru Tripon (Trial97) %1</p>\n"_s.arg(getGitHub(u"Trial97"_s));
    stream << "<br />\n";

    // TODO: possibly retrieve from git history at build time?
    //: %1 is the name of the launcher, determined at build time, e.g. "Prism Launcher Developers"
    stream << "<h3>" << QObject::tr("%1 Developers", "About Credits").arg(u"MultiMC"_s) <<"</h3>\n";
    stream << "<p>Andrew Okin &lt;<a href='mailto:forkk@forkk.net'>forkk@forkk.net</a>&gt;</p>\n";
    stream << "<p>Petr Mrázek &lt;<a href='mailto:peterix@gmail.com'>peterix@gmail.com</a>&gt;</p>\n";
    stream << "<p>Sky Welch &lt;<a href='mailto:multimc@bunnies.io'>multimc@bunnies.io</a>&gt;</p>\n";
    stream << "<p>Jan (02JanDal) &lt;<a href='mailto:02jandal@gmail.com'>02jandal@gmail.com</a>&gt;</p>\n";
    stream << "<p>RoboSky &lt;<a href='https://twitter.com/RoboSky_'>@RoboSky_</a>&gt;</p>\n";
    stream << "<br />\n";

    stream << "<h3>" << QObject::tr("With thanks to", "About Credits") << "</h3>\n";
    stream << u"<p>Boba %1</p>\n"_s.arg(getWebsite(u"https://bobaonline.neocities.org/"_s));
    stream << u"<p>AutiOne %1</p>\n"_s.arg(getWebsite(u"https://auti.one/"_s));
    stream << u"<p>Fulmine %1</p>\n"_s.arg(getWebsite(u"https://fulmine.xyz/"_s));
    stream << u"<p>ely %1</p>\n"_s.arg(getGitHub(u"elyrodso"_s));
    stream << u"<p>gon sawa %1</p>\n"_s.arg(getGitHub(u"gonsawa"_s));
    stream << u"<p>Pankakes</p>\n"_s;
    stream << u"<p>tobimori %1</p>\n"_s.arg(getGitHub(u"tobimori"_s));
    stream << "<p>Orochimarufan &lt;<a href='mailto:orochimarufan.x3@gmail.com'>orochimarufan.x3@gmail.com</a>&gt;</p>\n";
    stream << "<p>TakSuyu &lt;<a href='mailto:taksuyu@gmail.com'>taksuyu@gmail.com</a>&gt;</p>\n";
    stream << "<p>Kilobyte &lt;<a href='mailto:stiepen22@gmx.de'>stiepen22@gmx.de</a>&gt;</p>\n";
    stream << "<p>Rootbear75 &lt;<a href='https://twitter.com/rootbear75'>@rootbear75</a>&gt;</p>\n";
    stream << "<p>Zeker Zhayard &lt;<a href='https://twitter.com/zeker_zhayard'>@Zeker_Zhayard</a>&gt;</p>\n";
    stream << "<p>Everyone who helped establish our branding!</p>\n";
    stream
        << "<p>And everyone else who <a href='https://github.com/PrismLauncher/PrismLauncher/graphs/contributors'>contributed</a>!</p>\n";
    stream << "<br />\n";

    stream << "</center>\n";
    return output;
}

QString getLicenseHtml()
{
    QFile dataFile(u":/documents/COPYING.md"_s);
    dataFile.open(QIODevice::ReadOnly);
    QByteArray fileContent = dataFile.readAll();
    QString output = markdownToHTMLUTF8(fileContent);
    return output;
}

}  // namespace

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);

    setWindowTitle(tr("About %1").arg(BuildConfig::LAUNCHER_DISPLAYNAME));

    QString chtml = getCreditsHtml();
    m_ui->creditsText->setHtml(chtml);

    QString lhtml = getLicenseHtml();
    m_ui->licenseText->setHtml(lhtml);

    m_ui->urlLabel->setOpenExternalLinks(true);

    // m_ui->icon->setPixmap(APPLICATION->logo().pixmap(64));
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

    QString urlText = u"<html><head/><body><p><a href=\"%1\">%1</a></p></body></html>"_s;
    m_ui->urlLabel->setText(urlText.arg(BuildConfig::SOURCE_CODE_URL));

    m_ui->copyLabel->setText(BuildConfig::LAUNCHER_COPYRIGHT);

    connect(m_ui->closeButton, &QPushButton::clicked, this, &AboutDialog::close);

    connect(m_ui->aboutQt, &QPushButton::clicked, &QApplication::aboutQt);
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
