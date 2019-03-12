#include "stdafx.h"
#include "SimulationMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimulationMainWindow w;
	w.show();
	return a.exec();
}
