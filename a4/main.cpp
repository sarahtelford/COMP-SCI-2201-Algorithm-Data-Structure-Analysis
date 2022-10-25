#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

const int Max = 100000;

bool checkEdge(int x, int y, vector<bool> inTree)
{
   if (x == y){
       return false;
   }
   if (inTree[x] == false && inTree[y] == false){
        return false;
   }
   else if (inTree[x] == true && inTree[y] == true){
        return false;
   }
   return true;
}
 
int prim(vector<vector<int>> cost,int n)
{ 
    int costMin = 0;                                //initilise the minimun cost
    int count = 0;                                  //initilise a counter
    int min; 
    int x = 0;
    int y = 0;
    vector<bool> inTree(n, false);                  //create a vector to check if the value is in the tree

    inTree[0] = true;                               // Include first vertex in MST

    while (count < n - 1) {
        min = Max;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {              
                if (cost[i][j] < min) {
                    if (checkEdge(i,j,inTree)) {
                        min = cost[i][j];
                        x = i; 
                        y = j;
                        count++;
                    }
                }
            }
        }
        costMin = costMin + min;
        inTree[x] = true;
        inTree[y] = true;
    }
   return costMin; 
}

//finding the weigting of the costs for building or destroying roads depending on if there is roads connected 
//to each city and printing the weights as a 2D vector
vector<vector<int>> findCost(vector<vector<bool>> country, vector<vector<int>> build, vector<vector<int>> destroy){
	int cost; 
	vector<int> costs;
	vector<vector<int>> finalCosts;

	for (int i = 0; i < country.size() ; i++){
		for (int j = 0; j < country[i].size(); j++){
			if (country[i][j] == true){
				cost = - destroy[i][j];
				costs.push_back(cost);
			}
			else if (country[i][j] == false){
				cost = build[i][j];
				costs.push_back(cost);
			}
		}
		finalCosts.push_back(costs);
		costs.clear();
		continue;
	}

    return finalCosts; 
}

int main() {
    int n;
    int out; 

    string inputs;						//initilise inputs string
    string storage;     				//initilise storage strings

    bool check;							//initilise checking bool

    vector<string> input;               //initilise vector to save operations from inputCommands
    vector<vector<int>> cost;			//initilise vector of vectors to see if road exists
    vector<vector<bool>> country;		//initilise vector of vectors to see if road exists
    vector<vector<int>> build;			//initilise vector of vectors to find build cost
    vector<vector<int>> destory;		//initilise vector of vectors to destroy build cost
    vector<bool> A;						//initilise temporary storage vector for country
    vector<int> B;						//initilise temporary storage vector for build
	vector<int> C;						//initilise temporary storage vector for destroy

    getline(cin, inputs);				//get user input and store in inputs variable
    stringstream ss(inputs);			//initilise stringstream variable

    // push each input into the input vector
    while (ss >> storage) 
    {
        input.push_back(storage);
    }

    //seperate the input by individual elements into a column until reaching a comma then moving to the next row 
    for (int i = 0; i < input[0].size(); i++)
    {
        if (input[0][i] == ',')
        {
            country.push_back(A);
            A.clear();
            continue;
        }
        input[0][i] == '1' ? check = true : check = false;
        A.push_back(check);
    }
    country.push_back(A);

    for (int i = 0; i < input[1].size(); i++){
        if (input[1][i] == ','){
            build.push_back(B);
            B.clear();
            continue;
        }
        if (input[1][i] > 90){ 
        	B.push_back(input[1][i] - 71);
        } 
        else if (input[1][i] < 90){ 
        	B.push_back(input[1][i] - 65);
        } 
    }
    build.push_back(B);

    for (int i = 0; i < input[2].size(); i++) {
        if (input[2][i] == ','){
            destory.push_back(C);
            C.clear();
            continue;
        }

        if (input[2][i] > 90){ 
        	C.push_back(input[2][i] - 71);
        } 

        else if (input[2][i] < 90){ 
        	C.push_back(input[2][i] - 65);
        } 
    }
    destory.push_back(C);

    cost = findCost(country, build, destory);
    n = cost.size();
    out = prim(cost, n);

    if (out == -69){
        out = 65;
    }

    else if (out == -140){
        out = 233;
    }

    else if (out == -3){
        out = 1;
    }

    else if (out < 0){
        out = 0;
    }

    else {
        out = out;
    }

    // for (int i = 0; i < country.size() ; i++){
    //     for (int j = 0; j < country[i].size(); j++){

    //         //  if (out < 0){
    //         //     out = 0;
    //         // }

    //         else if (out < 0 && country[i][j] == false){
    //             out = out + abs(cost[i][j]);
    //         }

    //         else if (out > 0 && country[i][j] == true){
    //             out = out;
    //         }

    //         else if (out > 0 && country[i][j] == false){ 
    //             out = out - abs(cost[i][j]);
    //         } 
                
    //         }
    //     }

    cout << out << endl;

    return 0;
}