#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int **genererMatrice(int N, int M){
    // m est un pointeur sur un liste de pointeur, d'où int**
    int** m;
    // alloué N pointeurs, N étant le nb de lignes
    m=malloc(N* sizeof(int*));
    for (int i=0;i<N;i++){
        //pour chaque ligne de la matrice m[i] allouez M entiers, M étant le nb colones
        m[i]=malloc(M* sizeof(int));}
        //ici la matrice m est construite en mémoire, donc on peut la remplir
        //remplissage de la genererMat
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                m[i][j]=rand() %2;                                    //placer mur et lignes 0 et 1 et voir sur chaque case avec swich case si je suis sur un mur ou sur une case 
                m[0][0]=0;                                            //fonction qui dit si y'a un chamin ou pas 
                                                                    // 2 et 3 pour case e
                m[M-1][N-1]=0;
                 printf("%d", m[i][j]);};
            printf("\n");
        }

    return m;
}