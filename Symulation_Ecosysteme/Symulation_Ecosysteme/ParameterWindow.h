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
	//Accesseur retournant les paramètres de population initial
	int getQteLapin();
	int getQteChevreuil();
	int getQteLoup();
	//Accesseur retourner le nombre de troupeau initial
	int getQteHorde();
	int getQteMeute();
	//Accesseur afin de déterminer si les mods on été cochés
	bool isSeasonCheck();
	bool isVirusCheck();

private slots:
	//Slots qui affiche l'aide des paramètres
	void showAide();
};
