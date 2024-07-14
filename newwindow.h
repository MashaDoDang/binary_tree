#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QMainWindow>
#include "binarytree.h"

namespace Ui {
class NewWindow;
}

class NewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr);
    ~NewWindow();

private slots:
    void on_actionExit_triggered();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_balanceButton_clicked();

    void on_deleteTreeButton_clicked();

    void on_preOrderButton_clicked();

    void on_inOrderButton_clicked();

    void on_postOrderButton_clicked();

    void on_actionSave_triggered();

    void on_actionInfTree_triggered();

    void on_actionInfProg_triggered();

private:
    Ui::NewWindow *ui;
    BinaryTree* root = nullptr;
    void saveFile();
    QString curFile;
    QString txt_size;
    QString txt_height;
    void set_param();
};

#endif // NEWWINDOW_H  
