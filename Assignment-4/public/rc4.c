#include <string.h>

unsigned char S[256];
int i, j;

void rc4_init(const char *key, int keylen)
{
    for (i = 0; i < 256; i++)
        S[i] = i;
    j = 0;
    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keylen]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    i = j = 0;
}

void rc4_process(unsigned char *data, int len)
{
    for (int k = 0; k < len; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        unsigned char rnd = S[(S[i] + S[j]) % 256];
        data[k] ^= rnd;
    }
}

char hexchar(unsigned char b)
{
    return b < 10 ? '0' + b : 'a' + (b - 10);
}

void to_hex(const unsigned char *data, int len, char *out)
{
    for (int k = 0; k < len; k++)
    {
        out[2 * k] = hexchar((data[k] >> 4) & 0xF);
        out[2 * k + 1] = hexchar(data[k] & 0xF);
    }
    out[2 * len] = '\0';
}

char from_hex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return 0;
}

char *encrypt(const char *text, const char *key)
{
    static char out[2048];
    int len = strlen(text);
    unsigned char buf[1024];
    memcpy(buf, text, len);
    rc4_init(key, strlen(key));
    rc4_process(buf, len);
    to_hex(buf, len, out);
    return out;
}

char *decrypt(const char *hex, const char *key)
{
    static char out[1024];
    int len = strlen(hex) / 2;
    unsigned char buf[512];
    for (int k = 0; k < len; k++)
    {
        buf[k] = (from_hex(hex[2 * k]) << 4) | from_hex(hex[2 * k + 1]);
    }
    rc4_init(key, strlen(key));
    rc4_process(buf, len);
    memcpy(out, buf, len);
    out[len] = '\0';
    return out;
}
