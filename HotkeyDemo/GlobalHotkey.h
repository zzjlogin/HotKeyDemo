#ifndef     __GLOBALHOTKEY__
#define     __GLOBALHOTKEY__
/*******************************
 * date 2022/01/16 17:18
 * author admin
 *******************************/

#include <QObject>
#include <QKeySequence>
#include <QMap>
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




	int undoAllHotkey();

	bool setHotkey(const QString& keyStr, int signalIndex);

	bool undoSetHotkey(const QString& keyStr);

	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);





private:



	quint32 getNativeKeycode(Qt::Key keycode);

	quint32 getNativeModifiers(Qt::KeyboardModifiers modifiers);

	GlobalHotkey();

	GlobalHotkey(QObject *parent);

private:
	QHash<QPair<quint32, quint32>, int> m_hotkeyIndex;

	static GlobalHotkey* mp_instance;

	bool m_isRegistered;

	QKeySequence m_keySeq;
	Qt::Key m_keycode;
	Qt::KeyboardModifiers m_modifiers;



signals:



	void hotkeyPressEvent(int);
};


#endif

