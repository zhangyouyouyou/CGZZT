#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QAction>
#include <QPixmap>
#include <QDrag>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QLabel *imageLabel;
    QLabel *ansLabel;
    QWidget *widget;
    QAction *openAction;
    QString path;

    void picSelected();
    void openFile();
    void setLabelPic();
    void predict();
    void setAnsStr(QString &ans);
};

#endif // MAINWINDOW_H
