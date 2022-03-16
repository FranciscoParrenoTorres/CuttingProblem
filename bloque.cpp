#pragma warning (disable: 4786)

//tipos.h
#include "bloque.h"
//CONSTRUCTOR DE UN BLOQUE
BLOQUE::BLOQUE(int x1,int x2,int y1,int y2, char tipo,bool mover):
RECTAN(x1,x2,y1,y2)
{
	m_tipo=tipo;
	m_puedo_mover=mover;
};

BLOQUE::BLOQUE(int x1,int x2,int y1,int y2, char tipo):
RECTAN(x1,x2,y1,y2)
{
	m_tipo=tipo;
	m_puedo_mover=true;

};
BLOQUE::BLOQUE(int x1,int x2,int y1,int y2):
RECTAN(x1,x2,y1,y2)
{
	m_puedo_mover=true;


};
BLOQUE::BLOQUE(CRect &Rect, char tipo):
RECTAN(Rect)
{
	m_tipo=tipo;
	m_puedo_mover=true;


};
//Constructor de Rectángulo
RECTAN::RECTAN(int x1,int x2,int y1,int y2):
CRect(x1,x2,y1,y2)
{
	m_numero=0;
};
RECTAN::RECTAN(CRect &Rect):
CRect(Rect)
{
	m_numero=0;

};
//
MOVE::MOVE(BLOQUE &Bloque1,BLOQUE &Bloque2,std::list<BLOQUE> &ListaN,int Valor,std::list<RECTAN> lista)
{
	m_Bloque1=Bloque1;
	m_Bloque2=Bloque2;
	m_Valor=Valor;
	m_lista_perdidas=lista;
	m_lista_Bloques_Nuevos=ListaN;
	m_algo_nuevo=true;
};
MOVE::MOVE(BLOQUE &Bloque1,BLOQUE &Bloque2,int Valor)
{
	m_Bloque1=Bloque1;
	m_Bloque2=Bloque2;
	m_Valor=Valor;
	m_algo_nuevo=true;
};

MOVE::MOVE(MOVE &otro)
{
	m_Bloque1=otro.m_Bloque1;
	m_Bloque2=otro.m_Bloque2;
	m_Valor=otro.m_Valor;
	m_lista_perdidas=otro.m_lista_perdidas;
	m_lista_Bloques_Nuevos=otro.m_lista_Bloques_Nuevos;
	m_algo_nuevo=otro.m_algo_nuevo;
};
void MOVE::Igual(MOVE &otro)
{
	m_Bloque1=otro.m_Bloque1;
	m_Bloque2=otro.m_Bloque2;
	m_Valor=otro.m_Valor;
	m_lista_perdidas=otro.m_lista_perdidas;
	m_lista_Bloques_Nuevos=otro.m_lista_Bloques_Nuevos;
	m_algo_nuevo=otro.m_algo_nuevo;
};
