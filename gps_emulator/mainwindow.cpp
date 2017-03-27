#include "mainwindow.h"

//using namespace log_ns;

//myStream *str;
QMap<QString, SvUdpWriter*> map;
bool stopped;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  AppParams::WindowParams p;
  p = AppParams::readWindowParams(this);
  this->resize(p.size);
  this->move(p.position);
  this->setWindowState(p.state);
  
  ui->spinMaxAngle->setValue(AppParams::readParam(this, "General", "MaxAngle", 45).toInt());
  ui->spinTimeout->setValue(AppParams::readParam(this, "General", "Timeout", 1000).toInt());
  ui->spinSpeed->setValue(AppParams::readParam(this, "General", "Speed", 360).toInt());
 
  
  connect(ui->bnStart, SIGNAL(pressed()), this, SLOT(slotStart()));
  connect(ui->bnStop, SIGNAL(pressed()), this, SLOT(slotStop()));
  connect(ui->bnSetTimeout, SIGNAL(pressed()), this, SLOT(slotSetTimeout()));
//  connect(str, SIGNAL(uu()), this, SLOT(slotLog()));
}

MainWindow::~MainWindow()
{
  AppParams::saveWindowParams(this, this->size(), this->pos(), this->windowState());
  AppParams::saveParam(this, "General", "MaxAngle", ui->spinMaxAngle->value());
  AppParams::saveParam(this, "General", "Timeout", ui->spinTimeout->value());
  AppParams::saveParam(this, "General", "Speed", ui->spinSpeed->value());
  
  delete ui;
}

QTextEdit* MainWindow::get_log()
{
  return ui->textEdit;
}

void MainWindow::slotSetTimeout()
{
  foreach (SvUdpWriter* udp, map.values()) {
    udp->setTimeout(ui->spinTimeout->value());
  }
}

void MainWindow::slotStart()
{
  QStringList sl = ui->textIpList->toPlainText().split('\n');
  quint16 port = ui->spinPort->value();
  quint16 speed = ui->spinSpeed->value();
  quint16 maxAngle = ui->spinMaxAngle->value();
  quint16 segmentLength = ui->spinSegmentLength->value();
  quint16 timeout = ui->spinTimeout->value();
  
  map.clear();
//  map = new QMap<QString, myStream*>();
  
  foreach (QString ip, sl) {
    if(QHostAddress(ip).toIPv4Address() > 0)
    {
      map.insert(ip, new SvUdpWriter(ip, port, speed, maxAngle, segmentLength, timeout, this));
//      map.value(ip)->setTimeout(ui->spinTimeout->value());
      connect(map.value(ip), SIGNAL(started()), this, SLOT(slotStarted()));
      connect(map.value(ip), SIGNAL(finished()), this, SLOT(slotStopped()));    
      
      map.value(ip)->start();
    }
  }
}

void MainWindow::slotStop()
{
  while(!map.isEmpty())
  {
//    stopped = false;
    map.last()->stop(); // = false;
    while(map.last()->isAsctive()) QApplication::processEvents();
    map.remove(map.lastKey());
  }
}

void MainWindow::slotStarted()
{
  
  ui->bnStart->setEnabled(false);
  ui->bnStop->setEnabled(true);
  
  SvUdpWriter* ms = static_cast<SvUdpWriter*>(sender());

  qDebug() << QString("Stream %1 started").arg(map.key(ms));
  
}

void MainWindow::slotStopped()
{

  ui->bnStart->setEnabled(true);
  ui->bnStop->setEnabled(false);
  
  SvUdpWriter* ms = static_cast<SvUdpWriter*>(sender());
  
  qDebug() << QString("Stream %1 stopped").arg(map.key(ms));

}
