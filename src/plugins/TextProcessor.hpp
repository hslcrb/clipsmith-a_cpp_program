#ifndef TEXTPROCESSOR_HPP
#define TEXTPROCESSOR_HPP

#include <QString>

enum class TextType {
    Text,
    Json,
    Base64,
    Url,
    Email
};

class TextProcessor {
public:
    static TextType detectType(const QString &text);
    static QString prettifyJson(const QString &json);
    static QString toBase64(const QString &text);
    static QString fromBase64(const QString &base64);
    static QString cleanText(const QString &text);
};

#endif // TEXTPROCESSOR_HPP
