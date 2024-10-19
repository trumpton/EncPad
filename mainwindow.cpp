#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "../Lib/supportfunctions.h"
#include "../Lib/warningok.h"
#include "../Lib/warningyesno.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialise encryption i/o
    enc = new Encryption(QString("trumpton.uk"), QString("TextFileEncryption")) ;

    // Handle menu hiding etc.
    connect(ui->menu_File, SIGNAL(aboutToShow()), this, SLOT(on_action_Menubar_AboutToShow_triggered())) ;

    // Login if not already logged in
    if (!enc->loggedIn()) { enc->login() ; }

    currentFilename=QString("") ;

}

MainWindow::~MainWindow()
{
    delete enc ;
    delete ui;
}

void MainWindow::on_action_Menubar_AboutToShow_triggered()
{
    bool loggedin = enc->loggedIn() ;
    ui->action_Open->setEnabled(loggedin) ;
    ui->action_logOut->setEnabled(loggedin) ;
    ui->action_Login->setEnabled(!loggedin) ;
    ui->action_Set_Keys->setEnabled(!loggedin) ;
    ui->actionChange_Password->setEnabled(!loggedin);
}

void MainWindow::on_action_Open_triggered()
{
    if (!enc->loggedIn()) return ;

    QFileDialog dlg ;
    QString filename = dlg.getOpenFileName(this, "Load Encrypted File", QString(), QString("*.z*")) ;
    if (!filename.isEmpty()) {
        QByteArray contents ;
        if (enc->load(filename, contents)) {
            QString data(contents);
            ui->plainTextEdit->setPlainText(data);
            currentFilename=filename ;
        } else {
            ui->plainTextEdit->setPlainText("Load failed");
            currentFilename=QString("") ;
        }
    }
}

void MainWindow::on_action_Login_triggered()
{
    if (!enc->loggedIn()) {
        enc->login() ;
        if (!enc->loggedIn()) {
            WarningOk warn ;
            warn.setText("Login Failed") ;
            warn.exec() ;
        }
    }
}

void MainWindow::on_action_logOut_triggered()
{
    if (enc->loggedIn()) {
        enc->logout() ;
    }

}

void MainWindow::on_action_Set_Keys_triggered()
{
    enc->setKey() ;
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::quit() ;
}

void MainWindow::on_actionChange_Password_triggered()
{
    if (enc->loggedIn()) return ;
    enc->changePassword();
}

void MainWindow::on_actionSave_As_triggered()
{
    if (!enc->loggedIn()) return ;

    QFileDialog dlg ;
    QString filename = dlg.getSaveFileName(this, "Save Encrypted File", QString(), QString("*.z*")) ;
    if (!filename.isEmpty()) {
        currentFilename = filename ;
        on_action_Save_triggered() ;
    }
}


void MainWindow::on_action_Save_triggered()
{
    if (!enc->loggedIn()) return ;
    if (currentFilename.isEmpty()) return ;

    QFileInfo fi(currentFilename) ;

    if (fi.exists()) {
        WarningYesNo yn ;
        yn.setText(QString("Overwrite file?"));
        yn.setButtons("Yes", 'y', "No", 'n');
        if (!yn.exec()) {
            return ;
        }
    }

    QString contents ;
    contents = ui->plainTextEdit->toPlainText() ;
    QByteArray data = contents.toUtf8() ;

    if (!enc->save(currentFilename, data)) {
        WarningOk ok ;
        ok.setText("Error saving file") ;
        ok.exec() ;
    }

}

void MainWindow::on_action_About_triggered()
{
    QString text ;

    if (QString(GITHASH).length()>0) text = text + QString("Easy Notepad Version: %1.\n").arg(GITHASH) ;
    if (QString(LIBHASH).length()>0) text = text + QString("Library Version: %1.\n").arg(LIBHASH) ;
    text = text + QString("Build Date: %1.\n").arg(BUILDDATE) ;

    warningOkDialog(this, QString("About Encrypt Pad"), text)  ;

}
