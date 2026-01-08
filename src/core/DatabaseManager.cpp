#include "DatabaseManager.hpp"

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::init() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("clipsmith.db");

    if (!m_db.open()) {
        qDebug() << "데이터베이스 연결 실패:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS clipboard_history ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "content TEXT NOT NULL, "
                          "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
                          "is_pinned INTEGER DEFAULT 0, "
                          "type TEXT DEFAULT 'text')";
    
    if (!query.exec(createTable)) {
        qDebug() << "테이블 생성 실패:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::saveItem(const QString &content, const QString &type) {
    QSqlQuery query;
    query.prepare("INSERT INTO clipboard_history (content, type) VALUES (:content, :type)");
    query.bindValue(":content", content);
    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "데이터 저장 실패:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<ClipboardItem> DatabaseManager::getAllItems() {
    QList<ClipboardItem> items;
    QSqlQuery query("SELECT id, content, timestamp, is_pinned, type FROM clipboard_history ORDER BY is_pinned DESC, timestamp DESC");
    
    while (query.next()) {
        ClipboardItem item;
        item.id = query.value(0).toInt();
        item.content = query.value(1).toString();
        item.timestamp = query.value(2).toDateTime();
        item.isPinned = query.value(3).toBool();
        item.type = query.value(4).toString();
        items.append(item);
    }
    return items;
}

bool DatabaseManager::deleteItem(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM clipboard_history WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool DatabaseManager::togglePin(int id, bool pinned) {
    QSqlQuery query;
    query.prepare("UPDATE clipboard_history SET is_pinned = :pinned WHERE id = :id");
    query.bindValue(":pinned", pinned ? 1 : 0);
    query.bindValue(":id", id);
    return query.exec();
}

QList<ClipboardItem> DatabaseManager::searchItems(const QString &searchQuery) {
    QList<ClipboardItem> items;
    QSqlQuery query;
    query.prepare("SELECT id, content, timestamp, is_pinned, type FROM clipboard_history "
                  "WHERE content LIKE :query ORDER BY is_pinned DESC, timestamp DESC");
    query.bindValue(":query", "%" + searchQuery + "%");
    
    if (query.exec()) {
        while (query.next()) {
            ClipboardItem item;
            item.id = query.value(0).toInt();
            item.content = query.value(1).toString();
            item.timestamp = query.value(2).toDateTime();
            item.isPinned = query.value(3).toBool();
            item.type = query.value(4).toString();
            items.append(item);
        }
    }
    return items;
}
