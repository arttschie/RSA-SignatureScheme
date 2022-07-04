// generate random 1024-bit prime
#include <gmp.h>
#include <time.h>

int main ()
  {
  mpz_t p;
  mpz_init (p);
  gmp_randstate_t rs;
  gmp_randinit_mt (rs), gmp_randseed_ui (rs, time (0));
  mpz_urandomb (p, rs, 1024);
  mpz_nextprime (p, p);
  gmp_printf ("p = %#0Zx\n");
  return 0;
  }

