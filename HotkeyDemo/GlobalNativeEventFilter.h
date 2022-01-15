#pragma once

#include <QAbstractNativeEventFilter>
#include <QObject>
#include <windows.h>
#include <QDebug>

class GlobalNativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:
	GlobalNativeEventFilter(QObject *parent);
	
	GlobalNativeEventFilter();
	
	~GlobalNativeEventFilter();

	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);

signals:
	void activeHotkeyEvent();


};
