#ifndef ADDALARMDIALOG_H
#define ADDALARMDIALOG_H

#include <QDialog>
#include <QDebug>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <QMessageBox>
#include <QRegularExpressionValidator>

namespace Ui {
class AddAlarmDialog;
}

class AddAlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAlarmDialog(QWidget *parent = nullptr);
    ~AddAlarmDialog();
    QString getNameEdtLineText(){return  nameEdtLineText;} // метод для отримання назви сирени
    sockaddr_in getIpEdtLineText(){return ipAddress;} // метод для отримання ip адреси сирени
    QString getMacEdtLineText() {return macEdtLineText;} // метод для отримання mac адреси сирени
    int getIdEdtLineText(){return idEdtLineText.toInt();} // метод для отримання id сирени

private slots:
    void on_Ok_clicked();

private:
    Ui::AddAlarmDialog *ui;
    QRegularExpressionValidator *ipValidator;
    QRegularExpressionValidator *portValidator;
    QRegularExpressionValidator *macValidator;
    QRegularExpressionValidator *idValidator;
    QString nameEdtLineText;
    QString ipEdtLineText;
    QString portEdtLineText;
    QString macEdtLineText;
    QString idEdtLineText;

    void socketSetUp();
    sockaddr_in ipAddress;// метод для налаштування ip та порту



};

#endif // ADDALARMDIALOG_H
