#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int CharacterQuantity(int row, int column, char board[500][500], char inputValue){
    int quantity = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == inputValue){
                quantity++;
            }
        }
    }
    return quantity;
}
class Character{
    public:
    int hp, hpMax, attack, armor, Mresistence;
    int iPosition;
    int jPosition;
    int direction;
    int movement;
    int ability;
    
    Character(){}  

    void AskAttributes(ifstream &entrada){
        entrada >> this->hp;
        this->hpMax = this->hp;
        entrada >> this->attack;
        entrada >> this->armor;
        entrada >> this->Mresistence;
    }
    void changeCoordinates(int &iPosition, int &jPosition, int x, int y){
        iPosition = x;
        jPosition = y;
    }
    void AskDirectionAndMovement(ifstream &entrada){
        int aux = 0;
        entrada >> aux;
        this->direction = aux / 100;
        this->movement = (aux / 10) % 10;
        this->ability = aux % 10;
    }  
    void AskMovement(int row, int column, char board[500][500], char inputValue){
        bool CharacterFound = false;
        
        switch(direction){

            case 1:
                for(int i = 1; i <= movement;){
                    if(iPosition - i >= 0){
                        if(board[iPosition - i][jPosition] == '_'){
                            i++;
                        }
                        else {
                            board[iPosition][jPosition] = '_';
                            board[iPosition - i + 1][jPosition] = inputValue;
                            iPosition = iPosition - i + 1;
                            CharacterFound = true;
                            break;
                        }
                    }
                    else {
                        board[iPosition][jPosition] = '_';
                        board[iPosition - i + 1][jPosition] = inputValue;
                        iPosition = iPosition - i + 1;
                        CharacterFound = true;
                        break;
                    }
                }
                if (!CharacterFound && board[iPosition - movement][jPosition] == '_'){
                    board[iPosition][jPosition] = '_';
                    board[iPosition - movement][jPosition] = inputValue;
                    iPosition = iPosition - movement;
                    break;   
                }
            break; 
            case 2:
                for(int i = 1; i <= movement;){
                    if(jPosition + i < column){
                        if(board[iPosition][jPosition + i] == '_'){
                            i++;
                        }
                        else {
                            board[iPosition][jPosition] = '_';
                            board[iPosition][jPosition + i - 1] = inputValue;
                            jPosition = jPosition + i - 1;
                            CharacterFound = true;
                            break;
                        }
                    }
                    else {
                        board[iPosition][jPosition] = '_';
                        board[iPosition][jPosition + i - 1] = inputValue;
                        jPosition = jPosition + i - 1;
                        CharacterFound = true;
                        break;
                    }
                }
                if (!CharacterFound && board[iPosition][jPosition + movement] == '_'){
                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition + movement] = inputValue;
                    jPosition += movement;
                    break;
                }
            break;
            case 3:
                for(int i = 1; i <= movement;){
                    if(iPosition + i < row){
                        if(board[iPosition + i][jPosition] == '_'){
                            i++;
                        }
                        else {
                            board[iPosition][jPosition] = '_';
                            board[iPosition + i - 1][jPosition] = inputValue;
                            iPosition = iPosition + i - 1;
                            CharacterFound = true;
                            break;
                        }
                    }
                    else {
                        board[iPosition][jPosition] = '_';
                        board[iPosition + i - 1][jPosition] = inputValue;
                        iPosition = iPosition + i - 1;
                        CharacterFound = true;
                        break;
                    }
                }
                if (!CharacterFound && board[iPosition + movement][jPosition] == '_'){
                    board[iPosition][jPosition] = '_';
                    board[iPosition + movement][jPosition] = inputValue;
                    iPosition += movement;
                    break;   
                }
            break;

            case 4:
            for(int i = 1; i <= movement;){
                    if(jPosition - i >= 0){
                        if(board[iPosition][jPosition - i] == '_'){
                            i++;
                        }
                        else {
                            board[iPosition][jPosition] = '_';
                            board[iPosition][jPosition - i + 1] = inputValue;
                            jPosition = jPosition - i + 1;
                            CharacterFound = true;
                            break;
                        }
                    }
                    else {
                        board[iPosition][jPosition] = '_';
                        board[iPosition][jPosition - i + 1] = inputValue;
                        jPosition = jPosition - i + 1;
                        CharacterFound = true;
                        break;
                    }
                }
                if (!CharacterFound && board[iPosition][jPosition - movement] == '_'){
                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition - movement] = inputValue;
                    jPosition -= movement;
                    break;   
                }
            break;
        }
    }
    ~Character(){}
};
class Enemy: public Character{
    public:

        Enemy(){}

        
        ~Enemy(){}
};
class Healer: public Character{
public: 
    Healer(){}
    ~Healer(){}
};
void calculoDanio(int attack, bool physical, char board[500][500], Enemy e[1000], int FE, int CE, int quantity);
class Warrior:public Character{
    public:

        Warrior(){} 
        void Quebrajar(int row, int column, char board[500][500], Enemy e[1000], int quantity){
            int x = iPosition, y = jPosition;
            switch(direction){
                case 1:
                if(x - 1 >= 0 && y - 1 >= 0){if(board[x - 1][y - 1] == 'E'){calculoDanio(attack + 2, true, board, e, x - 1, y - 1, quantity);}}
                if(x - 1 >= 0){if(board[x - 1][y] == 'E'){calculoDanio(attack + 2, true, board, e, x - 1, y, quantity);}}
                if(x - 1 >= 0 && y + 1 < column){if(board[x - 1][y + 1] == 'E'){calculoDanio(attack + 2, true, board, e, x - 1, y + 1, quantity);}}
                break;
                case 2:
                    if(x - 1 >= 0 && y + 1 < column){if(board[x - 1][y + 1] == 'E'){calculoDanio(attack + 2, true, board, e, x - 1, y + 1, quantity);}}
                    if(y + 1 < column){if(board[x][y + 1] == 'E'){calculoDanio(attack + 2, true, board, e, x, y + 1, quantity);}}
                    if(x + 1 < row && y + 1 < column){if(board[x + 1][y + 1] == 'E'){calculoDanio(attack + 2, true, board, e, x + 1, y + 1, quantity);}}
                break;
                case 3:
                    if(x + 1 < row && y - 1 >= 0){if(board[x + 1][y - 1] == 'E'){calculoDanio(attack + 2, true, board, e, x + 1, y - 1, quantity);}}
                    if(x + 1 < row){if(board[x + 1][y] == 'E'){calculoDanio(attack + 2, true, board, e, x - 1, y, quantity);}}
                    if(x + 1 < row && y + 1 < column){if(board[x + 1][y + 1] == 'E'){calculoDanio(attack + 2, true, board, e, x + 1, y + 1, quantity);}}
                break;
                case 4:
                    if(x - 1 >= 0 && y - 1 >= 0){if(board[x - 1][y - 1] == 'E'){calculoDanio(attack + 2, true, board, e, x - 1, y - 1, quantity);}}
                    if(y - 1 >= 0){if(board[x][y - 1] == 'E'){calculoDanio(attack + 2, true, board, e, x, y - 1, quantity);}}
                    if(x + 1 < row && y - 1 >= 0){if(board[x + 1][y - 1] == 'E'){calculoDanio(attack + 2, true, board, e, x + 1, y - 1, quantity);}}

                break;
            }
        }
        void Estocada(int row, int column, char board[500][500], Enemy e[1000], int quantity){
            switch(direction){
                case 1:
                if(iPosition - 1 >= 0){
                    if(board[iPosition - 1][jPosition] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition - 1, jPosition, quantity); }
                }
                if(iPosition - 2 >= 0){
                    if(board[iPosition - 2][jPosition] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition - 2, jPosition, quantity); }
                }
                break;
                case 2:
                if(jPosition + 1 <= column - 1){
                    if(board[iPosition][jPosition + 1] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition, jPosition + 1, quantity); }
                }
                if(jPosition + 2 <= column - 1){
                    if(board[iPosition][jPosition + 2] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition, jPosition + 2, quantity); }
                }
                break;
                case 3:
                if(iPosition + 1 <= row - 1){
                    if(board[iPosition + 1][jPosition] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition + 1, jPosition, quantity); }
                }
                if(iPosition + 2 <= row - 1){
                    if(board[iPosition + 2][jPosition] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition + 2, jPosition, quantity); }
                }
                break;
                case 4:
                if(jPosition - 1 >= 0){
                    if(board[iPosition][jPosition - 1] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition, jPosition - 1, quantity); }
                }
                if(jPosition - 2 >= 0){
                    if(board[iPosition][jPosition - 2] == 'E'){ calculoDanio(attack + 4, true, board, e, iPosition, jPosition - 2, quantity); }
                }
                break;
            }
        }
        void Torbellino(int row, int column, char board[500][500], Enemy e[1000], int quantity){
            int contEnemigos = 0;
            int x = iPosition, y = jPosition;

            if(x - 1 >= 0){ if(board[x - 1][y] == 'E'){contEnemigos++;}}
            if(y + 1 < column){ if(board[x][y + 1] == 'E'){contEnemigos++;}}
            if(x + 1 < row){if(board[x + 1][y] == 'E'){contEnemigos++;}}
            if(y - 1 >= 0){ if(board[x][y - 1] == 'E'){contEnemigos++;}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'E'){calculoDanio((attack + 1)* contEnemigos, true, board, e, x - 1, y, quantity);}}
            if(y + 1 < column){if(board[x][y + 1] == 'E'){calculoDanio((attack + 1)* contEnemigos, true, board, e, x, y + 1, quantity);}}
            if(x + 1 < row){if(board[x + 1][y] == 'E'){calculoDanio((attack + 1)* contEnemigos, true, board, e, x + 1, y, quantity);}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'E'){calculoDanio((attack + 1)* contEnemigos, true, board, e, x, y - 1, quantity);}}
        }
        ~Warrior(){}
};
class Wizard:public Character{
public:
    Wizard(){}

    void Tp(int row, int column, char board[500][500]){
        
        switch(direction){

            case 1:

            if(iPosition - 2 >= 0){

                if(board[iPosition - 2][jPosition] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition - 2][jPosition] = 'M';
                    iPosition -= 2;
                }
                else if(board[iPosition - 1][jPosition] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition - 1][jPosition] = 'M';
                    iPosition -= 1;
                }
            }
            else if(iPosition - 1 >= 0 && board[iPosition - 1][jPosition] == '_'){

                board[iPosition][jPosition] = '_';
                board[iPosition - 1][jPosition] = 'M';
                iPosition -= 1;
            }
            break;
            case 2:

            if(jPosition + 2 < column){

                if(board[iPosition][jPosition + 2] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition + 2] = 'M';
                    jPosition += 2;
                }
                else if(board[iPosition][jPosition + 1] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition + 1] = 'M';
                    jPosition += 1;
                }
            }
            else if(jPosition + 1 < column && board[iPosition][jPosition + 1] == '_'){

                board[iPosition][jPosition] = '_';
                board[iPosition][jPosition + 1] = 'M';
                jPosition += 1;
            }
            break;
            case 3:

            if(iPosition + 2 < row){

                if(board[iPosition + 2][jPosition] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition + 2][jPosition] = 'M';
                    iPosition =+ 2;
                }
                else if(board[iPosition + 1][jPosition] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition + 1][jPosition] = 'M';
                    iPosition += 1;
                }
            }
            else if(iPosition + 1 < row && board[iPosition + 1][jPosition] == '_'){

                board[iPosition][jPosition] = '_';
                board[iPosition + 1][jPosition] = 'M';
                iPosition += 1;
            }
            break;
            case 4:

            if(jPosition - 2 >= 0){

                if(board[iPosition][jPosition - 2] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition - 2] = 'M';
                    jPosition -= 2;
                }
                else if(board[iPosition][jPosition - 1] == 'E'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition - 1] = 'M';
                    jPosition -= 1;
                }
            }
            else if(jPosition - 1 >= 0 && board[iPosition][jPosition - 1] == '_'){

                board[iPosition][jPosition] = '_';
                board[iPosition][jPosition - 1] = 'M';
                jPosition -= 1;
            }
            break;
        }
    }
    void EsferaDeHielo(char board[500][500], Enemy e[1000], ifstream &archivo, int quantity){
        int x = 0, y = 0;
        archivo >> y;
        archivo >> x;
                
        if(board[x][y] == 'E'){
            calculoDanio(attack * 3, false, board, e, x, y, quantity);
        }
    }
    void Tempestad(int row, int column, char board[500][500], Enemy e[1000], ifstream &entrada, int quantity){
        int x = 0, y = 0, i = 1;
        entrada >> y;
        entrada >> x;

        if(board[x - i][y - i] == 'E' && x - i >= 0 && y - i >= 0){calculoDanio(attack, false, board, e, x - i, y - i, quantity);}
        if(board[x - i][y] == 'E' && x - i >= 0){calculoDanio(attack, false, board, e, x - i, y, quantity);}
        if(board[x - i][y + i] == 'E' && x - i >= 0 && y + i < column){calculoDanio(attack, false, board, e, x - i, y + i, quantity);}
        if(board[x][y + i] == 'E' && y + i < column){calculoDanio(attack, false, board, e, x, y + i, quantity);}
        if(board[x + i][y + i] == 'E'&& x + i < row && y + i < column){calculoDanio(attack, false, board, e, x + i, y + i, quantity);}
        if(board[x + i][y] == 'E' && x + i < row){calculoDanio(attack, false, board, e, x + i, y, quantity);}
        if(board[x + i][y - i] == 'E' && x + i < row && y - i >= 0){calculoDanio(attack, false, board, e, x + i, y - i, quantity);}
        if(board[x][y - i] == 'E' && y - i >= 0){calculoDanio(attack, false, board, e, x, y - i, quantity);}
        if(board[x][y] == 'E'){calculoDanio(attack, false, board, e, x, y, quantity);}    
    }

    ~Wizard(){}
};
class Archer:public Character{
public:
    Archer(){}
    void Multidisparo(int row, int column, char board[500][500], Enemy e[1000], int quantity){
        int aux = iPosition;
        int aux2 = jPosition;

            aux = iPosition;
            aux2 = jPosition;

            for(int i = 1; iPosition - i >= 0 && i <= 2 && jPosition - i >= 0; i++){calculoDanio(attack, true, board, e, iPosition - i, jPosition - i, quantity);}
            for(int i = 1; iPosition - i >= 0 && i <= 2; i++){calculoDanio(attack, true, board, e, iPosition - i, jPosition, quantity);}
            for(int i = 1; iPosition - i >= 0 && i <= 2 && jPosition + i < column; i++){calculoDanio(attack, true, board, e, iPosition - i, jPosition + i, quantity);}
            for(int i = 1; jPosition + i < column && i <= 2 ; i++){calculoDanio(attack, true, board, e, iPosition, jPosition + i, quantity);}
            for(int i = 1; iPosition + i < row && i <= 2 && jPosition + i < column; i++){calculoDanio(attack, true, board, e, iPosition + i, jPosition + i, quantity);}
            for(int i = 1; iPosition + i < row && i <= 2 ; i++){calculoDanio(attack, true, board, e, iPosition + i, jPosition, quantity);}
            for(int i = 1; iPosition + i < row && i <= 2 && jPosition - i >= 0; i++){calculoDanio(attack, true, board, e, iPosition + i, jPosition - i, quantity);}
            for(int i = 1; jPosition - i >= 0 && i <= 2; i++){calculoDanio(attack, true, board, e, iPosition, jPosition - i, quantity);}   
    }
    void DisparoLongevo(int row, int column, char board[500][500], Enemy e[1000], int quantity){
        switch(direction){
                case 1:
                for(int i = 1; iPosition - i >= 0; i++){
                    if(board[iPosition - i][jPosition] == 'E'){ 
                        calculoDanio(attack * 4, true, board, e, iPosition - i, jPosition, quantity);
                        break; 
                    }
                }
                break;
                case 2:
                for(int i = 1; jPosition + i < column; i++){
                    if(board[iPosition][jPosition + i] == 'E'){ 
                        calculoDanio(attack * 4, true, board, e, iPosition, jPosition + i, quantity); 
                        break;
                    }
                }
                break;
                case 3:
                for(int i = 1; iPosition + i < row; i++){
                    if(board[iPosition + i][jPosition] == 'E'){
                        calculoDanio(attack * 4, true, board, e, iPosition + i, jPosition, quantity); 
                        break;
                    }
                }
                break;
                case 4:
                for(int i = 1; jPosition - i >= 0; i++){
                    if(board[iPosition][jPosition - i] == 'E'){ 
                        calculoDanio(attack * 4, true, board, e, iPosition, jPosition - i, quantity);
                        break;
                    }
                }
                break;
            }
    }
    void Voltereta(int row, int column, char board[500][500], Enemy e[1000], int quantity){
        int x = iPosition, y = jPosition;

        switch(direction){
                case 1:
                    if(x - 1 >= 0 && y - 1 >= 0){if(board[x - 1][y - 1] == 'E'){calculoDanio(attack, true, board, e, x - 1, y - 1, quantity);}}
                    if(x - 1 >= 0){if(board[x - 1][y] == 'E'){calculoDanio(attack, true, board, e, x - 1, y, quantity);}}
                    if(x - 1 >= 0 && y + 1 < column){if(board[x - 1][y + 1] == 'E'){calculoDanio(attack, true, board, e, x - 1, y + 1, quantity);}}

                    if(iPosition + 1 < row){
                        if(board[iPosition + 1][jPosition] == '_'){
                            board[iPosition][jPosition] = '_';
                            iPosition += 1;
                            board[iPosition][jPosition] = 'A';
                        }   
                    }
                break;
                case 2:
                    if(x - 1 >= 0 && y + 1 < column){if(board[x - 1][y + 1] == 'E'){calculoDanio(attack, true, board, e, x - 1, y + 1, quantity);}}
                    if(y + 1 < column){if(board[x][y + 1] == 'E'){calculoDanio(attack, true, board, e, x, y + 1, quantity);}}
                    if(x + 1 < row && y + 1 < column){if(board[x + 1][y + 1] == 'E'){calculoDanio(attack, true, board, e, x + 1, y + 1, quantity);}}
                

                    if(jPosition - 1 >= 0){
                        if(board[iPosition][jPosition - 1] == '_'){
                            board[iPosition][jPosition - 1] = 'A';
                            board[iPosition][jPosition] = '_';
                            jPosition -= 1;
                        }   
                    }
                break;
                case 3:
                    if(x + 1 < row && y - 1 >= 0){if(board[x + 1][y - 1] == 'E'){calculoDanio(attack, true, board, e, x + 1, y - 1, quantity);}}
                    if(x + 1 < row){if(board[x + 1][y] == 'E'){calculoDanio(attack, true, board, e, x - 1, y, quantity);}}
                    if(x + 1 < row && y + 1 < column){if(board[x + 1][y + 1] == 'E'){calculoDanio(attack, true, board, e, x + 1, y + 1, quantity);}}
                
                    if(iPosition - 1 >= 0){
                        if(board[iPosition - 1][jPosition] == '_'){
                            board[iPosition - 1][jPosition] = 'A';
                            board[iPosition][jPosition] = '_';
                            iPosition -= 1;
                        }   
                    }
                break;
                case 4:
                    if(x - 1 >= 0 && y - 1 >= 0){if(board[x - 1][y - 1] == 'E'){calculoDanio(attack, true, board, e, x - 1, y - 1, quantity);}}
                    if(y - 1 >= 0){if(board[x][y - 1] == 'E'){calculoDanio(attack, true, board, e, x, y - 1, quantity);}}
                    if(x + 1 < row && y - 1 >= 0){if(board[x + 1][y - 1] == 'E'){calculoDanio(attack, true, board, e, x + 1, y - 1, quantity);}}

                    if(jPosition + 1 < column){
                        if(board[iPosition][jPosition + 1] == '_'){
                            board[iPosition][jPosition + 1] = 'A';
                            board[iPosition][jPosition] = '_';
                            jPosition += 1;
                        }   
                    }
                    
                break;
            }
    }
    ~Archer(){}
};
void CuracionG(int healing, char board[500][500], Warrior g[100], int FE, int CE, int quantity);
void CuracionK(int healing, char board[500][500], Healer k[100], int FE, int CE, int quantity);
void CuracionM(int healing, char board[500][500], Wizard m[100], int FE, int CE, int quantity);
void CuracionA(int healing, char board[500][500], Archer a[100], int FE, int CE, int quantity);
class HealerCopy:public Healer{
public:
    HealerCopy(){}
    void NovaDeLuz(int row, int column, char board[500][500], Warrior G[100], Healer K[100], Wizard M[100], Archer A[100], Enemy e[1000], int quantity, int quantityG, int quantityK, int quantityM, int quantityA){
        int contAliados = 1;
        int x = iPosition, y = jPosition, i = 1;

        if(board[x - i][y - i] == 'G' && x - i >= 0 && y - i >= 0){contAliados++;}
        if(board[x - i][y - i] == 'K' && x - i >= 0 && y - i >= 0){contAliados++;}
        if(board[x - i][y - i] == 'M' && x - i >= 0 && y - i >= 0){contAliados++;}
        if(board[x - i][y - i] == 'A' && x - i >= 0 && y - i >= 0){contAliados++;}

        if(board[x - i][y] == 'G' && x - i >= 0){contAliados++;}
        if(board[x - i][y] == 'K' && x - i >= 0){contAliados++;}
        if(board[x - i][y] == 'M' && x - i >= 0){contAliados++;}
        if(board[x - i][y] == 'A' && x - i >= 0){contAliados++;}

        if(board[x - i][y + i] == 'G' && x - i >= 0 && y + i < column){contAliados++;}
        if(board[x - i][y + i] == 'K' && x - i >= 0 && y + i < column){contAliados++;}
        if(board[x - i][y + i] == 'M' && x - i >= 0 && y + i < column){contAliados++;}
        if(board[x - i][y + i] == 'A' && x - i >= 0 && y + i < column){contAliados++;}

        if(board[x][y + i] == 'G' && y + i < column){contAliados++;}
        if(board[x][y + i] == 'K' && y + i < column){contAliados++;}
        if(board[x][y + i] == 'M' && y + i < column){contAliados++;}
        if(board[x][y + i] == 'A' && y + i < column){contAliados++;}

        if(board[x + i][y + i] == 'G'&& x + i < row && y + i < column){contAliados++;}
        if(board[x + i][y + i] == 'K'&& x + i < row && y + i < column){contAliados++;}
        if(board[x + i][y + i] == 'M'&& x + i < row && y + i < column){contAliados++;}
        if(board[x + i][y + i] == 'A'&& x + i < row && y + i < column){contAliados++;}

        if(board[x + i][y] == 'G' && x + i < row){contAliados++;}
        if(board[x + i][y] == 'K' && x + i < row){contAliados++;}
        if(board[x + i][y] == 'M' && x + i < row){contAliados++;}
        if(board[x + i][y] == 'A' && x + i < row){contAliados++;}

        if(board[x + i][y - i] == 'G' && x + i < row && y - i >= 0){contAliados++;}
        if(board[x + i][y - i] == 'K' && x + i < row && y - i >= 0){contAliados++;}
        if(board[x + i][y - i] == 'M' && x + i < row && y - i >= 0){contAliados++;}
        if(board[x + i][y - i] == 'A' && x + i < row && y - i >= 0){contAliados++;}
        
        if(board[x][y - i] == 'G' && y - i >= 0){contAliados++;}
        if(board[x][y - i] == 'K' && y - i >= 0){contAliados++;}
        if(board[x][y - i] == 'M' && y - i >= 0){contAliados++;}
        if(board[x][y - i] == 'A' && y - i >= 0){contAliados++;}
   
        if(board[x - i][y - i] == 'G' && x - i >= 0 && y - i >= 0){CuracionG( 3 + contAliados, board, G, iPosition - i, jPosition - i, quantityG);}
        if(board[x - i][y - i] == 'K' && x - i >= 0 && y - i >= 0){CuracionK( 3 + contAliados, board, K, iPosition - i, jPosition - i, quantityK);}
        if(board[x - i][y - i] == 'M' && x - i >= 0 && y - i >= 0){CuracionM( 3 + contAliados, board, M, iPosition - i, jPosition - i, quantityM);}
        if(board[x - i][y - i] == 'A' && x - i >= 0 && y - i >= 0){CuracionA( 3 + contAliados, board, A, iPosition - i, jPosition - i, quantityA);}

        if(board[x - i][y] == 'G' && x - i >= 0){CuracionG( 3 + contAliados, board, G, iPosition - i, jPosition, quantityG);}
        if(board[x - i][y] == 'K' && x - i >= 0){CuracionK( 3 + contAliados, board, K, iPosition - i, jPosition, quantityK);}
        if(board[x - i][y] == 'M' && x - i >= 0){CuracionM( 3 + contAliados, board, M, iPosition - i, jPosition, quantityM);}
        if(board[x - i][y] == 'A' && x - i >= 0){CuracionA( 3 + contAliados, board, A, iPosition - i, jPosition, quantityA);}

        if(board[x - i][y + i] == 'G' && x - i >= 0 && y + i < column){CuracionG( 3 + contAliados, board, G, iPosition - i, jPosition + i, quantityG);}
        if(board[x - i][y + i] == 'K' && x - i >= 0 && y + i < column){CuracionK( 3 + contAliados, board, K, iPosition - i, jPosition + i, quantityK);}
        if(board[x - i][y + i] == 'M' && x - i >= 0 && y + i < column){CuracionM( 3 + contAliados, board, M, iPosition - i, jPosition + i, quantityM);}
        if(board[x - i][y + i] == 'A' && x - i >= 0 && y + i < column){CuracionA( 3 + contAliados, board, A, iPosition - i, jPosition + i, quantityA);}

        if(board[x][y + i] == 'G' && y + i < column){CuracionG( 3 + contAliados, board, G, iPosition, jPosition + i, quantityG);}
        if(board[x][y + i] == 'K' && y + i < column){CuracionK( 3 + contAliados, board, K, iPosition, jPosition + i, quantityK);}
        if(board[x][y + i] == 'M' && y + i < column){CuracionM( 3 + contAliados, board, M, iPosition, jPosition + i, quantityM);}
        if(board[x][y + i] == 'A' && y + i < column){CuracionA( 3 + contAliados, board, A, iPosition, jPosition + i, quantityA);}

        if(board[x + i][y + i] == 'G'&& x + i < row && y + i < column){CuracionG( 3 + contAliados, board, G, iPosition + i, jPosition + i, quantityG);}
        if(board[x + i][y + i] == 'K'&& x + i < row && y + i < column){CuracionK( 3 + contAliados, board, K, iPosition + i, jPosition + i, quantityK);}
        if(board[x + i][y + i] == 'M'&& x + i < row && y + i < column){CuracionM( 3 + contAliados, board, M, iPosition + i, jPosition + i, quantityM);}
        if(board[x + i][y + i] == 'A'&& x + i < row && y + i < column){CuracionA( 3 + contAliados, board, A, iPosition + i, jPosition + i, quantityA);}

        if(board[x + i][y] == 'G' && x + i < row){CuracionG( 3 + contAliados, board, G, iPosition + i, jPosition, quantityG);}
        if(board[x + i][y] == 'K' && x + i < row){CuracionK( 3 + contAliados, board, K, iPosition + i, jPosition, quantityK);}
        if(board[x + i][y] == 'M' && x + i < row){CuracionM( 3 + contAliados, board, M, iPosition + i, jPosition, quantityM);}
        if(board[x + i][y] == 'A' && x + i < row){CuracionA( 3 + contAliados, board, A, iPosition + i, jPosition, quantityA);}

        if(board[x + i][y - i] == 'G' && x + i < row && y - i >= 0){CuracionG( 3 + contAliados, board, G, iPosition + i, jPosition - i, quantityG);}
        if(board[x + i][y - i] == 'K' && x + i < row && y - i >= 0){CuracionK( 3 + contAliados, board, K, iPosition + i, jPosition - i, quantityK);}
        if(board[x + i][y - i] == 'M' && x + i < row && y - i >= 0){CuracionM( 3 + contAliados, board, M, iPosition + i, jPosition - i, quantityM);}
        if(board[x + i][y - i] == 'A' && x + i < row && y - i >= 0){CuracionA( 3 + contAliados, board, A, iPosition + i, jPosition - i, quantityA);}
        
        if(board[x][y - i] == 'G' && y - i >= 0){CuracionG( 3 + contAliados, board, G, iPosition, jPosition - i, quantityG);}
        if(board[x][y - i] == 'K' && y - i >= 0){CuracionK( 3 + contAliados, board, K, iPosition, jPosition - i, quantityK);}
        if(board[x][y - i] == 'M' && y - i >= 0){CuracionM( 3 + contAliados, board, M, iPosition, jPosition - i, quantityM);}
        if(board[x][y - i] == 'A' && y - i >= 0){CuracionA( 3 + contAliados, board, A, iPosition, jPosition - i, quantityA);}

        if(board[x][y] == 'K'){CuracionK( 3 + contAliados, board, K, iPosition, jPosition, quantityK);}         

        //Danos

        for(int i = 1; iPosition - i >= 0 && i <= 1 && jPosition - i >= 0; i++){calculoDanio(2, false, board, e, iPosition - i, jPosition - i, quantity);}
        for(int i = 1; iPosition - i >= 0 && i <= 1; i++){calculoDanio(2, false, board, e, iPosition - i, jPosition, quantity);}
        for(int i = 1; iPosition - i >= 0 && i <= 1 && jPosition + i < column; i++){calculoDanio(2, false, board, e, iPosition - i, jPosition + i, quantity);}
        for(int i = 1; jPosition + i < column && i <= 1 ; i++){calculoDanio(2, false, board, e, iPosition, jPosition + i, quantity);}
        for(int i = 1; iPosition + i < row && i <= 1 && jPosition + i < column; i++){calculoDanio(2, false, board, e, iPosition + i, jPosition + i, quantity);}
        for(int i = 1; iPosition + i < row && i <= 1 ; i++){calculoDanio(2, false, board, e, iPosition + i, jPosition, quantity);}
        for(int i = 1; iPosition + i < row && i <= 1 && jPosition - i >= 0; i++){calculoDanio(2, false, board, e, iPosition + i, jPosition - i, quantity);}
        for(int i = 1; jPosition - i >= 0 && i <= 1; i++){calculoDanio(2, false, board, e, iPosition, jPosition - i, quantity);}
    }
    void ImpactoSagrado(char board[500][500], Warrior g[100], Healer k[100], Wizard m[100], Archer a[100], Enemy e[100], ifstream &entrada, int quantityG, int quantityK, int quantityM, int quantityA, int quantityE){
        int x = 0, y = 0;
        entrada >> y;
        entrada >> x;

        if(x == iPosition && y == jPosition){
             if(hp + 4 + attack > hpMax){
                hp = hpMax;
            }
            else {hp += 4 + attack;}
        }
        else if(board[x][y] == 'G'){ CuracionG( 4 + attack, board, g, x, y, quantityG);}
        else if(board[x][y] == 'K'){ CuracionK( 4 + attack, board, k, x, y, quantityK);}
        else if(board[x][y] == 'M'){ CuracionM( 4 + attack, board, m, x, y, quantityM);}
        else if (board[x][y] == 'A'){ CuracionA(4 + attack, board, a, x, y, quantityA);}
        else if(board[x][y] == 'E'){ calculoDanio( 2 + attack, false, board, e, x, y, quantityE);}
        
    }
    void LuzSagrada(char board[500][500], Warrior g[100], Healer k[100], Wizard m[100], Archer a[100], ifstream &entrada, int quantityG, int quantityK, int quantityM, int quantityA){
        int x = 0, y = 0;
        entrada >> y;
        entrada >> x;

        if(x == iPosition && y == jPosition){
             if(hp + 8 + attack > hpMax){
                hp = hpMax;
            }
            else {hp += 8 + attack;}
        }
        else if(board[x][y] == 'G'){ CuracionG( 8 + attack, board, g, x, y, quantityG);}
        else if(board[x][y] == 'K'){ CuracionK( 8 + attack, board, k, x, y, quantityK);}
        else if(board[x][y] == 'M'){ CuracionM( 8 + attack, board, m, x, y, quantityM);}
        else if(board[x][y] == 'A'){ CuracionA( 8 + attack, board, a, x, y, quantityA);}
    }
    ~HealerCopy(){}
};
void calculoDanioG(int attack, char board[500][500], Warrior g[100], int FE, int CE, int quantity);
void calculoDanioK(int attack, char board[500][500], Healer k[100], int FE, int CE, int quantity);
void calculoDanioM(int damage, char board[500][500], Wizard m[100], int FE, int CE, int quantity);
void calculoDanioA(int damage, char board[500][500], Archer a[100], int FE, int CE, int quantity);
class EnemyCopy: public Enemy{
    public:

        EnemyCopy(){}
        void DisparoLongevoE(int row, int column, char board[500][500], Warrior G[100], Healer K[100], Wizard M[100], Archer A[100], int quantityG, int quantityK, int quantityM, int quantityA){
            switch(direction){
                case 1:
                for(int i = 0; iPosition - i >= 0; i++){
                    if(board[iPosition - i][jPosition] == 'G'){ 
                        calculoDanioG(attack * 4, board, G, iPosition - i, jPosition, quantityG);
                        break; 
                    }
                    if(board[iPosition - i][jPosition] == 'K'){ 
                        calculoDanioK(attack * 4, board, K, iPosition - i, jPosition, quantityK);
                        break; 
                    }
                    if(board[iPosition - i][jPosition] == 'M'){ 
                        calculoDanioM(attack * 4, board, M, iPosition - i, jPosition, quantityM);
                        break; 
                    }
                    if(board[iPosition - i][jPosition] == 'A'){ 
                        calculoDanioA(attack * 4, board, A, iPosition - i, jPosition, quantityA);
                        break; 
                    }
                }
                break;
                case 2:
                for(int i = 0; jPosition + i < column; i++){
                    if(board[iPosition][jPosition + i] == 'G'){ 
                        calculoDanioG(attack * 4, board, G, iPosition, jPosition + i, quantityG); 
                        break;
                    }
                    if(board[iPosition][jPosition + i] == 'K'){ 
                        calculoDanioK(attack * 4, board, K, iPosition, jPosition + i, quantityK); 
                        break;
                    }
                    if(board[iPosition][jPosition + i] == 'M'){ 
                        calculoDanioM(attack * 4, board, M, iPosition, jPosition + i, quantityM); 
                        break;
                    }
                    if(board[iPosition][jPosition + i] == 'A'){ 
                        calculoDanioA(attack * 4, board, A, iPosition, jPosition + i, quantityA); 
                        break;
                    }
                }
                break;
                case 3:
                for(int i = 0; iPosition + i < row; i++){
                    if(board[iPosition + i][jPosition] == 'G'){
                        calculoDanioG(attack * 4, board, G, iPosition + i, jPosition, quantityG); 
                        break;
                    }
                    if(board[iPosition + i][jPosition] == 'K'){
                        calculoDanioK(attack * 4, board, K, iPosition + i, jPosition, quantityK); 
                        break;
                    }
                    if(board[iPosition + i][jPosition] == 'M'){
                        calculoDanioM(attack * 4, board, M, iPosition + i, jPosition, quantityM); 
                        break;
                    }
                    if(board[iPosition + i][jPosition] == 'A'){
                        calculoDanioA(attack * 4, board, A, iPosition + i, jPosition, quantityA); 
                        break;
                    }
                }
                break;
                case 4:
                for(int i = 0; jPosition - i >= 0; i++){
                    if(board[iPosition][jPosition - i] == 'G'){ 
                        calculoDanioG(attack * 4, board, G, iPosition, jPosition - i, quantityG); 
                        break;
                    }
                    if(board[iPosition][jPosition - i] == 'K'){ 
                        calculoDanioK(attack * 4, board, K, iPosition, jPosition - i, quantityK); 
                        break;
                    }

                    if(board[iPosition][jPosition - i] == 'M'){ 
                        calculoDanioM(attack * 4, board, M, iPosition, jPosition - i, quantityM); 
                        break;
                    }
                    if(board[iPosition][jPosition - i] == 'A'){
                        calculoDanioA(attack * 4, board, A, iPosition, jPosition - i, quantityA); 
                        break;
                    }
                }
                break;
            }
        }               
        void TpE(int row, int column, char board[500][500]){
        
        switch(direction){

            case 1:

            if(iPosition - 2 >= 0){

                if(board[iPosition - 2][jPosition] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition - 2][jPosition] = 'E';
                    iPosition -= 2;
                }
                else if(board[iPosition - 1][jPosition]){

                    board[iPosition][jPosition] = '_';
                    board[iPosition - 1][jPosition] = 'E';
                    iPosition -= 1;
                }
            }
            else if(iPosition - 1 >= 0){

                board[iPosition][jPosition] = '_';
                board[iPosition - 1][jPosition] = 'E';
                iPosition -= 1;
            }
            break;
            case 2:

            if(jPosition + 2 < column){

                if(board[iPosition][jPosition + 2] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition + 2] = 'E';
                    jPosition += 2;
                }
                else if(board[iPosition][jPosition + 1]){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition + 1] = 'E';
                    jPosition += 1;
                }
            }
            else if(jPosition + 1 < column){

                board[iPosition][jPosition] = '_';
                board[iPosition][jPosition + 1] = 'E';
                jPosition += 1;
            }
            break;
            case 3:

            if(iPosition + 2 < row){

                if(board[iPosition + 2][jPosition] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition + 2][jPosition] = 'E';
                    iPosition += 2;
                }
                else if(board[iPosition + 1][jPosition]){

                    board[iPosition][jPosition] = '_';
                    board[iPosition + 1][jPosition] = 'E';
                    iPosition += 1;
                }
            }
            else if(iPosition + 1 < row){

                board[iPosition][jPosition] = '_';
                board[iPosition + 1][jPosition] = 'E';
                iPosition += 1;
            }
            break;
            case 4:

            if(jPosition - 2 >= 0){

                if(board[iPosition][jPosition - 2] == '_'){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition - 2] = 'E';
                    jPosition -= 2;
                }
                else if(board[iPosition][jPosition - 1]){

                    board[iPosition][jPosition] = '_';
                    board[iPosition][jPosition - 1] = 'E';
                    jPosition -= 1;
                }
            }
            else if(jPosition - 1 >= 0){

                board[iPosition][jPosition] = '_';
                board[iPosition][jPosition - 1] = 'E';
                jPosition -= 1;
            }
            break;
        }
    }
        void TorbellinoE(int row, int column, char board[500][500], Warrior G[100], Healer K[100], Wizard M[100], Archer A[100], int quantityG, int quantityK, int quantityM, int quantityA){
            int contEnemigos = 0;
            int x = iPosition, y = jPosition;

            if(x - 1 >= 0){if(board[x - 1][y] == 'G'){contEnemigos++;}}
            if(y + 1 < column){if(board[x][y + 1] == 'G'){contEnemigos++;}}
            if(x + 1 < row){if(board[x + 1][y] == 'G'){contEnemigos++;}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'G'){contEnemigos++;}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'K'){contEnemigos++;}}
            if(y + 1 < column){if(board[x][y + 1] == 'K'){contEnemigos++;}}
            if(x + 1 < row){if(board[x + 1][y] == 'K'){contEnemigos++;}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'K'){contEnemigos++;}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'M'){contEnemigos++;}}
            if(y + 1 < column){if(board[x][y + 1] == 'M'){contEnemigos++;}}
            if(x + 1 < row){if(board[x + 1][y] == 'M'){contEnemigos++;}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'M'){contEnemigos++;}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'A'){contEnemigos++;}}
            if(y + 1 < column){if(board[x][y + 1] == 'A'){contEnemigos++;}}
            if(x + 1 < row){if(board[x + 1][y] == 'A'){contEnemigos++;}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'A'){contEnemigos++;}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'G'){calculoDanioG((attack + 1) * contEnemigos, board, G, iPosition - 1, jPosition, quantityG);}}
            if(y + 1 < column){if(board[x][y + 1] == 'G'){calculoDanioG((attack + 1) * contEnemigos, board, G, iPosition, jPosition + 1, quantityG);}}
            if(x + 1 < row){if(board[x + 1][y] == 'G'){calculoDanioG((attack + 1) * contEnemigos, board, G, iPosition + 1, jPosition, quantityG);}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'G'){calculoDanioG((attack + 1) * contEnemigos, board, G, iPosition, jPosition - 1, quantityG);}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'K'){calculoDanioK((attack + 1) * contEnemigos, board, K, iPosition - 1, jPosition, quantityK);}}
            if(y + 1 < column){if(board[x][y + 1] == 'K'){calculoDanioK((attack + 1) * contEnemigos, board, K, iPosition, jPosition + 1, quantityK);}}
            if(x + 1 < row){if(board[x + 1][y] == 'K'){calculoDanioK((attack + 1) * contEnemigos, board, K, iPosition + 1, jPosition, quantityK);}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'K'){calculoDanioK((attack + 1) * contEnemigos, board, K, iPosition, jPosition - 1, quantityK);}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'M'){calculoDanioM((attack + 1) * contEnemigos, board, M, iPosition - 1, jPosition, quantityM);}}
            if(y + 1 < column){if(board[x][y + 1] == 'M'){calculoDanioM((attack + 1) * contEnemigos, board, M, iPosition, jPosition + 1, quantityM);}}
            if(x + 1 < row){if(board[x + 1][y] == 'M'){calculoDanioM((attack + 1) * contEnemigos, board, M, iPosition + 1, jPosition, quantityM);}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'M'){calculoDanioM((attack + 1) * contEnemigos, board, M, iPosition, jPosition - 1, quantityM);}}

            if(x - 1 >= 0){if(board[x - 1][y] == 'A'){calculoDanioA((attack + 1) * contEnemigos, board, A, iPosition - 1, jPosition, quantityA);}}
            if(y + 1 < column){if(board[x][y + 1] == 'A'){calculoDanioA((attack + 1) * contEnemigos, board, A, iPosition, jPosition + 1, quantityA);}}
            if(x + 1 < row){if(board[x + 1][y] == 'A'){calculoDanioA((attack + 1) * contEnemigos, board, A, iPosition + 1, jPosition, quantityA);}}
            if(y - 1 >= 0){if(board[x][y - 1] == 'A'){calculoDanioA((attack + 1) * contEnemigos, board, A, iPosition, jPosition - 1, quantityA);}}

        }
    ~EnemyCopy(){}
};
void calculoDanio(int damage, bool physical, char board[500][500], Enemy e[1000], int FE, int CE, int quantity){
    if(physical){
        for(int i = 0; i < quantity; i++){
            if(e[i].iPosition == FE && e[i].jPosition == CE && e[i].hp > 0){
                if(e[i].armor < damage && e[i].hp > 0){ 
                    e[i].hp = e[i].hp  + e[i].armor - damage;
                }
            }
            if(e[i].hp <= 0){ board[e[i].iPosition][e[i].jPosition] = '_'; }
        }
    }else {
        for(int i = 0; i < quantity; i++){
            if(e[i].iPosition == FE && e[i].jPosition == CE && e[i].hp > 0){
                if(e[i].Mresistence < damage && e[i].hp > 0){
                    e[i].hp = e[i].hp + e[i].Mresistence - damage;
                }
            }
            if(e[i].hp <= 0){ board[e[i].iPosition][e[i].jPosition] = '_'; }
        }
    }
}
void calculoDanioG(int damage, char board[500][500], Warrior g[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(g[i].iPosition == FE && g[i].jPosition == CE && g[i].hp > 0){
            if(g[i].armor < damage && g[i].hp > 0){ 
                g[i].hp = g[i].hp  + g[i].armor - damage;
            }
        }
        if(g[i].hp <= 0){ 
            board[g[i].iPosition][g[i].jPosition] = '_'; }
    }
}
void calculoDanioK(int damage, char board[500][500], Healer k[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(k[i].iPosition == FE && k[i].jPosition == CE && k[i].hp > 0){
            if(k[i].armor < damage && k[i].hp > 0){ 
                k[i].hp = k[i].hp  + k[i].armor - damage;
            }
        }
        if(k[i].hp <= 0){ board[k[i].iPosition][k[i].jPosition] = '_'; }
    }
}
void calculoDanioM(int damage, char board[500][500], Wizard m[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(m[i].iPosition == FE && m[i].jPosition == CE && m[i].hp > 0){
            if(m[i].armor < damage && m[i].hp > 0){ 
                m[i].hp = m[i].hp  + m[i].armor - damage;
            }
        }
        if(m[i].hp <= 0){ board[m[i].iPosition][m[i].jPosition] = '_'; }
    }
}
void calculoDanioA(int damage, char board[500][500], Archer a[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(a[i].iPosition == FE && a[i].jPosition == CE && a[i].hp > 0){
            if(a[i].armor < damage && a[i].hp > 0){ 
                a[i].hp = a[i].hp  + a[i].armor - damage;
            }
        }
        if(a[i].hp <= 0){ board[a[i].iPosition][a[i].jPosition] = '_'; }
    }
}
void CuracionG(int healing, char board[500][500], Warrior g[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(g[i].iPosition == FE && g[i].jPosition == CE && g[i].hp > 0){
            if(g[i].hp + healing < g[i].hpMax && g[i].hp > 0){
                g[i].hp += healing;
            }
            else if(g[i].hp > 0) {g[i].hp = g[i].hpMax;;}
        }
    }
}
void CuracionK(int healing, char board[500][500], Healer k[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(k[i].iPosition == FE && k[i].jPosition == CE && k[i].hp > 0){
            if(k[i].hp + healing < k[i].hpMax && k[i].hp > 0){
                k[i].hp += healing;
            }
            else if(k[i].hp > 0){k[i].hp = k[i].hpMax;}
        }   
    }
}
void CuracionM(int healing, char board[500][500], Wizard m[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(m[i].iPosition == FE && m[i].jPosition == CE && m[i].hp > 0){
            if(m[i].hp + healing < m[i].hpMax && m[i].hp > 0){
                m[i].hp += healing;
            }
            else if(m[i].hp > 0) {m[i].hp = m[i].hpMax;}
        }
    }
}
void CuracionA(int healing, char board[500][500], Archer a[100], int FE, int CE, int quantity){
    for(int i = 0; i < quantity; i++){
        if(a[i].iPosition == FE && a[i].jPosition == CE && a[i].hp > 0){
            if(a[i].hp + healing < a[i].hpMax && a[i].hp > 0){
                a[i].hp += healing;
            }
            else if(a[i].hp > 0) {a[i].hp = a[i].hpMax;}
        }
    }
}
void FillBoard(int row, int column, char board[500][500], ifstream &entrada){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            entrada >> board[i][j];
        }
    }
}
void PrintBoard(int row, int column, char board[500][500], ofstream &salida){ 
    for(int i = 0; i < row; i++){  
        for(int j = 0; j < column; j++){
            salida << board[i][j];
        }
        salida << endl;
    }

}
int main(int argc, char *argv[]){

    ifstream entrada;
    ofstream salida;
    int iteraciones = 0;

    entrada.open(argv[1]);
    salida.open(argv[2]);

    int row = 0, column = 0, aux = 0;

    entrada >> row;
    entrada >> column;

    char board[500][500];
    FillBoard(row, column, board, entrada);

    int quantityG = CharacterQuantity(row, column, board, 'G');
    int quantityK = CharacterQuantity(row, column, board, 'K');
    int quantityM = CharacterQuantity(row, column, board, 'M');
    int quantityA = CharacterQuantity(row, column, board, 'A');
    int quantityE = CharacterQuantity(row, column, board, 'E');

    Warrior G[100];
    Healer K[100];
    Wizard M[100];
    Archer A[100];
    Enemy E[1000];
    HealerCopy H[quantityK];
    EnemyCopy Enemigo[quantityE];

    for(int i = 0; i < quantityG; i++){ G[i].AskAttributes(entrada); }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == 'G'){
                if(aux - 1 < 0){
                    G[aux].changeCoordinates(G[aux].iPosition, G[aux].jPosition, i, j);
                    aux++;
                }
                else{
                    G[aux].changeCoordinates(G[aux].iPosition, G[aux].jPosition, i, j);
                    aux++;
                }   
            }
        }
    }

    aux = 0;

    //--------------------------------------------------------------------------
    
    for(int i = 0; i < quantityK; i++){ K[i].AskAttributes(entrada); }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == 'K'){
                if(aux - 1 < 0){
                    K[aux].changeCoordinates(K[aux].iPosition, K[aux].jPosition, i, j);
                    aux++;
                }
                else{
                    K[aux].changeCoordinates(K[aux].iPosition, K[aux].jPosition, i, j);
                    aux++;
                }   
            }
        }
    }

    aux = 0;
    //--------------------------------------------------------------------------
    
    for(int i = 0; i < quantityM; i++){ M[i].AskAttributes(entrada); }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == 'M'){
                if(aux - 1 < 0){
                    M[aux].changeCoordinates(M[aux].iPosition, M[aux].jPosition, i, j);
                    aux++;
                }
                else{
                    M[aux].changeCoordinates(M[aux].iPosition, M[aux].jPosition, i, j);
                    aux++;
                }   
            }
        }
    }

    aux = 0;
    //--------------------------------------------------------------------------

    for(int i = 0; i < quantityA; i++){ A[i].AskAttributes(entrada); }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == 'A'){
                if(aux - 1 < 0){
                    A[aux].changeCoordinates(A[aux].iPosition, A[aux].jPosition, i, j);
                    aux++;
                }
                else{
                    A[aux].changeCoordinates(A[aux].iPosition, A[aux].jPosition, i, j);
                    aux++;
                }   
            }
        }
    }

    aux = 0;
    //--------------------------------------------------------------------------

    for(int i = 0; i < quantityE; i++){ E[i].AskAttributes(entrada); }
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(board[i][j] == 'E'){
                if(aux - 1 < 0){
                    E[aux].changeCoordinates(E[aux].iPosition, E[aux].jPosition, i, j);
                    aux++;
                }
                else{
                    E[aux].changeCoordinates(E[aux].iPosition, E[aux].jPosition, i, j);
                    aux++;
                }   
            }
        }
    }
    aux = 0;

    entrada >> iteraciones;
    //---Warrior---------------------------------------------------------------------
    for(int i = 1; i <= iteraciones; i++){

        for(int i = 0; i < quantityG; i++){
            G[i].AskDirectionAndMovement(entrada);
            if(G[i].hp > 0){ 
                G[i].AskMovement(row,column, board, 'G'); 
                switch(G[i].ability){
                    case 1:
                        G[i].Quebrajar(row, column, board, E, quantityE); 
                    break;
                    case 2:
                        G[i].Estocada(row, column, board, E, quantityE);
                    break;
                    case 3:
                        G[i].Torbellino(row, column, board, E, quantityE);
                    break;
                }  
            } 
        }


        //---Healer---------------------------------------------------------------------

        for(int i = 0; i < quantityK; i++){
            H[i].hp = K[i].hp;
            H[i].attack = K[i].attack;
            H[i].armor = K[i].armor;
            H[i].Mresistence = K[i].Mresistence;
            H[i].iPosition = K[i].iPosition;
            H[i].jPosition = K[i].jPosition;
            H[i].AskDirectionAndMovement(entrada);

            if(H[i].hp > 0){
                H[i].AskMovement(row,column, board, 'K');
                switch(H[i].ability){
                    case 1:
                        H[i].NovaDeLuz(row, column, board, G, K, M, A, E, quantityE, quantityG, quantityK, quantityM, quantityA);
                    break;
                    case 2:
                        H[i].ImpactoSagrado(board, G, K, M, A, E, entrada, quantityG, quantityK, quantityM, quantityA, quantityE);
                    break;
                    case 3:
                        H[i].LuzSagrada(board, G, K, M, A, entrada, quantityG, quantityK, quantityM, quantityA);
                    break;
                } 
            }
            K[i].iPosition = H[i].iPosition;
            K[i].jPosition = H[i].jPosition;
        }
        
        //---Wizard----------------------------------------------------------------------
        
        for(int i = 0; i < quantityM; i++){
            M[i].AskDirectionAndMovement(entrada);
            if(M[i].hp > 0){ 
                M[i].AskMovement(row,column, board, 'M'); 
                switch(M[i].ability){
                    case 1:
                        M[i].Tp(row, column, board); 
                    break;
                    case 2:
                        M[i].EsferaDeHielo(board, E, entrada, quantityE);
                    break;
                    case 3:
                        M[i].Tempestad(row, column, board, E, entrada, quantityE);
                    break;
                } 
            }

        }
    //-------Archer----------------------------------------------------------------
        
        for(int i = 0; i < quantityA; i++){
            A[i].AskDirectionAndMovement(entrada);
            if(A[i].hp > 0){ 
                A[i].AskMovement(row,column, board, 'A'); 
                switch(A[i].ability){
                    case 1:
                        A[i].Multidisparo(row, column, board, E, quantityE); 
                    break;
                    case 2:
                        A[i].DisparoLongevo(row, column, board, E, quantityE);
                    break;
                    case 3:
                        A[i].Voltereta(row, column, board, E, quantityE);
                    break;
                } 
            }
        }

    //--------Enemy--------------------------------------------------------------
        for(int i = 0; i < quantityE; i++){
            Enemigo[i].hp = E[i].hp;
            Enemigo[i].attack = E[i].attack;
            Enemigo[i].armor = E[i].armor;
            Enemigo[i].Mresistence = E[i].Mresistence;
            Enemigo[i].iPosition = E[i].iPosition;
            Enemigo[i].jPosition = E[i].jPosition;
            Enemigo[i].AskDirectionAndMovement(entrada);
            if(Enemigo[i].hp > 0){ 
                Enemigo[i].AskMovement(row,column, board, 'E');
                switch(Enemigo[i].ability){
                    case 1:
                        Enemigo[i].DisparoLongevoE(row, column, board, G, K, M, A, quantityG, quantityK, quantityM, quantityA);
                    break;
                    case 2:
                        Enemigo[i].TpE(row, column, board);
                        E[i].iPosition = Enemigo[i].iPosition;
                        E[i].jPosition = Enemigo[i].jPosition;
                    break;
                    case 3:
                        Enemigo[i].TorbellinoE(row, column, board, G, K, M, A, quantityG, quantityK, quantityM, quantityA);
                    break;
                } 
            }
            E[i].iPosition = Enemigo[i].iPosition;
            E[i].jPosition = Enemigo[i].jPosition;
        }
    }
    PrintBoard(row, column, board, salida);
    for(int i = 0; i < quantityG; i++){salida << G[i].hp << " " << G[i].attack << " " << G[i].armor << " " << G[i].Mresistence << endl; }
    for(int i = 0; i < quantityK; i++){salida << K[i].hp << " " << K[i].attack << " " << K[i].armor << " " << K[i].Mresistence << endl; }
    for(int i = 0; i < quantityM; i++){salida << M[i].hp << " " << M[i].attack << " " << M[i].armor << " " << M[i].Mresistence << endl; }
    for(int i = 0; i < quantityA; i++){salida << A[i].hp << " " << A[i].attack << " " << A[i].armor << " " << A[i].Mresistence << endl; }
    for(int i = 0; i < quantityE; i++){salida << E[i].hp << " " << E[i].attack << " " << E[i].armor << " " << E[i].Mresistence << endl; }

    entrada.close();
    salida.close();

    return 0;
}