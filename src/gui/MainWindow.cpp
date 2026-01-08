#include "MainWindow.hpp"
#include <QApplication>
#include <QStyle>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_dbManager = new DatabaseManager(this);
    m_dbManager->init();

    m_cbMonitor = new ClipboardMonitor(this);
    connect(m_cbMonitor, &ClipboardMonitor::contentChanged, this, &MainWindow::onNewContent);

    setupUi();
    createTrayIcon();
    refreshList();

    setWindowTitle("Clipsmith");
    resize(450, 700);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // 검색 박스 스타일링
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("검색어를 입력하세요... (Search here...)");
    m_searchEdit->setMinimumHeight(35);
    m_searchEdit->setStyleSheet(
        "QLineEdit { border: 1px solid #444; border-radius: 5px; padding: 5px; background: #2b2b2b; color: #eee; }"
        "QLineEdit:focus { border: 1px solid #0078d4; }"
    );
    connect(m_searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);

    // 툴바 설정
    m_toolBar = new QToolBar("가공 도구 (Tools)", this);
    m_toolBar->setIconSize(QSize(20, 20));
    m_toolBar->setStyleSheet("QToolBar { background: #333; border: none; spacing: 5px; }");

    m_prettifyAction = m_toolBar->addAction("JSON 정리 (Prettify)");
    m_decodeAction = m_toolBar->addAction("Base64 디코드 (Decode)");
    m_cleanAction = m_toolBar->addAction("공백 제거 (Clean)");
    m_toolBar->addSeparator();
    m_copyAction = m_toolBar->addAction("재복사 (Copy)");
    m_deleteAction = m_toolBar->addAction("삭제 (Delete)");

    m_prettifyAction->setEnabled(false);
    m_decodeAction->setEnabled(false);

    connect(m_prettifyAction, &QAction::triggered, this, &MainWindow::actionPrettify);
    connect(m_decodeAction, &QAction::triggered, this, &MainWindow::actionBase64Decode);
    connect(m_cleanAction, &QAction::triggered, this, &MainWindow::actionCleanText);
    connect(m_copyAction, &QAction::triggered, this, &MainWindow::actionCopyItem);
    connect(m_deleteAction, &QAction::triggered, this, &MainWindow::actionDeleteItem);

    // 리스트 위젯 스타일링
    m_historyList = new QListWidget(this);
    m_historyList->setStyleSheet(
        "QListWidget { background: #1e1e1e; border: 1px solid #333; border-radius: 5px; color: #ccc; outline: none; }"
        "QListWidget::item { padding: 10px; border-bottom: 1px solid #2d2d2d; }"
        "QListWidget::item:selected { background: #0078d4; color: white; border-radius: 3px; }"
        "QListWidget::item:hover { background: #333; }"
    );
    connect(m_historyList, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(m_historyList, &QListWidget::itemSelectionChanged, this, &MainWindow::onSelectionChanged);

    m_statusLabel = new QLabel("준비 완료 (Ready)", this);
    m_statusLabel->setStyleSheet("color: #888; font-size: 11px;");

    mainLayout->addWidget(m_searchEdit);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_historyList);
    mainLayout->addWidget(m_statusLabel);

    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(":/logo.png"));
    
    // 메인 윈도우 배경색 설정
    this->setStyleSheet("QMainWindow { background-color: #1a1a1a; }");
}

void MainWindow::onSelectionChanged() {
    QListWidgetItem *item = m_historyList->currentItem();
    if (!item) {
        m_prettifyAction->setEnabled(false);
        m_decodeAction->setEnabled(false);
        m_statusLabel->setText("항목을 선택하세요. (Select an item.)");
        return;
    }

    // 실제로는 전체 내용을 저장해두어야 가공이 가능함. 
    // 리스트에는 요약만 있으므로, DB에서 다시 가져오거나 데이터를 item에 담아야 함.
    // 여기서는 간단히 content를 가져와 분석하는 것으로 가정 (refreshList 수정 필요)
    QString content = item->data(Qt::UserRole).toString();
    updateActionStates(content);
}

void MainWindow::updateActionStates(const QString &text) {
    TextType type = TextProcessor::detectType(text);
    m_prettifyAction->setEnabled(type == TextType::Json);
    m_decodeAction->setEnabled(type == TextType::Base64);
    
    QString typeStr = "텍스트 (Text)";
    if (type == TextType::Json) typeStr = "JSON 코드 (JSON)";
    else if (type == TextType::Url) typeStr = "URL";
    else if (type == TextType::Email) typeStr = "이메일 (Email)";
    else if (type == TextType::Base64) typeStr = "Base64 데이터 (Base64)";
    
    m_statusLabel->setText(QString("감지됨 (Detected): %1 (%2 chars)").arg(typeStr).arg(text.length()));
}

void MainWindow::actionPrettify() {
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QString original = item->data(Qt::UserRole).toString();
        QString prettified = TextProcessor::prettifyJson(original);
        QApplication::clipboard()->setText(prettified);
        m_statusLabel->setText("JSON 정리 완료! (JSON Prettified!)");
    }
}

void MainWindow::actionBase64Decode() {
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QString original = item->data(Qt::UserRole).toString();
        QString decoded = TextProcessor::fromBase64(original);
        QApplication::clipboard()->setText(decoded);
        m_statusLabel->setText("디코딩 완료! (Base64 Decoded!)");
    }
}

void MainWindow::actionCleanText() {
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QString original = item->data(Qt::UserRole).toString();
        QString cleaned = TextProcessor::cleanText(original);
        QApplication::clipboard()->setText(cleaned);
        m_statusLabel->setText("공백 제거 완료! (Text Cleaned!)");
    }
}

void MainWindow::actionCopyItem() {
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QApplication::clipboard()->setText(item->data(Qt::UserRole).toString());
        m_statusLabel->setText("복사되었습니다. (Copied.)");
    }
}

void MainWindow::actionDeleteItem() {
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        int id = item->data(Qt::UserRole + 1).toInt();
        if (m_dbManager->deleteItem(id)) {
            refreshList();
            m_statusLabel->setText("삭제되었습니다. (Deleted.)");
        }
    }
}

void MainWindow::refreshList() {
    m_historyList->clear();
    auto items = m_dbManager->getAllItems();
    for (const auto &item : items) {
        QString display = item.content.left(100).replace("\n", " ");
        if (item.content.length() > 100) display += "...";
        
        QListWidgetItem *listItem = new QListWidgetItem(display, m_historyList);
        listItem->setData(Qt::UserRole, item.content);
        listItem->setData(Qt::UserRole + 1, item.id);
        m_historyList->addItem(listItem);
    }
}

void MainWindow::createTrayIcon() {
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/logo.png"));
    m_trayIcon->setToolTip("Clipsmith");

    m_trayMenu = new QMenu(this);
    QAction *showAction = m_trayMenu->addAction("열기 (Open)");
    connect(showAction, &QAction::triggered, this, &MainWindow::showWindow);

    QAction *quitAction = m_trayMenu->addAction("종료 (Exit)");
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitApp);

    m_trayIcon->setContextMenu(m_trayMenu);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
    
    m_trayIcon->show();
}

void MainWindow::onNewContent(const QString &text) {
    m_dbManager->saveItem(text);
    refreshList();
    m_statusLabel->setText("새 내용이 저장되었습니다. (New content saved.)");
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
            QString display = item.content.left(100).replace("\n", " ");
            if (item.content.length() > 100) display += "...";
            
            QListWidgetItem *listItem = new QListWidgetItem(display, m_historyList);
            listItem->setData(Qt::UserRole, item.content);
            listItem->setData(Qt::UserRole + 1, item.id);
            m_historyList->addItem(listItem);
        }
    }
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item) {
    if (item) {
        actionCopyItem();
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
