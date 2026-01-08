#ifndef CLIPBOARDMONITOR_HPP
#define CLIPBOARDMONITOR_HPP

#include <QObject>
#include <QClipboard>
#include <QMimeData>
#include <QApplication>

class ClipboardMonitor : public QObject {
    Q_OBJECT
public:
    explicit ClipboardMonitor(QObject *parent = nullptr);

signals:
    void contentChanged(const QString &text);

private slots:
    void onClipboardChanged();

private:
    QClipboard *m_clipboard;
};

#endif // CLIPBOARDMONITOR_HPP
