#pragma once

#include <QDialog>
#include "ui_ParameterWindow.h"
#include "SimulationMainWindow.h"

class ParameterWindow : public QDialog, public Ui::ParameterWindow
{
	Q_OBJECT

public:
	ParameterWindow(QWidget *parent = Q_NULLPTR);
	~ParameterWindow();
	/*
	****ACCESSEURS****
	*/
	//Accesseur retournant les param�tres de population initial
	int getQteLapin();
	int getQteChevreuil();
	int getQteLoup();
	//Accesseur retourner le nombre de troupeau initial
	int getQteHorde();
	int getQteMeute();
	//Accesseur afin de d�terminer si les mods on �t� coch�s
	bool isSeasonCheck();
	bool isVirusCheck();

private slots:
	//Slots qui affiche l'aide des param�tres
	void showAide();
};
