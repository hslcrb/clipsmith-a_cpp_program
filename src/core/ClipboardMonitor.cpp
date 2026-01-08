#include "ClipboardMonitor.hpp"

ClipboardMonitor::ClipboardMonitor(QObject *parent) : QObject(parent) {
    m_clipboard = QApplication::clipboard();
    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardMonitor::onClipboardChanged);
}

void ClipboardMonitor::onClipboardChanged() {
    const QMimeData *mimeData = m_clipboard->mimeData();
    if (mimeData->hasText()) {
        QString text = mimeData->text();
        if (!text.isEmpty()) {
            emit contentChanged(text);
        }
    }
}
