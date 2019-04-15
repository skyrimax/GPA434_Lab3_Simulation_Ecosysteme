#pragma once

#include <QDialog>
#include <QMessageBox>
#include "ui_ParameterWindow.h"
#include "SimulationMainWindow.h"

class ParameterWindow : public QDialog, public Ui::ParameterWindow
{
	Q_OBJECT

public:
	ParameterWindow(QWidget *parent = Q_NULLPTR);
	~ParameterWindow()=default;


private slots:
	//Slots qui affiche l'aide des paramètres
	void showAide();
};
