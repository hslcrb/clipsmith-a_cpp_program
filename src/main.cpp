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

    MainWindow window;
    // 초기에는 트레이 아이콘만 표시되도록 설정할 수 있습니다.
    // window.show(); 

    return app.exec();
}
