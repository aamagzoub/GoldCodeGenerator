#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"
#include <iostream>
#include <QDebug>
#include <QBitArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/gold_icon.ico"));
    mpmSeqGenA = new mSeqGenA;
    mpmSeqGenB = new mSeqGenB;

    QPalette p = ui->status_win->palette();
    p.setColor(QPalette::Base, QColor(0, 0, 24));
    p.setColor(QPalette::Text,Qt::white);
    ui->status_win->setPalette(p);

    connect(ui->generate_btn,SIGNAL(clicked()),this,SLOT(generateGoldCode()));

    connect(ui->clear_btn,SIGNAL(clicked()),this,SLOT(clearViewOnGui()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateGoldCode()
{
    polyDeg = ui->poly_deg_val->currentText().toInt();
    seqLength = setSeqLength(polyDeg);

    QBitArray taps_seed(polyDeg);
    taps_seed.setBit(4,true);

    ui->status_win->appendPlainText("-> Attempt No\t: " + QString::number(attemptID));
    ui->status_win->appendPlainText("-> Polynomials degree\t: " + QString::number(polyDeg));
    ui->status_win->appendPlainText("-> Sequence Length\t: " + QString::number(seqLength));

    QBitArray seqA = mpmSeqGenA->PNseq(polyDeg, seqLength, taps_seed);
    ui->seq_1_bits->setText(arrToStr(seqA));
    ui->status_win->appendPlainText("-> 1st m-sequence\t: READY");

    QBitArray seqB = mpmSeqGenB->PNseq(polyDeg, seqLength, taps_seed);
    ui->seq_2_bits->setText(arrToStr(seqB));
    ui->status_win->appendPlainText("-> 2st m-sequence\t: READY");

    gold(seqLength, seqA, seqB);
    ui->status_win->appendPlainText("-> Gold-code\t: GENERATED");

    ui->status_win->appendPlainText("\n");

    setAttemptID(attemptID);
}

int MainWindow::setSeqLength(int polyDeg)
{
    int seqLength = (int)(pow(2,polyDeg) - 1);
    return seqLength;
}

void MainWindow::setAttemptID(int value)
{
    attemptID = value+1;
}

int MainWindow::getAttemptID() const
{
    return attemptID;
}

QString MainWindow::arrToStr(QBitArray arr)
{
    QString arrStr = "";
    for(int i = 0; i<arr.size(); i++)
    {
        arrStr += arr.at(i) ? '1':'0';
    }
    return arrStr;
}

void MainWindow::gold(int seqLength, QBitArray seqA, QBitArray seqB)
{
    int i, j, d;
    QBitArray gold_code(seqLength);

    for (d=0; d<seqLength; d++){
        QBitArray temp(seqLength);

        // generating the gold code
        for (i=0; i<seqLength; i++)
        {
            gold_code[i] = seqA[i] ^ seqB[i];
        }

        //checking if the gold sequence is balanced & showing the gold code
        int zeros = 0;
        int ones = 0;
        for (i = 0; i<seqLength; i++)
        {
            if (gold_code[i] == 0)
            {
                zeros = zeros+1;
            }
            else
            {
                ones = ones+1;
            }
        }

        if ((zeros == ones) || (zeros == (ones-1)))
        {
            ui->gold_code_bits->insertPlainText(arrToStr(gold_code));
            ui->gold_code_bits->insertPlainText("\t'BALANCED'\n");
            ui->gold_code_bits->moveCursor (QTextCursor::End);
        }
        else
        {
            //ui->gold_code_bits->insertPlainText(arrToStr(gold_code));
            //ui->gold_code_bits->insertPlainText("\t'unbalanced'\n");
        }

        //shifting the second m-sequence
        for (j=(seqLength-1); j>0; j--)
        {
            temp[j] = seqB[j-1];
        }

        j=0;
        temp[j] = seqB[(seqLength-1)];

        seqB = temp;
    }
    ui->gold_code_bits->insertPlainText("\n");
}

void MainWindow::clearViewOnGui()
{
    ui->status_win->clear();
    ui->seq_1_bits->clear();
    ui->seq_2_bits->clear();
    ui->gold_code_bits->clear();
}



