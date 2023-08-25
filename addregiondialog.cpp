#include "addregiondialog.h"
#include "ui_addregiondialog.h"


AddRegionDialog::AddRegionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRegionDialog)
{
    ui->setupUi(this);
    // регулярний вираз для перевірки правильності введення id
    idValidator = new QRegularExpressionValidator(QRegularExpression("^[0-9]{1,3}$"), this);
    ui->idLineEdit->setValidator(idValidator);
}

AddRegionDialog::~AddRegionDialog()
{
    delete ui;
}



void AddRegionDialog::on_okButton_clicked()
{
    nameEdtLineText = ui->nameLineEdit->text();
    idEdtLineText = ui->idLineEdit->text();

    if(nameEdtLineText.isEmpty() || idEdtLineText.isEmpty()){
        QMessageBox::warning(this, "Warning", "Заповніть всі поля!");
        return;
    }

    this->close();
}

