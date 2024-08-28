#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptRowColumnTransposition(const string& text, int rows, int cols) {
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols && index < text.length(); ++c) {
            matrix[r][c] = text[index++];
        }
    }

    string encryptedText;
    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            if (matrix[r][c] != ' ') {
                encryptedText += matrix[r][c];
            }
        }
    }

    return encryptedText;
}

string decryptRowColumnTransposition(const string& text, int rows, int cols) {
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    int index = 0;
    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows && index < text.length(); ++r) {
            matrix[r][c] = text[index++];
        }
    }

    string decryptedText;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (matrix[r][c] != ' ') {
                decryptedText += matrix[r][c];
            }
        }
    }

    return decryptedText;
}

int main() {
    string plaintext = "GUINDY";
    int rows = 2;
    int cols = 3;

    string ciphertext = encryptRowColumnTransposition(plaintext, rows, cols);
    string decryptedText = decryptRowColumnTransposition(ciphertext, rows, cols);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
