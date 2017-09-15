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
    void setCurrentPolyDegree(int value);
    int getCurrentPolyDegree() const;
private:
    Ui::MainWindow *ui;

    int attemptID = 1;
    int currentPolyDegree;
    int polyDeg;
    int seqLength;
    mSeqGenA *mpmSeqGenA;
    mSeqGenB *mpmSeqGenB;
    int setSeqLength(int polyDeg);
    QString arrToStr(QBitArray arr);
    QString arrToStr(QByteArray arr);
    QByteArray bitsToBytes(QBitArray arr);
    void gold(int seqLength, QBitArray seqA, QBitArray seqB);    
    void setGGVersionOnStart();
    void setStatusWinColors();
private slots:
    void generateGoldCode();
    void clearViewOnGui();
    void isSamePolyDeg();

};

#endif // MAINWINDOW_H
