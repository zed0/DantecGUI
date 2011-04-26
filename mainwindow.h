#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include "qextserialport.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QextSerialPort *commPort;

private slots:
	void receiveMsg();
	void transmitMsg();
	void moveTo();
	void calibrate();
	void sendCalibrate();
	void home();
};

#endif // MAINWINDOW_H
