#ifndef ADDREGIONDIALOG_H
#define ADDREGIONDIALOG_H

#include <QDialog>
#include <QRegularExpressionValidator>
#include <QMessageBox>

namespace Ui {
class AddRegionDialog;
}

class AddRegionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRegionDialog(QWidget *parent = nullptr);
    ~AddRegionDialog();
    QString getNameEdtLineText(){return  nameEdtLineText;} // метод для отримання назви регіону
    int getIdEdtLineText(){return idEdtLineText.toInt();} // метод для отримання id регіону


private slots:


    void on_okButton_clicked();

private:
    Ui::AddRegionDialog *ui;
    QRegularExpressionValidator *idValidator;
    QString nameEdtLineText;
    QString idEdtLineText;
};

#endif // ADDREGIONDIALOG_H
