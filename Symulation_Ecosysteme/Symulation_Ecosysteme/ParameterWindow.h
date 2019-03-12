#pragma once

#include <QDialog>
#include "ui_ParameterWindow.h"

class ParameterWindow : public QDialog, public Ui::ParameterWindow
{
	Q_OBJECT

public:
	ParameterWindow(QWidget *parent = Q_NULLPTR);
	~ParameterWindow();

private slots:

	void showAide();
};
