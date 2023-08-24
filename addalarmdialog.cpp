#include "addalarmdialog.h"
#include "ui_addalarmdialog.h"

AddAlarmDialog::AddAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAlarmDialog)
{
    ui->setupUi(this);

    ipValidator = new QRegularExpressionValidator
        (QRegularExpression("^((\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d{2}|2[0-4]\\d|25[0-5])$"), this);
    ui->ipLineEdit->setValidator(ipValidator);
    portValidator = new QRegularExpressionValidator(QRegularExpression("^[0-9]{1,5}$"), this);
    ui->portLineEdit->setValidator(portValidator);
    macValidator = new QRegularExpressionValidator(QRegularExpression("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$"), this);
    ui->macLineEdit->setValidator(macValidator);

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

    if(checkIp == INADDR_NONE)
    {
        QMessageBox::warning(this, "Warning", "Невірна IP адреса");
        return;
    }
    ipAddress.sin_addr.s_addr = // Встановити IP адресу
    ipAddress.sin_port = htons(portEdtLineText.toInt()); // перетворення порта в мережевий байтовий порядок

}

void AddAlarmDialog::on_Ok_clicked()
{
    if(nameEdtLineText.isEmpty())
        QMessageBox::warning(this, "Warning", "Пусте поле вводу назви");
    if(macEdtLineText.isEmpty())
        QMessageBox::warning(this, "Warning", "Пусте поле вводу mac адреси");
    if(idEdtLineText.isEmpty())
        QMessageBox::warning(this, "Warning", "Пусте поле вводу ідентифікатора");

  //треба хробиьтит ще перевірку на ID щоб вона була цилочислена і значення записути в змінні до перевірки, бо воно завжди видає що поля путі

    socketSetUp();
    nameEdtLineText = ui->nameLineEdit->text();
    macEdtLineText = ui->macLineEdit->text();
    idEdtLineText = ui->idLineEdit->text();
}

