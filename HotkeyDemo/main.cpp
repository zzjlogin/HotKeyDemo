#include "HotkeyDemo.h"
#include <QtWidgets/QApplication>

#include "GlobalHotkey.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HotkeyDemo w;

	GlobalHotkey *pHotKey = new GlobalHotkey(&w);

	bool s = pHotKey->setHotkey("ctrl+b");
	if (pHotKey->registerHotkey()) {
		QObject::connect(pHotKey, &GlobalHotkey::activateHotkey, &w, &HotkeyDemo::getHotkey);
	}
    w.show();
    return a.exec();
}
