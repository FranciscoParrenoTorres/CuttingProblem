#ifndef Bloque_H
#define Bloque_H
//lectura y escritura

#pragma warning(disable: 4786)

#include <list>
#include <afxwin.h>
#define _WIN32_WINNT_MAXVER     0x0601
//CLASE Réctangulo
class RECTAN:public CRect{
	int m_numero;
	
public:
	//constructor
	RECTAN(int x1,int x2,int y1,int y2);
	RECTAN(){};
	RECTAN(CRect &Rect);
	void SetNumero( int r){m_numero=r;};
	int GetNumero(void){return m_numero;};
};

//CLASE BLOQUE
class BLOQUE:public RECTAN{
	char m_tipo;
	bool m_puedo_mover;
	
public:
	//constructor
	BLOQUE(int x1,int x2,int y1,int y2, char tipo,bool mover);
	BLOQUE(int x1,int y1,int x2,int y2,char tipo);
	BLOQUE(int x1,int y1,int x2,int y2);
	BLOQUE(){};
	BLOQUE(CRect &Rect, char tipo);
	bool PuedoMover(){return m_puedo_mover;};
	char GetTipo(){return m_tipo;};
	void SetTipo(char M){m_tipo=M;};
	void SetPuedoMover(bool r){m_puedo_mover=r;};
};

//CLASE MOVIMIENTO
class MOVE{
	BLOQUE m_Bloque1;
	BLOQUE m_Bloque2;
	std::list<BLOQUE> m_lista_Bloques_Nuevos;
	std::list<RECTAN> m_lista_perdidas;
	long int m_Valor;	
	bool m_algo_nuevo;
	
	
public:
	//constructor
	MOVE(BLOQUE &Bloque1,BLOQUE &Bloque2,std::list<BLOQUE> &listaN,int Valor,std::list<RECTAN> lista);
	MOVE(BLOQUE &Bloque1,BLOQUE &Bloque2,int Valor);
	MOVE(){};
	MOVE(MOVE &otro);
	void Igual(MOVE &otro);
	//sET
	void SetValor(int Val){m_Valor=Val;};
	void SetBloquesNuevos(std::list<BLOQUE> &listaN){m_lista_Bloques_Nuevos=listaN;};
	void SetListaPerdidas(std::list<RECTAN> lista){m_lista_perdidas=lista;};
	void SetAlgoNuevo(bool Val){m_algo_nuevo=Val;};
	//fUNCIONEs Get
	std::list<BLOQUE> &GetBloquesNuevos(void){return m_lista_Bloques_Nuevos;};
	int GetValor(void){return m_Valor;};
	bool GetAlgoNuevo(void){return m_algo_nuevo;};
	BLOQUE &GetBloqueAntiguo(){return m_Bloque1;};
	BLOQUE &GetBloqueNuevo(){return m_Bloque2;};
	std::list<RECTAN> &GetListaPerdidas(){return m_lista_perdidas;};
	std::list<BLOQUE> &GetListaBloques(){return m_lista_Bloques_Nuevos;};
};
#endif