#ifndef AMODEWINDOW_H
#define AMODEWINDOW_H

#include <QMainWindow>

namespace Ui {
class AModeWindow;
}

class AModeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AModeWindow(QWidget *parent = nullptr);
    ~AModeWindow();

private:
    Ui::AModeWindow *ui;
};

#endif // AMODEWINDOW_H
