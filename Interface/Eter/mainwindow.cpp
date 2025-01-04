#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"amodewindow.h"
using namespace eter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ETER");
    setFixedSize(1380, 575);

    this->setStyleSheet("QMainWindow { background-image: url(:/background.jpg); "
                        "background-repeat: no-repeat; "
                        "background-position: center; }");

    ui->startGame->setVisible(false);
    ui->loadGame->setVisible(false);

    ShowModeButtons(false);

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
std::pair<QString,QString> MainWindow::GetPLayerName()
{
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
    std::pair<QString,QString> players;
    players.first=text1;
    players.second=text2;
    return players;
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

    hide();

    AModeWindow *amodeWindow = new AModeWindow(this);
    amodeWindow->show();

    // std::pair<QString,QString>players=GetPLayerName();
    // Player player1(players.first,"red");
    // Player player2(players.second,"blue");
    // GameManager game;
    //game.StartNewGame(player1, player2, "AMode");
}
void MainWindow::on_CMode_clicked()
{
    ShowModeButtons(false);
    //GetPLayerName();
}
void MainWindow::on_BMode_clicked()
{
    ShowModeButtons(false);
    //GetPLayerName();
}
void MainWindow::on_BCMode_clicked()
{
    ShowModeButtons(false);
    //GetPLayerName();
}

