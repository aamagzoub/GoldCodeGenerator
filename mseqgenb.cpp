#include "mseqgenb.h"
#include <QDebug>
#include <QBitArray>

mSeqGenB::mSeqGenB()
{

}

QBitArray mSeqGenB::PNseq(int polyDeg,int seqLength, QBitArray taps_seed){
    int i, j;
    int xor1;
    QBitArray PNseq(seqLength);
    QBitArray temp(polyDeg);

    temp = taps_seed;

    if (seqLength<=32){
        for (i=0; i<seqLength; i++){

            xor1 = taps_seed[2] ^ taps_seed[polyDeg-1];

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
    else if (seqLength>31){
        if (seqLength<=64){
            for (i=0; i<seqLength; i++){

                xor1 = taps_seed[0] ^ taps_seed[polyDeg-1];

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

                xor1 = taps_seed[3] ^ taps_seed[polyDeg-1];

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

