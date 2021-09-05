#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_File_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSava_as_csv_triggered();

    void on_actionQuit_triggered();

private:
    void setValueAt(int ix, int jx, const QString &value);
    QString getValueAt(int ix, int jx);

    Ui::MainWindow *ui;
    QStandardItemModel *mModel;
};
#endif // MAINWINDOW_H
