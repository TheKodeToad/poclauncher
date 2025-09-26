// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
 *  Copyright (C) 2023 TheKodeToad <TheKodeToad@proton.me>
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
 *      Authors: Andrew Okin
 *               Peterix
 *               Orochimarufan <orochimarufan.x3@gmail.com>
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
#include <QDesktopServices>
#include <QPushButton>
#include <QToolButton>
#include <QUrl>

#include "./AboutDialog.h"
#include "./MainWindow.h"
#include "BuildConfig.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_ui->statusBar->hide();

    setWindowTitle(QApplication::applicationDisplayName());
    setUnifiedTitleAndToolBarOnMac(true);

    connect(m_ui->actionReportBug, &QAction::triggered, this, [] { QDesktopServices::openUrl(QUrl(BuildConfig::BUG_TRACKER_URL)); });
    connect(m_ui->actionMATRIX, &QAction::triggered, this, [] { QDesktopServices::openUrl(QUrl(BuildConfig::MATRIX_URL)); });
    connect(m_ui->actionDISCORD, &QAction::triggered, this, [] { QDesktopServices::openUrl(QUrl(BuildConfig::DISCORD_URL)); });
    connect(m_ui->actionREDDIT, &QAction::triggered, this, [] { QDesktopServices::openUrl(QUrl(BuildConfig::SUBREDDIT_URL)); });
    connect(m_ui->actionOpenWiki, &QAction::triggered, this, [] { QDesktopServices::openUrl(QUrl(BuildConfig::HELP_URL)); });
    connect(m_ui->actionAbout, &QAction::triggered, this, [this] { (new AboutDialog(this))->open(); });

    connect(m_ui->actionToggleStatusBar, &QAction::triggered, statusBar(), &QStatusBar::setVisible);
    connect(m_ui->actionLockToolbars, &QAction::triggered, this, &MainWindow::setToolbarsLocked);

    m_ui->actionHelpButton->setMenu(m_ui->helpMenu);

    auto helpMenuButton = static_cast<QToolButton*>(m_ui->mainToolBar->widgetForAction(m_ui->actionHelpButton));
    helpMenuButton->setPopupMode(QToolButton::InstantPopup);

    retranslate();
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslate();

    QMainWindow::changeEvent(event);
}

QMenu* MainWindow::createPopupMenu()
{
    QMenu* filteredMenu = QMainWindow::createPopupMenu();
    filteredMenu->removeAction(m_ui->mainToolBar->toggleViewAction());

    filteredMenu->addAction(m_ui->actionToggleStatusBar);
    filteredMenu->addAction(m_ui->actionLockToolbars);

    return filteredMenu;
}

void MainWindow::retranslate()
{
    m_ui->retranslateUi(this);
    m_ui->actionOpenWiki->setText(m_ui->actionOpenWiki->text().arg(BuildConfig::LAUNCHER_DISPLAYNAME));
    m_ui->actionAbout->setText(m_ui->actionAbout->text().arg(BuildConfig::LAUNCHER_DISPLAYNAME));
}

void MainWindow::setToolbarsLocked(bool locked)
{
    for (QToolBar* toolbar : findChildren<QToolBar*>(Qt::FindDirectChildrenOnly))
        toolbar->setMovable(!locked);
}
