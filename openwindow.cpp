#include "openwindow.h"
#include "mainwindow.h"
#include "newwindow.h"
#include "ui_openwindow.h"
#include "binarytree.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QString>
#include <string>

OpenWindow::OpenWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenWindow)
{
    ui->setupUi(this);
    QString filename = QFileDialog::getOpenFileName(this, "Відкрити файл");
    curFile = filename;
    QFile file(curFile);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл: " + file.errorString());
        MainWindow* mw = new MainWindow();
        mw->show();
        this->hide();
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        words = line.split(" ");
    }
    file.close();
    root = root->arrToTree(words);
    set_param();
}

OpenWindow::~OpenWindow()
{
    delete ui;
}

void OpenWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Зберегти як", "C://", "Text Files (*.txt);;All Files (*.*)");
    if (!filename.isEmpty()) {
        curFile = filename;
        saveFile();
    }
}

void OpenWindow::set_param() {
    if (root == nullptr) ui->labelTree_2->setText("Дерево пусте");
    else {
        QString text_tree = "";
        root->print2D(root, 0, &text_tree);
        ui->labelTree_2->setText(text_tree);
        ui->labelTree_2->show();
    }
    txt_size = "Розмір дерева: " + QString::number(root->get_size(root));
    txt_height = "Висота дерева: " + QString::number(root->get_height(root));
    ui->labelSize->setText(txt_size);
    ui->labelHeight->setText(txt_height);
}

void OpenWindow::saveFile() {
    QFile file(curFile);
    if (file.open(QFile::WriteOnly)) {
        QString tree_text;
        root->preOrder_print(root, &tree_text);
        QTextStream out(&file);
        out << tree_text;
    } else {
        QMessageBox::warning(
                    this, "Помилка",
                    tr("Не вдалося відкрити файл %1. \nПомилка: %2").arg(curFile).arg(file.errorString()));
    }
}

bool OpenWindow::int_check(std::string s) {
    int neg = 0;
    if (s[0] == '-') neg = 1;
    for (int i = neg; i < s.size(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

void OpenWindow::on_addButton_2_clicked()
{
    QString Qdata = ui->lineEdit_elem_2->text();
    std::string s_data = Qdata.toStdString();
    ui->lineEdit_elem_2->clear();

    if (!int_check(s_data) || s_data == "") {
        QMessageBox::information(this, "Помилка", "Неправильний формат даних");
    }
    else {
        int data = stoi(s_data);
        if (root->find(root, data) != nullptr){
            QMessageBox::information(this, "Помилка", "Елемент вже був доданий раніше");
        }
        else {
            root->insert(root, data);
            set_param();
        }
    }
}


void OpenWindow::on_deleteButton_2_clicked()
{
    if (root == nullptr) QMessageBox::information(this, "Помилка", "Дерево пусте. Додайте елементи і спробуйте ще раз");
    else {
        QString Qdata = ui->lineEdit_elem_2->text();
        std::string s_data = Qdata.toStdString();
        ui->lineEdit_elem_2->clear();

        if (!int_check(s_data) || s_data == "") {
            QMessageBox::information(this, "Помилка", "Неправильний формат даних");
        }
        else {
            int data = stoi(s_data);
            if (root->find(root, data) == nullptr){
                QMessageBox::information(this, "Помилка", "Елемент не був знайдений в дереві");
            }
            else {
                root = root->erase(root, data);
                set_param();
            }
        }
    }
}


void OpenWindow::on_balanceButton_2_clicked()
{
    if (root->isComplete(root)) QMessageBox::information(this, "Виконано успішно", "Дерево вже збалансоване");
    else {
        root = root->balanceTree(root);
        set_param();
    }
}


void OpenWindow::on_deleteTreeButton_2_clicked()
{
    if (root == nullptr) QMessageBox::information(this, "Помилка", "Дерево вже пусте");
    else {
        root->delete_tree(root);
        root = nullptr;
        set_param();
    }
}


void OpenWindow::on_preOrderButton_2_clicked()
{
    if (root == nullptr) QMessageBox::information(this, "Помилка", "Дерево пусте");
    else {
        QString tree_text;
        root->preOrder_print(root, &tree_text);
        QMessageBox::information(this, "Прямий обхід дерева", tree_text);
    }
}


void OpenWindow::on_inOrderButton_2_clicked()
{
    if (root == nullptr) QMessageBox::information(this, "Помилка", "Дерево пусте");
    else {
        QString tree_text;
        root->inOrder_print(root, &tree_text);
        QMessageBox::information(this, "Серединний обхід дерева", tree_text);
    }
}


void OpenWindow::on_postOrderButton_2_clicked()
{
    if (root == nullptr) QMessageBox::information(this, "Помилка", "Дерево пусте");
    else {
        QString tree_text;
        root->postOrder_print(root, &tree_text);
        QMessageBox::information(this, "Зворотній обхід дерева", tree_text);
    }
}


void OpenWindow::on_actionInfTree_triggered()
{
    QMessageBox::information(this, "Про дерева", "Дерево — структура даних, яка складається з вузлів (вершин) \
    і ребер, без будь-яких циклів.\n\n"
    "Бінарне дерево пошуку — це структура даних на основі вузлів, де кожен вузол містить ключ і два піддерева, лівий та правий. \
    Для всіх вузлів ключ лівого піддерева повинен бути меншим ніж ключ вузла, а ключ правого піддерева повинен бути більшим ніж ключ вузла.\n\n"
    "Висота дерева - довжина найдовшого шляху від кореня (вузла без батьківських елементів) до листя(вузла без дочірніх елементів).\n\n"
    "Розмір дерева - кількість вузлів у ньому\n\n"
    "Бінарне дерево пошуку є збалансованим, якщо різниця у висоті обох піддерев довільної вершини дерева дорівнює нулю або одиниці. \
    Також дерево вважається ідельно збалансованим, якщо воно збалансоване, листя знаходяться на одному або двох рівнях \
    та всі вузли останнього рівня знаходяться якомога лівіше");
}



void OpenWindow::on_actionInfProg_triggered()
{
    QMessageBox::information(this, "Про роботу програми", "Суть роботи даної програми полягає в проведені операцій над бінарними деревами пошуку,зокрема з ідеально збалансованими деревами.\n\n"
                                                          "В лівій частині екрана зображується поточне дерево. Для проведення операцій над ним необхідно натиснути на відповідну кнопку, що знаходиться справа. У випадку додавання/видалення елементу також потрібно ввести дані (цілі числа) в текстове поле, що знаходиться над кнопками. В нижній частині екрана можна обрати метод для роздрукування дерева в потрібному вигляді (згідно з прямим, серединним чи зворотнім обходом). Також у правій верхній частині екрані можна спостерігати поточну висоту та розмір дерева, що змінюється після кожного відпрацювання методу над деревом.\n\n"
                                                          "Вгорі розташовано панель меню, яка дозволяє зберегти поточне дерево, дізнатися більше про роботу програми та сутність дерева як структур даних, завершити роботу програми\n\n"
                                                          "У разі виникнення проблем, наприклад, введення некоректних даних, на екран виведеться відповідне повідомлення");
}


void OpenWindow::on_actionInfExit_triggered()
{
    QApplication::exit();
}
