#include <iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<array>
#include<algorithm>

using namespace std;

struct celda{
    celda(int fila_,int col_,int cont){
        fila=fila_;
        col=col_;
        contenido=cont;
        n=0;
    }
    int n;
    int fila;
    int col;
    int contenido;
};
bool operator <(celda c1, celda c2){
    return c1.n>c2.n;
}
struct tablero
{
    tablero(int n){
        for(int e=0;e<n;e++){
            board.push_back({});
            for(int o=0;o<n;o++){
                board.back().push_back(celda(e,o,0));
             }
            }
    }
 vector<vector<celda>> board;
};
ostream& operator<<(ostream& os, const tablero& t)
{
        for(int e=0;e<t.board.size();e++){
            for(int o=0;o<t.board.size();o++){
                os<<t.board[e][o].contenido<<" ";
                if(t.board[e][o].contenido<10){
                    os<<"  ";
                }
                else if(t.board[e][o].contenido<100){
                    os<<" ";
                }
             }
            os<<endl;
            }
        return os;
}
bool esLegal(int fila, int col,int mov,tablero tablero){
      switch(mov){
        case 5:
        if(fila<2){
          return 0;
        }
        else if(col<1){
          return 0;
        }
        else if(tablero.board[fila-2][col-1].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 4:
        if(fila<2){
          return 0;
        }
        else if(col>tablero.board.size()-2){
          return 0;
        }
        else if(tablero.board[fila-2][col+1].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 3:
        if(fila<1){
          return 0;
        }
        else if(col>tablero.board.size()-3){
          return 0;
        }
        else if(tablero.board[fila-1][col+2].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 2:
        if(fila>tablero.board.size()-2){
          return 0;
        }
        else if(col>tablero.board.size()-3){
          return 0;
        }
        else if(tablero.board[fila+1][col+2].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 1:
        if(fila>tablero.board.size()-3){
          return 0;
        }
        else if(col>tablero.board.size()-2){
          return 0;
        }
        else if(tablero.board[fila+2][col+1].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 8:
        if(fila>tablero.board.size()-3){
          return 0;
        }
        else if(col<1){
          return 0;
        }
        else if(tablero.board[fila+2][col-1].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 7:
        if(fila>tablero.board.size()-2){
          return 0;
        }
        else if(col<2){
          return 0;
        }
        else if(tablero.board[fila+1][col-2].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
        case 6:
        if(fila<1){
          return 0;
        }
        else if(col<2){
          return 0;
        }
        else if(tablero.board[fila-1][col-2].contenido!=0){
          return 0;
        }
        else{return 1;}
        break;
      }
    return 0;
    }
void definirprioridadcelda(celda& c,tablero& t){
    int res=0;
    for(int i=1;i<9;i++){
        if(!esLegal(c.fila,c.col,i,t)){
            res++;
        }
    }
    c.n=res;
}
bool menorQue(celda& c1, celda& c2, tablero t){
   definirprioridadcelda(c1,t);
   definirprioridadcelda(c2,t);
   return(c1.n<c2.n);
}
bool movimiento(celda& c, tablero& t, int p, bool b){
    t.board[c.fila][c.col].contenido=p;
    if(p>=t.board.size()*t.board.size()){
        return 1;
    }
    else{
        vector<celda> lista;
        celda mov(0,0,0);
        for(int i=1;i<9;i++){
            if(esLegal(c.fila,c.col,i,t)){
              switch(i){
              case 5:
                  mov=t.board[c.fila-2][c.col-1];
                  break;
              case 4:
                  mov=t.board[c.fila-2][c.col+1];
                  break;
              case 3:
                  mov=t.board[c.fila-1][c.col+2];
                  break;
              case 2:
                  mov=t.board[c.fila+1][c.col+2];
                  break;
              case 1:
                  mov=t.board[c.fila+2][c.col+1];
                  break;
              case 8:
                  mov=t.board[c.fila+2][c.col-1];
                  break;
              case 7:
                  mov=t.board[c.fila+1][c.col-2];
                  break;
              case 6:
                  mov=t.board[c.fila-1][c.col-2];
                  break;
              }
              lista.push_back(t.board[mov.fila][mov.col]);
            }
    }
        for(int i=0;i<lista.size();i++){
            definirprioridadcelda(lista[i],t);
        }
        sort(lista.begin(), lista.end());
        for(int i=0;i<lista.size();i++){
                            p++;
                            if(b){
                                cout<<t<<endl;
                            }
                            if (movimiento(t.board[lista[i].fila][lista[i].col],t,p,b)){
                                return 1;
                            }
                            else{
                            p--;
                            t.board[lista[i].fila][lista[i].col].contenido=0;
                            }

        }
        t.board[c.fila][c.col].contenido=0;
        return 0;
}
    return 0;
}
int main() {
    int n,f,c;
    bool b;
    cout<<"Escribe la dimension del tablero: ";
    cin>>n;
    cout<<endl<<"Escribe la fila y columna desde la cual saldra el caballo: ";
    cin>>f>>c;

    cout<<endl<<"¿Quieres ver todo el camino del caballo o solo el resultado final?\n1=ver todo 0=solo resultado final"<<endl;
    cin>>b;
    cout<<endl;
    tablero tab(n);
if(movimiento(tab.board[f][c],tab,1,b)){
    cout<<tab;
}

else{
    cout<<"No hay solucion para este problema."<<endl;
}
}
