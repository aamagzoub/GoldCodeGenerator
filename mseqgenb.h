#ifndef MSEQGENB_H
#define MSEQGENB_H
#include <QBitArray>


class mSeqGenB
{
public:
    mSeqGenB();
    QBitArray PNseq(int polyDeg, int seqLength, QBitArray taps_seed);
};

#endif // MSEQGENB_H
