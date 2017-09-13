
#include <iostream>
#include <vector>

using namespace std;
clock_t begin = clock();

int m[20][7];
int maior=0;
int nr_piece=0;
int comb[20][20];


bool recursao(int soma,int aux){
	int i,j;
   //ja todas as peÃ§as foram jogadas
	if(aux>=nr_piece){
        
		if(soma>maior){
	   		maior=soma;
	 	}
 		return true;
	}
	
    //correr todas as peÃ§as   
   for(i=0;i<=nr_piece;i++){
   
     for(j=0;j<=nr_piece;j++){
        //verificar se temos uma peÃ§a nao jogada e uma no tabuleiro pra comparar- vamos ver se podemos meter peÃ§as ainda nao jogadas no tabuleiro de acordo com as ja jogadas 
       /////////////////////////////
        if( comb[i][j]<nr_piece*nr_piece*9){ 

           if((m[i][6]==0) && (m[j][6]==1)){ 
           comb[i][j]+=1;
           //verificar se par da peÃ§a ja no tabuleiro esta livre- repetir para todos os pares
             if(m[j][3]==0){ 
                //se esta compara lo com todos os pares da peÃ§a ainda nao jogada e que se pretende jogar- se pares corresonderem abrir recursao com soma atualizada e pares ocupados tb, bem como peÃ§as jogadas
             	if(m[i][0]==m[j][1] &&  m[i][1]==m[j][0] ){
                   
             		m[i][6]=1;
             		m[j][3]=1;
             		m[i][3]=1;
             		recursao(soma+m[i][0]+m[i][1],aux++);
             		m[i][6]=0;
             		m[j][3]=0;
             		m[i][3]=0;
             	}
             	if(m[i][1]==m[j][1] &&  m[i][2]==m[j][0] ){
                   
             		m[i][6]=1;
             		m[j][3]=1;
             		m[i][4]=1;
             		recursao(soma+m[i][1]+m[i][2],aux++);
             		m[i][6]=0;
             		m[j][3]=0;
             		m[i][4]=0;
             	}
             	if(m[i][2]==m[j][1] &&  m[i][0]==m[j][0] ){
                   
             		m[i][6]=1;
             		m[j][3]=1;
             		m[i][5]=1;
             		recursao(soma+m[i][2]+m[i][0],aux++);
             		m[i][6]=0;
             		m[j][3]=0;
             		m[i][5]=0;
             	}
             }	
             if(m[j][4]==0){ 
             	if(m[i][0]==m[j][2] &&  m[i][1]==m[j][1] ){
                 
             		m[i][6]=1;
             		m[j][4]=1;
             		m[i][3]=1;
             		recursao(soma+m[i][0]+m[i][1],aux++);
             		m[i][6]=0;
             		m[j][4]=0;
             		m[i][3]=0;
             	}
             	if(m[i][1]==m[j][2] &&  m[i][2]==m[j][1] ){
                  
             		m[i][6]=1;
             		m[j][4]=1;
             		m[i][4]=1;
             		recursao(soma+m[i][1]+m[i][2],aux++);
             		m[i][6]=0;
             		m[j][4]=0;
             		m[i][4]=0;
             	}
             	if(m[i][2]==m[j][2] &&  m[i][0]==m[j][1] ){
                   
             		m[i][6]=1;
             		m[j][4]=1;
             		m[i][5]=1;
             		recursao(soma+m[i][2]+m[i][0],aux++);
             		m[i][6]=0;
             		m[j][4]=0;
             		m[i][5]=0;
             	}
             }	
             if(m[j][5]==0){ //sentido do relogio mas sides sao juntas em espelho
             	if(m[i][0]==m[j][0] &&  m[i][1]==m[j][2] ){
                  
             		m[i][6]=1;
             		m[j][5]=1;
             		m[i][3]=1;
             		recursao(soma+m[i][0]+m[i][1],aux++);
             		m[i][6]=0;
             		m[j][5]=0;
             		m[i][3]=0;
             	}
             	if(m[i][1]==m[j][0] &&  m[i][2]==m[j][2] ){
               
             		m[i][6]=1;
             		m[j][5]=1;
             		m[i][4]=1;
             		recursao(soma+m[i][1]+m[i][2],aux++);
             		m[i][6]=0;
             		m[j][5]=0;
             		m[i][4]=0;
             	}
             	if(m[i][2]==m[j][0] &&  m[i][0]==m[j][2] ){
                   
             		m[i][6]=1;
             		m[j][5]=1;
             		m[i][5]=1;
             		recursao(soma+m[i][2]+m[i][0],aux++);
             		m[i][6]=0;
             		m[j][5]=0;
             		m[i][5]=0;
             	}
             }	
                   
               
    	    }
        //////////////////
        }



	  }
	}

    //nao ha mais jogadas 
	if(soma>maior){
	   		maior=soma;
	 	}
 		
    return false;       
}



int main(){

	ios::sync_with_stdio(false);

   
	int n1,n2,n3,i;


	while(cin >> n1 >> n2 >> n3){
	    //nr de vertices
		m[nr_piece][0]=n1;
		m[nr_piece][1]=n2;
		m[nr_piece][2]=n3;
        //par 0 1 desocupado(a 0)
	    m[nr_piece][3]=0;
        //par 1 2 desocupado(a 0)
	    m[nr_piece][4]=0;
        //par 2 0 desocupado(a 0)
	    m[nr_piece][5]=0;
        //peÃ§a nao foi jogada ainda(a 0)
	    m[nr_piece][6]=0;
        //numero de peÃ§as atualizado
		nr_piece++;
		
	}

    //comeÃ§ar por jogar todas as peÃ§as (a primeira que se mete, sem ter pares ocupados)
    for(i=0;i<=nr_piece;i++){

        m[i][6]=1;
        recursao(0,0);
        m[i][6]=0;
       

    }

  
     cout<<maior<<"\n";



	return 0;
}