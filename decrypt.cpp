#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <Windows.h>

#include "aes256.cpp"

#define BUFFER_SIZE 1024*1024

#ifdef __APPLE__
#define fseeko64 fseeko
#endif

int decrypt(char *ginput, char *gkey) {
    ByteArray key, dec;
    size_t file_len;
    FILE *input, *output;
    srand(time(0));
    size_t key_len = 0;
    char *goutput = (char*)"tmp";
    while (gkey[key_len])
        key.push_back(gkey[key_len++]);
    input = fopen(ginput, "rb");
    output = fopen(goutput, "wb");
    Aes256 aes(key);
    _fseeki64(input, 0, SEEK_END);
    file_len = ftell(input);
    _fseeki64(input, 0, SEEK_SET);
    aes.decrypt_start(file_len);
    while (!feof(input)) {
        unsigned char buffer[BUFFER_SIZE];
        size_t buffer_len;
        buffer_len = fread(buffer, 1, BUFFER_SIZE, input);
        if (buffer_len > 0) {
            dec.clear();
            aes.decrypt_continue(buffer, buffer_len, dec);
            fwrite(dec.data(), dec.size(), 1, output);
        }
    }
    dec.clear();
    aes.decrypt_end(dec);
    fwrite(dec.data(), dec.size(), 1, output);
    fclose(input);
    fclose(output);
    CopyFile(goutput, ginput, 0);
    return 0;
}

int main(int argc, char** argv) {
    return 0;
}