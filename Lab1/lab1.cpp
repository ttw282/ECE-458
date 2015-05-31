//t7wei, 20441863

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string convertedkey;

void key(string key){
	for(int i = 0; i < key.length(); i++)
    {
		convertedkey += key[i] + 'A' - 'a';
    }
}

string encrypt(string text){
	string result;
	int j = 0;
	
	for(int i = 0; i < text.length(); i++)
	{
		char ch = text[i];
		ch += 'A' - 'a';
		result += (ch + convertedkey[j] - 2*'A') % 26 + 'a'; 
		j = (j + 1) % convertedkey.length();
	}
 
	return result;
}
 
string decrypt(string text){
	string result;
	int j = 0;
	
	for(int i = 0; i < text.length(); i++)
	{
		char ch = text[i];
		ch += 'A' - 'a';
		result += (ch - convertedkey[j] + 26) % 26 + 'a'; 
		j = (j + 1) % convertedkey.length();
	}
 
	return result;
}

void find_frequency(string s, double count[]) {
	for(int i = 0; i < s.length(); i++){
		if(s[i] >= 'a' && s[i] <= 'z'){
			count[s[i]-'a']++;
		}
	}
}

int main(int argc) {
	
	string ciphertext;
	string plaintext;
	key("vkshgye");
	int N = 7;
	int startpos = 0;
	string subset;
	int c;
	double count[26] = {0};
	
	ifstream input("ciphertext.txt");
	if(input.is_open()){
		while(getline(input, ciphertext)){
			plaintext = decrypt(ciphertext);
			
			for(int i = startpos; i < ciphertext.length(); i+=N){
				subset += ciphertext[i];
			}
		}
		
		find_frequency(subset, count);
		printf("subset of chars starting from position %d, every %d letter is: %s \n", startpos, N, subset.c_str());
		printf("Character Count Frequency\n");
		for(int c = 0; c < 26; c++){
			printf("%c \t %.0f \t %.2f %\n", c+'a', count[c], count[c]*100/subset.length());
		}
		
		input.close();
	}
	else {
		printf("unable to open file\n");
	}
	
	ofstream output;
	output.open("decrypted.txt");
	output << plaintext;
	output.close();
	
	ifstream input1("decrypted.txt");
	if(input1.is_open()){
		while(getline(input1, plaintext)){
			ciphertext = encrypt(plaintext);
		}
		input1.close();
	}
	else {
		printf("unable to open file\n");
	}
	
	ofstream output1;
	output1.open("encrypted.txt");
	output1 << ciphertext;
	output1.close();
	
	return 0;
};
