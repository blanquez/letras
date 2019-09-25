#ifndef BOLSALETRAS_H
#define BOLSALETRAS_H

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "conjuntoletras.h"

class BolsaLetras{
private:
	vector<char> bolsaletras;

	void llenar(ConjuntoLetras conjunto){
		char a='a';
		for(int i=0;i<conjunto.size();++i){
			for(int j=0;j<conjunto[a].repeticiones;++j){
				bolsaletras.push_back(a);
			}
			a++;
		}
	}
public:
	/**
		@brief Constructor de BolsaLetras
		@param conj: ConjuntoLetras para construir la bolsa
	**/
	BolsaLetras(ConjuntoLetras conj){
		llenar(conj);
	}

	/**
		@brief Saca n letras al azar de la bolsa
		@param num: numero de letras a sacar
		@return un vector de char con las letras que ha sacado de la bolsa
	**/
	vector<char> sacarLetras(int num){
		vector<char> buff;
		vector<char> aux=bolsaletras;
		srand(time(NULL));
		for(int i=0;i<num;i++){
			int n=rand()%aux.size();
			buff.push_back(aux[n]);
			aux.erase(aux.begin()+n);
		}
		return buff;
	}
};

#endif