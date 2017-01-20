/*
 * Copyright (C) 2014-2016 Symeon Huang <hzwhuang@gmail.com>
 *
 * shadowsocks-qt5 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * shadowsocks-qt5 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libQtShadowsocks; see the file LICENSE. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalServer>
#include <QTimer>
#include <QSortFilterProxyModel>
#include "connectiontablemodel.h"
#include "confighelper.h"
#include "statusnotifier.h"
#include "httpclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ConfigHelper *confHelper, QWidget *parent = 0);
    ~MainWindow();

    void startAutoStartConnections();
    bool isInstanceRunning() const;
    void stopCurrentConnection();
    void clearConnectionList();
    void setUserInfo(const QJsonObject &obj);
    void setSessionId(const QString &id);
    void startHeartBeat();

private:
    Ui::MainWindow *ui;

    ConnectionTableModel *model;
    QSortFilterProxyModel *proxyModel;
    ConfigHelper *configHelper;
    StatusNotifier *notifier;

    QLocalServer* instanceServer;
    bool instanceRunning;
    void initSingleInstance();
    QJsonObject *userInfo = NULL;
    QString sessionId;
    QTimer *heartbeatTimer;
    HttpClient *heartbeatRequester;
    bool newVersionAsked = false;

    void newProfile(Connection *);
    void editRow(int row);
    void blockChildrenSignals(bool);
    void checkCurrentIndex();
    void setupActionIcon();
    void updateDisplayServers();

    static const QUrl issueUrl;

private slots:
    void onChangeUser();
    void onSingleInstanceConnect();
    void onImportGuiJson();
    void onExportGuiJson();
    void onSaveManually();
    void onAddManually();
    void onAddFromConfigJSON();
    void onDelete();
    void onEdit();
    void onConnect();
    void onForceConnect();
    void onDisconnect();
    void onConnectionStatusChanged(const int row, const bool running);
    void onLatencyTest();
    void onViewLog();
    void onMoveUp();
    void onMoveDown();
    void onGeneralSettings();
    void checkCurrentIndex(const QModelIndex &index);
    void onAbout();
    void onReportBug();
    void onCustomContextMenuRequested(const QPoint &pos);
    void onFilterToggled(bool);
    void onFilterTextChanged(const QString &text);
    void onHeartBeat();
    void onHeartBeatResponse(const QJsonObject &obj);

protected slots:
    void hideEvent(QHideEvent *e);
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
