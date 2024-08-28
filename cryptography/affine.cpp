#include <iostream>
#include <string>

using namespace std;

const int a = 5; 
const int b = 8; 
const int m = 26; 

char encryptChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return char(((a * (ch - 'A') + b) % m) + 'A');
    }
    return ch;
}

char decryptChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        int a_inv = 21; 
        return char(((a_inv * (ch - 'A' - b + m)) % m + m) % m + 'A');
    }
    return ch;
}

int main() {
    string plaintext = "AFFINECIPHER";
    string ciphertext = "";
    string decryptedText = "";

    for (char ch : plaintext) {
        ciphertext += encryptChar(ch);
    }

    for (char ch : ciphertext) {
        decryptedText += decryptChar(ch);
    }

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
