#include "mainwindow.h"
//#include "log.h"

#include <QApplication>

//using namespace log_ns;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  
//  assign_log(w.get_log());
  
  return a.exec();
}
