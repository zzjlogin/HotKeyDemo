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
		QMessageBox::about(0, QString::fromLocal8Bit("ʧ��"), QString::fromLocal8Bit("��ݼ��ɼ�Ϊ��"));
		return;
	}

	//����ȫ���ȼ�
	bool s = GlobalHotkey::getInstance().setHotkey(keyStr, m_num);
	if (s)
	{
		QMessageBox::about(0, QString::fromLocal8Bit("�ɹ�"), QString::fromLocal8Bit("ע���ȼ��ɹ�:")+keyStr);
		m_hotkeyMap.insert(m_num, keyStr);
	}
	m_num++;

}

void HotkeyDemo::getHotkey(int hotkey)
{
	
	ui.textEdit_show->setPlainText(m_hotkeyMap.value(hotkey));

}
