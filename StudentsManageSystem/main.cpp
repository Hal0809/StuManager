#include <QApplication>

#include "student.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Student k;
    k.show();
    return a.exec();
}
