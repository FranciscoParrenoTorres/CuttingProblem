#ifndef CUTTING_H
#define CUTTING_H
//lectura y escritura
#pragma warning(disable: 4786)
#define MAX_IMPORTANCIA 99999;
#define get_random(min,max) ((rand() %(int) (((max)+1)-(min)))+(min))
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//#include <iostream>
//#include <fstream>
#include <time.h>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include "Bloque.h"
#include <sys/timeb.h>
//#include "Pallet.h"
/*
#define map std::map
#define pair std::pair
#define vector std::vector
#define set2 std:set
#define list std::list
//#define ofstream1 std::ofstream
//#define ifstream1 std::ifstream
#define sort1 std::sort
#define reverse1 std::reverse
#define cout1 std::cout*/
//#define operator << std::operator << 
//#define <<< std::<<

extern  int DibujarOpenGL();
//#ifdef _WIN32 
//extern  int DibujarOpenGL();
/*void DibujarOpenGL() {
	return;
}*/
//#endif

typedef  std::pair<double, double> cota;
typedef  std::vector<int> inter_corto;
typedef  std::vector<double> intervalo;
typedef  std::vector<int> vec_short;
typedef  std::vector<short int> Cortos;
typedef std::list<BLOQUE> lista_BLOQUES;


typedef struct PIEZA{
//	unsigned char orientacion;
	int largo;
	int ancho;//W
	int min;//Cantidad mínima
	int max;//Cantidad máxima
	int valor;
	int num;//Numero de pieza utilizadas
	int frecuencia;
}Pieza;
typedef struct CANDI{
	int numero;
	int nump;
	char orienta;
}candi;
typedef struct ETABU{
	int area;
	RECTAN Union;
	int num;
}etabu;
#ifndef struct_caminito
#define struct_caminito
typedef struct PATHRE{
	int fobjetivo;
	int num_bloques;
	std::list<BLOQUE> lista_bloques;
	std::list<RECTAN> lista_perdidas;
}pathre;
#endif

# define epsilon 0.00025
# define infinito 99999

//CLASE PROBLEMA
class CUTTING{
	int m_L; //Largo tablero
	int m_W; //Ancho tablero
	int m_Numpiezas; //Numero de piezas
	int m_Q;//Total de piezas posibles
	int m_b;//Es el minimo de pisinger
	bool m_conpesos;
	std::vector< Pieza > m_Piezas;//Lista de piezas
//	std::vector< Piezas> m_PiezasArea;
	char m_Nombre[60];//Nombre de la instancia
	//Valor de la solucion
	int m_ValSolucion;
	//Yipo de greedy
	int m_tipo;
	//Tipo de lista de candidatos
	int m_tipo_de_lista;
	//Tipo de aleatoriedad
	int m_tipo_aleatoriedad;
	//Total del valor de las piezas
	int m_total_valor;
	int m_total_superficie;
	int m_TrozoFijado;//Trozo fijado

	//
	int m_tipo_mejora;
	bool m_Restringido;//Si el problema es restringido o no
	bool m_Posible;//si el problema es restringido si es posible la solucion
	bool m_Determinista; //Si el heurístico es determinista o no
	bool m_PuedenRotarsePiezas;//Si se pueden rotar las piezas o no
	int m_NumPiezasBestSol;
	int m_NumBloques;
	int m_iter_solbest;
	//Valor de la cota
	int m_Cota;
	//Solucion list de punteros a variables
	std::list<BLOQUE> m_Solucion;
	std::list<RECTAN> m_lista_perdidas;
	std::list<BLOQUE> m_lista_bloques;
	std::list<BLOQUE> m_lista_bloques_fijos;

	std::list<BLOQUE> m_lista_tabu;
	std::list< etabu  > m_lista_tabu_new;
	int m_MinLargo;
	int m_MinAncho;
	int m_MaxLargo;
	int m_MaxAncho;
	int m_TotalAncho;
	int m_AreaTotalRestante;
	int m_EmpiezaPorAqui;
	bool	m_HacerMejoraLocal;
	std::list< std::list<RECTAN>  > m_lista_tabu_perdidas;

	//
	std::vector<int> m_lista_intG4;
//	std::list<strg4> m_lista_GCuatros;

	//
	//Factor aleatorio para con cuales se queda
	double m_FactorAleatorio;
	//Factor aleatorio para con cuales se queda
	double m_FactorAleatorio2;

	bool m_paso_a_paso;
	//
	int m_iter_actual;
	//Mejor solucion por encima
	int m_best_sol;
	//Mejor solucion 
	int m_solbest;
	//Mejor solucion actual
	int m_sol_actual;
	//
	int	m_perdida_menor;

	//factor para dibujar
	double m_factor;
	int m_Hmin;
	int m_Hmax;
	int m_Vmin;
	int m_Vmax;
	int m_F_Rectangulo;
	bool m_Dibujar;
	int m_noquiero;
	bool m_utilizar_frecuencias;
	//

	CClientDC *m_clientedc;
	//Máximo de cajas horizontales eficientes L
	int m_hL;
	//Máximo de cajas verticales eficientes L
	int m_vL;
	//Máximo de cajas horizontales eficientes W
	int m_hW;
	//Máximo de cajas verticales eficientes W
	int m_vW;
	//Numero de movimientos que estudio
	int m_movimientos;
	int m_movaumen;
	int m_movdismi;
	int m_totalmov;
	int m_movtabu;
	bool m_todas;
	int m_max_iteraciones;
	int m_tam_tabu;
	int m_tam_tabu_perdidas;
	int m_max_iteracionesGrasp;
	int m_max_iteracionesCadaGrasp;
	int	m_PerdidaFijado;


//	int m_movimientosval;
//	int m_movaumenval;
//	int m_movdismival;
	bool m_Eficientes;
	int m_lpartidow;
	int m_perdidaCota;
	bool m_PathRelinking;
	bool m_no_hay;
	double m_proporcion;
	//
	int m_hechomovdismi;
	int m_hechomovaumen;
	//Pesos
	int NUEVO;
	//Lista tabu 2
	int TABU2;
	//Peso para soluciones no cumplen simétria
	int SIMETRIA;
	//Peso que se le resta para soluciones con todos los bloques eficientes.
	int EFICIENTES;
	//Peso para el valor de cada caja de la solución
	int VALOROPTIMO;
	//Peso negativo para soluciones con bloques que no puedan estar en una solu-
	//ción mejor que la actual
	int OPTIMO;
	//Peso para el número de los bloques de la solución
	int VALBLOQUES;
	//
	int PERDIDALADOS;
	int PERDIDAMAYOR;
	//Peso positivo si el bloque anterior no era eficiente
	int EFIBLOQUE;
	int CAMBIOTIPO;
	int m_tipo_rectangulo;
	//Para juntar los rectangulos varias formas esta variable controla la
	//manera de juntarlos
	int m_tipo_junta;
	int m_max_valor;
	int m_iter_sin_mejorar;
	int m_diversificaciones;
	bool m_Diversificar;
	int m_iter_diversificar;	
		//
	//Conjunto de referencia
	std::list<pathre> m_conjunto_ref;

	//
	bool m_Intensificar;
	bool m_Raster;
	bool m_Simetria;
	bool m_fijos;
	int m_valor_maximo;
	int m_valor_maximo2;
	//Para variables de estudio de los parámetros
	int m_max_rect;
	int m_min_rect;
	int m_max_blo;
	int m_min_blo;
	bool m_empieza_sol_grasp;
//	std::list< MOVE > m_lista_grasp;
	//Para guardar la mejor solución
	std::list<RECTAN> m_solbest_lista_perdidas;
	std::list<BLOQUE> m_solbest_lista_bloques;
	int m_total_time = 60;
public:
	//constructor
	CUTTING(int L,int W,int numpiezas);
	CUTTING(char *nombre);

	CUTTING(){};
	void LeerProblema(char *name);
	void Clear();
	//destructor
	//funciones Set
	void SetDibujar(int a) { m_Dibujar = a; };
	void SetEmpiezaSolGrasp(bool a) { m_empieza_sol_grasp=a; };
	void SetTotalTime(int a) { m_total_time = a; };
	void SetLargoTablero(int a){m_L=a;};
	void SetAnchoTablero(int a){m_W=a;};
	void SetNombre(char *name){strcpy(m_Nombre,name);};
	void SetValSolucion(int a){m_ValSolucion=a;};
	void SetCota(int a){m_Cota=a;};
	void SetFactorDibujar(double factor){m_factor=factor;};
	void SetClienteDC(CClientDC *d){m_clientedc=d;};
	void SetMaxIteraciones(int a){m_max_iteraciones=a;};
	void SetMaxIteracionesGrasp(int a){m_max_iteracionesGrasp=a;};
	void SetMaxIteracionesCadaGrasp(int a){m_max_iteracionesCadaGrasp=a;};
	void SetPasoaPaso(bool a){m_paso_a_paso=a;};
	void SetDeterminista(bool a){m_Determinista=a;};
	void SetTipoMejora(int a){m_tipo_mejora=a;};
	void SetTipoGreedy(int a){m_tipo=a;};
	void SetTipoListaCandidatos(int a){m_tipo_de_lista=a;};	
	void SetTipoAleatoriedad(int a){m_tipo_aleatoriedad=a;};
	void SetHacerMejoraLocal(bool a){m_HacerMejoraLocal=a;};
	void SetFactorAleatorio(double a){m_FactorAleatorio=a;};
	void SetPuedenRotarsePiezasGrasp(bool a){m_PuedenRotarsePiezas=a;};
	int GetPuedenRotarsePiezasGrasp(){return m_PuedenRotarsePiezas;};
	int CotaSuperiorArchivo(void);		
	int CotaInferiorArchivoStrip(void);		
	//funciones Get
	//regresa 
	int GetTotalTime() { return m_total_time; };
	int GetDiversificaciones(){return m_diversificaciones;};
	int GetMovimientos(){return m_movimientos;};
	int GetMovDismi(){return m_movdismi;};
	int GetMovAumen(){return m_movaumen;};
/*	int GetMovimientosVal(){return m_movimientos_val;};
	int GetMovDismiVal(){return m_movdismi_val;};
	int GetMovAumenVal(){return m_movaumen_val;};
*/	int GetHechoMovDismi(){return m_hechomovdismi;};
	int GetHechoMovAumen(){return m_hechomovaumen;};
	int GetMaxIteraciones(){return m_max_iteraciones;};
	bool GetPasoaPaso(){return m_paso_a_paso;};
	bool GetPosible(){return m_Posible;};
	int GetTotalValor(){return m_total_valor;};
	int GetTotalSuperficie(){return m_total_superficie;};
	int GetTamTabu(void){return m_tam_tabu;};
	int GetLargoTablero(){return m_L;};
	int GetAnchoTablero(){return m_W;};
	char *GetNombre(){return m_Nombre;};
	int GetValSolucion(){return m_ValSolucion;};
	int GetNumeroPiezas(){return m_Numpiezas;};
	int GetMinPerdida(){return m_perdida_menor;};
	int GetTotalPiezas(){return m_Q;};
	int GetCota(){return m_Cota;};
	int GetNumPiezasMejorSol(){return m_NumPiezasBestSol;};	
	int ContarPiezas(std::list<BLOQUE> &listaT);
	int GetNumBloquesMejorSol(){return m_NumBloques;};
	double GetMitadLargo(){return (double)(m_L)/2;}
	double GetMitadAncho(){return (double)(m_W)/2;}
	double GetAreaTablero() {return (double)m_L*m_W;};
	int GetIteraciones(){return m_iter_actual;};
	int GetIteracionesBest(){return m_iter_solbest;};
	int Grasp(bool dibu);
	int GraspStrip(bool dibu);
	bool ComprobarBloquesYPerNoIntersectan(std::list<BLOQUE> &lista,std::list<RECTAN> &lista2);
	bool Disminuir_Bloques(BLOQUE &B1,int x,int y);
	void Bloques_Hacia_Las_Esquinas(BLOQUE &B, std::list<RECTAN> &listaP);
	void Bloques_Hacia_Las_EsquinasStrip(BLOQUE &B, std::list<RECTAN> &listaP);
	int RespuestaAJuntar(RECTAN &RectGrande,RECTAN &Rect1,RECTAN &Rect2);
	void ColocarNumeros(std::list<BLOQUE> &lista);

	void PintarPiezas(void);
	void EscribirPiezas(void);
	bool BloqueCercaPerdida(BLOQUE &B,RECTAN &Rect);
	int JuntarPerdida(std::list<RECTAN> &lista,BLOQUE &B, char tipo);
	int JuntarDosRectangulosImportancia(RECTAN &Nuevo1,RECTAN &Nuevo2,RECTAN &Nuevo3,RECTAN &rect1,RECTAN &rect2,char tipo);
	void MejoraLocalRapida();
	int ElegirAleatorioPorProbabilidad(std::vector< std::pair<double, candi > > &lista_candidatos,double total);
	int CotaSuperiorArea();


	MOVE Disminuir_Bloques_Tabu(BLOQUE &B1,int x,int y);


//	**** Funciones
	void PiezasNoPosiblesEnSolMejor(int sb);
	void HeuristicoGreedy(bool dibu);
	void HeuristicoGreedyStrip(bool dibu);
	void HeuristicoGreedyOrden(bool dibu);
	int Tabu2DStrip(bool dibu,bool,int );
	void EscribirSolucionStripLatex(std::list<BLOQUE> &lista);
	void ColocarEsquinaMasCercana(RECTAN &Rect,BLOQUE &B1);
	int ContarSolucion(std::list<BLOQUE> &listaB);
	int ContarSolucionStrip(std::list<BLOQUE> &listaB);
	void ElegirPieza(BLOQUE &b1,RECTAN &Rect,int tipo,int num);
	void ElegirPiezaAleatoria(BLOQUE &b1,RECTAN &Rect, int tipo,int num);
	void ElegirPiezaStrip(BLOQUE &b1,RECTAN &Rect,int tipo,int num);
	void ElegirPiezaAleatoriaStrip(BLOQUE &b1,RECTAN &Rect, int tipo,int num);
	//me dice si cabe alguna pieza de las posibles
	//DETALLE si el porblema es restingido solo deberia mirar las que necesito
	int CabeAlguna(RECTAN &Rect,int);
	//me dice si el problema es restringido si la solución es posible
	void Posible(void);
	// devuelve uno de los posibles para elegir
	int ElegirAleatorioPorCiento(std::vector< std::pair<double, candi > > &);
	//devuelve uno de los posibles para elegir
	int ElegirAleatorioPorValor(std::vector< std::pair<double, candi > > &,double);
	//Rellenar un rectángulo me rellena el réctangulo
	void Rellenar(std::list<BLOQUE> &listaB,std::list<RECTAN> &lista,int con_este_numero_no);
	//Rellenar un rectángulo me rellena el réctangulo
	void RellenarStrip();
	void CotaSuperior();
	void EscribirSolucion(std::list<BLOQUE> &lista);
	void EscribirSolucionLatex(std::list<BLOQUE> &lista);
	void JuntarPerdida(std::list<RECTAN> &lista,char );
	void VerificarSolucion(std::list<BLOQUE> &lista_bloques,std::list<RECTAN> &lista_perdidas,int lugar);
	int Contar(std::list<RECTAN> &lista);
	int Contar(std::list<BLOQUE> &lista);
//	bool EsTabu2(MOVE &M1,int tipo_Mov);
	void MejoraLocal();
	void MejoraLocalRapidaStrip();
	void RepararNumeros(std::list<BLOQUE> &lista);
	void Actualizar_Perdida(BLOQUE &,std::list<RECTAN> &);
	void Actualizar_Perdida(std::list<BLOQUE> &,std::list<RECTAN> &);
	void Elijo_Menor_Lista(RECTAN ,RECTAN &,int );
	void BorrarListaPerdidas(RECTAN &R);



	//Devuelve list de Solucion
	intervalo  Heuristico4Bloques(void);
	//aqui además i,j,k,l segun sea en horizontal o vertical
	intervalo  Heuristico5Bloques(void);
	//Solucion exacta con lindo.
	int CotaNelisen(void);

//	void ActualizarPerdida(BLOQUE &B1);
//	int Tabu(int , int ,int );
	int Tabu(bool);
	int Perdida_Entre_Bloques(BLOQUE &B1,BLOQUE &B2);
//	MOVE Disminuir_Bloques(BLOQUE &B1,int x,int y);
	std::list<RECTAN> PerdidasBloques(BLOQUE &B1,BLOQUE &B2);
	std::list<BLOQUE> Construir_Bloques(intervalo solu);
	void CompactarPerdida(std::list<RECTAN> &Nuevas);
	void CompactarBloques(MOVE &M1);
	std::list<BLOQUE> Paletizar(std::list<RECTAN> &lista,char tipo);
	MOVE Aumentar_Bloques_UnaPerdida(int num,int,char);

	int CuatroBloques(RECTAN &Rect,char tipo);
	int Heuristico1Bloque(RECTAN &Rect,char tipo);
	bool PuedeDisminuirse(BLOQUE &B1,int xder,int xizq, int yarr, int yaba,bool bloque_nulo);
	bool PuedeAumentarse(BLOQUE &B1,int xizq,int xder,int yaba, int yarr);
	bool PorDondeDisminuir(BLOQUE &B1,int x,int y);
	void Actualizar_Lista_Bloques(MOVE &BestMove);
//	bool EsTabu(BLOQUE &B1);
	bool EsTabuSinLaUltima(std::list<BLOQUE> &lista);
	int Rectangulo_menor_estan_perdidas(std::list<RECTAN> &lista);
	int EsTabu(MOVE &);
	void AumentarBloque(MOVE &M1 );
	void Add_Lista_Tabu(BLOQUE &B1);
	void DibujarBloques(std::list<BLOQUE> &,std::list<RECTAN> &,int contador,int sol,int perdida,int solbest,bool parar,int veces);
	void DibujarSolucion(std::list<BLOQUE> &,std::list<RECTAN> &, int ,int );
	void DibujarBloques(std::list<BLOQUE> &,std::list<RECTAN> &,int contador,int sol,int perdida,int solbest,bool parar,int veces,BLOQUE &);
	void DibujarSolucion(std::list<BLOQUE> &,std::list<RECTAN> &, int ,int , BLOQUE &);
	bool ComprobarBloquesNoIntersectan(std::list<BLOQUE> &);
//	void JuntarPerdida(void);

	bool JuntarDosRectangulos(RECTAN &,RECTAN &,RECTAN &,RECTAN &,RECTAN &,char );
	bool  Existe_Perdida(RECTAN &rect);
	bool  Existe_Perdida(std::list<RECTAN> &lista,RECTAN &rect);
	bool ParticionEficienteY(int i);
	bool ParticionEficienteX(int i);
	bool ParticionEficienteY(int i,char tipo);
	bool ParticionEficienteX(int i,char tipo);

	//Numeradas en el sentido de las agujas del reloj
	//1 esquina inferior izquierda 
	void ColocarEsquinaMasCercana(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho);
	void ColocarEsquinaMasCercanaStrip(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho);
	bool  Existe_Perdida(RECTAN &rect,int tipo);
	bool  Existe_Perdida(std::list<RECTAN> &lista,RECTAN &rect,int tipo);
	std::list<RECTAN> CompactarPerdida2(std::list<RECTAN> &Nuevas);
	void cortar_Bloques(BLOQUE &b1,MOVE &M1);
	//0 no corta , 1 si
	int Restar_Rectangulo(RECTAN &b1,BLOQUE &b2,RECTAN &B1,RECTAN &B2,RECTAN &B3,RECTAN &B4);
//	bool Valida_Simetria(std::list<RECTAN> &lista);
	bool Valida_Optimo(std::list<BLOQUE> &lista);
	int OptimoTipoI(void);		
	void Calcular_Estructura_G4(int );
	void ColocarG4(std::list<RECTAN> &lista,std::list<BLOQUE> &listablo,RECTAN &Rect,char tipo,int x,int y,int);
	bool EsTabu2(BLOQUE &B1);
	void Add_Lista_Tabu2(std::list< BLOQUE> &lista,std::list <BLOQUE> &lista2);
//	int Rectangulo_menor_estan_perdidas(std::list<RECTAN> &lista);
	bool Lista_de_Perdidas_Iguales(std::list<RECTAN> &lista,std::list<RECTAN> &lista2);
	int ProximoBloque(BLOQUE &B,int tipo);
	int ProximoBloque(std::list<BLOQUE> &lista,BLOQUE &B,int tipo);
	void  ProximoBloque(std::list<RECTAN> &,BLOQUE &,int ,RECTAN &);

	void ColocarG4_recursivo_ancho(std::list<RECTAN> &lista,std::list<BLOQUE> &listablo,RECTAN &Rect,int tam);
	void ColocarG4_recursivo_largo(std::list<RECTAN> &lista,std::list<BLOQUE> &listablo,RECTAN &Rect,int tam);
	bool Comprobar_Puede_Mejorar(BLOQUE &B1,BLOQUE &B2,char tipo);
	bool PerdidaPosibleX(BLOQUE &B1,int x);
	bool PerdidaPosibleY(BLOQUE &B1,int x);
	bool EsTabu2SinLaUltima(BLOQUE &B1);
	bool Es_Eficiente(std::list<BLOQUE> &lista);
	void Bloques_Hacia_Las_Esquinas(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP);
	void Bloques_Hacia_Las_EsquinasStrip(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP);
	int OptimoTipoII(void);
	int Cuantas_Cajas(std::list<BLOQUE> &lista,RECTAN &Rect);
	int Contar_Cajas_Interseccion(BLOQUE &B1,RECTAN &Rect1);
	void Mejorar_Con_Bloques_G4(std::list<BLOQUE> &lista_blo,std::list<RECTAN> &lista_per);
	int BloqueCercaPerdidas(BLOQUE &B,int val);
	bool Es_Eficiente_Bloque(BLOQUE &B);
	void CalcularMaximosCajas(void);
	void ColocarG4_recursivo_ancho_varias(std::list<RECTAN> &lista,std::list<BLOQUE> &listablo,RECTAN &Rect,int tam);
	int MayorPerdida();
	bool EsTabuPerdidasSinLaUltima(std::list<RECTAN> &lista);
	bool Es_Perfecto_Bloque(BLOQUE &B);
	bool TieneRasterPoint(int x, int y, char tipo);
	void EscribirBloquesPantalla(std::list<BLOQUE> &lista);
	void EscribirBloques(std::list<BLOQUE> &lista);
	bool EstaBloque(BLOQUE &B,std::list<BLOQUE> lista);
	bool  TodosTieneRasterPoint(std::list<BLOQUE> &lista);
	bool Es_Perfecta(int tam,char tipo,char lado);
	bool ParticionEficiente(int i, char meto, char lado);
	bool TieneRasterPoint(int x, int y, char tipo,int x2,int y2);
	int CuantosG4(int Ancho, int Largo);
	int Restar_Rectangulo(BLOQUE &b1,BLOQUE &b2,RECTAN &B1,RECTAN &B2,RECTAN &B3,RECTAN &B4);
	void cortar_Bloques_Rectangulos(BLOQUE &b1,MOVE &M1);
	void CrearMatrices(void);
	void ActualizarMatrices(void);
	double Porcentaje_Eficiente(BLOQUE &B);
	int EvaluarMovimiento(MOVE &);
	void AlgoritmoUnBloque(std::list<BLOQUE> &,std::list<RECTAN> &);
	int ContarH(std::list<BLOQUE> &listaT);
	bool EstaLaPerdida(std::list<RECTAN> &,RECTAN &); 
	bool EstaElBloque(std::list<BLOQUE> &,BLOQUE &);
	int PerdidaMayor(std::list<RECTAN> &);
	int PerdidaEnLados(std::list<RECTAN> &listaP);
	void ActualizarConjuntoReferencia(MOVE &M,int valor);
	int MinimoConjuntoRef(void);
	int MaximoConjuntoRefPerdidas(void);
	int CaminoDeAaB(PATHRE A,PATHRE &B);
	void MeterBloqueSolucion(BLOQUE &B1,std::list<BLOQUE> &listaB);
	int CombinarSolucionesConjuntoRef();
	void cortar_Bloques(BLOQUE &b1,BLOQUE &b2,std::list<BLOQUE> &listaB);
	void Bloques_Hacia_Las_Esquinas_Combinar(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP);
	void CotaNelisenMaxMin(int Cota);
	bool CumpleNumHV(std::list<BLOQUE> &listaB);
	void OscilacionEstrategica(void);
	int PerdidasPequenas(std::list<RECTAN> &listaP);
	void MostrarFrecuencias(void);
	int VecesQueHaAparecidoElBloque(BLOQUE &B);
	int BusquedaLocal(bool dibu);
	void AlgoritmoCuatroBloques(std::list<BLOQUE> &,std::list<RECTAN> &);
	int ParticionesGrandes(std::list<BLOQUE> &listaB);
	bool BloquesGrandes(std::list<BLOQUE> &listaB);
	int NoQuieroParticionesPerfectas(std::list<BLOQUE> &listaB);
	bool Es_un_huecoG4(int large,int wid);
	void Calcular_Estructura_G4_Unica(int vez);
	void Elijo_Menor_Lista(RECTAN R, RECTAN &resultante, int tipo_orden, std::list<RECTAN> &lista);
	void Elijo_Menor_ListaStrip(RECTAN R, RECTAN &resultante, int tipo_orden, std::list<RECTAN> &lista);

	//Nuevo
	std::pair<int,int> Maximo_Restriccion_X(inter_corto &);
	std::pair<int,int> Maximo_Restriccion_Y(inter_corto &);
	void BorrarListaPerdidas(RECTAN &R, std::list<RECTAN> &lista);
	void Add_Lista_Tabu(MOVE &M1);
	bool Valida_Simetria(std::list<RECTAN> &lista);
	int Perdida_Mitad(std::list<RECTAN> &lista);
	MOVE Aumentar_Bloques_Esquina(int num,int cuantos,char sentido, RECTAN &Rect1);
	void ColocarEsquinaMasCercana(RECTAN &Rect,BLOQUE &B1,int esq);
	MOVE Aumentar_Bloques(int num,int cuantos,char sentido, RECTAN &Rect1,int esq);
	int EsTabuPerdidas(MOVE &M1);
	void Add_Lista_TabuPerdidas(std::list<RECTAN> &lista);
	int EsTabuNew(MOVE &M1);
	void Add_Lista_TabuNew(std::list<RECTAN> &lista);
	int Perdida_Mitad(std::list<RECTAN> &lista, CRect &rect);
	void BorrarFrecuencias(void);
	void ActualizarFrecuencias(void);
	int ContarFrecuencias(std::list<BLOQUE> &lista);
	bool EsPosible(void);
	void HeuristicoGreedyOrdenStrip(bool dibu);
	void Elijo_Menor_ListaStrip(RECTAN R, RECTAN &resultante, int tipo_orden,bool all);
	int CabeAlgunaAncho(RECTAN &Rect);
	int ActualizarMinMax(void);
	int DondeColocoMonaci(RECTAN &Rect, BLOQUE &B);
	int Altura(int A,int tipo);
	void ColocarEsquinaMonaciStrip(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho);
	int PiezaMayorEsteRectangulo(RECTAN &R);
	void JuntarPerdidaStrip(std::list<RECTAN> &lista, char tipo);
	int AreaRestante(int A);
	int AreaRestanteSiguiente(RECTAN &Rect,int largo_suple,int ancho_pieza,int long_pieza);
	void Bloques_Hacia_Las_EsquinasStrip(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP,int min);
	void MejoraLocalRapidaTrozoStrip();
	void MejoraLocalRapidaEPCStrip();
	void AumentarBloque(BLOQUE &M1);
	void Aumentar_Bloques_UnaPerdidaStrip(int num,int cuantos);
	void ColocarEsquinaMasCercanaStrip(RECTAN &Rect,BLOQUE &B1);
	void MejoraLocalRapidaTabuStrip();
	int AreaRestanteSiguiente(RECTAN &rectan,int largo_bloque,int ancho_bloque,int ancho_pieza, int long_pieza);
	void ColocarEsquinaMonaciModiStrip(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho);
	int DondeColocoMonaciModi(RECTAN &Rect, BLOQUE &B);
	void Actualizar_Perdida_Simetria(BLOQUE &B1,int,int );
	int Altura(int A,int tipo,BLOQUE &B);
	void HeuristicoGreedyOrdenStripRotacion(bool dibu);
	int PiezaMayorEsteRectangulo(RECTAN &R,int);
	int Buscar_Pieza_No_Metida(int ,int ,int );
	bool Existe_Bloque(RECTAN &rect,int tipo);
	void JuntarPiezasIguales();
	void JuntarRectangulo(RECTAN &rect);
	int ContarPerdidaSegura(std::list<RECTAN> &lista);
	void MejoraLocalIntercambioStrip();
	void CambiarBloque(BLOQUE &B1,BLOQUE &B2);
	void FijarPiezasInicialmente();
	int CotaInferiorL2();
	int CotaInferiorL1();
	void WriteSolution();


/*	void DibujarOpenGL() {
		return;
	}
	*/






};
#endif