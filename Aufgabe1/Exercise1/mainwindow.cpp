#include "mainwindow.h"

#include <QFileDialog>
#include <QKeyEvent>

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
	ui->glwidget->setFocusPolicy(Qt::StrongFocus);
    ui->glwidget->setFocus();

    _camera = QSharedPointer<Camera>(new Camera());
    ui->glwidget->attachCamera(_camera);

    QObject::connect(ui->pushButton,&QPushButton::clicked,ui->glwidget, &GLWidget::openFileDialog);
    QObject::connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::updatePointSize);
    QObject::connect(ui->radioButton_1,&QRadioButton::clicked,ui->glwidget,&GLWidget::radioButton1Clicked);
    QObject::connect(ui->radioButton_2,&QRadioButton::clicked,ui->glwidget,&GLWidget::radioButton2Clicked);
    QObject::connect(ui->radioButton,&QRadioButton::clicked,ui->glwidget,&GLWidget::radioButton3Clicked);
    QObject::connect(ui->radioButton_3,&QRadioButton::clicked,ui->glwidget,&GLWidget::radioButton4Clicked);

    QObject::connect(ui->checkBox,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_camera_1);
    QObject::connect(ui->checkBox_2,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_camera_2);
    QObject::connect(ui->checkBox_3,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_cubes);
    QObject::connect(ui->checkBox_4,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_projection);
    QObject::connect(ui->checkBox_5,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_reconstruction);
    QObject::connect(ui->checkBox_6,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_rays);
    QObject::connect(ui->checkBox_7,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_image_plane);
    QObject::connect(ui->checkBox_8,&QCheckBox::clicked,ui->glwidget,&GLWidget::disable_tree);


    updatePointSize(1);

    _camera->setPosition(QVector3D(0.0f, -0.1f, -0.2f));
    _camera->rotate(0, 50, 0);
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::openFileDialog()
{
  const QString filePath = QFileDialog::getOpenFileName(this, tr("Open PLY file"), "", tr("PLY Files (*.ply)"));
  if (!filePath.isEmpty())
  {
      std::cout << "file path: " << filePath.toStdString() << std::endl;
  }
}

void MainWindow::updatePointSize(size_t value)
{
    std::cout << "new pointsize: " << value << std::endl;
    ui->glwidget->setPointSize(value);
}
