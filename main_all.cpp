#pragma warning (disable: 4786)


//Cositas:

//Hay otra función como se dice en lo escrito para colocar piezas
//Recordar que para cuando son orientables está en el NUEVA es otra función HeurísticoOrdenStrip
//#include "Cutting.h"
//#include "Pallet.h"
#include <time.h>
#include <string>
#include <sys/timeb.h>
clock_t fintime_best;
extern  int DibujarOpenGL();
#include "Cutting.h"

void main(int argc,char **argv)
{
	int tipo_greedy = 2;
	int tipo_lista = 4;
	int tipo_aleator = 5;
	int tipo_mejora = 3;
	int tiempo_total = 60;
	//tipo algoritmo 
	//2 Tabu
	//1 Grasp
	//3 Heurístico
	int tipo_algoritmo = 1;
	int seed = 1;
	int max_Iter = 50000;
	int Seconds=100;
	int visible = 0;
	std::string file_to_read, file_to_write;
	if ((argc > 2)) //&& (argc % 2 == 1))
	{               //Se comprueba que haya pares de argumentos (y al menos un par)
		while (argc > 1)
		{
			if (strcmp(argv[1], "-t") == 0)
			{ //Tiempo
				sscanf(argv[2], "%d", &Seconds);
			}
			else if (strcmp(argv[1], "-Instancia") == 0)
			{ //File to read
				file_to_read = argv[2];
			}
			else if (strcmp(argv[1], "-Salida") == 0)
			{
				file_to_write = argv[2];
			}
			else if (strcmp(argv[1], "-Seed") == 0)
			{
				sscanf(argv[2], "%d", &seed);
			}
			else if (strcmp(argv[1], "-TipoAlgoritmo") == 0)
			{
				sscanf(argv[2], "%d", &tipo_algoritmo);
			}

			else if (strcmp(argv[1], "-iter") == 0)
			{
				sscanf(argv[2], "%d", &max_Iter);
			} //For the test
			else if (strcmp(argv[1], "-Greedy") == 0)
			{
				sscanf(argv[2], "%d", &tipo_greedy);
			}
			else if (strcmp(argv[1], "-Alea") == 0)
			{
				sscanf(argv[2], "%d", &tipo_aleator);
			} //For the test
			else if (strcmp(argv[1], "-Mejora") == 0)
			{
				sscanf(argv[2], "%d", &tipo_mejora);
			}
			else if (strcmp(argv[1], "-Lista") == 0)
			{
				sscanf(argv[2], "%d", &tipo_lista);
			}
			else if (strcmp(argv[1], "-Time") == 0)
			{
				sscanf(argv[2], "%d", &tiempo_total);
			}
			else if (strcmp(argv[1], "-Visible") == 0)
			{
				sscanf(argv[2], "%d",
					&visible); //Type=0 is the usual //Type=1 is the new one
			}
			argc -= 2;
			argv += 2;
		}
	}
	srand(seed);
	clock_t inicio,fintime;
	double tiempo,tiempo_best;
	inicio=clock();
	char nombre[100];
	strcpy(nombre, file_to_read.c_str());
	CUTTING Problema(nombre);
	Problema.LeerProblema(nombre);
	Problema.SetTotalTime(tiempo_total);
	Problema.SetDibujar(visible);
	int m=Problema.GetNumeroPiezas();
	int M=Problema.GetTotalPiezas();
/*
	int tot=Problema.GetTotalValor();
	int totSup=Problema.GetTotalSuperficie();
	int cota=Problema.CotaSuperiorArchivo();
	Problema.CotaSuperior();
*/
//	************GRASP
	//100000 con la mejora local rápida es lo mismo que 1000 iter de la lenta
//	if (tipo_mejora==1)

	Problema.SetMaxIteracionesGrasp(max_Iter);
//	else Problema.SetMaxIteracionesGrasp(1000);
//	Problema.SetMaxIteraciones(1500);
	Problema.SetMaxIteraciones(max_Iter/5);
	//Si vamos a hacer mejora local o no
	Problema.SetHacerMejoraLocal(true);
//	tipo_greedy=4;
//	tipo_lista=4;
//	tipo_aleator=5;
//	tipo_mejora=2;
//	Problema.SetHacerMejoraLocal(false);
	//1 elijo la más ancha
	//2 la más ancha con 0.01 por largo
	//3 la más ancha con 0.1 por largo
	//4 la más ancha con 0.5 por largo
	//5 el que mas se ajusta al horizonte del problema
	//6 el que tenga un mayor mínimo de las dos dimensiones
	//7 para cuando se pueden rotar las piezas resto 0.01 por largo
	//8 la más ancha con aleatorio por largo
	//9 el que utilizo
	Problema.SetTipoGreedy(tipo_greedy);
	//Tipo de lista de candidatos
	//**1 Por ciento
	//**2 por valor
	//**3 por probabilidad
	//**4 por valor min+alea*(max-min)
	Problema.SetTipoListaCandidatos(tipo_lista);
	//Tipo de delta
	//1 aleatorio en un rango (0.4,0.9)
	//2 Cada 250 iteraciones en aumento de 0.5 a 0.9
	//3 aleatorio en un rango (0.25,0.75)
	//4 Fijo en el valor el que le ponga en este caso FactorAleatorio
	//5 Reactive Grasp
	Problema.SetTipoAleatoriedad(tipo_aleator);
//	tipo_mejora=0;
	//Tipo de mejora
	//0 mejorando haciendo intercambios
	//1 quitando los últimos y fijando la pared
	//2 insertando en los huecos
	//3 mejora quitando un tanto porciento de las últimas colocadas
	//4 quitando los que se encuentre en el último trozo de tira
	//5 haciendo un reactive de las anteriores cuatro
	//6 primero con el 4 y luego el 6
	Problema.SetTipoMejora(tipo_mejora);
	if (tipo_mejora==7)
	Problema.SetFactorAleatorio(0.5);
	else
	Problema.SetFactorAleatorio(0.9);
	//Para el tabu
	Problema.SetDeterminista(true);
	Problema.SetPuedenRotarsePiezasGrasp(false);
	

	//Para el Tabu
	int sol = 0;
	//El segundo parametro indica si empieza con la solución del grasp o no
	if (tipo_algoritmo==2)
		sol=Problema.Tabu2DStrip(false,false,max_Iter);
	else
	{
		//	tipo_lista=9;

			//Para el Grasp
		bool hacer_tabu = false;
		if (tipo_algoritmo == 1)
		{
			if (tipo_mejora == 6)
			{
				Problema.SetTipoMejora(4);
				hacer_tabu = true;
			}
			Problema.SetDeterminista(false);
			Problema.WriteSolution();
			DibujarOpenGL();
			sol = Problema.GraspStrip(false);
			if (hacer_tabu == true) Problema.Tabu2DStrip(false, true, 50000);
		}
		else
		{

			//Para hacer el heurístico

		//	Para hacer el constructivo

			Problema.SetDeterminista(true);
			if (Problema.GetPuedenRotarsePiezasGrasp() == false)
				Problema.HeuristicoGreedyOrdenStrip(false);
			else
				Problema.HeuristicoGreedyOrdenStripRotacion(false);
			sol = Problema.GetValSolucion();
		}
	}
	//	Problema.PintarPiezas();




//	Problema.HeuristicoGreedy(false);
//	Problema.CotaSuperior();
	fintime=clock();
	tiempo=((double)(fintime-inicio))/CLOCKS_PER_SEC;
	tiempo_best=((double)(fintime_best-inicio))/CLOCKS_PER_SEC;
	//Si estamos haciendo tabu
//	printf("Tiempo %d %f MovDismi %d MovAumen %d",Problema.GetCota(),tiempo,Problema.GetHechoMovDismi(),Problema.GetHechoMovAumen());
//	Problema.Posible();
	FILE *fin;
	fin=fopen("Solcut.txt","a+");
//	printf("Time %f seg Solucion % d ",tiempo,sol);
//	fprintf(fin,"%s\t%d\t%d\t%d\t%d\t%d\n",argv[1],Problema.GetLargoTablero(),Problema.GetAnchoTablero(),sol,Problema.GetCota(),Problema.GetPosible());

//	fprintf(fin,"%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\t%d\n",argv[1],Problema.GetLargoTablero(),Problema.GetAnchoTablero(),m,M,sol,Problema.GetCota(),tiempo,Problema.GetIteracionesBest());
	fprintf(fin,"%s\t MaxL \t%d\t L \t%d\t%d\t%d\t%f\tTiempoBESt\t%f\t%d\t%d\t%d\t%d\t%d\t%d\n",nombre,Problema.GetLargoTablero(),Problema.GetAnchoTablero(),m,sol,tiempo,tiempo_best,Problema.GetMinPerdida(),tipo_greedy,tipo_lista,tipo_aleator,tipo_mejora,Problema.GetCota());
	//Numero de piezas y Valor, propiedades
/*
	int cotarea=Problema.CotaSuperiorArea();
	fprintf(fin,"%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",argv[1],Problema.GetLargoTablero(),Problema.GetAnchoTablero(),m,M,totSup,cotarea,tot,cota);
*/
	fclose(fin);
}
