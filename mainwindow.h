#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mseqgena.h"
#include "mseqgenb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setAttemptID(int value);
    int getAttemptID() const;

private:
    Ui::MainWindow *ui;

    int attemptID = 1;

    int polyDeg;
    int seqLength;

    mSeqGenA *mpmSeqGenA;
    mSeqGenB *mpmSeqGenB;

    int setSeqLength(int polyDeg);

    QString arrToStr(QBitArray arr);
    QString arrToStr(QByteArray arr);
    QByteArray bitsToBytes(QBitArray arr);
    QBitArray gold(int seqLength, QBitArray seqA, QBitArray seqB);

private slots:
    void GenerateGoldCode();

};

#endif // MAINWINDOW_H
