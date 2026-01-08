/**
 * @file TextProcessor.hpp
 * @brief 텍스트 분석 및 가공 유틸리티 클래스 (Text Analysis and Processing Utility Class)
 * 
 * 다양한 텍스트 패턴(JSON, URL 등)을 감지하고 가공하는 정적 메소드를 제공합니다.
 * Provides static methods for detecting and processing various text patterns.
 * 
 * @author Rheehose (Rhee Creative)
 * @date 2008-2026
 */

#ifndef TEXTPROCESSOR_HPP
#define TEXTPROCESSOR_HPP

#include <QString>

/**
 * @enum TextType
 * @brief 감지된 텍스트의 데이터 유형 (Data types of detected text)
 */
enum class TextType {
    Text,   ///< 일반 텍스트 (Plain Text)
    Json,   ///< JSON 데이터 (JSON Data)
    Base64, ///< Base64 인코딩 (Base64 Encoded)
    Url,    ///< 웹 URL (Web URL)
    Email   ///< 이메일 주소 (Email Address)
};

/**
 * @class TextProcessor
 * @brief 텍스트 가공 엔진 (Text Processing Engine)
 */
class TextProcessor {
public:
    /**
     * @brief 텍스트의 데이터 유형 감지 (Detect data type of text)
     * @param text 분석할 텍스트 (Text to analyze)
     * @return 감지된 유형 (Detected type)
     */
    static TextType detectType(const QString &text);

    /**
     * @brief JSON 문자열 보기 좋게 정리 (Prettify JSON string)
     * @param json 원본 JSON (Original JSON)
     * @return 정리된 JSON (Formatted JSON)
     */
    static QString prettifyJson(const QString &json);

    /**
     * @brief 텍스트를 Base64로 인코딩 (Encode text to Base64)
     * @param text 원문 (Original text)
     * @return 인코딩된 문자열 (Encoded string)
     */
    static QString toBase64(const QString &text);

    /**
     * @brief Base64를 일반 텍스트로 디코딩 (Decode Base64 to plain text)
     * @param base64 인코딩된 문자열 (Encoded string)
     * @return 디코딩된 원문 (Decoded text)
     */
    static QString fromBase64(const QString &base64);

    /**
     * @brief 텍스트 공백 및 줄바꿈 정리 (Normalize whitespace and newlines)
     * @param text 원문 (Original text)
     * @return 정리된 텍스트 (Cleaned text)
     */
    static QString cleanText(const QString &text);
};

#endif // TEXTPROCESSOR_HPP
