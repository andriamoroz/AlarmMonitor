#ifndef OBJECTTREEMODEL_H
#define OBJECTTREEMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QMouseEvent>
#include <QModelIndex>
#include <qtcore>



class ObjectTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ObjectTreeModel(QObject* parent = nullptr);
    void setColumns(QStringList cols); // реєструємо кількість колонок
    void addItem(QObject* item, const QModelIndex &parentIdx);
    bool removeItem(const QModelIndex &index);
    QList<QModelIndex> getSavedIndexes();


protected:
    QStringList _columns;
    QObject* _rootItem;
    QObject* objByIndex(const QModelIndex &index) const;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    //метод для фіксації натискання кнопок

private:
    QList<QModelIndex> savedIndexes; // список для зберігання індексів

};

#endif // OBJECTTREEMODEL_H
