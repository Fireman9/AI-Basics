#include <QApplication>

#include "GameWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GameWidget widget;
    widget.show();

    return QApplication::exec();
}
