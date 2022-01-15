#include "HotkeyDemo.h"
#include <QtWidgets/QApplication>

#include "GlobalHotkey.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HotkeyDemo w;
	//����ϵͳ��Ϣ
	a.installNativeEventFilter(&GlobalHotkey::getInstance());
	
	//����ȫ���ȼ�
	bool s = GlobalHotkey::getInstance().setHotkey("alt+q");
	
	//�����ȼ���������������,�رճ����Զ����ٶ���
	GlobalHotkey::getInstance().setInstancParent(&w);
	
	//����������
	QObject::connect(&GlobalHotkey::getInstance(), &GlobalHotkey::activeHotkeyEvent, &w, &HotkeyDemo::getHotkey);
	
	/*if (pHotKey->registerHotkey()) {
		QObject::connect(pHotKey, &GlobalHotkey::activateHotkey, &w, &HotkeyDemo::getHotkey);
	}*/
    w.show();
    return a.exec();
}
