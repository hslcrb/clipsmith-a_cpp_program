#include "TextProcessor.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QByteArray>
#include <QRegularExpression>

TextType TextProcessor::detectType(const QString &text) {
    QString trimmed = text.trimmed();
    
    // JSON 감지
    if ((trimmed.startsWith("{") && trimmed.endsWith("}")) || 
        (trimmed.startsWith("[") && trimmed.endsWith("]"))) {
        QJsonParseError error;
        QJsonDocument::fromJson(trimmed.toUtf8(), &error);
        if (error.error == QJsonParseError::NoError) return TextType::Json;
    }

    // URL 감지
    static QRegularExpression urlRegex("^(https?|ftp)://[\\w.-]+(?:\\.[\\w.-]+)+[\\w\\-_~:/?#\\[\\]@!$&'()*+,;=.]+$");
    if (urlRegex.match(trimmed).hasMatch()) return TextType::Url;

    // Email 감지
    static QRegularExpression emailRegex("^[\\w.!#$%&'*+/=?^_`{|}~-]+@[\\w](?:[\\w-]{0,61}[\\w])?(?:\\.[\\w](?:[\\w-]{0,61}[\\w])?)*$");
    if (emailRegex.match(trimmed).hasMatch()) return TextType::Email;

    // Base64 감지 (어느 정도 정확도가 낮을 수 있음)
    static QRegularExpression b64Regex("^[A-Za-z0-9+/]+={0,2}$");
    if (trimmed.length() > 8 && trimmed.length() % 4 == 0 && b64Regex.match(trimmed).hasMatch()) {
        return TextType::Base64;
    }

    return TextType::Text;
}

QString TextProcessor::prettifyJson(const QString &json) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        return "Invalid JSON";
    }
    return doc.toJson(QJsonDocument::Indented);
}

QString TextProcessor::toBase64(const QString &text) {
    return QString(text.toUtf8().toBase64());
}

QString TextProcessor::fromBase64(const QString &base64) {
    QByteArray decoded = QByteArray::fromBase64(base64.toUtf8());
    return QString::fromUtf8(decoded);
}

QString TextProcessor::cleanText(const QString &text) {
    QString cleaned = text.trimmed();
    // 연속된 공백을 하나로 변경하거나 불필요한 줄바꿈 정리
    cleaned = cleaned.replace(QRegularExpression("\\s+"), " ");
    return cleaned;
}
