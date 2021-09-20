#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//g++ main.cpp -Wall -Werror -o a.out

vector<vector<int>> brd(3, vector<int> {0, 0, 0});
stack<vector<vector<int>>> st;

void buildBoard(m, n, k){
    
}

//Prints
void printBoard(){
    cout << endl;
    for(unsigned int i = 0;i < brd.size(); i++){
        for(int j = 0; j < 3; j++){
            cout << brd[i][j] << " ";
        }
        cout << " | " << (i*3)+1 << " " << (i*3)+2 << " " << (i*3)+3 << endl;
    }
    cout << endl;
}

//If the value is already inputted(not 0), then ignore it
bool checkValid(int num, int sz){
    if(num < 0 || num > 8 || sz > 1){
        cout << "Invalid! Try again. " << endl;
        return false;
    }
    if(brd[num/3][num%3] != 0){
        cout << "Space " << num+1 << " is already taken, choose a different one." << endl;
        return false;
    }
    return true;
}

//Inputs either 1 or 2 into the board
void inputBoard(int num, int& counter){ 
    st.push(brd);
    brd[num/3][num%3] = counter;
}

//We only need to check if the spot the player placed their point at wins the game
//If our stack reaches size 9, that means theres no more spots left. If no win, then a draw
bool checkBoard(int num, int counter){
    int rowCnt = 0;
    int colCnt = 0;
    int diag1 = 0;
    int diag2 = 0;
    for(int i = 0; i < 3; i++){
        if(brd[i][num%3] == counter) ++rowCnt;
        if(brd[num/3][i] == counter) ++colCnt;
        if(brd[i][i] == counter) ++diag1;
        if(brd[i][2-i] == counter) ++diag2;
    }
    if(rowCnt == 3 || colCnt == 3 || diag1 == 3 || diag2 == 3){
        cout << "Player " << counter << " wins!" << endl;
        return true;
    }
    else if(st.size() == 9){
        cout << "Draw!" << endl;
        return true;
    }
    return false;
}

//Reverts the board back to a previous state
void undoBoard(int& counter){
    cout << "Back 1 turn" << endl;
    brd = st.top();
    st.pop();
    counter = (counter)%2 + 1; 
}

//Returns the inputted value, regardless of upper/lower case and length of input
char getKey(string& inpt){
    string undo = "";
    if(st.size() == 0){
        undo = "";
    }
    else{
        undo = " or u to undo";
    } 
    cout << "Press q to quit" << undo << endl;
    cout << "Press a key 1-9: ";

    //Catches any values larger than size 1
    getline(cin, inpt);

    return tolower(inpt[0]);
}

//Once the game ends, ask the player if they want to keep playing(undo)
bool keepPlaying(){
    string str = "";
    while(true){
        cout << "Press q to quit or u to undo: ";
        getline(cin, str);

        char val = tolower(str[0]);

        if(val != 'q' && val != 'u'){
            system("cls");
            cout << "Invalid input" << endl;
            continue;
        }
        else if(val == 'q'){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

int main(){

    char key;
    string inpt;
    int counter = 1;
    int num = 0;

    system("cls"); //Clears


    int m, n, k;
    cout << "Input m: ";
    cin >> m;

    cout << "Input n: ";
    cin >> n;

    cout << "Inptu k: ";
    cin >> k;

    buildBoard(m, n, k);

    while(true){
        printBoard();

        key = getKey(inpt);

        system("cls");
        
        if(key == 'q'){ //quit
            break;
        } 
        if(key == 'u' && st.size() != 0 && inpt.size() == 1){ //undo
            undoBoard(counter);
            continue;
        }

        //Getting the actual value of the character inputted
        num = (key-'0') - 1; 

        if(!checkValid(num, inpt.size())){
            continue;
        }


        //----------------------------------------------Past this Point, the input is Valid--------------------------------------------


        inputBoard(num, counter);

        if(checkBoard(num, counter)){
            //If keep playing returns true, then the board is undone
            if(keepPlaying()){
                system("cls");
                undoBoard(counter);
                continue;
            }
            //Otherwise, just break
            break;
        }
        
        counter = (counter)%2 + 1; 
    }

    printBoard();

    cout << "Thanks for playing!" << endl;

    return 0;
}

/*
To do list:
- Be able to revert even after drawing / winning

*/