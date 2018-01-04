# RSA-Implementation-C
(Key Generation, Encryption, Decryption, 2^32 base arithmatic operations)

C++ implementation of RSA algortihm for BigInteger numbers. 

In this project, a C++ implementation has been provided to perform RSA encryption and
decryption for up to 3072 bits of N value. The project also includes random public and private key
generation for RSA algorithm. In order to achieve the desired results, the design includes methods
for basic operations of N bit numbers. The performance of these methods were compared with a
Java BigInteger implementation on the same workstation. It was found that the implemented
methods in this project provides better latency compared to the Java BigInteger class.

Description of the Project files:
The project includes two class. The BigInteger class and the RSABigInteger class.
The BigInteger class holds the BigInteger numbers and their size as member variables. The large
integer numbers are stored as 232 bit base numbers in an array of unsigned integers.
The class also includes a number of methods to perform basic operations of these large numbers.
The implemented methods of this class are given below:

1. addBigInteger- This method takes two BigInteger objects as input and produces the summation
as the result. The algorithm used in this method is described in the book of Donald E. Knuth. [2]

2. subBigInteger- This method takes two BigInteger objects as input and produces the subtraction
as the result. The algorithm used in this method is described in the book of Donald E. Knuth. [2]

3. multBigInteger- This method takes two BigInteger objects as input and produces the
multiplication as the result. The algorithm used in this method is described in the book of Donald
E. Knuth. [2]

4. msbBigInteger: This method gives the bit number of the non-zero MSB of the object. Here the
indexing starts from zero.

5. expoModNBigInteger: This method takes four BigInteger objects as input and produces
param1param2 % param3 = result
The algorithm used in this method is explained in the textbook of Dasgupta [3].

6. clearBigInteger: This method clears value of all the digits in the 32-bit unsigned int array.
Miscellaneous methods: showDigits, setDigits, setSize, copyBigInteger
Methods implemented separately from the class:

1. normalize- This method is used to do normalization of step one in the division of BigInteger
according to Knuth. [2]

2. Compare- This method takes two BigInteger objects as input and perform comparison. It
returns 1 if the first BigInteger is bigger and returns minus one if the second BigInteger is larger.
It returns zero if both are the same.

3. divBigInteger- This method takes four BigInteger objects as input and divide the first one with
the second one. The result is saved in the third parameter and the remainder is saved in the fourth
parameter.

4. gcdBigInteger- This method takes three BigInteger objects as input and produces the GCD of
the first two on the third parameter.
The second class in the project is the RSABigInteger class. This class is used to do generate public
and private keys for the RSA algorithms.

The key method includes in this project:

- randomNGeneration- This method generates a random BigInteger of size n given as a
parameter to this.

- primeNumberGeneration- This method generates a prime number of given length. The
algorithm is to generate a random number at each iteration and check with the Fermat’s
little theorem whether it is prime or not.

- CalculateD- This method calculates the d for the RSA algorithm as described in the
introduction section. It takes three BigInteger as input (e, phi, d) and calculate d.

- Init- This method initializes the RSA key-generation by calling a set of methods within the
class.

- eGeneration- This method generates the value of e as described in the introduction.

- encryption- This method takes two BigInteger objects as input and produces encrypted
data with the RSA public key generated in the Init method.

- decryption- This method takes two BigInteger objects as input and produces decrypts the
actual message with the RSA private key corresponding to the public key pair.


How to run the code
The project folder contains three subfolders.
/src /bin /obj
The source files are in the /src folder. It contains a script file build.bash. Simply running this file
with ./build.bash command will run the code. It will generate a random set of private public key
and encrypt a random generated message and decrypt it again to show you the original number.
The executable will be generated in the /bin folder. The executable will take an input N where N
represents the number of bits of the Algorithm. i.e. 1920. If no input is given it will assume the
value of N to be 960 bits. The input value can also be changed from the script by changing the last
line of the build.bash file.
./obj <desired value of N>

References:
[1] RSA Algorithm Example
https://www.cs.utexas.edu/~mitra/honors/soln.html
[2] Donald E. Knuth The Art Of Computer Programming 4.3.1 pages 266-273
[3] Sanjoy Dasgupta Algorithms
