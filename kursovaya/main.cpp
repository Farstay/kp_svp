#include "measurementapp.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MeasurementApp app;
    app.show();

    return a.exec();
}
