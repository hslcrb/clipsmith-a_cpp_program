#include "TextProcessor.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QByteArray>

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
