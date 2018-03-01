#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple Notepad");
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//New window/file
void MainWindow::on_actionNew_triggered()
{
    //I ask whether user want to save file first
        if(QMessageBox::question(this, "Warning", "Do you want to save file before opening a new one?") == QMessageBox::Yes)
           this->on_actionSave_triggered();

    file_path = ""; //reset
    ui->textEdit->clear();  //clear editor
    this->setWindowTitle("Simple Notepad"); //reset notepad name
}

//Open a text file
void MainWindow::on_actionOpen_triggered()
{
    //Open a file .txt
    QString filter = "Text File (*.txt)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C:/Users/secret/Documents", filter);
    file_path = file_name;
    QFile file(file_name);

    //Print error msg if file is not opened
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Error", "File isn't open");
        return;
    }

    //Change title of notepad
    QFileInfo fileInfo(file.fileName());
    this->setWindowTitle(fileInfo.fileName());

    //Add text to Editor
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();
}

//Save already opened file
void MainWindow::on_actionSave_triggered()
{
    //Check already opened file
        QFile file(file_path);

    //If no file is selected, we shall make one, by calling Save As function
        if (!file.open(QFile::WriteOnly | QFile::Text)){
            MainWindow::on_actionSave_As_triggered();
            return;
        }

    //To change name of title
        QFileInfo fileInfo(file.fileName());
        this->setWindowTitle(fileInfo.fileName());

    //Save PLAIN text
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out<<text;
        file.flush();
        file.close();

}

//Save as
void MainWindow::on_actionSave_As_triggered()
{
    //To choose directory and write the name of the file
        QString file_name = QFileDialog::getSaveFileName(this, "Select a directory", "C:/Users/secret/Documents", "Text File (*.txt)");
        QFile file(file_name);

    //Show an error msg if file is not saved
        if (!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "Error", "File isn't saved");
            return;
        }

    //To change name of title
        QFileInfo fileInfo(file.fileName());
        this->setWindowTitle(fileInfo.fileName());

    //save file_name i file_path
        file_path = file_name;

    //Save PLAIN text
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out<<text;
        file.flush();
        file.close();
}

//close the window
void MainWindow::on_actionExit_triggered()
{
    //I ask whether user want to save file first
    if(QMessageBox::question(this, "Warning", "Do you want to save file before exit?") == QMessageBox::Yes)
       this->on_actionSave_triggered();

    this->close();
}

//Cut selected text
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//Copy selected text
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

//Paste text in clipboard
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//Redo last undo
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//Undo last change
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//Change font
void MainWindow::on_actionFont_triggered()
{
    bool check;
    QFont font  = QFontDialog::getFont(&check, this);

    //if font is selected
    if (check)
        ui->textEdit->setFont(font);

}

//Change color of text
void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");
    //make sure color is valid
    if (color.isValid())
        ui->textEdit->setTextColor(color);
}

//Highligh text
void MainWindow::on_actionHighlight_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");

    if (color.isValid())
        ui->textEdit->setTextBackgroundColor(color);
}

//Change background color for editor
void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");

    if (color.isValid())
        ui->textEdit->setPalette(QPalette(color));
}

//about the program
void MainWindow::on_actionAbout_SimpleNotePad_triggered()
{
    QString info = "Author: Radwa Khattab\n";
    info += "Date: 01 March 2018\n";
    info += "(C) Notepad (R)";
    QMessageBox::about(this, "About Simple Notepad", info);
}
