#include "HotkeyDemo.h"
#include <QtWidgets/QApplication>

#include "GlobalHotkey.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HotkeyDemo w;

	//GlobalHotkey *pHotKey = new GlobalHotkey(&w);
	GlobalHotkey pHotKey(&w);
	a.installNativeEventFilter(&pHotKey);
	bool s = pHotKey.setHotkey("ctrl+b");
	QObject::connect(&pHotKey, &GlobalHotkey::activeHotkeyEvent, &w, &HotkeyDemo::getHotkey);
	/*if (pHotKey->registerHotkey()) {
		QObject::connect(pHotKey, &GlobalHotkey::activateHotkey, &w, &HotkeyDemo::getHotkey);
	}*/
    w.show();
    return a.exec();
}
