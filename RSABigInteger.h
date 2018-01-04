
#include "BigInteger.h"

#ifndef RSABIGINTEGER_H
#define RSABIGINTEGER_H


class RSABigInteger
{
    public:
        int nSize;

        RSABigInteger();

        void eGeneration(BigInteger& phi,BigInteger& result);
        void CalculateD(BigInteger& e, BigInteger& phi, BigInteger& d);

        void encryption(BigInteger& PublicKey, BigInteger& N, BigInteger& msg, BigInteger& code);
        void decryption(BigInteger& PrivateKey, BigInteger& N, BigInteger& code, BigInteger& msg);

        virtual ~RSABigInteger();

};

#endif // RSABIGINTEGER_H
