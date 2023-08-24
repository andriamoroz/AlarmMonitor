#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objecttreemodel.h"
#include <QMouseEvent>
#include "./ui_mainwindow.h"
#include <QDebug>
#include "addalarmdialog.h"
#include "ConfigStruct.h"
#include <QApplication>





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
    void onRemoveAlarm();

private:
    Ui::MainWindow *ui;
    ObjectTreeModel* _treeModel;
    QObject* firstTreeItem;

    // обявлення контекстоного меню та екшенів для нього
    QMenu* contextMenu;
    QAction* addNewAlarmAction;
    QAction* removeAlarmAction;



};
#endif // MAINWINDOW_H
