# RSA Signature Scheme
Implementation of RSA digital signature scheme presented.

* Progaming language: C; 
* Prefered IDE: DEV-C++ 5.11; 
* Prefered compiler: TDM-GCC 4.9.2 32-bit Release.

For operations on large numbers GMP library is used. <br/>
> To use GMP library copy libgmp.a libgmp.la to *Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib32*<br/>
> Copy gmp.h rdtsc.h to *Dev-Cpp\MinGW64\x86_64-w64-mingw32\include*

As hash function GOST-R 34.11-2012 is used.
> To use GOST-R 34.11-2012 add all files from directory to your project
