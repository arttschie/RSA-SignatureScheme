GOST R 34.11-2012 hash function with 512/256 bit digest
=======================================================

About
-----
This is non-portable implementation of the GOST R 34.11-2012 hash function.
The standard for this hash function developed by the Center for
Information Protection and Special Communications of the Federal
Security Service of the Russian Federation with participation of the
Open joint-stock company "Information Technologies and Communication
Systems" (InfoTeCS JSC).

Author
------
Alexey Degtyarev <alexey@renatasystems.org>

Edited to be compiled both as C and C++ by A. Fionov
MMX and SSE extentions excluded.

GOST34112012Context

    This is the hash context.  There should be one GOST34112012Context
    for each object to be hashed.


void
GOST34112012Init(GOST34112012Context *CTX, 
    const unsigned int digest_size);

    Return initialized GOST34112012Context of specified hash size
    (digest_size) on allocated memory block pointed by CTX.  Digest size
    can be either 512 or 256. 


void
GOST34112012Update(GOST34112012Context *CTX, const unsigned char *data,
    size_t len);

    Hash some data in memory of "len" bytes size.
    

void
GOST34112012Final(GOST34112012Context *CTX, unsigned char *digest);

    Finalizes hashing process and set GOST R 34.11-2012 hash in
    memory block pointed by "digest".


For example of usage see test.cpp

Command to compile:
g++ -O2 test.cpp gost3411-2012-core.c

