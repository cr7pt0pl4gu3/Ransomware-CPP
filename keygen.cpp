#include <string>
#include <cstring>
#include <ctime>

using namespace std;

// Generating the key
string keygen(int max_length=16) {
    string possible_characters = "!abcdefghijklmnopqrstuvwxyz";
    int str_len = 26;
    srand(time(nullptr));
    string ret;
    while (max_length != 0) {
        --max_length;
        int r = rand() % str_len + 1;
        ret.push_back(possible_characters[r]);
    }
    return ret;
}

// Text key to number key
string ttn(char* t) {
    string o;
    char* combs[26][2] = {{(char*)"10",(char*)"a"},
                          {(char*)"11",(char*)"b"},
                          {(char*)"12",(char*)"c"},
                          {(char*)"13",(char*)"d"},
                          {(char*)"14",(char*)"e"},
                          {(char*)"15",(char*)"f"},
                          {(char*)"16",(char*)"g"},
                          {(char*)"17",(char*)"h"},
                          {(char*)"18",(char*)"i"},
                          {(char*)"19",(char*)"j"},
                          {(char*)"20",(char*)"k"},
                          {(char*)"21",(char*)"l"},
                          {(char*)"22",(char*)"m"},
                          {(char*)"23",(char*)"n"},
                          {(char*)"24",(char*)"o"},
                          {(char*)"25",(char*)"p"},
                          {(char*)"26",(char*)"q"},
                          {(char*)"27",(char*)"r"},
                          {(char*)"28",(char*)"s"},
                          {(char*)"29",(char*)"t"},
                          {(char*)"30",(char*)"u"},
                          {(char*)"31",(char*)"v"},
                          {(char*)"32",(char*)"w"},
                          {(char*)"33",(char*)"x"},
                          {(char*)"34",(char*)"y"},
                          {(char*)"35",(char*)"z"}};
    for(int i = 0; i < strlen(t); i++)
        for(auto & comb : combs)
            if(t[i] == *comb[1])
                o += comb[0];
    return o;
}

// Number key to text key
string ntt(char* t) {
    string o;
    char* combs[26][2] = {{(char*)"10",(char*)"a"},
                          {(char*)"11",(char*)"b"},
                          {(char*)"12",(char*)"c"},
                          {(char*)"13",(char*)"d"},
                          {(char*)"14",(char*)"e"},
                          {(char*)"15",(char*)"f"},
                          {(char*)"16",(char*)"g"},
                          {(char*)"17",(char*)"h"},
                          {(char*)"18",(char*)"i"},
                          {(char*)"19",(char*)"j"},
                          {(char*)"20",(char*)"k"},
                          {(char*)"21",(char*)"l"},
                          {(char*)"22",(char*)"m"},
                          {(char*)"23",(char*)"n"},
                          {(char*)"24",(char*)"o"},
                          {(char*)"25",(char*)"p"},
                          {(char*)"26",(char*)"q"},
                          {(char*)"27",(char*)"r"},
                          {(char*)"28",(char*)"s"},
                          {(char*)"29",(char*)"t"},
                          {(char*)"30",(char*)"u"},
                          {(char*)"31",(char*)"v"},
                          {(char*)"32",(char*)"w"},
                          {(char*)"33",(char*)"x"},
                          {(char*)"34",(char*)"y"},
                          {(char*)"35",(char*)"z"}};
    for(int i = 0; i < strlen(t); i+=2) {
        char c[3] = {t[i], t[i + 1], 0};
        for(auto & comb : combs)
            if(comb[0][0] == c[0] && comb[0][1] == c[1])
                o += comb[1];
    }
    return o;
}

//int main() {
//    string key = keygen(16);
//    cout << "Key -> " << key << "\n";
//
//    char *key_char = new char[key.length() + 1];
//    strcpy(key_char, key.c_str());
//    key = ttn(key_char);
//
//    cout << "Number key -> " << key << "\n";
//
//    char *key_num = new char[key.length() + 1];
//    strcpy(key_num, key.c_str());
//    key = ntt(key_num);
//
//    cout << "Text key -> " << key << "\n";
//
//    return 0;
//}