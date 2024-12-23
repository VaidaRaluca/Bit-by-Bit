#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ETER");
    setFixedSize(1380, 575);

    this->setStyleSheet("QMainWindow { background-image: url(C:/Users/40720/OneDrive/Desktop/FACULTATE/AN II/Modern C++/Eter/background.jpg); "
                        "background-repeat: no-repeat; "
                        "background-position: center; }");

    ui->startGame->setVisible(false);
    ui->loadGame->setVisible(false);

    ShowModeButtons(false);

    // connect(ui->Eter, &QPushButton::clicked, this, &MainWindow::on_Eter_clicked);
    // connect(ui->startGame, &QPushButton::clicked, this, &MainWindow::on_startGame_clicked);
    // //connect(ui->AMode, &QPushButton::clicked, this, &MainWindow::on_AMode_clicked);
    // connect(ui->BMode, &QPushButton::clicked, this, &MainWindow::on_BMode_clicked);
    // connect(ui->CMode, &QPushButton::clicked, this, &MainWindow::on_CMode_clicked);
    // connect(ui->BCMode, &QPushButton::clicked, this, &MainWindow::on_BCMode_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowModeButtons(bool ok)
{
    ui->AMode->setVisible(ok);
    ui->BMode->setVisible(ok);
    ui->CMode->setVisible(ok);
    ui->BCMode->setVisible(ok);
}
void MainWindow::GetPLayerName()
{
    static int counter = 1;
    qDebug() << "GetPlayerName() apelat:" << counter++;
    bool ok;
    QString text1 = QInputDialog::getText(this,
                                         tr("PLAYER 1 "),
                                         tr("Name: "),
                                         QLineEdit::Normal,
                                         "Player1",
                                         &ok);

    // Verifică dacă utilizatorul a apăsat OK și nu Cancel
    if (ok && !text1.isEmpty())
    {
        qDebug() << "Text introdus:" << text1;
    }
    else
    {
        qDebug() << "Niciun text introdus.";
    }
    QString text2 = QInputDialog::getText(this,
                                         tr("PLAYER 2 "),
                                         tr("Name: "),
                                         QLineEdit::Normal,
                                         "Player2",
                                         &ok);

    // Verifică dacă utilizatorul a apăsat OK și nu Cancel
    if (ok && !text2.isEmpty())
    {
        qDebug() << "Text introdus:" << text2;
    }
    else
    {
        qDebug() << "Niciun text introdus.";
    }
}


void MainWindow::on_Eter_clicked()
{
    ui->startGame->setVisible(true);
    ui->loadGame->setVisible(true);
    ui->Eter->setVisible(false);

}

void MainWindow::on_startGame_clicked()
{
    ui->startGame->setVisible(false);
    ui->loadGame->setVisible(false);
    ShowModeButtons(true);
}

void MainWindow::on_AMode_clicked()
{
    ShowModeButtons(false);
    GetPLayerName();
}
void MainWindow::on_CMode_clicked()
{
    ShowModeButtons(false);
    GetPLayerName();
}
void MainWindow::on_BMode_clicked()
{
    ShowModeButtons(false);
    GetPLayerName();
}
void MainWindow::on_BCMode_clicked()
{
    ShowModeButtons(false);
    GetPLayerName();
}
