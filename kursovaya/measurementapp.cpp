#include "measurementapp.h"
#include "ui_measurementapp.h"

MeasurementApp::MeasurementApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasurementApp)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);

    lengthLabel = new QLabel("Длина: ");
    lengthLineEdit = new QLineEdit;
    lengthLineEdit->setReadOnly(true);

    koefLabel = new QLabel("Коэффициент (во сколько раз предмет в реальности больше, чем на изображении): ");
    koefLineEdit = new QLineEdit;
    Coeff = 0.0;

    QPushButton *calculateButton = new QPushButton("Рассчитать длину");
    connect(calculateButton, &QPushButton::clicked, this, &MeasurementApp::calculateLength);

    QPushButton *coeffButton = new QPushButton("Задать коэффициент");
    connect(coeffButton, &QPushButton::clicked, this, &MeasurementApp::setCoeff);

    QPushButton *loadImage = new QPushButton("Загрузить изображение");
    connect(loadImage, &QPushButton::clicked, this, &MeasurementApp::loadImage);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);

    layout->addWidget(lengthLabel);
    layout->addWidget(lengthLineEdit);
    layout->addWidget(calculateButton);

    layout->addWidget(koefLabel);
    layout->addWidget(coeffButton);
    layout->addWidget(koefLineEdit);

    layout->addWidget(loadImage);


    setLayout(layout);
}

void MeasurementApp::loadImage() {
    fileName = QFileDialog::getOpenFileName(this, tr("Выберите изображение"), "", tr("Изображения (*.png)"));

    if (!fileName.isEmpty()) {
        QPixmap image(fileName);

        if (!image.isNull()) {
            scene->clear();

            QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(image);
            scene->addItem(imageItem);

            scene->setSceneRect(imageItem->pixmap().rect());

            currentLineExists = false;
        }
        else QMessageBox::critical(this, "Ошибка загрузки изображения", "Не удалось открыть изображение.");
    }
}

void MeasurementApp::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(currentLineExists)
        {
            scene->removeItem(currentLine);
            currentLineExists = false;
        }
        if (!isDrawing) {
            firstPoint = view->mapToScene(event->pos()) - QPointF(12, 12);
            isDrawing = true;
        }
        else {
            secondPoint = view->mapToScene(event->pos()) - QPointF(12, 12);

            QLineF line(firstPoint, secondPoint);

            currentLine = new QGraphicsLineItem(line);
            QPen pen(QColor(Qt::red));
            pen.setWidth(2);
            currentLine->setPen(pen);
            scene->addItem(currentLine);
            currentLineExists = true;

            isDrawing = false;
        }
    }
}

void MeasurementApp::setCoeff(){
    QString coefficientText = koefLineEdit->text();

    bool conversionOk;
    double coefficientValue = coefficientText.toDouble(&conversionOk);

    if (conversionOk) {
        Coeff = coefficientValue;
        qDebug() << Coeff;
    } else {
        QMessageBox::critical(this, "Ошибка ввода коэффициента", "Не удалось задать коэффициент. Проверьте правильность ввода.");
    }
}

void MeasurementApp::calculateLength() {
    if (currentLineExists && Coeff) {

        double lengthInPixels = currentLine->line().length();

        lengthInMillimeters = lengthInPixels * Coeff;

        lengthLineEdit->setText(QString::number(lengthInMillimeters));
    } else {
        isDrawing = false;
        QMessageBox::critical(this, "Ошибка расчёта", "Линия не существует, либо вы не ввели коэффициент");
    }
}

MeasurementApp::~MeasurementApp()
{
    delete ui;
}
