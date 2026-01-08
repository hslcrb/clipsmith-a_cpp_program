#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include "gui/MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, "Clipsmith", "시스템 트레이를 사용할 수 없는 환경입니다.");
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);
    app.setWindowIcon(QIcon(":/logo.png"));

    MainWindow window;
    window.show(); 

    return app.exec();
}
