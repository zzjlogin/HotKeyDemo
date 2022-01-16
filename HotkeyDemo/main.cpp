#include "HotkeyDemo.h"
#include <QtWidgets/QApplication>

#include "GlobalHotkey.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HotkeyDemo w;
	//�����ȼ���������������,�رճ����Զ����ٶ���
	GlobalHotkey::getInstance().setInstancParent(&w);

	//����ϵͳ��Ϣ
	a.installNativeEventFilter(&GlobalHotkey::getInstance());
	

	
	
	//����������
	QObject::connect(&GlobalHotkey::getInstance(), &(GlobalHotkey::hotkeyPressEvent), &w, &(HotkeyDemo::getHotkey));
	
	/*if (pHotKey->registerHotkey()) {
		QObject::connect(pHotKey, &GlobalHotkey::activateHotkey, &w, &HotkeyDemo::getHotkey);
	}*/
    w.show();
    return a.exec();
}
