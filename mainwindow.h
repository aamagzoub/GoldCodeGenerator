#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mseqgena.h"
#include "mseqgenb.h"

#include <QTimer>

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
    void setCurrentPolyDegree(int value);

    int getAttemptID() const;
    int getCurrentPolyDegree() const;

private:
    Ui::MainWindow *ui;

    int attemptID;
    int currentPolyDegree;
    int polyDeg;
    int seqLength;
    int setSeqLength(int polyDeg);
    int polyValue;

    mSeqGenA *mpmSeqGenA;
    mSeqGenB *mpmSeqGenB;
    QString arrToStr(QBitArray arr);
    QString arrToStr(QByteArray arr);
    QByteArray bitsToBytes(QBitArray arr);

    void generateGoldCodes(int seqLength, QBitArray seqA, QBitArray seqB);
    void setGGVersionOnStart();
    void setStatusWinColors();
    void progressCount();

private slots:
    void generateGoldCode();
    void clearViewOnGui();
    void setPolyValue5();
    void setPolyValue6();
    void setPolyValue7();
    void setPolyValue8();
    void setPolyValue9();
    void setPolyValue10();
};

#endif // MAINWINDOW_H
