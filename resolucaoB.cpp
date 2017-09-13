//================================================================================
// LPA - Problem B - In the assembly line
//
// Author: LPA_AAN
//
// Description:
// n <= 400
// INPUT:   n_operation
//          ...
//          op_probability_i    machine_i_cost
//          ...
//          op_probability_n    machine_n_cost
//          budget
//
//
//================================================================================
#include <iostream>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ZERO 1.0E-15
//=========================================================
using namespace std;
//=========================================================
int budget;
long double maqProb[450][1050]; // prob de cada maquina tipo i de acordo com a quantidade j
int  maqCusto[450]; //custo de cada maquina
long double probU=1.0;
int n=0;
int i,j,k,x;
int budgetMin = 0;
long double regista[450][1050];  // prob de acordo com i-tipoMaquina e j-orçamento
int money=0;
int tempSol[450];
int sols[10000][450];
int linha=0;
int preencher[450];
long double currMax=0.0;
int  minGato=1000000;

//=========================================================

 long double dp(){ // Calcular combinação com menor probabilidade de insucesso


    for(j=budgetMin; j<=budget; j++){
        regista[0][j]=probU;
    }
    for(j=1; j<=n; j++){
        regista[j][budgetMin]=probU;
         regista[j][n]=probU;
    }

    for (i=1;i<=n;i++){
        for (j=budgetMin+1; j<=budget;j++){
            currMax = regista[i-1][j];
            for(k=1; k<=(int)((j-budgetMin)/maqCusto[i-1]); k++){

                 if(preencher[i-1]<k){
                    for( x=preencher[i-1]+1; x<=k; x++){
                        maqProb[i-1][x]= maqProb[i-1][x-1]*maqProb[i-1][0];
                    }
                    preencher[i-1]=k;
                 }
                currMax=(currMax<((regista[i-1][j-(maqCusto[i-1]*k)])/(1-maqProb[i-1][0]))* (1-maqProb[i-1][k]))?((regista[i-1][j-(maqCusto[i-1]*k)])/(1-maqProb[i-1][0]))* (1-maqProb[i-1][k]):currMax;

            }
            regista [i][j]=  currMax;
        }
    }
    return regista[n][budget];
}

void getSolutions(int line,int col){

    if(money>budget - budgetMin){ // se soluçao nao ultrapassar budget incrementamos n de soluçoes
        return;
    }

    if((line<=1 && col <=budgetMin+1) ||((fabs(regista[line][col]-probU)/max(regista[line][col],probU))<ZERO)){
        if(money<minGato){
            minGato=money;
        }
        for(int l=0;l<n;l++){
           sols[linha][l]=tempSol[l];
        }
        linha++;
        return;
    }

    if((fabs(regista[line][col]-regista[line-1][col])/max(regista[line][col],regista[line-1][col]))<ZERO){ // significa que nao foi usada mais nenhuma maquina desse tipo
        getSolutions(line-1,col);
    }
    for( int a=1; a<=(int)(((budget-budgetMin)-money)/(double)maqCusto[line-1]); a++){
        if((fabs((regista[line][col]/(1-maqProb[line-1][a]))*(1-maqProb[line-1][0]) - regista[line-1][col - maqCusto[line-1]*a])/max((regista[line][col]/(1-maqProb[line-1][a]))*(1-maqProb[line-1][0]), regista[line-1][col - maqCusto[line-1]*a]))<ZERO){
            tempSol[line-1]=a;
             money+= a*maqCusto[line-1];
             if(money>minGato){
                return;
             }
            getSolutions(line-1, (col - maqCusto[line-1]*a));
             money-=a*maqCusto[line-1];
            tempSol[line-1]=0;
        }
    }

}

//=========================================================
int main(){

    ios::sync_with_stdio(false);
    //cin.tie(NULL);
    cout << fixed << setprecision(12);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> maqProb[i][0] >> maqCusto[i];
        budgetMin+= maqCusto[i];
        probU*=maqProb[i][0]; // probabilidade minima de sucesso-> so ter uma maquina de cada
        maqProb[i][0] = 1 - maqProb[i][0]; // guardar probabilidade de insucesso de cada máquina


    }
    cin >> budget;

    cout<<dp()<<"\n";
    minGato=100000000;
    getSolutions(n,budget);
    int ver=0;
    for(int i=0;i<linha;i++){
        ver=0;
        for(int b=0;b<n;b++){
            ver+=(sols[i][b]*maqCusto[b]);
        }

        if(ver==minGato){
            for(int j=0;j<n;j++){
                cout<<1+sols[i][j];
                if(j<n-1){
                    cout<<" ";
                }
            }
            cout<<"\n";
        }
    }

    return 0;
}
//=====================================================