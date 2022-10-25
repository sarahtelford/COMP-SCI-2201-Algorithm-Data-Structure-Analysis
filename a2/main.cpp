#include<iostream>
#include <sstream>
#include <vector>
#include <sstream>
using namespace std;

class AVL
{
	//initilise public functions and varaibles
	public:
		AVL * insert(AVL * root, int value);									//inserting a root
		AVL * remove(AVL * root, int value);									//deleting a root
		void pre(AVL * root);													//printing AVL in a preorder traversal
		void post(AVL * root);													//printing AVL in a postorder traversal
		void inorder(AVL * root);												//printing AVL in a inorder traversal
			int nodeValue;															//value of root variable
	private:	
		AVL * rotateRight(AVL * root);											//performing right subtree rotations
		AVL * rotateLeft(AVL * root);											//performing left subtree rotations
		AVL * Max(AVL * root);													//finding the minimum value root in the AVL tree
		int height(AVL * root);													//finding height of the AVL tree
		int balance(AVL * root);												//checking if the AVL tree is balanced
		
		int maxNode;															//maximum value in root
		int AVLheight;															//height of AVL variable
		AVL * left;																//left root variable
		AVL * right;															//right root variable
		int getNodeValue();
};

int AVL :: getNodeValue(){
	// cout<<"trying to print nodeValue"<<endl;
	// cout<<"nodeValue is "<<nodeValue<<endl;
	return nodeValue;
}
//function to insert desired nodes into the AVL tree and balance the tree
AVL * AVL :: insert(AVL * root, int value) {
	int balanceCheck ;															//initilise the balance checking variable

	if (root == NULL){															//if the root is empty add a new root and make its value = to the desired input 
		AVL * root = new AVL;													//create a new AVL root
		root -> nodeValue = value;												//make the root value equal to the desires value
		root -> left = NULL;
		root -> right = NULL;
		root -> AVLheight = 1; 
		return(root);
	}

	else if (value < root -> nodeValue) { 										// else if the input value < the current root value insert the value to the left of the current root
		root -> left = insert(root -> left, value);
	}

	else if (value > root -> nodeValue) {										// else if the input value > the current root value insert the value to the right of the current root
		root -> right = insert(root -> right, value);
	}

	else { 																		// else the values are equal
		return root;
	}
	
	//get the height of the new AVL tree
	maxNode = max(height(root -> left), height(root -> right));					//find the max height between the two subtrees 
	root -> AVLheight = 1 + maxNode;											//add 1 to maxNode to the include the root root int the AVL height
	balanceCheck = balance(root);												//get the balance check value by calling the balance function

	//use the balance check variable to determine what rotation needs to occour. 
	//there are four possible outcomes for rotations:
	if (balanceCheck > 1) {													
		if (value < root -> left -> nodeValue){									//left left rotation 
			return rotateRight(root);
		}
		else if (value > root -> left -> nodeValue){							//left right rotation
			root -> left = rotateLeft(root -> left);
			return rotateRight(root);
		}
		
	}

	else if (balanceCheck < -1) {			
		if (value > root -> right -> nodeValue) {								//right right rotation
			return rotateLeft(root);
		}
		else if (value < root -> right -> nodeValue){							//right left rotation
			root -> right = rotateRight(root -> right);
			return rotateLeft(root);
		}
	}

	maxNode = max(height(root -> left), height(root -> right));					//find the max height between the two subtrees 
	root -> AVLheight = 1 + maxNode;											//add 1 to maxNode to the include the root root int the AVL height

	return root;
}

//function to remove desired nodes from the AVL tree and balance the tree
AVL * AVL :: remove(AVL * root, int value) {
	int balanceCheck;

	if (root == NULL){															//if the root is empty return null
		return root;
	}

	if ( value < root -> nodeValue ) {											//if the value to be deleted in < the root, the value liesin the left subtree
		root -> left = remove(root -> left, value);								//keep moving left until locating value
	}
	
	else if( value > root -> nodeValue) {										//if the value to be deleted in > the root, the value liesin the right subtree
		root -> right = remove(root -> right, value); 							//keep moving left until locating value
	}

	else {												
		if( (root -> left == NULL) || (root -> right == NULL) ) {				//if the root has 0 or 1 children

            AVL * temp = root->left ? root->left : root->right;					//if temp = root->left is null perform on left root else perform on right

				if (temp == NULL)												//if there are no children store the root value in the temp root and delete the root
				{
					temp = root;
					root = NULL;
				}

				else {
					* root = * temp; 											//reassign the pointer for the temp root to the root root pointer
					free(temp);													//delete the temp root
				}
		}
		else {
			AVL * temp = Max(root -> left);										//create a temporay root which is = to the smallest root in the right subtree
			root -> nodeValue = temp -> nodeValue;								//copy the root value into the temp root
			root -> left = remove(root -> left, temp -> nodeValue);				//remove the nodeValue root from the right subtree	
			// cout << root -> left  << endl;		
		}
	}

	if (root == NULL){															//if the avl has one root 
		return root;
	}

	balanceCheck = balance(root);												//get the balance check value by calling the balance function

	//use the balance check variable to determine what rotation needs to occour. 
	//there are four possible outcomes for rotations:
	if (balanceCheck > 1 ){
		if (balance(root -> left) >= 0) {										//left left rotation 
			return rotateRight(root);
		} 
		else if (balance(root -> left) < 0){									//left right rotation
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}

	else if (balanceCheck < -1){
		if (balance(root -> right) <= 0){										//right right rotation
			return rotateLeft(root);
		}
		else if (balance(root -> right) > 0) {									//right Left rotation
			root -> right = rotateRight(root -> right);
			return rotateLeft(root);
		}
	}
	
	maxNode = max(height(root -> left), height(root -> right));					//find the max height between the two subtrees 
	root -> AVLheight = maxNode + 1;											//add 1 to maxNode to the include the root root int the AVL height
	

	return root;
}

//check the height of the AVL tree and return the total height of the tree
int AVL :: height(AVL * root) {
	int hght; 
	if (root == NULL) { 														//if the root is empty return 0
		hght = 0;	
	}

	else {																		//else if the return the height of the tree
		hght = root -> AVLheight;
	}
	return hght;
}

//the minimum value will always be placed on the leftmost root. To find max value find the leftmost root
AVL * AVL :: Max(AVL * root) {
	AVL * currentNode = root;													//initilise and set the current root 

	while (currentNode -> right != NULL){											// if the current root is not NULl set the current root to the next left root
		currentNode = currentNode -> right;
	}
	
	return currentNode;															//return the leftmost root
}

//performing right rotations on the AVL tree
AVL * AVL :: rotateRight(AVL * storageNode) {
	AVL * changeRoot = storageNode -> left;										//create a pointer for the left subtree, this will conatin the new root
	AVL * rightStorage = changeRoot -> right;									//create a pointer for the right subtree

	changeRoot -> right = storageNode;
	storageNode -> left = rightStorage;

	//update the hegists of the tree for the balancing function
	maxNode =  max(height(storageNode -> left), height(storageNode -> right)); 	//find the max height between the two subtrees 
	storageNode -> AVLheight = maxNode + 1;										//add 1 to maxNode to the include the root root int the AVL height

	maxNode =  max(height(changeRoot -> left), height(changeRoot -> right)); 	//find the max height between the two subtrees 
	changeRoot -> AVLheight = maxNode + 1;										//add 1 to maxNode to the include the root root int the AVL height

	return changeRoot;
}

//performing left rotations on the AVL tree
AVL * AVL :: rotateLeft(AVL * storageNode) {
	AVL * changeRoot = storageNode -> right;									//create a pointer for the right subtree, this will conatin the new root
	AVL * leftStorage = changeRoot -> left;										//create a pointer for the left subtree

	changeRoot -> left = storageNode;
	storageNode -> right = leftStorage;

	maxNode = max(height(storageNode->left), height(storageNode->right));		//find the max height between the two subtrees 		
	storageNode -> AVLheight = maxNode + 1;										//add 1 to maxNode to the include the root root int the AVL height
	maxNode = max(height(changeRoot->left), height(changeRoot->right));			//find the max height between the two subtrees 									
	changeRoot -> AVLheight = maxNode + 1;										//add 1 to maxNode to the include the root root int the AVL height

	return changeRoot;
}

//finding the balancing value of the AVL
int AVL :: balance(AVL * balance) {
	int balanceValLeft;															//initilise left height variable
	int balanceValRight;  														//initilise right height variable
	int balanceVal; 															//initilise balancing value variable

	if (balance == NULL) {														//if the AVL is empty no balncing need to occur
		balanceVal = 0;
	}

	else {
		balanceValLeft =  height(balance -> left); 									// find the height of the left subtree and store it
		balanceValRight = height(balance -> right); 								// find the height of the left subtree and store it
		balanceVal = balanceValLeft - balanceValRight;								//subtract the left height from the right height to find the balancing factor 
	}
	
	return balanceVal;															//return the balancing factor
}

//printing the preorder traversal of the AVL tree
void AVL :: pre(AVL * root) {
	// cout<<"in pre function"<<endl;
	if (root != NULL){
		// cout<<"in pre function if"<<endl;
		//cout << root -> nodeValue << " ";
		cout << root -> getNodeValue() << " "; 										//output the current root root value 
		pre(root -> left);														//traversing to the left of the root				
		pre(root -> right);														//traversing to the right of the root
	}
}

//printing the postorder traversal of the AVL tree
void AVL :: post(AVL * root) {
	if (root != NULL){
		post(root -> left);														//traversing to the left of the root
		post(root -> right);													//traversing to the right of the root
		cout << root-> getNodeValue() << " " ;										//output the current root root value 
	}
}

//printing the inorder traversal of the AVL tree
void AVL :: inorder(AVL * root) {
	// cout<<"in IN function"<<endl;
	if (root != NULL){
		inorder(root -> left);													//traversing to the left of the root
		cout << root -> getNodeValue() << " ";								//output the current root root value 
		inorder(root -> right);													//traversing to the left of the root
	}
}

int main() {
string input, save, currentString;												//initilise string	
	AVL * root = NULL;															//initialise the root root to be empty							
	vector<string> digit;														//intitilise the varaible to store the digit 
	int number, length;
	
	getline(cin, input);														//get input from the user
	stringstream ss(input);

	while (ss){
        ss>>save;
        digit.push_back(save);
    };
	// cout<<"digit length is "<<digit.size()<<endl;
	length = digit.size();

	for(int i = 0; i < length-1; i++){
		// cout<<"entering for loop"<<endl;
		currentString = digit[i];
		// cout<<"currentString is "<<currentString<<endl;
		// cout<<"currentString[i] is "<<currentString[i]<<endl;
		// cout <<"last letter is "<<currentString[currentString.length()-1]<<endl;
		if(currentString[0] == 'A'){											//if the current input is 'A' insert a root in the the AVL tree
			// cout<<"entering for if A"<<endl;
			number = 0; 
			for(int j = 1; j < digit[i].size(); j++){ 
				// cout << "in A number loop "<< endl;
				// cout<<"currentString[j] is "<<currentString[j]<<endl;
				number = number*10+(currentString[j] - '0');
			}
			root = root -> insert(root, number);
			// cout<<"number is "<<number<<endl;		
			// cout<<"nodeValue is "<<root->getNodeValue()<<endl;
		}

		else if(currentString[0] == 'D'){	
			// cout<<"entering for if D"<<endl;									//if the current input is 'D' insert a root in the the AVL tree
			number = 0; 
			for(int j = 1; j < digit[i].size(); j++){ 
				number = number*10+(currentString[j] - '0');
			}
			root = root -> remove(root, number);
		}

		if(currentString[currentString.length()-1] == 'N') {					// else if character at i position is 'I' then perform an in order traversal
			if(root == NULL) {
				cout << "EMPTY" << endl;
			}
			else {
				root -> inorder(root);
			}
			cout << endl; 
		}

		else if(currentString[currentString.length()-1] == 'E') {				// else if character at i position is 'I' then perform an in order traversal
			// cout<<"in PRE"<<endl;
			if(root == NULL) {
				// cout<<"in PRE if"<<endl;
				cout << "EMPTY" << endl;
			}
			else {
				// cout<<"in PRE else"<<endl;
				root-> pre(root);
			}
			cout << endl; 
		}

		else if(currentString[currentString.length()-1] == 'T') {				// else if character at i+1 position is 'O' or 'o' a post order traversal
			if(root == NULL) {
				cout << "EMPTY" << endl;
			}
			else{
				root -> post(root);
			} 
			cout << endl; 
		}	
		// cout << root -> nodeValue ;
	}
	return 0;
}