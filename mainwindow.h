#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Lib/encryption.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Menubar_AboutToShow_triggered();
    void on_action_Open_triggered();
    void on_action_Login_triggered();
    void on_action_logOut_triggered();
    void on_action_Set_Keys_triggered();
    void on_action_Exit_triggered();

    void on_actionChange_Password_triggered();

    void on_actionSave_As_triggered();

    void on_action_Save_triggered();

    void on_action_About_triggered();

private:
    Ui::MainWindow *ui;
    Encryption *enc;
    QString currentFilename ;

};

#endif // MAINWINDOW_H
