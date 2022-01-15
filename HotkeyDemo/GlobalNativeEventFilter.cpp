#include "GlobalNativeEventFilter.h"

GlobalNativeEventFilter::GlobalNativeEventFilter(QObject *parent)
{

}

GlobalNativeEventFilter::GlobalNativeEventFilter()
{

}

GlobalNativeEventFilter::~GlobalNativeEventFilter()
{
}

bool GlobalNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
	//�ο�https://doc.qt.io/qt-5/qabstractnativeeventfilter.html
	if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
	{
		//��Ϣ�ṹ����ת��
		//MSG *msg = static_cast<MSG *>(message);
		MSG *msg = reinterpret_cast<MSG *>(message);
		//�����Ϣ�������ȼ������������źŲ�����true
		if (msg->message == WM_HOTKEY)
		{
			emit activeHotkeyEvent();
			return true;
		}
	}
	return false;
}
