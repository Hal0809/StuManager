#include "student.h"
#include "ui_student.h"
#include <QAbstractItemView>
#include <QMouseEvent>
#include <QMessageBox>

#include "studenttableview.h"
Student::Student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Student),
    valueIndex(0),
    condIndex(0)
{
    ui->setupUi(this);
    createDB();
    createTable();
    queryTable();
    ui->deleteBtn->setEnabled(false);
    ui->modifyBtn->setEnabled(false);
    ui->value->setCurrentIndex(valueIndex);
    ui->cond->setCurrentIndex(condIndex);

    //点击学生，使得删除和修改按钮可用
    connect(ui->tableView,&StudentTableView::clickValidArea,ui->deleteBtn,[this](){
        ui->deleteBtn->setEnabled(true);
        ui->modifyBtn->setEnabled(true);

    });

    //点击空白区域恢复初始状态
    connect(ui->tableView,&StudentTableView::clickInvalidArea,ui->deleteBtn,[this](){
        ui->IDEdit->setReadOnly(false);
        ui->deleteBtn->setEnabled(false);
        ui->modifyBtn->setEnabled(false);
        clearEdits();

    });

    //点击学生并获取行号
    connect(ui->tableView,&QTableView::clicked,this,[=](const QModelIndex &index){
        this->row = index.row();
        ui->IDEdit->setReadOnly(true);
        ui->IDEdit->setText(ui->tableView->model()->index(row,0).data().toString());
        ui->nameEdit->setText(ui->tableView->model()->index(row,1).data().toString());
        ui->scoreEdit->setText(model.index(row,2).data().toString());
    });

    connect(ui->value,&QComboBox::activated,this,[=](int index){
        valueIndex = index;
        queryTable();
    });
    connect(ui->cond,&QComboBox::activated,this,[=](int index){
        condIndex = index;
        queryTable();
    });

}



Student::~Student()
{
    delete ui;
    db.close();
}

void Student::createDB(){
    //添加数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名称
    db.setDatabaseName("student.db");
    db.setUserName("root");
    db.setPassword("123456");
    //打开数据库
    if(db.open() == true){
        qDebug()<<"数据库打开成功！";
    }
    else{
        qDebug()<<"数据库打开失败！";
    }
}
void Student::createTable(){
    QSqlQuery query;//无参定义则默认使用当前打卡的数据库
    QString str = "create table student (id int PRIMARY KEY NOT NULL, name TEXT NOT NULL, score REAL NOT NULL);";
    if(query.exec(str) == false){
        qDebug()<<"关系表创建失败！\t"<<str;
    }
    else{
        qDebug()<<"关系表创建成功！";
    }
}
void Student::queryTable(){
    QString str = QString("select * from student order by %1 %2").arg(valueState()).arg(condState());
    model.setQuery(str);//执行查询语句，查询结果保存在model中
    model.setHeaderData(0,Qt::Horizontal,"学号");
    model.setHeaderData(1,Qt::Horizontal,"姓名");
    model.setHeaderData(2,Qt::Horizontal,"成绩");
    ui->tableView->setModel(&model);//tableView会自动匹配相应内容的格式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Student::on_insertBtn_clicked()
{
    if(isEditsEmpty()){
        QMessageBox::warning(this,"警告","插入信息不完整！");
        return;
    }
    QSqlQuery query;
    int id = ui->IDEdit->text().toInt();
    QString name = ui->nameEdit->text();
    double score = ui->scoreEdit->text().toDouble();

    QString str = QString("insert into student values (%1,'%2',%3)").arg(id).arg(name).arg(score);//Qt字符串占位
    //注意query语句格式：字符串用引号
    if(query.exec(str) == false){
        QMessageBox::warning(this,"错误","学号重复，数据插入失败。","确定");
    }
    queryTable();
    clearEdits();
}



void Student::on_deleteBtn_clicked()
{
    if(QMessageBox::warning(this,"警告",QString("确定要删除学生 %1 吗？").arg(model.index(row,1).data().toString()),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        QSqlQuery query;
        int id = ui->tableView->model()->index(row,0).data().toInt();
        QString str = QString("delete from student where id = %1").arg(id);
        query.exec(str);
        queryTable();
        ui->IDEdit->setReadOnly(false);
        ui->deleteBtn->setEnabled(false);
        ui->modifyBtn->setEnabled(false);
        clearEdits();
    }
}


void Student::on_modifyBtn_clicked()
{
    QSqlQuery query;
    int id = ui->IDEdit->text().toInt();
    QString name = ui->nameEdit->text();
    double score = ui->scoreEdit->text().toDouble();

    QString str = QString("update student set name = '%1', score = %2 where id = %3").arg(name).arg(score).arg(id);//Qt字符串占位
    //注意query语句格式：字符串用引号
    if(query.exec(str) == false){
        qDebug()<<"数据修改失败！";
    }
    else{
        qDebug()<<"数据修改成功！\t"<<str;
    }
    queryTable();
    ui->IDEdit->setReadOnly(false);
    ui->deleteBtn->setEnabled(false);
    ui->modifyBtn->setEnabled(false);
    clearEdits();
}

void Student::clearEdits(){
    ui->IDEdit->clear();
    ui->nameEdit->clear();
    ui->scoreEdit->clear();
}

bool Student::isEditsEmpty(){
    if(ui->IDEdit->text().isEmpty() || ui->nameEdit->text().isEmpty() || ui->scoreEdit->text().isEmpty()){
        return true;
    }
    else return false;
}

QString Student::valueState(){
    if(valueIndex == 0){
        return "id";
    }
    else
        return "score";
}
QString Student::condState(){
    if(condIndex == 0){
        return "asc";
    }
    else return "desc";
}
