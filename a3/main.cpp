#include <iostream>
#include <string.h> 
#include <sstream>
#include <vector>

using namespace std; 

const int tableSize = 26;                                                       //set table size equal to 26

//create HashTable and define its elements
struct HashTable
{
    char key;
    string state;
    string data; 
} 
table[tableSize];

//assign state of each entry of the HashTable to "Never Used"
void emptyTable() {
    for (int i = 0; i < tableSize; i++){
        table[i].state = "Never Used";
    }
}

//finding the key value as a integer
int hashFunc(char key){
    int index = toupper(key);                                                   // convert to uppercase 
    index = (key - 'A') - 32;                                                   // convert char to integer
    return index; 
}

//function to complete search
bool search(char key, string data){

    int curr = hashFunc(key);                                                   //get the key as an integer

    if (table[curr].data == data) {                                             //if the data input matches 
        return true;
    }

    return false;
}

//function to insert the string
void insert(char key, string data){ 

    int curr = hashFunc(key);                                                   //get the key as an integer
    int num = 0;                                                            

    //while number is not 0 run through the table elements 
    while (num == 0){               
        if (table[curr].state == "Never Used" || table[curr].state == "Tombstone"){
            table[curr].state = "Occupied";                                     //change state at current table element
            table[curr].data = data;                                            //change data at current table element
            num = 1;                                                            //increment num
        }
        
        else if (table[curr].state == "Occupied" && table[curr].data == data){
             num = 1;                                                           //increment num
        }
        else {
            curr = (curr + 1)%26;                                               //increment current value
        }
    }
}

//function to remove the string
void remove(char key, string data){ 

    int curr = hashFunc(key);                                                   //get the key as an integer
    int num = 0;

    //while number is not 0 run through the table elements 
        while (num == 0){

            if (table[curr].state == "Occupied" && table[curr].data == data){
                table[curr].state = "Tombstone";                                //change data at current table element
                num = 1;                                                        //increment num
            }

            else if (table[curr].state == "Never Used") {
                num = 1;                                                        //increment num
            }

            else { 
                curr = (curr + 1)%26;                                           //increment current value
            }
        }
}

int main() { 
    string input;                                                               //initilise variables
    string save;
    vector<string> word;

    emptyTable();                                                               //create the empty table

    getline(cin, input);                                                        //get user input

    stringstream ss(input);

    while (ss >> save){                                                         //push each word inputted into a vector
        word.push_back(save);
    };

    int size =  word.size();                                                    //find the number of words in the vector

    for(int i = 0; i < size; i++){


        if(word[i][0] == 'A'){                                                  //check if the first element of the word is A
            string data =  word[i];                                             //set data == to the current word in the vector
            data.erase(0,1);                                                    //remove the first element from the word
            char key = data[data.length()-1];                                   //set key to be the last element of the word 
            insert(key,data);                                                   //insert data
        }


        else if (word[i][0] == 'D'){                                            //check if the first element of the word is D
            string data =  word[i];                                             //set data == to the current word in the vector
            data.erase(0,1);                                                    //remove the first element from the word
            char key = data[data.length()-1];                                   //set key to be the last element of the word 
            remove(key, data);                                                  //remove data
        }
    }

    for(int i = 0; i < 26; i++) {                                               //print the data saved in Occupied table elements
        if(table[i].state == "Occupied"){
            cout << table[i].data << " ";
        }
    }

    cout << endl << endl;
    return 0;
}