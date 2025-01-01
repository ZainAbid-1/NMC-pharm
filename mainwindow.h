#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include<QMessageBox>
#include <QMainWindow>

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

private slots:
    void on_signupbutton_clicked();

    void on_pushButton_clicked();

    void on_signupbtn_clicked();

    void on_signupbt_clicked();

    void on_confirmbutton_clicked();

    void on_pushButton_7_clicked();

    void on_signupbutton_2_clicked();

    void on_signupbutton_3_clicked();

    void on_nmcpharm_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_adminsignin_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_confirmorder_clicked();

    void on_confirmorder2_clicked();

    void on_typemed_clicked();

    void on_diseaseconfirm_clicked();

    void on_vieworderbutton_clicked();

    void on_adminsignin_2_clicked();

    void on_vieworderbutton_2_clicked();

    void on_vieworderbutton_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_medline_cursorPositionChanged(int arg1, int arg2);

    void on_azomaxP_linkActivated(const QString &link);

    void displayPrice();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_37_clicked();

    void on_prev_clicked();

    void on_prev_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
};
#endif // MAINWINDOW_H
