#ifndef MSEQGENA_H
#define MSEQGENA_H
#include <QBitArray>

class mSeqGenA
{
public:
    mSeqGenA();
    QBitArray PNseq(int polyDeg, int seqLength, QBitArray taps_seed);

};

#endif // MSEQGENA_H
