#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"

AddAlarmDialog::AddAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmDialog)
{
    ui->setupUi(this);
    // регулярний вираз для перевірки правильності введення IPv4
    ipValidator = new QRegularExpressionValidator
        (QRegularExpression("^((\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])$"), this);
    ui->ipLineEdit->setValidator(ipValidator);
    // регулярний вираз для перевірки правильності ввдеення порту
    portValidator = new QRegularExpressionValidator(QRegularExpression("^[0-9]{1,5}$"), this);
    ui->portLineEdit->setValidator(portValidator);
    // регулярний вираз для перевірки правильності введення mac адреси
    macValidator = new QRegularExpressionValidator(QRegularExpression("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$"), this);
    ui->macLineEdit->setValidator(macValidator);
    // регулярний вираз для перевірки правильності введення id
    idValidator = new QRegularExpressionValidator(QRegularExpression("^[0-9]{1,3}$"), this);
    ui->idLineEdit->setValidator(idValidator);


}

AddAlarmDialog::~AddAlarmDialog()
{
    delete macValidator;
    delete portValidator;
    delete ipValidator;
    delete ui;

}


void AddAlarmDialog::socketSetUp()
{
    ipAddress.sin_family = AF_INET; // Встановити сімейство адреси на AF_INET (IPv4)

    ipEdtLineText = ui->ipLineEdit->text();
    portEdtLineText = ui->portLineEdit->text();

    unsigned long checkIp;
    int checkPort;
    checkIp = inet_addr(ipEdtLineText.toStdString().c_str());
    checkPort = htons(portEdtLineText.toInt());

    if(checkIp == INADDR_NONE || checkPort == INADDR_NONE)
    {
        QMessageBox::warning(this, "Warning", "Невірна IP адреса або порт");
        return;
    }

    ipAddress.sin_addr.s_addr = // Встановити IP адресу
    ipAddress.sin_port = htons(portEdtLineText.toInt()); // перетворення порта в мережевий байтовий порядок

}

void AddAlarmDialog::on_Ok_clicked()
{
    socketSetUp();
    nameEdtLineText = ui->nameLineEdit->text();
    macEdtLineText = ui->macLineEdit->text();
    idEdtLineText = ui->idLineEdit->text();

    if(nameEdtLineText.isEmpty() || macEdtLineText.isEmpty() || idEdtLineText.isEmpty())
        QMessageBox::warning(this, "Warning",  "Заповніть всі поля!");


    this->close();
  //треба зробиьтит ще перевірку на ID щоб вона була цілочисленна і значення записути в змінні до перевірки, бо воно завжди видає що поля пусті

}

