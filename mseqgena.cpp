#include "mseqgena.h"
#include <QDebug>
#include <QBitArray>

mSeqGenA::mSeqGenA()
{

}

QBitArray mSeqGenA::PNseq(int polyDeg,int seqLength, QBitArray taps_seed){
    int i,j;
    int xor1, xor2;
    QBitArray PNseq(seqLength);
    QBitArray temp(polyDeg);

    temp = taps_seed;

    if (seqLength<32){
        for (i=0; i<seqLength; i++){

            xor2 = taps_seed[3] ^ taps_seed[polyDeg-1];
            xor2 = xor2 ^ taps_seed[2];
            xor1 = xor2 ^ taps_seed[1];

            //shifting the taps
            for (j=(polyDeg-1); j>0; j--){
                temp[j]= taps_seed[j-1];
            }
            j=0;
            temp[j] = xor1;

            PNseq[i] = taps_seed[polyDeg-1];
            taps_seed = temp;
        }

//        for (i=seqLength; i>0; i--){
//            qDebug() << PNseq[i-1];}
//        qDebug() << "";
    }
    else if(seqLength>32){
        if (seqLength<64){
            for (i=0; i<seqLength; i++){

                xor2 = taps_seed[4] ^ taps_seed[polyDeg-1];
                xor2 = xor2 ^ taps_seed[1];
                xor1 = xor2 ^ taps_seed[0];

                //shifting the sequence
                for (j=(polyDeg-1); j>0; j--){
                    temp[j]= taps_seed[j-1];
                }
                j=0;
                temp[j] = xor1;

                PNseq[i] = taps_seed[polyDeg-1];
                taps_seed = temp;
            }

//            for (i=0; i<seqLength; i++){
//                qDebug() << PNseq[i];}
//            qDebug() << "";
        }
        else if (seqLength>64){
            for (i=0; i<seqLength; i++){

                xor2 = taps_seed[5] ^ taps_seed[polyDeg-1];
                xor2 = xor2 ^ taps_seed[4];
                xor1 = xor2 ^ taps_seed[3];

                //shifting the sequence
                for (j=(polyDeg-1); j>0; j--){
                    temp[j]= taps_seed[j-1];
                }
                j=0;
                temp[j] = xor1;

                PNseq[i] = taps_seed[polyDeg-1];
                taps_seed = temp;
            }

//            for (i=0; i<seqLength; i++){
//                qDebug() << PNseq[i];}
//            qDebug() << "";
        }
    }
    return PNseq;
}

