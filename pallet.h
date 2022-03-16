#ifndef PALLET_H
#define PALLET_H
//lectura y escritura
#pragma warning(disable: 4786)
#define get_random(min,max) ((rand() %(int) (((max)+1)-(min)))+(min))
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//#include <iostream>
//#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include "Bloque.h"
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



typedef  std::pair<double, double> cota;
typedef  std::vector<int> inter_corto;
typedef  std::vector<double> intervalo;
typedef  std::vector<int> vec_short;
typedef  std::vector<short int> Cortos;
typedef std::list<BLOQUE> lista_BLOQUES;
//suplementaria para CotaNelisen
typedef struct VARCOTA{
	char name[10];
	float i1;
	float j1;
	unsigned char Eficiente;
	int cotinf;
	int cotsup;
}varcota;



#ifndef struct_var
#define struct_var
typedef struct VAR{
	unsigned char orientacion;
	int x;
	int y;
}var;
#endif
typedef struct PERDIDA{
	unsigned char orientacion;
	int x;
	int y;
	int PA;//Perdida derecha
	int PD;//Perdida Arriba
}perdida;

# define epsilon 0.00025


//CLASE PROBLEMA
class PALLET{
	int m_Ancho_Pallet;
	int m_L;
	int m_Largo_Pallet;
	int m_W;
	int m_Ancho_Caja;
	int m_l;
	int m_Largo_Caja;
	int m_w;
	//Dimensiones Reducidas
	int m_AnchoR_Pallet;
	int m_LargoR_Pallet;
		//Conjunto rasterpointsAncho

		//Conjunto S(Ancho)
	std::vector<int> m_SAncho;
			//Conjunto S(Ancho)
	std::vector<int> m_SRAncho;
	//Conjunto S(Largo)
	std::vector<int> m_SLargo;
	//Conjunto S(Largo)
	std::vector<int> m_SRLargo;

	//Variables y Restricciones
	std::vector<var> m_VectorDeVar;
	std::vector<var> m_VectorDeVarH;
	std::vector<var> m_VectorDeVarV;
	std::list<inter_corto> m_ListaDeRes;
	//

	//Valor de la solucion
	int m_ValSolucion;
	//Valor de la cota
	int m_Cota;
	//Solucion list de punteros a variables
	std::list<var*> m_Solucion;
	//Dimensiones del pallet originales
	int m_Ancho0_Pallet;
	int m_Largo0_Pallet;
	int m_Ancho0_Caja;
	int m_Largo0_Caja;

	//particiones Eficientes
	std::list<cota> m_Eficientes_X;
	std::list<cota> m_Eficientes_Y;
	//particiones sin perdida
	std::list<cota> m_Eficientes_L;
	std::list<cota> m_Eficientes_W;
	//
	std::list<perdida> m_Perdida_Bordes;
	std::list<var> m_Heuristico;
	std::list<var> m_Best;
	std::vector<vec_short> m_Perdida_Restri;
	bool m_simetria;
	bool m_nuevas;
	bool m_eliminadas;
	int m_lineales;
	std::list<RECTAN> m_lista_perdidas;
	std::list<BLOQUE> m_lista_bloques;
	std::list<BLOQUE> m_lista_tabu;
	std::list< std::list<BLOQUE> > m_lista_tabu2;
	std::list< std::list<RECTAN>  > m_lista_tabu_perdidas;
	//
	int m_tam_tabu_perdidas;
	//
	int m_tam_tabu2;
	//
	int m_tam_tabu;
	//
	int m_max_iteraciones;
	//
	bool m_paso_a_paso;
	//
	int m_iter_actual;
	//Mejor solucion por encima
	int m_best_sol;
	//Mejor solucion 
	int m_solbest;
	//Mejor solucion actual
	int m_sol_actual;
	//factor para dibujar
	int m_factor;
	int m_Hmin;
	int m_Hmax;
	int m_F_Rectangulo;
	bool m_Dibujar;
	//
	CClientDC *m_clientedc;
	//Estructura normal G4
	int m_G4_THorizontal;
	int m_G4_TVertical;
	int m_G4_HuecoH;
	int m_G4_HuecoV;
	int m_G4_CajasH;
	int m_G4_CajasV;
	int m_G4_PequeH;
	int m_G4_PequeV;
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
//	int m_movimientosval;
//	int m_movaumenval;
//	int m_movdismival;
	bool m_Eficientes;
	int m_lpartidow;
	int m_perdidaCota;
	bool m_no_hay;
	double m_proporcion;
	//
	int m_hechomovdismi;
	int m_hechomovaumen;
	//Para utilizar memoria 

	std::vector< std::vector<short int> > m_matrizH;
	std::vector< std::vector<short int> > m_matrizV;
	//Lo ancho o lo largo de la perdida asociada
	int m_gano;
//	 m_utilizados;
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
	//Peso positivo si el bloque anterior no era eficiente
	int EFIBLOQUE;
	int m_tipo_rectangulo;
	//Para juntar los rectangulos varias formas esta variable controla la
	//manera de juntarlos
	int m_tipo_junta;
	int m_max_valor;
		//
	int m_valor_maximo;
	//
	std::list<RECTAN> m_solbest_lista_perdidas;
	std::list<BLOQUE> m_solbest_lista_bloques;

public:
	//constructor
	PALLET(int X,int Y,int a,int b);
	PALLET(){};
	void CrearEficientes();
	void Clear();
	//destructor
	//funciones Set
	void SetAnchoPallet(int a){m_Ancho_Pallet=a;m_L=a;};
	void SetLargoPallet(int a){m_Largo_Pallet=a;m_W=a;};
	void SetAnchoRPallet(int a){m_AnchoR_Pallet=a;};
	void SetLargoRPallet(int a){m_LargoR_Pallet=a;};

	void SetAnchoCaja(int a){m_Ancho_Caja=a;m_l=a;};
	void SetLargoCaja(int a){m_Largo_Caja=a;m_w=a;};
	void SetHeuristico(std::list<var>& a){m_Heuristico=a;};
	void SetBest(std::list<var>& a){m_Best=a;};
	void SetValSolucion(int a){m_ValSolucion=a;};
	void SetCotaDowsland(int a){m_Cota=a;};
	void SetFactorDibujar(int factor){m_factor=factor;};
	void SetClienteDC(CClientDC *d){m_clientedc=d;};
	void SetSolucion(std::list<var*> &lista){m_Solucion=lista;};
	void SetTamTabu(int a){m_tam_tabu=a;};
	void SetMaxIteraciones(int a){m_max_iteraciones=a;};
	void SetPasoaPaso(bool a){m_paso_a_paso=a;};
	//funciones Get
	//regresa 
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

	int GetTamTabu(void){return m_tam_tabu;};
	int GetAnchoPallet(){return m_Ancho_Pallet;};
	int GetLargoPallet(){return m_Largo_Pallet;};
	int GetAnchoRPallet(){return m_AnchoR_Pallet;};
	int GetLargoRPallet(){return m_LargoR_Pallet;};

	int GetAnchoCaja(){return m_Ancho_Caja;};
	int GetLargoCaja(){return m_Largo_Caja;};
	int GetValSolucion(){return m_ValSolucion;};
	int GetCotaDowsland(){return m_Cota;};
	double GetMitadAncho(){return (double)(m_AnchoR_Pallet)/2;}
	double GetMitadLargo(){return (double)(m_LargoR_Pallet)/2;}
	int GetMitadPalletH(){ return m_AnchoR_Pallet*ceil(((double)m_LargoR_Pallet/2));};
	int GetMitadPalletV(){ return ceil(((double)m_AnchoR_Pallet/2))*m_LargoR_Pallet;};
	double GetAreaPallet() {return (double)m_AnchoR_Pallet*m_LargoR_Pallet;};
	double GetAreaCaja() {return (double)m_Ancho_Caja*m_Largo_Caja;};
	int GetIteraciones(){return m_iter_actual;};
	std::list<var> &GetHeuristico(){return m_Heuristico;};
	std::list<var> &GetBest(){return m_Best;};
//	bool EsTabu2(MOVE &M1,int tipo_Mov);

	//Devuelve las particiones
	std::list<cota> &GetParticionesX(){return m_Eficientes_X;};
	std::list<cota> &GetParticionesY(){return m_Eficientes_Y;};
	std::list<perdida> &GetListaDePerdidas(){return m_Perdida_Bordes;};
	//Devuelve list de restricciones
	std::list<inter_corto> &GetListaDeRes(){return m_ListaDeRes;};
	//Devuelve Perdida Restricciones
	std::vector<vec_short> &GetPerdidaRestri(){return m_Perdida_Restri;};
	//Devuelve list de Solucion
	std::list<var*> &GetSolucion(){return m_Solucion;};
	//Devuelve list de Variables
	std::vector<var> &GetVectorDeVar(){return m_VectorDeVar;};
	//Devuelve el número de variables que tiene el problema
	int GetNumeroVar(){return m_VectorDeVar.size();};
	//Devuelve el número de restricciones que tiene el problema más la de Cota más la de Simetria V más la otra H
	//Si los dos impares son dos más depende
	int GetNumeroRes();
	int GetNumeroResSime();
	void SetMetidasSimetria(bool a){m_simetria=a;};
	bool GetMetidasSimetria(void){return m_simetria;};
	void SetEliminadas(bool a){m_eliminadas=a;};
	bool GetEliminadas(void){return m_eliminadas;};
	void ConstruirVariables(void);
	int HeuristicoG4(void);
	void SetMetidasNuevas(bool a){m_nuevas=a;};
	bool GetMetidasNuevas(void){return m_nuevas;};
	//Devuelve un vector con las dimensiones del reducido y la
	//Cota de Nelisen
	intervalo  CotaReduNelisen(int);
	//heuristico de cuatro bloques me devuelve
	//un vector con a,b,c,d,e,f,g,h y la cota
	intervalo  Heuristico4Bloques(void);
	//aqui además i,j,k,l segun sea en horizontal o vertical
	intervalo  Heuristico5Bloques(void);
	//Solucion exacta con lindo.
	int CotaNelisen(void);

	friend int ComprobarParticiones(PALLET &P1,PALLET &P2);
	//Escribe caja
	void CotaBarnes(void);
	//Particion Perfecta
	int ParticionPerfecta(int);

//	void EscribePallet();
	void InicializarLineales(){m_lineales=0;};
	void SetLineales(int a){m_lineales++;};
	int GetLineales(void){return m_lineales;};
	int no_esta_Perdida(perdida &, std::list<perdida> &);
//	void ActualizarPerdida(BLOQUE &B1);
//	int Tabu(int , int ,int );
	int Tabu(bool);
	int Perdida_Entre_Bloques(BLOQUE &B1,BLOQUE &B2);
//	MOVE Disminuir_Bloques(BLOQUE &B1,int x,int y);
	std::list<RECTAN> PerdidasBloques(BLOQUE &B1,BLOQUE &B2);
	std::list<BLOQUE> Construir_Bloques(intervalo solu);
	void CompactarPerdida(std::list<RECTAN> &Nuevas);
	void CompactarBloques(MOVE &M1,bool);
	std::list<RECTAN> JuntarPerdida(std::list<RECTAN> &Nuevas,char tipo);
	std::list<BLOQUE> Paletizar(std::list<RECTAN> &lista,char tipo);
	int CuatroBloques(RECTAN &Rect,char tipo);
	int Heuristico1Bloque(RECTAN &Rect,char tipo);
	bool PuedeDisminuirse(BLOQUE &B1,int xder,int xizq, int yarr, int yaba,bool bloque_nulo);
	bool PuedeAumentarse(BLOQUE &B1,int xizq,int xder,int yaba, int yarr);
	void Actualizar_Perdida(std::list<BLOQUE> &listaBlo,std::list<RECTAN> &listaPer);
	bool PorDondeDisminuir(BLOQUE &B1,int x,int y);
	void Actualizar_Lista_Bloques(MOVE &BestMove);
//	bool EsTabu(BLOQUE &B1);
	 bool PALLET::EsTabuSinLaUltima(std::list<BLOQUE> &lista);
	int Rectangulo_menor_estan_perdidas(std::list<RECTAN> &lista);
	bool EsTabu(std::list<BLOQUE> &lista);
	MOVE Aumentar_Bloques(BLOQUE &B1,int xder,int xizq,int yarr, int yaba);
	void AumentarBloque(MOVE &M1,int );
	void Add_Lista_Tabu(BLOQUE &B1);
	void DibujarBloques(std::list<BLOQUE> &,std::list<RECTAN> &,int contador,int sol,int perdida,int solbest,bool parar,int veces);
	void DibujarSolucion(std::list<BLOQUE> &,std::list<RECTAN> &, int ,int );

	bool ComprobarBloquesNoIntersectan(std::list<BLOQUE> &);
	void JuntarPerdida(void);
	int Contar(std::list<RECTAN> &lista);
	void JuntarPerdida(std::list<RECTAN> &lista);

	int Contar(std::list<BLOQUE> &lista);
	bool JuntarDosRectangulos(RECTAN &Nuevo1,RECTAN &Nuevo2,RECTAN &Nuevo3,RECTAN &rect1,RECTAN &rect2,char tipo);
	MOVE Disminuir_Bloques(BLOQUE &B1,int xder,int xizq,int yarr, int yaba);
	bool  Existe_Perdida(RECTAN &rect);
	bool  Existe_Perdida(std::list<RECTAN> &lista,RECTAN &rect);
	bool ParticionEficienteY(int i);
	bool ParticionEficienteX(int i);
	bool ParticionEficienteY(int i,char tipo);
	bool ParticionEficienteX(int i,char tipo);
	bool ComprobarBloquesYPerNoIntersectan(std::list<BLOQUE> &lista,std::list<RECTAN> &lista2);

	//Numeradas en el sentido de las agujas del reloj
	//1 esquina inferior izquierda 
	void ColocarEsquinaMasCercana(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,char tipo);
	bool  Existe_Perdida(RECTAN &rect,int tipo);
	bool  Existe_Perdida(std::list<RECTAN> &lista,RECTAN &rect,int tipo);
	std::list<RECTAN> CompactarPerdida2(std::list<RECTAN> &Nuevas);
	void cortar_Bloques(BLOQUE &b1,MOVE &M1);
	//0 no corta , 1 si
	int Restar_Rectangulo(RECTAN &b1,RECTAN &b2,RECTAN &B1,RECTAN &B2,RECTAN &B3,RECTAN &B4);
	bool Valida_Simetria(std::list<RECTAN> &lista);
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
	bool EsTabuPerdidas(std::list<RECTAN> &lista);
	void Add_Lista_TabuPerdidas(std::list<RECTAN> &lista);
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
	int ContarFrecuencias(std::list<BLOQUE> &lista);
	double Porcentaje_Eficiente(BLOQUE &B);
	long int EvaluarMovimiento(MOVE &);
	void AlgoritmoUnBloque(std::list<BLOQUE> &,std::list<RECTAN> &);
	void VerificarSolucion(std::list<BLOQUE> &,std::list<RECTAN> &,int );
	int ContarH(std::list<BLOQUE> &listaT);
	bool EstaLaPerdida(std::list<RECTAN> &,RECTAN &); 
	bool EstaElBloque(std::list<BLOQUE> &,BLOQUE &);
	int PerdidaMayor(std::list<RECTAN> &);
	int PerdidaEnLados(std::list<RECTAN> &listaP);
	void ActualizarConjuntoReferencia(MOVE &M,int valor);
	int MinimoConjuntoRef(void);
	void MeterBloqueSolucion(BLOQUE &B1,std::list<BLOQUE> &listaB);
	int CombinarSolucionesConjuntoRef();
	void cortar_Bloques(BLOQUE &b1,BLOQUE &b2,std::list<BLOQUE> &listaB);
	void EscribirSolucionLatex(std::list<BLOQUE> &lista);
	bool no_esta_Bloque(BLOQUE &b1,std::list<BLOQUE> &lista);

//	bool operator < (PATHRE& otra) {return fobjetivo<otra.fobjetivo;};

};
#endif