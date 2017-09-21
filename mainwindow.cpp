#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"
#include <iostream>
#include <QDebug>
#include <QBitArray>
#include <QElapsedTimer>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/gold_icon.ico"));
    mpmSeqGenA = new mSeqGenA;
    mpmSeqGenB = new mSeqGenB;
    attemptID= 1;

    setStatusWinColors();
    setGGVersionOnStart();

    connect(ui->generate_btn,SIGNAL(clicked()),this,SLOT(isSamePolyDeg()));
    connect(ui->clear_btn,SIGNAL(clicked()),this,SLOT(clearViewOnGui()));
    connect(ui->exit_btn,SIGNAL(clicked()),this,SLOT(close()));


}

void MainWindow::isSamePolyDeg(){
    if(getCurrentPolyDegree() != ui->poly_deg_val->currentIndex()){
        clearViewOnGui();
        generateGoldCode();
    }
}

void MainWindow::generateGoldCode(){
    QTime myTimer;
    myTimer.start();
    ui->progressBar->reset();
    setCurrentPolyDegree(ui->poly_deg_val->currentIndex());

    polyDeg = ui->poly_deg_val->currentText().toInt();
    seqLength = setSeqLength(polyDeg);

    QBitArray taps_seed(polyDeg);
    taps_seed.setBit(4,true);

    ui->status_win->appendPlainText("-> Attempt No\t: " + QString::number(attemptID));
    ui->status_win->appendPlainText("-> Polynomials degree\t: " + QString::number(polyDeg));
    ui->status_win->appendPlainText("-> Sequence Length\t: " + QString::number(seqLength));

    QBitArray seqA = mpmSeqGenA->PNseq(polyDeg, seqLength, taps_seed);
    ui->mseq_1_bits->setText(arrToStr(seqA));
    ui->status_win->appendPlainText("-> 1st m-sequence\t: READY");

    QBitArray seqB = mpmSeqGenB->PNseq(polyDeg, seqLength, taps_seed);
    ui->mseq_2_bits->setText(arrToStr(seqB));
    ui->status_win->appendPlainText("-> 2st m-sequence\t: READY");

    generateGoldCodes(seqLength, seqA, seqB);
    ui->status_win->appendPlainText("-> Gold Codes\t: GENERATED");
    ui->status_win->appendPlainText("-> Time elapsed\t: "+QString::number(myTimer.elapsed()));
    ui->status_win->appendPlainText("-> No. of Bal. Seqs.\t: "+ QString::number(ui->balanced_seq_val->document()->blockCount()-2));
    ui->status_win->appendPlainText("-> No. of Unbal. Seqs.\t: "+ QString::number(ui->unbalanced_seq_val->document()->blockCount()-2));

    ui->status_win->appendPlainText("");

    setAttemptID(attemptID);

}

int MainWindow::setSeqLength(int polyDeg){
    int seqLength = (int)(pow(2,polyDeg) - 1);
    return seqLength;
}

void MainWindow::setAttemptID(int value){
    attemptID = value+1;
}

int MainWindow::getAttemptID() const{
    return attemptID;
}

void MainWindow::setCurrentPolyDegree(int value){
    currentPolyDegree = value;
}

int MainWindow::getCurrentPolyDegree() const{
    return currentPolyDegree;
}

QString MainWindow::arrToStr(QBitArray arr){
    QString arrStr = "";
    for(int i = 0; i<arr.size(); i++)
    {
        arrStr += arr.at(i) ? '1':'0';
    }
    return arrStr;
}

void MainWindow::generateGoldCodes(int seqLength, QBitArray seqA, QBitArray seqB){
    int i, j, d;
    QBitArray gold_code(seqLength);

    ui->progressBar->setRange(0,seqLength);

    for (d=0; d<seqLength; d++){
        ui->progressBar->setValue(d+1);
        QBitArray temp(seqLength);

        // generating the gold code
        for (i=0; i<seqLength; i++)
        {
            gold_code[i] = seqA[i] ^ seqB[i];

        }

        //checking if the gold sequence is balanced & showing the gold code
        int zeros = 0;
        int ones = 0;
        for (i = 0; i<seqLength; i++){
            if (gold_code[i] == 0){
                zeros = zeros+1;
            }
            else            {
                ones = ones+1;
            }
        }

        // display codes:
        if (((zeros == ones) || (zeros == (ones-1)))){
            //balanced codes
            ui->balanced_seq_val->insertPlainText(arrToStr(gold_code));
            ui->balanced_seq_val->insertPlainText("\n");
            ui->balanced_seq_val->moveCursor (QTextCursor::End);
        }else{
            //unbalanced codes
            ui->unbalanced_seq_val->insertPlainText(arrToStr(gold_code));
            ui->unbalanced_seq_val->insertPlainText("\n");
            ui->unbalanced_seq_val->moveCursor (QTextCursor::End);

        }

        //shifting the second m-sequence
        for (j=(seqLength-1); j>0; j--){
            temp[j] = seqB[j-1];
        }

        j=0;
        temp[j] = seqB[(seqLength-1)];

        seqB = temp;
    }
    ui->balanced_seq_val->insertPlainText("\n");
    ui->unbalanced_seq_val->insertPlainText("\n");
}

void MainWindow::clearViewOnGui(){
    ui->status_win->clear();
    ui->mseq_1_bits->clear();
    ui->mseq_2_bits->clear();
    ui->balanced_seq_val->clear();
    ui->unbalanced_seq_val->clear();

    setCurrentPolyDegree(-1);
    setGGVersionOnStart();

    ui->progressBar->reset();
}

void MainWindow::setGGVersionOnStart(){
    ui->status_win->appendPlainText("Gold-Code Generator (version 0.1)");
    ui->status_win->appendPlainText("____________________________");
    ui->status_win->appendPlainText("");
}

void MainWindow::setStatusWinColors(){
    QPalette p = ui->status_win->palette();
    p.setColor(QPalette::Base, QColor(0, 0, 24));
    p.setColor(QPalette::Text,Qt::white);
    ui->status_win->setPalette(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}
