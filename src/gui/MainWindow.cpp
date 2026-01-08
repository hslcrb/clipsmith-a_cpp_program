/**
 * @file MainWindow.cpp
 * @brief 메인 윈도우 UI 및 사용자 인터페이스 로직 (Main Window UI and User Interface Logic)
 * 
 * Glassmorphism 및 Frutiger Aero 미학이 적용된 세련된 사용자 환경을 구현합니다.
 * Implements a sophisticated user environment with Glassmorphism and Frutiger Aero aesthetics.
 * 
 * @author Rheehose (Rhee Creative)
 * @date 2008-2026
 */

#include "MainWindow.hpp"
#include <QApplication>
#include <QStyle>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // DB 관리자 및 클립보드 모니터링 초기화
    // Initialize DB Manager and Clipboard Monitoring
    m_dbManager = new DatabaseManager(this);
    m_dbManager->init();

    m_cbMonitor = new ClipboardMonitor(this);
    connect(m_cbMonitor, &ClipboardMonitor::contentChanged, this, &MainWindow::onNewContent);

    // 환경 설정 및 UI 구성
    // Environment setup and UI configuration
    setupUi();
    createTrayIcon();
    refreshList();

    setWindowTitle("Clipsmith 🛠️");
    resize(480, 750);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);

    // 검색 박스 스타일링 (Glassmorphism & Frutiger Aero)
    // Search Box Styling
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("검색어를 입력하세요... (Search here...)");
    m_searchEdit->setMinimumHeight(45);
    m_searchEdit->setStyleSheet(
        "QLineEdit { "
        "  border: 1px solid rgba(255, 255, 255, 0.2); "
        "  border-radius: 12px; "
        "  padding: 10px 15px; "
        "  background: rgba(255, 255, 255, 0.1); "
        "  color: white; "
        "  font-family: 'Segoe UI', system-ui; "
        "} "
        "QLineEdit:focus { "
        "  border: 1px solid rgba(0, 120, 212, 0.8); "
        "  background: rgba(255, 255, 255, 0.15); "
        "}"
    );
    connect(m_searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);

    // 툴바 설정 (Glossy Glass Style)
    // Toolbar configuration
    m_toolBar = new QToolBar("Action Toolbar", this);
    m_toolBar->setIconSize(QSize(24, 24));
    m_toolBar->setStyleSheet(
        "QToolBar { "
        "  background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 0.2), stop:1 rgba(255, 255, 255, 0.05)); "
        "  border-radius: 12px; "
        "  padding: 5px; "
        "  spacing: 8px; "
        "  border: 1px solid rgba(255, 255, 255, 0.1); "
        "} "
        "QToolButton { color: white; border-radius: 8px; padding: 5px; } "
        "QToolButton:hover { background: rgba(255, 255, 255, 0.2); } "
        "QToolButton:disabled { color: rgba(255, 255, 255, 0.3); }"
    );

    m_prettifyAction = m_toolBar->addAction("✨ JSON 정리 (Prettify)");
    m_decodeAction = m_toolBar->addAction("🔓 Base64 디코드 (Decode)");
    m_cleanAction = m_toolBar->addAction("🧹 공백 제거 (Clean)");
    m_toolBar->addSeparator();
    m_copyAction = m_toolBar->addAction("📋 재복사 (Copy)");
    m_deleteAction = m_toolBar->addAction("🗑️ 삭제 (Delete)");

    m_prettifyAction->setEnabled(false);
    m_decodeAction->setEnabled(false);

    // 신호 연결
    // Signal connections
    connect(m_prettifyAction, &QAction::triggered, this, &MainWindow::actionPrettify);
    connect(m_decodeAction, &QAction::triggered, this, &MainWindow::actionBase64Decode);
    connect(m_cleanAction, &QAction::triggered, this, &MainWindow::actionCleanText);
    connect(m_copyAction, &QAction::triggered, this, &MainWindow::actionCopyItem);
    connect(m_deleteAction, &QAction::triggered, this, &MainWindow::actionDeleteItem);

    // 히스토리 리스트 위젯 스타일링 (Glassmorphism List)
    // History List Widget Styling
    m_historyList = new QListWidget(this);
    m_historyList->setStyleSheet(
        "QListWidget { "
        "  background: rgba(0, 0, 0, 0.2); "
        "  border: 1px solid rgba(255, 255, 255, 0.1); "
        "  border-radius: 15px; "
        "  color: #e0e0e0; "
        "  outline: none; "
        "  padding: 5px; "
        "} "
        "QListWidget::item { "
        "  padding: 15px; "
        "  border-bottom: 1px solid rgba(255, 255, 255, 0.05); "
        "  border-radius: 10px; "
        "  margin-bottom: 5px; "
        "  font-size: 13px; "
        "} "
        "QListWidget::item:selected { "
        "  background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 120, 212, 0.6), stop:1 rgba(0, 180, 255, 0.4)); "
        "  color: white; "
        "} "
        "QListWidget::item:hover { background: rgba(255, 255, 255, 0.05); }"
    );
    connect(m_historyList, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(m_historyList, &QListWidget::itemSelectionChanged, this, &MainWindow::onSelectionChanged);

    // 하단 상태 표시줄
    // Bottom Status Label
    m_statusLabel = new QLabel("🎨 Clipsmith 시각적 프리미엄 엔진 준비됨 (Premium UI Loaded)", this);
    m_statusLabel->setStyleSheet("color: rgba(255, 255, 255, 0.5); font-size: 11px; font-weight: bold;");

    mainLayout->addWidget(m_searchEdit);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_historyList);
    mainLayout->addWidget(m_statusLabel);

    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(":/logo.png"));
    
    // 전체 메인 윈도우 스타일 (Frutiger Aero Gradient)
    // Full MainWindow Style
    this->setStyleSheet(
        "QMainWindow { "
        "  background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #004b73, stop:0.5 #0078d4, stop:1 #00b4ff); "
        "} "
    );

    // 시스템 트레이 그림자 효과
    // Shadow effects
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 180));
    shadow->setOffset(0, 4);
    m_historyList->setGraphicsEffect(shadow);
}

void MainWindow::onSelectionChanged() {
    // 선택된 항목에 따른 액션 상태 업데이트
    // Update action states based on selected item
    QListWidgetItem *item = m_historyList->currentItem();
    if (!item) {
        m_prettifyAction->setEnabled(false);
        m_decodeAction->setEnabled(false);
        m_statusLabel->setText("항목을 선택하세요. (Select an item.)");
        return;
    }

    QString content = item->data(Qt::UserRole).toString();
    updateActionStates(content);
}

void MainWindow::updateActionStates(const QString &text) {
    // 텍스트 타입 감지 및 UI 업데이트
    // Detect text type and update UI
    TextType type = TextProcessor::detectType(text);
    m_prettifyAction->setEnabled(type == TextType::Json);
    m_decodeAction->setEnabled(type == TextType::Base64);
    
    QString typeStr = "일반 텍스트 (Text)";
    if (type == TextType::Json) typeStr = "JSON 데이터 (JSON)";
    else if (type == TextType::Url) typeStr = "웹 URL (URL)";
    else if (type == TextType::Email) typeStr = "이메일 (Email)";
    else if (type == TextType::Base64) typeStr = "Base64 데이터 (Base64)";
    
    m_statusLabel->setText(QString("🔍 감지됨 (Detected): %1 | 📏 크기: %2 chars").arg(typeStr).arg(text.length()));
}

void MainWindow::actionPrettify() {
    // JSON 정리 기능 (Prettify JSON)
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QString original = item->data(Qt::UserRole).toString();
        QString prettified = TextProcessor::prettifyJson(original);
        QApplication::clipboard()->setText(prettified);
        m_statusLabel->setText("✨ JSON 포맷팅 완료! 클립보드에 복사되었습니다. (JSON Prettified!)");
    }
}

void MainWindow::actionBase64Decode() {
    // Base64 디코딩 기능 (Base64 Decode)
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QString original = item->data(Qt::UserRole).toString();
        QString decoded = TextProcessor::fromBase64(original);
        QApplication::clipboard()->setText(decoded);
        m_statusLabel->setText("🔓 Base64 디코딩 완료! 클립보드에 복사되었습니다. (Base64 Decoded!)");
    }
}

void MainWindow::actionCleanText() {
    // 텍스트 정규화 기능 (Text Normalization)
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QString original = item->data(Qt::UserRole).toString();
        QString cleaned = TextProcessor::cleanText(original);
        QApplication::clipboard()->setText(cleaned);
        m_statusLabel->setText("🧹 텍스트 정리 완료! 클립보드에 복사되었습니다. (Text Cleaned!)");
    }
}

void MainWindow::actionCopyItem() {
    // 클립보드 재복사 (Recopy to clipboard)
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        QApplication::clipboard()->setText(item->data(Qt::UserRole).toString());
        m_statusLabel->setText("📋 클립보드에 다시 복사되었습니다. (Recopied.)");
    }
}

void MainWindow::actionDeleteItem() {
    // 항목 영구 삭제 (Permanent deletion)
    QListWidgetItem *item = m_historyList->currentItem();
    if (item) {
        int id = item->data(Qt::UserRole + 1).toInt();
        if (m_dbManager->deleteItem(id)) {
            refreshList();
            m_statusLabel->setText("🗑️ 항목이 삭제되었습니다. (Deleted.)");
        }
    }
}

void MainWindow::refreshList() {
    // 히스토리 리스트 갱신 (Refresh history list)
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
    // 시스템 트레이 아이콘 설정 (System Tray Icon Setup)
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/logo.png"));
    m_trayIcon->setToolTip("Clipsmith 🛠️");

    m_trayMenu = new QMenu(this);
    m_trayMenu->setStyleSheet("QMenu { background: #222; color: white; border: 1px solid #444; }");
    
    QAction *showAction = m_trayMenu->addAction("🔓 열기 (Open)");
    connect(showAction, &QAction::triggered, this, &MainWindow::showWindow);

    m_trayMenu->addSeparator();

    QAction *quitAction = m_trayMenu->addAction("❌ 종료 (Exit)");
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitApp);

    m_trayIcon->setContextMenu(m_trayMenu);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
    
    m_trayIcon->show();
}

void MainWindow::onNewContent(const QString &text) {
    // 클립보드 변화 감지 시 저장 처리 (Handle storage on clipboard change)
    m_dbManager->saveItem(text);
    refreshList();
    m_statusLabel->setText("📥 새로운 클립보드 내용 감지됨. (New content captured.)");
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        showWindow();
    }
}

void MainWindow::onSearchChanged(const QString &text) {
    // 검색 필터링 로직 (Search filtering logic)
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
    // 창 표시 및 활성화 (Show and activate window)
    this->show();
    this->raise();
    this->activateWindow();
}

void MainWindow::quitApp() {
    // 애플리케이션 안전 종료 (Safe application exit)
    QApplication::quit();
}
