#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QListWidget>
#include <QLineEdit>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include "../core/DatabaseManager.hpp"
#include "../core/ClipboardMonitor.hpp"
#include "../plugins/TextProcessor.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewContent(const QString &text);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onSearchChanged(const QString &text);
    void onItemDoubleClicked(QListWidgetItem *item);
    void onSelectionChanged();
    
    // 스마트 액션 슬롯
    void actionPrettify();
    void actionBase64Decode();
    void actionCleanText();
    void actionCopyItem();
    void actionDeleteItem();

    void refreshList();
    void showWindow();
    void quitApp();

private:
    void setupUi();
    void createTrayIcon();
    void updateActionStates(const QString &text);

    DatabaseManager *m_dbManager;
    ClipboardMonitor *m_cbMonitor;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayMenu;

    QLineEdit *m_searchEdit;
    QListWidget *m_historyList;
    
    // 툴바 및 액션
    QToolBar *m_toolBar;
    QAction *m_prettifyAction;
    QAction *m_decodeAction;
    QAction *m_cleanAction;
    QAction *m_copyAction;
    QAction *m_deleteAction;
    
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_HPP
