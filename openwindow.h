#ifndef OPENWINDOW_H
#define OPENWINDOW_H
#include "binarytree.h"
#include <QMainWindow>

namespace Ui {
class OpenWindow;
}

class OpenWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenWindow(QWidget *parent = nullptr);
    ~OpenWindow();

private slots:
    void on_addButton_2_clicked();

    void on_deleteButton_2_clicked();

    void on_balanceButton_2_clicked();

    void on_deleteTreeButton_2_clicked();

    void on_preOrderButton_2_clicked();

    void on_inOrderButton_2_clicked();

    void on_postOrderButton_2_clicked();

    void on_actionSave_triggered();

    void on_actionInfTree_triggered();

    void on_actionInfProg_triggered();

    void on_actionInfExit_triggered();

private:
    Ui::OpenWindow *ui;
    QString curFile;
    QStringList words;
    QString txt_size;
    QString txt_height;
    void set_param();
    BinaryTree* root = nullptr;
    void saveFile();
    bool int_check(std::string s);
};

#endif // OPENWINDOW_H
