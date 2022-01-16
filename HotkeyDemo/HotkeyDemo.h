#pragma once

#include <QtWidgets/QWidget>
#include "ui_HotkeyDemo.h"

#include <QMap>
#include <QMessageBox>

#include "GlobalHotkey.h"



class HotkeyDemo : public QWidget
{
    Q_OBJECT

public:
    HotkeyDemo(QWidget *parent = Q_NULLPTR);

public slots:
	
	void on_btn_registerHotkey_clicked();


	void getHotkey(int hotkey);


private:
    Ui::HotkeyDemoClass ui;

	int m_num;

	QMap<int, QString> m_hotkeyMap;

};
