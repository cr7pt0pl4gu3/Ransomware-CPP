#include <iostream>

using namespace std;

unsigned long long int ipow(unsigned long long int base, unsigned long long int exp)
{
    unsigned long long int result = 1ULL;
    while(exp)
    {
        if (exp & 1)
        {
            result *= (unsigned long long int)base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}

string encrypt_rsa(const string &unencrypted, unsigned long long e=3, unsigned long long n=22) {
    string result;
    for (auto i : unencrypted) {
        unsigned long long truncate = ipow(i - '0', e);
        result.append(to_string(truncate % n));
        result.append(":");
    }
    return result;
}
