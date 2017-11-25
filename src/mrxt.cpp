
#include "team.h"
#include "simulatedModel.h"
#include "time.h"
#include <opencv2/opencv.hpp>
#include <QApplication>
//#include "ui_mainWindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QDir>

using namespace std;


/*! \mainpage Multi-Robot eXploration Tool Documentation
 *
 * This is source code documentation.
 *
 * Visit http://arvc.umh.es/~mjulia/mrxt for a general description of the application.
 *
 */
int main(int argc, char **argv)
{

	QApplication app( argc, argv );

	MainWindow mywin;

	app.exec();


	return (0);
} 

