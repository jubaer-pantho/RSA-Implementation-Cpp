#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include "BigInteger.h"
#include "RSABigInteger.h"
#include <time.h>

using std::cout;
using std::cerr;
using std::string;
using std::auto_ptr;

using namespace std;

#define SIZEN 98         //     word size bit = N*32
#define HALFSIZE 48      //

#define WORD_COUNT 390
#define SIZE 960		//N

void basicOperationOfBigInteger()
{
    BigInteger num1(SIZEN);
    BigInteger num2(SIZEN);

    RSABigInteger operationCheck(SIZEN);

    operationCheck.randomNGeneration(num1, HALFSIZE); // 1536 bit numbers
    operationCheck.randomNGeneration(num2, HALFSIZE); // 1536 bit numbers

    BigInteger add(SIZEN);
    BigInteger sub(SIZEN);

    cout<<"\nnum1 :\n";
    num1.showDigits();
    cout<<"\nnum2 :\n";
    num2.showDigits();
    

    struct timespec tstart={0,0}, tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    
    add.addBigInteger(num1,num2);
    
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\naddition took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
           
	cout<<"\naddition = num1 + num2 :\n";
	add.showDigits();

    tstart={0,0};
    tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);

	sub.subBigInteger(add, num1);
    
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nsubtraction took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

    cout<<"\nsubtraction = addition - num1 :\n";
    sub.showDigits();
           
    BigInteger mult(SIZEN);
         
    tstart={0,0};
    tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    
    mult.multBigInteger(num1, num2);

    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nmultiplication took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

    cout<<"\nmultiplication = num1 * num2 :\n";
    mult.showDigits();

    BigInteger qotnt(SIZEN);
    BigInteger rem(SIZEN);

    tstart={0,0};
    tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
 
    divBigInteger(mult, num1, qotnt, rem);

    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nDivistion took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
           
    cout<<"\nqotient = multiplication / num1 :\n";
    qotnt.showDigits();

    cout<<"\nremainder = multiplication % num1 :\n";
    rem.showDigits();

    BigInteger gcd(SIZEN);

    tstart={0,0};
    tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);

    gcdBigInteger(num1, num2, gcd);

    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nGCD took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));    
    
    
    cout<<"\ngcd (num1, num2) :\n";
    gcd.showDigits();

}

int main(int argc,  char** argv)
{

    
    srand ( time(NULL) );
    
    

    //call this function to see basic operation results of 1536 bits
    basicOperationOfBigInteger();
    
        int nSize;
    if(argc  < 2)
        nSize = SIZE;
    else
        nSize = atoi(argv[1]);

    nSize = nSize/32;

    cout<<"RSA Algorithm"<<endl;
    RSABigInteger rsa(WORD_COUNT);
    cout<<"Random Prime Number Generation"<<endl;

    struct timespec tstart={0,0}, tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    
    BigInteger primeNumberP(WORD_COUNT), primeNumberQ(WORD_COUNT);
    rsa.primeNumberGeneration(primeNumberP, nSize/2);
    cout<<"\nprimeNumber, p=\n";
    primeNumberP.showDigits();	
	
    rsa.primeNumberGeneration(primeNumberQ, nSize/2);
    cout<<"\nprimeNumber, q=\n";
    primeNumberQ.showDigits();

    rsa.init(primeNumberP,primeNumberQ);

    BigInteger rslt(WORD_COUNT);

    BigInteger msg(WORD_COUNT);
    RSABigInteger operationCheck(WORD_COUNT);
    operationCheck.randomNGeneration(msg, 4);
    cout<<"\nmsg  to be encrypt: "<<endl;
    msg.showDigits();

    rsa.encryption(msg,rslt);
    cout<<"\nEncrypted code:\n";
    rslt.showDigits();

    rsa.decryption(rslt,msg);
    cout<<"\nDecrypted message:\n";
    msg.showDigits();
    
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nKey Generation & Encryption-Decryption took %.2f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec)); 

    return 0;
}
