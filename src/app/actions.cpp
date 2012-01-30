/***************************************************************************
 *   Copyright (C) 2010-2011 by Francesco Cecconi                          *
 *   francesco.cecconi@gmail.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License.        *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "mainwin.h"


void nmapClass::menuScanBook()
{
    QAction removeBook(this);
    removeBook.setIcon(QIcon(QString::fromUtf8(":/images/images/window-close.png")));
    removeBook.setIconText(tr("Remove Host"));

    QAction scanBook(this);
    scanBook.setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag.png")));
    scanBook.setIconText(tr("Scan Host"));

    connect(&scanBook, SIGNAL(triggered()), this, SLOT(callScanH()));
    connect(&removeBook, SIGNAL(triggered()), this, SLOT(deleteBookMark()));

    QMenu menuBook(this);
    menuBook.addAction(&scanBook);
    menuBook.addAction(&removeBook);

    menuBook.exec(QCursor::pos());
}

void nmapClass::menuVulnBook()
{
    QAction removeBook(this);
    removeBook.setIcon(QIcon(QString::fromUtf8(":/images/images/window-close.png")));
    removeBook.setIconText(tr("Remove Service"));

    QAction addBook(this);
    addBook.setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag.png")));
    addBook.setIconText(tr("Search for vulnerabilities"));

    connect(&addBook, SIGNAL(triggered()), _vulnerability, SLOT(callVulnCheck()));
    connect(&removeBook, SIGNAL(triggered()), this, SLOT(deleteBookMark()));

    QMenu menuBook(this);
    menuBook.addAction(&addBook);
    menuBook.addAction(&removeBook);

    menuBook.exec(QCursor::pos());
}

void nmapClass::menuParBook()
{
    QAction removeBook(this);
    removeBook.setIcon(QIcon(QString::fromUtf8(":/images/images/window-close.png")));
    removeBook.setIconText(tr("Remove Scan Parameters"));

    connect(&removeBook, SIGNAL(triggered()), this, SLOT(deleteBookMarkPar()));

    QMenu menuBook(this);
    menuBook.addAction(&removeBook);

    menuBook.exec(QCursor::pos());
}

void nmapClass::menuServiceMain()
{
    QAction checkVuln(this);
    checkVuln.setIcon(QIcon(QString::fromUtf8(":/images/images/viewmag+.png")));
    checkVuln.setIconText(tr("Check Vulnerability"));

    connect(&checkVuln, SIGNAL(triggered()), _vulnerability, SLOT(objVulnButton()));

    QMenu menuVulnMain(this);
    menuVulnMain.addAction(&checkVuln);
    menuVulnMain.exec(QCursor::pos());
}

void nmapClass::menuVulnUrlBookmark()
{
    QAction removeVulnUrl(this);
    removeVulnUrl.setIcon(QIcon(QString::fromUtf8(":/images/images/window-close.png")));
    removeVulnUrl.setIconText(tr("Remove url"));
    connect(&removeVulnUrl, SIGNAL(triggered()), _vulnerability, SLOT(removeUrlToBookmarks()));

    QMenu menuVulnUrl(this);
    menuVulnUrl.addAction(&removeVulnUrl);
    menuVulnUrl.exec(QCursor::pos());
}

void nmapClass::createBar()
{
    QPushButtonOrientated* actionButt;
    const int verticalButtonWidth = 25;

    actionButt = new QPushButtonOrientated(QIcon(QString::fromUtf8(":/images/images/network_local.png")),tr("Scan host(s)"));
    actionButt->setToolTip(tr("Scan host(s)"));
    actionButt->setOrientation(Qt::Vertical);
    actionButt->setFlat(true);
    actionButt->setMaximumWidth(verticalButtonWidth);
    actionButt->setCheckable(true);
    actionButt->setStyleSheet(verticalStyleSheet);
    _collectionsButton.insert("scan-sez",actionButt);
    connect(actionButt, SIGNAL(clicked(bool)),this, SLOT(updateSezScan()));
    sezBar->addWidget(actionButt);

    actionButt = new QPushButtonOrientated(QIcon(QString::fromUtf8(":/images/images/document-preview-archive.png")),tr("Network Discover"));
    actionButt->setToolTip(tr("Network Discover"));
    actionButt->setOrientation(Qt::Vertical);
    actionButt->setFlat(true);
    actionButt->setMaximumWidth(verticalButtonWidth);
    actionButt->setCheckable(true);
    actionButt->setStyleSheet(verticalStyleSheet);
    _collectionsButton.insert("discover-sez",actionButt);
    connect(actionButt, SIGNAL(clicked(bool)),this, SLOT(updateSezDiscover()));
    sezBar->addWidget(actionButt);

    actionButt = new QPushButtonOrientated(QIcon(QString::fromUtf8(":/images/images/viewmag+.png")),tr("Vulnerability"));
    actionButt->setToolTip(tr("Check Vulnerabilities"));
    actionButt->setOrientation(Qt::Vertical);
    actionButt->setFlat(true);
    actionButt->setMaximumWidth(verticalButtonWidth);
    actionButt->setCheckable(true);
    actionButt->setStyleSheet(verticalStyleSheet);
    _collectionsButton.insert("vuln-sez",actionButt);
    connect(actionButt, SIGNAL(clicked(bool)),this, SLOT(updateSezVuln()));
    sezBar->addWidget(actionButt);

    sezBar->setContextMenuPolicy(Qt::PreventContextMenu);

    actionButt = new QPushButtonOrientated(QIcon(QString::fromUtf8(":/images/images/network-workgroup.png")),tr("Show Lookup"));
    actionButt->setToolTip(tr("Show/Hide Lookup"));
    actionButt->setOrientation(Qt::Vertical);
    actionButt->setMirrored(true);
    actionButt->setFlat(true);
    actionButt->setMaximumWidth(verticalButtonWidth);
    actionButt->setCheckable(true);
    actionButt->setStyleSheet(verticalStyleSheet);
    _collectionsButton.insert("tab-look-act",actionButt);
    connect(actionButt, SIGNAL(clicked(bool)),this, SLOT(updateTabLook()));
    toolBarTab->addWidget(actionButt);

    actionButt = new QPushButtonOrientated(QIcon(QString::fromUtf8(":/images/images/network-wired.png")),tr("Show Traceroute"));
    actionButt->setToolTip(tr("Show/Hide Traceroute"));
    actionButt->setOrientation(Qt::Vertical);
    actionButt->setMirrored(true);
    actionButt->setFlat(true);
    actionButt->setMaximumWidth(verticalButtonWidth);
    actionButt->setCheckable(true);
    actionButt->setStyleSheet(verticalStyleSheet);
    _collectionsButton.insert("tab-trace-act",actionButt);
    connect(actionButt, SIGNAL(clicked(bool)),this, SLOT(updateTabTrace()));
    toolBarTab->addWidget(actionButt);

    toolBarTab->setContextMenuPolicy(Qt::PreventContextMenu);
}

void nmapClass::createToolButtonSetup()
{
    // new QToolButton menu
    menuSetup = new QToolButton();
    menuSetup->setPopupMode(QToolButton::InstantPopup);
    menuSetup->setText(tr("Setup"));
    menuSetup->setIcon(QIcon(QString::fromUtf8(":/images/images/tool.png")));

    QMenu *menu = new QMenu();
    menu->addAction(action_Scan_2);
    menu->addAction(actionSave);
    menu->addAction(actionSave_As_Menu);
    menu->addSeparator();
    menu->addAction(actionAdd_Bookmark);
    menu->addSeparator();
    menu->addAction(actionScan_section);
    menu->addAction(actionVulnerabilities_section);
    menu->addAction(actionSection_Discover);
    menu->addSeparator();
    menu->addAction(actionProfile);
    menu->addAction(actionNew_Profile);
    menu->addAction(actionEdit_Profile);
    menu->addSeparator();
    menu->addMenu(menu_Help);
    menu->addSeparator();
    menu->addAction(actionMenuBar);
    menu->addSeparator();
    menu->addAction(action_Quit_2);
    menu->setLayoutDirection(Qt::LeftToRight);
    menuSetup->setMenu(menu);
    //toolBarQuit->addWidget(menuSetup);
    toolMenuBar->addWidget(menuSetup);

    // profiler menu
    m_profilerTool = new QToolButton();
    m_profilerTool->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_profilerTool->setPopupMode(QToolButton::InstantPopup);
    m_profilerTool->setText(tr("Profile"));
    m_profilerTool->setIcon(QIcon(QString::fromUtf8(":/images/images/documentation.png")));

    QMenu *menuProfiler = new QMenu();
    menuProfiler->addAction(actionNew_Profile);
    menuProfiler->addAction(actionEdit_Profile);
    m_profilerTool->setMenu(menuProfiler);

    toolBar_2->addWidget(m_profilerTool);

    // save menu
    m_saveTool = new QToolButton();
    m_saveTool->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_saveTool->setPopupMode(QToolButton::InstantPopup);
    m_saveTool->setText(tr("Save"));
    m_saveTool->setIcon(QIcon(QString::fromUtf8(":/images/images/save_all.png")));

    QMenu *menuSave = new QMenu();
    menuSave->addAction(actionSave_Menu);
    menuSave->addAction(actionSave_As_Menu);
    m_saveTool->setMenu(menuSave);

    toolBar->addWidget(m_saveTool);
    toolBar->addSeparator();
}