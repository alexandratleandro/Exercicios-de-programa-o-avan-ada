#include <iostream>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <math.h>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

// compara estado atual com os anterios para ver se domina algum 
string domina(vector<string> v, int novo[10], int nPlaces){
    string s;
    string d =" ";
    string novoS="";
    int token [10];
    int sz;
    bool domina=true; // saber se estado atual domina o estado visitado que tamos a testar
    vector<int> ww; // guardar os indices dos lugares anteriores onde ha w
    int tam = v.size();
    for (int i=0; i<tam; i++){
        vector<int> ind; // guardar os indices onde se vai por w
        s= v[i];
        domina=true;
        /// converter estado visitado para int[] e comparar com o estado atual
        for(int p = 1;p<=nPlaces;p++){
            sz = s.find(d);
            string aux = s.substr(0, sz);
            if(aux.compare("w")==0){  
                token[p]=-1;
                //ww.push_back(p);
            }else{
                token[p]=atoi(aux.c_str());
            }
            s.erase(0, sz + d.length());
            if(token[p]>=0){
                if(token[p]>novo[p]){ 
                    domina=false;
                }
                if(token[p]<novo[p]){
                    ind.push_back(p); // guardar indices onde meter w --> estado novo domina anterior
                }
            }            

        }
        // se estado novo domina algum anterior
        if(domina && ind.size()>0){ 
            for(int p = 1;p<=nPlaces;p++){
                    // se lugar em questao p, tiver na lista de indices estritamente maiores
                if (find(ind.begin(), ind.end(), p) != ind.end() ){
                    novoS +="w";
                }
                else if(token[p]==-1){
                    novoS+="w";
                }
                else{
                    stringstream ss;
                    ss<<novo[p];
                    novoS += ss.str();
                }
                if(p<nPlaces){
                    novoS+=" ";
                }
            }
            return novoS;
        }
    }

    // se novo estado nao dominar nenhum dos anteriores retornar a "string " original
    for(int z = 1;z<=nPlaces;z++){

        if (find(ww.begin(), ww.end(), z) != ww.end()){
            novoS +="w";
        }
        else if(novo[z]==-1){
            novoS+="w";
        }
        else{
            stringstream ss;
            ss<<novo[z];
            novoS += ss.str();
        }
        if(z<nPlaces){
            novoS+=" ";
        }
    }
    return novoS;
}

void dfs(vector<string> visitados, int inPT[6][6],int outTP[6][6],string estado,int nPlaces,int nTransitions, int nivel){

    string d = " ";
    int sz;
    int token[10];

    // imprimir estado de acordo com o ivel
    for(int n=0; n<nivel; n++){
       cout<<" ";
    }
    cout<<estado<<"\n";

    if (find(visitados.begin(), visitados.end(), estado) == visitados.end()){
        visitados.push_back(estado); // marcar estado como visitado
        // obter os tokens em cada place no estado
        for(int i = 1;i<=nPlaces;i++){
            sz = estado.find(d);
            string aux = estado.substr(0, sz);
            if(aux.compare("w")==0){
                token[i]=-1;
            }else{
                token[i]=atoi(aux.c_str());
            }
            estado.erase(0, sz + d.length());
        } 
        for(int t=1; t<=nTransitions; t++){
            int var[10]; // guardar valores dos tokens depois de disparar t
            bool next=true;

            // verrificar para cada place
            for(int p=1; p<=nPlaces; p++){
                var[p]=token[p]; 
                if(inPT[p][t]>=1 && token[p]==-1){ // significa que ÃƒÂ© w
                    var[p]= -1; //fica tb a w
                }

                if(inPT[p][t]<=token[p]){
                    var[p]= token[p]-inPT[p][t]; //
                }
                 
                else if(inPT[p][t]>token[p] && token[p]>=0){
                    next=false;
                    break; 
                }
            }
            if(next){   
                for(int p=1; p<=nPlaces; p++){
                   if(outTP[t][p]>=1){
                        if(var[p]>=0){
                            var[p] = var[p]+outTP[t][p];
                        }
                       
                   }
                }
                // obter novo estado
                string prox=domina(visitados, var, nPlaces);
                // se esse estado nao tiver sido expandido ainda explorar
                /// continuar dfs com o proximo estado e um nivel maior
                dfs(visitados, inPT, outTP,prox,nPlaces,nTransitions, nivel+1);

            }

        }
    }

}



int main(){

    ios::sync_with_stdio(false);

    int nPlaces,nTransitions;
    string str;
    int p_t_In[6][6]={};  
    int t_p_Out[6][6]={}; 
    int n1,n2,n3,sz;
    string d = " ";
    string estadoI;
    cin >> nPlaces >> nTransitions;
    getline(cin,str);
    while(str != "STATE"){
        sz = str.find(d);
        n1=atoi(str.substr(0, sz).c_str());
        str.erase(0, sz + d.length());

        sz = str.find(d);
        n2=atoi(str.substr(0, sz).c_str());
        str.erase(0, sz + d.length());

        sz = str.find(d);
        n3=atoi(str.substr(0, sz).c_str());
        str.erase(0, sz + d.length());

        if(n3 == 2){
            p_t_In[n1][n2]+=1; /// vai de p para t--> ingoing arc I(t)
        }else{
            t_p_Out[n1][n2]+=1; /// vai de t para p--> outgoing arc O(t)
        }

        getline(cin,str);
    }

    getline(cin,estadoI);
    vector<string> visitados;
    dfs(visitados, p_t_In,t_p_Out,estadoI,nPlaces,nTransitions, 0);

    return 0;
}