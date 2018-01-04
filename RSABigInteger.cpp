#include "RSABigInteger.h"

RSABigInteger::RSABigInteger()
{
    //ctor
}

RSABigInteger::~RSABigInteger()
{
    //dtor
}


void RSABigInteger::eGeneration(BigInteger& phi, BigInteger& result)
{
    BigInteger temp(phi.nSize);
    temp.digit[0]=3;

    BigInteger value2(phi.nSize);
    value2.digit[0]=2;
    BigInteger temp2(phi.nSize);

    while(1)
    {
        BigInteger gcdValue(phi.nSize);
        gcdBigInteger(phi, temp, gcdValue);

        if(gcdValue.msbBigInteger() == 0 && gcdValue.digit[0]==1)
        {
            break;
        }

        temp2.addBigInteger(temp, value2);

        temp.copyBigInteger(temp2,0);


    }

    result.copyBigInteger(temp, 0);



}

void RSABigInteger::encryption(BigInteger& PublicKey, BigInteger& N, BigInteger& msg, BigInteger& code)
{
    BigInteger temp(N.nSize);

    temp.expoModNBigInteger(msg, PublicKey, N, code);

}

void RSABigInteger::decryption(BigInteger& PrivateKey, BigInteger& N, BigInteger& code, BigInteger& msg)
{
    BigInteger temp(N.nSize);

    temp.expoModNBigInteger(code, PrivateKey, N, msg);

}


void RSABigInteger::CalculateD(BigInteger& e, BigInteger& phi, BigInteger& d)
{
    int i =0;
    BigInteger temp1(phi.nSize),temp2(phi.nSize),quotient(phi.nSize),remainder(phi.nSize);
    BigInteger one(phi.nSize);
    one.digit[0] = 1;
    BigInteger k(phi.nSize);
    while(true)
    {
        i++;
        k.digit[0] = i;
        temp1.multBigInteger(k,phi);
        temp2.addBigInteger(temp1,one);
        divBigInteger(temp2,e,quotient,remainder);
        if(remainder.msbBigInteger() == 0 && remainder.digit[0] == 0)
        {
            d.copyBigInteger(quotient,0);
            break;
        }
    }
}
