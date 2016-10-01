#include "mainwindow.h"

#include <QDebug>
#include <QPixmap>
#include <QPicture>
#include <QHBoxLayout>
#include <QProcess>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget(this);

    imageLabel = new QLabel(widget);
    imageLabel->setGeometry(0,0,600,400);

    ansLabel = new QLabel(widget);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);
    layout->addWidget(ansLabel);

    widget->setLayout(layout);

    openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{
    path = QFileDialog::getOpenFileName(this,
                                        tr("Open File"),
                                        ".",
                                        tr("PNG Files(*.png)"));
    qDebug() << path;
    if(!path.isEmpty()) {
        setLabelPic();
        predict();
    } else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
}

void MainWindow::setLabelPic()
{
    QPixmap pix(path);
    imageLabel->setPixmap(pix);
    imageLabel->setPixmap(pix.scaled(300,200));
    //
}

void MainWindow::predict()
{
    QProcess *p = new QProcess;
    QString command = "python";
    QStringList args;
    args.append("predictone.py");
    args.append(path);

    connect(p,&QProcess::readyReadStandardOutput,[=]{
        QString ans = p->readAllStandardOutput();
        qDebug() << "Get " << ans;
        setAnsStr(ans);
    });
    p->start(command,args);
}

void MainWindow::setAnsStr(QString &ans)
{
    qDebug() << ans;
    ansLabel->setText(ans);
}
