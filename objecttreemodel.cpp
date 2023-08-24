#include "objecttreemodel.h"
#include <QDebug>
#include <QAbstractItemModel>


ObjectTreeModel::ObjectTreeModel(QObject* parent)
    :QAbstractItemModel(parent)
{
    _rootItem = new QObject(this);
}

// реєструємо кількість колонок
// Цей метод дозволяє динамічно змінювати набір характеристик або назв стовпців моделі дерева в процесі роботи програми.
void ObjectTreeModel::setColumns(QStringList cols)
{
    _columns = cols;
}

//метод використовується для додавання нового елемента даних до моделі дерева.
// Параметр item представляє об'єкт даних, який має бути доданий до моделі.
//Параметр parentIdx вказує на батьківський модельний індекс, до якого буде додано новий елемент.
void ObjectTreeModel::addItem(QObject *item, const QModelIndex &parentIdx)
{
    beginInsertRows(parentIdx, rowCount(parentIdx), rowCount(parentIdx)); // початок вставки нових рядків у модель
    item->setParent(objByIndex(parentIdx)); // назначаємо батьківський елемент для item
    savedIndexes.append(parentIdx); // додаємо індекс до списку збережених індексів
    endInsertRows(); // завершення вставки нових рядків у модель


}

// метод для видалення елемента з моделі дерева.
bool ObjectTreeModel::removeItem(const QModelIndex &index)
{
    if(!index.isValid())
        return false;


    QObject *item = objByIndex(index);
    if(!item)
        return false;

    QObject *parent = item->parent();
    if(!parent)
        return false;

    QObject *child = parent->findChild<QObject*>(item->objectName());
    if(!child)
        return false;

     // Видаляємо дитинський об'єкт
    beginRemoveRows(index.parent(), index.row(), index.row());
    child->deleteLater();
    savedIndexes.removeAt(index.row()); // видаляємо індекс зі списку збережених індексів
    endRemoveRows();


    return true;
}

QList<QModelIndex> ObjectTreeModel::getSavedIndexes()
{
 //тут треба дописати логіку роботи зберігання індексів в список щоб звертатися до нього коли буду видаляти елементи
    if(!savedIndexes.isEmpty()){
        return savedIndexes; // якщо список не пустий то повертаємо список індексів
    }
    return QList<QModelIndex>(); // якщо список пустий то повертаємо пустий список
}

QObject *ObjectTreeModel::objByIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return _rootItem;   // якщо не валідний обєкт то повертаємо корневий віртуальний елемент
                            // в решті випадків приводимо index до типу QObject
    return static_cast<QObject*>(index.internalPointer());

}


// Цей метод викликається для отримання модельного індексу (QModelIndex)
//для певного рядка (row), колонки (column) та батьківського модельного індексу (parent).
QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) // якщо немає вілідного індексу
        return QModelIndex();           // то повертаємо невалідний індекс
    QObject* parentObj = objByIndex(parent); // отримуємо батьківський елемент
    return createIndex(row, column, parentObj->children().at(row)); // в простому випадку коли немає ієрархії використовується метод createIndex()
}

// Цей метод викликається для отримання батьківського модельного індексу (QModelIndex)
//для певного дочірнього модельного індексу (child).
QModelIndex ObjectTreeModel::parent(const QModelIndex &child) const
{
    QObject* childObj = objByIndex(child); // отримуємо дочірний обєкт
    QObject* parentObj = childObj->parent(); // отримуємо батьківський об'єкт для дочірнього об'єкта
    if (parentObj == _rootItem)  // якщо батьківський елемент це корнівий елемент то повертаємо невалідний індекс
        return QModelIndex();
    QObject* grandParentObj = parentObj->parent(); // отримуємо прабатьківський елемент
    int row = grandParentObj->children().indexOf(parentObj); // запитуємо в grandParentObj який по порядку оцей (parentObj) дочірній елеметнт
    return createIndex(row, 0 , parentObj);

}

// метод викликається для отримання кількості рядків у моделі
int ObjectTreeModel::rowCount(const QModelIndex &parent) const
{
    return objByIndex(parent)->children().count(); // вертаємо кількість дочерніх елементів
}

//Цей метод викликається для отримання кількості стовпців у моделі
int ObjectTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _columns.count(); // вертаємо список характеристик з елемента
}


// метод викликається для отримання даних, які будуть відображені у певній модельній клітинці,
// представленій модельним індексом (index), з певною роллю (role).
QVariant ObjectTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // якщо не вілідний вертаємо порожнє значення

    if (role == Qt::DisplayRole) // якщо роль на відтворення то вертаємо
        return objByIndex(index)->property(_columns.at(index.column()).toUtf8()); // повертає назву що відображається в колонці (назва елементу)

    return QVariant(); // якщо нічого не робимо то вертаємо порожнє значення
}




