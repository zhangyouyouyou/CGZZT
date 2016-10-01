#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QAction>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLabel *imageLabel;
    QLabel *ansLabel;
    QWidget *widget;
    QAction *openAction;
    QString path;

    void openFile();
    void setLabelPic();
    void predict();
    void setAnsStr(QString &ans);
};

#endif // MAINWINDOW_H
