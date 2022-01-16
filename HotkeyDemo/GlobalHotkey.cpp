#include "GlobalHotkey.h"

GlobalHotkey::GlobalHotkey(QObject *parent)
	: QObject(parent),m_isRegistered(false)
{
	
}

GlobalHotkey::GlobalHotkey()
	: m_isRegistered(false)
{
	
}


GlobalHotkey* GlobalHotkey::mp_instance = nullptr;

GlobalHotkey& GlobalHotkey::getInstance()
{
	if (mp_instance == nullptr)
	{
		mp_instance = new GlobalHotkey;
	}
	
	return *mp_instance;
}

void GlobalHotkey::setInstancParent(QObject *parent)
{
	mp_instance->setParent(parent);
}

GlobalHotkey::~GlobalHotkey()
{
	if (!m_hotkeyIndex.isEmpty())
	{
		undoAllHotkey();
	}
}



int GlobalHotkey::undoAllHotkey()
{
	int count(0);
	for(QHash<QPair<quint32, quint32>, int>::iterator it = m_hotkeyIndex.begin();it != m_hotkeyIndex.end(); ++it)
	{
		QPair<quint32, quint32> temp = it.key();
		bool ret = UnregisterHotKey(0, temp.second ^ temp.first);
		count++;
	}
	
	m_hotkeyIndex.clear();
	return count;
}


bool GlobalHotkey::setHotkey(const QString& keyStr, int signalIndex)
{
	QKeySequence keySeq = QKeySequence(keyStr);
	Qt::KeyboardModifiers allMods = Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;
	m_keycode = (keySeq.isEmpty() ? Qt::Key(0) : Qt::Key((keySeq[0] ^ allMods) & keySeq[0]));
	m_modifiers = keySeq.isEmpty() ? Qt::KeyboardModifiers(0) : Qt::KeyboardModifiers(keySeq[0] & allMods);

	const quint32 nativeKey = getNativeKeycode(m_keycode);
	const quint32 nativeMods = getNativeModifiers(m_modifiers);

	if (m_hotkeyIndex.contains(qMakePair(nativeKey, nativeMods)))
	{
		return false;
	}

	
	//m_hotkey.insert(qMakePair(nativeKey, nativeMods), this);
	if (RegisterHotKey(0, nativeMods ^ nativeKey, nativeMods, nativeKey)) {
		m_isRegistered = true;
		m_hotkeyIndex.insert(qMakePair(nativeKey, nativeMods), signalIndex);
		return true;
	}
	else {
		m_isRegistered = false;
		return false;
	}
}

bool GlobalHotkey::undoSetHotkey(const QString& keyStr)
{
	QKeySequence keySeq = QKeySequence(keyStr);
	Qt::KeyboardModifiers allMods = Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;
	m_keycode = (keySeq.isEmpty() ? Qt::Key(0) : Qt::Key((keySeq[0] ^ allMods) & keySeq[0]));
	m_modifiers = keySeq.isEmpty() ? Qt::KeyboardModifiers(0) : Qt::KeyboardModifiers(keySeq[0] & allMods);

	const quint32 nativeKey = getNativeKeycode(m_keycode);
	const quint32 nativeMods = getNativeModifiers(m_modifiers);


	if (m_hotkeyIndex.remove(qMakePair(nativeKey, nativeMods)))
	{
		return UnregisterHotKey(0, nativeMods ^ nativeKey);
	}
	//没有设置此快捷键，返回false
	return false;
	
}

bool GlobalHotkey::nativeEventFilter(const QByteArray &eventType, void *message, long *)
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
			const quint32 keycode = HIWORD(msg->lParam);
			const quint32 modifiers = LOWORD(msg->lParam);
			int hotkeyIndex = m_hotkeyIndex.value(qMakePair(keycode, modifiers));
			
			emit hotkeyPressEvent(hotkeyIndex);


			return true;
		}
	}
	return false;
}

//void GlobalHotkey::on_activeHotkeyEvent()
//{
//	emit activateHotkey();
//}

quint32 GlobalHotkey::getNativeKeycode(Qt::Key keycode)
{
	switch (keycode)
	{
	case Qt::Key_Escape:
		return VK_ESCAPE;
	case Qt::Key_Tab:
	case Qt::Key_Backtab:
		return VK_TAB;
	case Qt::Key_Backspace:
		return VK_BACK;
	case Qt::Key_Return:
	case Qt::Key_Enter:
		return VK_RETURN;
	case Qt::Key_Insert:
		return VK_INSERT;
	case Qt::Key_Delete:
		return VK_DELETE;
	case Qt::Key_Pause:
		return VK_PAUSE;
	case Qt::Key_Print:
		return VK_PRINT;
	case Qt::Key_Clear:
		return VK_CLEAR;
	case Qt::Key_Home:
		return VK_HOME;
	case Qt::Key_End:
		return VK_END;
	case Qt::Key_Left:
		return VK_LEFT;
	case Qt::Key_Up:
		return VK_UP;
	case Qt::Key_Right:
		return VK_RIGHT;
	case Qt::Key_Down:
		return VK_DOWN;
	case Qt::Key_PageUp:
		return VK_PRIOR;
	case Qt::Key_PageDown:
		return VK_NEXT;
	case Qt::Key_F1:
		return VK_F1;
	case Qt::Key_F2:
		return VK_F2;
	case Qt::Key_F3:
		return VK_F3;
	case Qt::Key_F4:
		return VK_F4;
	case Qt::Key_F5:
		return VK_F5;
	case Qt::Key_F6:
		return VK_F6;
	case Qt::Key_F7:
		return VK_F7;
	case Qt::Key_F8:
		return VK_F8;
	case Qt::Key_F9:
		return VK_F9;
	case Qt::Key_F10:
		return VK_F10;
	case Qt::Key_F11:
		return VK_F11;
	case Qt::Key_F12:
		return VK_F12;
	case Qt::Key_F13:
		return VK_F13;
	case Qt::Key_F14:
		return VK_F14;
	case Qt::Key_F15:
		return VK_F15;
	case Qt::Key_F16:
		return VK_F16;
	case Qt::Key_F17:
		return VK_F17;
	case Qt::Key_F18:
		return VK_F18;
	case Qt::Key_F19:
		return VK_F19;
	case Qt::Key_F20:
		return VK_F20;
	case Qt::Key_F21:
		return VK_F21;
	case Qt::Key_F22:
		return VK_F22;
	case Qt::Key_F23:
		return VK_F23;
	case Qt::Key_F24:
		return VK_F24;
	case Qt::Key_Space:
		return VK_SPACE;
	case Qt::Key_Asterisk:
		return VK_MULTIPLY;
	case Qt::Key_Plus:
		return VK_ADD;
	case Qt::Key_Comma:
		return VK_SEPARATOR;
	case Qt::Key_Minus:
		return VK_SUBTRACT;
	case Qt::Key_Slash:
		return VK_DIVIDE;

		// numbers
	case Qt::Key_0:
	case Qt::Key_1:
	case Qt::Key_2:
	case Qt::Key_3:
	case Qt::Key_4:
	case Qt::Key_5:
	case Qt::Key_6:
	case Qt::Key_7:
	case Qt::Key_8:
	case Qt::Key_9:

		// letters
	case Qt::Key_A:
	case Qt::Key_B:
	case Qt::Key_C:
	case Qt::Key_D:
	case Qt::Key_E:
	case Qt::Key_F:
	case Qt::Key_G:
	case Qt::Key_H:
	case Qt::Key_I:
	case Qt::Key_J:
	case Qt::Key_K:
	case Qt::Key_L:
	case Qt::Key_M:
	case Qt::Key_N:
	case Qt::Key_O:
	case Qt::Key_P:
	case Qt::Key_Q:
	case Qt::Key_R:
	case Qt::Key_S:
	case Qt::Key_T:
	case Qt::Key_U:
	case Qt::Key_V:
	case Qt::Key_W:
	case Qt::Key_X:
	case Qt::Key_Y:
	case Qt::Key_Z:
		return keycode;

	default:
		return 0;
	}
}

quint32 GlobalHotkey::getNativeModifiers(Qt::KeyboardModifiers modifiers)
{
	// MOD_ALT, MOD_CONTROL, (MOD_KEYUP), MOD_SHIFT, MOD_WIN
	quint32 native = 0;
	if (modifiers & Qt::ShiftModifier)
		native |= MOD_SHIFT;
	if (modifiers & Qt::ControlModifier)
		native |= MOD_CONTROL;
	if (modifiers & Qt::AltModifier)
		native |= MOD_ALT;
	if (modifiers & Qt::MetaModifier)
		native |= MOD_WIN;
	// TODO: resolve these?
	//if (modifiers & Qt::KeypadModifier)
	//if (modifiers & Qt::GroupSwitchModifier)
	return native;
}
