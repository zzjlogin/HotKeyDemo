#include "HotkeyDemo.h"
#include <QtWidgets/QApplication>

#include "GlobalHotkey.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HotkeyDemo w;
	//过滤系统消息
	a.installNativeEventFilter(&GlobalHotkey::getInstance());
	
	//设置全局热键
	bool s = GlobalHotkey::getInstance().setHotkey("alt+q");
	
	//设置热键对象依赖主程序,关闭程序自动销毁对象
	GlobalHotkey::getInstance().setInstancParent(&w);
	
	//关联主程序
	QObject::connect(&GlobalHotkey::getInstance(), &GlobalHotkey::activeHotkeyEvent, &w, &HotkeyDemo::getHotkey);
	
	/*if (pHotKey->registerHotkey()) {
		QObject::connect(pHotKey, &GlobalHotkey::activateHotkey, &w, &HotkeyDemo::getHotkey);
	}*/
    w.show();
    return a.exec();
}
