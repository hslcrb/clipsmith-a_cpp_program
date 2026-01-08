#include "MainWindow.hpp"
#include <QApplication>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_dbManager = new DatabaseManager(this);
    m_dbManager->init();

    m_cbMonitor = new ClipboardMonitor(this);
    connect(m_cbMonitor, &ClipboardMonitor::contentChanged, this, &MainWindow::onNewContent);

    setupUi();
    createTrayIcon();
    refreshList();

    setWindowTitle("Clipsmith");
    resize(400, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("검색...");
    connect(m_searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);

    m_historyList = new QListWidget(this);
    connect(m_historyList, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);

    layout->addWidget(m_searchEdit);
    layout->addWidget(m_historyList);

    setCentralWidget(centralWidget);
}

void MainWindow::createTrayIcon() {
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(style()->standardIcon(QStyle::SP_ComputerIcon)); // 기본 아이콘 사용
    m_trayIcon->setToolTip("Clipsmith");

    m_trayMenu = new QMenu(this);
    QAction *showAction = m_trayMenu->addAction("열기");
    connect(showAction, &QAction::triggered, this, &MainWindow::showWindow);

    QAction *quitAction = m_trayMenu->addAction("종료");
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitApp);

    m_trayIcon->setContextMenu(m_trayMenu);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
    
    m_trayIcon->show();
}

void MainWindow::onNewContent(const QString &text) {
    // 중복 저장 방지 로직 등을 추가할 수 있습니다.
    m_dbManager->saveItem(text);
    refreshList();
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        showWindow();
    }
}

void MainWindow::onSearchChanged(const QString &text) {
    if (text.isEmpty()) {
        refreshList();
    } else {
        m_historyList->clear();
        auto items = m_dbManager->searchItems(text);
        for (const auto &item : items) {
            m_historyList->addItem(item.content.left(100).replace("\n", " "));
        }
    }
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item) {
    // 더블 클릭 시 클립보드로 다시 복사
    QApplication::clipboard()->setText(item->text());
}

void MainWindow::refreshList() {
    m_historyList->clear();
    auto items = m_dbManager->getAllItems();
    for (const auto &item : items) {
        // 리스트에는 첫 100자만 표시
        QString display = item.content.left(100).replace("\n", " ");
        m_historyList->addItem(display);
    }
}

void MainWindow::showWindow() {
    this->show();
    this->raise();
    this->activateWindow();
}

void MainWindow::quitApp() {
    QApplication::quit();
}
