#include <iostream>
#include <vector>
#include <stack>
#include <string> 

using namespace std;

//g++ main.cpp -Wall -Werror -o a.out

vector<vector<int>> brd;
stack<vector<vector<int>>> st;
int m, n, k;

//Builds board mxn
void buildBoard(){
    vector<int> temp(m, 0);

    for(int i = 0; i < n; i++){
        brd.push_back(temp);
    }
}

//Prints
void printBoard(){
    cout << endl;
    for(unsigned int i = 0;i < brd.size(); i++){
        for(int j = 0; j < brd[i].size(); j++){
            cout << brd[i][j] << " ";
        }
        cout << " | ";
        for(int k = 0; k < m; k++){
            cout << (i*m)+k+1 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//If the value is already inputted(not 0), then ignore it
bool checkValid(int num){
    if(num < 0 || num > m*n){
        cout << "Invalid! Try again. " << endl;
        return false;
    }
    if(brd[num/m][num%m] != 0){
        cout << "Space " << num+1 << " is already taken, choose a different one." << endl;
        return false;
    }
    return true;
}

//Inputs either 1 or 2 into the board
void inputBoard(int num, int& counter){ 
    st.push(brd);
    brd[num/m][num%m] = counter;
}

//We only need to check if the spot the player placed their point at wins the game
//If our stack reaches size m*n, that means theres no more spots left. If no win, then a draw
bool checkBoard(int num, int counter){
    int x = num%m;
    int y = num/m;

    int rowCnt = 1;
    int colCnt = 1;
    int diag1 = 1;
    int diag2 = 1;
    
    int i = 1;

    while(x+i < m && brd[y][x+i] == counter){
        ++colCnt;
        i++;
    }

    i = 1;

    while(x-i >= 0 && brd[y][x-i] == counter){
        ++colCnt;
        i++;
    }

    if(colCnt == k){
        cout << "Player " << counter << " wins!" << endl;
        return true;
    }

    i = 1;

    while(y+i < n && brd[y+i][x] == counter){
        ++rowCnt;
        i++;
    }

    i = 1;

    while(y-i >= 0 && brd[y-i][x] == counter){
        ++rowCnt;
        i++;
    }

    if(rowCnt == k){
        cout << "Player " << counter << " wins!" << endl;
        return true;
    }

    i = 1;

    while(x+i < m && y+i < n && brd[y+i][x+i] == counter){
        ++diag1;
        i++;
    }
    
    i = 1;

    while(x-i >= 0 && y-i >= 0 && brd[y-i][x-i] == counter){
        ++diag1;
        i++;
    }

    if(diag1 == k){
        cout << "Player " << counter << " wins!" << endl;
        return true;
    }

    i = 1;

    while(x+i < m && y-i >= 0 && brd[y-i][x+i] == counter){
        ++diag2;
        i++;
    }

    i = 1;

    while(y+i < n && x-i >= 0 && brd[y+i][x-i] == counter){
        ++diag2;
        i++;
    }

    if(diag2 == k){
        cout << "Player " << counter << " wins!" << endl;
        return true;
    }
    else if(st.size() == m*n){
        cout << "Draw!" << endl;
        return true;
    }
    return false;
}

//Reverts the board back to a previous state
void undoBoard(int& counter){
    counter = (counter)%2 + 1; 
    cout << "Went back" << endl;
    brd = st.top();
    st.pop();
    
}

//Returns the inputted value as an int
int getNum(){
    int x = 0;
    cout << "Press a key 1-" << m*n << ": ";
    cin >> x;
    return x;
}

//Once the game ends, ask the player if they want to keep playing(undo)
bool keepPlaying(){
    string str = "";
    while(true){
        cout << "Press q to finish or u to undo: ";
        cin.clear();
        fflush(stdin);
        getline(cin, str);

        char val = tolower(str[0]);

        if(val != 'q' && val != 'u' || str.size() > 1){
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

    cout << "Input m: ";
    cin >> m;

    cout << "Input n: ";
    cin >> n;

    while(true){
        cout << "Input k: ";
        cin >> k;
        if(k > max(m, n)){
            cout << "k is too large, try again" << endl;
            continue;
        }
        break;
    }
    

    buildBoard();

    system("cls");

    while(true){
        
        cout << "It is now Player " << counter << "\'s turn" << endl;

        printBoard();

        string undo = "";
        if(st.size() == 0){
            undo = "";
        }
        else{
            undo = ", or u to undo";
        } 
        cout << "Press p to play, q to quit" << undo << endl;

        //Catches any large values
        cin.clear();
        fflush(stdin);
        getline(cin, inpt);

        if(inpt.size() > 1){
            system("cls");
            cout << "You can only input one character" << endl;
            continue;
        }

        key = tolower(inpt[0]);
        
        if(key == 'q'){ //quit
            break;
        } 
        else if(key == 'u' && st.size() != 0){ //undo
            system("cls");
            undoBoard(counter);
            continue;
        }
        else if(key != 'p'){ //Anything else that is not q, u, or p
            system("cls");
            cout << "Invalid Input" << endl;
            continue;
        }

        //Getting the actual value of the character inputted
        num = getNum() - 1;
        system("cls");
        if(!checkValid(num)){
            continue;
        }


        //----------------------------------------------Past this Point, the input is Valid--------------------------------------------


        inputBoard(num, counter);

        if(checkBoard(num, counter)){
            //If keep playing returns true, then the board is undone
            if(keepPlaying()){
                system("cls");
                counter = (counter)%2 + 1; 
                undoBoard(counter);
                continue;
            }
            //Otherwise, just break
            break;
        }
        
        counter = (counter)%2 + 1; 
    }

    system("cls");

    printBoard();

    cout << "Thanks for playing!" << endl;

    return 0;
}

/*
To do list:
- 

*/