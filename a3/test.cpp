#include <iostream>
#include <string.h> 
#include <sstream>
#include <vector>

using namespace std; 

typedef struct HashTable HashTable;

const int tableSize = 26;

struct HashTable
{
    string key;
    string data;
    string state;
} 

table[tableSize];

//create an initial table that has all elements set to never used
void emptyTable() {
    for (int i = 0; i < tableSize; i++){
        table[i].state = "Never Used";
    }
}

int findIndex (string key){
    int length = key.length();
    int index = key[length - 1] - 'a';
    return index; 
}

bool search(string wordReturn){

    string key = wordReturn[0];

    int curr = findIndex(key);

    if (table[curr].state == "Never Used"){
        return false; 
    }

    else if (table[curr].state == "Occupied" && table[curr].data == data) {
        return true;
    }

    else if ((table[curr].state == "Occupied" && table[curr].data != data) || (table[curr].state == "Tombstone")){
        curr = curr + 1; 
        return search(wordReturn); 
    }
    return false;
}


void insert(string key, string wordReturn){ 

    int curr = findIndex(key);
    if (search(wordReturn) == true) {
        return;
    }

    else {
        table[curr].key = key;
        table[curr].state = "Occupied";
        table[curr].data = wordReturn;
    }
    return;
}


void remove(string key, string wordReturn){ 

    int curr = findIndex(key);

    if (search(wordReturn) == false) {
        return;
    }

    else {
        table[curr].state = "tombstone";
    }
    return;
}

int main() { 
    string input, wordReturn, removeWord, save, value; 

    char key[10], func;

    vector<string> word;    

    emptyTable();                                                   
    
    getline(cin, input);                                                       
    stringstream ss(input);

    while (ss){
        ss >> save;
        word.push_back(save);
    };

    int length = word.size();

    func = input[0];

    for(int i = 1; input[i] != ' ' ; i++){

        if(func == 'A'){

            value = input[1];
            
            for(int j = 1; j < length; j++){ 
            
                wordReturn =  input[j];
            }
            
             cout << wordReturn<< endl;

            insert(value, wordReturn);
        }

        else if(func == 'D'){  
            cout << "in D if" << endl;
            value = input[1];

            for(int j = 1; j < word[i].length(); j++){ 
                if (word[j] != " "){
                    wordReturn =  wordReturn + input[j];
                }
            } 
            
            remove(value, wordReturn); 
        }
    }

    for(int i = 0; i < tableSize; i++) {
        if(table[i].state == "Occupied"){
        cout << table[i].key;
            if(i + 1 < tableSize) {
                cout << " ";
            }    
        }
    }

    cout << endl;
    return 0;
}