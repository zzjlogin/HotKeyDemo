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
	//参考https://doc.qt.io/qt-5/qabstractnativeeventfilter.html
	if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
	{
		//消息结构类型转换
		//MSG *msg = static_cast<MSG *>(message);
		MSG *msg = reinterpret_cast<MSG *>(message);
		//如果消息类型是热键触发，则发射信号并返回true
		if (msg->message == WM_HOTKEY)
		{
			emit activeHotkeyEvent();
			return true;
		}
	}
	return false;
}
