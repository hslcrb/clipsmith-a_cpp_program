#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

struct ClipboardItem {
    int id;
    QString content;
    QDateTime timestamp;
    bool isPinned;
    QString type;
};

class DatabaseManager : public QObject {
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool init();
    bool saveItem(const QString &content, const QString &type = "text");
    QList<ClipboardItem> getAllItems();
    bool deleteItem(int id);
    bool togglePin(int id, bool pinned);
    QList<ClipboardItem> searchItems(const QString &query);

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_HPP
