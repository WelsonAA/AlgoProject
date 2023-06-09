//
// Created by George Welson on 28-Nov-22.
//
#include "ChessB.h"


/*
 * 1- This is the constructor of the chess game which builds the 8 x 8 chess board with the nodes
 * 2- A node represent a square in the board e.g. : a1 , h8 , etc.
 * 3- A vector is used to insert all nodes into it thus implementing the idea of "Graph"
 *   which makes it easy to traverse through the board
 * */

ChessB::ChessB(int x,int y)//constructing the board
{
    for(int i= 0; i<N;i++){
        for(int j=0;j<N;j++){
            Node k(i,j);
            cb[i][j]=k;
        }
    }
    for(int i=0;i<N*N;i++){
        this->pathK[i]=NULL;
    }
    cnt=0;
    this->src=&this->cb[x][y];
    this->src->visited=true;
    this->current=this->src;
    this->pathK[cnt]=this->current;
    cnt++;
}


/*
 4-This function is implemented to avoid the chess pieces used (knight, pawn, bishop) to go
 out of the chess board (A chess piece can't go beyond A & H, and 1 & 8)
 */





void ChessB::addNexts() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            addKnight(i, j);
        }
    }
}


/*
 addKnight is a function used to create the nodes available for the knights to move to
  it's implemented using the xMovesK and yMovesK which is the positions the knight can move to
 */
void ChessB::addKnight(int i, int j) {
    int y = 0;
    for (int k = 0; k < N; k++) {
        int temp1;
        int temp2;
        temp1 = this->cb[i][j].c + xMovesK[k];
        temp2 = this->cb[i][j].r + yMovesK[k];
        if (!(isValid(temp2,temp1)))
            this->cb[i][j].nextK[y]=NULL;
        else {
            this->cb[i][j].nextK[y] = &this->cb[temp2][temp1];
            this->cb[i][j].deg++;
            y++;
        }
    }
}


void ChessB::choosePathKWarnsdorff() {//Building the path with Warnsdorff's rule
    Node* tmp= nullptr;
    for(int i=0;i<N*N-1;i++){
        tmp = this->current->getLowestNext();
        if (tmp == nullptr)
            break;
        else {
            this->current = tmp;
            this->current->visit();
            this->pathK[cnt]=tmp;
            cnt++;
        }
    }
}
void ChessB::choosePathKBacktracking() {
    Node* tmp= nullptr;
    for(int j=0;j<N*N;j++){
        for(int i=0;(i<8);i++) {
            tmp = this->current->nextK[i];
            if (tmp == nullptr||(tmp->visited == true && i>=7)) {//backtracking
                this->current->visited= false;
                cnt-=2;
                this->current = this->pathK[cnt];
                i= this->current->nextPossibleMove - 1;
                cnt++;
                this->pathK[cnt]=NULL;
                j=cnt-1;
                continue;
            }
            else if (tmp->visited == true)
                continue;
            else {
                this->current->nextPossibleMove= i + 1;
                this->current = tmp;
                this->current->visited=true;
                this->pathK[cnt] = tmp;
                cnt++;
                break;
            }
        }
    }
}