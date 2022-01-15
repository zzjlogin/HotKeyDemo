#include "HotkeyDemo.h"

HotkeyDemo::HotkeyDemo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void HotkeyDemo::getHotkey()
{
	QMessageBox::about(0, "tishi", "ha");
}
