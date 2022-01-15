#pragma once

#include <QtWidgets/QWidget>
#include "ui_HotkeyDemo.h"

#include <QMessageBox>

class HotkeyDemo : public QWidget
{
    Q_OBJECT

public:
    HotkeyDemo(QWidget *parent = Q_NULLPTR);

public slots:
	void getHotkey();


private:
    Ui::HotkeyDemoClass ui;



};
