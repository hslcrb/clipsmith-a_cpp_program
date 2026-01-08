/**
 * @file DatabaseManager.hpp
 * @brief SQLite 데이터베이스 관리 클래스 (SQLite Database Management Class)
 * 
 * 이 클래스는 클립보드 히스토리를 SQLite 데이터베이스에 저장하고 관리하는 기능을 담당합니다.
 * This class handles saving and managing clipboard history in an SQLite database.
 * 
 * @author Rheehose (Rhee Creative)
 * @date 2008-2026
 */

#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

/**
 * @struct ClipboardItem
 * @brief 클립보드 항목을 나타내는 구조체 (Structure representing a clipboard item)
 */
struct ClipboardItem {
    int id;                 ///< 고유 ID (Unique ID)
    QString content;        ///< 복사된 내용 (Copied content)
    QDateTime timestamp;    ///< 복사된 시간 (Time of copy)
    bool isPinned;          ///< 고정 여부 (Whether it is pinned)
    QString type;           ///< 데이터 타입 (Data type: Text, JSON, etc.)
};

/**
 * @class DatabaseManager
 * @brief 데이터베이스 CRUD 작업을 수행하는 클래스 (Class for database CRUD operations)
 */
class DatabaseManager : public QObject {
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    /**
     * @brief 데이터베이스 초기화 및 테이블 생성 (Initialize database and create tables)
     * @return 성공 여부 (Success or failure)
     */
    bool init();

    /**
     * @brief 새로운 클립보드 항목 저장 (Save a new clipboard item)
     * @param content 내용 (Content)
     * @param type 타입 (Type)
     * @return 성공 여부 (Success or failure)
     */
    bool saveItem(const QString &content, const QString &type = "text");

    /**
     * @brief 모든 히스토리 항목 가져오기 (Retreive all history items)
     * @return 항목 리스트 (List of items)
     */
    QList<ClipboardItem> getAllItems();

    /**
     * @brief 특정 항목 삭제 (Delete a specific item)
     * @param id 항목 ID (Item ID)
     * @return 성공 여부 (Success or failure)
     */
    bool deleteItem(int id);

    /**
     * @brief 항목 고정 상태 전환 (Toggle pin status of an item)
     * @param id 항목 ID (Item ID)
     * @param pinned 고정 여부 (Pin status)
     * @return 성공 여부 (Success or failure)
     */
    bool togglePin(int id, bool pinned);

    /**
     * @brief 검색어로 항목 찾기 (Search items by query)
     * @param query 검색어 (Search query)
     * @return 검색된 항목 리스트 (List of searched items)
     */
    QList<ClipboardItem> searchItems(const QString &query);

private:
    QSqlDatabase m_db; ///< SQLite 데이터베이스 인스턴스 (SQLite Database Instance)
};

#endif // DATABASEMANAGER_HPP
