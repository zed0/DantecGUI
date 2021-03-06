#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	qDebug("Creating QextSerialPort instance");
	commPort = new QextSerialPort();
	commPort->setPortName(QString("COM5"));
	commPort->setDataBits(DATA_8);
	commPort->setParity(PAR_NONE);
	commPort->setFlowControl(FLOW_HARDWARE);
	commPort->setStopBits(STOP_1);
	commPort->setBaudRate(BAUD9600);
	commPort->open(QIODevice::ReadWrite);

	QTimer *receiveTimer = new QTimer(this);
	connect(receiveTimer, SIGNAL(timeout()), SLOT(receiveMsg()));
	receiveTimer->start(0);
	QString text = "@07\x0D\x0A";
	int i = commPort->write(text.toAscii(), text.length());
	ui->textBrowser->append("Sending ready signal...");
	ui->textBrowser->append("-> "+text);
	qDebug(text.toAscii());
	qDebug("trasmitted : %d", i);

	QTimer::singleShot(300, this, SLOT(sendCalibrate()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::receiveMsg()
{
	int numBytes = commPort->bytesAvailable();
	if(numBytes > 0) {
		if(numBytes > 80) numBytes = 80;
		char buff[80];

		int i = commPort->read(buff, numBytes);
		buff[numBytes] = '\0';
		QString msg = buff;

		ui->textBrowser->append("<- "+msg);
		qDebug("received : %d", i);
	}
}

void MainWindow::transmitMsg()
{
	QString text = ui->lineEdit->text()+"\x0D\x0A";
	int i = commPort->write(text.toAscii(), text.length());
	ui->textBrowser->append("-> "+text);
	qDebug(text.toAscii());
	qDebug("trasmitted : %d", i);
}

void MainWindow::moveTo()
{
	int x = 0;
	int y = 0;
	int z = 0;
	if(ui->checkBox->isChecked())
	{
		x = ui->horizontalSlider->value();
	}
	if(ui->checkBox_2->isChecked())
	{
		y = ui->horizontalSlider_2->value();
	}
	if(ui->checkBox_3->isChecked())
	{
		z = ui->horizontalSlider_3->value();
	}

	QString text = "@0M";
	text.append(QString::number(x*16));
	text.append(",4000,");
	text.append(QString::number(y*16));
	text.append(",4000,");
	text.append(QString::number(y*16));
	text.append(",4000,0,2500");
	text.append("\x0D\x0A");

	int i = commPort->write(text.toAscii(), text.length());
	ui->textBrowser->append(QString("Moving to ")+QString::number(x)+","+QString::number(y)+","+QString::number(z)+"...");
	ui->textBrowser->append("-> "+text);
	qDebug(text.toAscii());
	qDebug("trasmitted : %d", i);
}

void MainWindow::calibrate()
{
	int originalX = ui->horizontalSlider->value();
	int originalY = ui->horizontalSlider->value();
	int originalZ = ui->horizontalSlider->value();

	int currentX = originalX;
	int currentY = originalY;
	int currentZ = originalZ;

	int increment = 2;
	QTime myTimer;
	myTimer.start();

	while(currentX <= 100 && currentY <= 100 && currentZ <= 100)
	{
		currentX += increment;
		currentY += increment;
		currentZ += increment;

		QString text = "@0M";
		text.append(QString::number(currentX*160*6));
		text.append(",4000,");
		text.append(QString::number(currentY*160*6));
		text.append(",4000,");
		text.append(QString::number(currentZ*160*6));
		text.append(",4000,0,2500");
		text.append("\x0D\x0A");
		int i = commPort->write(text.toAscii(), text.length());
		ui->textBrowser->append("-> "+text);
		qDebug(text.toAscii());
		qDebug("trasmitted : %d", i);
		while(myTimer.elapsed() < 4000)
		{
		}
		myTimer.restart();
	}

	QString text = "@0M";
	text.append(QString::number(originalX*160*6));
	text.append(",4000,");
	text.append(QString::number(originalY*160*6));
	text.append(",4000,");
	text.append(QString::number(originalZ*160*6));
	text.append(",4000,0,2500");
	text.append("\x0D\x0A");
	int i = commPort->write(text.toAscii(), text.length());
	ui->textBrowser->append("-> "+text);
	qDebug(text.toAscii());
	qDebug("trasmitted : %d", i);
}

void MainWindow::home()
{
	int axes = 0;
	axes += ui->checkBox->isChecked();
	axes += ui->checkBox_2->isChecked()*2;
	axes += ui->checkBox_3->isChecked()*4;

	QString text = "@0R"+QString::number(axes)+"\x0D\x0A";
	int i = commPort->write(text.toAscii(), text.length());
	ui->textBrowser->append("Going to home position...");
	ui->textBrowser->append("-> "+text);
	qDebug(text.toAscii());
	qDebug("trasmitted : %d", i);
}

void MainWindow::sendCalibrate()
{
	QString text;
	text = "@0d4000,4000,4000\x0D\x0A";
	int i = commPort->write(text.toAscii(), text.length());
	ui->textBrowser->append("Sending calibration values...");
	ui->textBrowser->append("-> "+text);
	qDebug(text.toAscii());
	qDebug("trasmitted : %d", i);
}
