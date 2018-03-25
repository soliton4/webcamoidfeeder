#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "feeder.h"

Feeder* gFeeder = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gFeeder = new Feeder();

    m_timer.setInterval(1000);
    m_timer.setSingleShot(false);
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::itsTimeSlot);
    m_timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::itsTimeSlot(){
    m_white = !m_white;
    gFeeder->feed(m_white);
};
