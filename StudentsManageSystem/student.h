#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QModelIndex>
namespace Ui {
class Student;
}

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    ~Student();

private slots:
    void on_insertBtn_clicked();

    void on_deleteBtn_clicked();

    void on_modifyBtn_clicked();


private:
    Ui::Student *ui;
    QSqlDatabase db;//建立Qt和数据库的连接
    QSqlQueryModel model;//保存结果集
    int row;
    int valueIndex;
    int condIndex;

    void createDB();
    void createTable();
    void queryTable();
    void clearEdits();
    bool isEditsEmpty();
    QString valueState();
    QString condState();
};

#endif // STUDENT_H
