#include "BigInteger.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <malloc.h>

#define max(x, y) ((x) > (y) ? (x) : (y))


using namespace std;


BigInteger::BigInteger(int n)
{
	nSize = n;
	digit = new unsigned int[n];
	for (int i = 0; i < nSize;i++)
	{
		digit[i] = 0;
	}

}

BigInteger::BigInteger(const BigInteger &obj)
{
    cout << "Using copy constructor";
 	nSize = obj.nSize;
	digit = new unsigned int[nSize];
	for (int i = 0; i < nSize; i++)
	{
		digit[i] = obj.digit[i];
	}

}

BigInteger::~BigInteger()
{
    delete [] digit;
}

void BigInteger::showDigits()
{
    int nonZeroDigitFlag =0;
    for(int i=(nSize-1);i>=0; i--)
    {
        if(digit[i]!=0)
        {
            nonZeroDigitFlag=1;
        }
        if(nonZeroDigitFlag==1)
        {
            printf("%u ",digit[i]);
        }
    }

    if(nonZeroDigitFlag ==0)
    {
        printf("0");
    }
    cout << endl;
}

void BigInteger::setDigits(int index)
{
    if(index == 0)
    {
        digit[1] = 1; //4294967295;
        digit[0] = 1;
    }
    else if(index ==1)
     {
         digit[1]= 0;
         digit[0] = 2 ;//429496725;
     }

}

void BigInteger::addBigInteger(BigInteger& a, BigInteger& b)
{
    unsigned long long int base = 4294967296;
    unsigned int k=0;
    for(int i=0;i<nSize;i++)
    {
        unsigned long long int sum = 0;
        sum = (unsigned long long int) a.digit[i] + (unsigned long long int) b.digit[i] + k;
        digit[i] = (unsigned int) (sum % base);
        k = (unsigned int) (sum / base);
    }
}

void BigInteger::subBigInteger(BigInteger& a, BigInteger& b)
{
    long long int base = 4294967296;
    int k=0;
    for(int i=0;i<nSize;i++)
    {
        unsigned long long int sum = 0;
        sum = (long long int) a.digit[i] - (long long int) b.digit[i] + k;
        digit[i] = (unsigned int) (sum % base);
        k = sum / base;
    }
}

void BigInteger::multBigInteger(BigInteger& a, BigInteger& b)
{
    for(int k=0;k<nSize;k++)
    {
        digit[k] =0;
    }
    
    int smallN = a.nSize/2;
    unsigned long long int base = 4294967296;

    for(int j=0; j<smallN; j++)
    {
       if(b.digit[j] ==0)
           {
               digit[j+smallN] =0;
           }
       else
        {
          unsigned int k=0;

          for(int i=0; i<smallN; i++)
            {
                unsigned long long int t = ((unsigned long long int) a.digit[i])*b.digit[j] + (unsigned long long int) digit[i+j]+k;
                digit[i+j] = t % base;
                k =  t/base;


            }
        }
    }

}

void BigInteger::copyBigInteger(BigInteger& a, int index)
{
    for(int i=0; i<nSize;i++)
	{
		if(i>=index && (i-index)<a.nSize)
		{
				digit[i] = a.digit[i-index];
		}
		else
		{
				digit[i] =0;
		}
	}
}

int Compare(BigInteger& first, BigInteger& second)
{
 int nResult=0;

 for(int i= (first.nSize-1); i>=0;i--)
 {
    if(first.digit[i]!=second.digit[i])
    {
        if(first.digit[i]>second.digit[i])
        {
            nResult = 1;
            break;
        }
        else if(first.digit[i]<second.digit[i])
        {
            nResult = -1;
            break;
        }
    }
 }

	return nResult;


}

int BigInteger::msbBigInteger()
{
    int msb=0;

    for(int i=(nSize-1);i>=0;i--)
    {
        if(digit[i]!=0)
        {
            msb=i;
            break;
        }
    }

    return msb;
}

void BigInteger::clearBigInteger()
{
    for(int i=(nSize-1);i>=0;i--)
        digit[i]=0;
}



long long int normalize(unsigned long long int x)
{

   long long int n;

   if (x == 0) return(32);
   n = 0;
   if (x <= 0x00000000FFFFFFFF) {n = n +32; x = x <<32;}
   if (x <= 0x0000FFFFFFFFFFFF) {n = n +16; x = x <<16;}
   if (x <= 0x00FFFFFFFFFFFFFF) {n = n + 8; x = x << 8;}
   if (x <= 0x0FFFFFFFFFFFFFFF) {n = n + 4; x = x << 4;}
   if (x <= 0x3FFFFFFFFFFFFFFF) {n = n + 2; x = x << 2;}
   if (x <= 0x7FFFFFFFFFFFFFFF) {n = n + 1;}
   return n;
}

int divBigInteger(BigInteger& u, BigInteger& v, BigInteger& q, BigInteger& r)
{
    int flagCompare = Compare(u,v);
    if(flagCompare==-1)
    {
        q.clearBigInteger();
        r.copyBigInteger(u,0);
    }
    else if(flagCompare ==0)
    {
        q.clearBigInteger();
        r.clearBigInteger();
        q.digit[0]=1;
    }
    else
    {

   int m = u.msbBigInteger() +1;
   int n = v.msbBigInteger() +1;
   unsigned long long int b = 4294967296; // Number base (32 bits).

   // Normalized form of u, v.
   unsigned int *unorm = new unsigned int[2*(m + 1)];
   unsigned int *vnorm = new unsigned int[2*n];
   // Estimated quotient digit.
   unsigned long long int qhat;
   unsigned long long int rhat;
   // Product of two digits.
   unsigned long long int p;
   long long int s, i, j, t, k;

   if (m < n || n <= 0 || v.digit[n-1] == 0)
      return 1;              // Return if invalid param.

   if (n == 1) {                        // Take care of
      k = 0;                            // the case of a
      for (j = m - 1; j >= 0; j--) {    // single-digit
         q.digit[j] = (k*b + u.digit[j])/v.digit[0];      // divisor here.
         k = (k*b + u.digit[j]) - q.digit[j]*v.digit[0];
      }
      r.digit[0] = k;
      return 0;
   }

   s = normalize(v.digit[n-1]) - 32;        // 0 <= s <= 15.
   //vnorm = (unsigned int *)malloc(2*n);
   for (i = n - 1; i > 0; i--)
   vnorm[i] = (v.digit[i] << s) | (v.digit[i-1] >> (32-s));
   vnorm[0] = v.digit[0] << s;

   //unorm = (unsigned int *)malloc(2*(m + 1));
   unorm[m] = u.digit[m-1] >> (32-s);
   for (i = m - 1; i > 0; i--)
      unorm[i] = (u.digit[i] << s) | (u.digit[i-1] >> (32-s));
   unorm[0] = u.digit[0] << s;

   //step D2, D3 loop
   for (j = m - n; j >= 0; j--) {
      qhat = (unorm[j+n]*b + unorm[j+n-1])/vnorm[n-1];
      rhat = (unorm[j+n]*b + unorm[j+n-1]) - qhat*vnorm[n-1];
again:
      if (qhat >= b || qhat*vnorm[n-2] > b*rhat + unorm[j+n-2])
      { qhat = qhat - 1;
        rhat = rhat + vnorm[n-1];
        if (rhat < b) goto again;
      }

      // D4 Multiply and subtract.
      k = 0;
      for (i = 0; i < n; i++) {
         p = qhat*vnorm[i];
         t = unorm[i+j] - k - (p & 0xFFFFFFFF);
         unorm[i+j] = t;
         k = (p >> 32) - (t >> 32);
      }
      t = unorm[j+n] - k;
      unorm[j+n] = t;

      q.digit[j] = qhat;              // Store quotient digit.
      if (t < 0) {              // If we subtracted too
         q.digit[j] = q.digit[j] - 1;       // much, add back.
         k = 0;
         for (i = 0; i < n; i++) {
            t = unorm[i+j] + vnorm[i] + k;
            unorm[i+j] = t;
            k = t >> 32;
         }
         unorm[j+n] = unorm[j+n] + k;
      }
   } // End j.

      for (i = 0; i < n; i++)
         r.digit[i] = (unorm[i] >> s) | (unorm[i+1] << (32-s));

    delete[] unorm;
    delete[] vnorm;
    }
   return 0;
}

void gcdBigInteger(BigInteger& a, BigInteger& b, BigInteger& result)
{
    BigInteger tmpa(a.nSize);
    BigInteger tmpb(a.nSize);

    tmpa.copyBigInteger(a,0);
    tmpb.copyBigInteger(b,0);

    if(tmpb.msbBigInteger()==0 && tmpb.digit[0]==0)
    {
        for(int i=0;i<result.nSize;i++)
        {
            result.digit[i] = tmpa.digit[i];
        }
    }
    else
    {
        BigInteger q(a.nSize);
        BigInteger r(a.nSize);
        divBigInteger(tmpa, tmpb, q, r);
        gcdBigInteger(tmpb, r, result);
    }
}


void BigInteger::expoModNBigInteger(BigInteger& x, BigInteger& y, BigInteger& N, BigInteger& result)
{
	if (y.msbBigInteger() == 0 && y.digit[0] ==0)
	{
		result.digit[0] = 1;
		for (int i = 1; i < result.nSize; i++)
		{
			result.digit[i] = 0;
		}
	}
	else
	{
		BigInteger temp(nSize);
		BigInteger reminder(nSize);

		BigInteger value2(nSize);
		value2.digit[0]=2;
		divBigInteger(y,value2, *this, reminder);

		temp.copyBigInteger(*this, 0);
		expoModNBigInteger(x, temp,N, result);

		multBigInteger(result, result);

		temp.copyBigInteger(*this, 0);

		if (y.digit[0] % 2 != 0)
		{
			multBigInteger(temp, x);
			temp.copyBigInteger(*this, 0);
		}
		BigInteger q(nSize), r(nSize);
		divBigInteger(temp, N,q,r);
		result.copyBigInteger(r,0);
	}

	return;
}

void BigInteger::setSize(int n)
{
	nSize = n;
	digit = new unsigned int[n];
	for (int i = 0; i < nSize;i++)
	{
		digit[i] = 0;
	}
}

