#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //створюємо модель дерева
    _treeModel = new ObjectTreeModel(this);
    QStringList cols;
    cols << "objectName";
    _treeModel->setColumns(cols);
    // створюємо конфігураційні дані для регіону
    regionConfig_t firstRegionConfig; // створюємо об'єкт структури для регіону
    firstRegionConfig.name = "Перший об'єкт";
    firstRegionConfig.id = 1;
     // задаємо назву батькіському елементу
    firstTreeItem = new QObject(this);
    firstTreeItem->setObjectName(firstRegionConfig.name);
    firstTreeItem->objectName();
    // Додаємо елементи до моделі
    _treeModel->addItem(firstTreeItem,QModelIndex());
    // Встановлюємо модель у QTreeView
    ui->treeView->setModel(_treeModel);
    // Встановлюємо фільтр подій для QTreeView
    ui->treeView->viewport()->installEventFilter(this);
    // Створення контекстного меню та його пункти
    contextMenu = new QMenu(this);
    addNewRegionAction = new QAction("add region", this);
    addNewAlarmAction = new QAction("add alarm", this);
    configurationAction = new QAction("configuration", this);
    removeAlarmAction = new QAction("remove alarm", this);
    contextMenu->addAction(addNewRegionAction);
    contextMenu->addAction(addNewAlarmAction);
    contextMenu->addAction(configurationAction);
    contextMenu->addAction(removeAlarmAction);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::onCustomContextMenuRequested);
    connect(addNewRegionAction, &QAction::triggered, this, &MainWindow::onAddNewRegion);
    connect(addNewAlarmAction, &QAction::triggered, this, &MainWindow::onAddNewAlarm);
    connect(removeAlarmAction, &QAction::triggered, this, &MainWindow::onRemoveAlarmOrRegion);
    connect(configurationAction, &QAction::triggered, this, &MainWindow::onConfiguration);

    // відображення карти





}

MainWindow::~MainWindow()
{
    delete ui;
}

// фільтр який перевіряє чи натиснута кнопка в дереводивному полі
bool MainWindow::eventFilter(QObject *obj, QEvent *event){

    if (obj == ui->treeView->viewport()  && event->type() == QEvent::MouseButtonPress)
    {
       QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {

            // Обробка натискання лівої кнопки
            // Отримання QModelIndex елементу
            QModelIndex clickedIndex = ui->treeView->indexAt(mouseEvent->pos());
            if(clickedIndex.isValid()){
                qDebug() << "detect left mouse click on tree item";
            }
            //qDebug() << clickedIndex;
            // Виконання необхідних дій для натискання лівої кнопки
        }
        else if (mouseEvent->button() == Qt::RightButton)
        {

            // Обробка натискання правої кнопки
            // Отримання QModelIndex елементу
            QModelIndex clickedIndex = ui->treeView->indexAt(mouseEvent->pos());
            if(clickedIndex.isValid()){
                qDebug() << "detect right mouse click on tree item";
            }
            // Виконання необхідних дій для натискання правої кнопки
        }
    }

    return QObject::eventFilter(obj, event);
}

// обробник контекстного меню
void MainWindow::onCustomContextMenuRequested(const QPoint& treeViewPos){
    // Показ контекстного меню
    int d = 3;
    QModelIndex index = ui->treeView->indexAt(treeViewPos);
    if (index.isValid() ) {
        qDebug() << "context menu appeared";
        contextMenu->exec(ui->treeView->viewport()->mapToGlobal(treeViewPos));
        qDebug() << "context menu disappeared";
    }

}

void MainWindow::onAddNewAlarm()
{
    AddAlarmDialog alarmDialog;
    QObject* newTreeItem = new QObject();
    alarmConfig_t newAlarmConfig;
    configManager = new ConfigManager();
    alarmDialog.setModal(true);
    alarmDialog.exec();
    if(alarmDialog.getNameEdtLineText().isEmpty())
    {
        delete newTreeItem;
        return;
    }
    newAlarmConfig.name = alarmDialog.getNameEdtLineText();
    newAlarmConfig.id = alarmDialog.getIdEdtLineText();
    newAlarmConfig.ipAddress = alarmDialog.getIpEdtLineText();
    newAlarmConfig.macAddress = alarmDialog.getMacEdtLineText();
    configManager->addAlarmConfig(newAlarmConfig);
    configManager->saveToFile(newAlarmConfig);
    newTreeItem->setObjectName(alarmDialog.getNameEdtLineText());
    _treeModel->addItem(newTreeItem, ui->treeView->currentIndex());



    //delete newItem; // якщо видалити newItem то він не зявляється в списку
}

void MainWindow::onAddNewRegion()
{
    AddRegionDialog regionDialog;
    QObject* newTreeItem = new QObject();
    regionConfig_t newRegionConfig;
    regionDialog.setModal(true);
    regionDialog.exec();
    if(regionDialog.getNameEdtLineText().isEmpty())
    {
        delete newTreeItem;
        return;
    }
    newRegionConfig.name = regionDialog.getNameEdtLineText();
    newRegionConfig.id = regionDialog.getIdEdtLineText();

    newTreeItem->setObjectName(regionDialog.getNameEdtLineText());
    _treeModel->addItem(newTreeItem, ui->treeView->currentIndex());

}

void MainWindow::onRemoveAlarmOrRegion()
{
    QModelIndex index = ui->treeView->currentIndex();
    QString name = _treeModel->getObjectName(index);
        if(index.isValid()){
        {
            if(name != firstTreeItem->objectName()){
                qDebug() << "onRemoveAlarm";
                _treeModel->removeItem(index);
            }
        }
        }
}

void MainWindow::onConfiguration()
{
    QModelIndex index = ui->treeView->currentIndex();
        if(index.isValid()){
        {
            //_treeModel->
            qDebug() << "onConfiguration";
        }
        }
}

//ToDo

//    1)створити контекстне вікно яке буде відкриватися при натисканні правої кнопки мишки на елелемент деревовидної струкрури
//    2)в меню має бути пункт додати та видалити елемент та можливість добавити ще пункти на майбутнє
//    3)при натискані на добавити, має зявитися дочірнє вікно з полем вводу та кнопкою додати

