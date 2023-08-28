#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objecttreemodel.h"
#include <QMouseEvent>
#include "./ui_mainwindow.h"
#include <QDebug>
#include "addalarmdialog.h"
#include "addregiondialog.h"
#include "configmanager.h"
#include <QApplication>
#include <QList>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);
    void onCustomContextMenuRequested(const QPoint&); // обявлення слоту визону контекстного меню
    void onAddNewAlarm();
    void onAddNewRegion();
    void onRemoveAlarmOrRegion();
    void onConfiguration();

private:
    Ui::MainWindow *ui;
    ObjectTreeModel* _treeModel;
    QObject* firstTreeItem;
    void configTreeMetod(); // метод для базового налаштування древовидної моделі

    // обявлення контекстоного меню та екшенів для нього
    QMenu* contextMenu;
    QAction* addNewRegionAction;
    QAction* addNewAlarmAction;
    QAction* configurationAction;
    QAction* removeAlarmAction;

    //
    ConfigManager* configManager;




};
#endif // MAINWINDOW_H
