#include "RSABigInteger.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

RSABigInteger::RSABigInteger(int nSize)
{
    SIZE= nSize;
    N.setSize(nSize);
    d.setSize(nSize);
    e.setSize(nSize);
}

RSABigInteger::~RSABigInteger()
{

}

void RSABigInteger::init(BigInteger&p, BigInteger& q)
{
    N.multBigInteger(p,q);
    BigInteger one(p.nSize);
    one.digit[0] = 1;
    BigInteger phi(p.nSize);

    BigInteger tempP(p.nSize), tempQ(p.nSize);

    tempP.subBigInteger(p,one);
    tempQ.subBigInteger(q,one);

    phi.multBigInteger(tempP,tempQ);
    cout<<"\nGenerated 'phi' :"<<endl;
    phi.showDigits();
    eGeneration(phi,e);
    cout<<"\nGenerated 'e' :"<<endl;
    e.showDigits();
    CalculateD(e,phi,d);
    cout<<"\nGenerated 'd' :"<<endl;
    d.showDigits();
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

void RSABigInteger::encryption(BigInteger& msg, BigInteger& code)
{
    BigInteger temp(SIZE);
    temp.expoModNBigInteger(msg, e, N, code);

}

void RSABigInteger::decryption(BigInteger& code, BigInteger& msg)
{
    BigInteger temp(SIZE);
    temp.expoModNBigInteger(code, d, N, msg);

}

void RSABigInteger::primeNumberGeneration(BigInteger& randPrime, int n)
{
    BigInteger valueOne(randPrime.nSize);
    valueOne.digit[0] = 1;
    BigInteger valueTwo(randPrime.nSize);
    valueTwo.digit[0] = 2;
    BigInteger valueThree(randPrime.nSize);
    valueThree.digit[0] = 3;

    BigInteger tempPrime(randPrime.nSize);
    BigInteger tempExpoDummy(randPrime.nSize);
    BigInteger ExpoDummy(randPrime.nSize);

    BigInteger tempRemainder(randPrime.nSize);
    BigInteger tempPrimeMinusOne(randPrime.nSize);
    randomNGeneration(tempPrime,n);

    while(1)
    {
        tempPrimeMinusOne.clearBigInteger();
        tempRemainder.clearBigInteger();
        ExpoDummy.clearBigInteger();
        tempExpoDummy.clearBigInteger();
        tempPrimeMinusOne.subBigInteger(tempPrime, valueOne);

        ExpoDummy.expoModNBigInteger(valueTwo, tempPrimeMinusOne, tempPrime, tempRemainder);

        if(tempRemainder.msbBigInteger()==0 && tempRemainder.digit[0]==1)
        {
            cout<<"Prime Number Generating ... Wait a little bit\n";
            tempRemainder.clearBigInteger();
            tempExpoDummy.expoModNBigInteger(valueThree, tempPrimeMinusOne, tempPrime, tempRemainder);
            if(tempRemainder.msbBigInteger()==0 && tempRemainder.digit[0]==1)
            {
                break;
            }
        }
        tempPrime.clearBigInteger();
        randomNGeneration(tempPrime,n);
    }
    randPrime.copyBigInteger(tempPrime,0);
}

void RSABigInteger::randomNGeneration(BigInteger& randResult, int n)
{
    for(int i=0;i<n;i++)
    {
        unsigned int rnd = rand();
        randResult.digit[i] = randResult.digit[i] | rnd<<16;
        rnd = rand();
        randResult.digit[i] = randResult.digit[i] | rnd<<1;
    }
    randResult.digit[0] = randResult.digit[0] | 1;
    randResult.digit[n-1] = randResult.digit[n-1] | 1<<30;
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
