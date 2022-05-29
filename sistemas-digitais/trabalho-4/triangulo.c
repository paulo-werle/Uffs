
#include <stdio.h>


int area(int x1, int x2, int x3, int y1, int y2, int y3){
    int a;
    a = ((x1*y2 + y1*x3 + x2*y3)-(x3*y2 + y3*x1 + x2*y1))/2;
    
    if (a < 0){
        return a * (-1);
    }
    return a;
}

int triangulo( int x1, int x2, int x3, int y1, int y2, int y3, int i, int j){
    int t1 = area (x1, x2, i ,y1, y2, j);
    int t2 = area (x1, x3, i ,y1, y3, j);
    int t3 = area (x2, x3, i ,y2, y3, j);
    int t = area (x1, x2, x3, y1, y2, y3);


    return t1 + t2 + t3 <= t;
}

int main(){
    int x1, y1, x2, y2, x3 , y3 ;
    x1=1;
    y1=1;
    x2=1;
    y2=9;
    x3=8;
    y3=5;
/*
    printf("Digite os pontos A x1 do triangulo: ");
    scanf("%d", x1);
    printf("Digite os pontos A y1 do triangulo: ");
        scanf("%d", y1);
    printf("Digite os pontos B x2 do triangulo: ");
        scanf("%d", x2);
    printf("Digite os pontos B y2 do triangulo: ");
        scanf("%d", y2);
    printf("Digite os pontos C x3 do triangulo: ");
        scanf("%d", x3);
    printf("Digite os pontos C y3 do triangulo: ");
        scanf("%d", y3);
*/

int x = 10; //linhas por coluna

for (int i=0 ; i<x; ++i){
    for (int j =0; j<x; ++j){
        if (triangulo(x1, x2, x3, y1, y2, y3, i, j)){
            
            printf("X");
        }
        else{
            printf("-");
        }
    }
        printf ("\n");
}
}
