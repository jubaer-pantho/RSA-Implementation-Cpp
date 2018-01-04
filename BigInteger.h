#ifndef BIGINTEGER_H
#define BIGINTEGER_H


class BigInteger
{
    public:
        int nSize;
        unsigned int *digit;
        BigInteger(){}
		BigInteger(int n);
		BigInteger(const BigInteger &obj);
        ~BigInteger();


        void addBigInteger(BigInteger& a, BigInteger& b);
        void subBigInteger(BigInteger& a, BigInteger& b);
        void multBigInteger(BigInteger& a, BigInteger& b);
        void copyBigInteger(BigInteger& a, int index);
        void expoModNBigInteger(BigInteger& x, BigInteger& y, BigInteger& N, BigInteger& result);

        //div function is written separately from the class

        int msbBigInteger();
        void clearBigInteger();
        void showDigits();
		void setDigits(int index);
};

int Compare(BigInteger& first, BigInteger& second);
int divBigInteger(BigInteger& u, BigInteger& v, BigInteger& q, BigInteger& r);
void gcdBigInteger(BigInteger& a, BigInteger& b, BigInteger& result);

#endif // BIGINTEGER_H
