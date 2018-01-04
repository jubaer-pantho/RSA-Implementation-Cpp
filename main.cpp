#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include "BigInteger.h"
#include "RSABigInteger.h"


using std::cout;
using std::cerr;
using std::string;
using std::auto_ptr;

using namespace std;


int main()
{
    BigInteger a(10);
    BigInteger b(10);
    BigInteger sum(10);
    BigInteger sub(10);
    BigInteger mult(10);
    BigInteger modd(10);



    a.setDigits(0);
    b.setDigits(1);

    printf("a=");
    a.showDigits();

    printf("b=");
    b.showDigits();

    sum.addBigInteger(a,b);
    printf("add=");
    sum.showDigits();

    sub.subBigInteger(a,b);
    printf("sub=");
    sub.showDigits();

    mult.multBigInteger(a,b);
    printf("mult=");
    mult.showDigits();

    int comp= Compare(a,b);
    cout<< "comp = " << comp << endl;

    BigInteger d(10);
    divBigInteger(a, b, d, modd);
    cout<<"Division=";
    d.showDigits();
    cout<<"Remainder=";
    modd.showDigits();

    BigInteger result(10);

    gcdBigInteger(a,b,result);

    cout <<"gcd=";
    result.showDigits();

    BigInteger expo(10), expoThis(10);

    BigInteger N(10);
    N.setDigits(2);
    cout<<"expo=";
    expoThis.expoModNBigInteger(b,a,N,expo);
    expo.showDigits();

    RSABigInteger eGen;
    BigInteger phi(10);
    BigInteger e(10);
    phi.digit[0]=20;

    BigInteger c(10);
    c.setDigits(2);


    cout<<"evalue=";
    eGen.eGeneration(phi, e);
    e.showDigits();

    BigInteger msg(10);
    BigInteger msg2(10);

    msg.digit[0] = 2;
    BigInteger code(10);


    eGen.encryption(b, a, msg, code);

    cout<<"code=";
    code.showDigits();

    eGen.decryption(c, a, code, msg2);

    cout<<"msg=";
    msg2.showDigits();


    return 0;

}
