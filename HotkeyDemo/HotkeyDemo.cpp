#include "HotkeyDemo.h"

HotkeyDemo::HotkeyDemo(QWidget *parent)
    : QWidget(parent),m_num(1)
{
    ui.setupUi(this);
}

void HotkeyDemo::on_btn_registerHotkey_clicked()
{
	QString keyStr = ui.keySeqEdit_main->keySequence().toString();

	if (keyStr.isEmpty())
	{
		QMessageBox::about(0, QString::fromLocal8Bit("失败"), QString::fromLocal8Bit("快捷键采集为空"));
		return;
	}

	//设置全局热键
	bool s = GlobalHotkey::getInstance().setHotkey(keyStr, m_num);
	if (s)
	{
		QMessageBox::about(0, QString::fromLocal8Bit("成功"), QString::fromLocal8Bit("注册热键成功:")+keyStr);
		m_hotkeyMap.insert(m_num, keyStr);
	}
	m_num++;

}

void HotkeyDemo::getHotkey(int hotkey)
{
	
	ui.textEdit_show->setPlainText(m_hotkeyMap.value(hotkey));

}
