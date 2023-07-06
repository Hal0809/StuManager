#include "studenttableview.h"
#include <QModelIndex>

StudentTableView::StudentTableView(QWidget* parent):
    QTableView(parent)
{

}

void StudentTableView::mousePressEvent(QMouseEvent* event){
    QModelIndex index = indexAt(event->pos());
    if(index.isValid()){
        emit clickValidArea();
    }
    else{
        emit clickInvalidArea();
    }
    QTableView::mousePressEvent(event);
}
