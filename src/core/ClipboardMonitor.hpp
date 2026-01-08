/**
 * @file ClipboardMonitor.hpp
 * @brief 시스템 클립보드 감시 클래스 (System Clipboard Monitoring Class)
 * 
 * 운영체제의 클립보드 변화를 실시간으로 감지하여 신호를 발생시킵니다.
 * Detects system clipboard changes in real-time and emits signals.
 * 
 * @author Rheehose (Rhee Creative)
 * @date 2008-2026
 */

#ifndef CLIPBOARDMONITOR_HPP
#define CLIPBOARDMONITOR_HPP

#include <QObject>
#include <QClipboard>
#include <QMimeData>
#include <QApplication>

/**
 * @class ClipboardMonitor
 * @brief 클립보드 감시 엔진 (Clipboard Monitoring Engine)
 */
class ClipboardMonitor : public QObject {
    Q_OBJECT
public:
    explicit ClipboardMonitor(QObject *parent = nullptr);

signals:
    /**
     * @brief 클립보드 내용이 변경되었을 때 발생하는 신호 (Signal emitted when clipboard content changes)
     * @param text 새로운 내용 (New content)
     */
    void contentChanged(const QString &text);

private slots:
    /**
     * @brief 시스템 클립보드 신호를 처리하는 내부 슬롯 (Internal slot to handle system clipboard signal)
     */
    void onClipboardChanged();

private:
    QClipboard *m_clipboard; ///< 시스템 클립보드 포인터 (Pointer to system clipboard)
};

#endif // CLIPBOARDMONITOR_HPP
