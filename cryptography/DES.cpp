#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

using namespace std;
 
string round_keys[16];
string pt;

string convertDecimalToBinary(int decimal, int length = 8) {
    return bitset<8>(decimal).to_string().substr(8 - length);
}

int convertBinaryToDecimal(string binary) {
    return stoi(binary, nullptr, 2);
}

string shift_left_once(string key_chunk) {
    return key_chunk.substr(1, 27) + key_chunk[0];
}

string shift_left_twice(string key_chunk) {
    for(int i = 0; i < 2; i++) {
        key_chunk = shift_left_once(key_chunk);
    }
    return key_chunk;
}

string xorStrings(string a, string b) {
    string result = "";
    for(int i = 0; i < b.size(); i++) {
        result += (a[i] != b[i]) ? "1" : "0";
    }
    return result;
}

void generate_keys(string key) {
    int pc1[56] = {
        57,49,41,33,25,17,9, 1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4
    };
    int pc2[48] = {
        14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,
        30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32
    };
    string perm_key = "";
    for(int i = 0; i < 56; i++) perm_key += key[pc1[i] - 1];
    string left = perm_key.substr(0, 28), right = perm_key.substr(28, 28);
    for(int i = 0; i < 16; i++) {
        if(i == 0 || i == 1 || i == 8 || i == 15) {
            left = shift_left_once(left);
            right = shift_left_once(right);
        } else {
            left = shift_left_twice(left);
            right = shift_left_twice(right);
        }
        string combined_key = left + right, round_key = "";
        for(int i = 0; i < 48; i++) round_key += combined_key[pc2[i] - 1];
        round_keys[i] = round_key;
    }
}

string DES() {
    int initial_permutation[64] = {
        58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
    };
    int expansion_table[48] = {
        32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1
    };
    int substition_boxes[8][4][16] = {
        {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
        {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
        {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
        {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}},
        {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}},
        {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}},
    };
    int per[32] = {
        16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
    };
    int inverse_permutation[64] = {
        40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
    };
    
    string permuted_pt = "";
    for(int i = 0; i < 64; i++) permuted_pt += pt[initial_permutation[i] - 1];
    string left = permuted_pt.substr(0, 32), right = permuted_pt.substr(32, 32);
    for(int i = 0; i < 16; i++) {
        string expanded_right = "";
        for(int j = 0; j < 48; j++) expanded_right += right[expansion_table[j] - 1];
        string xored = xorStrings(round_keys[i], expanded_right);
        string substituted = "";
        for(int j = 0; j < 8; j++) {
            int row = convertBinaryToDecimal(string(1, xored[j * 6]) + string(1, xored[j * 6 + 5]));
            int col = convertBinaryToDecimal(xored.substr(j * 6 + 1, 4));
            substituted += convertDecimalToBinary(substition_boxes[j][row][col]);
        }
        string permuted_substituted = "";
        for(int j = 0; j < 32; j++) permuted_substituted += substituted[per[j] - 1];
        string new_right = xorStrings(left, permuted_substituted);
        left = right;
        right = new_right;
    }
    string combined = right + left;
    string ciphertext = "";
    for(int i = 0; i < 64; i++) ciphertext += combined[inverse_permutation[i] - 1];
    return ciphertext;
}

string stringToBinary(string input) {
    string binary = "";
    for(char c : input) {
        binary += convertDecimalToBinary((int)c, 8);
    }
    return binary;
}

int main() {
    string key_str, plaintext_str;
    
    cout << "Enter 8-character key: ";
    cin >> key_str;
    cout << "Enter 8-character plaintext: ";
    cin >> plaintext_str;

    // Convert input strings to 64-bit binary
    string key = stringToBinary(key_str);
    pt = stringToBinary(plaintext_str);

    // Generate round keys
    generate_keys(key);

    // Perform DES encryption
    string ciphertext = DES();

    // Output the ciphertext in binary
    cout << "Ciphertext (binary): " << ciphertext << endl;

    return 0;
}
