#include <iostream>
#include <vector>

using namespace std;

//g++ main.cpp -Wall -Werror -o a.out

vector<vector<int>> brd(3, vector<int> {0, 0, 0});

void printBoard(vector<vector<int>>& brd){
    for(unsigned int i = 0;i < brd.size(); i++){
        for(int j = 0; j < 3; j++){
            cout << brd[i][j] << " ";
        }
        cout << endl;
    }
}

//Inputs either x or o into the board
void inputBoard(int num, int& counter){ 

    if(brd[num/3][num%3] != 0){ //If the value is already inputted(not -1), then ignore it
        cout << "Space " << num << " is already taken, choose a different one." << endl;
        return; 
    } 

    //Set it either to 1 or 0, depending on the player
    brd[num/3][num%3] = counter; 

    //Increment
    counter = (counter)%2 + 1; 
}

int main(){

    char key;
    string inpt = "";

    int counter = 1;
    int num = 0;

    while(key != 'q'){
        printBoard(brd);
        
        cout << "Press a key 1-9: ";

        //Catches any values larger than size 1
        getline(cin, inpt); 
        key = inpt[0];

        //Getting the actual value of the character inputted
        num = (key-'0') - 1; 

        if(key-'0' < 1 || key-'0' > 9 || inpt.size() > 1){ //Out of bounds
            cout << "Invalid! Try again: " << endl;
            continue;
        }

        inputBoard(num, counter);
    }

    return 0;
}

/*
Bugs to fix:

- When inputting in 10, it does not recognize 10 as a character, rather recognizes 1 first, then 0, which fails at the part of 0. Fix this


*/