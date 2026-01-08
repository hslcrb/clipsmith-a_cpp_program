#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include "../core/DatabaseManager.hpp"
#include "../core/ClipboardMonitor.hpp"

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
    void refreshList();
    void showWindow();
    void quitApp();

private:
    void setupUi();
    void createTrayIcon();

    DatabaseManager *m_dbManager;
    ClipboardMonitor *m_cbMonitor;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayMenu;

    QLineEdit *m_searchEdit;
    QListWidget *m_historyList;
};

#endif // MAINWINDOW_HPP
