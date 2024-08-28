#include<iostream>
#include <string>
using namespace std;

int main(){
	string letter;
	int k=0;
	int lettermatrix[3][1];
	
	cout<<"enter the letter=";
	getline(cin,letter);
	
	for(int i=0;i<3;i++){
		for(int j=0;j<1;j++){
			lettermatrix[i][j]=(letter[k])%65;
            k++;
		}
	}
	cout<<"letter to number=";
	 for(int i=0;i<3;i++)
    {
        for ( int j = 0; j<1; j++)
        {
            cout<<lettermatrix[i][j];
        }
    } 
	string key;
	k=0;
	int keymatrix[3][3];
    cout<<"\nEnter the key =";
    getline(cin,key);
 
    for(int i=0;i<3;i++)
    {
        for ( int j = 0; j<3; j++)
        {
            keymatrix[i][j]=(key[k])%65;
            k++;
        }
    }
     for(int i=0;i<3;i++)
    {
        for (int  j = 0; j<3; j++)
        {
            cout<<keymatrix[i][j];
        }
    }
    string choice;
    cout<<"enter your choice \n1. encryption\n2. decryption";
    cin>>choice;
    
    if(choice==1){
    int sum;
    int multmatrix[3][1];
    
    int result[3][1];
    
    for (int i = 0; i < 3; i++) {
        sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += keymatrix[i][j] * lettermatrix[j][0];
        }
        result[i][0] = sum % 26;
    }
    
    for(int i=0;i<3;i++){
    	for(int j=0;j<1;j++){
    		cout<<result[i][j];
		}
	}
}

	string ans[3][1];
	char ch;
	for(int i=0;i<3;i++){
		for(int j=0;j<1;j++){
			ans[i][j]=result[i][j]+'A';
		}
	}
   
}


