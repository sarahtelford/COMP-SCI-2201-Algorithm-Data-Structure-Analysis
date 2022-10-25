#include <iostream>
#include <string>
#include <vector>

using namespace std; 

string sumvalues(string SI1, string SI2, int B){

	//creating and setting string variables to save string data 
	string sum = "";						
	string zeros = "";						
	string saveCurrent = "";
	string saveCarry = "";

	//creating and setting variables to track carry and current values
	int carry = 0, current = 0;		

	// creating and setting variable to equal the size of the input strings SI1 and SI2
   	int sizeS1 = SI1.size();				
	int sizeS2 = SI2.size();

	//creating and setting variable to equal the difference in the size of the SI1 and SI2 strings		
	int ratio = abs(sizeS1 - sizeS2);	

	//for the size of the ratio varaible save that number of 0's in the zeros variable 
    for (int i = 1; i <= ratio; i++) {		
        zeros += "0";
    }

	//if the size of the SI2 string is bigger than the SI1 string add the zeros variable  
	//to the beginning of the SI1 string. Making both strings the same length
	if (sizeS1 < sizeS2){					
	    SI1 = zeros + SI1;					
	}

	//else add the zeros variable to the beginning of the SI2 string to make both strings 
	//the same length
	else{									
	    SI2 = zeros + SI2;					
	}
	
	for (int i=max(sizeS1,sizeS2)-1;i>-1;i--) {
         
        //add any carry vaules to the current postition
        current = carry + (SI1[i] - '0') + (SI2[i] - '0');
 
        //update the value of carry
        carry = current/B;
 
        //find the current value
        current = current % B;

        //converting the current variable from an int to a string 
        saveCurrent = current + '0'; 
 
        //adding the saveCurrent value to the sum 
        sum = saveCurrent + sum;
    }


    if (carry > 0){

    	//converting the carry value from an int to a string 
    	saveCarry = carry + '0'; 

    	//adding the saveCarry value to the sum 
        sum = saveCarry + sum;
    }

    //return the final sum
    return sum;
}

string multiply(string SI1, string SI2, int B){
	//create string varaibles
	string product;
	string zeros;
	string calculationOne;
	string calculationTwo; 
	string calculationThree; 

	//create interger varaibles
	int range;
	int range2; 
	int hold;
	int hold2; 
	int size; 

	// creating and setting variable to equal the size of the input strings SI1 and SI2
	int sizeS1 = SI1.size();				
	int sizeS2 = SI2.size();

	//creating and setting variable to equal the difference in the size of the SI1 and SI2 strings		
	int ratio = abs(sizeS1 - sizeS2);	

	//for the size of the ratio varaible save that number of 0's in the zeros variable 
    for (int i = 1; i <= ratio; i++) {		
        zeros += "0";
    }

	//if the size of the SI2 string is bigger than the SI1 string add the zeros variable  
	//to the beginning of the SI1 string. Making both strings the same length
	if (sizeS1 < sizeS2){					
	    SI1 = zeros + SI1;					
	}

	//else add the zeros variable to the beginning of the SI2 string to make both strings 
	//the same length
	else{									
	    SI2 = zeros + SI2;					
	}
		
    size = SI1.size(); //length of SI1 and SI2 will now be the same, find lenght of one of them to complete calculations

    //create a base case for when the length is one
    if (size<2){ 

    	// multiply the two strings together 
    	for (int m=0; m<size; m++){
    		//create a hold variable to store the product of the two strings as an int
	    	hold = (SI1[m] - '0')*(SI2[m] - '0');
	    	//convert the int to a string 
	        hold2= hold + '0';
	        //save the string in the product
	        product = hold2; 
    	}
        return product;
    }

    //set the range to half the size if the size is bigger than 1
    range=size/2;

    //break the string into substrings to complete calculations
    string SI1OneValue = SI1.substr(0,range);
    string SI2OneValue = SI2.substr(0,range);
    string SI1ZeroValue = SI1.substr(range,SI1.length()-1);
    string SI2ZeroValue = SI2.substr(range,SI2.length()-1);

   	//calculate products
    string SI1SI2Ones = multiply(SI1OneValue,SI2OneValue,B);
    string SI1OneSI2Zero = multiply(SI1OneValue,SI2ZeroValue,B);
    string SI1ZeroSI2One = multiply(SI1ZeroValue,SI2OneValue,B);
    string SI1SI2Zeros = multiply(SI1ZeroValue,SI2ZeroValue,B);

    //set calculation varaibles
    calculationOne = SI1SI2Ones;
    calculationTwo = sumvalues(SI1OneSI2Zero,SI1ZeroSI2One,B);
    calculationThree = SI1SI2Zeros;

    // set the range dependent on the size of the string
    if(size==1){
    	range2=1;
    }

    else if(size%2==1){
    	range2=(size/2)+1;
	}

    else {
    	range2=(size/2);
    }

  	for(int j=0;j<2*range2;j++){
  		//add 0's to the end od the calaculations
        calculationOne = calculationOne + '0';
    }

    for(int l=0;l<range2;l++){
    	//add 0's to the end od the calaculations
        calculationTwo = calculationTwo + '0';
    }

    //sum the two final products together 
    product = sumvalues(calculationOne,calculationTwo,B);
    product = sumvalues(product,calculationThree,B);

    //remove 0's from the beggining of the string
  	product = product.erase(0, product.find_first_not_of('0'));

    return product;
}


int main(){
	//create string variables 
	string SI1, SI2, binaryString, tempStorage = ""; 

	//create integer varaibles 
	int B, i, k, storage; 
	int j = 0;

	//creating a counter and inisilising it to 0 
	int counter = 0; 
	
	//get input from user and save in binaryString variable
	getline(cin, binaryString); 
	
	//create and set variable to equal the length of the binaryString variable
	int length  = binaryString.length(); 

	for(i=0;i<length;i++){
		//save the current values in storage
		storage = binaryString[i]-'0';

		//if the current value is a space set j = i+1 and increase the counter
		if (binaryString[i] ==' '){
			j = i+1; 
			counter = counter + 1;
			break;
		}

		//push the current value onto the SI1 string and increase the counter
		else {
			SI1.push_back(binaryString[i]);
			counter = counter +1; 
		}
	}

	for(i=j;i<length;i++){
		//save the current values in storage
		storage = binaryString[i]-'0'; 

		//if the current value is a space set k=j and increase the counter
		if (binaryString[i] ==' '){
			k = j;
			counter = counter +1;
			break;
		}

		//push the current value onto the SI2 string and increase the counter
		else {
			SI2.push_back(binaryString[i]);
			counter = counter +1;
		}
	}

	//reset the varaibales
	for(i=counter;i<length;i++){
		if (binaryString[i] ==' '){
			k = i; 
			j = i; 
			break;
		}
		//set the temporary stargae variable equal to the current value of binaryString
		else {
			tempStorage =  tempStorage + binaryString[i]; 
		}
	}

	//convert the tempStorage string value into an integer and save it in the B variable
	B = stoi(tempStorage);

	//reset tempStorage variable to an empty string
	tempStorage = ""; 

	//display the outputs
	cout << '\n' << sumvalues(SI1,SI2,B) << " "  << multiply(SI1,SI2,B) << " " << "0" <<endl;
}




	