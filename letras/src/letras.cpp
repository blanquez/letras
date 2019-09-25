#include <iostream>
#include <fstream>
#include <cstring>
#include "diccionario.h"
#include "conjuntoletras.h"
#include "bolsaletras.h"

using namespace std;

char Diccionario::modo;
ConjuntoLetras Diccionario::conjunto;

bool comprobar(string pal, vector<char> bol){
	multiset<char>::iterator mit;
	multiset<char> bolsa;
	for(int i=0;i<bol.size();++i)
		bolsa.insert(bol[i]);
	multiset<char> palabra;
	for(int i=0;i<pal.size();++i)
		palabra.insert(pal[i]);
	bool correcto=true;
	for(mit=palabra.begin();mit!=palabra.end();++mit){
		if(palabra.count(*mit)>bolsa.count(*mit)){
			correcto=false;
			break;
		}
	}
	return correcto;
}

int main(int argc, char *argv[]){
	if(argc != 5){
		cout << "Uso: bin/letras <idioma> <dificultad> <n_letras> <modo_juego>" << endl;
		cout << "Opciones:\n\t*idioma:{d1000.txt,spanish.txt,english.txt,french.txt,german.txt,italian.txt}\n\t Idioma en el que deberemos buscar las palabras\n\t (d1000 es una seleccion de 1000 palabras en espanol)" << endl;
		cout << "\t*dificultad:{normal.txt,dificil.txt}\n\t La dificultad varia la posibilidad de que salgan letras mas faciles de combinar" << endl;
		cout << "\t*n_letras:[3-20]\n\t Numero de letras que se proporcionan para formar palabras" << endl;
		cout << "\t*modo_juego:{L,P}\n\t L:mayor puntuacion a mayor longitud\n\t P:mayor puntuacion a letra con mas puntos(puntuacion dada al inicio)" << endl;
		cout << "Ejemplo de uso: bin/letras spanish.txt normal.txt 8 L" << endl;
		return 0;
	}

	if(atoi(argv[3]) < 3 || atoi(argv[3]) > 20){
		cout << "No se puede jugar con menos de 3 o mas de 20 letras" << endl;
		return 0;
	}

	if(*argv[4]!='L' && *argv[4]!='P'){
		cout << "Error al seleccionar el modo de juego" << endl;
		return 0;
	}

	ifstream d(argv[1]);
	if(!d){
		cout << "Error al abrir el fichero de diccionario" << endl;
		return 0;
	}

	ifstream c(argv[2]);
	if(!c){
		cout << "Error al abrir el fichero del conjunto de letras(modo de juego)" << endl;
		return 0;
	}

	cout << "****************************************************" << endl;
	cout << "   *       *****   *****   *****   *****   *****" << endl;
	cout << "   *       *         *     *   *   *   *   *" << endl;
	cout << "   *       *****     *     *****   *****   *****" << endl;
	cout << "   *       *         *     *  *    *   *       *" << endl;
	cout << "   *****   *****     *     *   *   *   *   *****" << endl;
	cout << "****************************************************" << endl;
	cout << "	Idioma seleccionado: " << argv[1] << endl;
	cout << "	Dificultad: " << argv[2] << endl;
	cout << "	Numero de letras por partida: " << argv[3] << endl;
	cout << "	Modo de juego seleccionado: ";
	if(*argv[4]=='L') cout << "Longitud\n\t-Debe de buscar la palabra mas larga posible" << endl;
	else cout << "Puntuacion\n\t-Debe buscar la palabra que contenga las letras con la mayor puntuacion" << endl;

	cout << "****************************************************" << endl;
	cout << "Cargando diccionario..." << endl;
	Diccionario::modo=*argv[4];
	int num_letras = atoi(argv[3]);
	int corte;
	ConjuntoLetras conj;
	c>>conj;
	Diccionario::conjunto=conj;	
	Diccionario diccionario;
	d>>diccionario;
	if(Diccionario::modo=='L') corte=num_letras;
	else corte=(num_letras*conj.puntuacion_maxima());
	diccionario.preparar(corte);

	cout << "Cargando bolsa de letras..." << endl;
	BolsaLetras bolsa(conj);
	char bucle = 's';
	vector<char> letras;
	string solucion;
	int puntuacion;
	cout << "Carga completada";
	if(Diccionario::modo == 'P') cout << "\n****************************************************" << conj;

	while(bucle == 's'){
		cout << "\n****************************************************" << endl;
		letras=bolsa.sacarLetras(num_letras);
		cout << "Las letras son:" << endl;
		for(int i=0;i<letras.size();++i)
			cout << letras[i] << " ";
		cout << endl;

		bool esta=false;
		do{
			cout << "Dime tu solucion: ";
			cin >> solucion;
			if(solucion!="."){
				esta=comprobar(solucion, letras);
				if(!esta) cout << "Esa solucion no esta formada por las letras dadas\nPara pasar introduce un punto\n" << endl;
				else{
					esta=diccionario.Esta(solucion);
					if(!esta) cout << "Esa solucion no existe en el diccionario\nPara pasar introduce un punto\n" << endl;
				}
			}
		}while(!esta && solucion!=".");

		cout << "\nTu solucion: ";

		if(solucion==".") cout << "Has pasado" << endl;
		else{
			puntuacion=0;
			if(Diccionario::modo=='L') puntuacion = strlen(solucion.c_str());
			else{
				for(int i=0;i<strlen(solucion.c_str());++i)
					puntuacion += conj.puntuacion(solucion[i]);
			}

			cout << solucion << "\tPuntuacion: " << puntuacion << endl;
		}
		
		cout << "Mi solucion: ";

		solucion = diccionario.buscarPalabra(letras);
		if(solucion==" ") cout << "No se ha encontrado ninguna" << endl;
		else{
			puntuacion=0;
			if(Diccionario::modo=='L') puntuacion = strlen(solucion.c_str());
			else{
				for(int i=0;i<strlen(solucion.c_str());++i)
					puntuacion += conj.puntuacion(solucion[i]);
			}

			cout << solucion << "\tPuntuacion: " << puntuacion << endl;
		}

		cout << endl;

		do{
			cout << "¿Quieres seguir jugando[s/n]?: ";
			cin >> bucle;
		}while(bucle!='s' && bucle!='n');
	}
	cout << "****************************************************" << endl;
	cout << "  JUEGO TERMINADO" << endl;
	cout << "****************************************************" << endl;
	return 0;
}