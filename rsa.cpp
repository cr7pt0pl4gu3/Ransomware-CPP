#include <iostream>
#include <cmath>
#include <cstring>
#include "keygen.cpp"

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

bool isPrime(unsigned long long prime)
{
    unsigned long long i, j;

    j = (unsigned long long)sqrt((long double)prime);

    for (i = 2; i <= j; i++)
    {
        if (prime % i == 0)
        {
            return false;
        }
    }

    return true;
}

unsigned long long calculate_d(unsigned long long e, unsigned long long t) {
    unsigned long long d = 2;
    while (true) {
        if ((d * e) % t == 1) {
            break;
        }
        ++d;
    }
    return d;
}

unsigned long long calculate_e(unsigned long long t) {
    unsigned long long e = 2;
    while (true) {
        if (t % e != 0) {
            if (isPrime(e)) {
                break;
            }
        }
        ++e;
    }
    return e;
}

string encrypt(const string &unencrypted, unsigned long long e, unsigned long long n) {
    string result;
    for (auto i : unencrypted) {
        unsigned long long truncate = ipow(i - '0', e);
        result.append(to_string(truncate % n));
        result.append(":");
    }
    return result;
}

string decrypt(const string &encrypted, unsigned long long d, unsigned long long n) {
    string result;
    string buffer;
    for (int i = 0; i < encrypted.size(); i++) {
        if (encrypted[i] != ':') {
            buffer.append(to_string(encrypted[i] - '0'));
        }
        else {
            result.append(to_string((unsigned long long) ipow(stoi(buffer), d) % n));
            buffer = "";
        }
        }
    return result;
}

int main() {
    unsigned long long p = 2;
    unsigned long long q = 11;
    unsigned long long n = p * q;
    unsigned long long t = (p - 1) * (q - 1);
    unsigned long long e = calculate_e(t);
    unsigned long long d = calculate_d(e, t);
    string unencrypted = "34222912143330352214312512212210";
    //string encrypted = encrypt(unencrypted, e, n);
    string encrypted;
    cout << "Enter encrypted string -> ";
    cin >> encrypted;

    string decrypted = decrypt(encrypted, d, n);
    char *decrypted_num = new char[decrypted.length() + 1];
    strcpy(decrypted_num, decrypted.c_str());
    decrypted = ntt(decrypted_num);

    cout << "Text key -> " << decrypted << "\n";

    ///cout << "RSA Public Key -> " << "e:" << e << " n:" << n << "\n";
    //cout << "RSA Private Key -> " << "d:" << d << " n:" << n << "\n";
    cout << "Encrypted number -> " << encrypted << "\n";
    cout << "Decrypted number -> " << decrypted << "\n";
    return 0;
}