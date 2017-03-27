#ifndef LOG_H
#define LOG_H

#include <QWidget>
#include <QTextEdit>
//#include <QColor>
#include <QString>
#include <QMainWindow>
#include <QSqlError>

namespace log_ns
{

  const int m_Data = 0;
  const int m_Err = 1;
  const int m_Info = 2;
  const int m_Duty = 3;
  const int m_Attention = 4;
  const int m_NewData = 5;
  const int m_Fail = 6;
  const int m_Debug = 7;
  const int m_Success = 8;
  const int m_Critical = 9;
  
  void create_log(QMainWindow *parent = 0);
  void assign_log(QTextEdit *Widget = 0);
  void log(int mode, QString text, QWidget *parent = 0);
  void log_SQL_error(QSqlError error, QString noErrorMsg = "OK");
  
}




#endif // LOG_H
