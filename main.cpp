#include <QApplication>
#include "getvideo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc >= 2) {
        if (QString(argv[1]) == "PLAY_VIDEO") {
            GetVideo* getVideo = new GetVideo();
        } else if (QString(argv[1]) == "ENABLE_AUTO_RUN") { // 开启自启动
            QSettings* settings = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings->setValue("EverydayVideo", "\"" + qApp->applicationFilePath().replace("/", "\\") + "\" PLAY_VIDEO");
            QApplication::quit();
        } else if (QString(argv[1]) == "DISANLE_AUTO_RUN") { // 关闭自启动
            QSettings* settings = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings->remove("EverydayVideo");
            QApplication::quit();
        } else if (QString(argv[1]) == "ADD_RIGHT_CLICK_MENU_ACTION") { // 添加右键菜单
            QSettings* settings = new QSettings("HKEY_CLASSES_ROOT\\DesktopBackground\\Shell\\PlayEverydayVideo", QSettings::NativeFormat);
            settings->setValue(".", "播放每日视频");
            settings->setValue("icon", "\"" + qApp->applicationFilePath().replace("/", "\\") + "\"");
            QSettings* command = new QSettings("HKEY_CLASSES_ROOT\\DesktopBackground\\Shell\\PlayEverydayVideo\\command", QSettings::NativeFormat);
            command->setValue(".", "\"" + qApp->applicationFilePath().replace("/", "\\") + "\" PLAY_VIDEO");
            QApplication::quit();
        } else if (QString(argv[1]) == "REMOVE_RIGHT_CLICK_MENU_ACTION") { // 移除右键菜单
            QSettings* settings = new QSettings("HKEY_CLASSES_ROOT\\DesktopBackground\\Shell", QSettings::NativeFormat);
            settings->remove("PlayEverydayVideo");
            QApplication::quit();
        } else {
                GetVideo* getVideo = new GetVideo();
        }
    } else {
            GetVideo* getVideo = new GetVideo();
    }

    return a.exec();
}
