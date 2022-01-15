#pragma once

#include <QObject>
#include <QKeySequence>
#include <QHash>
#include <windows.h>
#include <QAbstractNativeEventFilter>

class GlobalHotkey;

class GlobalHotkey : public QObject, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:

	GlobalHotkey();

	GlobalHotkey(QObject *parent);

	~GlobalHotkey();
	

	bool registerHotkey();

	bool unregisterHotkey();

	bool setHotkey(QString keyStr);

	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);

public slots:
	void on_activeHotkeyEvent();

private:
	
	bool m_isRegistered;

	QApplication *mp_app;

	QKeySequence m_keySeq;
	Qt::Key m_keycode;
	Qt::KeyboardModifiers m_modifiers;

private:

	quint32 getNativeKeycode(Qt::Key keycode);

	quint32 getNativeModifiers(Qt::KeyboardModifiers modifiers);

signals:
	//
	void activateHotkey();
	
	void activeHotkeyEvent();
};
