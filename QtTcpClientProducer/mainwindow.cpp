#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include<QLineEdit>
#include<QTextBrowser>
#include<QTimer>
#include<QLabel>
#include<QLCDNumber>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();

  connect(ui->pushButtonPut,
          SIGNAL(clicked(bool)),
          this,
          SLOT(putData()));

  connect(ui->pushButton_conectar,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tpcConnect()));

  connect(ui->pushButton_desconectar,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tpcdisconnect()));

  connect(ui->pushButton_pere,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tpcparar()));
}

void MainWindow::tcpConnect(){
  socket->connectToHost("127.0.0.1",1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tpcdisconnect()
{
    socket->disconnectFromHost();
}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;

  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%35)+"\r\n";

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}

/*void MainWindow::tpcparar()
{
    killTimer();
}
*/
MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
