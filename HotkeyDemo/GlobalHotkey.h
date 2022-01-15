#pragma once

#include <QObject>
#include <QKeySequence>
#include <QHash>
#include <QApplication>

#include "GlobalNativeEventFilter.h"


class GlobalHotkey;

class GlobalHotkey : public QObject
{
	Q_OBJECT

public:

	GlobalHotkey();

	GlobalHotkey(QObject *parent);

	~GlobalHotkey();
	

	bool registerHotkey();

	bool unregisterHotkey();

	bool setHotkey(QString keyStr);

	//QHash<QPair<quint32, quint32>, GlobalHotkey*> m_hotkey;

public slots:
	void on_activeHotkeyEvent();

private:
	
	GlobalNativeEventFilter *mp_nativeEventFilter;

	bool m_isRegistered;

	QApplication *mp_app;

	QKeySequence m_keySeq;
	Qt::Key m_keycode;
	Qt::KeyboardModifiers m_modifiers;

private:

	quint32 getNativeKeycode(Qt::Key keycode);

	quint32 getNativeModifiers(Qt::KeyboardModifiers modifiers);

signals:
	void activateHotkey();

};
