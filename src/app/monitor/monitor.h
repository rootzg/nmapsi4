/***************************************************************************
 *   Copyright (C) 2011 by Francesco Cecconi                               *
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

#ifndef MONITOR_H
#define MONITOR_H

// Qt include
#include <QtGui/QTreeWidget>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <QtCore/QWeakPointer>
#include <QtCore/QSettings>
#include <QtNetwork/QHostInfo>

#ifdef Q_WS_X11
#include <QtDBus/QDBusConnection>
#endif

// local include
#include "memorytools.h"
#include "qprocessthread.h"
#include "details.h"
#include "lookupmanager.h"
#include "digmanager.h"

using namespace memory;

class nmapClass;

class monitor : public QObject
{
    Q_OBJECT

#ifdef Q_WS_X11
    Q_CLASSINFO("D-Bus Interface", "org.nmapsi4.Nmapsi4")
#endif

public:
    monitor(QTreeWidget* monitor, nmapClass* parent=0);
    ~monitor();

    enum LookupType
    {
        DigLookup,
        InternalLookup,
        DisabledLookup
    };
    /*
     * Add host in the monitor and start scan.
     */
    void addMonitorHost(const QString hostName, const QStringList parameters, LookupType option);
    /*
     * Return true if host is present in the monitor, otherwise return false.
     */
    bool isHostOnMonitor(const QString hostname);
    /*
     * Return current number of scanning host in the monitor.
     */
    int monitorHostNumber();
    /*
     * Clear all host in monitor
     */
    void clearHostMonitor();
    /*
     * Clear all scan host details
     */
    void clearHostMonitorDetails();
    /*
     * Load max parallel scan option from config file
     */
    void updateMaxParallelScan();

private:
    void startScan(const QString hostname, QStringList parameters);
    void startLookup(const QString hostname, LookupType option);
    void updateMonitorHost(const QString hostName, int valueIndex, const QString newData);
    /*
     * This method remove scanThread elem from scan hashTable
     */
    QProcessThread* takeMonitorElem(const QString hostName);
    /*
     * Delete host from monitor
     */
    void delMonitorHost(const QString hostName);
    /*
     * Cache for parallel host thread
     */
    void cacheScan(const QString& hostname, const QStringList& parameters, LookupType option, QTreeWidgetItem *item);

    QList<QTreeWidgetItem*> m_monitorElem;
    QList<lookupManager*> m_internealLookupList;
    QList<digManager*> m_digLookupList;
    QList< QPair<QString, QStringList> > m_hostScanCacheList;
    QList< QPair<LookupType, QTreeWidgetItem*> > m_lookupScanCacheList;
    QHash<QString, QProcessThread*> m_scanHashList;
    QHash<QString, QStringList> m_scanHashListFlow;
    QTreeWidget* m_monitor;
    nmapClass* m_ui;
    int m_parallelThreadLimit;
    bool m_isHostcached;
    QTimer* m_timer;

signals:
    /*
     * Exported with dbus
     */
    Q_SCRIPTABLE void monitorUpdated(int hostNumber);
    /*
     * Return scan result
     */
    void hostFinisced(const QStringList parametersList, QByteArray dataBuffer, QByteArray errorBuffer);

private slots:
    void readFlowFromThread(const QString hostname, QString lineData);
    void scanFinisced(const QStringList parametersList, QByteArray dataBuffer, QByteArray errorBuffer);
    void lookupFinisced(QHostInfo info, int state, const QString hostname);
    void cacheRepeat();

public slots:
        /*
     * Stop host scan selected in the QTreeWidget.
     */
    void stopSelectedScan();
    void stopAllScan();
    void showSelectedScanDetails();
};

#endif