#ifndef STUDENTTABLEVIEW_H
#define STUDENTTABLEVIEW_H

#include <QTableView>
#include <QWidget>
#include <QMouseEvent>

/*
    自定义控件使用指南：
    1.继承要重定义的控件
    2.构造函数的参数是QWidget*类型，但是初始化列表中要初始化基类，而非QWidget
    3.重写事件函数后重新调用基类中的函数完成剩余工作
    4.准确包含所需的头文件
*/

class StudentTableView : public QTableView
{
    Q_OBJECT
public:
    explicit StudentTableView(QWidget* parent = nullptr);
private:
    void mousePressEvent(QMouseEvent*);
signals:
    void clickValidArea();
    void clickInvalidArea();

};

#endif // STUDENTTABLEVIEW_H
