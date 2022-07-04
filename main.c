#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "gost3411-2012-core.h"

GOST34112012Context CTX;

int main() {
	gmp_randstate_t rs; // Generation algorithm declaration
	gmp_randinit_mt (rs), gmp_randseed_ui (rs, time(0)); // Algorithm initialization and seed definition 
	mpz_t f, p, q, n, e, r, d, h, c, m; // Variables of type mpz_t declaration 
	mpz_inits (f, p, q, n, e, r, d, h, c, m, 0);
	int iter = 0;
	
	while (mpz_cmp_ui(f, 1) != 0) {
		mpz_urandomb (p, rs, 1024); // Generating fist random prime 1024 bit number
		mpz_nextprime (p, p); 
		mpz_urandomb (q, rs, 1024); // Generating second random prime 1024 bit number
		mpz_nextprime (q, q);
		mpz_mul (n, p, q); // Product of prime numbers
		mpz_sub_ui (p, p, 1); // p = p - 1
		mpz_sub_ui (q, q, 1); // q = q - 1
		mpz_mul (e, p, q); // Calculation of the Euler function
		mpz_set_ui (r, 3); // Assigning an open exponent to an integer 3
		mpz_gcd (f, e, r); // Calculation of the values of the Euler function and 3
		iter += 1;
	}
	
	printf("Generate the first 1024-bit prime number:\n");
	gmp_printf("%s = %#0Zx\n", "p", p);
	printf("Generate the second 1024-bit prime number:\n");
	gmp_printf("%s = %#0Zx\n", "q", q);
	printf("Multiplication product of p and q:\n");
	gmp_printf("%s = %#0Zx\n", "n", n);
	printf("Euler's totient function is:\n");
	gmp_printf("%s = (p-1)*(q-1) = %#0Zx\n", "e", e);
	printf("Public exp is: 3\n");
	printf("The greatest common factor of e and 3 is:");
	gmp_printf ("%s %Zd\n", "", f);
	mpz_invert (d, r, e); // Multiplicative inversion calculation
	printf("Secret exp is:\n");
	gmp_printf("%s = %#0Zx\n", "d", d);
	printf("Public key {r,n}, and secret key {d,n}, have been successfully generated!\n");
	
	unsigned char H [32];
	unsigned char buf [512];
	char str [65];
	int l, i;
	FILE *fp = fopen("text.txt", "rb");
	GOST34112012Init(&CTX, 256);
	
	do {
		l = fread(buf, 1, 512, fp),
		GOST34112012Update (&CTX, buf, l);
	} while (! feof(fp));
	
	GOST34112012Final(&CTX, H); // Ends hash function generation and writes to 'H'
	
	for (i=0; i<32; i++) sprintf(str+(2*i), "%02X", H[i]);
	
	printf("Generating hash value...\n");
	printf("Hash value is H = %s\n", str);
	mpz_set_str(h, str, 16);
	gmp_printf("%s = %#0Zx\n", "h", h);
	printf("Generating signature...\n");
	mpz_powm(c, h, d, n); // Signature generation
	gmp_printf("Segnature is:\n%s = %#0Zx\n", "c", c);
	printf("Decryption process...\n");
	mpz_powm_ui(m, c, 3, n); // Calculating hash value to signature
	printf("Decrypted signature is:\n");
	gmp_printf("%s = %#0Zx\n", "m", m);
	
	if (mpz_cmp(h, m) != 0) { // Signature verifying 
		printf("Hash is not equal to decrypted signature! The message is wrong!\n");
		getch();
		return 0;
	}
	
	printf("Decrypted signature is equal to hash!\n");
	getch();
	
	return 0;
}
