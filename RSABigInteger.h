#ifndef RSABIGINTEGER_H
#define RSABIGINTEGER_H
#include "BigInteger.h"

class RSABigInteger
{
    public:
        RSABigInteger(int nSize);
        virtual ~RSABigInteger();

        void CalculateD(BigInteger& e, BigInteger& phi, BigInteger& d);
        void init(BigInteger&p, BigInteger& q);
        void eGeneration(BigInteger& phi,BigInteger& result);
        void encryption(BigInteger& msg, BigInteger& code);
        void decryption(BigInteger& code, BigInteger& msg);
        void randomNGeneration(BigInteger& randResult, int n);
        void primeNumberGeneration(BigInteger& randPrime, int n);

    private:
        int SIZE;
        BigInteger N;
        BigInteger d;
        BigInteger e;
};

#endif // RSABIGINTEGER_H
