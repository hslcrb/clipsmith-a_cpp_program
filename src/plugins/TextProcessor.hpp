#ifndef TEXTPROCESSOR_HPP
#define TEXTPROCESSOR_HPP

#include <QString>

class TextProcessor {
public:
    static QString prettifyJson(const QString &json);
    static QString toBase64(const QString &text);
    static QString fromBase64(const QString &base64);
    static QString cleanText(const QString &text);
};

#endif // TEXTPROCESSOR_HPP
