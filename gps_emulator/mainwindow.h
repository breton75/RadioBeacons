#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTextEdit>
#include <QMap>
#include <QStringList>

#include "ui_mainwindow.h"
#include "../beacon_2/sv_udpstream.h"
#include "../../Common/sv_settings.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
  QTextEdit* get_log(); 
    
  public slots:
    void slotStart();
    void slotStop();
//    void slotLog();
    void slotStarted();
    void slotStopped();
    void slotSetTimeout();
    
  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
