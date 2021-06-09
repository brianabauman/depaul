/* calculateD.c */
#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a)
{
    /* Use BN_bn2hex(a) for hex string
     * Use BN_bn2dec(a) for decimal string */
    char * number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main ()
{
    BN_CTX* ctx = BN_CTX_new();
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *n = BN_new();
    BIGNUM *z = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *d = BN_new();

    // initialize values
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0D88C3");

    // n = p * q
    BN_mul(n, p, q, ctx);
    printBN("n = p * q = ", n);

    // z = (p - 1) * (q - 1)
    BIGNUM *one = BN_new();
    BN_dec2bn(&one, "1");
    BIGNUM *pMinusOne = BN_new();
    BIGNUM *qMinusOne = BN_new();
    BN_sub(pMinusOne, p, one);
    BN_sub(qMinusOne, q, one);
    BN_mul(z, pMinusOne, qMinusOne, ctx);
    printBN("z = (p - 1) * (q - 1) = ", z);

    // (e * d) mod n = 1
    BN_mod_inverse(d, e, n, ctx);
    printBN("(e * d) mod n = 1, d = ", d);

    return 0;
}
