#include "amodewindow.h"
#include "ui_amodewindow.h"
#include <QPixmap>

AModeWindow::AModeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AModeWindow)
{
    ui->setupUi(this);
    setWindowTitle("ETER: TRAINING MODE");
    this->setStyleSheet("AModeWindow { background-image: url(:/purpleBG.jpeg); "
                        "background-repeat: no-repeat; "
                        "background-position: center; }");
    QPixmap card1(":\card_1_red.png");
    ui->label->setScaledContents(true);  // Permite QLabel să ajusteze imaginea
    ui->label->setFixedSize(100, 100); // O dimensiune pătrată mai mică decât imaginea


    // Scalarea cu transformare lină și păstrarea proporțiilor
    QPixmap scaledPixmap = card1.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(scaledPixmap);
}

AModeWindow::~AModeWindow()
{
    delete ui;
}
