#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include<QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void ShowModeButtons(bool ok);
    void GetPLayerName();
private slots:
    void on_Eter_clicked();
    void on_startGame_clicked();
    // void on_loadGame_clicked();
    void on_AMode_clicked();
    void on_BMode_clicked();
    void on_CMode_clicked();
    void on_BCMode_clicked();

};
#endif // MAINWINDOW_H
