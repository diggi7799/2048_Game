#include <bits/stdc++.h>
using namespace std;

int board[4][4];
int dirRow[] = {1, 0, -1, 0};           //{down, right, up, left}; refrence of lines
int dirCol[] = {0, 1, 0, -1};

pair<int,int> generateUnoccupiedPosition(){
    int occupied = 1, line, column;
    while(occupied){
        line = rand() % 4;
        column = rand() % 4;
        if(board[line][column] == 0){
            occupied = 0;
        }
    }
    return make_pair(line, column);
}

void addPiece(){
    pair<int,int> pos =  generateUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
}

void newGame(){
    for(int i=0; i<4; i++){
        for(int  j=0; j<4; j++){
            board[i][j] = 0;
        }
    }
    addPiece();
}

void printUI(){
    system("cls");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j] == 0){
                cout<< setw(4) <<".";
            }
            else{
                cout<< setw(4) << board[i][j];
            }
        }
        cout<<"\n";
    }
    cout<<"n: NewGame, w: up, s: down, d: right, a: left, q: quit\n";
}


bool canDoMove(int row, int column, int nextRow, int nextColumn){
    if(nextRow < 0 || nextColumn < 0 || nextRow >=4 || nextColumn >= 4 || (board[row][column] != board[nextRow][nextColumn] && board[nextRow][nextColumn] != 0)){
        return false;
    }
    return true;
}

void applyMove(int direction){

    int startRow = 0, startCol = 0, rowStep = 1, colStep = 1;
    if(direction == 0){
        startRow = 3;
        rowStep = -1;
    }
    if(direction == 1){
        startCol = 3;
        colStep = -1;
    }


    int movePossible, canAddPiece = 0;
    do
    {
        movePossible = 0;
        for(int i=startRow; i>=0 && i<4; i += rowStep){
            for(int j=startCol; j>=0 && j<4; j += colStep){
                int nextI = i + dirRow[direction], nextJ = j + dirCol[direction];
                if(board[i][j] && canDoMove(i ,j, nextI, nextJ)){
                    board[nextI][nextJ] += board[i][j];
                    board[i][j] = 0;
                    movePossible = canAddPiece = 1;
                }
            }
        }
        printUI();
    } while (movePossible);
    
    if(canAddPiece){
        addPiece();
    }
}

int main(){

    srand(time(0));
    char commandToDir[128];
    commandToDir['s'] = 0;
    commandToDir['d'] = 1;
    commandToDir['w'] = 2;
    commandToDir['a'] = 3;
    newGame();

    while(true){
        printUI();
        char command;
        cin>>command;
        if(command == 'n'){
            newGame();
        }
        else if(command == 'q'){
            break;
        }
        else{
            int currentDir = commandToDir[command];
            applyMove(currentDir);
        }
    }

    return 0;
}