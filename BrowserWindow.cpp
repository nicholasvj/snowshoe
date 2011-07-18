/****************************************************************************
 *   Copyright (C) 2011  Andreas Kling <awesomekling@gmail.com>             *
 *                                                                          *
 *   This file may be used under the terms of the GNU Lesser                *
 *   General Public License version 2.1 as published by the Free Software   *
 *   Foundation and appearing in the file LICENSE.LGPL included in the      *
 *   packaging of this file.  Please review the following information to    *
 *   ensure the GNU Lesser General Public License version 2.1 requirements  *
 *   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.   *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 ****************************************************************************/

#include "BrowserWindow.h"
#include "MainView.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>
#include <QtGui/QAction>
#include <QtGui/QImageReader>

BrowserWindow* BrowserWindow::create()
{
    return new BrowserWindow();
}

BrowserWindow::BrowserWindow()
    : QMainWindow(0)
{

    setAttribute(Qt::WA_DeleteOnClose);

    m_mainView = new MainView(this);

    connect(m_mainView, SIGNAL(titleChanged(QString)), this, SLOT(onPageTitleChanged(QString)));

    QAction* nextTabAction = new QAction(this);
    nextTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_PageDown));
    connect(nextTabAction, SIGNAL(triggered()), this, SLOT(jumpToNextTab()));
    addAction(nextTabAction);

    QAction* previousTabAction = new QAction(this);
    previousTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_PageUp));
    connect(previousTabAction, SIGNAL(triggered()), this, SLOT(jumpToPreviousTab()));
    addAction(previousTabAction);

    QAction* newWindowAction = new QAction(this);
    newWindowAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(openNewWindow()));
    addAction(newWindowAction);

    setCentralWidget(m_mainView);

    resize(800, 600);
}

void BrowserWindow::openInNewTab(const QString& urlFromUserInput)
{
    m_mainView->openInNewTab(urlFromUserInput);
}

BrowserWindow* BrowserWindow::openInNewWindow(const QString& url)
{
    BrowserWindow* window = BrowserWindow::create();
    openInNewTab(url);
    window->show();
    return window;
}

void BrowserWindow::openNewWindow()
{
    openInNewWindow(QString());
}

BrowserWindow::~BrowserWindow()
{
}

void BrowserWindow::jumpToNextTab()
{
    m_mainView->jumpToNextTab();
}

void BrowserWindow::jumpToPreviousTab()
{
    m_mainView->jumpToPreviousTab();
}

void BrowserWindow::onPageTitleChanged(const QString& title)
{
    setFancyWindowTitle(title);
}

void BrowserWindow::setFancyWindowTitle(const QString& title)
{
    setWindowTitle(QString::fromLatin1("%1 ~ %2").arg(title, QCoreApplication::applicationName()));
}
