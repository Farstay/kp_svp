#ifndef MEASUREMENTAPP_H
#define MEASUREMENTAPP_H
#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include <QFileDialog>
#include <QMessageBox>


namespace Ui {
class MeasurementApp;
}

class MeasurementApp : public QWidget
{
    Q_OBJECT

public:
    explicit MeasurementApp(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event) override;
    ~MeasurementApp();

private slots:
    void calculateLength();
    void setCoeff();
    void loadImage();

private:
    Ui::MeasurementApp *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;

    QLabel *lengthLabel;
    QLineEdit *lengthLineEdit;
    QLabel *koefLabel;
    QLineEdit *koefLineEdit;

    QPointF firstPoint;
    QPointF secondPoint;
    bool isDrawing = false;
    QGraphicsLineItem *currentLine;
    bool currentLineExists = false;

    QString fileName;

    double Coeff;

    double lengthInMillimeters;
};

#endif // MEASUREMENTAPP_H
