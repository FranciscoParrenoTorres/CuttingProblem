#pragma warning (disable: 4786)
//#define TAM_TABU 21
//tipos.h
#include "Pallet.h"


//#define list std::list
//#define vector std::vector
// Funciones utilizadas para hacer Variables y Restricciones
int bueno(int i,int a,int b);
int no_esta_lista(std::list<inter_corto> &,int,int);
int no_esta(int x, std::vector<int> &vec);
//Nuevo

int maximoRpertenece(int x,std::vector<int> &vec);
void primer_lineal(std::list<varcota> & varX,std::list<varcota> & varY,int AnchoP,int LargoP,int AnchoC, int LargoC,char salida2[10],int tipo,double primcota,char varia[300]);

//CONSTRUCTOR DE UN TABLERO
PALLET::PALLET(int X,int Y,int p,int q)
{
	m_Nueva_Redu=true;
	m_nuevas=false;
	m_eliminadas=false;
	m_simetria=false;
	m_ValSolucion=0;
	m_L=X;
	m_W=Y;
	m_l=p;
	m_w=q;
	m_Ancho_Pallet=X;
	m_Largo_Pallet=Y;
	m_Ancho_Caja=p;
	m_Largo_Caja=q;
	m_AnchoR_Pallet=X;
	m_LargoR_Pallet=Y;
	m_Ancho0_Pallet=X;
	m_Largo0_Pallet=Y;
	m_Ancho0_Caja=p;
	m_Largo0_Caja=q;
	m_Cota=0;
	//Particiones del lado X
	int maxim=0;
	int M=m_Ancho_Pallet;
	int a=m_Ancho_Caja;
	int b=m_Largo_Caja;
	for(int register i=0;i<=(M/a);i++)
	{
		for(int register j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{
			//Si consigo el máximo
			if ((i*a+b*j)>maxim)
			maxim=i*a+b*j;
			//Si es eficiente la meto
			if ((M-(i*a+b*j))<b)
			{
			cota pt(i,j);
			
			m_Eficientes_X.push_back(pt);
				if ((M-(i*a+b*j))==0)
				{
					m_Eficientes_L.push_back(pt);
				}

			}
			

			
		}
	}
//	pintar_lista_cota(lista);
	m_AnchoR_Pallet=maxim;
	maxim=0;
	M=m_LargoR_Pallet;
	a=m_Ancho_Caja;
	b=m_Largo_Caja;
	for( i=0;i<=(M/a);i++)
	{
		for(int register j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{
			//Si consigo el máximo
			if ((i*a+b*j)>maxim)
			maxim=i*a+b*j;
			//Si es eficiente la meto
			if ((M-(i*a+b*j))<b)
			{
			cota pt(i,j);
			
			m_Eficientes_Y.push_back(pt);
			if ((M-(i*a+b*j))==0)
			{
				m_Eficientes_W.push_back(pt);
			}

			}
			

			
		}
	}
	m_LargoR_Pallet=maxim;
}
void PALLET::Clear()
{
	m_Ancho_Pallet;
	m_Largo_Pallet;
	m_Ancho_Caja;
	m_Largo_Caja;
	//Dimensiones Reducidas
	m_AnchoR_Pallet;
	m_LargoR_Pallet;
		//Conjunto rasterpointsAncho

		//Conjunto S(Ancho)
	m_SAncho.clear();
			//Conjunto S(Ancho)
	m_SRAncho.clear();
	//Conjunto S(Largo)
	m_SLargo.clear();
	//Conjunto S(Largo)
	m_SRLargo.clear();

	//Variables y Restricciones
	m_VectorDeVar.clear();
	m_VectorDeVarH.clear();
	m_VectorDeVarV.clear();
	m_ListaDeRes.clear();
	//Valor de la solucion
	m_ValSolucion=0;
	//Valor de la cota
	m_Cota=0;
	//Solucion list de punteros a variables
	m_Solucion.clear();
	//Dimensiones del pallet originales
	m_Ancho0_Pallet=0;
	m_Largo0_Pallet=0;
	m_Ancho0_Caja=0;
	m_Largo0_Caja=0;

	m_Eficientes_X.clear();
	m_Eficientes_Y.clear();
	m_Eficientes_L.clear();
	m_Eficientes_W.clear();
	m_Perdida_Bordes.clear();
	m_Heuristico.clear();
	m_Best.clear();
	m_Perdida_Restri.clear();
	m_lista_perdidas.clear();
	m_lista_bloques.clear();
	m_lista_tabu.clear();
	//factor para dibujar

}
void PALLET::CrearEficientes()
{	m_nuevas=false;
	m_eliminadas=false;
	m_simetria=false;
	m_ValSolucion=0;
	int p=m_Ancho_Caja;
	int q=m_Largo_Caja;
	m_AnchoR_Pallet=m_Ancho_Pallet;
	m_LargoR_Pallet=m_Largo_Pallet;
	m_Ancho0_Pallet=m_Ancho_Pallet;
	m_Largo0_Pallet=m_Largo_Pallet;
	m_Ancho0_Caja=p;
	m_Largo0_Caja=q;

	//Particiones del lado X
	int maxim=0;
	int M=m_Ancho_Pallet;
	int a=m_Ancho_Caja;
	int b=m_Largo_Caja;
	for(int register i=0;i<=(M/a);i++)
	{
		for(int register j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{
			//Si consigo el máximo
			if ((i*a+b*j)>maxim)
			maxim=i*a+b*j;
			//Si es eficiente la meto
			if ((M-(i*a+b*j))<b)
			{
			cota pt(i,j);
			
			m_Eficientes_X.push_back(pt);
			if ((M-(i*a+b*j))==0)
			{
				m_Eficientes_L.push_back(pt);
			}
			}
			

			
		}
	}
//	pintar_lista_cota(lista);
	m_AnchoR_Pallet=maxim;
	maxim=0;
	M=m_LargoR_Pallet;
	a=m_Ancho_Caja;
	b=m_Largo_Caja;
	for( i=0;i<=(M/a);i++)
	{
		for(int register j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{
			//Si consigo el máximo
			if ((i*a+b*j)>maxim)
			maxim=i*a+b*j;
			//Si es eficiente la meto
			if ((M-(i*a+b*j))<b)
			{
			cota pt(i,j);
			
			m_Eficientes_Y.push_back(pt);
			if ((M-(i*a+b*j))==0)
			{
				m_Eficientes_W.push_back(pt);
			}

			}
			

			
		}
	}
	m_LargoR_Pallet=maxim;
}
//Esta es para el pallet

void PALLET::ConstruirVariables(void)
{
	int a=m_Ancho_Caja;
	int b=m_Largo_Caja;

	//Construyo conjuntos de puntos formado por particiones 
		//Ancho
	for(int register ii=0;ii<=(m_AnchoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=0;jj<=(m_AnchoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_AnchoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,m_SAncho)==0)
				m_SAncho.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
		}
	}
	//Largo
	for(ii=0;ii<=(m_LargoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj1=0;jj1<=(m_LargoR_Pallet/m_Largo_Caja);jj1++)
		{
			if ((ii*m_Ancho_Caja+jj1*m_Largo_Caja<m_LargoR_Pallet) && (ii*m_Ancho_Caja+jj1*m_Largo_Caja>0))
			{
			if (no_esta(ii*m_Ancho_Caja+jj1*m_Largo_Caja,m_SLargo)==0)
				m_SLargo.push_back(ii*m_Ancho_Caja+jj1*m_Largo_Caja);
			}
		}
	}
	
	std::sort(m_SAncho.begin(),m_SAncho.end());
	std::sort(m_SLargo.begin(),m_SLargo.end());

	//Construyo lista de Variables
	//Construyo SLH
	std::vector<int> SHW,SHL,SVW,SVL,SRHW,SRHL,SRVW,SRVL;
	//SHW
	for(ii=1;ii<=(m_AnchoR_Pallet/m_Ancho_Caja);ii++)
	{
		for( int register jj=0;jj<=(m_AnchoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_AnchoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SHW)==0)
				SHW.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
		}
	}
	//SVW
	for(ii=0;ii<=(m_AnchoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=1;jj<=(m_AnchoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_AnchoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SVW)==0)
				SVW.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
		}
	}
	//SVL
	for(ii=1;ii<=(m_LargoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=0;jj<=(m_LargoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_LargoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{
			{
	//			printf("%4d",ii*m_Ancho_Caja+jj*m_Largo_Caja);
			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SVL)==0)
				SVL.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
			}
		}
	}
	//SHL
	for(ii=0;ii<=(m_LargoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=1;jj<=(m_LargoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_LargoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SHL)==0)
			{
	//			printf("%4d",ii*m_Ancho_Caja+jj*m_Largo_Caja);
				SHL.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
			}
		}
	}
	
	std::sort(SHL.begin(),SHL.end());
	std::sort(SHW.begin(),SHW.end());
	std::sort(SVL.begin(),SVL.end());
	std::sort(SVW.begin(),SVW.end());
	//Ya tengo S(L)
	//Ahora los raster points
	int LmenosR,maxSR;
	std::vector<int>::iterator v1,v2;
//	m_SRAncho.push_back(0);
//	m_SRLargo.push_back(0);
//SRHW
	for (v1=SHW.begin();v1!=SHW.end();v1++)
	{
		LmenosR=m_AnchoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SAncho);
		if (LmenosR>m_L/2 && LmenosR!=maxSR)
			maxSR=LmenosR;
		if (no_esta(maxSR,SRHW)==0)
			SRHW.push_back(maxSR);
	}
	//SRH
	for (v1=SHL.begin();v1!=SHL.end();v1++)
	{
		LmenosR=m_LargoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SLargo);
		if (LmenosR>m_W/2 && LmenosR!=maxSR)
			maxSR=LmenosR;

		if (no_esta(maxSR,SRHL)==0)
			SRHL.push_back(maxSR);
	}
	//SRVW
	for (v1=SVW.begin();v1!=SVW.end();v1++)
	{
		LmenosR=m_AnchoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SAncho);
		if (LmenosR>m_L/2 && LmenosR!=maxSR)
			maxSR=LmenosR;

		if (no_esta(maxSR,SRVW)==0)
			SRVW.push_back(maxSR);
	}
	//SRVW
	for (v1=SVL.begin();v1!=SVL.end();v1++)
	{
		LmenosR=m_LargoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SLargo);
		if (LmenosR>m_W/2 && LmenosR!=maxSR)
			maxSR=LmenosR;

		if (no_esta(maxSR,SRVL)==0)
			SRVL.push_back(maxSR);
	}
//Ya tengo los raster points
	std::sort(SRHL.begin(),SRHL.end());
	std::sort(SRHW.begin(),SRHW.end());
	std::sort(SRVL.begin(),SRVL.end());
	std::sort(SRVW.begin(),SRVW.end());

	//Construyo lista de Variables y de Restricciones
	//Horizontales
	int total_var=0,L,W;
	L=m_AnchoR_Pallet;
	W=m_LargoR_Pallet;
	inter_corto vec2;
	
	for(v1=SRHW.begin();v1!=SRHW.end() ;v1++)
	{
		for(v2=SRHL.begin();v2!=SRHL.end();v2++)
		{
			var pp={'H',(*v1),(*v2)};
			m_VectorDeVar.push_back(pp);
			m_VectorDeVarH.push_back(pp);
		}
		
    }
    //Verticales    
	for(v1=SRVW.begin();v1!=SRVW.end() ;v1++)
	{
		for(v2=SRVL.begin();v2!=SRVL.end();v2++)
		{
			var pp={'V',(*v1),(*v2)};
			m_VectorDeVar.push_back(pp);
			m_VectorDeVarV.push_back(pp);
		}
		
    }


}

/*
void PALLET::ConstruirVariables(void)
{
//	m_Nueva_Redu=true;
//	m_Nueva_Redu=false;
	int a=m_Ancho_Caja;
	int b=m_Largo_Caja;
	//Construyo conjuntos de puntos formado por particiones 
	//Ancho
	for(int register ii=0;ii<=(m_AnchoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=0;jj<=(m_AnchoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_AnchoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,m_SAncho)==0)
				m_SAncho.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
		}
	}
	//Largo
	for(ii=0;ii<=(m_LargoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj1=0;jj1<=(m_LargoR_Pallet/m_Largo_Caja);jj1++)
		{
			if ((ii*m_Ancho_Caja+jj1*m_Largo_Caja<m_LargoR_Pallet) && (ii*m_Ancho_Caja+jj1*m_Largo_Caja>0))
			{
			if (no_esta(ii*m_Ancho_Caja+jj1*m_Largo_Caja,m_SLargo)==0)
				m_SLargo.push_back(ii*m_Ancho_Caja+jj1*m_Largo_Caja);
			}
		}
	}
	
	std::sort(m_SAncho.begin(),m_SAncho.end());
	std::sort(m_SLargo.begin(),m_SLargo.end());
	//Ahora los raster points antiguos
	std::vector<int>::iterator v1,v2;
	int LmenosR,maxSR;

	m_SRAncho.push_back(0);
    m_SRLargo.push_back(0);

	for (v1=m_SAncho.begin();v1!=m_SAncho.end();v1++)
	{
		LmenosR=m_AnchoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SAncho);
		if (no_esta(maxSR,m_SRAncho)==0)
			m_SRAncho.push_back(maxSR);
	}
	for (v2=m_SLargo.begin();v2!=m_SLargo.end();v2++)
	{
		LmenosR=m_LargoR_Pallet-(*v2);
		maxSR=maximoRpertenece(LmenosR,m_SLargo);
		if (no_esta(maxSR,m_SRLargo)==0)
			m_SRLargo.push_back(maxSR);
	}
	printf("\n");
	std::sort(m_SRAncho.begin(),m_SRAncho.end());
	std::sort(m_SRLargo.begin(),m_SRLargo.end());


	//Construyo lista de Variables
	//Construyo SLH
	std::vector<int> SHW,SHL,SVW,SVL,SRHW,SRHL,SRVW,SRVL;
	//SHW
	for(ii=1;ii<=(m_AnchoR_Pallet/m_Ancho_Caja);ii++)
	{
		for( int register jj=0;jj<=(m_AnchoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_AnchoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SHW)==0)
				SHW.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
		}
	}
	//SVW
	for(ii=0;ii<=(m_AnchoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=1;jj<=(m_AnchoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_AnchoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SVW)==0)
				SVW.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
		}
	}
	//SVL
	for(ii=1;ii<=(m_LargoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=0;jj<=(m_LargoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_LargoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{
			{
//				printf("%4d",ii*m_Ancho_Caja+jj*m_Largo_Caja);
			if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SVL)==0)
				SVL.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
			}
			}
		}
	}
	//SHL
	for(ii=0;ii<=(m_LargoR_Pallet/m_Ancho_Caja);ii++)
	{
		for(int register jj=1;jj<=(m_LargoR_Pallet/m_Largo_Caja);jj++)
		{
			if (((ii*m_Ancho_Caja+jj*m_Largo_Caja)<m_LargoR_Pallet) && ((ii*m_Ancho_Caja+jj*m_Largo_Caja)>0))
			{

				if (no_esta(ii*m_Ancho_Caja+jj*m_Largo_Caja,SHL)==0)
				{
//					printf("%4d",ii*m_Ancho_Caja+jj*m_Largo_Caja);
					SHL.push_back(ii*m_Ancho_Caja+jj*m_Largo_Caja);
				}
			}
		}
	}
	
	std::sort(SHL.begin(),SHL.end());
	std::sort(SHW.begin(),SHW.end());
	std::sort(SVL.begin(),SVL.end());
	std::sort(SVW.begin(),SVW.end());
	//Ya tengo S(L)
	//Ahora los raster points
//	m_SRAncho.push_back(0);
//	m_SRLargo.push_back(0);
    SRHW.push_back(0);
    SRHL.push_back(0);
    SRVL.push_back(0);
    SRVW.push_back(0);

//SRHW
	for (v1=SHW.begin();v1!=SHW.end();v1++)
	{
		LmenosR=m_AnchoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SAncho);
		if (no_esta(maxSR,SRHW)==0)
			SRHW.push_back(maxSR);
	}
	//SRH
	for (v1=SHL.begin();v1!=SHL.end();v1++)
	{
		LmenosR=m_LargoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SRLargo);
		if (no_esta(maxSR,SRHL)==0)
			SRHL.push_back(maxSR);
	}
	//SRVW
	for (v1=SVW.begin();v1!=SVW.end();v1++)
	{
		LmenosR=m_AnchoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SRAncho);
		if (no_esta(maxSR,SRVW)==0)
			SRVW.push_back(maxSR);
	}
	//SRVW
	for (v1=SVL.begin();v1!=SVL.end();v1++)
	{
		LmenosR=m_LargoR_Pallet-(*v1);
		maxSR=maximoRpertenece(LmenosR,m_SRLargo);
		if (no_esta(maxSR,SRVL)==0)
			SRVL.push_back(maxSR);
	}
//Ya tengo los raster points
	std::sort(SRHL.begin(),SRHL.end());
	std::sort(SRHW.begin(),SRHW.end());
	std::sort(SRVL.begin(),SRVL.end());
	std::sort(SRVW.begin(),SRVW.end());
	//Construyo lista de Variables y de Restricciones
	//Horizontales
	int total_var=0,L,W;
	L=m_AnchoR_Pallet;
	W=m_LargoR_Pallet;
	inter_corto vec2;
	if (m_Nueva_Redu==true)
	{
		for(v1=SRHW.begin();v1!=SRHW.end() ;v1++)
		{
			for(v2=SRHL.begin();v2!=SRHL.end();v2++)
			{
				var pp={'H',(*v1),(*v2)};
				if (((*v1)+m_Ancho_Caja<=m_AnchoR_Pallet) && ((*v2)+m_Largo_Caja<=m_LargoR_Pallet))
					m_VectorDeVar.push_back(pp);
			}
		
	    }
	    //Verticales    
		for(v1=SRVW.begin();v1!=SRVW.end() ;v1++)
		{
			for(v2=SRVL.begin();v2!=SRVL.end();v2++)
			{
				var pp={'V',(*v1),(*v2)};
				if (((*v1)+m_Largo_Caja<=m_AnchoR_Pallet) && ((*v2)+m_Ancho_Caja<=m_LargoR_Pallet))
					m_VectorDeVar.push_back(pp);
			}
		
		}
	}
	else
	{

		for(v2=m_SRLargo.begin();v2!=m_SRLargo.end();v2++)
		{
			for(v1=m_SRAncho.begin();v1!=m_SRAncho.end();v1++)
			{
				var pp={'V',(*v1),(*v2)};
				if (((*v1)+m_Largo_Caja<=m_AnchoR_Pallet) && ((*v2)+m_Ancho_Caja<=m_LargoR_Pallet))
				m_VectorDeVar.push_back(pp);
				var pp2={'H',(*v1),(*v2)};
				if (((*v1)+m_Ancho_Caja<=m_AnchoR_Pallet) && ((*v2)+m_Largo_Caja<=m_LargoR_Pallet))
				m_VectorDeVar.push_back(pp2);

			}
		
		}
	}
	//Voy a construir una lista con la variable y su perdida derecha o izquierda
	//Para luego meter restricciones
	L=m_AnchoR_Pallet;
	W=m_LargoR_Pallet;
	int RestoArriba1,RestoDerecha1;
	//Horizontal
	for(v1=SRHW.begin();v1!=SRHW.end() ;v1++)
	{
		for(v2=SRHL.begin();v2!=SRHL.end();v2++)
		{
			int kkk1=(*v1);
			int kkk2=(*v2);
			RestoArriba1=ParticionPerfecta(W-((*v2)+b));
			RestoDerecha1=ParticionPerfecta(L-((*v1)+a));
			if (RestoArriba1>=RestoDerecha1 && RestoArriba1>0)
			{
				perdida px={'H',-1,(*v2),RestoArriba1,0};
				if (no_esta_Perdida(px,m_Perdida_Bordes)==0)
					m_Perdida_Bordes.push_back(px);
			}
			if (RestoDerecha1>0)
			{
				perdida px={'H',(*v1),-1,0,RestoDerecha1};
				if (no_esta_Perdida(px,m_Perdida_Bordes)==0)
					m_Perdida_Bordes.push_back(px);
			}
		}
		
    }
    //Verticales    
	for(v1=SRVW.begin();v1!=SRVW.end() ;v1++)
	{
		for(v2=SRVL.begin();v2!=SRVL.end();v2++)
		{
			RestoArriba1=ParticionPerfecta(W-((*v2)+a));
			RestoDerecha1=ParticionPerfecta(L-((*v1)+b));

			if (RestoDerecha1>=RestoArriba1 && RestoDerecha1>0)
			{
				perdida px={'V',(*v1),-1,0,RestoDerecha1};
				if (no_esta_Perdida(px,m_Perdida_Bordes)==0)
					m_Perdida_Bordes.push_back(px);
			}
			if (RestoArriba1>0)
			{
				perdida px={'V',-1,(*v2),RestoArriba1,0};
				if (no_esta_Perdida(px,m_Perdida_Bordes)==0)
					m_Perdida_Bordes.push_back(px);
			}
		}
		
    }

		//Construyo lista de Restricciones
	//Tendré las que aparecian en los raster points antiguos
	//Construyo conjunto de puntos que tenia antes
		//Construyo SL
	//Ya tengo S(L)
	//Ahora los raster points antiguos
	if (m_Nueva_Redu==true)
	{
		 //Recorro las variables y si no esta en la lista pues no la meto
		std::vector<var> ::iterator itV;
		for (itV=m_VectorDeVar.begin();itV!=m_VectorDeVar.end();itV++)
		{
			if (no_esta_lista(m_ListaDeRes,(*itV).x,(*itV).y)==0)
			{
				inter_corto vec;

				vec.push_back((*itV).x);
				vec.push_back((*itV).y);
				m_ListaDeRes.push_back(vec);
			}

		}
//		inter_corto vec;
//		vec.push_back(m_AnchoR_Pallet-m_Ancho_Caja);
//		vec.push_back(m_LargoR_Pallet-m_Ancho_Caja);
//		m_ListaDeRes.push_back(vec);
		//Debo meter todas las que tienen una variable y la de la esquina seguro 
		//todas esas ya las he metido ahora falta meter las restantes
		// ahora faltaría ver si alguna más debo de meter
		//solo tendría que estudiar las que no esten metidas ya que las otras entran seguro
		std::sort(m_SRAncho.begin(),m_SRAncho.end());
		std::sort(m_SRLargo.begin(),m_SRLargo.end());

		int register l,k;
		total_var=0;
		for(v2=m_SRLargo.begin();v2!=m_SRLargo.end();v2++)
		{
			for(v1=m_SRAncho.begin();v1!=m_SRAncho.end();v1++)
			{
				if (no_esta_lista(m_ListaDeRes,(*v1),(*v2))==0)
				{
					inter_corto vec;
					vec.push_back((*v1));
					vec.push_back((*v2));
					std::pair<int,int> uno=Maximo_Restriccion_X(vec);
					std::pair<int,int> dos=Maximo_Restriccion_Y(vec);
					if (!((uno.first==dos.first) && (uno.second==dos.second) ))
					m_ListaDeRes.push_back(vec);
					else
					{
						int kk=9;
					}
				}

			}
   
	    }	
	}
	else
	{
		std::sort(m_SRAncho.begin(),m_SRAncho.end());
		std::sort(m_SRLargo.begin(),m_SRLargo.end());

		int register l,k;
		total_var=0;
		for(v2=m_SRLargo.begin();v2!=m_SRLargo.end();v2++)
		{
			for(v1=m_SRAncho.begin();v1!=m_SRAncho.end();v1++)
			{
				k=(*v1);
				l=(*v2);
				total_var=1;
				if (total_var>0)
				{
					inter_corto vec;
					if (vec.size()!=0) vec.erase(vec.begin(),vec.end());
					vec.push_back(k);
					vec.push_back(l);
					m_ListaDeRes.push_back(vec);
				}

			

			}
   
	    }	
	}
/*
	//******************
	//Ya tengo la lista de lugares donde voy a poner un raster point
	// Ahora tendría que mirar cuales son las perdidas en cada lugar
	//esto se hace mirando cual es el siguiente raster o el maximo del
	//pallet, por arriba o por la derecha y guardandonos este valor
	// esto sirve por que existen determinadas zonas que se deben de cubrir 
	// igual a 1 si consideramos las perdidas
	int contador=0,perdidaResTotal=0;
	int minimoderecha=99999,minimoarriba=99999;
	int Desperdicio=3;
	std::list<inter_corto>::iterator itlis1,itlis2;
	for (itlis1=m_ListaDeRes.begin();itlis1!=m_ListaDeRes.end();itlis1++)
	{
		int k11=(*itlis1)[0];
		int k12=(*itlis1)[1];
		minimoderecha=99999,minimoarriba=99999;
		vec_short vshort;
		for (itlis2=m_ListaDeRes.begin();itlis2!=m_ListaDeRes.end();itlis2++)
		{
			int k21=(*itlis2)[0];
			int k22=(*itlis2)[1];

			if (((*itlis1)[0]==(*itlis2)[0]) && ((*itlis1)[0]==(*itlis2)[0]))
				continue;
			if ((((*itlis2)[0]-(*itlis1)[0])<minimoderecha) && (((*itlis2)[0]-(*itlis1)[0])>0))
				minimoderecha=((*itlis2)[0]-(*itlis1)[0]);
			if ((((*itlis2)[1]-(*itlis1)[1])<minimoarriba) && (((*itlis2)[1]-(*itlis1)[1])>0))
				minimoarriba=((*itlis2)[1]-(*itlis1)[1]);
		}
		if (minimoderecha==99999)
		{
			minimoderecha=m_AnchoR_Pallet-(*itlis1)[0];
		}
		if (minimoarriba==99999)
		{
			minimoarriba=m_LargoR_Pallet-(*itlis1)[1];
		}
		perdidaResTotal=minimoderecha*minimoarriba;
		vshort.push_back(perdidaResTotal);
		vshort.push_back(minimoderecha);
		vshort.push_back(minimoarriba);
		m_Perdida_Restri.push_back(vshort);
		if ((((*itlis1)[0]+minimoderecha)<(m_AnchoR_Pallet/2)) && (((*itlis1)[1]+minimoarriba)<(m_LargoR_Pallet/2)))
		{
			if (perdidaResTotal>(Desperdicio/2))
			{
				contador++;
				continue;
			}
		}
			
		if (perdidaResTotal>Desperdicio) contador++;
	}	
*/	
	//**********
//}

//Devuelve un vector con las componentes de la siguiente manera
// Primer bloque horizontal segundo vertical empezando en la esquina 
//derecha, tercero horizonta empezando en la esquina derecha superior
// cuarto vertical empezando en la esquina izqda vertical 

intervalo PALLET::Heuristico4Bloques(void)
{
	std::list<cota> lista_X=m_Eficientes_X;
	std::list<cota> lista_Y=m_Eficientes_Y;
	std::list<cota> ::iterator itx1,ity1,it2,it3;

	int V,W,a,b,c,d,e,f,g,h,maximo=0;
	//buscar partición perfecta
	V=m_AnchoR_Pallet;

	W=m_LargoR_Pallet;
	intervalo salida;
	int a1=m_Ancho_Caja;
	int b1=m_Largo_Caja;
	for (itx1=lista_X.begin();itx1!=lista_X.end();itx1++)
	{
		b=(*itx1).first;
		for (ity1=lista_Y.begin();ity1!=lista_Y.end();ity1++)
		{
			if (b!=0)
			{
				a=(*ity1).second;//primer Rectangulo a,b
			}
			else a=0;

			for (it2=lista_Y.begin();it2!=lista_Y.end();it2++)
			{

				c=(*itx1).second;
				d=(*it2).first;
				if (c==0 || d==0) {c=0;d=0;}

				for (it3=lista_X.begin();it3!=lista_X.end();it3++)
				{
					e=(*it2).second;
					f=(*it3).first;
					h=(*ity1).first;
					g=(*it3).second;
					if (e==0 || f==0) {e=0;f=0;}
					if (h==0 || g==0) {h=0;g=0;}

					if ((a*b+c*d+e*f+g*h) >= maximo && !((a+e>(W/b1)) && (b+f>(V/a1))) && !((h+d>(W/a1)) && (g+c>(V/b1))))
					{
					//	cout1<<"\n"<<a<<"x"<<b<<"\t"<<c<<"x"<<d<<"\t"<<e<<"x"<<f<<"\t"<<g<<"x"<<h<<"\t"<<"Total"<<"\t"<<a*b+c*d+e*f+g*h;
						maximo=a*b+c*d+e*f+g*h;
						if (salida.size()!=0) (salida.clear());
						//primer bloque en horizontal
						//segundo bloque en vértical
						//tercer bloque en horizontal
						//cuarto bloque en vértical
						salida.push_back(b);
						salida.push_back(a);
						salida.push_back(c);
						salida.push_back(d);
						salida.push_back(f);
						salida.push_back(e);
						salida.push_back(g);
						salida.push_back(h);
						salida.push_back(maximo);
					//	cout1<<"\n"<<a<<"x"<<b<<"\t"<<c<<"x"<<d<<"\t"<<e<<"x"<<f<<"\t"<<g<<"x"<<h<<"\t"<<"Total"<<"\t"<<a*b+c*d+e*f+g*h;
						maximo=a*b+c*d+e*f+g*h;
					}
				}
			}
		}
	}
	return salida;
}
//Devuelve un vector con las componentes de la siguiente manera
// Primer bloque horizontal segundo vertical empezando en la esquina 
//derecha, tercero horizonta empezando en la esquina derecha superior
// cuarto vertical empezando en la esquina izqda vertical 
// quinto horizontal en el centro, sexto vertical en el centro.
//examina el valor de la solucion y si es mejor actualiza solucion
/* --------------------
   |                  |
   |                  |
   |                  |
   |                  |
   --------------------*/

intervalo PALLET::Heuristico5Bloques(void)
{
	std::list<cota> lista_X=m_Eficientes_X;
	std::list<cota> lista_Y=m_Eficientes_Y;
	std::list<cota> ::iterator itx1,ity1,it2,it3,it2x;

	int V,W,a,b,c,d,e,f,g,h,maximo=0,maxim2=0,i,j,k,l,A5=0,B5=0;
	//buscar partición perfecta
	V=m_AnchoR_Pallet;

	W=m_LargoR_Pallet;
	intervalo salida;
	int a1=m_Ancho_Caja;
	int b1=m_Largo_Caja;
	for (itx1=lista_X.begin();itx1!=lista_X.end();itx1++)
	{
		b=(*itx1).first;
		for (ity1=lista_Y.begin();ity1!=lista_Y.end();ity1++)
		{
			if (b!=0)
			{
				a=(*ity1).second;//primer Rectangulo a,b
			}
			else a=0;
			for (int cx=0;cx<=(V-(b*a1))/b1;cx++)
			{
			for (it2=lista_Y.begin();it2!=lista_Y.end();it2++)
			{

				c=cx;
				d=(*it2).first;
				if (c==0 || d==0) {c=0;d=0;}

				for (it3=lista_X.begin();it3!=lista_X.end();it3++)
				{
//					e=(*it2).second;
					e=(W-(d*a1))/b1;

					f=(*it3).first;
					h=(W-(a*b1))/a1;//
					g=(*it3).second;
					if (e==0 || f==0) {e=0;f=0;}
					if (h==0 || g==0) {h=0;g=0;}
					//No sobrelapamientos y maximiza
					i=0;
					j=0;
					k=0;
					l=0;
					//Posible quinto bloque, cabe al menos una horizontal o vertical
					if (((d+h<=(W/a1)) && (f+b<=(V/a1))) || ((c+g<=(W/b1)) && (a+e<=(V/b1))))
					{
						//Area es
						unsigned int Area5=0;
						A5=0,B5=0,maxim2=0;
						if ((W-(a*b1+e*b1))>0 && (V-(g*b1+c*b1))>0)
						{
							(Area5=(W-(a*b1+e*b1))*(V-(g*b1+c*b1)));
							A5=(W-(a*b1+e*b1));
							B5=(V-(g*b1+c*b1));
						}
						if ((V-(b*a1+f*a1))>0 && (W-(h*a1+d*a1))>0)
						{
							(Area5=(V-(b*a1+f*a1))*(W-(h*a1+d*a1)));
							A5=(V-(b*a1+f*a1));
							B5=(W-(h*a1+d*a1));
						}

						//horizontal
						for (int register i1=0;i1<=A5/a1;i1++)
						{
							for (int register j1=0;j1<=B5/b1;j1++)
							{
								if ((i1*j1>maxim2) && (i1*a1+b1*j1<=Area5))
								{
									i=i1;
									j=j1;
									k=0;
									l=0;
									maxim2=i1*j1;
								}
							}
						}
						//vertical
						for (int register i2=0;i2<=A5/b1;i2++)
						{
							for (int register j2=0;j2<=B5/a1;j2++)
							{
								if ((i2*j2>maxim2) && (i2*b1+j2*a1<=Area5))
								{
									k=i2;
									l=j2;
									i=0;
									j=0;
									maxim2=i2*j2;
								}
							}
						}
					}
					
					if ((a*b+c*d+e*f+g*h+i*j+k*l) >= maximo && !((a+e>(W/b1)) && (b+f>(V/a1))) && !((h+d>(W/a1)) && (g+c>(V/b1))))
					{
					//Prefiero soluciones sin bloque interior
						if ((((i!=0 && j!=0) || (k!=0 && l!=0)) && ((a*b+c*d+e*f+g*h+i*j+k*l) ==maximo))!=true)
						{
					//	cout1<<"\n"<<a<<"x"<<b<<"\t"<<c<<"x"<<d<<"\t"<<e<<"x"<<f<<"\t"<<g<<"x"<<h<<"\t"<<"Total"<<"\t"<<a*b+c*d+e*f+g*h;
						maximo=a*b+c*d+e*f+g*h+i*j+k*l;
						if (salida.size()!=0) (salida.clear());
						//Primer bloque en horizontal
						//Segundo bloque en vértical
						//Tercer bloque en horizontal
						//Cuarto bloque en vértical
						//Quinto bloque horizontal
						//Sexto bloque en vértical
						salida.push_back(a);
						salida.push_back(b);
						salida.push_back(c);
						salida.push_back(d);
						salida.push_back(e);
						salida.push_back(f);
						salida.push_back(g);
						salida.push_back(h);
						salida.push_back(i);
						salida.push_back(j);
						salida.push_back(k);
						salida.push_back(l);

						salida.push_back(maximo);
					//	cout1<<"\n"<<a<<"x"<<b<<"\t"<<c<<"x"<<d<<"\t"<<e<<"x"<<f<<"\t"<<g<<"x"<<h<<"\t"<<"Total"<<"\t"<<a*b+c*d+e*f+g*h;
						maximo=a*b+c*d+e*f+g*h+i*j+k*l;
						}
					}
				}
			}
			}
		}
	}
	a=salida[0];
	b=salida[1];
	c=salida[2];
	d=salida[3];
	e=salida[4];
	f=salida[5];
	g=salida[6];
	h=salida[7];
	i=salida[8];
	j=salida[9];
	k=salida[10];
	l=salida[11];
	//Examina la actual solucion
	if (GetValSolucion()<salida[12])

	{
		std::list<var> m_Heuristico;
		std::list<var*> listapvar;
		int kx,ky;
		//DEbo meter la nueva solucion
		//Primer Bloque
		for(kx=0;kx<b;kx++)
		{
			for (ky=0;ky<a;ky++)

			{
				var caja;

				caja.orientacion='H';
				caja.x=kx;
				caja.y=ky;
				m_Heuristico.push_back(caja);
			}
		}
		//Segundo Bloque
		for(kx=b;kx<b+c;kx++)
		{
			for (ky=0;ky<d;ky++)
			{
				var caja;

				caja.orientacion='V';
				caja.x=kx;
				caja.y=ky;
				m_Heuristico.push_back(caja);
			}
		}
		//Tercer Bloque
		for(kx=g;kx<g+f;kx++)
		{
			for (ky=d;ky<d+e;ky++)
			{
				var caja;
			
				caja.orientacion='H';
				caja.x=kx;
				caja.y=ky;
				m_Heuristico.push_back(caja);
			}
		}
		//Cuarto Bloque
		for(kx=0;kx<g;kx++)
		{
			for (ky=a;ky<a+h;ky++)
			{
				var caja;

				caja.orientacion='V';

				caja.x=kx;
				caja.y=ky;
				m_Heuristico.push_back(caja);
			}
		}
	
		//Quinto Bloque
		//Horizontal
		if ((i!=0 && j!=0) )
		{
			// Al lado de A1 encima de A2
			if (b*a1+i*a1+f*a1<=V && d*b1+j*b1+g*b1<=W)
			{
				//Al lado de A1 encima de A2
				for(kx=b;kx<b+i;kx++)
				{
					for (ky=d;ky<d+j;ky++)
					{
								var caja;

					caja.orientacion='H';
					caja.x=kx;
					caja.y=ky;
					m_Heuristico.push_back(caja);
					}
				}
			}
				//Encima de A1
			if (g*b1+i*a1+c*a1<=V && a*b1+j*b1+e*b1<=W)
			{
				for(kx=g;kx<g+i;kx++)
				{
					for (ky=a;ky<a+j;ky++)
					{
								var caja;

					caja.orientacion='H';
					caja.x=kx;
					caja.y=ky;
					m_Heuristico.push_back(caja);
					}
				}
			}
		}
	
	
		if ((k!=0 && l!=0) )
		{
			// Al lado
			if (b*a1+k*b1+f*a1<=V && d*b1+l*a1+g*b1<=W)
			{
				//Al lado de A1 encima de A2
				for(kx=b;kx<b+i;kx++)
				{
					for (ky=d;ky<d+j;ky++)
					{
					var caja;

					caja.orientacion='V';
					caja.x=kx;
					caja.y=ky;
					m_Heuristico.push_back(caja);
					}
				}
			}
		

		
				//Encima de A1
			if (g*b1+k*b1+c*a1<=V && a*b1+l*a1+e*b1<=W)
			{
				for(kx=g;kx<g+i;kx++)
				{
					for (ky=a;ky<a+j;ky++)
					{
					var caja;

					caja.orientacion='V';
					caja.x=kx;
					caja.y=ky;
					m_Heuristico.push_back(caja);
					}
				}
			}
		}
		SetBest(m_Heuristico);

		m_ValSolucion=m_Heuristico.size();
		m_ValSolucion=salida[12];

		std::list<var> ::iterator iv;
		std::list<var*> pp;
		for (iv=m_Best.begin();iv!=m_Best.end();iv++)
		{
			m_Solucion.push_back(&(*iv));
		}


	}
	return salida;
}
void PALLET::CotaNelisenMaxMin(int Cota)
{
//	return;
	//Añadidas
	m_Hmin=0;
	m_Hmax=0;
	int H_max=0, V_max=0, H_min=0, V_min=0,uyne=0,lyne=0;
	//Primero tengo que tener todas las variables
	//conseguir las xij meterlas en una lista de estructuras con el 
	//nombre y su i j y si eficiente o no
	char salida[10]="prime",salida2[10],salida3[10];
	strcpy(salida2,salida);
	strcat(salida2,".for");
	std::list<varcota> varX,varY;
	std::list<varcota>::iterator it,it2;
	int M=m_AnchoR_Pallet;
	int a=m_Ancho_Caja;
	int b=m_Largo_Caja;
	char texto[10],texto2[10],buff[6],lindo[30];
	unsigned char ak='0';
	int j,i;
	int cont1=0,cont2=0;
	for(i=0;i<=(M/a);i++)
	{
		for(j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{
			cont1++;
			//Si es eficiente la meto
			ak='0';

			if ((M-(i*a+b*j))<b)
			{
				ak='1';				
			}
			if (i<10) strcpy(texto,"X0");
			else strcpy(texto,"X");
			itoa(i,buff,10);
			strcat(texto,buff);
			if (j<10) strcat(texto,"0");
			itoa(j,buff,10);
			strcat(texto,buff);
			varcota var1={"000000",i,j,ak,0,m_LargoR_Pallet};
			strcpy(var1.name,texto);

			varX.push_back(var1);
		}
	}
	M=m_LargoR_Pallet;
	a=m_Ancho_Caja;
	b=m_Largo_Caja;
	
	//Ahora metemos los Y
	for( i=0;i<=(M/a);i++)
	{
		for(j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{

			cont2++;
			//Si es eficiente la meto
			ak='0';

			if ((M-(i*a+b*j))<b)
			{
				ak='1';				
			}
			if (i<10) strcpy(texto2,"Y0");
			else strcpy(texto2,"Y");
			itoa(i,buff,10);
			strcat(texto2,buff);
			if (j<10) strcat(texto2,"0");
			itoa(j,buff,10);
			strcat(texto2,buff);
			varcota var1={"000000",i,j,ak,0,m_AnchoR_Pallet};
			strcpy(var1.name,texto2);

			varY.push_back(var1);



		}
	}
	int U2=0;
	int m=0;
	int cambios;
//	do{   // mientras haya cambios en las cotas de las variables, repetimos el calculo de cotas de H y V
		 cambios=0;

	//Ahora escribo y resuelvo el lineal
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,1,1,texto);

	strcpy(lindo,"lindo.exe < ");
	strcat(lindo,salida2); //argv[2] es archivo de formulacion
	system(lindo);
	
//Recojo solo la funcion objetivo que sera
	strcpy(salida3,salida);
	strcat(salida3,".sol");
	//Para clase poner
//	ifstream fin(salida3);
	using namespace std;
	char kkk[40];
	int H=0,V=0;
	int Z=0;
	FILE *fpp;
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	Z=atoi(kkk);
	fclose(fpp);
	Z=Z/m_Largo_Caja;
	intervalo  sol;
//	sol=Heuristico5Bloques();
	double heuri2=Cota-1;
	double heuri=Cota;
	if (heuri2==Z)
		return;
	Z=Z+1;
	heuri=heuri++;
perro: heuri--,Z--;
	if (heuri2==Z)
		return;
	//meto ahora la 7 
	//Maximizar H
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,2,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	H=atoi(kkk);
	fclose(fpp);
	H=(H/m_Largo_Caja);
	H_max=H;

	//Maximizar V
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,3,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	V=atoi(kkk);
	fclose(fpp);
	V=(V/m_Largo_Caja);
	V_max=V;
	if (H+V<Z)
		U2=H+V;
	else 
		U2=Z;
//	cout<<U2<<" "<<H<<" "<<V;

    m_Vmin=V_min;
	m_Vmax=V_max;
    m_Hmin=H_min;
	m_Hmax=H_max;

	//Ahora hacemos cada uno de los lineales para 
	//Las cotas de las variables 


	for(it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Para MAximo de cada variable eficiente
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,4,heuri,(*it).name);
			system(lindo);
//			_fcloseall();
//			fin.open(salida3);
			fpp=fopen("prime.sol","r");

			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotsup=atoi(kkk);
			fclose(fpp);;
			//Para minimo de cada variable
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,5,heuri,(*it).name);
			system(lindo);
//			_fcloseall();
			fpp=fopen("prime.sol","r");

			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotinf=atoi(kkk);
			fclose(fpp);
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}
	
	}
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Para MAximo de cada variable eficiente 
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,4,heuri,(*it).name);
			system(lindo);
			FILE *fpp;
			fpp=fopen("prime.sol","r");
	
			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotsup=atoi(kkk);
			fclose(fpp);;
			//Para minimo de cada variable
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,5,heuri,(*it).name);
			system(lindo);
			fpp=fopen("prime.sol","r");

			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotinf=atoi(kkk);
			fclose(fpp);
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;

		}
	}
	/***** esto es para calcular lo quito
	//Cota superior e inferior para las no eficientes
	// ya tengo los nombres ahora 
	// resuelvo los dos lineales
	//Para MAximo de cada variable no eficiente 
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,9,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	uyne=atoi(kkk);
	fclose(fpp);;
	//Para minimo de cada variable
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,10,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	lyne=atoi(kkk);
	fclose(fpp);
	if (lyne>uyne) 
		goto perro;
************************/
//	delete fin;

	/*
	ofstream fout("prueva5.txt");
	for(it=varY.begin();it!=varY.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	for(it=varX.begin();it!=varX.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	fout.close();
*/
	/*
	ofstream fout("prueva5.txt");
	for(it=varY.begin();it!=varY.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	for(it=varX.begin();it!=varX.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	fout.close();
	*/
	//Como ya solo nos van a hacer falta solo las eficientes 

	//Construyo ahora solo las eficientes


	//Ahora vamos a hacer apartado 5.1
	//Calculo de Hmin
	//ESTan mal es r * sumatorio
	int Hmin=0,Vmin=0,max1=0,max2=0;
	float sumlya=0,sumlxb=0;
	for (int r=2;r<=(m_LargoR_Pallet)/(m_Largo_Caja);r++)
	{
		sumlya=0;
		for(it=varY.begin();it!=varY.end();it++)
		{
			if ((*it).Eficiente=='1' && ((*it).j1>=r))
			{
				int ppp=(*it).j1;
				int ppp5=(*it).i1;
				int ppp2=(*it).cotinf;
				sumlya=sumlya+((float)(*it).cotinf/(float)m_Ancho_Caja);
			}
		}
		if (r*ceil(sumlya)>max1)
					max1=r*ceil(sumlya);

	}
	for (r=2;r<=(m_AnchoR_Pallet)/(m_Ancho_Caja);r++)
	{
		sumlxb=0;
		for(it=varX.begin();it!=varX.end();it++)
		{
			if ((*it).Eficiente=='1'&& ((*it).i1>=r))
			{
				sumlxb=sumlxb+((float)(*it).cotinf/(float)m_Largo_Caja);
			}
		}
		if (r*ceil(sumlxb)>max1)
				max1=r*ceil(sumlxb);

	}
	Hmin=max1;
	max1=0;
	float sumlyb=0,sumlxa=0;

	//Calculo de Vmin
	for (r=2;r<=(m_LargoR_Pallet)/(m_Ancho_Caja);r++)
	{
		sumlyb=0;
		for(it=varY.begin();it!=varY.end();it++)
		{
			if ((*it).Eficiente=='1' && ((*it).i1>=r))
			{
				sumlyb=sumlyb+((float)(*it).cotinf/(float)m_Largo_Caja);
			}
		}
		if (r*ceil(sumlyb)>max1)
			max1=r*ceil(sumlyb);

	}
	for (r=2;r<=(m_AnchoR_Pallet)/(m_Largo_Caja);r++)
	{
		sumlxa=0;
		for(it=varX.begin();it!=varX.end();it++)
		{
			if ((*it).Eficiente=='1' && ((*it).j1>=r))
			{
				sumlxa=sumlxa+((float)(*it).cotinf/(float)m_Ancho_Caja);
			}
		}
		if (r*ceil(sumlxa)>max1)
			max1=r*ceil(sumlxa);
	}
	Vmin=max1;
	if ((U2-Vmin)<H) H=U2-Vmin;
	if ((U2-Hmin)<V) V=U2-Hmin;

	//lo mismo para las nuevas V_min y H_min
	if ((U2-V_min)<H) H=U2-V_min;
	if ((U2-H_min)<V) V=U2-H_min;


//	cout<<"\n"<<H<<"\t"<<V;
	//Apartado 5.2 del Articulo
	//if X-lyf,g<a ---> q>2*g -->uyp,q=0;
	//                  H=floor(H/g)*g;
	//Primeras ecuaciones 12,13,14,15
	for (it=varY.begin();it!=varY.end();it++)
	{		
		if ((*it).Eficiente=='1')
		{

			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Ancho_Caja && ((*it).j1!=0))
			{

				H=((H/int((*it).j1)))*(*it).j1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
		
			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Largo_Caja)
			{
			if ((*it).i1!=0)
			{

				V=((V/int((*it).i1)))*(*it).i1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
		}
	}
	//Segundas ecuaciones 12,13,14,15
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((m_LargoR_Pallet-(*it).cotinf)<m_Ancho_Caja)
			{
			if ((*it).j1!=0)
			{

				V=(V/int((*it).j1))*((*it).j1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
			if ((m_LargoR_Pallet-(*it).cotinf)<m_Largo_Caja && ((*it).i1!=0))
			{
				H=(H/int((*it).i1))*((*it).i1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
		}
	}

	//Hasta Aqui bien
	//Apartado 5.3 intenta reducir mas aun esta cota
	//Ecuación 20
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).j1!=0 )
			{

				if ((*it).cotsup>(H/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(H/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}
			if ((*it).i1!=0 )
			{

				if ((*it).cotsup>(V/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(V/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}

			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}


	//MAL
	//Ecuación 21
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 )
			{
				if ((*it).cotsup>(H/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(H/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}
			if ((*it).j1!=0 )
			{
				if ((*it).cotsup>(V/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(V/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}


			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}



	//Apartado 5. 2)
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{
			int kkkk=(*it).j1;
		//Ecuación 22
			if ((*it).j1!=0)
			{
			if ((((H/int((*it).j1)))*(*it).j1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 23
			if ((*it).i1!=0)
			{

			if ((((V/int((*it).i1)))*(*it).i1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			int kk=(*it).cotinf;
			int kkk=(*it).cotsup;
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}


	}



	for (it=varX.begin();it!=varX.end();it++)
	{		
		if ((*it).Eficiente=='1')
		{

			//Ecuación 24
			if ((*it).j1!=0)
			{

			if ((((V/int((*it).j1)))*(*it).j1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 25
			if ((*it).i1!=0)
			{

			if ((((H/int((*it).i1)))*(*it).i1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}


	}


			//Pintar para ver que esta bien
//Aqui bien
	//Apartado 5.2 3)
	int na1=0,sumna1=0,nb1=0,sumnb1=0,n1a=0,sumn1a=0,n1b=0,sumn1b=0;
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Calculo aqui las variables que tengo
		m++;
		sumna1+=(*it).i1*(*it).cotinf;
		sumnb1+=(*it).j1*(*it).cotinf;
		}
	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		
		sumn1a+=(*it).i1*(*it).cotinf;
		sumn1b+=(*it).j1*(*it).cotinf;
		}
	}
	na1=(H*m_Largo_Caja)-sumna1;
	nb1=(V*m_Ancho_Caja)-sumnb1;
	n1a=(V*m_Largo_Caja)-sumn1a;
	n1b=(H*m_Ancho_Caja)-sumn1b;


	
	for (it=varX.begin();it!=varX.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(na1/(*it).i1),floor(nb1/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(n1a/(*it).i1),floor(n1b/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	//


	//Ahora vamos a hacer apartado 5.1
	//Calculo de Hmin
	if ((U2-Hmin)<V) V=U2-Hmin;


//	cout<<"\n"<<H<<"\t"<<V;
	//Apartado 5.2 del Articulo
	//if X-lyf,g<a ---> q>2*g -->uyp,q=0;
	//                  H=floor(H/g)*g;
	//Primeras ecuaciones 12,13,14,15
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Ancho_Caja && ((*it).j1!=0))
			{

				H=((H/int((*it).j1)))*(*it).j1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Largo_Caja)
			{
			if ((*it).i1!=0)
			{

				V=((V/int((*it).i1)))*(*it).i1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
		}
	}
	//Segundas ecuaciones 12,13,14,15
	for (it=varX.begin();it!=varX.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((m_LargoR_Pallet-(*it).cotinf)<m_Ancho_Caja)
			{
			if ((*it).j1!=0)
			{

				V=(V/int((*it).j1))*((*it).j1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
			if ((m_LargoR_Pallet-(*it).cotinf)<m_Largo_Caja && ((*it).i1!=0))
			{
				H=(H/int((*it).i1))*((*it).i1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
		}
	}

	//Hasta Aqui bien
	//Apartado 5.3 intenta reducir mas aun esta cota
	//Ecuación 20
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((*it).j1!=0 )
			{

				if ((*it).cotsup>(H/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(H/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}
			if ((*it).i1!=0 )
			{

				if ((*it).cotsup>(V/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(V/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}


	//MAL
	//Ecuación 21
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 )
			{
				if ((*it).cotsup>(H/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(H/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}
			if ((*it).j1!=0 )
			{
				if ((*it).cotsup>(V/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(V/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}

//MAL

	//Apartado 5.2 2)
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			//Ecuación 22
			if ((*it).j1!=0)
			{
			if ((((H/int((*it).j1)))*(*it).j1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 23
			if ((*it).i1!=0)
			{

			if ((((V/int((*it).i1)))*(*it).i1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}



	for (it=varX.begin();it!=varX.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			//Ecuación 24
			if ((*it).j1!=0)
			{

			if ((((V/int((*it).j1)))*(*it).j1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 25
			if ((*it).i1!=0)
			{

			if ((((H/int((*it).i1)))*(*it).i1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}


	}

//MAL
			//Pintar para ver que esta bien
//Aqui bien
	//Apartado 5.2 3)
    na1=0,sumna1=0,nb1=0,sumnb1=0,n1a=0,sumn1a=0,n1b=0,sumn1b=0,m=0;
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Calculo aqui las variables que tengo
		m++;
		sumna1+=(*it).i1*(*it).cotinf;
		sumnb1+=(*it).j1*(*it).cotinf;
		}
	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		
		sumn1a+=(*it).i1*(*it).cotinf;
		sumn1b+=(*it).j1*(*it).cotinf;
		}
	}
	na1=(H*m_Largo_Caja)-sumna1;
	nb1=(V*m_Ancho_Caja)-sumnb1;
	n1a=(V*m_Largo_Caja)-sumn1a;
	n1b=(H*m_Ancho_Caja)-sumn1b;


	
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(na1/(*it).i1),floor(nb1/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(n1a/(*it).i1),floor(n1b/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	//
//	}while(cambios!=0);


//	cout<<"\n"<<H<<"\t"<<V;

	//Ya tenemos todo ahora podemos pasar a resolver el problema 
	//mochila
	//No tenemos el uyne
	if (uyne>floor(((m_LargoR_Pallet*m_AnchoR_Pallet)-(U2*m_Ancho_Caja*m_Largo_Caja))/b))
	uyne=floor(((m_LargoR_Pallet*m_AnchoR_Pallet)-(U2*m_Ancho_Caja*m_Largo_Caja))/b);
	//Aplicamos Martello and Toth
	m++;
	vector<cota> xjota;
	int x,u;
	//Tengo m variables
	//Hay que tenerlas ordenadas
	int zast=0;
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		x=((m_Ancho_Caja*(*it).i1)+(m_Largo_Caja*(*it).j1));
		u=(*it).cotsup;
//		cout<<u<<"\n";
		pair<double,double> p(x,u);
		xjota.push_back(p);
		if (((__min(u,m_AnchoR_Pallet))*x)>zast)
		zast=((__min(u,m_AnchoR_Pallet))*x);
		}
	}
	x=m_LargoR_Pallet-m_Largo_Caja;
	u=uyne;
	pair<double,double> p2(x,u);
	vector<cota> ::iterator itc;
	xjota.push_back(p2);
//	for(itc=xjota.begin();itc!=xjota.end();itc++)
	std::sort(xjota.begin(),xjota.end());
	std::reverse(xjota.begin(),xjota.end());
//	cout<<"ey";

///
	//Step1
	int c=m_AnchoR_Pallet;

	int jast,jota=1,z=0;
	//Un tipo

	//Dos tipos
	for(itc=xjota.begin();itc!=xjota.end();itc++)
	{
		x=__min((*itc).second,floor(c));
		z=z+(((*itc).first)*x);
		c=c-x;
		if (((*itc).first*x)>zast)
		{
			zast=((*itc).first*(*itc).second);
			jast=jota;
		}
	}
	if (zast>z) (z=zast);
/*	while (z<U2*m_Ancho_Caja*m_Largo_Caja)
	{
		U2--;
	}*/
//	cout<<"\n"<<U2;
	if (U2-V>Hmin) Hmin=U2-V;
	if ((U2-Vmin)<H) H=U2-Vmin;
    m_Hmin=Hmin;
	m_Hmax=H;
    m_Vmin=Vmin;
	m_Vmax=V;


	
}
int PALLET::CotaNelisen(void)
{
	//Añadidas
	m_Hmin=0;
	m_Hmax=0;
	int H_max=0, V_max=0, H_min=0, V_min=0,uyne=0,lyne=0;
	//Primero tengo que tener todas las variables
	//conseguir las xij meterlas en una lista de estructuras con el 
	//nombre y su i j y si eficiente o no
	char salida[10]="prime",salida2[10],salida3[10];
	strcpy(salida2,salida);
	strcat(salida2,".for");
	std::list<varcota> varX,varY;
	std::list<varcota>::iterator it,it2;
	int M=m_AnchoR_Pallet;
	int a=m_Ancho_Caja;
	int b=m_Largo_Caja;
	char texto[10],texto2[10],buff[6],lindo[30];
	unsigned char ak='0';
	int j,i;
	int cont1=0,cont2=0;
	for(i=0;i<=(M/a);i++)
	{
		for(j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{
			cont1++;
			//Si es eficiente la meto
			ak='0';

			if ((M-(i*a+b*j))<b)
			{
				ak='1';				
			}
			if (i<10) strcpy(texto,"X0");
			else strcpy(texto,"X");
			itoa(i,buff,10);
			strcat(texto,buff);
			if (j<10) strcat(texto,"0");
			itoa(j,buff,10);
			strcat(texto,buff);
			varcota var1={"000000",i,j,ak,0,m_LargoR_Pallet};
			strcpy(var1.name,texto);

			varX.push_back(var1);
		}
	}
	M=m_LargoR_Pallet;
	a=m_Ancho_Caja;
	b=m_Largo_Caja;
	
	//Ahora metemos los Y
	for( i=0;i<=(M/a);i++)
	{
		for(j=0;j<=(M/b) && (i*a+b*j)<(M+1);j++)
		{

			cont2++;
			//Si es eficiente la meto
			ak='0';

			if ((M-(i*a+b*j))<b)
			{
				ak='1';				
			}
			if (i<10) strcpy(texto2,"Y0");
			else strcpy(texto2,"Y");
			itoa(i,buff,10);
			strcat(texto2,buff);
			if (j<10) strcat(texto2,"0");
			itoa(j,buff,10);
			strcat(texto2,buff);
			varcota var1={"000000",i,j,ak,0,m_AnchoR_Pallet};
			strcpy(var1.name,texto2);

			varY.push_back(var1);



		}
	}
	int U2=0;
	int m=0;
	int cambios;
//	do{   // mientras haya cambios en las cotas de las variables, repetimos el calculo de cotas de H y V
		 cambios=0;

	//Ahora escribo y resuelvo el lineal
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,1,1,texto);

	strcpy(lindo,"lindo.exe < ");
	strcat(lindo,salida2); //argv[2] es archivo de formulacion
	system(lindo);
	
//Recojo solo la funcion objetivo que sera
	strcpy(salida3,salida);
	strcat(salida3,".sol");
	//Para clase poner
//	ifstream fin(salida3);
	using namespace std;
	char kkk[40];
	int H=0,V=0;
	int Z=0;
	FILE *fpp;
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	Z=atoi(kkk);
	fclose(fpp);
	Z=Z/m_Largo_Caja;
	intervalo  sol;
	sol=Heuristico5Bloques();
	double heuri2=sol[12];
	double heuri=Z;
	if (heuri2==Z)
		return Z;
	Z=Z+1;
	heuri=heuri++;
perro: heuri--,Z--;
	if (heuri2==Z)
		return Z;
	//meto ahora la 7 
	//Maximizar H
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,2,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	H=atoi(kkk);
	fclose(fpp);
	H=(H/m_Largo_Caja);
	H_max=H;

	//Maximizar V
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,3,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	V=atoi(kkk);
	fclose(fpp);
	V=(V/m_Largo_Caja);
	V_max=V;
	if (H+V<Z)
		U2=H+V;
	else 
		U2=Z;
//	cout<<U2<<" "<<H<<" "<<V;



	//Ahora hacemos cada uno de los lineales para 
	//Las cotas de las variables 


	for(it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Para MAximo de cada variable eficiente
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,4,heuri,(*it).name);
			system(lindo);
//			_fcloseall();
//			fin.open(salida3);
			fpp=fopen("prime.sol","r");

			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotsup=atoi(kkk);
			fclose(fpp);;
			//Para minimo de cada variable
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,5,heuri,(*it).name);
			system(lindo);
//			_fcloseall();
			fpp=fopen("prime.sol","r");

			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotinf=atoi(kkk);
			fclose(fpp);
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}
	
	}
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Para MAximo de cada variable eficiente 
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,4,heuri,(*it).name);
			system(lindo);
			FILE *fpp;
			fpp=fopen("prime.sol","r");
	
			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotsup=atoi(kkk);
			fclose(fpp);;
			//Para minimo de cada variable
			primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,5,heuri,(*it).name);
			system(lindo);
			fpp=fopen("prime.sol","r");

			if(fpp==NULL) 
			{
				printf("problemas al leer fichero de salida de Lindo3\n");
//				goto perro;
			}
			do
			{
				fscanf(fpp,"%s",kkk);
			if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");

			}while(strcmp(kkk,"1)")!=0);
			fscanf(fpp,"%s",kkk);
			(*it).cotinf=atoi(kkk);
			fclose(fpp);
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;

		}
	}
	/***** esto es para calcular lo quito
	//Cota superior e inferior para las no eficientes
	// ya tengo los nombres ahora 
	// resuelvo los dos lineales
	//Para MAximo de cada variable no eficiente 
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,9,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	uyne=atoi(kkk);
	fclose(fpp);;
	//Para minimo de cada variable
	primer_lineal(varX,varY,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja, m_Largo_Caja,salida2,10,heuri,texto);
	system(lindo);
	fpp=fopen("prime.sol","r");
	if(fpp==NULL) 
	{
		printf("problemas al leer fichero de salida de Lindo3\n");
	}
	do
	{
		fscanf(fpp,"%s",kkk);
		if (strcmp(kkk,"WARNING,")==0)
			printf("Algo mal");
	}while(strcmp(kkk,"1)")!=0);
	fscanf(fpp,"%s",kkk);
	lyne=atoi(kkk);
	fclose(fpp);
	if (lyne>uyne) 
		goto perro;
************************/
//	delete fin;

	/*
	ofstream fout("prueva5.txt");
	for(it=varY.begin();it!=varY.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	for(it=varX.begin();it!=varX.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	fout.close();
*/
	/*
	ofstream fout("prueva5.txt");
	for(it=varY.begin();it!=varY.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	for(it=varX.begin();it!=varX.end();it++)
	{
		fout<<(*it).name<<"\t"<<(*it).i1<<"\t"<<(*it).j1<<"\t"<<(*it).cotinf<<"\t"<<(*it).cotsup<<"\n";
	}
	fout.close();
	*/
	//Como ya solo nos van a hacer falta solo las eficientes 

	//Construyo ahora solo las eficientes


	//Ahora vamos a hacer apartado 5.1
	//Calculo de Hmin
	//ESTan mal es r * sumatorio
	int Hmin=0,Vmin=0,max1=0,max2=0;
	float sumlya=0,sumlxb=0;
	for (int r=2;r<=(m_LargoR_Pallet)/(m_Largo_Caja);r++)
	{
		sumlya=0;
		for(it=varY.begin();it!=varY.end();it++)
		{
			if ((*it).Eficiente=='1' && ((*it).j1>=r))
			{
				int ppp=(*it).j1;
				int ppp5=(*it).i1;
				int ppp2=(*it).cotinf;
				sumlya=sumlya+((float)(*it).cotinf/(float)m_Ancho_Caja);
			}
		}
		if (r*ceil(sumlya)>max1)
					max1=r*ceil(sumlya);

	}
	for (r=2;r<=(m_AnchoR_Pallet)/(m_Ancho_Caja);r++)
	{
		sumlxb=0;
		for(it=varX.begin();it!=varX.end();it++)
		{
			if ((*it).Eficiente=='1'&& ((*it).i1>=r))
			{
				sumlxb=sumlxb+((float)(*it).cotinf/(float)m_Largo_Caja);
			}
		}
		if (r*ceil(sumlxb)>max1)
				max1=r*ceil(sumlxb);

	}
	Hmin=max1;
	max1=0;
	float sumlyb=0,sumlxa=0;

	//Calculo de Vmin
	for (r=2;r<=(m_LargoR_Pallet)/(m_Ancho_Caja);r++)
	{
		sumlyb=0;
		for(it=varY.begin();it!=varY.end();it++)
		{
			if ((*it).Eficiente=='1' && ((*it).i1>=r))
			{
				sumlyb=sumlyb+((float)(*it).cotinf/(float)m_Largo_Caja);
			}
		}
		if (r*ceil(sumlyb)>max1)
			max1=r*ceil(sumlyb);

	}
	for (r=2;r<=(m_AnchoR_Pallet)/(m_Largo_Caja);r++)
	{
		sumlxa=0;
		for(it=varX.begin();it!=varX.end();it++)
		{
			if ((*it).Eficiente=='1' && ((*it).j1>=r))
			{
				sumlxa=sumlxa+((float)(*it).cotinf/(float)m_Ancho_Caja);
			}
		}
		if (r*ceil(sumlxa)>max1)
			max1=r*ceil(sumlxa);
	}
	Vmin=max1;
	if ((U2-Vmin)<H) H=U2-Vmin;
	if ((U2-Hmin)<V) V=U2-Hmin;

	//lo mismo para las nuevas V_min y H_min
	if ((U2-V_min)<H) H=U2-V_min;
	if ((U2-H_min)<V) V=U2-H_min;


//	cout<<"\n"<<H<<"\t"<<V;
	//Apartado 5.2 del Articulo
	//if X-lyf,g<a ---> q>2*g -->uyp,q=0;
	//                  H=floor(H/g)*g;
	//Primeras ecuaciones 12,13,14,15
	for (it=varY.begin();it!=varY.end();it++)
	{		
		if ((*it).Eficiente=='1')
		{

			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Ancho_Caja && ((*it).j1!=0))
			{

				H=((H/int((*it).j1)))*(*it).j1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
		
			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Largo_Caja)
			{
			if ((*it).i1!=0)
			{

				V=((V/int((*it).i1)))*(*it).i1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
		}
	}
	//Segundas ecuaciones 12,13,14,15
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((m_LargoR_Pallet-(*it).cotinf)<m_Ancho_Caja)
			{
			if ((*it).j1!=0)
			{

				V=(V/int((*it).j1))*((*it).j1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
			if ((m_LargoR_Pallet-(*it).cotinf)<m_Largo_Caja && ((*it).i1!=0))
			{
				H=(H/int((*it).i1))*((*it).i1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
		}
	}

	//Hasta Aqui bien
	//Apartado 5.3 intenta reducir mas aun esta cota
	//Ecuación 20
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).j1!=0 )
			{

				if ((*it).cotsup>(H/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(H/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}
			if ((*it).i1!=0 )
			{

				if ((*it).cotsup>(V/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(V/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}

			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}


	//MAL
	//Ecuación 21
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 )
			{
				if ((*it).cotsup>(H/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(H/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}
			if ((*it).j1!=0 )
			{
				if ((*it).cotsup>(V/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(V/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}


			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}



	//Apartado 5. 2)
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{
			int kkkk=(*it).j1;
		//Ecuación 22
			if ((*it).j1!=0)
			{
			if ((((H/int((*it).j1)))*(*it).j1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 23
			if ((*it).i1!=0)
			{

			if ((((V/int((*it).i1)))*(*it).i1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			int kk=(*it).cotinf;
			int kkk=(*it).cotsup;
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}


	}



	for (it=varX.begin();it!=varX.end();it++)
	{		
		if ((*it).Eficiente=='1')
		{

			//Ecuación 24
			if ((*it).j1!=0)
			{

			if ((((V/int((*it).j1)))*(*it).j1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 25
			if ((*it).i1!=0)
			{

			if ((((H/int((*it).i1)))*(*it).i1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}


	}


			//Pintar para ver que esta bien
//Aqui bien
	//Apartado 5.2 3)
	int na1=0,sumna1=0,nb1=0,sumnb1=0,n1a=0,sumn1a=0,n1b=0,sumn1b=0;
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Calculo aqui las variables que tengo
		m++;
		sumna1+=(*it).i1*(*it).cotinf;
		sumnb1+=(*it).j1*(*it).cotinf;
		}
	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		
		sumn1a+=(*it).i1*(*it).cotinf;
		sumn1b+=(*it).j1*(*it).cotinf;
		}
	}
	na1=(H*m_Largo_Caja)-sumna1;
	nb1=(V*m_Ancho_Caja)-sumnb1;
	n1a=(V*m_Largo_Caja)-sumn1a;
	n1b=(H*m_Ancho_Caja)-sumn1b;


	
	for (it=varX.begin();it!=varX.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(na1/(*it).i1),floor(nb1/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(n1a/(*it).i1),floor(n1b/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	//


	//Ahora vamos a hacer apartado 5.1
	//Calculo de Hmin
	if ((U2-Hmin)<V) V=U2-Hmin;


//	cout<<"\n"<<H<<"\t"<<V;
	//Apartado 5.2 del Articulo
	//if X-lyf,g<a ---> q>2*g -->uyp,q=0;
	//                  H=floor(H/g)*g;
	//Primeras ecuaciones 12,13,14,15
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Ancho_Caja && ((*it).j1!=0))
			{

				H=((H/int((*it).j1)))*(*it).j1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			if ((m_AnchoR_Pallet-(*it).cotinf)<m_Largo_Caja)
			{
			if ((*it).i1!=0)
			{

				V=((V/int((*it).i1)))*(*it).i1;
				{
					for (it2=varY.begin();it2!=varY.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
		}
	}
	//Segundas ecuaciones 12,13,14,15
	for (it=varX.begin();it!=varX.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((m_LargoR_Pallet-(*it).cotinf)<m_Ancho_Caja)
			{
			if ((*it).j1!=0)
			{

				V=(V/int((*it).j1))*((*it).j1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).j1>2*(*it).j1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
			}
			if ((m_LargoR_Pallet-(*it).cotinf)<m_Largo_Caja && ((*it).i1!=0))
			{
				H=(H/int((*it).i1))*((*it).i1);
				{
					for (it2=varX.begin();it2!=varX.end();it2++)
					{
						if ((*it2).i1>2*(*it).i1) 
						{
							(*it2).cotsup=0;
							(*it2).cotinf=0;
							cambios++;
						}
					}
				}
			}
		}
	}

	//Hasta Aqui bien
	//Apartado 5.3 intenta reducir mas aun esta cota
	//Ecuación 20
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			if ((*it).j1!=0 )
			{

				if ((*it).cotsup>(H/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(H/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}
			if ((*it).i1!=0 )
			{

				if ((*it).cotsup>(V/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(V/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}


	//MAL
	//Ecuación 21
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 )
			{
				if ((*it).cotsup>(H/int((*it).i1))*m_Largo_Caja)
				{
					(*it).cotsup=(H/int((*it).i1))*m_Largo_Caja;
					cambios++;
				}
			}
			if ((*it).j1!=0 )
			{
				if ((*it).cotsup>(V/int((*it).j1))*m_Ancho_Caja)
				{
					(*it).cotsup=(V/int((*it).j1))*m_Ancho_Caja;
					cambios++;
				}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}

//MAL

	//Apartado 5.2 2)
	for (it=varY.begin();it!=varY.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			//Ecuación 22
			if ((*it).j1!=0)
			{
			if ((((H/int((*it).j1)))*(*it).j1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 23
			if ((*it).i1!=0)
			{

			if ((((V/int((*it).i1)))*(*it).i1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_AnchoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}



	for (it=varX.begin();it!=varX.end();it++)
	{	
		if ((*it).Eficiente=='1')
		{

			//Ecuación 24
			if ((*it).j1!=0)
			{

			if ((((V/int((*it).j1)))*(*it).j1)<U2-H)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Ancho_Caja);
				cambios++;
			}
			}
			//Ecuación 25
			if ((*it).i1!=0)
			{

			if ((((H/int((*it).i1)))*(*it).i1)<U2-V)
			{
				(*it).cotsup=__min((*it).cotsup,m_LargoR_Pallet-m_Largo_Caja);
				cambios++;
			}
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}


	}

//MAL
			//Pintar para ver que esta bien
//Aqui bien
	//Apartado 5.2 3)
    na1=0,sumna1=0,nb1=0,sumnb1=0,n1a=0,sumn1a=0,n1b=0,sumn1b=0,m=0;
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		//Calculo aqui las variables que tengo
		m++;
		sumna1+=(*it).i1*(*it).cotinf;
		sumnb1+=(*it).j1*(*it).cotinf;
		}
	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		
		sumn1a+=(*it).i1*(*it).cotinf;
		sumn1b+=(*it).j1*(*it).cotinf;
		}
	}
	na1=(H*m_Largo_Caja)-sumna1;
	nb1=(V*m_Ancho_Caja)-sumnb1;
	n1a=(V*m_Largo_Caja)-sumn1a;
	n1b=(H*m_Ancho_Caja)-sumn1b;


	
	for (it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(na1/(*it).i1),floor(nb1/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	for (it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{

			if ((*it).i1!=0 && (*it).j1!=0)
			{
			(*it).cotsup=__min((*it).cotsup,(*it).cotinf+__min(floor(n1a/(*it).i1),floor(n1b/(*it).j1)));
			cambios++;
			}
			if ((*it).cotinf>(*it).cotsup) 
				goto perro;
		}

	}
	//
//	}while(cambios!=0);


//	cout<<"\n"<<H<<"\t"<<V;

	//Ya tenemos todo ahora podemos pasar a resolver el problema 
	//mochila
	//No tenemos el uyne
	if (uyne>floor(((m_LargoR_Pallet*m_AnchoR_Pallet)-(U2*m_Ancho_Caja*m_Largo_Caja))/b))
	uyne=floor(((m_LargoR_Pallet*m_AnchoR_Pallet)-(U2*m_Ancho_Caja*m_Largo_Caja))/b);
	//Aplicamos Martello and Toth
	m++;
	vector<cota> xjota;
	int x,u;
	//Tengo m variables
	//Hay que tenerlas ordenadas
	int zast=0;
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).Eficiente=='1')
		{
		x=((m_Ancho_Caja*(*it).i1)+(m_Largo_Caja*(*it).j1));
		u=(*it).cotsup;
//		cout<<u<<"\n";
		pair<double,double> p(x,u);
		xjota.push_back(p);
		if (((__min(u,m_AnchoR_Pallet))*x)>zast)
		zast=((__min(u,m_AnchoR_Pallet))*x);
		}
	}
	x=m_LargoR_Pallet-m_Largo_Caja;
	u=uyne;
	pair<double,double> p2(x,u);
	vector<cota> ::iterator itc;
	xjota.push_back(p2);
//	for(itc=xjota.begin();itc!=xjota.end();itc++)
	std::sort(xjota.begin(),xjota.end());
	std::reverse(xjota.begin(),xjota.end());
//	cout<<"ey";

///
	//Step1
	int c=m_AnchoR_Pallet;

	int jast,jota=1,z=0;
	//Un tipo

	//Dos tipos
	for(itc=xjota.begin();itc!=xjota.end();itc++)
	{
		x=__min((*itc).second,floor(c));
		z=z+(((*itc).first)*x);
		c=c-x;
		if (((*itc).first*x)>zast)
		{
			zast=((*itc).first*(*itc).second);
			jast=jota;
		}
	}
	if (zast>z) (z=zast);
/*	while (z<U2*m_Ancho_Caja*m_Largo_Caja)
	{
		U2--;
	}*/
//	cout<<"\n"<<U2;
	if (U2-V>Hmin) Hmin=U2-V;
	if ((U2-Vmin)<H) H=U2-Vmin;
    m_Hmin=Hmin;
	m_Hmax=H;
	m_Vmin=Vmin;
	m_Vmax=V;
	return U2;
	
}
void primer_lineal(std::list<varcota> & varX,std::list<varcota> & varY,int AnchoP,int LargoP,int AnchoC, int LargoC,char salida2[10],int tipo,double primcota,char varia[300])
{

	//Mirar esto aqui puede mal, merci....ç
//	FILE *foutlindo;
//	foutlindo=fopen(salida2,"w");
//	ofstream foutlindo(salida2);
	FILE *fpw;
	fpw=fopen("prime.for","w");
	if(fpw==NULL) 
	{
		fprintf(fpw,"problemas al Crear fichero de Lindo3\n");
	}

//	foutlindo.open("prime.for");
	fprintf(fpw,"TERSE\n");
	if (tipo!=5 && tipo!=6 && tipo!=7 && tipo!=10) fprintf(fpw,"Max");
	else fprintf(fpw,"Min");
	std::list<varcota>::iterator it,it2;
	int total_var=0;
	div_t div_resultado;

	//Ya tengo todo lo que me hace falta para escribir
	//Función objetivo
	if (tipo==4 || tipo==5)
	{
		fprintf(fpw," + %s",varia);
	}
	if (tipo==1 || tipo==2  || tipo==6)
	{
	for(it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).i1!=0)
		{
		total_var++;

		div_resultado=div(total_var,4);

		if (div_resultado.rem==3)
		fprintf(fpw,"\n");

		fprintf(fpw," + %f %s",(*it).i1,(*it).name);
		}
		
	}
	}
	if (tipo==1 ||tipo==3 || tipo==7)
	{
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).i1!=0)
		{
		total_var++;
		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
		fprintf(fpw,"\n");

		fprintf(fpw," + %f %s",(*it).i1,(*it).name);
		}
		
	}
	}
	if (tipo==9 || tipo==10)
	{
		for(it=varX.begin();it!=varX.end();it++)
		{
			if ((*it).Eficiente!=1)
			{
			total_var++;	

			div_resultado=div(total_var,4);

			if (div_resultado.rem==3)
				fprintf(fpw,"\n");

			fprintf(fpw," + %f %s",(*it).i1,(*it).name);
			}
		}

		for(it=varY.begin();it!=varY.end();it++)
		{
			if ((*it).Eficiente!=1)
			{
				total_var++;
				div_resultado=div(total_var,4);
				if (div_resultado.rem==3)
					fprintf(fpw,"\n");
				fprintf(fpw," + %f %s",(*it).i1,(*it).name);
			}
		
		}
	}

	fprintf(fpw,"\n\nSUBJECT TO\n");
	total_var=0;
	//Ahora restriccion xij<=Y
	for(it=varX.begin();it!=varX.end();it++)
	{
		total_var++;

		div_resultado=div(total_var,4);

		if (div_resultado.rem==3)
		fprintf(fpw,"\n");

		fprintf(fpw," + %s",(*it).name);
	}
	fprintf(fpw,"< %d\n",LargoP);

	//Ahora yij <=X
	total_var=0;

	for(it=varY.begin();it!=varY.end();it++)
	{
		total_var++;

		div_resultado=div(total_var,4);

		if (div_resultado.rem==3)
		fprintf(fpw,"\n");

		fprintf(fpw," + %s",(*it).name);
	}
	fprintf(fpw,"< %d\n",AnchoP);
	//Ahora restricción 5 y restriccion 6

	total_var=0;

	for(it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).i1!=0)
		{
		total_var++;
		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
			fprintf(fpw,"\n");

		fprintf(fpw," + %f %s",(AnchoC)*(*it).i1,(*it).name);
		it2=it;
		it2++;
		}
	}
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).j1!=0)
		{
		total_var++;
		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
			fprintf(fpw,"\n");

		fprintf(fpw," - %f %s",(LargoC)*(*it).j1,(*it).name);
		}
	}
	fprintf(fpw,"\n=0\n");
	//Restriccion 6
	total_var=0;


	for(it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).j1!=0)
		{
		total_var++;
		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
			fprintf(fpw,"\n");

		fprintf(fpw," + %f %s",(LargoC)*(*it).j1,(*it).name);
		}
	}

	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).i1!=0)
		{
		total_var++;

		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
			fprintf(fpw,"\n");

		fprintf(fpw," - %f %s",(AnchoC)*(*it).i1,(*it).name);
		}
	}
	fprintf(fpw," \n= 0\n");
	total_var=0;
	//Restricción siete
	if (tipo!=1)
	{
	for(it=varX.begin();it!=varX.end();it++)
	{
		if ((*it).i1!=0)
		{
		total_var++;

		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
			fprintf(fpw,"\n");

		fprintf(fpw," + %f %s",(*it).i1,(*it).name);
		}
		
	}
//	foutlindo<<"\n";
//	total_var=0;
	for(it=varY.begin();it!=varY.end();it++)
	{
		if ((*it).i1!=0)
		{
		total_var++;
		div_resultado=div(total_var,4);
		if (div_resultado.rem==3)
			fprintf(fpw,"\n");

		fprintf(fpw," + %f %s",(*it).i1,(*it).name);
		}
		
	}
	fprintf(fpw," > %f \n",LargoC*primcota);
	}
	fprintf(fpw,"END\n");
	
/*	//Incluir cotas superiores e inferiores para las variables
	for(it=varX.begin();it!=varX.end();it++)
	{
		fprintf(fpw," SLB %s %d \n", (*it).name, (*it).cotinf);	
		fprintf(fpw," SUB %s %d \n", (*it).name, (*it).cotsup);
	}

	for(it=varY.begin();it!=varY.end();it++)
	{
		fprintf(fpw," SLB %s %d \n", (*it).name, (*it).cotinf);	
		fprintf(fpw," SUB %s %d \n", (*it).name, (*it).cotsup);
	}
*/
	
	fprintf(fpw,"TERSE\nGO 10000\nDIVE prime.sol\nSOLU\nQUIT\nLEAVE");
	fclose(fpw);
//	delete foutlindo;
}

int bueno(int i,int a,int b)
{
	div_t div_resultado;
	if (i==0) return 1;
	div_resultado=div(i,a);
	if (div_resultado.rem==0) return 1;
	div_resultado=div(i,b);
	if (div_resultado.rem==0) return 1;
	for (int register k=0;k*a<=i;k++)
	{
		for (int register m=0;m<=((i-k*a)/b);m++)
		{
			if (k*a+m*b==i) return 1;
		}
	}
	return 0;
}
//funciones utilizadas en CotaReduNelisen
//Si paso un uno ademas me calcula la de Nelisen
void obtener_cota_lower(std::list<cota>& lista1,std::list<cota>& lista2,int maxV, int maxW, cota& cotaLU);
void hayar_intervalos(std::list<cota>& lista1,std::list<cota>& lista2,cota& cotaLU,std::list<intervalo>& listabuena);
int next_intervalo(std::list<cota>& lista1,cota& cotaLU,std::list<intervalo>& listaintervalos,int ne1,int me1);
intervalo calcular_maximo(std::list<intervalo>& listabu,cota& LU,int V,int W,int l,int h,int tipo);
void merge_intervalos(std::list<intervalo>& listan,std::list<intervalo>& listap,cota& LU,std::list<intervalo>& listabuena);
double valor_funcion(intervalo& elegido,double x0);
intervalo mostrar_nueva(intervalo& elegido,cota& LU,double val_cota,int tipo,int V, int W,int l,int a,double x0,int mayor);
void redu_Nelisen(intervalo &,intervalo &,double,int , int ,int ,int  );

//Haya la cota de Dowsland y la de Nelisen si 

intervalo PALLET::CotaReduNelisen(int tipo)
{


	intervalo salida;

	cota LU(0,0);

	std::list<intervalo> lbue;
//	std::list<v> m_lista_W;

//	cin >> X >> Y >> a >> b;

	//buscar partición perfecta
//	if (V<L)  return;
//	if (W<A)  return;
	//Por la forma de generarlos

	obtener_cota_lower(m_Eficientes_X,m_Eficientes_Y,(m_AnchoR_Pallet/m_Ancho_Caja),(m_LargoR_Pallet/m_Ancho_Caja),LU);
//	if (LU.first==LU.second) (cout1<<"UN PUNTO");
//	cout1<<"("<<LU.first<<","<<LU.second<<")"<<"\n";

	hayar_intervalos(m_Eficientes_X,m_Eficientes_Y,LU,lbue);
//	fout<<"\n"<<"Pallet"<<" "<<L<<" "<<A<<" "<<l<<" "<<a;
	
	salida=calcular_maximo(lbue,LU,m_AnchoR_Pallet,m_LargoR_Pallet,m_Ancho_Caja,m_Largo_Caja,tipo);
	//

//	SetAnchoRPallet(salida[0]);
//	SetLargoRPallet(salida[1]);
//	SetAnchoCaja(salida[2]);
//	SetLargoCaja(salida[3]);
	printf("");
	int CoTa=salida[4];
	SetCotaDowsland(CoTa);

	return salida;

//	W=particion(Y,a,b);
/*	pV=particiones(V);
	pW=particiones(W);*/
//	cout1<<"Intervalo"<<"( "<<LU.first<<" ,"<<LU.second<<")"<<"\n";
//	fout<<"\t"<<"Cota"<<"\t"<< num_boxes<<"\n";


}
void obtener_cota_lower(std::list<cota>& lista1,std::list<cota>& lista2,int maxV, int maxW, cota& cotaLU)
{
	
	int n1,m1,n2,m2;
	double a,maxim=0,minim=99999,b,val;
	std::list<cota>::iterator lp1,lp2;
	//Primera ecuación
	for(lp1=lista1.begin();lp1!=lista1.end();lp1++)
	{
		for(lp2=lista1.begin();lp2!=lista1.end() && lp1!=lp2;lp2++)
		{
			n1=(*lp1).first;
			m1=(*lp1).second;
			n2=(*lp2).first;
			m2=(*lp2).second;
			//Primera ecuación
			a=(m2-m1-1);
			b=(n1-n2);
			if (b!=0) (val=(a/b));
			else val=0;
			if (val>maxim) (maxim=val);
			//Segunda ecuación
			a=(m2);
			b=(maxV+1-n2);
			if (b!=0) (val=(a/b));
			else val=0;
			if (val>maxim) (maxim=val);
			//Tercera ecuación
			a=(m2-m1+1);
			b=(n1-n2);
			if (b!=0) (val=(a/b));
			else val=0;
			if (val<minim) (minim=val);
//			cout1<<n1<<" "<<m1<<" "<<n2<<" "<<m2<<"\n";
		}
	}
	//Cuarta ecuación
	for(lp1=lista2.begin();lp1!=lista2.end();lp1++)
	{
		for(lp2=lista2.begin();lp2!=lista2.end() && lp1!=lp2;lp2++)
		{
			n1=(*lp1).first;
			m1=(*lp1).second;
			n2=(*lp2).first;
			m2=(*lp2).second;
			a=(m2-m1-1);
			b=(n1-n2);
			if (b!=0) (val=(a/b));
			else val=0;
			if (val>maxim) (maxim=val);
			a=(m2);
			b=(maxW+1-n2);
			if (b!=0) (val=(a/b));
			else val=0;
			if (val>maxim) (maxim=val);
			//TERcera 
			a=(m2-m1+1);
			b=(n1-n2);
			if (b!=0) (val=(a/b));
			else val=0;
			if (val<minim) (minim=val);
//			cout1<<n1<<" "<<m1<<" "<<n2<<" "<<m2<<"\n";
			
		}
	}
	cotaLU.first=maxim;
	cotaLU.second=minim;
	
}

void hayar_intervalos(std::list<cota>& lista1,std::list<cota>& lista2,cota& cotaLU,std::list<intervalo>& listabuena)
{
	int n1,m1,N1,M1;
	int falla=0;
	double maxim1=0,maxim2=0;
	double r2=9999;
	intervalo intern,interp;
	std::list<intervalo> listan,listap;

	std::list<intervalo>::iterator it1,it2;
	std::list<cota>::iterator lc1,lc2;
//	pintar_lista_cota(lista1);
//	pintar_lista_cota(lista2);

	//Haya el màximo para el primero
	for(lc1=lista1.begin();lc1!=lista1.end();lc1++)
	{
		n1=(*lc1).first;
		m1=(*lc1).second;
		if ((n1*cotaLU.first+m1)>=maxim1) 
		{
			(maxim1=(n1*cotaLU.first+m1));
			N1=n1;		
			M1=m1;
		}
	}
	//Guardo en mi nueva listan
	intern.push_back(N1);
	intern.push_back(M1);
	intern.push_back(cotaLU.first);
	listan.push_back(intern);
//	cout1<<inter[0]<<inter[1]<<"\n";


	//HAya el maximo para el segundo

	for(lc2=lista2.begin();lc2!=lista2.end();lc2++)
	{
		n1=(*lc2).first;
		m1=(*lc2).second;
		if ((n1*cotaLU.first+m1)>=maxim2) 
		{
			(maxim2=(n1*cotaLU.first+m1));
			N1=n1;		
			M1=m1;
		}
	}
	interp.push_back(N1);
	interp.push_back(M1);
	interp.push_back(cotaLU.first);
	listap.push_back(interp);

	//Si tengo el primero tengo que calcular ahora donde meto 
	// los intervalos y como
	//Ordeno las particiones
//	reverse1(lista1.begin(),lista1.end());
//	reverse1(lista2.begin(),lista2.end());
	
	int casca=0;

	do{
		it1=listan.end();
		assert(it1!=listap.begin());

		it1--;
	casca=next_intervalo(lista1,cotaLU,listan,(*it1)[0],(*it1)[1]);
	}
	while(casca!=1);
		
	do{
		it1=listap.end();
		assert(it1!=listap.begin());

		it1--;
	casca=next_intervalo(lista2,cotaLU,listap,(*it1)[0],(*it1)[1]);
	}
	while(casca!=1);

	//Ya tengo dos listas listan me dice los intervalos para n
	//listap los intervalos para los que tengo
/*	pintar_lista(listan);
	cout1<<"una"<<endl;
	pintar_lista(listap);
	cout1<<"una"<<endl;*/

	for(it1=listan.begin();it1!=listan.end();it1++)
	{
		it2=it1;
		it2++;

		if (it2!=listan.end())
			(*it1).push_back((*it2)[2]);
		else
			(*it1).push_back(cotaLU.second);

		
	}

	for(it1=listap.begin();it1!=listap.end();it1++)
	{
		it2=it1;
		it2++;
		if (it2!=listap.end())
			(*it1).push_back((*it2)[2]);
		else
			(*it1).push_back(cotaLU.second);
		
	}
//	pintar_lista(listabuena);

	//Borro los que sean iguales
	for(it1=listap.begin();it1!=listap.end();it1++)
	{
		
		if((*it1)[2]==(*it1)[3])
		{
			
			it2=it1;
			it2--;
			listap.erase(it1);
			it1=it2;
			
		}
		
	}
	for(it1=listan.begin();it1!=listan.end();it1++)
	{
		
		if((*it1)[2]==(*it1)[3])
		{
			it2=it1;
			it2--;
			listan.erase(it1);
			it1=it2;
		}
		
	}

//	pintar_lista(listan);
//	pintar_lista(listap);


	//Ahora ya tengo los intervalos como yo quiero
	//Ahora intentare unir estos intervalos
	merge_intervalos(listan,listap,cotaLU,listabuena);

	it1=listabuena.begin();
	do
	{		
		if((*it1)[4]==(*it1)[5])
		{
		
			it1=listabuena.erase(it1);
			continue;
		}
		it1++;
		
	}while(it1!=listabuena.end());

/*	cout1<<"una"<<endl;

	pintar_lista(listan);
	cout1<<"una"<<endl;

	pintar_lista(listap);
	cout1<<"una"<<endl;

	pintar_lista(listabuena);
*/

}

int next_intervalo(std::list<cota>& lista1,cota& cotaLU,std::list<intervalo>& listaintervalos,int ne1,int me1)
{
	int n1,m1,N1=0,M1=0;
	double maxim=0,l1;

	double r2=9999;
	intervalo inter;
	std::list<cota>::iterator lc1;
	for(lc1=lista1.begin();lc1!=lista1.end();lc1++)
	{
		if ((*lc1).first>ne1)
		{
			n1=(*lc1).first;
			m1=(*lc1).second;
			//	l1=((m1-me1)/(ne1-n1));
			l1=(m1-me1);
			l1=l1/(ne1-n1);
			//mayor que el extremo inferior abierto
			if (l1<r2) 
			{
				r2=l1;
				N1=n1;
				M1=m1;
			}
		}
		
	}
	inter.push_back(N1);
	inter.push_back(M1);
	inter.push_back(r2);
	if (r2>cotaLU.second)
	{
//		inter.pop_back();
//		inter.push_back(LU.second);
//		listainter.push_back(inter);

		return 1;
	}
	else
	{
		listaintervalos.push_back(inter);
//		int casca=next_intervalo(lista1,LU,listainter,N1,M1);
		return 0;
	}


	return 0;
}
void merge_intervalos(std::list<intervalo>& listan,std::list<intervalo>& listap,cota& LU,std::list<intervalo>& listabuena)
{

	std::list<intervalo>::iterator li1,li2;


	for(li1=listan.begin();li1!=listan.end();li1++)
	{
		for(li2=listap.begin();li2!=listap.end();li2++)
		{
			//intervalo es el mismo
/*			double a1=(*li1)[2];
			double a2=(*li2)[2];
			double b1=(*li1)[3];
			double b2=(*li2)[3];*/


			if (((*li2)[2]==(*li1)[2]) && ((*li2)[3]==(*li1)[3]))
			{
				intervalo new_intervalo1;
				new_intervalo1.push_back((*li1)[0]);
				new_intervalo1.push_back((*li1)[1]);
				new_intervalo1.push_back((*li2)[0]);
				new_intervalo1.push_back((*li2)[1]);
				new_intervalo1.push_back((*li2)[2]);
				new_intervalo1.push_back((*li2)[3]);
				listabuena.push_back(new_intervalo1);
			}
			
			//Intervalo mas grande por la derecha
			if ((((*li2)[2]<(*li1)[3]) && ((*li2)[2]>(*li1)[2])) && ((*li2)[3]>(*li1)[3]))
			{
				intervalo new_intervalo2;
				new_intervalo2.push_back((*li1)[0]);
				new_intervalo2.push_back((*li1)[1]);
				new_intervalo2.push_back((*li2)[0]);
				new_intervalo2.push_back((*li2)[1]);
				new_intervalo2.push_back((*li2)[2]);
				new_intervalo2.push_back((*li1)[3]);
				listabuena.push_back(new_intervalo2);
			}
			//Intervalo mas grande por la izquierda
			if ((((*li2)[3]<(*li1)[3]) && ((*li2)[3]>(*li1)[2])) && ((*li2)[2]<(*li1)[2]))
			{
				intervalo new_intervalo3;
				new_intervalo3.push_back((*li1)[0]);
				new_intervalo3.push_back((*li1)[1]);
				new_intervalo3.push_back((*li2)[0]);
				new_intervalo3.push_back((*li2)[1]);
				new_intervalo3.push_back((*li1)[2]);
				new_intervalo3.push_back((*li2)[3]);
				listabuena.push_back(new_intervalo3);
			}
			//Intervalo mas grande	el segundo incluye primero
			if ((((*li2)[2]<=(*li1)[2]) && ((*li2)[3]>=(*li1)[3])) && (((*li2)[2]!=(*li1)[2]) || ((*li2)[3]!=(*li1)[3])))
			{
				intervalo new_intervalo4;
				new_intervalo4.push_back((*li1)[0]);
				new_intervalo4.push_back((*li1)[1]);
				new_intervalo4.push_back((*li2)[0]);
				new_intervalo4.push_back((*li2)[1]);
				new_intervalo4.push_back((*li1)[2]);
				new_intervalo4.push_back((*li1)[3]);
				listabuena.push_back(new_intervalo4);
			}
			//Intervalo mas grande el primero incluye al segundo	
			if ((((*li2)[2]>=(*li1)[2]) && ((*li2)[3]<=(*li1)[3])) && (((*li2)[2]!=(*li1)[2]) || ((*li2)[3]!=(*li1)[3])))
			{
				intervalo new_intervalo5;
				new_intervalo5.push_back((*li1)[0]);
				new_intervalo5.push_back((*li1)[1]);
				new_intervalo5.push_back((*li2)[0]);
				new_intervalo5.push_back((*li2)[1]);
				new_intervalo5.push_back((*li2)[2]);
				new_intervalo5.push_back((*li2)[3]);
				listabuena.push_back(new_intervalo5);
			}



		}
	}
}
intervalo calcular_maximo(std::list<intervalo>& listabu,cota& LU,int V,int W,int l,int h,int mayor)
{
	double fobj;
	double a,b,val;
	double x0;
	int mi=0;
	intervalo nuevo;
	std::list<intervalo>::iterator li1,li2;
//	cout1<<"hola";
//	pintar_lista(listabu);
	intervalo perro;
	for(li1=listabu.begin();li1!=listabu.end();li1++)
	{

		a=((*li1)[1]) * ((*li1)[3]);
		b=((*li1)[0]) * ((*li1)[2]);
		if (b==0)
		{

			(x0=0);
		}
		else
		{	
			val=(a/b);
			x0=pow(val,0.5);
		}
		if ((*li1)[4]<x0 && x0<=(*li1)[5] && (x0!=LU.second))
		{
			//Si numero es extremo
			if ((x0==(*li1)[5]))
			{
			fobj=valor_funcion((*li1),x0);
			nuevo=mostrar_nueva((*li1),LU,fobj,0,V,W,l,h,x0,mayor);
			nuevo.push_back(fobj);
			return nuevo;
			}
			else
			{
			fobj=valor_funcion((*li1),x0);
			nuevo=mostrar_nueva((*li1),LU,fobj,1,V,W,l,h,x0,mayor);
			nuevo.push_back(fobj);
			return nuevo;
			}
			
		}
		double f1=valor_funcion((*li1),(*li1)[4]);
		double f2=valor_funcion((*li1),(*li1)[5]);
		if (f1<f2)
		{
			if (li1!=listabu.begin())
			{

			nuevo=mostrar_nueva((*li1),LU,f1,0,V,W,l,h,(*li1)[4],mayor);
			nuevo.push_back(f1);
			return nuevo;

			}
			else
			{
//				cout1<<"EXTREMO";
//				fout<<"EXTREMO";

//				cout1<<(*li1)[5];
//AQui
				nuevo=mostrar_nueva((*li1),LU,f1,2,V,W,l,h,(*li1)[4],mayor);
				nuevo.push_back(f1);
				return nuevo;

			}
			
			
		}
		mi++;
		if (mi==1)
		{

		perro.push_back((*li1)[0]);
		perro.push_back((*li1)[1]);
		perro.push_back((*li1)[2]);
		perro.push_back((*li1)[3]);
		perro.push_back((*li1)[4]);
		perro.push_back((*li1)[5]);
		}
		else
		{
			perro.erase(perro.begin(),perro.end());
			perro.push_back((*li1)[0]);
			perro.push_back((*li1)[1]);
			perro.push_back((*li1)[2]);
			perro.push_back((*li1)[3]);
			perro.push_back((*li1)[4]);
			perro.push_back((*li1)[5]);
		}



		
		
	}
	double f2=valor_funcion(perro,perro[5]);
//	cout1<<"EXTREMO";
//	fout<<"EXTREMO";

//	cout1<<perro[5];

	nuevo=mostrar_nueva(perro,LU,f2,3,V,W,l,h,LU.second,mayor);
	nuevo.push_back(f2);
	//Aqui
	return nuevo;
}
		
		


double valor_funcion(intervalo& elegido,double x0)
{
	double fobjetivo;
	fobjetivo=((elegido[0])*(elegido[2])*x0)+(elegido[0]*elegido[3])+(elegido[1]*elegido[2])+((elegido[1]*elegido[3])/x0);

	return fobjetivo;
}
intervalo mostrar_nueva(intervalo& elegido,cota& LU,double val_cota,int tipo,int V, int W,int l,int a,double x0,int mayor)
{
	double valor,val1,val2,i,p,extinf,extsup,extinf1,extsup1;
	int X,Y;
	int nume,deno;
	intervalo nuevo;
	extinf=elegido[4];
	extsup=elegido[5];
	extinf1=elegido[4];
	extsup1=elegido[5];

	
	for (nume=1;nume<100;nume++)
	{
		for(deno=1;deno<100;deno++)
		{
			p=elegido[4];
			i=elegido[5];
			p=V;
			i=W;

			val1=deno;
			val2=nume;
//			cout1<<val1<<" "<<val2<<" ";
			valor=((double) deno/(double) nume);
			valor=valor;
			// Si es mas grande que el intervalo otro
			if (valor>(elegido[5])) break;

			// si es igual pero no es en un extremo del intervalo
			if ((valor>=elegido[4]) && (valor<=elegido[5]) && (valor!=LU.first) && (valor!=LU.second) && (tipo!=3) && (tipo!=2) && (tipo!=1))
			{
//				cout1<<valor<<" "<<i<<" "<<j<<elegido[4]<<" "<<elegido[5]<<"\n";
				if (nume<a)
				{
				X=elegido[0]*deno+elegido[1]*nume;
				Y=elegido[2]*deno+elegido[3]*nume;

				PALLET P1(X,Y,deno,nume);
				PALLET P2(V,W,l,a);

				int valida=ComprobarParticiones(P1,P2);
					if (valida==0)
					{
						nuevo.push_back(X);
						nuevo.push_back(Y);
						nuevo.push_back(deno);
						nuevo.push_back(nume);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					

				//	fout<<"Pallet"<<"\t"<<X<<"\t"<<Y<<"\t"<<deno<<"\t"<<nume;
			//		if (X<Largo) return nuevo;

				//	buscar_lista(X,Y,deno,nume,val_cota);
					return nuevo ;
					}
				}
				else
				{	
						nuevo.push_back(V);
						nuevo.push_back(W);
						nuevo.push_back(l);
						nuevo.push_back(a);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					

				//	fout<<"Pallet"<<" "<<V<<" "<<W<<" "<<l<<" "<<a;
				//	buscar_lista(V,W,l,a,((V*W)/(l*a)));
					return nuevo;
				}

			}
			//Si es en un extremo
			if ((valor>elegido[4]) && (valor<elegido[5]) && (tipo!=3) && (tipo!=2) && (tipo!=1))
			{
				if (nume<a)
				{
					X=elegido[0]*deno+elegido[1]*nume;
					Y=elegido[2]*deno+elegido[3]*nume;
				PALLET P1(X,Y,deno,nume);
				PALLET P2(V,W,l,a);

				int valida=ComprobarParticiones(P1,P2);
					if (valida==0) 
					{
						nuevo.push_back(X);
						nuevo.push_back(Y);
						nuevo.push_back(deno);
						nuevo.push_back(nume);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					


				//		fout<<"Pallet"<<"\t"<<X<<"\t"<<Y<<"\t"<<deno<<"\t"<<nume;
		//				if (X<Largo) return nuevo;
				//		buscar_lista(X,Y,deno,nume,val_cota);
						return nuevo;
					}				
				}
				else
				{		
						nuevo.push_back(V);
						nuevo.push_back(W);
						nuevo.push_back(l);
						nuevo.push_back(a);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					

				//	fout<<"Pallet"<<" "<<V<<" "<<W<<" "<<l<<" "<<a;
				//	buscar_lista(V,W,l,a,((V*W)/(l*a)));
					return nuevo;
				}


			}
			//Si es en un estremo de la cota
			if ((valor>=elegido[4]) && (valor<=elegido[5]) && (tipo==3))
			{
				X=elegido[0]*deno+elegido[1]*nume;
				Y=elegido[2]*deno+elegido[3]*nume;
				PALLET P1(X,Y,deno,nume);
				PALLET P2(V,W,l,a);

				int valida=ComprobarParticiones(P1,P2);
				if (valida==0 && (nume<a)) //Son iguales y es mas pequeña
				{
						nuevo.push_back(X);
						nuevo.push_back(Y);
						nuevo.push_back(deno);
						nuevo.push_back(nume);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					
				//fout<<"Pallet"<<" "<<X<<" "<<Y<<" "<<deno<<" "<<nume;
				//buscar_lista(X,Y,deno,nume,val_cota);
				return nuevo;
				}
				else
				{ //si no es igual buscar otro
					if (valor!=elegido[5])	extinf=valor;
					if ((nume>=a))//Si es mayor meter antigua
					{
						nuevo.push_back(V);
						nuevo.push_back(W);
						nuevo.push_back(l);
						nuevo.push_back(a);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}
				//		fout<<"Pallet"<<" "<<V<<" "<<W<<" "<<l<<" "<<a;
				//		buscar_lista(V,W,l,a,((V*W)/(l*a)));
						return nuevo;

					}
				}
				

			}
			//Si es en otro extremo de la cota
			if ((valor>=elegido[4]) && (valor<=elegido[5]) && (tipo==2))
			{
				X=elegido[0]*deno+elegido[1]*nume;
				Y=elegido[2]*deno+elegido[3]*nume;
				PALLET P1(X,Y,deno,nume);
				PALLET P2(V,W,l,a);

				int valida=ComprobarParticiones(P1,P2);
				if (valida==0 && (nume<a)) //Son iguales y es mas pequeña
				{
						nuevo.push_back(X);
						nuevo.push_back(Y);
						nuevo.push_back(deno);
						nuevo.push_back(nume);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}
				//fout<<"Pallet"<<" "<<X<<" "<<Y<<" "<<deno<<" "<<nume;
				//buscar_lista(X,Y,deno,nume,val_cota);
				return nuevo;

				}
				else//Son diferentes buscar otro
				{
					if (valor!=elegido[4]) extsup=valor;
					if ((nume>=a))//Si es mayor meter antigua
					{
						nuevo.push_back(V);
						nuevo.push_back(W);
						nuevo.push_back(l);
						nuevo.push_back(a);

						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					

				//		fout<<"Pallet"<<" "<<V<<" "<<W<<" "<<l<<" "<<a;
				//		buscar_lista(V,W,l,a,((V*W)/(l*a)));
						return nuevo;

					}
				}


			}
						//Si es en un numero iracional
			if ((valor>=extinf1) && (valor<=extsup1) && (tipo==1))
			{
				X=elegido[0]*deno+elegido[1]*nume;
				Y=elegido[2]*deno+elegido[3]*nume;
		//		if (X<Largo) return nuevo;
				PALLET P1(X,Y,deno,nume);
				PALLET P2(V,W,l,a);

				int valida=ComprobarParticiones(P1,P2);
				if ((valida==0) && (nume<a)) //Son iguales
				{
						nuevo.push_back(X);
						nuevo.push_back(Y);
						nuevo.push_back(deno);
						nuevo.push_back(nume);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					
					
				//fout<<"Pallet"<<" "<<X<<" "<<Y<<" "<<deno<<" "<<nume;
				//buscar_lista(X,Y,deno,nume,val_cota);
				return nuevo;

				}
				else//Son diferentes buscar otro
				{
					if (valor>x0) extsup=valor;
					if (valor<x0) extinf=valor;
					if ((nume>=a))//Si es mayor meter antigua
					{
						nuevo.push_back(V);
						nuevo.push_back(W);
						nuevo.push_back(l);
						nuevo.push_back(a);
						if (mayor==1) 
						{
							redu_Nelisen(nuevo,elegido,x0,V,W,l,a);
						}					

				//		fout<<"Pallet"<<" "<<V<<" "<<W<<" "<<l<<" "<<a;
						//	buscar_lista(V,W,l,a,((V*W)/(l*a)));
						return nuevo ;

					}
				}


			}





		}
	}
	return nuevo;
//	fout<<"algo mal no pasa por ninguno";
}
	//Rutina que calcula con un x cual es el que corresponden con
	//Nelisen

void redu_Nelisen(intervalo &vec,intervalo &elegido,double x,int V, int W,int l,int a )
{
	double nume=0,deno=0,X,Y;
	double maximo=200,valor;
	double nume1=0,deno1=0,valor2=0;
	maximo=(double)(V*W)/(double)(l*a);
	for (deno=1;deno<=10000;deno++)
	{
		double pp=floor((double(x-double(epsilon))*double (deno)));
		for (nume=pp;nume<=40000;nume++)
		{
			nume1=nume;
			deno1=deno;
			valor=nume1/deno1;
			if (valor>x+epsilon) break;
			if(((x+double(epsilon))>valor) && (valor>(x-double(epsilon))))
			{
				X=elegido[0]*nume+elegido[1]*deno;
				Y=elegido[2]*nume+elegido[3]*deno;
				int valida=0;
				PALLET P1(X,Y,nume,deno);
				PALLET P2(V,W,l,a);
				valida=ComprobarParticiones(P1,P2);
				valor2=(double)(X*Y)/(double)(deno*nume);
				if (valida==0 && valor2<maximo-0.05)
				{	
						vec.clear();
						maximo=valor2;
						vec.push_back(X);
						vec.push_back(Y);
						vec.push_back(nume);
						vec.push_back(deno);

				}
			}
		}
	}
	return;
//	cout1<<"Algo mal"<<V<<" "<<W<<" "<<l<<" "<<a;
	exit(5);
}



int ComprobarParticiones(PALLET &P1,PALLET &P2)
{
	std::list<cota> lista_X1,lista_X2,lista_Y1,lista_Y2;

	lista_X1=P1.GetParticionesX();
	lista_X2=P2.GetParticionesX();
	lista_Y1=P1.GetParticionesY();
	lista_Y2=P2.GetParticionesY();
/*	cout1<<X1<<endl;
	pintar_lista_cota(lista_X1);
	cout1<<Y1<<endl;
	pintar_lista_cota(lista_Y1);
	cout1<<X2<<endl;
	pintar_lista_cota(lista_X2);
	cout1<<Y2<<endl;
	pintar_lista_cota(lista_Y2);*/
	//Si no tienen el mismo tamaño fin
	if (lista_X1.size()!=lista_X2.size()) return 1;
	if (lista_Y1.size()!=lista_Y2.size()) return 1;


	std::list<cota>::iterator k1,k2;
	//Comparar X
	for(k1=lista_X1.begin(),k2=lista_X2.begin();(k1!=lista_X1.end()) || (k2!=lista_X2.end())  ;k1++,k2++)
	{
		if ((k1==lista_X1.end()) || (k2==lista_X2.end()))
			return 1; //1 es FALSO
		else
		{
			if (((*k1).first!=(*k2).first) || ((*k1).second!=(*k2).second))
				return 1;
		}
	}
	//Comparar Y
	for(k1=lista_Y1.begin(),k2=lista_Y2.begin();(k1!=lista_Y1.end()) || (k2!=lista_Y2.end())  ;k1++,k2++)
	{
		if ((k1==lista_Y1.end()) || (k2==lista_Y2.end()))
			return 1; //1 es FALSO
		else
		{
			if (((*k1).first!=(*k2).first) || ((*k1).second!=(*k2).second))
				return 1;
		}
	}
	return 0;
}


bool PALLET::ParticionEficienteX(int i)
{
	if (m_Eficientes!=true) return true;

	if (i==0) return true;
	if (i==m_L) return true;
	std::list<cota> ::iterator itX;
	for (itX=m_Eficientes_L.begin();itX!=m_Eficientes_L.end();itX++)
	{
		for (int k=0;k<=(*itX).first;k++)
		{
			for(int j=0;j<=(*itX).second;j++)
			{
				
				if (i==((k*m_l)+(j*m_w))) return true;
			}
		}
	}
	return false;
}
bool PALLET::ParticionEficienteY(int i)
{
	if (m_Eficientes!=true) return true;
	if (i==0) return true;
	if (i==m_W) return true;

	std::list<cota> ::iterator itY;
	for (itY=m_Eficientes_W.begin();itY!=m_Eficientes_W.end();itY++)
	{
		for (int k=0;k<=(*itY).first;k++)
		{
			for(int j=0;j<=(*itY).second;j++)
			{
				if (i==((k*m_l)+(j*m_w))) return true;
			}
		}
	}
	return false;
}
bool PALLET::ParticionEficiente(int i, char meto, char lado)
{
	if (m_Eficientes!=true) return true;

	if (i==0) return true;
	if (i==m_W) return true;

	std::list<cota> ::iterator itY;
	if (lado=='L')
	{
	for (itY=m_Eficientes_L.begin();itY!=m_Eficientes_L.end();itY++)
	{
		int k=0;
		
		if (meto=='H') k=1;
		for (;k<=(*itY).first && (*itY).first!=0;k++)
		{
			int j=0;
			if (meto=='V') j=1;
			for(;j<=(*itY).second && (*itY).second!=0;j++)
			{
				if (i==((k*m_l)+(j*m_w))) return true;
			}
		}
	}
	}
	if (lado=='W')
	{
	for (itY=m_Eficientes_W.begin();itY!=m_Eficientes_W.end();itY++)
	{
		int k=0;
		if (meto=='V') k=1;
		for (;k<=(*itY).first && (*itY).first!=0;k++)
		{

			int j=0;
			if (meto=='H') j=1;
			for(;j<=(*itY).second && (*itY).second!=0;j++)
			{
				if (i==((k*m_l)+(j*m_w))) return true;
			}
		}
	}
	}

	return false;
}
bool PALLET::ParticionEficienteX(int i,char tipo)
{
	if (m_Eficientes!=true) return true;
	if (i==0) return true;
	if (i==m_L) return true;
/*
	if (tipo=='H')
	{
		if ((i/m_l)>m_hL) return false;
		else
		{
			if ((i/m_l)<m_hL)
			{
				return ParticionEficienteX(i+m_w);
			}
		}
	}
	if (tipo=='V')
	{
		if((i/m_w)>m_vL) return false;
		else
		{
			if ((i/m_w)<m_vL)
			{
				return ParticionEficienteX(i+m_l);
			}
		}
	}

	return true;*/

	if (tipo=='H' && (i/m_l)<=m_hL) return true;
	if (tipo=='V' && (i/m_w)<=m_vL) return true;
	return false;
		
		
		
/*
	if (i==0) return true;
	if (i==m_L) return true;
	std::list<cota> ::iterator itX;
	for (itX=m_Eficientes_L.begin();itX!=m_Eficientes_L.end();itX++)
	{
		if (tipo=='H')
		{
			for (int k=0;k<=(*itX).first;k++)
			{
				if (i==(k*m_l)) return true;
			}
		}
		if (tipo=='V')
		{
			for (int j=0;j<=(*itX).second;j++)
			{
				if (i==(j*m_w)) return true;
			}
		}
	}
	return false;*/
}

bool PALLET::PerdidaPosibleX(BLOQUE &B1,int x)
{
	std::list<cota> ::iterator itX;
	for (itX=m_Eficientes_L.begin();itX!=m_Eficientes_L.end();itX++)
	{
		if (B1.GetTipo()=='H')
		{
			if ((*itX).first==x)
			{
				if ((*itX).first*m_l+(*itX).second*m_w==m_L)
					return true;
				else
				{
					if (m_L-((*itX).first*m_l+(*itX).second*m_w)*B1.Width()>((m_L*m_W)-(m_best_sol)*(m_l*m_w)))
						return false;
				}
			}
		}
		if (B1.GetTipo()=='V')
		{
			if ((*itX).second==x)
			{
				if ((*itX).first*m_l+(*itX).second*m_w==m_L)
					return true;
				else
				{
					if (m_L-((*itX).first*m_l+(*itX).second*m_w)*B1.Width()>((m_L*m_W)-(m_best_sol)*(m_l*m_w)))
						return false;
				}
			}
		}
	}
	return true;
}
bool PALLET::PerdidaPosibleY(BLOQUE &B1,int x)
{
	std::list<cota> ::iterator itX;
	for (itX=m_Eficientes_W.begin();itX!=m_Eficientes_W.end();itX++)
	{
		if (B1.GetTipo()=='V')
		{
			if ((*itX).first==x)
			{
				if ((*itX).first*m_l+(*itX).second*m_w==m_L)
					return true;
				else
				{
					if (m_L-((*itX).first*m_l+(*itX).second*m_w)*B1.Height()>((m_L*m_W)-(m_best_sol+1)*(m_l*m_w)))
						return false;
				}
			}
		}
		if (B1.GetTipo()=='H')
		{
			if ((*itX).second==x)
			{
				if ((*itX).first*m_l+(*itX).second*m_w==m_L)
					return true;
				else
				{
					if (m_L-((*itX).first*m_l+(*itX).second*m_w)*B1.Height()>((m_L*m_W)-(m_best_sol+1)*(m_l*m_w)))
						return false;
				}
			}
		}
	}
	return true;
}
bool PALLET::ParticionEficienteY(int i,char tipo)
{
	if (m_Eficientes!=true) return true;

	if (i==0) return true;
	if (i==m_L) return true;


	/*
	if (tipo=='H')
	{
		if ((i/m_w)>m_hW) return false;
		else
		{
			if ((i/m_w)<m_hW)
			{
				return ParticionEficienteY(i+m_l);
			}
		}
	}
	if (tipo=='V')
	{
		if ((i/m_l)>m_vW) return false;
		else
		{
			if ((i/m_l)<m_vW)
			{
				return ParticionEficienteY(i+m_w);
			}
		}
	}
	return true;
	*/
	
	if (tipo=='H' && (i/m_w)<=m_hW) return true;
	if (tipo=='V' && (i/m_l)<=m_vW) return true;
	return false;
	
	/*

	if (i==0) return true;
	if (i==m_W) return true;

	std::list<cota> ::iterator itY;
	for (itY=m_Eficientes_W.begin();itY!=m_Eficientes_W.end();itY++)
	{
		if (tipo=='V')
		{
			for (int k=0;k<=(*itY).first;k++)
			{
				if (i==(k*m_l)) return true;
			}
		}
		if (tipo=='H')
		{
			for (int j=0;j<=(*itY).second;j++)
			{
				if (i==(j*m_w)) return true;
			}
		}
	}
	return false;*/
}
int no_esta_lista(std::list<inter_corto> &Lista,int x,int y)
{
	std::list<inter_corto>::iterator il;
//	inter_corto::iterator iv;
	for (il=Lista.begin();il!=Lista.end();il++)
	{
		if (x==(*il)[0] && y==(*il)[1]) return 1;
	}
	return 0;
}
int PALLET::no_esta_Perdida(perdida &Nueva,std::list<perdida> &Lista)
{
	std::list<perdida>::iterator il;
//	inter_corto::iterator iv;
	for (il=Lista.begin();il!=Lista.end();il++)
	{
		if (Nueva.orientacion==(*il).orientacion && Nueva.PA==(*il).PA && Nueva.PD==(*il).PD && Nueva.x==(*il).x && Nueva.y==(*il).y) return 1;
	}
	return 0;
}
int no_esta(int x, std::vector<int> &vec)
{
	std::vector<int>::iterator i4;
	for (i4=vec.begin();i4!=vec.end();i4++)
	{	
		if ((*i4)==x) return 1;
	}
	return 0;
}
int maximoRpertenece(int x,std::vector<int> &vec)
{
	std::vector<int>::iterator i4;
	int val=0;
	if (vec.size()==1) return 0;
	for (i4=vec.begin();i4!=vec.end() && (*i4)<=x;i4++)
	{
		val=(*i4);
	}
	return val;
}
int PALLET::GetNumeroRes()
{
	div_t par;
	int rest=2;
	par=div(m_LargoR_Pallet,2);
	if (par.rem!=0) rest++;
	par=div(m_AnchoR_Pallet,2);
	if (par.rem!=0) rest++;
	return (m_ListaDeRes.size()+1+rest);
//	return (m_ListaDeRes.size()+1);
}
int PALLET::GetNumeroResSime()
{
	div_t par;
	int rest=2;
	par=div(m_LargoR_Pallet,2);
	if (par.rem!=0) rest++;
	par=div(m_AnchoR_Pallet,2);
	if (par.rem!=0) rest++;
	return (rest);
}
void PALLET::CotaBarnes(void)
{
	printf("mierda");
	div_t r,s;
	unsigned long int A,B,Perdida;
	r=div(m_LargoR_Pallet,m_Ancho_Caja);
	s=div(m_AnchoR_Pallet,m_Ancho_Caja);
	A=__min((r.rem*s.rem),((m_Ancho_Caja-r.rem)*(m_Ancho_Caja-s.rem)));
	r=div(m_LargoR_Pallet,m_Largo_Caja);
	s=div(m_AnchoR_Pallet,m_Largo_Caja);
	B=__min((r.rem*s.rem),((m_Largo_Caja-r.rem)*(m_Largo_Caja-s.rem)));
	Perdida=__max(A,B);
	int NuevaCota=((m_AnchoR_Pallet*m_LargoR_Pallet)-Perdida)/(m_Largo_Caja*m_Ancho_Caja);
	if (m_Cota==0)
	{
		m_Cota=NuevaCota;
	}
	else if (m_Cota>NuevaCota)
	{
		m_Cota=NuevaCota;
	}
}
int PALLET::ParticionPerfecta(int i)
{
	if (i<m_w) return i;
	int maximo=0;
	int a=m_l;
	int b=m_w;
	div_t div_resultado;
	if (i==0) return 0;
	div_resultado=div(i,a);
	if (div_resultado.rem==0) return 0;
	div_resultado=div(i,b);
	if (div_resultado.rem==0) return 0;
	for (int register k=0;k*a<=i;k++)
	{
		for (int register m=0;m<=((i-k*a)/b);m++)
		{
			if (k*a+m*b==i) return 0;
			if (((k*a+m*b) > maximo )&&((k*a+m*b) <i)) (maximo=k*a+m*b);

		}
	}
	return (i-maximo);
}
int PALLET::HeuristicoG4(void)		
{
	FILE *salida;
	int result,X,Y,a,b,Heuri,Cota;
	salida=fopen("datosG4.txt","r");
	while (!feof(salida))
	{
		result=fscanf(salida,"%d %d %d %d %d %d",&X, &Y, &a, &b,&Heuri, &Cota);
		if ((X==m_Ancho0_Pallet) && (Y==m_Largo0_Pallet) && (a==m_Ancho0_Caja) && (b==m_Largo0_Caja))
		{
			fclose(salida);
			return Heuri;
		}
	}
	fclose(salida);
	return 0;
}
void PALLET::CalcularMaximosCajas(void)
{
	m_hL=1000;
	m_hW=1000;
	m_vL=1000;
	m_vW=1000;
		//Esta funcion me dice cuales son las maximas dimensiones para
	//un bloque de piezas horizontales y verticales
	//Lo hago a partir de la lista de variables de raster points
	int altoV=0;
	int anchoV=0;
	int altoH=0;
	int anchoH=0;/*
	bool valeAltoV=true;
	bool valeAnchoV=true;
	bool valeAltoH=true;
	bool valeAnchoH=true;
	std::vector<var> ::iterator itV;
	for (itV=m_VectorDeVar.begin();itV!=m_VectorDeVar.end();itV++)
	{
		if ((*itV).orientacion=='V')
		{
			//Busco maximo para alto
			if ((*itV).x==0 && valeAltoV==true && (*itV).y%m_l==0)
			{
				for (register int k=0;(k)<=((*itV).y/m_l);k++)
				{
					if ((*itV).y==k*m_l) 
					{
						altoV++;
						valeAltoV=true;
					}
					else
						valeAltoV=false;
				}
			}
			//Busco maximo para ancho
			if ((*itV).y==0 && valeAnchoV==true && (*itV).x%m_w==0)
			{
				for (register int k=0;(k)<=((*itV).x/m_w);k++)
				{
					if ((*itV).x==k*m_w) 
					{
						anchoV++;
						valeAnchoV=true;
					}
					else
						valeAnchoV=false;
				}

			}

		}
		else
		{
			//Busco maximo para alto
			if ((*itV).x==0 && valeAltoH==true && (*itV).y%m_w==0)
			{
				for (register int k=0;(k)<=((*itV).y/m_w);k++)
				{
					if ((*itV).y==k*m_w) 
					{
						altoH++;
						valeAltoH=true;
					}
					else
						valeAltoH=false;
				}
			}
			//Busco maximo para ancho
			if ((*itV).y==0 && valeAnchoH==true && (*itV).x%m_l==0)
			{
				for (register int k=0;(k)<=((*itV).x/m_l);k++)
				{
					if ((*itV).x==k*m_l) 
					{
						anchoH++;
						valeAnchoH=true;
					}
					else
						valeAnchoH=false;

				}

			}
		}
	}
	if (anchoH>1) m_hL=anchoH;
	if (anchoV>1) m_vL=anchoV;
	if (altoH>1) m_hW=altoH;
	if (altoV>1) m_vW=altoV;*/
	altoV=0;
	anchoV=0;
	altoH=0;
	anchoH=0;
	std::list<cota> ::iterator itX;
	for (itX=m_Eficientes_L.begin();itX!=m_Eficientes_L.end();itX++)
	{
		if ((*itX).first>=anchoH) anchoH=(*itX).first;
		if ((*itX).second>=anchoV) anchoV=(*itX).second;
	}
	for (itX=m_Eficientes_W.begin();itX!=m_Eficientes_W.end();itX++)
	{
		if ((*itX).first>=altoV) altoV=(*itX).first;
		if ((*itX).second>=altoH) altoH=(*itX).second;
	}
	if (anchoH<m_hL) m_hL=anchoH;
	if (anchoV<m_vL) m_vL=anchoV;
	if (altoH<m_hW) m_hW=altoH;
	if (altoV<m_vW) m_vW=altoV;

/*	if (anchoH<m_hL && anchoH>1) m_hL=anchoH;
	if (anchoV<m_vL && anchoV>1) m_vL=anchoV;
	if (altoH<m_hW && altoH>1) m_hW=altoH;
	if (altoV<m_vW && altoV>1) m_vW=altoV;*/

}
std::pair<int,int> PALLET::Maximo_Restriccion_X(inter_corto &vec)
{
	 //Recorro las variables 
	int max_X=0;
	int max_Y=0;
	std::vector<var> ::iterator itV;
	for (itV=m_VectorDeVar.begin();itV!=m_VectorDeVar.end();itV++)
	{
		if ((*itV).orientacion=='V')
		{
			if ((*itV).x+m_w>vec[0] && (*itV).x<=vec[0] && (*itV).y+m_l>vec[1] && (*itV).y<=vec[1])
			{
				if ((*itV).x>max_X) 
				{
					max_Y=(*itV).y;
					max_X=(*itV).x;
				}
				else
				{
					if ((*itV).x==max_X)
					{
						if ((*itV).y>max_Y) 
						{
							max_Y=(*itV).y;
						}
					}
				}
			}

		}
		else
		{
			if ((*itV).x+m_l>vec[0] && (*itV).x<=vec[0] && (*itV).y+m_w>vec[1] && (*itV).y<=vec[1])
			{
				if ((*itV).x>max_X) 
				{
					max_Y=(*itV).y;
					max_X=(*itV).x;
				}
				else
				{
					if ((*itV).x==max_X)
					{
						if ((*itV).y>max_Y) 
						{
							max_Y=(*itV).y;
						}
					}
				}

			}

		}
	}
	std::pair<int,int> pt(max_X,max_Y);
	return pt;

}

std::pair<int,int> PALLET::Maximo_Restriccion_Y(inter_corto &vec)
{
	 //Recorro las variables 
	int max_X=0;
	int max_Y=0;
	std::vector<var> ::iterator itV;
	for (itV=m_VectorDeVar.begin();itV!=m_VectorDeVar.end();itV++)
	{
		if ((*itV).orientacion=='V')
		{
			if ((*itV).x+m_w>vec[0] && (*itV).x<=vec[0] && (*itV).y+m_l>vec[1] && (*itV).y<=vec[1])
			{
				if ((*itV).y>max_Y) 
				{
					max_Y=(*itV).y;
					max_X=(*itV).x;
				}
				else
				{
					if ((*itV).y==max_Y)
					{
						if ((*itV).x>max_X) 
						{
							max_X=(*itV).x;
						}
					}
				}
			}

		}
		else
		{
			if ((*itV).x+m_l>vec[0] && (*itV).x<=vec[0] && (*itV).y+m_w>vec[1] && (*itV).y<=vec[1])
			{
				if ((*itV).y>max_Y) 
				{
					max_Y=(*itV).y;
					max_X=(*itV).x;
				}
				else
				{
					if ((*itV).y==max_Y)
					{
						if ((*itV).x>max_X) 
						{
							max_X=(*itV).x;
						}
					}
				}

			}

		}
	}
	std::pair<int,int> pt(max_X,max_Y);
	return pt;

}
