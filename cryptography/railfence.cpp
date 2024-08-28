#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptRailFence(const string& text, int key) {
    vector<string> rail(key);
    int direction = 1; 
    int row = 0;

    for (char ch : text) {
        rail[row] += ch;
        row += direction;
        if (row == 0 || row == key - 1) {
            direction *= -1;
        }
    }

    string cipherText;
    for (const string& r : rail) {
        cipherText += r;
    }
    return cipherText;
}

string decryptRailFence(const string& cipherText, int key) {
    vector<string> rail(key);
    vector<vector<bool>> pattern(key, vector<bool>(cipherText.length(), false));
    int direction = 1; 
    int row = 0;

    for (int i = 0; i < cipherText.length(); i++) {
        pattern[row][i] = true;
        row += direction;
        if (row == 0 || row == key - 1) {
            direction *= -1;
        }
    }

    int index = 0;
    for (int r = 0; r < key; r++) {
        for (int c = 0; c < cipherText.length(); c++) {
            if (pattern[r][c] && index < cipherText.length()) {
                rail[r] += cipherText[index++];
            }
        }
    }

    string decryptedText;
    row = 0;
    direction = 1;
    for (int i = 0; i < cipherText.length(); i++) {
        decryptedText += rail[row][0];
        rail[row].erase(0, 1);
        row += direction;
        if (row == 0 || row == key - 1) {
            direction *= -1;
        }
    }

    return decryptedText;
}

int main() {
    string plaintext = "RAIL_FENCE";
    int key = 3;

    string ciphertext = encryptRailFence(plaintext, key);
    string decryptedText = decryptRailFence(ciphertext, key);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
