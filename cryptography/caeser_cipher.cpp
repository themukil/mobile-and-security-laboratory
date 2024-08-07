#include <iostream>
using namespace std;

string encrypt(string t, int k){
    string new_string = "";

    for(int i=0; i<t.length(); i++){
        if(isupper(t[i])){
            new_string += char((int(t[i]) + k - 65) % 26 + 65);
        } else if(islower(t[i])){
            new_string += char((int(t[i]) + k - 97) % 26 + 97);
        } else{
            new_string += t[i];
        }
    }
    return new_string;
}

string decrypt(string t, int k){
    string new_string = "";

    for(int i=0; i<t.length(); i++){
        if(isupper(t[i])){
            new_string += char((int(t[i]) - k - 65) % 26 + 65);
        } else if(islower(t[i])){
            new_string += char((int(t[i]) - k - 97) % 26 + 97);
        } else{
            new_string += t[i];
        }
    }
    return new_string;
}

int main(){
    string plainText = "Hello world";
    int key;

    cout<<"Enter the key: ";
    cin>>key;

    string result = encrypt(plainText, key);
    cout<<"Encrypted text: "<<result<<endl;
    string result1 = decrypt(result, key);
    cout<<"Decrypted text: "<<result1;
}
