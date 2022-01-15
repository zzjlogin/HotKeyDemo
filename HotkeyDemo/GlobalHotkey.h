#pragma once

#include <QObject>
#include <QKeySequence>
#include <QHash>
#include <windows.h>
#include <QAbstractNativeEventFilter>
#include <QDebug>


class GlobalHotkey : public QObject, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:


	static GlobalHotkey& getInstance();

	void setInstancParent(QObject *parent);

	~GlobalHotkey();
	
	bool registerHotkey();

	bool unregisterHotkey();

	bool setHotkey(QString keyStr);

	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);



public slots:
	void on_activeHotkeyEvent();

private:



	quint32 getNativeKeycode(Qt::Key keycode);

	quint32 getNativeModifiers(Qt::KeyboardModifiers modifiers);

	GlobalHotkey();

	GlobalHotkey(QObject *parent);

private:
	

	static GlobalHotkey* mp_instance;

	bool m_isRegistered;

	QKeySequence m_keySeq;
	Qt::Key m_keycode;
	Qt::KeyboardModifiers m_modifiers;



signals:
	//
	void activateHotkey();
	
	void activeHotkeyEvent();
};
