//================================================================================
#include <iostream>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

int best;
int restricoes[50][50]; 
int varRes[50]; 
int valores[50]; 
int coef[50]; 
int maximize=0;
int ind0=50, indn=0; 
int nRestricoes=-1;
int inicio, fim, num, ind, eq;
string linha;
bool found=false; 
int sumParMenor[50][50]; 
int sumParMaior[50][50]; 
//int gBound[50];
int somaCheck[50];


void readInput(){
    int len = linha.length();
    inicio=0, fim=0, num=0, ind=0, eq=0;
    if(nRestricoes!=-1){
        len = linha.find("<=");
        if(len>0){
            restricoes[nRestricoes][0]=2;
            varRes[nRestricoes]= atoi(linha.substr(len+2,linha.length()-len+2).c_str());
        }
        else{
            len = linha.find(">=");
            if(len>0){
                restricoes[nRestricoes][0]=4;
                varRes[nRestricoes]= atoi(linha.substr(len+2,linha.length()-(len+2)).c_str());
            }
            else{
                len = linha.find("<");
                if(len>0){
                    restricoes[nRestricoes][0]=1;
                    varRes[nRestricoes]= atoi(linha.substr(len+1,linha.length()-(len+1)).c_str());
                }
                else{
                    len = linha.find(">");
                    if(len>0){
                        restricoes[nRestricoes][0]=3;
                        varRes[nRestricoes]= atoi(linha.substr(len+1,linha.length()-(len+1)).c_str());
                    }
                    else{// igual
                        len = linha.find("=");
                        restricoes[nRestricoes][0]=0;
                        varRes[nRestricoes]= atoi(linha.substr(len+1,linha.length()-(len+1)).c_str());
                    }
                }
            }
        }
    }

    for(int i=0; i<len; i++){

        if(i>0 && (linha.at(i-1)=='-' && linha.at(i)=='x')){
            num = -1;
            inicio =i+1;
        }
        else if(linha.at(i)=='x'){ 
            fim=i;
            num= atoi( linha.substr(inicio,fim-inicio).c_str());

            if(num==0){ 
                num=1;
            }
            inicio =i+1;
        }
        else if(linha.at(i)=='-' || linha.at(i)=='+' || linha.at(i)=='<' || linha.at(i)=='>' || linha.at(i)=='='){ 
            fim=i;
            ind= atoi( linha.substr(inicio,fim-inicio).c_str());
            if(num!=0 && ind!=0){
                if(nRestricoes==-1){
                    coef[ind]=num;
                    valores[ind]=0; 
                    if(ind >indn){
                        indn=ind;
                    }
                    if(ind<ind0){
                        ind0=ind;
                    }
                }
                else{
                    restricoes[nRestricoes][ind]=num;
                }
            }
            inicio =i;
        }
        else if(i==len-1){ 
            fim=i+1;
            ind= atoi( linha.substr(inicio,fim-inicio).c_str());
            if(num!=0 && ind!=0){
                if(nRestricoes==-1){
                    coef[ind]=num;
                    valores[ind]=0; 
                    if(ind >indn){
                        indn=ind;
                    }
                    if(ind<ind0){
                        ind0=ind;
                    }
                }
                else{
                    restricoes[nRestricoes][ind]=num;
                }
            }
            inicio =i;
        } 
    } 
}

bool constraint(int n, int i, int soma){
    for(int k=i+1; k<=45; k++){
        if(restricoes[n][k]!=0){
            if(valores[k]==1){ 
                soma+= restricoes[n][k];
            }
            else if(valores[k]==-1){ 

                if(constraint(n, k, soma)){
                    return true;
                }

                if(constraint(n, k, soma+restricoes[n][k])){
                    return true;
                }

            }
        }
    }

    somaCheck[n]=soma;
    if(restricoes[n][0]==0){// tem de ser ==
        if(soma ==varRes[n]){
             return true;
        }
    }
    else if(restricoes[n][0]==2){// tem de ser <=
        if(soma <=varRes[n]){
             return true;
        }
    }
    else if(restricoes[n][0]==4){// tem de ser >=
        if(soma >=varRes[n]){
            return true;
        }
    }

    return false; //nao cumpre restriÃ§oes
}


bool checkRest(){ 

    for(int n=0; n<nRestricoes; n++){
        if(constraint(n,0, 0)==false){
            return false; 
        }
    }
    return true; 
}

int g(int id, int atual){// funcao bounding -> vai dar upper/lower bound do valor que pode ser obtido para essa sol
    // se esse bound for maior/menor que o best guardado nao vale a pena continuar a arvore de recursao dessa sol parcial

    if(maximize){// maximizar -> por os x positivos a 1
        for(int b=id+1; b<=indn; b++){ // percorrer todos os indices
            if(coef[b]>0){
                atual +=coef[b];
            }
        }
    }
    else{ // minimizar por x negativos a 1
        for(int b=id+1; b<=indn; b++){ // percorrer todos os indices
            if(coef[b]<0){ // se for 2x3 -- por valor a 1
                atual +=coef[b];
            }
        }
    }
    return atual;
}


int objetivo(int i, long int var){
    if(maximize){
        if(g(i, var)<=best){ // se upper bound for menor que o best ja encontrado, sai
            return 0;
        }
    }
    else{ // minimizacao
        if(g(i, var)>=best){ // se lower bound for maior que o best ja encontrado, sai
            return 0;
        }
    }

    if(checkRest()){ // se forem cumpridas todas as restricoes--> verificar solucao

    // atualizar valor do best
         
        if(found){
            if(maximize){
                if(var>best)
                   best=var;
            }
            else{
                if(var<best)
                   best=var;
            }
        }
        else{
            found=true;
            best=var;
        }
        
    }
    
     for(int n=0;n<nRestricoes;n++){
        if(restricoes[n][0]==2){ //<=
          
            if(somaCheck[n]+sumParMenor[n][i]>varRes[n]){

                return 0;

            }

        }
        if(restricoes[n][0]==4){ //>=
            if(somaCheck[n]+sumParMaior[n][i]<varRes[n]){

                return 0;

            }
        }
       
    }
 
    for(int j=i+1; j<=indn; j++){
        if(coef[j]!=0){           
            valores[j]=1;
            objetivo(j, var+coef[j]); // recusao com valor 1
            valores[j]=0;

        }
    }
    return 0;
}


int main(){

    ios::sync_with_stdio(false);

    for(int z=1; z<=45; z++){
        valores[z]=-1;
    }
    getline(cin, linha);
    if(linha=="maximize"){
        best=-2147483647;
        maximize=1;
    }
    else{
        best= 2147483647;
    }
    getline(cin, linha);
    readInput();
    getline(cin, linha);
    if(linha=="st"){
        nRestricoes=0;
        while (getline(cin, linha) ) {
            if(linha=="BINARY"){
                break;
            }
            else{
                readInput();
                nRestricoes++;
            }
        }
    }
    
    int acumuladoMaior=0,acumuladoMenor=0;
    for(int i=0;i<nRestricoes;i++){
        acumuladoMaior=0;
        acumuladoMenor=0;
        for(int j=45;j>=1;j--){
           
            sumParMaior[i][j]=acumuladoMaior; 
            sumParMenor[i][j]=acumuladoMenor; 
            
            if(restricoes[i][j]>0){
                
                acumuladoMaior+=restricoes[i][j];
            }
            if(restricoes[i][j]<0){
               
                acumuladoMenor+=restricoes[i][j];
            }
        }
    }
 /// g()
   /* int soma=0; 
    gBound[indn]=soma;  

    for(int k=indn-1;k>=ind0;k--){   
        gBound[k]=soma;
        if(maximize){
            if(coef[k+1]>0){ 
                soma+=coef[k+1]; 
                gBound[k]=soma; 
            }
        }
        else{
            if(coef[k+1]<0){ 
                soma+=coef[k+1]; 
                gBound[k]=soma; 
            }
        }    
        
    }*/

    objetivo(ind0, 0); // recursiva para xind0 = 0
    valores[ind0]=1;
    objetivo(ind0,coef[ind0]); // recursiva para xindn =1
    valores[ind0]=0;
 

    if(found){ // encontrada sol
        cout<<best<<"\n";
    }
    else{ // nao ha solucoes
        cout<<"INFEASIBLE\n";
    }

    return 0;
}