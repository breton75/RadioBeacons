#include <QWidget>
#include <QTextEdit>
#include <QColor>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>

#include "log.h"

using namespace log_ns;

QTextEdit   *wLog;  
QDockWidget *wDock;
QWidget     *wDockContents;
QVBoxLayout *verticalLayout;

void log_ns::create_log(QMainWindow *parent)
{
  if (!parent)
    {
      wLog = new QTextEdit;
      wLog->show();
    }
  else 
    {
      wDock = new QDockWidget(parent);
      wDock->setObjectName(QStringLiteral("wDock"));
      wDock->setWindowTitle("Log");
      wDock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
      wDock->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);
      wDock->setMinimumSize(QSize(100, 50));
      wDock->setMaximumSize(QSize(16635, 16635));
      
      wDockContents = new QWidget();
      wDockContents->setObjectName(QStringLiteral("wDockContents"));
      
      verticalLayout = new QVBoxLayout(wDockContents);
      verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
      wLog = new QTextEdit(wDockContents);
      wLog->setObjectName(QStringLiteral("wLog"));

      verticalLayout->addWidget(wLog);

      wDock->setWidget(wDockContents);
      parent->addDockWidget(static_cast<Qt::DockWidgetArea>(4), wDock);

    }
}

void log_ns::assign_log(QTextEdit *Widget)
{
  if (!Widget)
  {
    wLog = new QTextEdit;
    wLog->show();
  }
  else
  {
    wLog = Widget;
  }
}
  

void log_ns::log(int mode, QString text, QWidget *parent)
{
  switch (mode) {
      
    case m_Data:
      {     
        wLog->setTextColor(QColor(223344));
        break;
      }

    case m_Err:
      {
        wLog->setTextColor(Qt::red);
        break;
      }
      
    case m_Info:
      {
        wLog->setTextColor(QColor(0x009A8832));// Qt::green);
        break;
      }
      
    case m_Duty:
      {
        wLog->setTextColor(QColor(0x003A6098));
        break;
      }
      
    case m_Attention:
      {
        wLog->setTextColor(Qt::darkCyan);
        break;
      } 
      
    case m_NewData:
      {
        wLog->setTextColor(QColor(0x00BD6311));
        break;
      }    
      
    case m_Fail:
      {
        wLog->setTextColor(QColor(0x00173EF4));
        break;
      }
      
    case m_Debug:
      {
        wLog->setTextColor(QColor(0x008A8A8A));
        break;
      } 
      
    case m_Success:
      {
        wLog->setTextColor(QColor(0x0020A230));
        break;
      }    
      
    case m_Critical:
    {
      wLog->setTextColor(Qt::red);
      QMessageBox::critical(parent, "Error", text, QMessageBox::Ok);
    }
      
    }
  
  QDateTime time;    
  wLog->append(time.currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz: ") + text);
}

void log_ns::log_SQL_error(QSqlError error, QString noErrorMsg)
{
  switch (error.type())
  {
    case QSqlError::NoError:
      log(m_Success, noErrorMsg);
      break;
  
    case QSqlError::ConnectionError:
      log(m_Critical, QString("Connection Error: %1").arg(error.text()));
      break;      
  
    case QSqlError::StatementError:
      log(m_Critical, QString("Statement Error: %1").arg(error.text()));
      break;  
      
    case QSqlError::TransactionError:
      log(m_Critical, QString("Transaction Error: %1").arg(error.text()));
      break;      
      
    case QSqlError::UnknownError:
      log(m_Critical, QString("Error: %1").arg(error.text()));
      break;       
  }
}
