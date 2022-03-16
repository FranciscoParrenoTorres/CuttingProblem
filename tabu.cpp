#pragma warning (disable: 4786)
#include "Pallet.h"
// Funciones utilizadas para hacer Variables y Restricciones
char tipo_union='X';
int tope=5;
void Generar_Vector_Aleatorio(std::vector<int> &vec_temp,std::vector<int> &vec_recorrer,int dim );
FILE *fin;
std::set<int> conjunto_kk;
/*
void PALLET::Calcular_Estructura_G4_Unica(int vez)
{
//	printf("Iteracion %d\n",m_iter_actual);

	m_lista_GCuatros.clear();
	//Primero busco una estructura G4 que 
	//sea eficiente
//	printf("Iter %d",m_iter_actual);
	int menor=200,menores=0;
	bool seguir=true;
	m_G4_TCajas=0;
	m_G4_THorizontal=0;
	m_G4_TVertical=0;
	m_G4_HuecoH=0;
	m_G4_HuecoV=0;
	m_G4_CajasH=0;
	m_G4_CajasHH=0;
	m_G4_CajasV=0;
	m_G4_CajasVV=0;
	m_G4_PequeH=0;
	m_G4_PequeV=0;
	strg4 Estructura_G4,Estructura_G41;
	m_G4_THorizontal=0;
	m_G4_TVertical=0;
	m_G4_HuecoH=0;
	m_G4_HuecoV=0;
	m_G4_CajasH=0;
	m_G4_CajasV=0;
	m_G4_PequeH=0;
	m_G4_PequeV=0;
	//Primero busco una estructura G4 que 
	//sea eficiente
	for (int register i=1;seguir==true;i++)
	{
		if (i*m_w>m_l) seguir=false;
		if (vez==2 || (abs((i*m_w)-m_l)<menor) )
		{
			if (ParticionEficienteX(i*m_w+m_l)==true && ParticionEficienteY(i*m_w+m_l)==true && abs((i*m_w)-m_l)<m_w)
			{
				//menor es el hueco caso que sea cuadrado
				menor=abs((i*m_w)-m_l);
				//menores son las piezas que meto del G-4
				menores=i;
			}
		}
	}	//Tamaño del G-4 horizontal
	Estructura_G4.G4_THorizontal=(m_l+(menores*m_w));
	//Piezas que pongo en vertical
	Estructura_G4.G4_CajasV=(menores);
	//Hueco que deja en vertical
	Estructura_G4.G4_HuecoV=(abs(m_l-(menores*m_w)));
	//Tamaño del menor bloque de altura
	if ((menores*m_w)>m_l)
	{
		//Ancho
		Estructura_G4.G4_PequeH=(m_l);
		Estructura_G4.G4_PequeV=(m_l);

	}
	else
	{
		Estructura_G4.G4_PequeH=(menores*m_w);
		Estructura_G4.G4_PequeV=(menores*m_w);
	}
	//Tamaño del G-4 vertical
	Estructura_G4.G4_TVertical=(m_l+(menores*m_w));
	//Piezas que pongo en horizontal
	Estructura_G4.G4_CajasH=(menores);
	//Hueco que deja en horizontal
	Estructura_G4.G4_HuecoH=(abs(m_l-(menores*m_w)));
	Estructura_G4.G4_TCajas=((Estructura_G4.G4_CajasH+Estructura_G4.G4_CajasV)*2);
	Estructura_G4.G4_CajasHH=1;
	Estructura_G4.G4_CajasVV=1;

	m_G4_TCajas=Estructura_G4.G4_TCajas;
	m_G4_THorizontal=Estructura_G4.G4_THorizontal;
	m_G4_TVertical=Estructura_G4.G4_TVertical;
	m_G4_HuecoH=Estructura_G4.G4_HuecoH;
	m_G4_HuecoV=Estructura_G4.G4_HuecoV;
	m_G4_CajasH=Estructura_G4.G4_CajasH;
	m_G4_CajasV=Estructura_G4.G4_CajasV;
	m_G4_CajasHH=Estructura_G4.G4_CajasHH;
	m_G4_CajasVV=Estructura_G4.G4_CajasVV;
	m_G4_PequeH=Estructura_G4.G4_PequeH;
	m_G4_PequeV=Estructura_G4.G4_PequeV;

	
	if ((Estructura_G4.G4_TCajas!=0) && ((Estructura_G4.G4_HuecoH*Estructura_G4.G4_HuecoV)<=((m_L*m_W-((vez+1)*m_l*m_w))/2)))	
	{
		m_lista_GCuatros.push_back(Estructura_G4);
		m_lista_intG4.clear();
		m_lista_intG4.push_back(0);
	}


	if (menor==m_G4_CajasV && menores==m_G4_CajasH) 
	{
		return;
	}
	else
	{
		m_lista_GCuatros.clear();
	}

	bool seguir1=true,seguir2=true;
	int menor1=2000,menor2=2000,menores1=0,menores2=0;
	//si no la encuentro 
	//busco la mejor pero con diferentes piezas
	if (menores==0)
	{
	for (i=1;seguir1==true;i++)
	{
		if ((i)*m_w>m_l) seguir1=false;
		seguir2=true;
		for (int register j=1;seguir2==true && (j*m_w<=m_l) ;j++)
		{
			if ((j)*m_w>m_l) seguir2=false;
			if (abs(((j*m_w)-m_l))*abs((i*m_w)-m_l)<menor1*menor2 && (((j*m_w<=m_l) && (i*m_w<=m_l))|| (j*m_w>m_l && i*m_w>m_l)))
			{
				if (ParticionEficienteX(i*m_w+m_l)==true && ParticionEficienteY(j*m_w+m_l)==true   && (abs(((j*m_w)-m_l))<m_w || abs((i*m_w)-m_l)<m_w) )
				{
					//menor es el hueco caso que sea cuadrado
					//hueco horizontal
					menor2=abs((i*m_w)-m_l);
					//hueco vertical
					menor1=abs((j*m_w)-m_l);
					//menores son las piezas que meto del G-4
					//piezas verticales
					menores1=i;
					//piezas horizontales
					menores2=j;
				}
			}
		}
	}
	}
	//busco la mejor aunque no sea eficiente
	if ((menores==0 && menores1==0 && menores2==0)|| ((menor*menor)>((m_L*m_W-(m_Cota*m_l*m_w))/2) && (menor1*menor2)>((m_L*m_W-(m_Cota*m_l*m_w))/2)))
	{
		menor=200;
		menores1=0;
		menores2=0;
		seguir=true;
		for (int register i=1;seguir==true;i++)
		{
			if (i*m_w>m_l) seguir=false;
			if (abs((i*m_w)-m_l)<menor)
			{
				//menor es el hueco caso que sea cuadrado
				menor=abs((i*m_w)-m_l);
				//menores son las piezas que meto del G-4
				menores=i;
			}
		}
	}
	//Tamaño del G-4 horizontal
	if (menores1==0) Estructura_G41.G4_THorizontal=(m_l+(menores*m_w));
	else Estructura_G41.G4_THorizontal=(m_l+(menores1*m_w));
	//Piezas que pongo en vertical
	if (menores1==0) Estructura_G41.G4_CajasV=(menores);
	else Estructura_G41.G4_CajasV=(menores1);
	//Hueco que deja en vertical
	if (menores1==0) Estructura_G41.G4_HuecoV=(abs(m_l-(menores*m_w)));
	else  Estructura_G41.G4_HuecoV=(abs(m_l-(menores2*m_w)));
	

	//Tamaño del menor bloque de altura
	if ((menores*m_w)>m_l)
	{
		//Ancho
		Estructura_G41.G4_PequeH=(m_l);
		Estructura_G41.G4_PequeV=(m_l);

	}
	else
	{
		Estructura_G41.G4_PequeH=(menores*m_w);
		Estructura_G41.G4_PequeV=(menores*m_w);
		if (menores1!=0)
		{
			Estructura_G41.G4_PequeV=(menores2*m_w);
			Estructura_G41.G4_PequeH=menores1*m_w;
		}
	}
	//Tamaño del G-4 vertical
	if (menores1==0) Estructura_G41.G4_TVertical=(m_l+(menores*m_w));
	else Estructura_G41.G4_TVertical=(m_l+(menores2*m_w));
	//Piezas que pongo en horizontal
	if (menores1==0) Estructura_G41.G4_CajasH=(menores);
	else Estructura_G41.G4_CajasH=(menores2);
	//Hueco que deja en horizontal
	if (menores1==0) Estructura_G41.G4_HuecoH=(abs(m_l-(menores*m_w)));
	else  Estructura_G41.G4_HuecoH=(abs(m_l-(menores1*m_w)));
	Estructura_G41.G4_TCajas=((Estructura_G41.G4_CajasH+Estructura_G41.G4_CajasV)*2);
	Estructura_G41.G4_CajasHH=1;
	Estructura_G41.G4_CajasVV=1;
	// Busco una con dos verticales por lo tanto necesito dos nuevas medidas para el numero 
// de verticales a lo ancho y horizontales a lo ancho
	m_G4_TCajas=Estructura_G41.G4_TCajas;
	m_G4_THorizontal=Estructura_G41.G4_THorizontal;
	m_G4_TVertical=Estructura_G41.G4_TVertical;
	m_G4_HuecoH=Estructura_G41.G4_HuecoH;
	m_G4_HuecoV=Estructura_G41.G4_HuecoV;
	m_G4_CajasH=Estructura_G41.G4_CajasH;
	m_G4_CajasV=Estructura_G41.G4_CajasV;
	m_G4_CajasHH=Estructura_G41.G4_CajasHH;
	m_G4_CajasVV=Estructura_G41.G4_CajasVV;
	m_G4_PequeH=Estructura_G41.G4_PequeH;
	m_G4_PequeV=Estructura_G41.G4_PequeV;
	m_lista_GCuatros.push_back(Estructura_G41);
	m_lista_intG4.clear();
	m_lista_intG4.push_back(0);
//	printf("Iteracion %d Tama %d\n",m_iter_actual,m_lista_intG4.size());

}*/
void PALLET::Calcular_Estructura_G4(int vez)
{
	m_lista_GCuatros.clear();
	//Primero busco una estructura G4 que 
	int menor=200,menores=0;
	bool seguir=true;
	m_G4_TCajas=0;
	m_G4_THorizontal=0;
	m_G4_TVertical=0;
	m_G4_HuecoH=0;
	m_G4_HuecoV=0;
	m_G4_CajasH=0;
	m_G4_CajasHH=0;
	m_G4_CajasV=0;
	m_G4_CajasVV=0;
	m_G4_PequeH=0;
	m_G4_PequeV=0;

	int ph_V=0,ph_H=0,pv_V=0,pv_H=0;
	bool seguir1=true;
	bool seguir2=true;

	bool seguir3=true,seguir4=true;;
	double min=1000;
	//Busco estructuras que sean  eficientes, pero también puede darse el caso que una que 
	// no sea eficiente sea buena puesto que la perdida que genera sea pequeña este también lo meto 
	//siempre que la perdida sea más pequeña que la mitad posible
	//Piezas verticales en vertical
	for (pv_V=1;seguir4==true;pv_V++)
	{
		//Si poner más verticales no puede ser
		seguir1=true;
		seguir2=true;
		
		if (pv_V*m_l>=(m_W/2)) seguir4=false;
		//Piezas horizontales en vertical
		for (ph_V=1;seguir1==true;ph_V++)
		{
			if ((ph_V)*m_w>pv_V*m_l) seguir1=false;
			seguir2=true;
			//Piezas verticales en horizontal
			//voy probando
			for (pv_H=1;seguir2==true && (pv_H*m_w<(m_L/2)) ;pv_H++)
			{
				//Piezas horizontales en horizontal
				//Depende de las verticales en horizontal y de si es mayor
				//o menor 
				//Sie s mayor 
				seguir3=true;
				for (ph_H=1;seguir3==true && (ph_H*m_l<(m_L/2));ph_H++)
				{
					//Si el bloque de horizontales es más bajo
					// debe de ser más ancho
					if (ph_V==3 && pv_V==2 && pv_H==4 && ph_H==3)
						int kk=8;
					if (ph_V*m_w<pv_V*m_l)
					{
						if (ph_H*m_l>pv_H*m_w)
						{

							if ( (abs(((ph_V*m_w)-pv_V*m_l))<m_w || abs((pv_H*m_w)-ph_H*m_l)<m_w) )
							{
								int perx=ParticionPerfecta(m_L-(pv_H*m_w+ph_H*m_l));
								int pery=ParticionPerfecta(m_W-(pv_V*m_l+ph_V*m_w));

								//Me quedo con el que menor perdida tenga y que se parezca más al anterior.
//								if (((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))/(double)((ph_H*m_l+pv_H*m_w)*(pv_V*m_l+ph_V*m_w)))<=((m_L*m_W-((vez+1)*m_l*m_w))/2)	)
								if (((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))+(((ph_H*m_l+pv_H*m_w)*pery)+((pv_V*m_l+ph_V*m_w)*perx)))<=((m_L*m_W-((vez+1)*m_l*m_w))/2)	)
								{
									strg4 EstrucuturaG4_2;
									EstrucuturaG4_2.G4_THorizontal=(ph_H*m_l+pv_H*m_w);
									EstrucuturaG4_2.G4_TVertical=(pv_V*m_l+ph_V*m_w);
									EstrucuturaG4_2.G4_HuecoV=abs(((ph_V*m_w)-pv_V*m_l));
									EstrucuturaG4_2.G4_HuecoH=abs(((ph_H*m_l)-pv_H*m_w));
									EstrucuturaG4_2.G4_PequeV=ph_V*m_w;
									EstrucuturaG4_2.G4_PequeH=pv_H*m_w;
									EstrucuturaG4_2.G4_CajasH=ph_V;
									EstrucuturaG4_2.G4_CajasV=pv_H;
									EstrucuturaG4_2.G4_CajasVV=pv_V;
									EstrucuturaG4_2.G4_CajasHH=ph_H;
									EstrucuturaG4_2.G4_TCajas=((EstrucuturaG4_2.G4_CajasH*EstrucuturaG4_2.G4_CajasHH+EstrucuturaG4_2.G4_CajasV*EstrucuturaG4_2.G4_CajasVV)*2);
									if (((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))+(((ph_H*m_l+pv_H*m_w)*pery)+((pv_V*m_l+ph_V*m_w)*perx)))<min)
									{
										min=((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))+(((ph_H*m_l+pv_H*m_w)*pery)+((pv_V*m_l+ph_V*m_w)*perx)));
										m_G4_TCajas=EstrucuturaG4_2.G4_TCajas;
										m_G4_THorizontal=EstrucuturaG4_2.G4_THorizontal;
										m_G4_TVertical=EstrucuturaG4_2.G4_TVertical;
										m_G4_HuecoH=EstrucuturaG4_2.G4_HuecoH;
										m_G4_HuecoV=EstrucuturaG4_2.G4_HuecoV;
										m_G4_CajasH=EstrucuturaG4_2.G4_CajasH;
										m_G4_CajasV=EstrucuturaG4_2.G4_CajasV;
										m_G4_CajasHH=EstrucuturaG4_2.G4_CajasHH;
										m_G4_CajasVV=EstrucuturaG4_2.G4_CajasVV;
										m_G4_PequeH=EstrucuturaG4_2.G4_PequeH;
										m_G4_PequeV=EstrucuturaG4_2.G4_PequeV;

									}
									if (EstrucuturaG4_2.G4_CajasH==0)
										int kk=9;
									m_lista_GCuatros.push_back(EstrucuturaG4_2);
								}
							}
						}
					}
					else
					{
						if (ph_H*m_l<pv_H*m_w)
						{
							if ( (abs(((ph_V*m_w)-pv_V*m_l))<m_w || abs((pv_H*m_w)-ph_H*m_l)<m_w) )
							{
								int perx=ParticionPerfecta(m_L-(pv_H*m_w+ph_H*m_l));
								int pery=ParticionPerfecta(m_W-(pv_V*m_l+ph_V*m_w));

								//Me quedo con el que menor perdida tenga y que se parezca más al anterior.
//								if (((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))/(double)((ph_H*m_l+pv_H*m_w)*(pv_V*m_l+ph_V*m_w)))<=min)
								if (((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))+(((ph_H*m_l+pv_H*m_w)*pery)+((pv_V*m_l+ph_V*m_w)*perx)))<=((m_L*m_W-((vez+1)*m_l*m_w))/2)	)
								{
									strg4 EstrucuturaG4_2;

									EstrucuturaG4_2.G4_THorizontal=(ph_H*m_l+pv_H*m_w);
									EstrucuturaG4_2.G4_TVertical=(pv_V*m_l+ph_V*m_w);
									EstrucuturaG4_2.G4_HuecoV=abs(((ph_V*m_w)-pv_V*m_l));
									EstrucuturaG4_2.G4_HuecoH=abs(((ph_H*m_l)-pv_H*m_w));
									EstrucuturaG4_2.G4_PequeV=pv_V*m_l;
									EstrucuturaG4_2.G4_PequeH=ph_H*m_l;
									EstrucuturaG4_2.G4_CajasH=ph_V;
									EstrucuturaG4_2.G4_CajasV=pv_H;
									EstrucuturaG4_2.G4_CajasVV=pv_V;
									EstrucuturaG4_2.G4_CajasHH=ph_H;
									EstrucuturaG4_2.G4_TCajas=((EstrucuturaG4_2.G4_CajasH*EstrucuturaG4_2.G4_CajasHH+EstrucuturaG4_2.G4_CajasV*EstrucuturaG4_2.G4_CajasVV)*2);
									if (((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))+(((ph_H*m_l+pv_H*m_w)*pery)+((pv_V*m_l+ph_V*m_w)*perx)))<min)
									{
										min=((double)(abs(((ph_V*m_w)-pv_V*m_l))*abs((pv_H*m_w)-ph_H*m_l))+(((ph_H*m_l+pv_H*m_w)*pery)+((pv_V*m_l+ph_V*m_w)*perx)));
										m_G4_TCajas=EstrucuturaG4_2.G4_TCajas;
										m_G4_THorizontal=EstrucuturaG4_2.G4_THorizontal;
										m_G4_TVertical=EstrucuturaG4_2.G4_TVertical;
										m_G4_HuecoH=EstrucuturaG4_2.G4_HuecoH;
										m_G4_HuecoV=EstrucuturaG4_2.G4_HuecoV;
										m_G4_CajasH=EstrucuturaG4_2.G4_CajasH;
										m_G4_CajasV=EstrucuturaG4_2.G4_CajasV;
										m_G4_CajasHH=EstrucuturaG4_2.G4_CajasHH;
										m_G4_CajasVV=EstrucuturaG4_2.G4_CajasVV;
										m_G4_PequeH=EstrucuturaG4_2.G4_PequeH;
										m_G4_PequeV=EstrucuturaG4_2.G4_PequeV;

									}

									m_lista_GCuatros.push_back(EstrucuturaG4_2);

								}
							}
						}
					}
				}
			}
		}
	}
	printf("ListaG4 %d\n",m_lista_GCuatros.size());
	m_lista_intG4.clear();
	for (int kyi=0;kyi<m_lista_GCuatros.size();kyi++)
		m_lista_intG4.push_back(kyi);

//	m_lista_GCuatros.clear();
}
int PALLET::Cuantas_Cajas(std::list<BLOQUE> &lista,CRect &RectT)
{
	int Suma=0;
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
//		BLOQUE b1=(*itB);
		//Los que esten fuera del actual rectángulo
		if (((*itB).bottom<=RectT.top) || ((*itB).top>=RectT.bottom)
		|| ((*itB).right<=RectT.left) || ((*itB).left>=RectT.right))
			continue;
		//Esta dentro el bloque del rectángulo
		if( (*itB).top>=RectT.top && RectT.bottom>=(*itB).bottom && (*itB).left>=RectT.left && RectT.right>=(*itB).right )
		{
			Suma+=((*itB).Width()*(*itB).Height())/(m_l*m_w);
			continue;
		}
		//Esta dentro el rectangulo del bloque
		if( (*itB).top<=RectT.top && RectT.bottom<=(*itB).bottom && (*itB).left<=RectT.left && RectT.right<=(*itB).right )
		{
			Suma+=(RectT.Width()*RectT.Height())/(m_l*m_w);
			continue;
		}
		int Suma_I=Contar_Cajas_Interseccion((*itB),RectT);
		Suma+=Suma_I;
		continue;
		//Corta con el rectángulo pero no esta incluido totalmente
	}
	return Suma;
	/*
	int Suma=0;
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
7		BLOQUE b1=(*itB);
		//Los que esten incluidos dentro del nuevo rectángulo los sumo
		if ((((*itB).bottom<=RectT.bottom) && ((*itB).top>=RectT.top))
		&& (((*itB).right<=RectT.right) && ((*itB).left>=RectT.left)))
			continue;
		if( (*itB).top>=RectT.bottom || RectT.top>=(*itB).bottom )
		{
			Suma+=((*itB).Width()*(*itB).Height())/(m_l*m_w);
			continue;
		}
		if( (*itB).left>=RectT.right || RectT.left>=(*itB).right)
		{
			Suma+=((*itB).Width()*(*itB).Height())/(m_l*m_w);
			continue;
		}
		//Corta con el rectángulo pero no esta incluido totalmente
		int Suma_I=Contar_Cajas_Interseccion((*itB),RectT);
		Suma+=(((*itB).Width()*(*itB).Height())/(m_l*m_w))-Suma_I;
	}
	return Suma;*/
}
//Cuenta las caja que hay en la intersección
int PALLET::Contar_Cajas_Interseccion(BLOQUE &B1,CRect &Rect1)
{
	int l=m_w,w=m_l;
	//Tengo el rectangulo menor que corta los dos
	CRect RectTemp;
	IntersectRect(&RectTemp,&B1,&Rect1);
	if (RectTemp.IsRectEmpty())
	{
		return 0;
	}
	if (B1.GetTipo()=='H')
	{
		l=m_l;
		w=m_w;
	}
	//Tengo que tener un rectángulo mayor con dimensiones 
	//válidas para un bloque
	int num_cajas=(ceil((double)RectTemp.Width()/(double)l))*(ceil((double)RectTemp.Height()/(double)w));
//	int num_cajas=(RectTemp.Width()/l)*(RectTemp.Height()/w);
	return num_cajas;

}
void PALLET::Mejorar_Con_Bloques_G4(std::list<RECTAN> &lista_blo,std::list<CRect> &lista_per)
{
	//Esta funcion intenta colocar una estructura G4 desde la 
	//esquina inferior izquierda el problema es localizar cuantas 
	//piezas existen actualmente en la nueva región.

	//Posible estructura G4 encadenado dos formas a lo ancho
	bool seguir=true;
	bool colocado=false;
	bool G4_recursivo=false;
	std::list<strg4> ::iterator itg;
	std::vector<int>::iterator itg4int;
		for (itg4int=m_lista_intG4.begin();itg4int!=m_lista_intG4.end() && colocado!=true && G4_recursivo!=true;itg4int++)
		{
			m_G4_TCajas=m_lista_GCuatros[*itg4int].G4_TCajas;
			m_G4_THorizontal=m_lista_GCuatros[*itg4int].G4_THorizontal;
			m_G4_TVertical=m_lista_GCuatros[*itg4int].G4_TVertical;
			m_G4_HuecoH=m_lista_GCuatros[*itg4int].G4_HuecoH;
			m_G4_HuecoV=m_lista_GCuatros[*itg4int].G4_HuecoV;
			m_G4_CajasH=m_lista_GCuatros[*itg4int].G4_CajasH;
			m_G4_CajasV=m_lista_GCuatros[*itg4int].G4_CajasV;
			m_G4_CajasHH=m_lista_GCuatros[*itg4int].G4_CajasHH;
			m_G4_CajasVV=m_lista_GCuatros[*itg4int].G4_CajasVV;
			m_G4_PequeH=m_lista_GCuatros[*itg4int].G4_PequeH;

/*		for (itg=m_lista_GCuatros.begin();itg!=m_lista_GCuatros.end() && colocado!=true && G4_recursivo!=true ;itg++)
		{
//			strg4 kk=*itg;
			m_G4_TCajas=(*itg).G4_TCajas;
			m_G4_THorizontal=(*itg).G4_THorizontal;
			m_G4_TVertical=(*itg).G4_TVertical;
			m_G4_HuecoH=(*itg).G4_HuecoH;
			m_G4_HuecoV=(*itg).G4_HuecoV;
			m_G4_CajasH=(*itg).G4_CajasH;
			m_G4_CajasV=(*itg).G4_CajasV;
			m_G4_CajasHH=(*itg).G4_CajasHH;
			m_G4_CajasVV=(*itg).G4_CajasVV;
			m_G4_PequeH=(*itg).G4_PequeH;
			m_G4_PequeV=(*itg).G4_PequeV;
*/
	int largo=m_G4_CajasHH*m_l,ancho=m_G4_CajasH*m_w;
	if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
	{
		largo=m_w*m_G4_CajasV;
		ancho=m_G4_CajasVV*m_l;
	}

	int SolNow=Contar(lista_blo);
	//Más de uno a lo ancho
	//Primer nivel de recursión
	for (int register i=__min(((m_L-m_G4_THorizontal)/largo),((m_W-m_G4_TVertical)/(ancho)));i>=1 && seguir==true ;i--)
	{
		//Segundo cuantos en paralelo
		for(int register j=(m_L/(m_G4_THorizontal+(largo*i)));((j>=1) && (seguir==true));j--)
		{
		for(int register j2=(m_W/(m_G4_TVertical+(ancho*i)));((j2>=1) && (seguir==true));j2--)
		{
			for (int register k=1;k<=4  && seguir==true;k++)
			{
				BLOQUE Rect4;
				if (k==1) 
				{
					Rect4.left=0;
					Rect4.top=0;
					Rect4.right=(m_G4_THorizontal+(largo*i))*j;
					Rect4.bottom=(m_G4_TVertical+(i*ancho))*j2;
					Rect4.SetTipo('H');
				}
				if (k==2) 
				{
					Rect4.left=m_L-(m_G4_THorizontal+(largo*i))*j;
					Rect4.top=0;
					Rect4.right=m_L;
					Rect4.bottom=((m_G4_TVertical+(i*ancho))*j2);
					Rect4.SetTipo('H');
				}
				if (k==3) 
				{
					Rect4.top=m_W-((m_G4_TVertical+(i*ancho))*j2);
					Rect4.left=0;
					Rect4.bottom=m_W;
					Rect4.right=(m_G4_THorizontal+(largo*i))*j;
					Rect4.SetTipo('H');
				}
				if (k==4) 
				{
					Rect4.top=m_W-((m_G4_TVertical+(i*ancho))*j2);
					Rect4.left=m_L-(m_G4_THorizontal+(largo*i))*j;
					Rect4.bottom=m_W;
					Rect4.right=m_L;
					Rect4.SetTipo('H');
				}
				int kk=((((m_G4_THorizontal+(m_l*i))*(m_G4_THorizontal+(m_w*i*m_G4_CajasH)))-(i*m_G4_HuecoH*m_G4_HuecoH))/(m_l*m_w));
				int kk2=(m_L/m_G4_THorizontal)*((m_W/m_G4_THorizontal)*m_G4_CajasH*4);
				if ((j2*(i+1)*j*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
				{
				//Condición para que sea la mejor
				int Num=SolNow-Cuantas_Cajas(lista_blo,Rect4);
				if (Num+(((((m_G4_THorizontal+(largo*i))*(m_G4_TVertical+(i*ancho)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))*j*j2)>m_solbest)
				{
					MOVE movimiento(Rect4,Rect4,0);

					CRect PTotal(0,0,m_L,m_W);
					movimiento.GetListaPerdidas().clear();
					movimiento.GetListaPerdidas().push_back(PTotal);
					AumentarBloque(movimiento,1);
					ColocarG4(movimiento.GetListaPerdidas(),movimiento.GetListaBloques(),Rect4,'A',i,j,j2);
					movimiento.GetListaPerdidas().clear();
					movimiento.GetListaPerdidas().push_back(PTotal);
					Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
					Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
					if (Contar(movimiento.GetListaBloques())<m_Cota)
					{
						if (TodosTieneRasterPoint(movimiento.GetListaBloques())!=true)	
							return;			 
					}
					
//					std::list<BLOQUE> lista=Paletizar(movimiento.GetListaPerdidas(),'X');
//					movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());

//					if (Contar(movimiento.GetListaBloques())>m_solbest)
//					{
//						printf("Tipo 1");
						lista_blo=movimiento.GetListaBloques();
						lista_per=movimiento.GetListaPerdidas();
						colocado=true;
						seguir=false;
						G4_recursivo=true;
						return;
//					}
				}
				}
			}
		}
		}
	}
	//Posible estructura G4 encadenado dos formas a lo alto
	seguir=true;
	largo=m_G4_CajasVV*m_l,ancho=m_w*m_G4_CajasV;
	if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
	{
		largo=m_G4_CajasH*m_w;
		ancho=m_G4_CajasHH*m_l;
	}


	for (i=__min(((m_L-m_G4_THorizontal)/ancho),((m_W-m_G4_TVertical)/(largo)));i>=1 && seguir==true ;i--)
	{
		//para varios a lo ancho
		for(int register j=(m_L/(m_G4_THorizontal+(ancho*i)));((j>=1) && (seguir==true));j--)
		{
			//para varios a lo alto
			for(int register j2=(m_W/(m_G4_TVertical+(largo*i)));((j2>=1) && (seguir==true));j2--)
			{
			for (int register k=1;k<=4  && seguir==true;k++)
			{
				BLOQUE Rect4;
				if (k==1) 
				{
					Rect4.left=0;
					Rect4.top=0;
					Rect4.right=(m_G4_THorizontal+(ancho*i))*j;
					Rect4.bottom=(m_G4_TVertical+(i*largo))*j2;
					Rect4.SetTipo('H');
				}
				if (k==2) 
				{
					Rect4.left=m_L-(m_G4_THorizontal+(ancho*i))*j;
					Rect4.top=0;
					Rect4.right=m_L;
					Rect4.bottom=(m_G4_TVertical+(i*largo))*j2;
					Rect4.SetTipo('H');
				}
				if (k==3) 
				{
					Rect4.top=m_W-((m_G4_TVertical+(i*largo))*j2);
					Rect4.left=0;
					Rect4.bottom=m_W;
					Rect4.right=(m_G4_THorizontal+(ancho*i))*j;
					Rect4.SetTipo('H');
				}
				if (k==4) 
				{
					Rect4.top=m_W-((m_G4_TVertical+(i*largo))*j2);
					Rect4.left=m_L-(m_G4_THorizontal+(ancho*i))*j;
					Rect4.bottom=m_W;
					Rect4.right=m_L;
					Rect4.SetTipo('H');
				}
				if (((i+1)*j*m_G4_HuecoH*m_G4_HuecoV*j2)<=m_perdidaCota)
				{
				int Num=SolNow-Cuantas_Cajas(lista_blo,Rect4);
				//Condición para que sea la mejor
				if (Num+(((((m_G4_THorizontal+(ancho*i))*(m_G4_TVertical+(i*largo)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))*j*j2)>m_solbest)
				{
					MOVE movimiento(Rect4,Rect4,0);
					CRect PTotal(0,0,m_L,m_W);
					movimiento.GetListaPerdidas().clear();
					movimiento.GetListaPerdidas().push_back(PTotal);
					AumentarBloque(movimiento,1);
					ColocarG4(movimiento.GetListaPerdidas(),movimiento.GetListaBloques(),Rect4,'L',i,j,j2);
					movimiento.GetListaPerdidas().clear();
					movimiento.GetListaPerdidas().push_back(PTotal);
					Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
					Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
					if (Contar(movimiento.GetListaBloques())<m_Cota)
					{
						if (TodosTieneRasterPoint(movimiento.GetListaBloques())!=true)	
							return;			 
					}


//					std::list<BLOQUE> lista=Paletizar(movimiento.GetListaPerdidas(),'X');
//					movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());
//						printf("Tipo 2");
						lista_blo=movimiento.GetListaBloques();
						lista_per=movimiento.GetListaPerdidas();
						colocado=true;
						seguir=false;
						G4_recursivo=true;
						return;
				}
				}
			}
			}
		}
	}
	//g4 NORMALES
	seguir=true;
	for (int register j=(m_L/m_G4_THorizontal);j>=1 && seguir==true;j--)
	{
		for (int register i=(m_W/m_G4_TVertical);i>=1 && seguir==true;i--)
		{
//			if ((i*j*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
//			{
			if (i+j>=2)
			{
				for (int register k=1;k<=4  && seguir==true;k++)
				{

				BLOQUE Rect4;
				if (k==1) 
				{
					Rect4.left=0;
					Rect4.top=0;
					Rect4.right=(m_G4_THorizontal*j);
					Rect4.bottom=(m_G4_TVertical*i);
					Rect4.SetTipo('H');
				}
				if (k==2) 
				{
					Rect4.left=m_L-(m_G4_THorizontal*j);
					Rect4.top=0;
					Rect4.right=m_L;
					Rect4.bottom=(m_G4_TVertical*i);
					Rect4.SetTipo('H');
				}
				if (k==3) 
				{
					Rect4.top=m_W-(m_G4_TVertical*i);
					Rect4.left=0;
					Rect4.bottom=m_W;
					Rect4.right=(m_G4_THorizontal*j);
					Rect4.SetTipo('H');
				}
				if (k==4) 
				{
					Rect4.top=m_W-(m_G4_TVertical*i);
					Rect4.left=m_L-(m_G4_THorizontal*j);
					Rect4.bottom=m_W;
					Rect4.right=m_L;
					Rect4.SetTipo('H');
				}
				if (((i)*j*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
				{

				Rect4.SetTipo('H');
				int Num=SolNow-Cuantas_Cajas(lista_blo,Rect4);
				//Condición para que sea la mejor
				if ((Num+(i*j*m_G4_TCajas))>m_solbest)
				{
					MOVE movimiento(Rect4,Rect4,0);
					CRect PTotal(0,0,m_L,m_W);
					movimiento.GetListaPerdidas().clear();
					movimiento.GetListaPerdidas().push_back(PTotal);
					AumentarBloque(movimiento,1);
					ColocarG4(movimiento.GetListaPerdidas(),movimiento.GetListaBloques(),Rect4,'H',j,i,1);
					movimiento.GetListaPerdidas().clear();
					movimiento.GetListaPerdidas().push_back(PTotal);
					Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
					Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
					if (Contar(movimiento.GetListaBloques())<m_Cota)
					{
						if (TodosTieneRasterPoint(movimiento.GetListaBloques())!=true)
							return;			 
					}

//					std::list<BLOQUE> lista=Paletizar(movimiento.GetListaPerdidas(),'X');
//					movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());
//						printf("Tipo 3");
						lista_blo=movimiento.GetListaBloques();
						lista_per=movimiento.GetListaPerdidas();
						colocado=true;
						seguir=false;
						G4_recursivo=true;
						return;
				}
//				}
				}

			}
			}
		}
	}
	}
}
int PALLET::Grasp(bool dibu)
{
	m_Cota=OptimoTipoII();

	int max=0;
	int Valor_sol=0;
	for (int i=0;i<=10;i++)
	{
		//Inicializar Semilla de aleatorización
		srand(i);
	
		Valor_sol=BusquedaLocal(dibu);
		m_Dibujar=dibu;
		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_valor_maximo,i);

		printf("%d\n",Valor_sol);
		if (Valor_sol>max) max=Valor_sol;
		if (max==m_Cota) return max;
	}
	return max;

}
int PALLET::BusquedaLocal(bool dibu)
{
	m_max_rect=0;
	m_min_rect=99990;
	m_max_blo=0;
	m_min_blo=99990;
	m_Hmin=0;
	m_Hmax=10000;
	m_Vmin=0;
	m_Vmax=10000;
	m_iter_sin_mejorar=0;
	m_diversificaciones=0;
	m_todas=true;
	m_Eficientes=true;
	m_Raster=true;
	m_Intensificar=false;
	m_Simetria=true;
	m_Diversificar=false;
	m_iter_diversificar=0;
	m_utilizar_frecuencias=false;
	//Variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Calculamos los maximos de cajas de acuerdo a los raster
	CalcularMaximosCajas();	


	//Inicializamos variables para contar los posibles movimientos
	m_movimientos=0;
	m_movdismi=0;
	m_movaumen=0;
	m_hechomovdismi=0;
	m_hechomovaumen=0;
	std::list<BLOQUE> ::iterator itB;

	//Limpio la lista de bloques y de perdidas
	m_lista_bloques.clear();
	m_lista_perdidas.clear();
	//Tengo la solución inicial
	//Como se juntan los rectangulo
	m_tipo_junta=1;
	//Pesos de una solución sin nada nuevo
	NUEVO=70;
	//Lista tabu 2
	TABU2=0;
	//Peso para soluciones no cumplen simétria
	SIMETRIA=1000;
	//Peso que se le resta para soluciones con todos los bloques eficientes.
	EFICIENTES=1500;
	if (m_Eficientes!=true) 
	{
		EFICIENTES=0;
		PERDIDALADOS=0;
	}

	//Peso para el valor de cada caja de la solución
	VALOROPTIMO=2500;
	PERDIDALADOS=3000;
	//Peso negativo para soluciones con bloques que no puedan estar en una solu-
	//ción mejor que la actual
	OPTIMO=400;
	//Peso para el número de los bloques de la solución
	VALBLOQUES=0;
	//
	PERDIDAMAYOR=1000;
	//La cota la leemos de un archivo donde tenemos los optimos
//	m_Cota=0;
	if (m_Cota==0) m_Cota=(((m_L*m_W)/(m_l*m_w)));
	//Peso positivo si el bloque anterior no era eficiente
	CAMBIOTIPO=100;
	//lo controla la función porcentaje eficiente
	EFIBLOQUE=25;
	if (((double)(m_L*m_W)/(double)(m_l*m_w))-m_Cota<1) 
	{
		EFIBLOQUE=40;
//		PERDIDALADOS=4000;
	}
	//Para poner que la eficiencia de los bloques dependa
	//del número de particiones eficientes
//	EFIBLOQUE=(m_Eficientes_L.size()+m_Eficientes_W.size())*EFIBLOQUE;
//	EFICIENTES=(m_Eficientes_L.size()+m_Eficientes_W.size())*EFICIENTES;
//	EFIBLOQUE=(__min(m_hL,m_vL)+__min(m_hW,m_vW))*150;
//	EFICIENTES=0;
//	PERDIDAMAYOR=0;
//	PERDIDALADOS=0;
//	EFIBLOQUE=0;
//	EFICIENTES=0;
	//Peso para el rectangulo donde están incluidas las pérdidas
	m_F_Rectangulo=5000;
	//Tipo de rectangulo de menor perdidas
	m_tipo_rectangulo=5;
//	if (((double)(m_L*m_W)/(double)(m_l*m_w))-m_Cota<1) m_tipo_rectangulo=1;

	m_lpartidow=(m_l/m_w);
//	m_Cota=HeuristicoG4();
	//Tamaño de inicial de la lista
	m_tam_tabu=m_Cota*0.75;
	//Iteracion actual
	m_iter_actual=0;
	//MAximo valor de la iteraccion actual
	m_max_valor=0;
	//
	m_sol_actual=0;
	//
	m_valor_maximo=-500000;
	//Tamñao de la lista tabu de tipo perdidas
	m_tam_tabu_perdidas=100;
	std::list<CRect> :: iterator itL;
	//Mejor solucion
	m_solbest=0;
	//Calcular estructura g4 con uno es la principal
	//2 es la siguiente en importancia
	Calcular_Estructura_G4_Unica(1);
	//Si la perdida es menor que m_l solo queremos particiones
	//eficientes todo lo que no sea eficiente no lo queremos
/*	if (((m_L*m_W)-(m_Cota*m_l*m_w))<2*m_l)
		m_Eficientes=true;
		else m_Eficientes=false;*/
	//Perdida de una solucion de valor a la cota superior
	m_perdidaCota=((m_L*m_W)-(m_Cota*m_l*m_w));

	//Solucion inicial un bloque
	//elijo el que mas quepan
	AlgoritmoCuatroBloques(m_lista_bloques,m_lista_perdidas);
	m_sol_actual=Contar(m_lista_bloques);
	if (m_sol_actual>m_solbest) m_solbest=m_sol_actual;
	if (m_sol_actual>=m_Cota) return m_sol_actual;
	//Tamaño de la lista tabu2
	m_tam_tabu2=1;
	//Empiezo a recorrer bloques
	int dosm_max_valor=0;

	int mov_dismi=0;  
	int contador=0;
	std::vector<int> vec_recorrer,vec_temp,vec_recorrer2,vec_recorrer_bloques;
//	int valor=0;
	int tipo_movimiento=0;
	bool bloque_nulo;


	std::vector<int>::iterator itvec,itvec2,itvec3;
	for (register int kyi=1;kyi<=8;kyi++)
		vec_recorrer.push_back(kyi);
	for (kyi=1;kyi<=(m_L/m_w);kyi++)
		vec_recorrer2.push_back(kyi);
	long int max_candi_actual=0;
	long int max_candidatos=0;
	long int dosmax_candi_actual=0;
	long int dosmax_candidatos=0;
	int cuenta_bloques=0;
	m_iter_sin_mejorar=0;
	int max_candi_grasp=-10000;
	do 
	{
//		if (m_iter_actual>=1000 && m_iter_actual<=2000) EFIBLOQUE=0;
//		if (m_iter_actual>=2000 && m_iter_actual<=3000) m_F_Rectangulo=0;
/*		if (m_iter_actual>500 )
		{
			if (m_iter_actual%10==0)
			CAMBIOTIPO=get_random(50,400);
			else CAMBIOTIPO=0;
		}*/
		m_iter_actual++;
		bool movdismi=false, movaumen=false;
		if (m_iter_actual%100==0) Calcular_Estructura_G4_Unica(2);
		if (m_iter_actual%200==0) Calcular_Estructura_G4_Unica(1);
		//Genero vector aleatorio para el tipo de movimiento
		std::random_shuffle(vec_recorrer.begin(),vec_recorrer.end());
		//Genero vector aleatorio para el numero de filas que quito
		std::random_shuffle(vec_recorrer2.begin(),vec_recorrer2.end());
		//Genero vector aleatorio para recorrer los bloques
		Generar_Vector_Aleatorio(vec_temp,vec_recorrer_bloques,m_lista_bloques.size());
		//Tamaño de la lista tabu aleatorio

//		int vecpermayor=MayorPerdida();
		
		m_max_valor=-25;
		dosm_max_valor=-25;
		m_best_sol=m_solbest+1;
//		if (m_iter_actual>=50000) m_todas=false;
//		else (m_todas=true);
		int veces=0;
		m_no_hay=false;
		dosmax_candi_actual=-3000000;
		dosmax_candidatos=-3000000;
		max_candi_actual=-3000000;
		max_candidatos=-3000000;

		bool ninguna_perdida=true;
		int movimientos=0;
		//Defino movimientos
		MOVE BestMove,Movimiento,dosBestMove;
		//Variable que me indica si puedo quitar un bloque completamente
		bloque_nulo=true;

		//Creo el vector de número aleatorios
		//Por arriba o por abajo
		bool ya_tengo=false;
		for (itvec3=vec_recorrer_bloques.begin();itvec3!=vec_recorrer_bloques.end();itvec3++)
		{
		cuenta_bloques=0;
		ya_tengo=false;
		for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end() && ya_tengo!=true && m_solbest<m_Cota;itB++)
		{

			int kkkk=(*itvec3);
			cuenta_bloques++;
			if ((*itvec3)==cuenta_bloques)
			{
				ya_tengo=true;
				
			}
			else continue;
			if (BloqueCercaPerdidas((*itB),0)==0 ) continue;

			bloque_nulo=true;
			for (itvec=vec_recorrer.begin();itvec!=vec_recorrer.end() && m_solbest<m_Cota;itvec++)
			{
				m_gano=BloqueCercaPerdidas((*itB),(*itvec));

				if (m_gano==0) continue;

				for (itvec2=vec_recorrer2.begin();itvec2!=vec_recorrer2.end() && m_solbest<m_Cota;itvec2++)
				{
					int i=(*itvec2);
					tipo_movimiento=(*itvec);
					//Por Arriba o por abajo
					//Arriba
					if (tipo_movimiento==1)
					{
						if (PuedeDisminuirse((*itB),0,0,i,0,bloque_nulo)) 
						{
							Movimiento=(Disminuir_Bloques((*itB),0,0,i,0));
						}
						else continue;
					}
					//Abajo
					if (tipo_movimiento==2)
					{
						if (PuedeDisminuirse((*itB),0,0,0,i,bloque_nulo))
						{
							Movimiento=(Disminuir_Bloques((*itB),0,0,0,i));
						}
						else continue;
					}
					//Arriba
					if (tipo_movimiento==3)
					{
						if (PuedeAumentarse((*itB),0,0,i,0)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),0,0,i,0));
						}
						else continue;
					}
					//Abajo
					if (tipo_movimiento==4)
					{
						if (PuedeAumentarse((*itB),0,0,0,i)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),0,0,0,i));
						}
						else continue;
					}
					//Por derecha o izquierda
					//derecha
					if (tipo_movimiento==5)
					{
//						if (m_iter_actual==49) fprintf(fin,"%3d",tipo_movimiento);

						if (PuedeDisminuirse((*itB),i,0,0,0,bloque_nulo))
						{
							
							Movimiento=(Disminuir_Bloques((*itB),i,0,0,0));
						}
						else continue;
					}
					//izquierda
					if (tipo_movimiento==6)
					{
//						if (m_iter_actual==49) fprintf(fin,"%3d",tipo_movimiento);

						if (PuedeDisminuirse((*itB),0,i,0,0,bloque_nulo)) 
						{
							Movimiento=(Disminuir_Bloques((*itB),0,i,0,0));
						}
						else continue;
					}
					//derecha
					if (tipo_movimiento==7)
					{
						if (PuedeAumentarse((*itB),i,0,0,0)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),i,0,0,0));
						}
						else continue;
					}
					//izquierda
					if (tipo_movimiento==8)
					{
						if (PuedeAumentarse((*itB),0,i,0,0)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),0,i,0,0));
						}
						else continue;
					}

					m_movimientos++;
					if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
						m_movdismi++;
					else 
						m_movaumen++;
					ninguna_perdida=false;

					if (Movimiento.GetValor()<m_max_valor) continue;
					max_candidatos=EvaluarMovimiento(Movimiento);
					max_candidatos-=Movimiento.GetValor()*VALOROPTIMO;
					max_candidatos-=(EFIBLOQUE)*Porcentaje_Eficiente(Movimiento.GetBloqueAntiguo());

					max_candidatos=max_candidatos/1000;
//					printf("%d\n",max_candidatos);
					if ( (max_candidatos>=max_candi_actual) || (m_sol_actual+Movimiento.GetValor()>m_solbest))
					{

						if ((m_sol_actual+Movimiento.GetValor())>m_solbest)
						{
							m_solbest=(Movimiento.GetValor()+m_sol_actual);
							m_max_valor=Movimiento.GetValor();
							BestMove.Igual(Movimiento);
							max_candi_actual=max_candidatos;
							if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
							{
								movdismi=true;
								movaumen=false;
							}
							else 
							{
								movaumen=true;
								movdismi=false;
							}

//							EscribirBloquesPantalla(Movimiento.GetListaBloques());

						}
						else
						{
							if ( max_candidatos>max_candi_actual &&  ((m_sol_actual+Movimiento.GetValor())>=m_max_valor))
							{

								m_max_valor=Movimiento.GetValor();
								BestMove.Igual(Movimiento);
								max_candi_actual=max_candidatos;
//								printf("Valor %d\tVO %d\tSim %d\tL %d\tE %d\tR %d\tVM %d\tI %d\n",max_candi_actual,Valida_Optimo(m_lista_bloques),Valida_Simetria(m_lista_perdidas),PerdidaEnLados(m_lista_perdidas),Es_Eficiente(m_lista_bloques),Rectangulo_menor_estan_perdidas(m_lista_perdidas),m_valor_maximo,m_iter_actual);
								if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
								{
									movdismi=true;
									movaumen=false;
								}
								else 
								{
									movaumen=true;
									movdismi=false;
								}	

							}
						}
					}
					}
					
				if (tipo_movimiento==1 || tipo_movimiento==2 || tipo_movimiento==5 || tipo_movimiento==6) bloque_nulo=false;
			}
		}
		}
		

		m_sol_actual=m_sol_actual+BestMove.GetValor();

		if (m_sol_actual>m_solbest) m_solbest=m_sol_actual;
		VerificarSolucion(BestMove.GetBloquesNuevos(),BestMove.GetListaPerdidas(),1);
		Actualizar_Lista_Bloques(BestMove);
		m_lista_perdidas.clear();
		m_lista_perdidas.insert(m_lista_perdidas.begin(),BestMove.GetListaPerdidas().begin(),BestMove.GetListaPerdidas().end());
		m_sol_actual=Contar(m_lista_bloques);
		VerificarSolucion(m_lista_bloques,m_lista_perdidas,2);

		if (m_solbest!=m_Cota) 	Mejorar_Con_Bloques_G4(m_lista_bloques,m_lista_perdidas);
		VerificarSolucion(m_lista_bloques,m_lista_perdidas,3);
//		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_sol_actual,max_candi_actual);
		m_sol_actual=Contar(m_lista_bloques);
		if (m_sol_actual>m_solbest || max_candi_actual>=max_candi_grasp)
		{
			if (m_sol_actual>m_solbest) m_solbest=m_sol_actual;
			else
			{
				max_candi_grasp=max_candi_actual;
			}

		}
		else m_iter_sin_mejorar++;

//		EscribirBloques(m_lista_bloques);

//		DibujarBloques(contador,sol,perdida,m_solbest,true);
//		printf(" Final %d\n",m_iter_actual);
//		printf("%d\n",m_iter_actual);
	}while((m_iter_actual<m_max_iteracionesCadaGrasp) && (m_sol_actual!=m_Cota) && (m_sol_actual!=((m_L*m_W)/(m_l*m_w))) && (m_max_valor!=-25) && m_iter_sin_mejorar<11) ;
//	printf("%d\t%d\t%d\t%d\t",m_min_rect,m_max_rect,m_min_blo,m_max_blo);
	printf("\n%d\t%d\n",m_iter_actual,max_candi_grasp);
//	EscribirBloques(m_lista_bloques);
	return m_solbest;
}
//int PALLET::Tabu(int opt,int efi,int nue)
//int PALLET::Tabu(int opt,int efi,int nue)
int PALLET::Tabu(bool dibu)
{
//	printf("Iter %d",m_iter_actual);
	m_lista_GCuatros.clear();

	m_max_rect=0;
	m_min_rect=99990;
	m_max_blo=0;
	m_min_blo=99990;
	m_Hmin=0;
	m_Hmax=10000;
	m_Vmin=0;
	m_Vmax=10000;
	m_iter_sin_mejorar=0;
	m_diversificaciones=0;
	m_PathRelinking=false;
	m_fijos=false;
	m_todas=true;
	m_Eficientes=true;
	m_Raster=true;
	m_Intensificar=false;
	m_Simetria=true;
	m_Diversificar=false;
	m_iter_diversificar=0;
	m_utilizar_frecuencias=false;
	//Variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Abrimos el archivo donde se escriben las soluciones
	fin=fopen("soluciones.txt","a+");
	//Reservo espacio para la memoria de las frecuencias
	CrearMatrices();
	//Calculamos los maximos de cajas de acuerdo a los raster
	CalcularMaximosCajas();	


	//Inicializamos variables para contar los posibles movimientos
	m_movimientos=0;
	m_movdismi=0;
	m_movaumen=0;
	m_hechomovdismi=0;
	m_hechomovaumen=0;
	//Inicializar Semilla de aleatorización
	srand(1);
	std::list<BLOQUE> ::iterator itB;


	//Limpio la lista de bloques y de perdidas
	m_lista_bloques.clear();
	m_lista_perdidas.clear();
	//Tengo la solución inicial
	//Como se juntan los rectangulo
	m_tipo_junta=1;
	//Pesos de una solución sin nada nuevo
	NUEVO=70;
	//Lista tabu 2
	TABU2=0;
	//Peso para soluciones no cumplen simétria
	SIMETRIA=1000;
	//Peso que se le resta para soluciones con todos los bloques eficientes.
	EFICIENTES=1500;
//	EFICIENTES=0;
	if (m_Eficientes!=true) 
	{
		EFICIENTES=0;
		PERDIDALADOS=0;
	}

	//Peso para el valor de cada caja de la solución
	VALOROPTIMO=2500;
	PERDIDALADOS=3000;
	//Peso negativo para soluciones con bloques que no puedan estar en una solu-
	//ción mejor que la actual
	OPTIMO=400;
	//Peso para el número de los bloques de la solución
	VALBLOQUES=0;
	//
	PERDIDAMAYOR=1000;
	//La cota la leemos de un archivo donde tenemos los optimos
	
	m_Cota=OptimoTipoII();
	if (m_Cota==0) m_Cota=(((m_L*m_W)/(m_l*m_w)));

	//Peso positivo si el bloque anterior no era eficiente
	CAMBIOTIPO=100;
	//lo controla la función porcentaje eficiente
	EFIBLOQUE=25;
	if (((double)(m_L*m_W)/(double)(m_l*m_w))-m_Cota<1) 
	{
		EFIBLOQUE=40;
//		PERDIDALADOS=4000;
	}
//	EFIBLOQUE=0;
	//Para poner que la eficiencia de los bloques dependa
	//del número de particiones eficientes
//	EFIBLOQUE=(m_Eficientes_L.size()+m_Eficientes_W.size())*EFIBLOQUE;
//	EFICIENTES=(m_Eficientes_L.size()+m_Eficientes_W.size())*EFICIENTES;
//	EFIBLOQUE=(__min(m_hL,m_vL)+__min(m_hW,m_vW))*150;
//	EFICIENTES=0;
//	PERDIDAMAYOR=0;
//	PERDIDALADOS=0;
//	EFIBLOQUE=0;
//	EFICIENTES=0;
//	OPTIMO=0;

	//Peso para el rectangulo donde están incluidas las pérdidas
	m_F_Rectangulo=5000;
	//Tipo de rectangulo de menor perdidas
	m_tipo_rectangulo=5;
//	if (((double)(m_L*m_W)/(double)(m_l*m_w))-m_Cota<1) m_tipo_rectangulo=1;

	m_lpartidow=(m_l/m_w);
//	m_Cota=HeuristicoG4();
	//Tamaño de inicial de la lista
	m_tam_tabu=m_Cota*0.75;
	//Iteracion actual
	m_iter_actual=0;
	//MAximo valor de la iteraccion actual
	m_max_valor=0;
	//
	m_sol_actual=0;
	//
	m_valor_maximo=-500000;
	//Tamñao de la lista tabu de tipo perdidas
	m_tam_tabu_perdidas=100;
	std::list<CRect> :: iterator itL;
	//Mejor solucion
	m_solbest=0;
	//Calcular estructura g4 con uno es la principal
	//2 es la siguiente en importancia
	//Si la perdida es menor que m_l solo queremos particiones
	//eficientes todo lo que no sea eficiente no lo queremos
/*	if (((m_L*m_W)-(m_Cota*m_l*m_w))<2*m_l)
		m_Eficientes=true;
		else m_Eficientes=false;*/
//	m_F_Rectangulo=0;
	//Solucion inicial un bloque
	//elijo el que mas quepan
	AlgoritmoUnBloque(m_lista_bloques,m_lista_perdidas);
	m_sol_actual=Contar(m_lista_bloques);
	if (m_sol_actual>m_solbest) m_solbest=m_sol_actual;
	if (m_sol_actual>=m_Cota) return m_sol_actual;
	//Perdida de una solucion de valor a la cota superior
	m_perdidaCota=((m_L*m_W)-((m_solbest+1)*m_l*m_w));

	Calcular_Estructura_G4(m_solbest);
//	Calcular_Estructura_G4_Unica(1);
	//Tamaño de la lista tabu2
	m_tam_tabu2=1;
	//Empiezo a recorrer bloques
	int dosm_max_valor=0;
	int cambiar=500;

	int mov_dismi=0;  
	int contador=0;
	std::vector<int> vec_recorrer,vec_temp,vec_recorrer2,vec_recorrer_bloques;
//	int valor=0;
	int tipo_movimiento=0;
	bool bloque_nulo;

	std::vector<int>::iterator itvec,itvec2,itvec3;
	for (register int kyi=1;kyi<=8;kyi++)
		vec_recorrer.push_back(kyi);
	for (kyi=1;kyi<=(m_L/m_w);kyi++)
		vec_recorrer2.push_back(kyi);
	long int max_candi_actual=0;
	long int max_candidatos=0;
	m_valor_maximo=-500000;
	long int dosmax_candi_actual=0;
	long int dosmax_candidatos=0;
	int cuenta_bloques=0;

	do 
	{
		m_perdidaCota=((m_L*m_W)-((m_solbest+1)*m_l*m_w));

//		if (m_iter_actual>=1000 && m_iter_actual<=2000) EFIBLOQUE=0;
//		if (m_iter_actual>=2000 && m_iter_actual<=3000) m_F_Rectangulo=0;
/*		if (m_iter_actual>500 )
		{
			if (m_iter_actual%10==0)
			CAMBIOTIPO=get_random(50,400);
			else CAMBIOTIPO=0;
		}*/
		m_iter_actual++;
		//Perdida de una solucion de valor a la cota superior
/*		m_perdidaCota=((m_L*m_W)-((m_solbest+1)*m_l*m_w));
		if (m_perdidaCota!=0) 
		{
			EFIBLOQUE=((double)(m_l*m_w)/(double)(m_perdidaCota))*50;
			EFICIENTES=((double)(m_l*m_w)/(double)(m_perdidaCota))*250;
		}*/
		if (m_iter_actual==10) Calcular_Estructura_G4(m_solbest);
/*		if (m_iter_actual==100) Calcular_Estructura_G4(m_solbest);

		if (m_iter_actual==10000) //ponia 5000
		{
			m_lista_GCuatros.clear();
			m_G4_THorizontal=100000;
			m_G4_TVertical=100000;
		}
	*/
//		printf("Iter %d",m_iter_actual);
//		if (m_iter_actual%10000==0) tope=get_random(2,9);
		bool movdismi=false, movaumen=false;

		if (m_iter_actual%100==0) Calcular_Estructura_G4_Unica(2);
		if (m_iter_actual%200==0) Calcular_Estructura_G4_Unica(1);

	  //Genero vector aleatorio para el tipo de movimiento
		std::random_shuffle(vec_recorrer.begin(),vec_recorrer.end());
		std::random_shuffle(m_lista_intG4.begin(),m_lista_intG4.end());
		//Genero vector aleatorio para el numero de filas que quito
		std::random_shuffle(vec_recorrer2.begin(),vec_recorrer2.end());
		//Genero vector aleatorio para recorrer los bloques
		Generar_Vector_Aleatorio(vec_temp,vec_recorrer_bloques,m_lista_bloques.size());
		//Tamaño de la lista tabu aleatorio
		//Cambiar por m_iter_actual
		if (m_iter_actual%100==0)
		{
			m_tam_tabu=get_random((int)(0.5*(((m_L*m_W)/(m_l*m_w)))),(int)(1.5*(((m_L*m_W)/(m_l*m_w)))));	
			if (m_lista_tabu.size()>m_tam_tabu)
			{
				int kk=m_lista_tabu.size();
				for (register int ki=1;ki<=(kk-m_tam_tabu);ki++)
					m_lista_tabu.pop_front();
			}
		}
//		int vecpermayor=MayorPerdida();
		
		m_max_valor=-25;
		dosm_max_valor=-25;
		m_best_sol=m_solbest+1;
//		if (m_iter_actual>=50000) m_todas=false;
//		else (m_todas=true);
		int veces=0;
		//Etiqueta donde vuelvo si no tengo ninguna solucion buena
		again:;
		m_no_hay=false;
		max_candi_actual=-3000000;
		max_candidatos=-3000000;
		dosmax_candi_actual=-3000000;
		dosmax_candidatos=-3000000;
		bool ninguna_perdida=true;
		int movimientos=0;
		//Defino movimientos
		MOVE BestMove,Movimiento,dosBestMove;
		//Variable que me indica si puedo quitar un bloque completamente
		bloque_nulo=true;

		//Creo el vector de número aleatorios
		//Por arriba o por abajo
		bool ya_tengo=false;
		for (itvec3=vec_recorrer_bloques.begin();itvec3!=vec_recorrer_bloques.end() && m_solbest<m_Cota;itvec3++)
		{
		cuenta_bloques=0;
		ya_tengo=false;
		for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end() && ya_tengo!=true && m_solbest<m_Cota;itB++)
		{

			int kkkk=(*itvec3);
			cuenta_bloques++;
			if ((*itvec3)==cuenta_bloques)
			{
				ya_tengo=true;
				
			}
			else continue;
			if (BloqueCercaPerdidas((*itB),0)==0 ) continue;

			bloque_nulo=true;
			for (itvec=vec_recorrer.begin();itvec!=vec_recorrer.end() && m_solbest<m_Cota;itvec++)
			{
				m_gano=BloqueCercaPerdidas((*itB),(*itvec));

				if (m_gano==0) continue;

				for (itvec2=vec_recorrer2.begin();itvec2!=vec_recorrer2.end() && m_solbest<m_Cota;itvec2++)
				{
					int i=(*itvec2);
					tipo_movimiento=(*itvec);
					//Por Arriba o por abajo
					//Arriba
					if (tipo_movimiento==1)
					{
						if (PuedeDisminuirse((*itB),0,0,i,0,bloque_nulo)) 
						{
							Movimiento=(Disminuir_Bloques((*itB),0,0,i,0));
						}
						else continue;
					}
					//Abajo
					if (tipo_movimiento==2)
					{
						if (PuedeDisminuirse((*itB),0,0,0,i,bloque_nulo))
						{
							Movimiento=(Disminuir_Bloques((*itB),0,0,0,i));
						}
						else continue;
					}
					//Arriba
					if (tipo_movimiento==3)
					{
						if (PuedeAumentarse((*itB),0,0,i,0)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),0,0,i,0));
						}
						else continue;
					}
					//Abajo
					if (tipo_movimiento==4)
					{
						if (PuedeAumentarse((*itB),0,0,0,i)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),0,0,0,i));
						}
						else continue;
					}
					//Por derecha o izquierda
					//derecha
					if (tipo_movimiento==5)
					{
//						if (m_iter_actual==49) fprintf(fin,"%3d",tipo_movimiento);

						if (PuedeDisminuirse((*itB),i,0,0,0,bloque_nulo))
						{
							
							Movimiento=(Disminuir_Bloques((*itB),i,0,0,0));
						}
						else continue;
					}
					//izquierda
					if (tipo_movimiento==6)
					{
//						if (m_iter_actual==49) fprintf(fin,"%3d",tipo_movimiento);

						if (PuedeDisminuirse((*itB),0,i,0,0,bloque_nulo)) 
						{
							Movimiento=(Disminuir_Bloques((*itB),0,i,0,0));
						}
						else continue;
					}
					//derecha
					if (tipo_movimiento==7)
					{
						if (PuedeAumentarse((*itB),i,0,0,0)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),i,0,0,0));
						}
						else continue;
					}
					//izquierda
					if (tipo_movimiento==8)
					{
						if (PuedeAumentarse((*itB),0,i,0,0)) 
						{
							Movimiento=(Aumentar_Bloques((*itB),0,i,0,0));
						}
						else continue;
					}
					//Ulima modificación aumento un G4
/*					if (tipo_movimiento==9)
					{
						if (PuedeAumentarseG4((*itB),i)) 
						{
							Movimiento=(Aumentar_BloquesG4((*itB),i));
						}
						else continue;
					}
*/					m_movimientos++;
					if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
						m_movdismi++;
					else 
						m_movaumen++;
					ninguna_perdida=false;

				if (Movimiento.GetValor()<m_max_valor) continue;
//					if (Movimiento.GetValor()<-20) continue;
//					movimientos++;

//						fprintf(fin,"%3d\t%3d\t%3d\t%3d\t%c\n",Movimiento.GetBloqueAntiguo().top,Movimiento.GetBloqueAntiguo().bottom,Movimiento.GetBloqueAntiguo().left,Movimiento.GetBloqueAntiguo().right,Movimiento.GetBloqueAntiguo().GetTipo());
//						fprintf(fin,"%3d\t%3d\t%3d\t%3d\t%c\n",Movimiento.GetBloqueNuevo().top,Movimiento.GetBloqueNuevo().bottom,Movimiento.GetBloqueNuevo().left,Movimiento.GetBloqueNuevo().right,Movimiento.GetBloqueNuevo().GetTipo());
//						fprintf(fin,"%3d\t%3d\t%3d\n",m_iter_actual,Movimiento.GetValor(),m_max_valor);
					//Criterio de aspiración 
//					if ( (!EsTabu(Movimiento.GetListaBloques()) && Valida_Simetria(Movimiento.GetListaPerdidas()) && Movimiento.GetValor()>=m_max_valor ) || ((Movimiento.GetValor()+sol)>m_solbest))
					if ( (Movimiento.GetValor()>=m_max_valor && EsTabu2(Movimiento.GetBloqueAntiguo())==false && TodosTieneRasterPoint(Movimiento.GetListaBloques())==true && !EsTabu(Movimiento.GetListaBloques()) && !EsTabuPerdidas(Movimiento.GetListaPerdidas()) ) || (m_sol_actual+Movimiento.GetValor()>m_solbest))
					{
//					if ( ( (TodosTieneRasterPoint(Movimiento.GetListaBloques())==true)  && (!EsTabu(Movimiento.GetListaBloques()))) || (m_sol_actual+Movimiento.GetValor()>m_solbest))
//					{
						max_candidatos=EvaluarMovimiento(Movimiento);
//						fprintf(fin,"%3d\n",max_candidatos);
						if ((m_sol_actual+Movimiento.GetValor())>m_solbest)
						{
							m_solbest=(Movimiento.GetValor()+m_sol_actual);
//							if (m_solbest+1==m_Cota) CotaNelisenMaxMin(m_Cota);
							m_max_valor=Movimiento.GetValor();
							BestMove.Igual(Movimiento);
							max_candi_actual=max_candidatos;
							if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
							{
								movdismi=true;
								movaumen=false;
							}
							else 
							{
								movaumen=true;
//								printf("Este es bueno");
								movdismi=false;
							}

//									EscribirBloquesPantalla(Movimiento.GetListaBloques());

						}

						else
						{
							if ( (max_candidatos>max_candi_actual) )
							{
								m_max_valor=Movimiento.GetValor();
								BestMove.Igual(Movimiento);
								max_candi_actual=max_candidatos;
								if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
								{
									movdismi=true;
									movaumen=false;
								}
								else 
								{
									movaumen=true;
									movdismi=false;
								}	
							}
						}
					}
					if ( m_max_valor==-25 && Movimiento.GetValor()>=dosm_max_valor && !EsTabuSinLaUltima(Movimiento.GetListaBloques()))
					{
						dosmax_candidatos=EvaluarMovimiento(Movimiento);
						if (dosmax_candidatos>dosmax_candi_actual )
						{
							dosm_max_valor=Movimiento.GetValor();
							dosBestMove.Igual(Movimiento);
							dosmax_candi_actual=dosmax_candidatos;
							if (tipo_movimiento<=2 || tipo_movimiento==5 || tipo_movimiento==6) 
							{
								movdismi=true;
								movaumen=false;
							}
							else 
							{
								movaumen=true;
								movdismi=false;
							}
						}
					}

				}
					
				if (tipo_movimiento==1 || tipo_movimiento==2 || tipo_movimiento==5 || tipo_movimiento==6) bloque_nulo=false;
			}
		}
		}
		if (ninguna_perdida==true && m_todas!=true) 
		{
			m_todas=true;
			goto again;
		}
		else 
			m_todas=false;
		if (movdismi==true) m_hechomovdismi++;
		if (movaumen==true) m_hechomovaumen++;
//		printf("Tamaño de la lista tabu %d\n",m_lista_tabu.size());
		if (m_lista_tabu.size()>0 && m_max_valor==-25 && dosm_max_valor==-25) 
		{
			if (m_lista_tabu.size()>1)		
			{
				m_lista_tabu.pop_front();
				m_lista_tabu.pop_front();
//				mirar_no_tabu_en_la_ultima=true;
			}
			if (m_lista_tabu.size()==1)
			{
				m_lista_tabu.pop_front();
//				mirar_no_tabu_en_la_ultima=true;
			}
//			printf("No encuentra en ninguna\n");

			goto again;
		}
		if (m_max_valor==-25 && dosm_max_valor!=-25)
		{	
			if (m_lista_tabu.size()>0)		
			{
				m_lista_tabu.pop_front();
			}
			BestMove.Igual(dosBestMove);
			m_max_valor=dosm_max_valor;
//			printf("Encuentra en la penultima, pero no en la ultima %d\n",m_iter_actual);

		}
//		if (m_iter_actual==1000) CotaNelisenMaxMin(m_solbest+1);
			
		if (m_sol_actual>m_solbest) m_solbest=m_sol_actual;
		VerificarSolucion(BestMove.GetBloquesNuevos(),BestMove.GetListaPerdidas(),1);
		if (m_iter_actual>30) 
			int ppero=9;
//		printf("%3d",sol);
		//Meto en la lista Tabu2 los que son nuevos que no los quiero mover
		//durante un número de iteraciones
		Add_Lista_Tabu2(m_lista_bloques,BestMove.GetBloquesNuevos());
		Add_Lista_TabuPerdidas(BestMove.GetListaPerdidas());
		Add_Lista_Tabu(BestMove.GetBloqueAntiguo());
		int Contar_H=ContarH(m_lista_bloques);
		Actualizar_Lista_Bloques(BestMove);
		//Actualiza la matriz de frecuencias solo si es una solución de las que definimos
		// como elite son soluciones cque cumplen simetria y cumplen optimo
		//Si quito esto funciona el 86 52 9 5
//		if (Valida_Simetria(m_lista_perdidas)==true && Valida_Optimo(m_lista_bloques) && m_sol_actual>=m_solbest)		
			ActualizarMatrices();
		//Actualizo la lista de perdidas
		int Contar_Nuevas_H=ContarH(BestMove.GetListaBloques());

		m_lista_perdidas.clear();
		m_lista_perdidas.insert(m_lista_perdidas.begin(),BestMove.GetListaPerdidas().begin(),BestMove.GetListaPerdidas().end());
		m_sol_actual=Contar(m_lista_bloques);
		VerificarSolucion(m_lista_bloques,m_lista_perdidas,2);
		bool b1=false,b2=false,b3=false,b4=false;
//		m_sol_actual=m_sol_actual+BestMove.GetValor();
/*		for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
		{
//			if ((*itB).top==0 && (*itB).left==0 && (*itB).bottom==8 && (*itB).right==33 && (*itB).GetTipo()=='H')
				b1=true;
//			if ((*itB).top==11 && (*itB).left==32 && (*itB).bottom==19 && (*itB).right==65 && (*itB).GetTipo()=='H')
				b2=true;
			if ((*itB).top==11 && (*itB).left==0 && (*itB).bottom==75 && (*itB).right==33 && (*itB).GetTipo()=='H')
				b3=true;
//			if ((*itB).top==78 && (*itB).left==48 && (*itB).bottom==86 && (*itB).right==103 && (*itB).GetTipo()=='H')
				b4=true;
		}
		if (b1==true && b2==true && b3==true && b4==true)
			for (int il=0;;il++) printf("Parecido");
*/		if (m_solbest!=m_Cota) 	Mejorar_Con_Bloques_G4(m_lista_bloques,m_lista_perdidas);
		VerificarSolucion(m_lista_bloques,m_lista_perdidas,3);
		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_sol_actual,max_candi_actual);
		m_sol_actual=Contar(m_lista_bloques);
		if (m_sol_actual>=m_solbest)
		{
			m_solbest=m_sol_actual;
//			if (m_iter_actual>250 && m_iter_actual%5==0) div_bloq=abs(Contar_Nuevas_H-Contar_H)*CAMBIOTIPO;
//			if (BloquesGrandes(BestMove.GetListaBloques())==true)
//				max_candidatos+=10000;

			if ((((max_candi_actual-((EFIBLOQUE)*Porcentaje_Eficiente(BestMove.GetBloqueAntiguo())))>=(m_valor_maximo2)) && m_Diversificar==false) || (m_sol_actual>m_solbest) || (m_sol_actual==m_Cota))
			{
				m_valor_maximo2=max_candi_actual-((EFIBLOQUE)*Porcentaje_Eficiente(BestMove.GetBloqueAntiguo()));
				m_iter_sin_mejorar=0;
			}
			else m_iter_sin_mejorar++;
		}
		else m_iter_sin_mejorar++;
//		int cambiar=50000;
		for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
		{
			(*itB).SetNumero(0);
			(*itB).SetPuedoMover(true);
		}

		if (m_iter_actual==(500*cambiar)) 
		{
			m_diversificaciones=0;
			cambiar=500;
		}
//		printf("%d\n",m_sol_actual);
		//Chapuza para que me queden poquitos
// No se porque no funsiona
/*		if (m_iter_actual==10)
		{
			printf(" empiezo de nuevo");
				m_lista_bloques.clear();
				m_lista_perdidas.clear();
				AlgoritmoUnBloque(m_lista_bloques,m_lista_perdidas);
				m_lista_tabu.clear();
				m_sol_actual=Contar(m_lista_bloques);
				m_solbest=m_sol_actual;
//				m_tam_tabu=m_Cota*0.75;
				srand(1);
		}
*/
//		printf("%d\n",m_sol_actual);

		if ((m_iter_actual>=150000) && (m_iter_actual%5000==0))
		{
			OscilacionEstrategica();
			if ((m_iter_actual%10000==0))
			{
				m_lista_bloques.clear();
				m_lista_perdidas.clear();
				AlgoritmoUnBloque(m_lista_bloques,m_lista_perdidas);
				m_lista_tabu.clear();
				m_sol_actual=Contar(m_lista_bloques);
				//Tamaño de inicial de la lista
				srand(1);
			}
			m_iter_sin_mejorar=0;
			m_valor_maximo2=-500000;

		}
/*		if (m_Diversificar==true) 
		{
			m_iter_diversificar++;
			int valor_maximo=max_candi_actual-(m_max_valor*VALOROPTIMO)-((EFIBLOQUE)*Porcentaje_Eficiente(BestMove.GetBloqueAntiguo()));

			int div_bloq=0;

			printf("Divers Optimo %d\tSim %d\tL %d\tE %d\tDB %d\tR %d\tVI %d\tVM %d\tI %d\n",Valida_Optimo(m_lista_bloques),Valida_Simetria(m_lista_perdidas),PerdidaEnLados(m_lista_perdidas),Es_Eficiente(m_lista_bloques),div_bloq,Rectangulo_menor_estan_perdidas(m_lista_perdidas),valor_maximo,m_valor_maximo,m_iter_actual);
		}

*/
//		if (m_iter_diversificar==30) m_Diversificar=false;
		if (m_PathRelinking==true)
		{

			if (((m_sol_actual>=m_solbest) && (Valida_Simetria(m_lista_perdidas)==true) && (Valida_Optimo(m_lista_bloques)==true))|| (m_sol_actual>m_solbest))
			{
				m_valor_maximo=max_candi_actual-(m_max_valor*VALOROPTIMO)-((EFIBLOQUE/10)*Porcentaje_Eficiente(BestMove.GetBloqueAntiguo()));
				if (Es_Eficiente(BestMove.GetListaBloques())==true ) m_valor_maximo-=EFICIENTES;
				if (Movimiento.GetAlgoNuevo()==true) m_valor_maximo-=NUEVO;
				if (m_utilizar_frecuencias==true) m_valor_maximo=VecesQueHaAparecidoElBloque(BestMove.GetBloqueAntiguo())*20;
				ActualizarConjuntoReferencia(BestMove,m_valor_maximo);
			}
//			else printf("%d\t%d\t%d\n",m_sol_actual,Valida_Simetria(m_lista_perdidas),Valida_Optimo(m_lista_bloques));
			if (m_iter_actual%4999==0)
			{
				std::list<pathre>::iterator itB;
				printf("Tama %d",m_conjunto_ref.size());
				for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end();itB++)
				{
					DibujarSolucion((*itB).lista_bloques,(*itB).lista_perdidas,(*itB).fobjetivo,777);
				}
				int solcomb=CombinarSolucionesConjuntoRef();
				if (solcomb>m_solbest) 
					return solcomb;
				m_conjunto_ref.clear();
			}
		}
//		if (m_iter_actual==10000) m_utilizar_frecuencias=true;
//		if (m_iter_actual==10000) MostrarFrecuencias();
//		fprintf(fin,"%3d\n",m_iter_actual);
//		fprintf(fin,"%3d\t%3d\t%3d\t%3d\n",BestMove.GetBloqueAntiguo().top,BestMove.GetBloqueAntiguo().bottom,BestMove.GetBloqueAntiguo().right,BestMove.GetBloqueAntiguo().left);
//		fprintf(fin,"%3d\t%3d\t%3d\t%3d\n",BestMove.GetBloqueNuevo().top,BestMove.GetBloqueNuevo().bottom,BestMove.GetBloqueNuevo().right,BestMove.GetBloqueNuevo().left);

//		EscribirBloques(m_lista_bloques);

//		DibujarBloques(contador,sol,perdida,m_solbest,true);
//		printf(" Final %d\n",m_iter_actual);
//		printf("%d\n",m_iter_actual);
		if (m_iter_actual%10000==0) printf("Iteracion %d",m_iter_actual);
	}while((m_iter_actual<m_max_iteraciones) && (m_sol_actual!=m_Cota) && (m_sol_actual!=((m_L*m_W)/(m_l*m_w))) && (m_max_valor!=-25));
//	std::set<int> ::iterator its;
//	for(its=conjunto_kk.begin();its!=conjunto_kk.end();its++)
//		fprintf(fin,"%d\n",(*its));

	fclose(fin);
//	printf("%d\t%d\t%d\t%d\t",m_min_rect,m_max_rect,m_min_blo,m_max_blo);
	printf("\n%d",m_iter_actual);
	return m_solbest;
}
bool PALLET::ComprobarBloquesNoIntersectan(std::list<BLOQUE> &lista)
{
	std::list<BLOQUE>::iterator itB1,itB2,itB3;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		itB2=itB1;
		itB2++;
		if (itB2==lista.end()) break;
		for(itB3=itB2;itB3!=lista.end();itB3++)
		{
//			BLOQUE b1=(*itB1);
//			BLOQUE b2=(*itB2);
			if( (*itB1).top>=(*itB3).bottom || (*itB3).top>=(*itB1).bottom )
				continue;
			if( (*itB1).left>=(*itB3).right || (*itB3).left>=(*itB1).right)
				continue;	
			return true;

		}
	}
	return false;
}
bool PALLET::ComprobarBloquesYPerNoIntersectan(std::list<BLOQUE> &lista,std::list<CRect> &lista2)
{
	std::list<BLOQUE>::iterator itB1;
	std::list< CRect >::iterator itB3;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		for(itB3=lista2.begin();itB3!=lista2.end();itB3++)
		{
//			BLOQUE b1=(*itB1);
//			BLOQUE b2=(*itB2);
			if( (*itB1).top>=(*itB3).bottom || (*itB3).top>=(*itB1).bottom )
				continue;
			if( (*itB1).left>=(*itB3).right || (*itB3).left>=(*itB1).right)
				continue;	
			return true;

		}
	}
	return false;
}
int PALLET::Contar(std::list<BLOQUE> &listaT)
{
	int Val=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=listaT.begin();itB!=listaT.end();itB++)
	{
		Val+=((*itB).Height()*(*itB).Width())/(m_l*m_w);
	}
//	printf("%3d\n",Val);
	return Val;
}
int PALLET::ContarH(std::list<BLOQUE> &listaT)
{
	int Val=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=listaT.begin();itB!=listaT.end();itB++)
	{
		if ((*itB).GetTipo()=='H') 
			Val+=((*itB).Height()*(*itB).Width())/(m_l*m_w);
	}
	return Val;
}
int PALLET::Contar(std::list<CRect> &lista)
{
	int Val=0;
	std::list<CRect>::iterator itB;
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		Val+=((*itB).Height()*(*itB).Width());
	}
	return Val;
}
std::list<CRect> PALLET::JuntarPerdida(std::list<CRect> &Nuevas,char tipo)
{
	tope=get_random(3,__max(3,15));

	std::list<CRect> Nuevas_Juntadas=Nuevas;
	if (Nuevas.size()==0) return Nuevas;

	int contador=0;
	std::list<CRect> nueva_lista,aux;
	std::list<CRect>::iterator itL1,itL2,itL3,itL4;
	bool mas=false,juntar2=false;
	do
	{
		juntar2=false;
		bool otro=false;
		contador++;

		mas=false;
		for(itL1=Nuevas_Juntadas.begin();itL1!=Nuevas_Juntadas.end() && juntar2!=true;itL1++)
		{
//			CRect rect1=(*itL1);
			juntar2=false;

			itL3=itL1;
			itL3++;
			if (itL3==Nuevas.end())
			{
				break;
			}

			for (itL2=itL3;itL2!=Nuevas_Juntadas.end() && juntar2!=true;itL2++)
			{
//				CRect rect2=(*itL2);
				otro=false;
				if (otro==true) continue;

				CRect Nuevo1(0,0,0,0),Nuevo2(0,0,0,0),Nuevo3(0,0,0,0),RectTemp(0,0,0,0);

				if (((*itL2).Width()<m_w) && ((*itL2).Height()<m_w)) continue;
				//Si no se tocan ni en horizontal ni en vertical  teniendo parte en común continue
				if (!((*itL1).right==(*itL2).left) && !((*itL1).left==(*itL2).right)
					&& !((*itL1).top==(*itL2).bottom) && !((*itL1).bottom==(*itL2).top)) continue;
				// si se compacta
				//Si coinciden en horizontal
				//voy a saber que una debajo de otra;
				juntar2=JuntarDosRectangulos(Nuevo1,Nuevo2,Nuevo3,(*itL1),(*itL2),tipo);
				if (juntar2==true)
				{
					if (!Nuevo1.IsRectEmpty()) Nuevas_Juntadas.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) Nuevas_Juntadas.push_back(Nuevo2);
					if (!Nuevo3.IsRectEmpty()) Nuevas_Juntadas.push_back(Nuevo3);
					itL2=Nuevas_Juntadas.erase(itL2);
					itL1=Nuevas_Juntadas.erase(itL1);
				}
			}
		}
	}while (juntar2==true && contador<tope);
	return Nuevas_Juntadas;	
	
}
void PALLET::JuntarPerdida(std::list<CRect> &lista)
{
	tope=get_random(3,__max(3,15));
	if (lista.size()==0) return ;
	bool juntar=false;
	bool seguir=false;
	std::list<CRect> ::iterator itL1,itL2,itL3;
	std::list<CRect> nueva_lista;
	CRect Nuevo1,Nuevo2,Nuevo3,RectTemp;
	int cuenta=0;
	do
	{

		cuenta++;
		seguir=false;
		nueva_lista.clear();
		itL1=lista.begin();
		do{
			juntar=false;
//			CRect rect1=(*itL1);
			itL3=itL1;
			itL3++;
			if (itL3==lista.end()) break;
//			if (((*itL1).Width()<m_w) && ((*itL1).Height()<m_w)) continue;
			itL2=itL1;
			do
			{
//				CRect rect2=(*itL2);
				juntar=false;
				if (((*itL1).BottomRight()==(*itL2).BottomRight()) &&
				((*itL1).TopLeft()==(*itL2).TopLeft()) )
				{
					itL2++;
					continue;
				}

	
//				if (((*itL2).Width()<m_w) && ((*itL2).Height()<m_w)) continue;
				//Si no se tocan ni en horizontal ni en vertical  teniendo parte en común continue
				if (!((*itL1).right==(*itL2).left) && !((*itL1).left==(*itL2).right)
						&& !((*itL1).top==(*itL2).bottom) && !((*itL1).bottom==(*itL2).top)) 
				{
					itL2++;
					continue;
				}
				//Si coinciden en horizontal
				//voy a saber que una debajo de otra;
				UnionRect(&RectTemp,&(*itL1),&(*itL2));	
				if (((RectTemp.Width()*RectTemp.Height())==(((*itL1).Width()*(*itL1).Height())+((*itL2).Width()*(*itL2).Height())) ))
				{
					nueva_lista.push_back(RectTemp);
					itL2=lista.erase(itL2);
					seguir=true;
					juntar=true;
					continue;
				}
				else
				{

					juntar=JuntarDosRectangulos(Nuevo1,Nuevo2,Nuevo3,(*itL1),(*itL2),tipo_union);
					if (juntar==true)
					{	
						if (!Nuevo1.IsRectEmpty()) nueva_lista.push_back(Nuevo1);
						if (!Nuevo2.IsRectEmpty()) nueva_lista.push_back(Nuevo2);
						if (!Nuevo3.IsRectEmpty()) nueva_lista.push_back(Nuevo3);
						itL2=lista.erase(itL2);
						seguir=true;
						continue;
					}
				}
				itL2++;
			}while((itL2!=lista.end()) && (juntar!=true));
			if (juntar==true) 
			{
				itL1=lista.erase(itL1);
				continue;
			}
			itL1++;
		}while(itL1!=lista.end());
	lista.insert(lista.begin(),nueva_lista.begin(),nueva_lista.end());
	} while (seguir==true && cuenta<tope);
}
void PALLET::JuntarPerdida(void)
{	
	bool juntar=false;
	bool seguir=false;
	std::list<CRect> ::iterator itL1,itL2,itL3;
	std::list<CRect> nueva_lista;
	CRect Nuevo1,Nuevo2,Nuevo3,RectTemp;
	int cuenta=0;
	do
	{
		cuenta++;
		seguir=false;
		nueva_lista.clear();
		itL1=m_lista_perdidas.begin();
		do{
			juntar=false;
//			CRect rect1=(*itL1);
			itL3=itL1;
			itL3++;
			if (itL3==m_lista_perdidas.end()) break;
//			if (((*itL1).Width()<m_w) && ((*itL1).Height()<m_w)) continue;
			itL2=itL1;
			do
			{
//				CRect rect2=(*itL2);
				juntar=false;
				if (((*itL1).BottomRight()==(*itL2).BottomRight()) &&
				((*itL1).TopLeft()==(*itL2).TopLeft()) )
				{
					itL2++;
					continue;
				}

	
//				if (((*itL2).Width()<m_w) && ((*itL2).Height()<m_w)) continue;
				//Si no se tocan ni en horizontal ni en vertical  teniendo parte en común continue
				if (!((*itL1).right==(*itL2).left) && !((*itL1).left==(*itL2).right)
						&& !((*itL1).top==(*itL2).bottom) && !((*itL1).bottom==(*itL2).top)) 
				{
					itL2++;
					continue;
				}
				//Si coinciden en horizontal
				//voy a saber que una debajo de otra;
				UnionRect(&RectTemp,&(*itL1),&(*itL2));	
				if (((RectTemp.Width()*RectTemp.Height())==(((*itL1).Width()*(*itL1).Height())+((*itL2).Width()*(*itL2).Height())) ))
				{
					nueva_lista.push_back(RectTemp);
					itL2=m_lista_perdidas.erase(itL2);
					seguir=true;
					juntar=true;
					continue;
				}
				else
				{

					juntar=JuntarDosRectangulos(Nuevo1,Nuevo2,Nuevo3,(*itL1),(*itL2),tipo_union);
					if (juntar==true)
					{	
						if (!Nuevo1.IsRectEmpty()) nueva_lista.push_back(Nuevo1);
						if (!Nuevo2.IsRectEmpty()) nueva_lista.push_back(Nuevo2);
						if (!Nuevo3.IsRectEmpty()) nueva_lista.push_back(Nuevo3);
						itL2=m_lista_perdidas.erase(itL2);
						seguir=true;
						continue;
					}
				}
				itL2++;
			}while((itL2!=m_lista_perdidas.end()) && (juntar!=true));
			if (juntar==true) 
			{
				itL1=m_lista_perdidas.erase(itL1);
				continue;
			}
			itL1++;
		}while(itL1!=m_lista_perdidas.end());
	m_lista_perdidas.insert(m_lista_perdidas.begin(),nueva_lista.begin(),nueva_lista.end());
	} while (seguir==true && cuenta<tope);

}
//La funcion que puede tener el tope igual al infinito
/*
bool PALLET::JuntarDosRectangulos(CRect &Nuevo1,CRect &Nuevo2,CRect &Nuevo3,CRect &rect1,CRect &rect2,char tipo)
{
//Cambio por 1	
	int deben_juntarse=m_w-1;
//	int deben_juntarse=1;
	bool juntar=false;
	CRect Pdown,Pup,Pleft,Pright;
	if (rect1.top<rect2.top)
	{
		Pdown=rect1;
		Pup=rect2;
	}
	else
	{
		Pdown=rect2;
		Pup=rect1;
	}
	if (rect1.left<rect2.left)
	{
		Pleft=rect1;
		Pright=rect2;
	}
	else
	{
		Pleft=rect2;
		Pright=rect1;
	}
	if ((rect1.right==rect2.left) || (rect2.right==rect1.left))
	{
		//Y tambien coincidan en al menos w
		if (Pdown.bottom-Pup.top>deben_juntarse && Pdown.Height()>deben_juntarse && Pup.Height()>deben_juntarse)
		{
			//Pdown izquierda de Pup
			if (Pdown.right==Pup.left)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.left=Pdown.left;
				Nuevo1.top=Pup.top;
				Nuevo1.right=Pup.right;
				
				Nuevo2.top=Pdown.top;
				Nuevo2.left=Pdown.left;
				Nuevo2.right=Pdown.right;
				Nuevo2.bottom=Pup.top;
				if (Pup.bottom>Pdown.bottom)
				{
					Nuevo1.bottom=Pdown.bottom;
					juntar=true;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pdown.bottom;
					Nuevo3.left=Pup.left;
					Nuevo3.right=Pup.right;
					Nuevo3.bottom=Pup.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.bottom=Pup.bottom;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pup.bottom;
					Nuevo3.left=Pdown.left;
					Nuevo3.right=Pdown.right;
					Nuevo3.bottom=Pdown.bottom;
				}
			}
			//Pdown derecha de Pup
			if (Pdown.left==Pup.right)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.left=Pup.left;
				Nuevo1.right=Pdown.right;
				Nuevo1.top=Pup.top;
				Nuevo1.bottom=Pdown.bottom;
				Nuevo2.top=Pdown.top;
				Nuevo2.left=Pdown.left;
				Nuevo2.right=Pdown.right;
				Nuevo2.bottom=Pup.top;
				if (Pup.bottom>Pdown.bottom)
				{
					juntar=true;
					Nuevo1.bottom=Pdown.bottom;
	//				if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pdown.bottom;
					Nuevo3.left=Pup.left;
					Nuevo3.right=Pup.right;
					Nuevo3.bottom=Pup.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.bottom=Pup.bottom;
	//				if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pup.bottom;
					Nuevo3.left=Pdown.left;
					Nuevo3.right=Pdown.right;
					Nuevo3.bottom=Pdown.bottom;
				}	
			}
		}	
	}

	//Coinciden en vertical
	if ((rect1.top==rect2.bottom) || (rect1.bottom==rect2.top))
	{
		//Y tambien coincidan en horizontal en al menos w
		if (Pleft.right-Pright.left>deben_juntarse && Pright.Width()>deben_juntarse && Pleft.Width()>deben_juntarse)
		{
			//Pleft abajo de Pright
			if (Pleft.bottom==Pright.top)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.top=Pleft.top;
				Nuevo1.bottom=Pright.bottom;
				Nuevo1.left=Pright.left;
				//Los pequeños
				Nuevo2.top=Pleft.top;
				Nuevo2.left=Pleft.left;
				Nuevo2.right=Pright.left;
				Nuevo2.bottom=Pleft.bottom;
				if (Pleft.right>Pright.right)
				{
					juntar=true;
					Nuevo1.right=Pright.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pleft.right;
					Nuevo3.left=Pright.right;
					Nuevo3.top=Pleft.top;
					Nuevo3.bottom=Pleft.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.right=Pleft.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pright.right;
					Nuevo3.left=Pleft.right;
					Nuevo3.top=Pright.top;
					Nuevo3.bottom=Pright.bottom;
				}
			}
			//Pleft arriba de Pright
			if (Pleft.top==Pright.bottom)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.top=Pright.top;
				Nuevo1.bottom=Pleft.bottom;
				Nuevo1.left=Pright.left;
				//Los pequeños
				Nuevo2.top=Pleft.top;
				Nuevo2.left=Pleft.left;
				Nuevo2.right=Pright.left;
				Nuevo2.bottom=Pleft.bottom;
				if (Pleft.right<Pright.right)
				{
					juntar=true;
					Nuevo1.right=Pleft.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pright.right;
					Nuevo3.left=Pleft.right;
					Nuevo3.top=Pright.top;
					Nuevo3.bottom=Pright.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.right=Pright.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pleft.right;
					Nuevo3.left=Pright.right;
					Nuevo3.top=Pleft.top;
					Nuevo3.bottom=Pleft.bottom;
				}
			}
		}
		
	}
	if (juntar==false) return juntar;
	if (m_tipo_junta==1 )
	{
		//Si quiero no quiero ni horizontal ni vertical quiero que el area del mayor 
		//sea mayor que el area de los que tenia
		if (tipo!='H' && tipo!='V' )
		{
			if	(((Nuevo1.Height()*Nuevo1.Width())>(rect1.Height()*rect1.Width())) && ((Nuevo1.Height()*Nuevo1.Width())>(rect2.Height()*rect2.Width())) )
				return true;
		}
		if (tipo=='H' )
		{
			//Si cabe una pieza horizontal
			if (Nuevo1.Height()>=m_w && Nuevo1.Width()>=m_l)
			{
//				int antiguasH=__max(((rect1.Width()/m_l)*(rect1.Height()/m_w)),(CuantosG4(rect1.Width(),rect1.Height())))+__max((CuantosG4(rect2.Width(),rect2.Height())),((rect2.Width()/m_l)*(rect2.Height()/m_w)));
//				int nuevasH=__max(((Nuevo1.Width()/m_l)*(Nuevo1.Height()/m_w)),(CuantosG4(Nuevo1.Width(),Nuevo1.Height())))+__max((CuantosG4(Nuevo2.Width(),Nuevo2.Height())),((Nuevo2.Width()/m_l)*(Nuevo2.Height()/m_w)))+__max(CuantosG4(Nuevo3.Width(),Nuevo3.Height()),((Nuevo3.Width()/m_l)*(Nuevo3.Height()/m_w)));
				int antiguasH=__max(((rect1.Width()/m_l)*(rect1.Height()/m_w)),(0))+__max(0,((rect2.Width()/m_l)*(rect2.Height()/m_w)));
				int nuevasH=__max(((Nuevo1.Width()/m_l)*(Nuevo1.Height()/m_w)),0)+__max(0,((Nuevo2.Width()/m_l)*(Nuevo2.Height()/m_w)))+__max(0,((Nuevo3.Width()/m_l)*(Nuevo3.Height()/m_w)));

				//Si caben más horizontales que antes o más G4 que horizontales
				if ((nuevasH>=antiguasH))
				{
					if (nuevasH>antiguasH) 
					{
						return true;
					}
					else
					{
						//Pero son más anchas las nuevas
						if	(((Nuevo1.Width()>rect1.Width()) && (Nuevo1.Width()>=rect2.Width())) ||
							((Nuevo1.Width()>=rect1.Width()) && (Nuevo1.Width()>rect2.Width())))
							return true;	
					}
				}
			}
			else
			{
				if	(((Nuevo1.Width()>rect1.Width()) && (Nuevo1.Width()>=rect2.Width())) ||
					((Nuevo1.Width()>=rect1.Width()) && (Nuevo1.Width()>rect2.Width())))
					return true;
			}
		}
		if (tipo=='V')
		{
			//Si cabeuna pieza horizontal
			if (Nuevo1.Height()>=m_l && Nuevo1.Width()>=m_w)
			{
//				int antiguasV=__max(((rect1.Width()/m_w)*(rect1.Height()/m_l)),(CuantosG4(rect1.Width(),rect1.Height())))+__max((CuantosG4(rect2.Width(),rect2.Height())),((rect2.Width()/m_w)*(rect2.Height()/m_l)));
//				int nuevasV=__max(((Nuevo1.Width()/m_w)*(Nuevo1.Height()/m_l)),(CuantosG4(Nuevo1.Width(),Nuevo1.Height())))+__max((CuantosG4(Nuevo2.Width(),Nuevo2.Height())),((Nuevo2.Width()/m_w)*(Nuevo2.Height()/m_l)))+__max(CuantosG4(Nuevo3.Width(),Nuevo3.Height()),((Nuevo3.Width()/m_w)*(Nuevo3.Height()/m_l)));
				int antiguasV=__max(((rect1.Width()/m_w)*(rect1.Height()/m_l)),0)+__max(0,((rect2.Width()/m_w)*(rect2.Height()/m_l)));
				int nuevasV=__max(((Nuevo1.Width()/m_w)*(Nuevo1.Height()/m_l)),0)+__max(0,((Nuevo2.Width()/m_w)*(Nuevo2.Height()/m_l)))+__max(0,((Nuevo3.Width()/m_w)*(Nuevo3.Height()/m_l)));
				//Si caben más horizontales que antes o más G4 que horizontales
				//Si caben más horizontales que antes o más G4 que horizontales
				if ((nuevasV>=antiguasV))
				{
					if (nuevasV>antiguasV) 
					{
						return true;
					}
					else
					{
						//Pero son más anchas las nuevas
						if	(((Nuevo1.Height()>=rect1.Height()) && (Nuevo1.Height()>rect2.Height())) ||
						((Nuevo1.Height()>rect1.Height()) && (Nuevo1.Height()>=rect2.Height())))
							return true;
					}
				}
			}
			else
			{
				if	(((Nuevo1.Height()>=rect1.Height()) && (Nuevo1.Height()>rect2.Height())) ||
					((Nuevo1.Height()>rect1.Height()) && (Nuevo1.Height()>=rect2.Height())))

					return true;
			}
		}

		return false;
	}
	if (m_tipo_junta==2 )
	{
	bool valido=false;
	//si el rectángulo nuevo cabe una pieza
	if (Nuevo1.Height()>=m_l && Nuevo1.Width()>=m_w)
		valido=true;
	if (Nuevo1.Height()>=m_w && Nuevo1.Width()>=m_l)
		valido=true;
	if (tipo=='H')
	{
		if (((Nuevo1.Width()/m_l)<(rect1.Width()/m_l)) || ((Nuevo1.Width()/m_l)<(rect2.Width()/m_l)))
			return false;
	}
	if (tipo=='V')
	{
		if (((Nuevo1.Height()/m_l)<(rect1.Height()/m_l)) || ((Nuevo1.Height()/m_l)<(rect2.Height()/m_l)))
			return false;
	}
//	if ((valido==false) ||
	if ((!((!Nuevo1.IsRectEmpty() || Nuevo1.Height()>m_w || Nuevo1.Width()>m_w))) ||
		(((Nuevo1.Width()*Nuevo1.Height())<(rect1.Width()*rect1.Height())) && valido==false) ||
		(((Nuevo1.Width()*Nuevo1.Height())<(rect2.Width()*rect2.Height())) && valido==false))
		juntar=false;
	return juntar;
	}
	if (m_tipo_junta==3 )
	{
		if (tipo=='H')
		{
//			if (((Nuevo1.Width()/m_l)<(rect1.Width()/m_l)) || ((Nuevo1.Width()/m_l)<(rect2.Width()/m_l)))
			if (((Nuevo1.Width())<(rect1.Width())) || ((Nuevo1.Width())<(rect2.Width())))
				return false;
		}
		if (tipo=='V')
		{
//			if (((Nuevo1.Height()/m_l)<(rect1.Height()/m_l)) || ((Nuevo1.Height()/m_l)<(rect2.Height()/m_l)))
			if (((Nuevo1.Height())<(rect1.Height())) || ((Nuevo1.Height())<(rect2.Height())))
				return false;
		}
		return true;
	}
	return false;
}
*/

bool PALLET::JuntarDosRectangulos(CRect &Nuevo1,CRect &Nuevo2,CRect &Nuevo3,CRect &rect1,CRect &rect2,char tipo)
{
//Cambio por 1	
	int deben_juntarse=m_w-1;
//	int deben_juntarse=1;
	bool juntar=false;
	CRect Pdown,Pup,Pleft,Pright;
	if (rect1.top<rect2.top)
	{
		Pdown=rect1;
		Pup=rect2;
	}
	else
	{
		Pdown=rect2;
		Pup=rect1;
	}
	if (rect1.left<rect2.left)
	{
		Pleft=rect1;
		Pright=rect2;
	}
	else
	{
		Pleft=rect2;
		Pright=rect1;
	}
	if ((rect1.right==rect2.left) || (rect2.right==rect1.left))
	{
		//Y tambien coincidan en al menos w
		if (Pdown.bottom-Pup.top>deben_juntarse && Pdown.Height()>deben_juntarse && Pup.Height()>deben_juntarse)
		{
			//Pdown izquierda de Pup
			if (Pdown.right==Pup.left)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.left=Pdown.left;
				Nuevo1.top=Pup.top;
				Nuevo1.right=Pup.right;
				
				Nuevo2.top=Pdown.top;
				Nuevo2.left=Pdown.left;
				Nuevo2.right=Pdown.right;
				Nuevo2.bottom=Pup.top;
				if (Pup.bottom>Pdown.bottom)
				{
					Nuevo1.bottom=Pdown.bottom;
					juntar=true;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pdown.bottom;
					Nuevo3.left=Pup.left;
					Nuevo3.right=Pup.right;
					Nuevo3.bottom=Pup.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.bottom=Pup.bottom;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pup.bottom;
					Nuevo3.left=Pdown.left;
					Nuevo3.right=Pdown.right;
					Nuevo3.bottom=Pdown.bottom;
				}
			}
			//Pdown derecha de Pup
			if (Pdown.left==Pup.right)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.left=Pup.left;
				Nuevo1.right=Pdown.right;
				Nuevo1.top=Pup.top;
				Nuevo1.bottom=Pdown.bottom;
				Nuevo2.top=Pdown.top;
				Nuevo2.left=Pdown.left;
				Nuevo2.right=Pdown.right;
				Nuevo2.bottom=Pup.top;
				if (Pup.bottom>Pdown.bottom)
				{
					juntar=true;
					Nuevo1.bottom=Pdown.bottom;
	//				if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pdown.bottom;
					Nuevo3.left=Pup.left;
					Nuevo3.right=Pup.right;
					Nuevo3.bottom=Pup.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.bottom=Pup.bottom;
	//				if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.top=Pup.bottom;
					Nuevo3.left=Pdown.left;
					Nuevo3.right=Pdown.right;
					Nuevo3.bottom=Pdown.bottom;
				}	
			}
		}	
	}

	//Coinciden en vertical
	if ((rect1.top==rect2.bottom) || (rect1.bottom==rect2.top))
	{
		//Y tambien coincidan en horizontal en al menos w
		if (Pleft.right-Pright.left>deben_juntarse && Pright.Width()>deben_juntarse && Pleft.Width()>deben_juntarse)
		{
			//Pleft abajo de Pright
			if (Pleft.bottom==Pright.top)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.top=Pleft.top;
				Nuevo1.bottom=Pright.bottom;
				Nuevo1.left=Pright.left;
				//Los pequeños
				Nuevo2.top=Pleft.top;
				Nuevo2.left=Pleft.left;
				Nuevo2.right=Pright.left;
				Nuevo2.bottom=Pleft.bottom;
				if (Pleft.right>Pright.right)
				{
					juntar=true;
					Nuevo1.right=Pright.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pleft.right;
					Nuevo3.left=Pright.right;
					Nuevo3.top=Pleft.top;
					Nuevo3.bottom=Pleft.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.right=Pleft.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pright.right;
					Nuevo3.left=Pleft.right;
					Nuevo3.top=Pright.top;
					Nuevo3.bottom=Pright.bottom;
				}
			}
			//Pleft arriba de Pright
			if (Pleft.top==Pright.bottom)
			{
				//Tres réctangulos uno grande y dos pequeños
				//el grande
				Nuevo1.top=Pright.top;
				Nuevo1.bottom=Pleft.bottom;
				Nuevo1.left=Pright.left;
				//Los pequeños
				Nuevo2.top=Pleft.top;
				Nuevo2.left=Pleft.left;
				Nuevo2.right=Pright.left;
				Nuevo2.bottom=Pleft.bottom;
				if (Pleft.right<Pright.right)
				{
					juntar=true;
					Nuevo1.right=Pleft.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pright.right;
					Nuevo3.left=Pleft.right;
					Nuevo3.top=Pright.top;
					Nuevo3.bottom=Pright.bottom;
				}
				else
				{
					juntar=true;
					Nuevo1.right=Pright.right;
//					if (((Nuevo1.Height()*Nuevo1.Width())/(m_l*m_w))>1) juntar=true;
					Nuevo3.right=Pleft.right;
					Nuevo3.left=Pright.right;
					Nuevo3.top=Pleft.top;
					Nuevo3.bottom=Pleft.bottom;
				}
			}
		}
		
	}
	if (juntar==false) return juntar;
	if (m_tipo_junta==1 )
	{
		//Si quiero no quiero ni horizontal ni vertical quiero que el area del mayor 
		//sea mayor que el area de los que tenia
		if (tipo!='H' && tipo!='V' )
		{
			if	(((Nuevo1.Height()*Nuevo1.Width())>(rect1.Height()*rect1.Width())) && ((Nuevo1.Height()*Nuevo1.Width())>(rect2.Height()*rect2.Width())) )
				return true;
		}
		if (tipo=='H' )
		{
			//Si cabe una pieza horizontal
			if (Nuevo1.Height()>=m_w && Nuevo1.Width()>=m_l)
			{
				int antiguasH=(((rect1.Width()/m_l)*(rect1.Height()/m_w))+((rect2.Width()/m_l)*(rect2.Height()/m_w)));
				int nuevasH=(((Nuevo1.Width()/m_l)*(Nuevo1.Height()/m_w))+((Nuevo2.Width()/m_l)*(Nuevo2.Height()/m_w))+((Nuevo3.Width()/m_l)*(Nuevo3.Height()/m_w)));
				//Si caben más horizontales que antes o más G4 que horizontales
				if ((nuevasH>antiguasH) || (CuantosG4(Nuevo1.Width(),Nuevo1.Height())>antiguasH))
					return true;
				else
				{	
					//Si caben las mismas
					if (nuevasH==antiguasH)
					{	
						//Pero son más anchas las nuevas
						if	(((Nuevo1.Width()>rect1.Width()) && (Nuevo1.Width()>=rect2.Width())) ||
							((Nuevo1.Width()>=rect1.Width()) && (Nuevo1.Width()>rect2.Width())))
							return true;
						
					}
				
				}
			}
			else
			{
				if	(((Nuevo1.Width()>rect1.Width()) && (Nuevo1.Width()>=rect2.Width())) ||
					((Nuevo1.Width()>=rect1.Width()) && (Nuevo1.Width()>rect2.Width())))
					return true;
			}
		}
		if (tipo=='V')
		{
			//Si cabeuna pieza horizontal
			if (Nuevo1.Height()>=m_l && Nuevo1.Width()>=m_w)
			{
				int antiguasV=(((rect1.Width()/m_w)*(rect1.Height()/m_l))+((rect2.Width()/m_w)*(rect2.Height()/m_l)));
				int nuevasV=(((Nuevo1.Width()/m_w)*(Nuevo1.Height()/m_l))+((Nuevo2.Width()/m_w)*(Nuevo2.Height()/m_l))+((Nuevo3.Width()/m_w)*(Nuevo3.Height()/m_l)));
				//Si caben más horizontales
				if ((nuevasV>antiguasV ) || (CuantosG4(Nuevo1.Width(),Nuevo1.Height())>antiguasV))
					return true;
				else 
				{
					if (nuevasV==antiguasV)
					{
						if	(((Nuevo1.Height()>rect1.Height()) && (Nuevo1.Height()>=rect2.Height())) ||
							((Nuevo1.Height()>=rect1.Height()) && (Nuevo1.Height()>rect2.Height())))
							return true;
//					if (
					}
				}
			}
			else
			{
				if	(((Nuevo1.Height()>=rect1.Height()) && (Nuevo1.Height()>rect2.Height())) ||
					((Nuevo1.Height()>rect1.Height()) && (Nuevo1.Height()>=rect2.Height())))

					return true;
			}
		}

		return false;
	}
	if (m_tipo_junta==2 )
	{
	bool valido=false;
	//si el rectángulo nuevo cabe una pieza
	if (Nuevo1.Height()>=m_l && Nuevo1.Width()>=m_w)
		valido=true;
	if (Nuevo1.Height()>=m_w && Nuevo1.Width()>=m_l)
		valido=true;
	if (tipo=='H')
	{
		if (((Nuevo1.Width()/m_l)<(rect1.Width()/m_l)) || ((Nuevo1.Width()/m_l)<(rect2.Width()/m_l)))
			return false;
	}
	if (tipo=='V')
	{
		if (((Nuevo1.Height()/m_l)<(rect1.Height()/m_l)) || ((Nuevo1.Height()/m_l)<(rect2.Height()/m_l)))
			return false;
	}
//	if ((valido==false) ||
	if ((!((!Nuevo1.IsRectEmpty() || Nuevo1.Height()>m_w || Nuevo1.Width()>m_w))) ||
		(((Nuevo1.Width()*Nuevo1.Height())<(rect1.Width()*rect1.Height())) && valido==false) ||
		(((Nuevo1.Width()*Nuevo1.Height())<(rect2.Width()*rect2.Height())) && valido==false))
		juntar=false;
	return juntar;
	}
	if (m_tipo_junta==3 )
	{
		if (tipo=='H')
		{
			if (((Nuevo1.Width()/m_l)<(rect1.Width()/m_l)) || ((Nuevo1.Width()/m_l)<(rect2.Width()/m_l)))
//			if (((Nuevo1.Width())<(rect1.Width())) || ((Nuevo1.Width())<(rect2.Width())))
				return false;
		}
		if (tipo=='V')
		{
			if (((Nuevo1.Height()/m_l)<(rect1.Height()/m_l)) || ((Nuevo1.Height()/m_l)<(rect2.Height()/m_l)))
//			if (((Nuevo1.Height())<(rect1.Height())) || ((Nuevo1.Height())<(rect2.Height())))
				return false;
		}
		return true;
	}
	return false;
}

void PALLET::DibujarBloques(std::list<BLOQUE> &lista_bloques,std::list<CRect> &lista_per,int contador,int sol,int perdida,int solbest, bool parar, int veces)
{
	CBrush brushclaro(RGB(208,248,253));
	CBrush brushblanco(RGB(255,255,255));
	CBrush brushrojo(RGB(255,0,0));
	//JMT
//	if (parar==true) 
//	{
//		int i=m_clientedc->GetWindow()->MessageBox("Siguiente Iteración","",0);
//	}
	//
//	m_clientedc->GetWindow()->OnCmdMsg
	int x=0,y=0;
	// Dibujar un rectangulo (el pallet)
	m_clientedc->FillSolidRect( 0, 0, m_factor*m_L, 
		                -m_factor*m_W, RGB(0,0,0) );
	m_clientedc->FillSolidRect( 0, 0, m_factor*m_L, 
		                -m_factor*m_W, RGB(0,0,0) );

	m_clientedc->SetBkColor(RGB(255,255,255));
	CString ss,ss1,ss2,ss3,ss4,ss5;
	char pallet[30],buff[20],vecesc[5];
	itoa(m_L,pallet,10);
	strcat(pallet," ");
	itoa(m_W,buff,10);
	strcat(pallet,buff);
	strcat(pallet," ");
	itoa(m_l,buff,10);
	strcat(pallet,buff);
	strcat(pallet," ");
	itoa(m_w,buff,10);
	strcat(pallet,buff);
	strcat(pallet," ");
	itoa(perdida,buff,10);
	itoa(veces,vecesc,10);
	ss5.Format("%3s",vecesc);
	ss4.Format("%s",pallet);
	ss.Format("%d",contador);
	ss1.Format("%d",sol);
	ss2.Format("%3s",buff);
	ss3.Format("%d",m_solbest);
	m_clientedc->TextOut((m_factor*m_L/2),0,ss4);
	m_clientedc->TextOut( m_factor*m_L, -m_factor*m_W,ss );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.75), ss1 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.5), ss2 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.25), ss3 );
	m_clientedc->TextOut( m_factor*m_L, 0, ss5 );
	
	int L=m_l,w=m_w;
	std::list<BLOQUE> ::iterator itB;
	std::list<CRect> ::iterator itL;
//	m_clientedc->SetBkMode(TRANSPARENT);
//	m_clientedc->SetPolyFillMode(ALTERNATE);
	m_clientedc->SelectObject(brushclaro);

	for (itL=lista_per.begin();itL!=lista_per.end();itL++)
	{
		
		m_clientedc->Rectangle(m_factor*((*itL).left),-m_factor*((*itL).top),m_factor*((*itL).right),-m_factor*((*itL).bottom));
	}
//	m_clientedc->SetBkColor(RGB(255,255,255));
//	m_clientedc->SetBkMode(OPAQUE);
	m_clientedc->SelectObject(brushblanco);
	for (itB=lista_bloques.begin();itB!=lista_bloques.end();itB++)
	{
//		BLOQUE b1=(*itB);
		if ((*itB).GetTipo()=='H')
		{
			L=m_l;
			w=m_w;
			if ((((*itB).Width()/m_l)<=m_hL) && (((*itB).Height()/m_w)<=m_hW))
				m_clientedc->SelectObject(brushblanco);
			else
				m_clientedc->SelectObject(brushrojo);
		}
		else
		{
			L=m_w;
			w=m_l;
			if ((((*itB).Width()/m_w)<=m_vL) && (((*itB).Height()/m_l)<=m_vW))
				m_clientedc->SelectObject(brushblanco);
			else
				m_clientedc->SelectObject(brushrojo);

		}
		x=(*itB).left;
		y=(*itB).top;
		
		for (register int ix=1;ix<=((*itB).Width()/L);ix++)
		{
			if (ix==1) x=(*itB).left;
			for (register int iy=1;iy<=((*itB).Height()/w);iy++)
			{
				if (iy==1) y=(*itB).top;
				m_clientedc->Rectangle(m_factor*x,-m_factor*y,m_factor*(x+(L)),-m_factor*(y+(w)));
				y=y+w;
			}
			x=x+L;
		}

	}
	CBrush brushblanco1(RGB(255,0,255));
	CBrush brushblanco2(RGB(0,255,255));

/*	std::vector<var> ::iterator itV;
	for (itV=m_VectorDeVar.begin();itV!=m_VectorDeVar.end();itV++)
	{
		if ((*itV).orientacion=='H')
		{
			m_clientedc->SelectObject(brushblanco1);

			m_clientedc->Rectangle(m_factor*(*itV).x,-m_factor*(*itV).y,m_factor*((*itV).x+0.5),-m_factor*((*itV).y+0.5));
		}
		if ((*itV).orientacion=='V')
		{
			m_clientedc->SelectObject(brushblanco2);

			m_clientedc->Rectangle(m_factor*(*itV).x,-m_factor*((*itV).y+0.5),m_factor*((*itV).x+0.5),-m_factor*((*itV).y+1));
		}

	}*/
	//Dibujar bloques y lo que cubren cada uno de estos bloques
/*	int i=0;
	std::list<inter_corto> ::iterator itK;
	for (itK=m_ListaDeRes.begin();itK!=m_ListaDeRes.end();itK++)
	{
		CBrush brushblanco1(RGB(255,i*0.1,255-(i*0.1)));
		if (i==1189)
		{
			int ppo=9;
			int x=m_Perdida_Restri[i][1];
			int y=m_Perdida_Restri[i][2];

		}
		m_clientedc->SelectObject(brushblanco1);
		m_clientedc->Rectangle(m_factor*(*itK)[0],-m_factor*(*itK)[1],m_factor*((*itK)[0]+m_Perdida_Restri[i][1]),-m_factor*((*itK)[1]+m_Perdida_Restri[i][2]));
		i++;
	}
*/
  //Retardo
/*	int mil=500;
	if (contador==2000) mil=10000;
	for(int register i1=0;i1<mil;i1++)
	{
		for(int register i2=0;i2<mil;i2++)
		{
			for(int register i3=0;i3<mil;i3++);
		}
	}*/
}
	

bool PALLET::EsTabu(std::list<BLOQUE> &lista)
{
//	return false;
	std::list<BLOQUE> ::iterator itB,itB1;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
		{

			//Si el bloque es de ancho o largo como el pallet entonces solo importa el
			//tamaño para ser tabu
			if ((*itB1).Width()==m_L || (*itB1).Height()==m_W)
			{
				if (((*itB1).GetTipo()==(*itB).GetTipo()) && ((*itB1).Width()==(*itB).Width()) && ((*itB1).Height()==(*itB).Height()))
					return true;
			}
			else
			{
				if (((*itB1).GetTipo()==(*itB).GetTipo()) && (*itB1).TopLeft()==(*itB).TopLeft() && (*itB1).BottomRight()==(*itB).BottomRight())
					return true;
/*
//Si no quiero que el bloque simétrico sea tabu tampoco
				else
				{
					CRect Sup_Rect(0,0,0,0);
					int kk=(*itB).Width();
					Sup_Rect.left=m_L-(*itB).left-(*itB).Width();
					Sup_Rect.right=Sup_Rect.left+kk;
					Sup_Rect.top=(*itB).top;
					Sup_Rect.bottom=(*itB).bottom;
					if (((*itB1).EqualRect((Sup_Rect))!=0))
						return true;
				}
*/

			}

//			if (((*itB1).GetTipo()==(*itB).GetTipo()) && ((*itB1).Width()==((*itB)).Width()) && ((*itB1).Height()==((*itB)).Height()) && (((*itB).Width()>m_L/2) || (((*itB).Height()>m_W/2))))
//				return true;

//		if ((B1.GetTipo()==(*itB).GetTipo())&& )
//			return true;
		}
	}
	return false;
}
 bool PALLET::EsTabuSinLaUltima(std::list<BLOQUE> &lista)
{
//	return false;
	if (m_lista_tabu.size()<=1) 
	{
		return false;
	}
	 int la_primera_no_vale=0;
	std::list<BLOQUE> ::iterator itB,itB1;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		la_primera_no_vale=0;
		for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
		{

			la_primera_no_vale++;
			if (la_primera_no_vale==1) continue;
//			BLOQUE b1=(*itB),b2=(*itB1);
			if (((*itB1).GetTipo()==(*itB).GetTipo())&&((*itB1).EqualRect((*itB))))
				return true;
/*		if ((B1.GetTipo()==(*itB).GetTipo())&&(B1.BottomRight().x>=(*itB).BottomRight().x) && (B1.BottomRight().y>=(*itB).BottomRight().y)  && (B1.TopLeft().x<=(*itB).TopLeft().x) && (B1.TopLeft().y<=(*itB).TopLeft().y))
			return true;*/
		}
	}
	return false;
}/*
bool PALLET::EsTabu(BLOQUE &B1)
{
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
	{
		if ((B1.GetTipo()==(*itB).GetTipo())&&(B1.EqualRect((*itB))))
			return true;
//		if ((B1.GetTipo()==(*itB).GetTipo())&&(B1.BottomRight().x>=(*itB).BottomRight().x) && (B1.BottomRight().y>=(*itB).BottomRight().y)  && (B1.TopLeft().x<=(*itB).TopLeft().x) && (B1.TopLeft().y<=(*itB).TopLeft().y))
//			return true;
	}
	return false;

}*/
bool PALLET::EsTabu2(BLOQUE &B1)
{
	return false;
	CRect RectTemp;
	std::list< std::list<BLOQUE> > ::iterator itB;
	std::list<BLOQUE>::iterator itB2,itB3;
	for (itB=m_lista_tabu2.begin();itB!=m_lista_tabu2.end();itB++)
	{
		for(itB2=(*itB).begin();itB2!=(*itB).end();itB2++)
		{

			if ((B1.GetTipo()==(*itB2).GetTipo())&&(B1.EqualRect((*itB2))))
				return false;
		}
	}
	return true;
}
bool PALLET::EsTabu2SinLaUltima(BLOQUE &B1)
{
	return false;
	CRect RectTemp;
	std::list< std::list<BLOQUE> > ::iterator itB;
	std::list<BLOQUE>::iterator itB2,itB3;
	int es_uno=0;
	for (itB=m_lista_tabu2.begin();itB!=m_lista_tabu2.end();itB++)
	{
		es_uno++;
		if (es_uno==1) continue;
		for(itB2=(*itB).begin();itB2!=(*itB).end();itB2++)
		{
			if ((B1.GetTipo()==(*itB2).GetTipo())&&(B1.EqualRect((*itB2))))
				return true;
		}
	}
	return false;
}
/*
bool PALLET::EsTabu2(MOVE &M1,int tipo_Mov)
{
//	return false;
	CRect RectTemp;
	std::list< std::list<BLOQUE> > ::iterator itB;
	std::list<BLOQUE>::iterator itB2,itB3;
	for (itB=m_lista_tabu2.begin();itB!=m_lista_tabu2.end();itB++)
	{
		for(itB2=(*itB).begin();itB2!=(*itB).end();itB2++)
		{
			if ((M1.GetBloqueAntiguo().GetTipo()==(*itB2).GetTipo())&&(M1.GetBloqueAntiguo().EqualRect((*itB2))))
				return true;
		}
	}
	return false;
	bool es_tabu=false;
	if (tipo_Mov==3 || tipo_Mov==4 || tipo_Mov==7 || tipo_Mov==8 )
	{
		for (itB=m_lista_tabu2.begin();itB!=m_lista_tabu2.end();itB++)
		{
			for(itB2=(*itB).begin();itB2!=(*itB).end();itB2++)
			{
				es_tabu=false;
				for (itB3=m_lista_bloques.begin();itB3!=m_lista_bloques.end();itB3++)
				{
					if (((*itB3).GetTipo()==(*itB2).GetTipo()) && ((*itB3).EqualRect((*itB2))))
						es_tabu=true;
					
				}
				if (es_tabu==false) continue;
				//Si corta con alguno de los rectángulos tabu 
				CRect rectInter;
				rectInter.IntersectRect((*itB2),M1.GetBloqueNuevo());
				if ((rectInter.Width()<(*itB2).Width()+M1.GetBloqueNuevo().Width())
					&& (rectInter.Height()<(*itB2).Height()+M1.GetBloqueNuevo().Height()))
				return true;

			}
		}
	}
	return false;

}
*/
void PALLET::Add_Lista_Tabu(BLOQUE &B1)
{
	std::list<BLOQUE> ::iterator itB;
	if (m_lista_tabu.size()>m_tam_tabu)
	{
		m_lista_tabu.pop_front();
		m_lista_tabu.push_back(B1);
	}
	else
	{
		m_lista_tabu.push_back(B1);

	}
}
void PALLET::Add_Lista_Tabu2(std::list<BLOQUE> &lista,std::list<BLOQUE> &lista2)
{
	return;
	CRect RectTemp;
	std::list< BLOQUE > ::iterator itB,itB2;
	std::list< BLOQUE > lista_temp;
	//movimiento de aumentar
	bool ya_existia=false;
	for (itB2=lista2.begin();itB2!=lista2.end();itB2++)
	{
		ya_existia=false;
		for (itB=lista.begin();itB!=lista.end();itB++)
		{
			if ((*itB).GetTipo()==(*itB2).GetTipo() && ((*itB).EqualRect((*itB2))!=0) )
				ya_existia=true;
		}
		if (ya_existia==false) lista_temp.push_back(*itB2);
	}
	if (m_lista_tabu2.size()>m_tam_tabu2)
	{
		m_lista_tabu2.pop_front();
		m_lista_tabu2.push_back(lista_temp);
	}
	else
	{
		m_lista_tabu2.push_back(lista_temp);

	}
}

void PALLET::Actualizar_Lista_Bloques(MOVE &BestMove)
{
	//SI es de Aumentar incluir también el 
	bool ya=false;
	std::list<BLOQUE> ::iterator itB,itB2;
	//Limpiar los bloques vacios
//	printf("AB %3d",BestMove.GetListaBloques().size());

	itB2=BestMove.GetListaBloques().begin();
//	if (BestMove.GetListaBloques().size()==0) exit(4);
	do
	{
		if ((*itB2).IsRectEmpty()) 
		{
			itB2=BestMove.GetListaBloques().erase(itB2);
			continue;
		}
		itB2++;
	}while(itB2!=BestMove.GetListaBloques().end());
/*	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end() && ya==false;itB++)
	{
		
		if (((*itB).BottomRight()==BestMove.GetBloqueAntiguo().BottomRight()) &&
			((*itB).TopLeft()==BestMove.GetBloqueAntiguo().TopLeft()) && ((*itB).GetTipo()==BestMove.GetBloqueAntiguo().GetTipo()))
		{
			itB=m_lista_bloques.erase(itB);
			ya=true;
		}
	}
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end() && ya==false;itB++)
	{
		for (itB2=BestMove.GetListaBloques().begin();itB2!=BestMove.GetListaBloques().end() ;itB2++)
		{
		if (((*itB).BottomRight()==(*itB2).BottomRight()) &&
			((*itB).TopLeft()==(*itB2).TopLeft()) && ((*itB).GetTipo()==(*itB2).GetTipo()))
			itB2=m_lista_bloques.erase(itB2);
		}
	}
	if (!BestMove.GetBloqueNuevo().IsRectEmpty()) m_lista_bloques.push_back(BestMove.GetBloqueNuevo());*/
	m_lista_bloques.clear();
//	printf("AB2 %3d",BestMove.GetListaBloques().size());
	m_lista_bloques.insert(m_lista_bloques.begin(),BestMove.GetListaBloques().begin(),BestMove.GetListaBloques().end());
//	printf("AB3");

}
//Al primer bloque le quito lo que tiene en común con 
// el segundo
int PALLET::Restar_Rectangulo(BLOQUE &b1,BLOQUE &b2,CRect &B1,CRect &B2,CRect &B3,CRect &B4)
{
	//A b1 le quito lo que tiene en común con el segundo
	int l=m_l;
	int w=m_w;
	if (b1.GetTipo()=='V')
	{
		l=m_w;
		w=m_l;
	}

	//Caso b2 parte en dos verticales a b1 
	if ((b2.top<=b1.top) && (b2.bottom>=b1.bottom)  && (b1.right>b2.right) && (b1.left<b2.left))
	{
		//Crear BLOQUEs
		int b=((b1.right-b2.right));
		int c=((b2.left-b1.left));
		//El que esta al lado derecho
		if (b>0)
		{
			B2.left=b1.right-(b/l)*l;
			B2.right=b1.right;
			B2.top=b1.top;
			B2.bottom=b1.bottom;
		}
		//El que esta al lado izquierdo
		if (c>0)
		{
			B3.right=b1.left+(c/l)*l;
			B3.left=b1.left;
			B3.top=b1.top;
			B3.bottom=b1.bottom;
		}
		return 1;
	}
	//Caso b2 parte en dos horizontales a b1 
	if ((b2.left<=b1.left) && (b2.right>=b1.right) && (b2.top>b1.top) && (b2.bottom<b1.bottom))
	{
		//Crear BLOQUEs
		int b=((b1.bottom-b2.bottom));
		int c=((b2.top-b1.top));
		//El que esta al arriba
		if (b>0)
		{
			B2.left=b1.left;
			B2.right=b1.right;
			B2.top=b1.bottom-(b/w)*w;
			B2.bottom=b1.bottom;
		}
		//El que esta abajo
		if (c>0)
		{
			B3.right=b1.right;
			B3.left=b1.left;
			B3.top=b1.top;
			B3.bottom=b1.top+(c/w)*w;
		}
		return 1;
	}

	//Casos donde se crean tres nuevos rectángulos
	//Caso b2 entra por la derecha en b1
	if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)) ||
	((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b1.right-b2.right));
		int c=((b2.top-b1.top));
		if (a<0) a=0;
		if (b<0) b=0;
		if (c<0) c=0;
		//El que esta por encima;
		if (a>0)
		{
			B1.BottomRight()=b1.BottomRight();
			B1.left=b1.left;
			B1.top=b1.bottom-(a/w)*w;
		}
		//El que esta por debajo
		if (c>0)
		{
			B3.TopLeft()=b1.TopLeft();
			B3.bottom=b1.top+(c/w)*w;
			B3.top=b1.top;
			B3.right=b1.right;
		}
		//El que esta al lado
		if (b>0)
		{
			B2.right=b1.right;
			B2.left=b1.right-(b/l)*l;
			B2.bottom=b1.bottom-(a/w)*w;
			B2.top=b1.top+(c/w)*w;
		}
		return 1;
	}
	//Caso b2 entra por la izquierda en b1
	if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.left>b1.left) && (b2.left<=b1.right) && (b2.right>=b1.right)) ||
	((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.left>b1.left) && (b2.left<=b1.right)&& (b2.right>=b1.right)))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b2.left-b1.left));
		int c=((b2.top-b1.top));
		if (a<0) a=0;
		if (b<0) b=0;
		if (c<0) c=0;
		//El que esta por encima;
		if (a>0)
		{
			B1.BottomRight()=b1.BottomRight();
			B1.left=b1.left;
			B1.top=b1.bottom-(a/w)*w;
		}
		//El que esta por debajo
		if (c>0)
		{
			B3.TopLeft()=b1.TopLeft();
			B3.bottom=b1.top+(c/w)*w;
			B3.top=b1.top;
			B3.right=b1.right;
		}
		//El que esta al lado
		if (b>0)
		{
			B2.left=b1.left;
			B2.right=b1.left+(b/l)*l;
			B2.bottom=b1.bottom-(a/w)*w;
			B2.top=b1.top+(c/w)*w;
		}


		return 1;
	}
	//Caso b2 entra a b1 por  abajo
	if ((b2.bottom<b1.bottom) && (b2.bottom>b1.top) && (b2.top<=b1.top) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b1.right-b2.right));
		int c=((b2.left-b1.left));
		//El que esta al lado derecho
		if (b>0)
		{
			B2.right=b1.right;
			B2.left=b1.right-(b/l)*l;
			B2.top=b1.top;
			B2.bottom=b1.bottom;
		}
		//El que esta al lado izquierdo
		if (c>0)
		{
			B3.left=b1.left;
			B3.right=b1.left+(c/l)*l;
			B3.top=b1.top;
			B3.bottom=b1.bottom;
		}
		//El que esta por debajo;
		if (a>0)
		{
			B1.top=b1.bottom-(a/w)*w;
			B1.bottom=b1.bottom;
			B1.right=b1.right-(b/l)*l;
			B1.left=b1.left+(c/l)*l;
		}

		return 1;
	}

	//Caso b2 entra en b1 por arriba
	if ((b2.top<b1.bottom) && (b2.top>b1.top) && (b2.bottom>=b1.bottom) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
	{
		//Crear bLOQUE
		int a=((b2.top-b1.top));
		int b=((b1.right-b2.right));
		int c=((b2.left-b1.left));
		//El que esta al lado derecho
		if (b>0)
		{
			B2.left=b1.right-(b/l)*l;
			B2.right=b1.right;
			B2.top=b1.top;
			B2.bottom=b1.bottom;
		}
		//El que esta al lado izquierdo
		if (c>0)
		{
			B3.left=b1.left;
			B3.right=b1.left+(c/l)*l;
			B3.top=b1.top;
			B3.bottom=b1.bottom;
		}
		//El que esta por debajo;
		if (a>0)
		{
			B1.bottom=b1.top+(a/w)*w;
			B1.top=b1.top;
			B1.right=b1.right-(b/l)*l;
			B1.left=b1.left+(c/l)*l;
		}

		return 1;		
	}

	//Caso RecTemp dentro de b1
	//Aqui cuatro rectángulos
	if ((b2.top>b1.top) && (b2.bottom<b1.bottom) && (b2.left>b1.left) && (b2.right<b1.right))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b2.left-b1.left));
		int c=((b2.top-b1.top));
		int d=((b1.right-b2.right));
		if (a<0) a=0;
		if (b<0) b=0;
		if (c<0) c=0;
		if (d<0) d=0;
		//El que esta por encima;
		if (a>0)
		{
			B1.BottomRight()=b1.BottomRight();
			B1.left=b1.left;
			B1.top=b1.bottom-(a/w)*w;
		}
		//El que esta por debajo
		if (c>0)
		{
			B3.TopLeft()=b1.TopLeft();
			B3.bottom=b1.top+(c/w)*w;
			B3.top=b1.top;
			B3.right=b1.right;
		}
		//El que esta al lado izquierdo
		if (b>0)
		{
			B2.left=b1.left;
			B2.right=b1.left+(b/l)*l;
			B2.bottom=b1.bottom-(a/w)*w;
			B2.top=b1.top+(c/w)*w;
		}

		//El que esta al lado derecho
		if (d>0)
		{
			B2.right=b1.right;
			B2.left=b1.right-(d/l)*l;
			B2.bottom=b1.bottom-(a/w)*w;
			B2.top=b1.top+(c/w)*w;
		}
		return 1;
	}
	CRect RectTemp;
	IntersectRect(&RectTemp,&b1,&b2);
	if (RectTemp.IsRectEmpty())
	{
		return 0;
	}
	//Si el b2 esta dentro de la intersección
	//me crea dos nuevos rectangulos
	//!!!Falta los casos donde los bloques estan en medio 
	//de la perdida sobrante
	CPoint b2TL=RectTemp.TopLeft();
	CPoint b2BR=RectTemp.BottomRight();
	CPoint b1TL=b1.TopLeft();
	CPoint b1BR=b1.BottomRight();
		//Cuatro casos
	//b2 más grande que b1 por la izquierda
	if (b2TL==b1TL && b1.right>b2.right)
	{
		B1.SetRect(b1.right-((b1.right-RectTemp.right)/l)*l,b1.top,b1.right,b1.bottom);
		return 1;
	}
	//b2 más grande que b1 por la derecha
	if (b2BR==b1BR && b1.left<b2.left)
	{
		B1.SetRect(b1.left,b1.top,b1.left+((RectTemp.left-b1.left)/l)*l,b1.bottom);
		return 1;
	}
	//b2 más grande que b1 por abajo
	if (b2TL==b1TL && b1.bottom>b2.bottom)
	{
 
		B1.SetRect(b1.left,b1.bottom-((b1.bottom-RectTemp.bottom)/w)*w,b1.right,b1.bottom);
		return 1;
	}
	//b2 más grande que b1 por arriba
	if (b2BR==b1BR && b1.top<b2.top)
	{
		B1.SetRect(b1.left,b1.top,b1.right,b1.top+((RectTemp.top-b1.top)/w)*w);
		return 1;
	}

	return 0;
}

int PALLET::Restar_Rectangulo(CRect &b1,CRect &b2,CRect &B1,CRect &B2,CRect &B3,CRect &B4)
{
	CRect RectTemp;
	IntersectRect(&RectTemp,&b1,&b2);
	if (RectTemp.IsRectEmpty())
	{
		return 0;
	}
	//Si el b2 esta dentro de la intersección
	//me crea dos nuevos rectangulos
	//!!!Falta los casos donde los bloques estan en medio 
	//de la perdida sobrante
	CPoint b2TL=RectTemp.TopLeft();
	CPoint b2BR=RectTemp.BottomRight();
	CPoint b1TL=b1.TopLeft();
	CPoint b1BR=b1.BottomRight();
	//Cuatro caso
	if (b2TL==b1TL)
	{
		//Esquina de arriba izquierda
		//Ahora dos rectangulos
		B1.SetRect(b2TL.x,b2BR.y,b1BR.x,b1BR.y);
		B2.SetRect(b2BR.x,b2TL.y,b1BR.x,b2BR.y);
		return 1;
	}
	if (b2BR==b1BR)
	{
		//Esquina de abajo derecha
		B1.SetRect(b1TL.x,b1TL.y,b1BR.x,b2TL.y);
		B2.SetRect(b1TL.x,b2TL.y,b2TL.x,b2BR.y);
		return 1;
	}
	if ((b2TL.x==b1TL.x) && (b2BR.y==b1BR.y))
	{
		//Esquina izquierda abajo
		B1.SetRect(b1TL.x,b1TL.y,b1BR.x,b2TL.y);
		B2.SetRect(b2BR.x,b2TL.y,b1BR.x,b1BR.y);
	return 1;
	}
	if ((b2TL.y==b1TL.y) && (b2BR.x==b1BR.x))
	{
		//Esquina arriba derecha
		B1.SetRect(b1TL.x,b1TL.y,b2TL.x,b2BR.y);
		B2.SetRect(b1TL.x,b2BR.y,b1BR.x,b1BR.y);
		return 1;
	}
	//Casos donde se crean tres nuevos rectángulos
	//Caso RecTemp dentro de b1 por la izquierda
	if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)) ||
	((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b1.right-b2.right));
		int c=((b2.top-b1.top));
		if (a<0) a=0;
		if (b<0) b=0;
		if (c<0) c=0;
		//El que esta por encima;
		if (a>0)
		{
			B1.BottomRight()=b1.BottomRight();
			B1.left=b1.left;
			B1.top=b1.bottom-a;
		}
		//El que esta al lado
		if (b>0)
		{
			B2.right=b1.right;
			B2.left=b1.right-b;
			B2.bottom=b1.bottom-a;
			if (c>0) B2.top=b1.top+c;
				else B2.top=b1.top;
		}
		if (c>0)
		{
			B3.right=b1.right;
			B3.left=b1.left;
			B3.bottom=b1.top+c;
			B3.top=b1.top;
		}
		return 1;
	}
	//Caso RecTemp dentro de b1 por la derecha
	if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.left>b1.left) && (b2.left<=b1.right) && (b2.right>=b1.right)) ||
	((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.left>b1.left) && (b2.left<=b1.right)&& (b2.right>=b1.right)))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b1.right-b2.left));
		int c=((b2.top-b1.top));
		if (a<0) a=0;
		if (b<0) b=0;
		if (c<0) c=0;
		//El que esta por encima;
		if (a>0)
		{
			B1.BottomRight()=b1.BottomRight();
			B1.left=b1.left;
			B1.top=b1.bottom-a;
		}
		//El que esta al lado
		if (b>0)
		{
			B2.left=b1.left;
			B2.right=b1.right-b;
			B2.bottom=b1.bottom-a;
			if (c>0) B2.top=b1.top+c;
				else B2.top=b1.top;
		}
		if (c>0)
		{
			B3.right=b1.right;
			B3.left=b1.left;
			B3.bottom=b1.top+c;
			B3.top=b1.top;
		}
		return 1;
	}
	//Caso RecTemp dentro de b1 por  abajo
	if ((b2.bottom<b1.bottom) && (b2.bottom>b1.top) && (b2.top<=b1.top) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom));
		int b=((b1.right-b2.right));
		int c=((b2.left-b1.left));
		//El que esta por debajo;
		if (a>0)
		{
			B1.top=b2.bottom;
			B1.bottom=b1.bottom;
			B1.right=b1.right;
			B1.left=b1.left;
		}
		//El que esta al lado derecho
		if (b>0)
		{
			B2.left=b1.right-b;
			B2.right=b1.right;
			B2.top=b1.top;
			B2.bottom=b1.bottom-a;
		}
		//El que esta al lado izquierdo
		if (c>0)
		{
			B3.right=b2.left;
			B3.left=b1.left;
			B3.top=b1.top;
			B3.bottom=b1.bottom-a;
		}
		return 1;
	}

	//Caso RecTemp dentro de b1 por arriba
	if ((b2.top<b1.bottom) && (b2.top>b1.top) && (b2.bottom>=b1.bottom) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
	{
		//Crear bLOQUE
		int a=((b1.bottom-b2.top));
		int b=((b1.right-b2.right));
		int c=((b2.left-b1.left));
		//El que esta por debajo;
		if (a>0)
		{
			B1.top=b1.top;
			B1.bottom=b1.bottom-a;
			B1.right=b1.right;
			B1.left=b1.left;
		}
		//El que esta al lado derecho
		if (b>0)
		{
			B2.left=b1.right-b;
			B2.right=b1.right;
			B2.top=b1.bottom-a;
			B2.bottom=b1.bottom;
		}
		//El que esta al lado izquierdo
		if (c>0)
		{
			B3.left=b1.left;
			B3.right=b2.left;
			B3.top=b1.bottom-a;
			B3.bottom=b1.bottom;
		}
		return 1;
	}
	//Caso RecTemp parte en dos verticales b1 
	if ((b2.top<=b1.top) && (b2.bottom>=b1.bottom) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
	{
		//Crear BLOQUEs
		int a=0;
		int b=((b1.right-b2.right));
		int c=((b2.left-b1.left));
		//El que esta por debajo;
		if (a>0)
		{
			B1.top=b1.top;
			B1.bottom=b1.bottom-a;
			B1.right=b1.right;
			B1.left=b1.left;
		}
		//El que esta al lado derecho
		if (b>0)
		{
			B2.left=b1.right-b;
			B2.right=b1.right;
			B2.top=b1.top;
			B2.bottom=b1.bottom;
		}
		//El que esta al lado izquierdo
		if (c>0)
		{
			B3.right=b2.left;
			B3.left=b1.left;
			B3.top=b1.top;
			B3.bottom=b1.bottom;
		}
		return 1;
	}
	//Caso RecTemp dentro de b1
	//Aqui cuatro rectángulos
	if ((b2.top>b1.top) && (b2.bottom<b1.bottom) && (b2.left>b1.left) && (b2.right<b1.right))
	{
		//Crear BLOQUEs
		//El que esta por debajo;
		B1.top=b1.top;
		B1.bottom=b2.top;
		B1.right=b1.right;
		B1.left=b1.left;
		//El que esta al lado derecho
		B2.left=b2.right;
		B2.right=b1.right;
		B2.top=b2.top;
		B2.bottom=b2.bottom;
		//El que esta al lado izquierdo
		B3.right=b2.left;
		B3.left=b1.left;
		B3.top=b2.top;
		B3.bottom=b2.bottom;
		//El que esta arriba
		B4.right=b1.right;
		B4.left=b1.left;
		B4.top=b2.bottom;
		B4.bottom=b1.bottom;
		return 1;
	}
	return 0;
}

void PALLET::Actualizar_Perdida(std::list<BLOQUE> &listaBlo,std::list<CRect> &listaPer)
{
	std::list<BLOQUE> ::iterator itB;
	std::list<CRect> ::iterator itL;
	CRect RectTemp;
	//Construyo rectangulos de pérdida con los bordes
	for (itB=listaBlo.begin();itB!=listaBlo.end();itB++)
	{
//		BLOQUE bloque=(*itB);
		itL=listaPer.begin();
		do{
//			CRect Perdida=(*itL);
			CRect B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
			CRect b1=(*itL);
			CRect b2=(*itB);
			int corta=Restar_Rectangulo(b1,b2,B1,B2,B3,B4);
			//No se cortan
			if (corta!=0)
			{
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				if (B4.IsRectEmpty()==0) listaPer.push_back(B4);
				itL=listaPer.erase(itL);
				continue;
			}


			itL++;
		}while(itL!=listaPer.end());
	}
}
/*
void PALLET::Actualizar_Perdida(std::list<BLOQUE> &listaBlo,std::list<CRect> &listaPer)
{
	std::list<BLOQUE> ::iterator itB;
	std::list<CRect> ::iterator itL;
	CRect RectTemp;
	//Construyo rectangulos de pérdida con los bordes
	for (itB=listaBlo.begin();itB!=listaBlo.end();itB++)
	{
		BLOQUE bloque=(*itB);
		itL=listaPer.begin();
		do{
			CRect PTotal=(*itL);
			IntersectRect(&RectTemp,&PTotal,&bloque);
			if (RectTemp.IsRectEmpty())
			{
				itL++;
				continue;
			}
			//Si el bloque esta dentro de la intersección
			//me crea dos nuevos rectangulos
			//!!!Falta los casos donde los bloques estan en medio 
			//de la perdida sobrante
			CPoint bloqueTL=RectTemp.TopLeft();
			CPoint bloqueBR=RectTemp.BottomRight();
			CPoint PTotalTL=PTotal.TopLeft();
			CPoint PTotalBR=PTotal.BottomRight();
			//Cuatro caso
			if (bloqueTL==PTotalTL)
			{
				//Esquina de arriba izquierda
				//Ahora dos rectangulos
				CRect Nuevo1(bloqueTL.x,bloqueBR.y,PTotalBR.x,PTotalBR.y);
				CRect Nuevo2(bloqueBR.x,bloqueTL.y,PTotalBR.x,bloqueBR.y);
				if (!Nuevo1.IsRectEmpty()) listaPer.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) listaPer.push_back(Nuevo2);
				itL=listaPer.erase(itL);

				continue;
				
			}
			if (bloqueBR==PTotalBR)
			{
				//Esquina de abajo derecha
				CRect Nuevo1(PTotalTL.x,PTotalTL.y,PTotalBR.x,bloqueTL.y);
				CRect Nuevo2(PTotalTL.x,bloqueTL.y,bloqueTL.x,bloqueBR.y);
				if (!Nuevo1.IsRectEmpty()) listaPer.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) listaPer.push_back(Nuevo2);
				itL=listaPer.erase(itL);
				continue;

			}
			if ((bloqueTL.x==PTotalTL.x) && (bloqueBR.y==PTotalBR.y))
			{
				//Esquina izquierda abajo
				CRect Nuevo1(PTotalTL.x,PTotalTL.y,PTotalBR.x,bloqueTL.y);
				CRect Nuevo2(bloqueBR.x,bloqueTL.y,PTotalBR.x,PTotalBR.y);
				if (!Nuevo1.IsRectEmpty()) listaPer.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) listaPer.push_back(Nuevo2);
				itL=listaPer.erase(itL);
				continue;

			}
			if ((bloqueTL.y==PTotalTL.y) && (bloqueBR.x==PTotalBR.x))
			{
				//Esquina arriba derecha
				CRect Nuevo1(PTotalTL.x,PTotalTL.y,bloqueTL.x,bloqueBR.y);
				CRect Nuevo2(PTotalTL.x,bloqueBR.y,PTotalBR.x,PTotalBR.y);
				(*itL)=Nuevo1;
				if (Nuevo1.IsRectEmpty()) itL=listaPer.erase(itL);
				if (!Nuevo2.IsRectEmpty()) listaPer.push_back(Nuevo2);
				continue;

			}
			//Casos donde se crean tres nuevos rectángulos
			//Caso RecTemp dentro de PTotal por la izquierda
			CRect B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0);
			CRect b2=bloque,b1=PTotal;
			if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)) ||
			((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)))
			{
				//Crear bLOQUE
				int a=((b1.bottom-b2.bottom));
				int b=((b1.right-b2.right));
				int c=((b2.top-b1.top));
				if (a<0) a=0;
				if (b<0) b=0;
				if (c<0) c=0;

				//El que esta por encima;
				if (a>0)
				{
					B1.BottomRight()=b1.BottomRight();
					B1.left=b1.left;
					B1.top=b1.bottom-a;
				}
				//El que esta al lado
				if (b>0)
				{
					B2.right=b1.right;
					B2.left=b1.right-b;
					B2.bottom=b1.bottom-a;
					if (c>0) B2.top=b1.top+c;
						else B2.top=b1.top;
				}
				if (c>0)
				{
					B3.right=b1.right;
					B3.left=b1.left;
					B3.bottom=b1.top+c;
					B3.top=b1.top;
				}
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				itL=listaPer.erase(itL);
				continue;
			}
			//Caso RecTemp dentro de PTotal por la derecha
			if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.left>b1.left) && (b2.left<=b1.right) && (b2.right>=b1.right)) ||
			((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.left>b1.left) && (b2.left<=b1.right)&& (b2.right>=b1.right)))
			{
				//Crear bLOQUE
				int a=((b1.bottom-b2.bottom));
				int b=((b1.right-b2.left));
				int c=((b2.top-b1.top));
				if (a<0) a=0;
				if (b<0) b=0;
				if (c<0) c=0;

				//El que esta por encima;
				if (a>0)
				{
					B1.BottomRight()=b1.BottomRight();
					B1.left=b1.left;
					B1.top=b1.bottom-a;
				}
				//El que esta al lado
				if (b>0)
				{
					B2.left=b1.left;
					B2.right=b1.right-b;
					B2.bottom=b1.bottom-a;
					if (c>0) B2.top=b1.top+c;
						else B2.top=b1.top;
				}
				if (c>0)
				{
					B3.right=b1.right;
					B3.left=b1.left;
					B3.bottom=b1.top+c;
					B3.top=b1.top;
				}
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				itL=listaPer.erase(itL);
				continue;
			}
			//Caso RecTemp dentro de PTotal por  abajo
			if ((b2.bottom<b1.bottom) && (b2.bottom>b1.top) && (b2.top<=b1.top) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
			{
				//Crear bLOQUE
				int a=((b1.bottom-b2.bottom));
				int b=((b1.right-b2.right));
				int c=((b2.left-b1.left));
				//El que esta por debajo;
				if (a>0)
				{
					B1.top=b2.bottom;
					B1.bottom=b1.bottom;
					B1.right=b1.right;
					B1.left=b1.left;
				}
				//El que esta al lado derecho
				if (b>0)
				{
					B2.left=b1.right-b;
					B2.right=b1.right;
					B2.top=b1.top;
					B2.bottom=b1.bottom-a;
				}
				//El que esta al lado izquierdo
				if (c>0)
				{
					B3.right=b2.left;
					B3.left=b1.left;
					B3.top=b1.top;
					B3.bottom=b1.bottom-a;
				}
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				itL=listaPer.erase(itL);
				continue;
			}

			//Caso RecTemp dentro de PTotal por arriba
			if ((b2.top<b1.bottom) && (b2.top>b1.top) && (b2.bottom>=b1.bottom) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
			{
				//Crear bLOQUE
				int a=((b1.bottom-b2.top));
				int b=((b1.right-b2.right));
				int c=((b2.left-b1.left));
				//El que esta por debajo;
				if (a>0)
				{
					B1.top=b1.top;
					B1.bottom=b1.bottom-a;
					B1.right=b1.right;
					B1.left=b1.left;
				}
				//El que esta al lado derecho
				if (b>0)
				{
					B2.left=b1.right-b;
					B2.right=b1.right;
					B2.top=b1.bottom-a;
					B2.bottom=b1.bottom;
				}
				//El que esta al lado izquierdo
				if (c>0)
				{
					B3.left=b1.left;
					B3.right=b2.left;
					B3.top=b1.bottom-a;
					B3.bottom=b1.bottom;
				}
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				itL=listaPer.erase(itL);
				continue;
			}
			//Caso RecTemp parte en dos verticales PTotal 
			if ((b2.top<=b1.top) && (b2.bottom>=b1.bottom) && (b2.left>b1.left) && (b2.left<b1.right) && (b2.right>b1.left) && (b2.right<b1.right))
			{
				//Crear BLOQUEs
				int a=0;
				int b=((b1.right-b2.right));
				int c=((b2.left-b1.left));
				//El que esta por debajo;
				if (a>0)
				{
					B1.top=b1.top;
					B1.bottom=b1.bottom-a;
					B1.right=b1.right;
					B1.left=b1.left;
				}
				//El que esta al lado derecho
				if (b>0)
				{
					B2.left=b1.right-b;
					B2.right=b1.right;
					B2.top=b1.top;
					B2.bottom=b1.bottom;
				}
				//El que esta al lado izquierdo
				if (c>0)
				{
					B3.right=b2.left;
					B3.left=b1.left;
					B3.top=b1.top;
					B3.bottom=b1.bottom;
				}
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				itL=listaPer.erase(itL);
				continue;
			}
			//Caso RecTemp dentro de PTotal
			//Aqui cuatro rectángulos
			if ((b2.top>b1.top) && (b2.bottom<b1.bottom) && (b2.left>b1.left) && (b2.right<b1.right))
			{
				CRect B4(0,0,0,0);
				//Crear BLOQUEs
				//El que esta por debajo;
				B1.top=b1.top;
				B1.bottom=b2.top;
				B1.right=b1.right;
				B1.left=b1.left;
				//El que esta al lado derecho
				B2.left=b2.right;
				B2.right=b1.right;
				B2.top=b2.top;
				B2.bottom=b2.bottom;
				//El que esta al lado izquierdo
				B3.right=b2.left;
				B3.left=b1.left;
				B3.top=b2.top;
				B3.bottom=b2.bottom;
				//El que esta arriba
				B4.right=b1.right;
				B4.left=b1.left;
				B4.top=b2.bottom;
				B4.bottom=b1.bottom;
				if (B1.IsRectEmpty()==0) listaPer.push_back(B1);
				if (B2.IsRectEmpty()==0) listaPer.push_back(B2);
				if (B3.IsRectEmpty()==0) listaPer.push_back(B3);
				if (B4.IsRectEmpty()==0) listaPer.push_back(B4);
				itL=listaPer.erase(itL);
				continue;
			}

		itL++;
		}while(itL!=listaPer.end());

	}
}*/
std::list<BLOQUE> PALLET::Construir_Bloques(intervalo solu)
{
	std::list<BLOQUE> lista_bloques;
	//Primer Bloque
	if (solu[0]>0 && solu[1]>0)
	{
	BLOQUE bloque1(0,0,solu[0]*m_l,solu[1]*m_w,'H');
	lista_bloques.push_back(bloque1);
	}
	//Segundo Bloque
	if (solu[2]>0 && solu[3]>0)
	{

	BLOQUE bloque2(m_L-solu[2]*m_w,0,m_L,m_W-solu[3]*m_l,'V');
	lista_bloques.push_back(bloque2);
	}
	//Tercer Bloque
	if (solu[4]>0 && solu[5]>0)
	{
	BLOQUE bloque3(m_L-solu[4]*m_l,m_W-solu[5]*m_w,m_L,m_W,'H');
	lista_bloques.push_back(bloque3);
	}
	//Cuarto Bloque
	if (solu[6]>0 && solu[7]>0)
	{
	BLOQUE bloque4(0,m_W-(solu[7]*m_l),solu[6]*m_w,m_W,'V');
	lista_bloques.push_back(bloque4);
	}
	return lista_bloques;
}
std::list<CRect> PALLET::PerdidasBloques(BLOQUE &B1,BLOQUE &B2)
{
	std::list<CRect> lista;
	CRect RectTemp;
	IntersectRect(&RectTemp,&B1,&B2);
	if (RectTemp.IsRectEmpty()) return lista;
	//Si el bloque esta dentro de la intersección
	//me crea dos nuevos rectangulos
	//!!!Falta los casos donde los bloques estan en medio 
			//de la perdida sobrante
	CPoint bloqueTL=RectTemp.TopLeft();
	CPoint bloqueBR=RectTemp.BottomRight();
	CPoint PTotalTL=B1.TopLeft();
	CPoint PTotalBR=B1.BottomRight();
	//Cuatro caso
	if (bloqueTL==PTotalTL)
	{
		//Esquina de arriba izquierda
		//Ahora dos rectangulos
		CRect Nuevo1(bloqueTL.x,bloqueBR.y,PTotalBR.x,PTotalBR.y);
		CRect Nuevo2(bloqueBR.x,bloqueTL.y,PTotalBR.x,bloqueBR.y);
		if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo2);
		if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
		return lista;
	}
	if (bloqueBR==PTotalBR)
	{
		//Esquina de abajo derecha
		CRect Nuevo1(PTotalTL.x,PTotalTL.y,PTotalBR.x,bloqueTL.y);
		CRect Nuevo2(PTotalTL.x,bloqueTL.y,bloqueTL.x,bloqueBR.y);
		if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo2);
		if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
		return lista;

	}
	if ((bloqueTL.x==PTotalTL.x) && (bloqueBR.y==PTotalBR.y))
	{
		//Esquina izquierda abajo
		CRect Nuevo1(PTotalTL.x,PTotalTL.y,PTotalBR.x,bloqueTL.y);
		CRect Nuevo2(bloqueBR.x,bloqueTL.y,PTotalBR.x,PTotalBR.y);
		if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo2);
		if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
		return lista;

	}
	if ((bloqueTL.y==PTotalTL.y) && (bloqueBR.x==PTotalBR.x))
	{
		//Esquina arriba derecha
		CRect Nuevo1(PTotalTL.x,PTotalTL.y,bloqueTL.x,bloqueBR.y);
		CRect Nuevo2(PTotalTL.x,bloqueBR.y,PTotalBR.x,PTotalBR.y);
		if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo2);
		if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
		return lista;

	}
	return lista;
}

/*
MOVE PALLET::Aumentar_Bloques(BLOQUE &B1,int xder,int xizq,int yarr, int yaba)
{
	BLOQUE B1Aumentado(0,0,0,0,B1.GetTipo());
	int x=0,y=0;
	//Estudio por donde es mejor dividirlo derecha o izquierda o 
	//arriba o abajo
	//Según donde termine el bloque lo disminuyo 
	//para un lado o para el otro
	int l,w;
	std::list<CRect> NuevasPerdidas;
	CRect RectTemp;
	int Quito=0,Meto=0;	
/*	if (x>0) derecha=PorDondeDisminuir(B1,x,y);
	if (y>0) arriba=PorDondeDisminuir(B1,x,y);*/
/*	if (B1.GetTipo()=='H')
	{
		l=m_l;
		w=m_w;
	}
	else
	{
		l=m_w;
		w=m_l;
	}
	B1Dismi.BottomRight()=B1.BottomRight();
	B1Dismi.TopLeft()=B1.TopLeft();
	B1Dismi.SetTipo(B1.GetTipo());
	x=xder+xizq;
	y=yarr+yaba;
	Quito=x*(B1.Height()/w)+y*(B1.Width()/l)-(x*y);
	if (xder>0) 	B1Dismi.BottomRight().x=B1.BottomRight().x+(x*l);
	if (xizq>0) 	B1Dismi.TopLeft().x=B1.TopLeft().x-(x*l);
	if (yarr>0)		B1Dismi.BottomRight().y=B1.BottomRight().y+(y*w);
	if (yaba>0) 	B1Dismi.TopLeft().y=B1.TopLeft().y-(y*w);*/
//Tengo que tener una función que me reduzca el resto de bloques,
// es decir todo lo que intersecte lo elimina

	
//	std::list<CRect> NuevasPerdidas=PerdidasBloques(B1,B1Dismi);

/*
	std::list<CRect> NuevasPerdidasC=CompactarPerdida(NuevasPerdidas);
//	int perdida=Contar(NuevasPerdidasC);
	std::list<CRect> NuevasPerdidasC1=JuntarPerdida(NuevasPerdidasC);
//	std::list<CRect> NuevasPerdidasC1=CompactarPerdida(NuevasPerdidasCJ);
	std::list<BLOQUE> lista=Paletizar(NuevasPerdidasC1,B1.GetTipo());
	std::list<BLOQUE> ::iterator itB;
//	if (lista.size()==1 && B1Dismi.IsRectEmpty()) B1Dismi=*lista.begin();
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		BLOQUE b=(*itB);
		Meto+=(((*itB).Width()*(*itB).Height())/(m_l*m_w));	
	}
	
	//Los que no metan nada nuevo en el pallet nos los quiero
	if (Meto==0) Meto=-10;
	MOVE movimiento(B1,B1Dismi,lista,(Meto-Quito),NuevasPerdidasC1);
	return movimiento;
}*/
/*
MOVE PALLET::Disminuir_Bloques(BLOQUE &B1,int xder,int xizq,int yarr, int yaba)
{
	BLOQUE B1Dismi(0,0,0,0,B1.GetTipo()),B1Dismi2(0,0,0,0,B1.GetTipo());
	char tipo='V',tipo2='H';
	int x=0,y=0;
	//Estudio por donde es mejor dividirlo derecha o izquierda o 
	//arriba o abajo
	//Según donde termine el bloque lo disminuyo 
	//para un lado o para el otro
	int l,w;
	std::list<CRect> NuevasPerdidas;
	CRect RectTemp;
	int Quito=0,Meto=0,Meto2=0;	
	if (B1.GetTipo()=='H')
	{
		l=m_l;
		w=m_w;
	}
	else
	{
		l=m_w;
		w=m_l;
		tipo='H';
		tipo2='V';
	}
	B1Dismi.BottomRight()=B1.BottomRight();
	B1Dismi.TopLeft()=B1.TopLeft();
	B1Dismi.SetTipo(B1.GetTipo());

	x=xder+xizq;
	y=yarr+yaba;
	if (x==0 || y==0)
	{
		Quito=x*(B1.Height()/w)+y*(B1.Width()/l)-(x*y);
		if (xder>0) 	B1Dismi.BottomRight().x=B1.BottomRight().x-(x*l);
		if (xizq>0) 	B1Dismi.TopLeft().x=B1.TopLeft().x+(x*l);
		if (yarr>0)		B1Dismi.BottomRight().y=B1.BottomRight().y-(y*w);
		if (yaba>0) 	B1Dismi.TopLeft().y=B1.TopLeft().y+(y*w);
	}
	else
	{
		B1Dismi2.BottomRight()=B1.BottomRight();
		B1Dismi2.TopLeft()=B1.TopLeft();
		B1Dismi2.SetTipo(B1.GetTipo());
		//Cuatro casos depende de que esquina se reduzca
		if (xder>0 && yarr>0)//esquina superior derecha
		{
			B1Dismi2.top=B1Dismi.bottom-(w*yarr);
			B1Dismi2.right=B1Dismi.right-(l*xder);
			B1Dismi.bottom=B1Dismi2.top;
		}
		if (xder>0 && yaba>0)//esquina superior derecha
		{
			B1Dismi2.bottom=B1Dismi.top+(w*yarr);
			B1Dismi2.right=B1Dismi.right-(l*xder);
			B1Dismi.top=B1Dismi2.bottom;
		}
		if (xizq>0 && yarr>0)//esquina superior derecha
		{
			B1Dismi2.top=B1Dismi.bottom-(w*yarr);
			B1Dismi2.left=B1Dismi.left+(l*xder);
			B1Dismi.bottom=B1Dismi2.top;
		}
		if (xizq>0 && yaba>0)//esquina superior derecha
		{
			B1Dismi2.bottom=B1Dismi.top+(w*yarr);
			B1Dismi2.left=B1Dismi.left+(l*xder);
			B1Dismi.top=B1Dismi2.bottom;
		}

	}
	if (x*y>0)//Caso en el que se reduce a ambos lados
	{
		SubtractRect(&RectTemp,&B1,&B1Dismi);
		SubtractRect(&RectTemp,&B1,&B1Dismi2);
		if (!RectTemp.IsRectEmpty()) NuevasPerdidas.push_back(RectTemp);
	}
	else
	{
		SubtractRect(&RectTemp,&B1,&B1Dismi);
		if (!RectTemp.IsRectEmpty()) NuevasPerdidas.push_back(RectTemp);

	}
	
	std::list<CRect>::iterator itC;

	NuevasPerdidas.insert(NuevasPerdidas.begin(),m_lista_perdidas.begin(),m_lista_perdidas.end());
	CompactarPerdida(NuevasPerdidas);
	std::list<BLOQUE> ::iterator itB;

//	int perdida=Contar(NuevasPerdidasC);
	//Primero pruebo de una manera y después de la otra
	std::list<CRect> NuevasPerdidasC1=JuntarPerdida(NuevasPerdidas,tipo);
	CompactarPerdida(NuevasPerdidasC1);
	std::list<BLOQUE> lista=Paletizar(NuevasPerdidasC1,B1.GetTipo());
	Meto=Contar(lista);
	MOVE movimiento;
	if (NuevasPerdidas.size()>1)
	{
		//Segundo pruebo en el otro sentido
		std::list<CRect> NuevasPerdidasC12=JuntarPerdida(NuevasPerdidas,tipo2);
		CompactarPerdida(NuevasPerdidasC12);
		if (Lista_de_Perdidas_Iguales(NuevasPerdidasC12,NuevasPerdidasC1)==false)
		{
			std::list<BLOQUE> lista2=Paletizar(NuevasPerdidasC12,B1.GetTipo());
			Meto2=Contar(lista2);
			if (Meto<Meto2)
			{
				std::list<CRect> NuevasPerdidasC2=JuntarPerdida(NuevasPerdidasC12,tipo_union);
				MOVE movimiento2(B1,B1Dismi,lista2,(Meto2-Quito),NuevasPerdidasC2);
				movimiento.Igual(movimiento2);
//				Bloques_Hacia_Las_Esquinas(movimiento);
				CompactarBloques(movimiento,true);
				Bloques_Hacia_Las_Esquinas(movimiento);
				JuntarPerdida(movimiento.GetListaPerdidas());
				CompactarBloques(movimiento,false);
				Bloques_Hacia_Las_Esquinas(movimiento);
				CompactarBloques(movimiento,false);


				int per=Contar(movimiento.GetListaPerdidas());
				int sol=Contar(movimiento.GetBloquesNuevos());
				if (per!=((m_L*m_W)-(Meto*m_l*m_w)))
					int mil=1000;
				assert(per==((m_L*m_W)-(sol*m_l*m_w)));

				if (Meto2<=0) movimiento.SetAlgoNuevo(false);
				return movimiento;
			}
		}

	}
	
	std::list<CRect> NuevasPerdidasC2=JuntarPerdida(NuevasPerdidasC1,tipo_union);

	MOVE movimiento3(B1,B1Dismi,lista,(Meto-Quito),NuevasPerdidasC2);
	movimiento.Igual(movimiento3);
	CompactarBloques(movimiento,true);

	Bloques_Hacia_Las_Esquinas(movimiento);

	int per=Contar(movimiento.GetListaPerdidas());
	int sol=Contar(movimiento.GetBloquesNuevos());
	JuntarPerdida(movimiento.GetListaPerdidas());
	CompactarBloques(movimiento,false);
	Bloques_Hacia_Las_Esquinas(movimiento);
	CompactarBloques(movimiento,false);

	if (Meto<=0) movimiento.SetAlgoNuevo(false);
	//No he metido nada nuevo


//	lista.clear();
//	BloquesNoEficientes(movimiento);
	return movimiento;
}
*/
MOVE PALLET::Disminuir_Bloques(BLOQUE &B1,int xder,int xizq,int yarr, int yaba)
{
	BLOQUE B1Dismi(0,0,0,0,B1.GetTipo()),B1Dismi2(0,0,0,0,B1.GetTipo());
	char tipo='V',tipo2='H';
	int x=0,y=0;
	//Estudio por donde es mejor dividirlo derecha o izquierda o 
	//arriba o abajo
	//Según donde termine el bloque lo disminuyo 
	//para un lado o para el otro
	int l,w;
	std::list<CRect> NuevasPerdidas;
	CRect RectTemp;
	int Quito=0,Meto=0,Meto2=0;	
/*	if (x>0) derecha=PorDondeDisminuir(B1,x,y);
	if (y>0) arriba=PorDondeDisminuir(B1,x,y);*/
	if (B1.GetTipo()=='H')
	{
		l=m_l;
		w=m_w;
	}
	else
	{
		l=m_w;
		w=m_l;
		tipo='H';
		tipo2='V';
	}
	B1Dismi.BottomRight()=B1.BottomRight();
	B1Dismi.TopLeft()=B1.TopLeft();
	B1Dismi.SetTipo(B1.GetTipo());

	x=xder+xizq;
	y=yarr+yaba;
	if (x==0 || y==0)
	{
		Quito=x*(B1.Height()/w)+y*(B1.Width()/l)-(x*y);
		if (xder>0) 	B1Dismi.BottomRight().x=B1.BottomRight().x-(x*l);
		if (xizq>0) 	B1Dismi.TopLeft().x=B1.TopLeft().x+(x*l);
		if (yarr>0)		B1Dismi.BottomRight().y=B1.BottomRight().y-(y*w);
		if (yaba>0) 	B1Dismi.TopLeft().y=B1.TopLeft().y+(y*w);
	}
	else
	{
		B1Dismi2.BottomRight()=B1.BottomRight();
		B1Dismi2.TopLeft()=B1.TopLeft();
		B1Dismi2.SetTipo(B1.GetTipo());
		//Cuatro casos depende de que esquina se reduzca
		if (xder>0 && yarr>0)//esquina superior derecha
		{
			B1Dismi2.top=B1Dismi.bottom-(w*yarr);
			B1Dismi2.right=B1Dismi.right-(l*xder);
			B1Dismi.bottom=B1Dismi2.top;
		}
		if (xder>0 && yaba>0)//esquina superior derecha
		{
			B1Dismi2.bottom=B1Dismi.top+(w*yaba);
			B1Dismi2.right=B1Dismi.right-(l*xder);
			B1Dismi.top=B1Dismi2.bottom;
		}
		if (xizq>0 && yarr>0)//esquina superior derecha
		{
			B1Dismi2.top=B1Dismi.bottom-(w*yarr);
			B1Dismi2.left=B1Dismi.left+(l*xizq);
			B1Dismi.bottom=B1Dismi2.top;
		}
		if (xizq>0 && yaba>0)//esquina superior derecha
		{
			B1Dismi2.bottom=B1Dismi.top+(w*yaba);
			B1Dismi2.left=B1Dismi.left+(l*xizq);
			B1Dismi.top=B1Dismi2.bottom;
		}

	}
	if (x*y>0)//Caso en el que se reduce a ambos lados
	{
		SubtractRect(&RectTemp,&B1,&B1Dismi);
		SubtractRect(&RectTemp,&RectTemp,&B1Dismi2);
		Quito=((RectTemp.Width()*RectTemp.Height())/(l*w));
		if (!RectTemp.IsRectEmpty()) NuevasPerdidas.push_back(RectTemp);
	}
	else
	{
		SubtractRect(&RectTemp,&B1,&B1Dismi);
		if (!RectTemp.IsRectEmpty()) NuevasPerdidas.push_back(RectTemp);

	}
	
	std::list<CRect>::iterator itC;
	std::list<BLOQUE> lista_temp_bloques;
	std::list<BLOQUE> :: iterator itLK;
	lista_temp_bloques.insert(lista_temp_bloques.begin(),m_lista_bloques.begin(),m_lista_bloques.end());
	if (x*y>0)//Caso en el que se reduce a ambos lados
	{
		lista_temp_bloques.push_back(B1Dismi2);		
	}

	lista_temp_bloques.push_back(B1Dismi);
	itLK=lista_temp_bloques.begin();
	do{
		if ((*itLK).IsRectEmpty()!=0)
		{
			itLK=lista_temp_bloques.erase(itLK);
			continue;
		}
		if ((*itLK).EqualRect(B1)) 
		{
			itLK=lista_temp_bloques.erase(itLK);
			continue;
		}
		itLK++;

	}while(itLK!=lista_temp_bloques.end());
	NuevasPerdidas.insert(NuevasPerdidas.end(),m_lista_perdidas.begin(),m_lista_perdidas.end());
	CompactarPerdida(NuevasPerdidas);

//	JuntarPerdida(NuevasPerdidas);
	if (m_iter_actual==3)
		int kkkk=8;
//	DibujarSolucion(lista_temp_bloques,NuevasPerdidas,9999,9999);
//	if (m_iter_actual==3 && B1.top==0 && B1.left==0 && B1.right==20  && B1.bottom==24 && xder==12)
//		int gato=9;	

	//Quito esto today
//	Bloques_Hacia_Las_Esquinas(lista_temp_bloques,NuevasPerdidas);
//	DibujarSolucion(lista_temp_bloques,NuevasPerdidas,4444,4444);

//	if (m_iter_actual==21) DibujarSolucion(lista_temp_bloques,NuevasPerdidas,1111,1111);
	//Aqui tengo que quitar para quedarme con solo los de un lado 
	//porque se ha desplazado el bloque donde ya lo vamos a hacer 
	//posteriormente.
	int Val=0;
	std::list<CRect>::iterator itB;
	for(itB=NuevasPerdidas.begin();itB!=NuevasPerdidas.end();itB++)
	{
		if (((*itB).Width()>m_l && (*itB).Height()>m_w) || ((*itB).Width()>m_w && (*itB).Height()>m_l))

		Val+=1;
	}
	if (Val>=2) 
		int kkk=9;
	
	BLOQUE B2(0,0,0,0,B1.GetTipo());
	B2.BottomRight()=B1.BottomRight();
	B2.TopLeft()=B1.TopLeft();
	double m_Lmedios=(double)m_L/(double)2;
	double m_Wmedios=(double)m_W/(double)2;
	bool mi_blo=false;

	CompactarPerdida(NuevasPerdidas);
//	std::list<CRect> NuevasPerdidas_suple=NuevasPerdidas;

//	std::list<BLOQUE> ::iterator itB;
	bool probar_otro=false;
//	int perdida=Contar(NuevasPerdidasC);
	//Primero pruebo de una manera y después de la otra

//Funciona mejora la primera el tipo para diversificar	
//	if (m_iter_actual%3==0) m_tipo_junta=2;
//	else m_tipo_junta=1;
	m_tipo_junta=1;
//	m_tipo_junta=2;
	std::list<CRect> NuevasPerdidasC1=JuntarPerdida(NuevasPerdidas,tipo);
	CompactarPerdida(NuevasPerdidasC1);
	
//	std::list<CRect> NuevasPerdidasC1_suple1=NuevasPerdidasC1;
//	m_tipo_junta=2;
	//Segundo pruebo en el otro sentido
//	m_tipo_junta=2;
	if (B1.top==0 && B1.bottom==32 && B1.left==0  && B1.right==70  && xder==10)
		int jjj=9;

//	m_tipo_junta=2;
//	std::list<CRect> NuevasPerdidasC13=JuntarPerdida(NuevasPerdidas,tipo);
//	CompactarPerdida(NuevasPerdidasC13);
//	m_tipo_junta=2;
//	std::list<CRect> NuevasPerdidasC12_suple1=NuevasPerdidasC12;
	std::list<BLOQUE> lista=Paletizar(NuevasPerdidasC1,B1.GetTipo());
	Meto=Contar(lista);
	MOVE movimiento;
	if (m_sol_actual==10000)
	{
		std::list<CRect> NuevasPerdidasC12=JuntarPerdida(NuevasPerdidas,tipo2);
		CompactarPerdida(NuevasPerdidasC12);
		if (Lista_de_Perdidas_Iguales(NuevasPerdidasC12,NuevasPerdidasC1)==false)
		{
			probar_otro=true;
		}
	//	printf("kk");
	//	if (m_iter_actual==4)	DibujarSolucion(lista_temp_bloques,NuevasPerdidasC1,1000,1000);
	//	probar_otro=false;

		if (probar_otro==true )
		{
			if (m_iter_actual==76 && B1.top==0 && B1.bottom==18 && B1.left==0  && B1.right==40  && B1Dismi.bottom==0)
				int jjj=9;

			std::list<BLOQUE> lista2=Paletizar(NuevasPerdidasC12,B1.GetTipo());
			Meto2=Contar(lista2);
			if (Meto<Meto2)
			{
				if ((Meto2-Quito)<m_max_valor) 
				{
					movimiento.SetValor(-1000);
					return movimiento;
				}
/*				if (EstaLaPerdida(NuevasPerdidasC12,RectTemp)==true) 
				{
					movimiento.SetValor(-1000);
					return movimiento;
				}*/
//				for(int i=0;;i++) printf("mierda");
				std::list<CRect> NuevasPerdidasC2=JuntarPerdida(NuevasPerdidasC12,tipo_union);
//				std::list<BLOQUE> lista3=Paletizar(NuevasPerdidasC1_suple1,B1.GetTipo());
				lista2.insert(lista2.begin(),lista_temp_bloques.begin(),lista_temp_bloques.end());

				MOVE movimiento2(B1,B1Dismi,lista2,(Meto2-Quito),NuevasPerdidasC2);
				movimiento.Igual(movimiento2);
//				Bloques_Hacia_Las_Esquinas(movimiento);
				CompactarBloques(movimiento,false);
				Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());

				JuntarPerdida(movimiento.GetListaPerdidas());
				CompactarBloques(movimiento,false);
				Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
				CompactarBloques(movimiento,false);
/*				if (EstaElBloque(movimiento.GetListaBloques(),B1)==true) 
				{
					movimiento.SetValor(-1000);
					return movimiento;
				}*/

//				if (m_iter_actual==21) DibujarSolucion(lista_temp_bloques,NuevasPerdidas,1111,1111);
//				DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),1000,1000);

				VerificarSolucion(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),6);

				if (Meto2<=0) movimiento.SetAlgoNuevo(false);
				return movimiento;
			}

		}
	}
	if ((Meto-Quito)<m_max_valor) 
	{
		movimiento.SetValor(-1000);
		return movimiento;
	}
/*	if (EstaLaPerdida(NuevasPerdidasC1,RectTemp)==true) 
	{
		movimiento.SetValor(-1000);
		return movimiento;
	}*/
	std::list<CRect> NuevasPerdidasC2=JuntarPerdida(NuevasPerdidasC1,tipo_union);
	lista.insert(lista.begin(),lista_temp_bloques.begin(),lista_temp_bloques.end());
//	printf("%3d\t%3d\n",Meto,Quito);
	MOVE movimiento3(B1,B1Dismi,lista,(Meto-Quito),NuevasPerdidasC2);
	movimiento.Igual(movimiento3);
//	VerificarSolucion(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),44);
	CompactarBloques(movimiento,false);
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),7777,7777);

	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),8888,8888);
	VerificarSolucion(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),4);

	movimiento.SetValor(Contar(movimiento.GetListaBloques())-Contar(m_lista_bloques));
	JuntarPerdida(movimiento.GetListaPerdidas());
	CompactarBloques(movimiento,false);
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),1000,1000);

	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
	CompactarBloques(movimiento,false);
/*	if (EstaElBloque(movimiento.GetListaBloques(),B1)==true) 
	{
		movimiento.SetValor(-1000);
					return movimiento;
				}
*/
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),1000,1000);

//	Mejorar_Con_Bloques_G4(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//	if (m_iter_actual==21) DibujarSolucion(lista_temp_bloques,NuevasPerdidas,1111,1111);
	if (Meto<=0) movimiento.SetAlgoNuevo(false);
	return movimiento;
}
bool PALLET::Lista_de_Perdidas_Iguales(std::list<CRect> &lista,std::list<CRect> &lista2)
{
	std::list<CRect> ::iterator itL,itL2;
	bool esta_perdida=false;
	if (lista.size()!=lista2.size()) return false;
	for (itL=lista.begin();itL!=lista.end();itL++)
	{
		esta_perdida=false;
		for (itL2=lista2.begin();itL2!=lista2.end();itL2++)
		{
			if ((*itL2).EqualRect((*itL))!=0) esta_perdida=true;
			
		}
		if (esta_perdida==false) return false;
	}
	return true;

}
MOVE PALLET::Aumentar_Bloques(BLOQUE &B1,int xder,int xizq,int yarr, int yaba)
{

	BLOQUE B1Aumen(0,0,0,0,B1.GetTipo());
	int x=0,y=0;
	//Estudio por donde es mejor dividirlo derecha o izquierda o 
	//arriba o abajo
	//Según donde termine el bloque lo disminuyo 
	//para un lado o para el otro
	int l,w;
	std::list<CRect> NuevasPerdidas;
	std::list<BLOQUE> ::iterator itB;
	CRect RectTemp;
	int Quito=0,Meto=0;	
/*	if (x>0) derecha=PorDondeDisminuir(B1,x,y);
	if (y>0) arriba=PorDondeDisminuir(B1,x,y);*/
	if (B1.GetTipo()=='H')
	{
		l=m_l;
		w=m_w;
	}
	else
	{
		l=m_w;
		w=m_l;
	}
	B1Aumen.BottomRight()=B1.BottomRight();
	B1Aumen.TopLeft()=B1.TopLeft();
	B1Aumen.SetTipo(B1.GetTipo());
	x=xder+xizq;
	y=yarr+yaba;
//	Quito=x*(B1.Height()/w)+y*(B1.Width()/l)-(x*y);
	if (xder>0) 	B1Aumen.BottomRight().x=B1.BottomRight().x+(x*l);
	if (xizq>0) 	B1Aumen.TopLeft().x=B1.TopLeft().x-(x*l);
	if (yarr>0)		B1Aumen.BottomRight().y=B1.BottomRight().y+(y*w);
	if (yaba>0) 	B1Aumen.TopLeft().y=B1.TopLeft().y-(y*w);
	for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
//		BLOQUE b=(*itB);
		Quito+=(((*itB).Width()*(*itB).Height())/(m_l*m_w));	
	}

	MOVE movimiento(B1,B1Aumen,0);

	movimiento.GetListaPerdidas().clear();
	CRect PTotal(0,0,m_L,m_W);

	movimiento.GetListaPerdidas().push_back(PTotal);
	if (m_iter_actual==6 && B1.top==37 && B1.bottom==42 && B1.left==12  && B1.right==24  && yaba==3)
		int jjj=9;
	if (yaba==3 && B1.top==19 && B1.bottom==25 && B1.left==27  && B1.right==34 )
		int jjj=9;

	if (x*y>0)//Caso en el que se reduce a ambos lados
	{

	}
	else
	{
		//Tengo las nuevas pérdidas
//		if (m_iter_actual%2==0)	 AumentarBloque(movimiento,2);
//		else AumentarBloque(movimiento,1);
		AumentarBloque(movimiento,1);

	}

	movimiento.GetListaBloques().push_back(B1Aumen);
	Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);
	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),7);
	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),25);

	CompactarPerdida(movimiento.GetListaPerdidas());
	std::list<BLOQUE> lista=Paletizar(movimiento.GetListaPerdidas(),'X');
	movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());
	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),251);

	for(itB=movimiento.GetListaBloques().begin();itB!=movimiento.GetListaBloques().end();itB++)
	{
//		BLOQUE b=(*itB);
		Meto+=(((*itB).Width()*(*itB).Height())/(m_l*m_w));	
	}
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),555,555);
	if ((Meto-Quito)<m_max_valor) 
	{
		movimiento.SetValor(-1000);
		return movimiento;
	}

	movimiento.SetValor(Meto-Quito);

	CompactarBloques(movimiento,false);
	JuntarPerdida(movimiento.GetListaPerdidas());
	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
	JuntarPerdida(movimiento.GetListaPerdidas());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),555,555);

	VerificarSolucion(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),8);

	return movimiento;
}
void PALLET::AumentarBloque(MOVE &M1,int metodo)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	//Creo lista de pérdidas nuevas y lista de bloques nueva
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
//		BLOQUE b11=(*itB);
		//Los que esten incluidos dentro del nuevo rectángulo los quito
		if ((((*itB).bottom<=M1.GetBloqueNuevo().bottom) && ((*itB).top>=M1.GetBloqueNuevo().top))
		&& (((*itB).right<=M1.GetBloqueNuevo().right) && ((*itB).left>=M1.GetBloqueNuevo().left)))
			continue;
		if( (*itB).top>=M1.GetBloqueNuevo().bottom || M1.GetBloqueNuevo().top>=(*itB).bottom )
		{
			M1.GetListaBloques().push_back((*itB));
			continue;
		}
		if( (*itB).left>=M1.GetBloqueNuevo().right || M1.GetBloqueNuevo().left>=(*itB).right)
		{
			M1.GetListaBloques().push_back((*itB));
			continue;
		}
		//Solapa con el bloque nuevo
		//Cambiar el bloque y crear pérdidas
		//Tenemos que el bottomRight cae dentro del nuevo rectángulo
		//Tengo cuatro casos
		if (metodo==1)	cortar_Bloques((*itB),M1);
		if (metodo==2)  cortar_Bloques_Rectangulos((*itB),M1);
		

	}
}
void PALLET::cortar_Bloques_Rectangulos(BLOQUE &b1,MOVE &M1)
{
	BLOQUE b2=M1.GetBloqueNuevo(),B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
	int l=m_l;
	int w=m_w;
	if (b1.GetTipo()=='H')
	{
		l=m_w;
		w=m_l;
	}
	//Tengo cuatro casos
	//BottomRight cae dentro del anterior
//	CRect B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
	CRect k1=b1;
	CRect k2=b2;
	int corta=Restar_Rectangulo(k1,k2,B1,B2,B3,B4);
	//No se cortan
	if (corta!=0)
	{
		//Tengo que hacerlos bloques 
		if (B1.IsRectEmpty()==0)
		{
			int a=((B1.bottom-B1.top)/l);
			int b=((B1.right-B1.left)/w);
			B1.bottom=B1.top+a*l;
			B1.right=B1.left+b*w;
		}
		if (B2.IsRectEmpty()==0)
		{
			int a=((B2.bottom-B2.top)/l);
			int b=((B2.right-B2.left)/w);
			B2.bottom=B2.top+a*l;
			B2.right=B2.left+b*w;
		}
		if (B3.IsRectEmpty()==0)
		{
			int a=((B3.bottom-B3.top)/l);
			int b=((B3.right-B3.left)/w);
			B3.bottom=B3.top+a*l;
			B3.right=B3.left+b*w;
		}
		if (B4.IsRectEmpty()==0)
		{
			int a=((B4.bottom-B4.top)/l);
			int b=((B4.right-B4.left)/w);
			B4.bottom=B4.top+a*l;
			B4.right=B4.left+b*w;
		}
		B1.SetTipo(b1.GetTipo());
		B2.SetTipo(b1.GetTipo());
		B3.SetTipo(b1.GetTipo());
		B4.SetTipo(b1.GetTipo());
		if (B1.IsRectEmpty()==0) M1.GetListaBloques().push_back(B1);
		if (B2.IsRectEmpty()==0) M1.GetListaBloques().push_back(B2);
		if (B3.IsRectEmpty()==0) M1.GetListaBloques().push_back(B3);
		if (B4.IsRectEmpty()==0) M1.GetListaBloques().push_back(B4);
	}

}
void PALLET::cortar_Bloques(BLOQUE &b1,MOVE &M1)
{
	BLOQUE b2=M1.GetBloqueNuevo(),B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
	//Tengo cuatro casos
	//BottomRight cae dentro del anterior
//	CRect B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
	int corta=Restar_Rectangulo(b1,b2,B1,B2,B3,B4);
	//No se cortan
	if (corta!=0)
	{

		B1.SetTipo(b1.GetTipo());
		B2.SetTipo(b1.GetTipo());
		B3.SetTipo(b1.GetTipo());
		B4.SetTipo(b1.GetTipo());
		if (B1.IsRectEmpty()==0) M1.GetListaBloques().push_back(B1);
		if (B2.IsRectEmpty()==0) M1.GetListaBloques().push_back(B2);
		if (B3.IsRectEmpty()==0) M1.GetListaBloques().push_back(B3);
		if (B4.IsRectEmpty()==0) M1.GetListaBloques().push_back(B4);
	}

/*		if (((b2.bottom<=b1.bottom) && (b2.bottom>b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)) ||
		((b2.top<b1.bottom) && (b2.top>=b1.top) && (b2.right>b1.left) && (b2.right<=b1.right) && (b2.left<=b1.left)))
		{
		//Crear bLOQUE
		int a=((b1.bottom-b2.bottom)/w);
		int b=((b1.right-b2.right)/l);
		int c=((b2.top-b1.top)/w);
		if (a<0) a=0;
		if (b<0) b=0;
		if (c<0) c=0;

		//El que esta por encima;
		if (a>0)
		{
			B1.BottomRight()=b1.BottomRight();
			B1.left=b1.left;
			B1.top=b1.bottom-a*w;
		}
		//El que esta al lado
		if (b>0)
		{
			B2.right=b1.right;
			B2.left=b1.right-b*l;
			B2.bottom=b1.bottom-a*w;
			if (c>0) B2.top=b1.top+c*w;
			else B2.top=b1.top;
		}
		if (c>0)
		{
			B3.right=b1.right;
			B3.left=b1.left;
			B3.bottom=b1.top+c*w;
			B3.top=b1.top;
		}
		if (B1.IsRectEmpty()==0) M1.GetListaBloques().push_back(B1);
		if (B2.IsRectEmpty()==0) M1.GetListaBloques().push_back(B2);
		if (B3.IsRectEmpty()==0) M1.GetListaBloques().push_back(B3);

	}
*/	
}
bool PALLET::PorDondeDisminuir(BLOQUE &B1,int x,int y)
{
	//Devuelve true si es por arriba o por abajo
	if (x>0) 
	{
		if (B1.TopLeft().x==0) return true;
		if (B1.BottomRight().x==m_L) return false;
		if (B1.TopLeft().x>(m_L/2))	return false;
		if (B1.BottomRight().x<(m_L/2))	return true;

	}
	if (y>0)
	{
		if (B1.TopLeft().y==0) return true;
		if (B1.BottomRight().y==m_W) return false;
		if (B1.TopLeft().y>(m_W/2)) return false;
		if (B1.BottomRight().y<(m_W/2))	return true;
	}
	return true;
}
bool PALLET::Comprobar_Puede_Mejorar(BLOQUE &B1,BLOQUE &B2,char tipo)
{
	int l=0,w=0;
	if (B1.GetTipo()=='H')
	{
		l=m_l;
		w=m_w;
	}
	else
	{
		l=m_w;
		w=m_l;
	}

	//Tengo que mirar cuantas hay de esta manera y
	//la pérdida que provocan
	CRect Nuevo1,Nuevo2;
	int suma=0;
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
//		BLOQUE b2=(*itB);
		if ((*itB).EqualRect(B1)!=0) continue;
		//Si tipo es uno busco el pegado a la izquierda
		if (B1.GetTipo()==(*itB).GetTipo() && tipo=='H')
		{
			if (((*itB).top<=B2.top) && ((*itB).bottom>=B2.bottom))
				suma+=((*itB).Width()/l);
		}
		if (B1.GetTipo()==(*itB).GetTipo() && tipo=='V')
		{
			if (((*itB).left<=B2.left) && ((*itB).right>=B2.right))
				suma+=((*itB).Height()/w);
		}

	}
	if (tipo=='H')
	{
		suma+=(B2.Width()/l);
		bool valido=PerdidaPosibleX(B2,suma);
		return valido;
	}
	if (tipo=='H')
	{
		suma+=(B2.Height()/l);
		bool valido=PerdidaPosibleY(B2,suma);
		return valido;
	}

	return true;

}
/*
bool PALLET::PuedeDisminuirse(BLOQUE &B1,int xder,int xizq, int yarr, int yaba,bool bloque_nulo)
{
	int	x=xder+xizq;
	int	y=yarr+yaba;
	int l=m_l;
	int w=m_w;
	if (B1.GetTipo()=='V')
	{
		l=m_w;
		w=m_l;
	}
	//Antiguo
//	if (x>(B1.Width()/l)) return false;
//	if (y>(B1.Height()/w))  return false;
	if (bloque_nulo==true)
	{
		if ((x>(B1.Width()/l))) return false;
	}
	else
		if ((x>=(B1.Width()/l))) return false;
	if (bloque_nulo==true)
	{
		if ((y>(B1.Height()/w))) return false;
	}
	else
		if ((y>=(B1.Height()/w))) return false;
	if (x*y>0)
	{
		if ((x>=(B1.Width()/l)) ||(y>=(B1.Height()/w))) return false;
	}
	//Solo por un lado
	if (xder>0 && (m_L-B1.left<B1.right))
		return false;
	if (xizq>0 && (B1.right<=m_L-B1.left)) 
		return false;
	if (yarr>0 && (m_W-B1.bottom<=B1.top)) 
		return false;
	if (yaba>0 && (B1.top<m_W-B1.bottom)) 
		return false;

	if (x>0 && m_Eficientes==true) 
	{
		if 	((ParticionEficienteX(B1.Width()-(x*l),B1.GetTipo())==false)) return false;
	}
	if (y>0 && m_Eficientes==true)
	{
		if	(((ParticionEficienteY(B1.Height()-(y*w),B1.GetTipo())==false))) return false;
	}
	//Solo por un lado
	if (x>0 && (x*l)<w) 
		return false;
	if (y>0 && (y*w)<l) 
		return false;
	//Si va a dejar algo que no es bueno

	return true;
}
bool PALLET::PuedeAumentarse(BLOQUE &B1,int xder,int xizq,int yarr, int yaba)
{
	//No permito que un bloque no eficiente se haga mayor
//	if (Es_Eficiente_Bloque(B1)==false) return false;
	int l=m_l,w=m_w,x,y;
	if (B1.GetTipo()=='V')
	{
		l=m_w;
		w=m_l;
	}
//	if (xder+xizq>(2*B1.Width()/l)) return false;
//	if (yaba+yarr>(2*B1.Height()/w)) return false;

	if (xder>0) 	
	{
		x=B1.BottomRight().x+(xder*l);
		if (x>m_L) return false;
	}
	if (xizq>0) 
	{
		x=B1.TopLeft().x-(xizq*l);
		if (x<0) return false;
	}
	if (yarr>0)
	{
		y=B1.BottomRight().y+(yarr*w);
		if (y>m_W) return false;
	}
	if (yaba>0)
	{
		y=B1.TopLeft().y-(yaba*w);
		if (y<0) return false;

	}
	x=xder+xizq;
	y=yarr+yaba;
	
	if ((x>0) && m_Eficientes==true &&(ParticionEficienteX(B1.Width()+(x*l))==false)) return false;
	if ((y>0) && m_Eficientes==true && (ParticionEficienteY(B1.Height()+(y*w))==false)) return false;
	BLOQUE B1Aumen;
	B1Aumen.BottomRight()=B1.BottomRight();
	B1Aumen.TopLeft()=B1.TopLeft();
	B1Aumen.SetTipo(B1.GetTipo());
	x=xder+xizq;
	y=yarr+yaba;
	if (xder>0) 	B1Aumen.BottomRight().x=B1.BottomRight().x+(x*l);
	if (xizq>0) 	B1Aumen.TopLeft().x=B1.TopLeft().x-(x*l);
	if (yarr>0)		B1Aumen.BottomRight().y=B1.BottomRight().y+(y*w);
	if (yaba>0) 	B1Aumen.TopLeft().y=B1.TopLeft().y-(y*w);
	int PerdidaPer=((m_L*m_W)-(m_l*m_w*m_Cota));
	if (m_Eficientes==true) PerdidaPer=0;
	//Si va darme algo que no va a mejorar
	if (x>0)
	{
		if ((ParticionPerfecta(m_L-B1Aumen.Width())*B1Aumen.Height())>PerdidaPer)
				return false;
	}
	if (y>0)
	{
		//Si no es valida para el alto
		if ((ParticionPerfecta(m_W-B1Aumen.Height())*B1Aumen.Width())>PerdidaPer)
				return false;
	}
	//Si aumenta no sirve para nada por que va a  auymentar donde hay una caja horizontal
/*	CRect RectTemp;
	SubtractRect(&RectTemp,&B1Aumen,&B1);
// Tengo la interseccion si ahora tengo que en ese cuadrado
	// solo hay del mismo tipo que el aumentado entonces no me vale
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
		CRect Temp2;
		IntersectRect(&Temp2,&(*itB),&RectTemp);
		if (Temp2.EqualRect(RectTemp)!=0 && (*itB).GetTipo()==B1.GetTipo())
			return false;

	}*/
	

/*	BLOQUE B1Aumen;
	B1Aumen.BottomRight()=B1.BottomRight();
	B1Aumen.TopLeft()=B1.TopLeft();
	B1Aumen.SetTipo(B1.GetTipo());
	x=xder+xizq;
	y=yarr+yaba;
	if (xder>0) 	B1Aumen.BottomRight().x=B1.BottomRight().x+(x*l);
	if (xizq>0) 	B1Aumen.TopLeft().x=B1.TopLeft().x-(x*l);
	if (yarr>0)		B1Aumen.BottomRight().y=B1.BottomRight().y+(y*w);
	if (yaba>0) 	B1Aumen.TopLeft().y=B1.TopLeft().y-(y*w);

	std::list<BLOQUE> lista;
	lista.push_back(B1Aumen);
	if (EsTabu(lista)==true) return false;*/
//	return true;


//}

bool PALLET::PuedeDisminuirse(BLOQUE &B1,int xder,int xizq, int yarr, int yaba,bool bloque_nulo)
{
	//Si no es una de la razon no lo quiero
	bool pocos=true;
	int	x=xder+xizq;
	int	y=yarr+yaba;
	if (y>0 && B1.GetTipo()=='H')
		int miki=9;
	int l=m_l;
	int w=m_w;
	char tipo2='V';
	if (B1.GetTipo()=='V')
	{
		l=m_w;
		w=m_l;
		tipo2='H';
	}
	//Si permito el bloque nulo
	if (bloque_nulo==true)
	{
		if (x==(B1.Width()/l) || y==(B1.Height()/w)) return true;
	}
	//Si las dimensiones no son posibles
	if (bloque_nulo==true)
	{
		if ((x>(B1.Width()/l))) return false;
	}
	else
		if ((x>=(B1.Width()/l))) return false;
	if (bloque_nulo==true)
	{
		if ((y>(B1.Height()/w))) return false;
	}
	else
		if ((y>=(B1.Height()/w))) return false;
//	return true;
	//Si queremos intensificar miramos todos los posibles
	//movimientos
	//	return true;
	if (m_Intensificar==true) return true;
	//Los que mas puede haber son los verticales o horizontales

	if (x>0 && B1.GetTipo()=='V' ) 
	{
			if (m_gano+x*m_w<m_l) return false;
			//Intenta evitar colocaciones que dejen en medio h y luego V
			if ((m_gano+x*m_w)%m_l>=m_w ) return false;
//			if ((m_gano+x*m_w)%m_l<=m_w ) return false;
		
	}
	if (y>0 && B1.GetTipo()=='H' ) 
	{
//		if (B1.Width()>m_G4_horizontal && m_gano+y*m_w>m_G4_vertical) re
		if (m_gano+y*m_w<m_l ) return false;
		//Intenta evitar colocaciones que dejen en medio V y luego H

		if ((m_gano+y*m_w)%m_l>=m_w) return false;
//		if ((m_gano+y*m_w)%m_l<=m_w) return false;
	}
	
	//Si voy a reducir por arriba o por abajo y no cabe una pieza no reduzco
//	if (B1.GetTipo()=='V' && (y>0) && B1.Width()<m_l) return false;
	//Si voy a reducir por derecha o por izquierda y no cabe una pieza no reduzco
//	if (B1.GetTipo()=='H' && (x>0) && B1.Height()<m_l) return false;


	if (x*y>0)
	{
		if ((x>=(B1.Width()/l)) ||(y>=(B1.Height()/w))) return false;
	}
	//Si es tan ancho o largo como todo el pallet reducir a una particion perfecta
	if ((B1.Width()==m_L && B1.Height()==m_l) && x>0)
	{
		if (Es_Perfecta(B1.Width()-(x*l),B1.GetTipo(),'L')==false ) 
			return false;
	}
	if ( (B1.Height()==m_W && B1.Width()==m_l) && y>0) 
	{
		if (Es_Perfecta(B1.Height()-(y*w),B1.GetTipo(),'W')==false ) 
			return false;
	}

//	return true;

/*	if (x>0 && (B1.Width()/l)==(m_L/l))
	{
		if (Es_Perfecta(B1.Width()-(x*l),B1.GetTipo(),'L')==false ) 
			return false;
	}
	if (y>0 && (B1.Height()/w)==(m_W/w))
	{
		if (Es_Perfecta(B1.Height()-(y*w),B1.GetTipo(),'W')==false ) 
			return false;
	}
*/
	//RasterPOINTS
		//RasterPoints

/*		if (xder>0 && (B1.left==0))
		{
			if (TieneRasterPoint(B1.right+(x*l),B1.top,B1.GetTipo())!=true)
				return false;
		}*/
/*
		if (xizq>0 && (B1.left>=(m_L/2)))
		{

			if (TieneRasterPoint(B1.left+(x*l)-(((x*l)/w)*w),B1.top,tipo2)!=true)
				return false;
		}

		if (yaba>0 && (B1.top>=(m_W/2)))
		{
			if (TieneRasterPoint(B1.left,B1.top+(y*w)-(((y*w)/l)*l),tipo2)!=true)
				return false;
		}
*/
		if (xizq>0 && ((B1.left>=(m_L/2)) || (B1.left+(x*l)>=(m_L/2))) && ((B1.Width()/l)>2))
		{
			if (TieneRasterPoint(B1.left+(x*l),B1.top,B1.GetTipo())!=true)
					return false;
		}

		if (yaba>0 && ((B1.top>=(m_W/2)) || (B1.top+(y*w)>=(m_W/2))) && ((B1.Height()/w)>2))
		{
			if (TieneRasterPoint(B1.left,B1.top+(y*w),B1.GetTipo())!=true)
					return false;
		}
		

		if (xder>0 && ((B1.right<=(m_L/2)) || (B1.left==0)) && ((B1.Width()/l)>2))
		{
			if ((B1.right-((x+1)*l))>B1.left)
			{
				if (TieneRasterPoint(B1.right-((x+1)*l),B1.top,B1.GetTipo())!=true)
					return false;
			}
		}

		if (yarr>0 && ((B1.bottom<=(m_W/2)) || (B1.top==0)) && ((B1.Height()/w)>2))
		{
			if ((B1.bottom-((y+1)*w))>B1.top)
			{

				if (TieneRasterPoint(B1.left,B1.bottom-((y+1)*w),B1.GetTipo())!=true)
					return false;
			}
		}
/*	if (x>0 && m_no_hay==false)
	{
		if (xder>0)
		{
			if (TieneRasterPoint(B1.right-(x*l)-l,B1.top,B1.GetTipo())!=true)
				return false;
		}
		if (xizq>0)
		{
			if (TieneRasterPoint(B1.left+(x*l),B1.top,B1.GetTipo())!=true)
				return false;
		}
	}
	if (y>0 &&  m_no_hay==false)
	{
		if (yarr>0)
		{
			if (TieneRasterPoint(B1.left,B1.bottom-(y*w)-w,B1.GetTipo())!=true)
				return false;
		}
		if (yaba>0)
		{
			if (TieneRasterPoint(B1.left,B1.top+(y*w),B1.GetTipo())!=true)
				return false;
		}
	}

*/
/*	if (x>0 && m_proporcion<1) 
	{
		if 	((ParticionEficienteX(B1.Width()-(x*l),B1.GetTipo())==false)) return false;
	}
	if (y>0 && m_proporcion<1)
	{
		if	(((ParticionEficienteY(B1.Height()-(y*w),B1.GetTipo())==false))) return false;
	}*/
/*	BLOQUE B1Dismi;
	B1Dismi.BottomRight()=B1.BottomRight();
	B1Dismi.TopLeft()=B1.TopLeft();
	B1Dismi.SetTipo(B1.GetTipo());
	if (xder>0) 	B1Dismi.BottomRight().x=B1.BottomRight().x-(x*l);
	if (xizq>0) 	B1Dismi.TopLeft().x=B1.TopLeft().x+(x*l);
	if (yarr>0)		B1Dismi.BottomRight().y=B1.BottomRight().y-(y*w);
	if (yaba>0) 	B1Dismi.TopLeft().y=B1.TopLeft().y+(y*w);
*/
/*	if (x>0)
	{
		if (Comprobar_Puede_Mejorar(B1,B1Dismi,'H')==false) return false;
	}
	if (y>0)
	{
		if (Comprobar_Puede_Mejorar(B1,B1Dismi,'V')==false) return false;
	}
*/

	return true;
}
bool PALLET::PuedeAumentarse(BLOQUE &B1,int xder,int xizq,int yarr, int yaba)
{
//	if ((B1.Width()==m_l && B1.Height()==m_w) || (B1.Width()==m_w && B1.Height()==m_l) )
//		return false;
	int l=m_l,w=m_w,x,y;
	if (B1.GetTipo()=='V')
	{
		l=m_w;
		w=m_l;
	}
	//Dimensiones posibles
	if (xder>0) 	
	{
		x=B1.BottomRight().x+(xder*l);
		if (x>m_L) return false;
	}
	if (xizq>0) 
	{
		x=B1.TopLeft().x-(xizq*l);
		if (x<0) return false;
	}
	if (yarr>0)
	{
		y=B1.BottomRight().y+(yarr*w);
		if (y>m_W) return false;
	}
	if (yaba>0)
	{
		y=B1.TopLeft().y-(yaba*w);
		if (y<0) return false;

	}
	//Si queremos intensificar miramos todos los posibles
	//movimientos
	if (m_Intensificar==true) return true;
	if ((xder+xizq)>0 && B1.GetTipo()=='V') 
	{
		if ((((xder+xizq)*m_w)%m_l)>=m_w) return false;
//		if ((((xder+xizq)*m_w)%m_l)<=m_w) return false;
//		if (((m_gano+(xder+xizq)*m_w)%m_l)>=m_w) return false;
//		if (ParticionEficiente(m_L-(B1.Width()+((xder+xizq)*m_w)),'H','L')==false) 
//			return false;
	}
	if ((yarr+yaba)>0 && B1.GetTipo()=='H') 
	{
		if ((((yarr+yaba)*m_w)%m_l)>=m_w) return false;
//		if ((((yarr+yaba)*m_w)%m_l)<=m_w) return false;
//		if (((m_gano+(yarr+yaba)*m_w)%m_l)>=m_w) return false;

//		if (ParticionEficiente(m_W-(B1.Height()+((yaba+yarr)*m_w)),'V','W')==false) 
//			return false;
	}

	x=xder+xizq;
	y=yarr+yaba;
/*	if (x>0)
	{
		if (Es_Perfecta(B1.Width()+(x*l),B1.GetTipo(),'L')==false ) 
			return false;
	}
	if (y>0)
	{
		if (Es_Perfecta(B1.Height()+(y*w),B1.GetTipo(),'A')==false ) 
			return false;
	}
*/
	
	if ((x>0) && (m_Eficientes==true) && (ParticionEficienteX(B1.Width()+(x*l),B1.GetTipo())==false)) return false;
	if ((y>0) && (m_Eficientes==true) && (ParticionEficienteY(B1.Height()+(y*w),B1.GetTipo())==false)) return false;
	BLOQUE B1Aumen;
	B1Aumen.BottomRight()=B1.BottomRight();
	B1Aumen.TopLeft()=B1.TopLeft();
	B1Aumen.SetTipo(B1.GetTipo());
	x=xder+xizq;
	y=yarr+yaba;
	if (xder>0) 	B1Aumen.BottomRight().x=B1.BottomRight().x+(x*l);
	if (xizq>0) 	B1Aumen.TopLeft().x=B1.TopLeft().x-(x*l);
	if (yarr>0)		B1Aumen.BottomRight().y=B1.BottomRight().y+(y*w);
	if (yaba>0) 	B1Aumen.TopLeft().y=B1.TopLeft().y-(y*w);

	//Si va darme algo que no va a mejorar
/*	if (m_iter_actual>250)
	{
		if (((ParticionPerfecta(m_L-B1Aumen.Width())*B1Aumen.Height())+(ParticionPerfecta(m_W-B1Aumen.Height())*B1Aumen.Width()))>PerdidaPer)
				return false;
	}
	if (x>0 )
	{
		if ((ParticionPerfecta(m_L-B1Aumen.Width())*B1Aumen.Height())>m_perdidaCota)
				return false;
	}
	if (y>0)
	{
		//Si no es valida para el alto
		if ((ParticionPerfecta(m_W-B1Aumen.Height())*B1Aumen.Width())>m_perdidaCota)
				return false;
	}*/
	//RasterPoints

	if (xder>0 && (B1.left==0) && (B1.Width()/l)>2)
	{
		if (TieneRasterPoint(B1.right+((x-1)*l),B1.top,B1.GetTipo())!=true)
			return false;
	}
	if (xizq>0 && (B1.right==m_L || (B1.left-(x*l))>=(m_L/2)))
	{
		if (TieneRasterPoint(B1.left-(x*l),B1.top,B1.GetTipo())!=true)
			return false;
	}
	if (yarr>0 && B1.top==0 && (B1.Height()/w)>2)
	{
		if (TieneRasterPoint(B1.left,B1.bottom+((y-1)*w),B1.GetTipo())!=true)
			return false;
	}
	if (yaba>0 && (B1.bottom==m_W || (B1.top-(y*w))>=(m_W/2)))
	{
		if (TieneRasterPoint(B1.left,B1.top-(y*w),B1.GetTipo())!=true)
			return false;
	}
	//Si aumenta no sirve para nada por que va a  auymentar donde hay una caja horizontal
/*	CRect RectTemp;
	SubtractRect(&RectTemp,&B1Aumen,&B1);
// Tengo la interseccion si ahora tengo que en ese cuadrado
	// solo hay del mismo tipo que el aumentado entonces no me vale
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
		CRect Temp2;
		IntersectRect(&Temp2,&(*itB),&RectTemp);
		if (Temp2.EqualRect(RectTemp)!=0 && (*itB).GetTipo()==B1.GetTipo())
			return false;

	}
*/	

/*	BLOQUE B1Aumen;
	B1Aumen.BottomRight()=B1.BottomRight();
	B1Aumen.TopLeft()=B1.TopLeft();
	B1Aumen.SetTipo(B1.GetTipo());
	x=xder+xizq;
	y=yarr+yaba;
	if (xder>0) 	B1Aumen.BottomRight().x=B1.BottomRight().x+(x*l);
	if (xizq>0) 	B1Aumen.TopLeft().x=B1.TopLeft().x-(x*l);
	if (yarr>0)		B1Aumen.BottomRight().y=B1.BottomRight().y+(y*w);
	if (yaba>0) 	B1Aumen.TopLeft().y=B1.TopLeft().y-(y*w);

	std::list<BLOQUE> lista;
	lista.push_back(B1Aumen);
	if (EsTabu(lista)==true) return false;*/
	return true;


}
void PALLET::CompactarPerdida(std::list<CRect> &Nuevas)
{
	std::list<CRect> lista,lista2,aux;
	bool compacta1=false,compacta2=false;
	std::list<CRect>::iterator itL,itL2,itL3,itL4;
	//Primera Pasada
	int contador=0;
	do 
	{
		contador++;
		
		compacta1=false;
		for (itL=Nuevas.begin();itL!=Nuevas.end() && compacta1!=true;itL++)
		{
			CRect rect1=(*itL);
			itL2=itL;
			itL2++;
			if (itL2==Nuevas.end()) break;
			for (;itL2!=Nuevas.end() && compacta1!=true;itL2++)
			{
				CRect rect2=(*itL2);	
					//recorro para ver si ya la he metido
				CRect RectTemp;
				UnionRect(&RectTemp,&(*itL),(*itL2));	
				if (((RectTemp.Width()*RectTemp.Height())==(((*itL).Width()*(*itL).Height())+((*itL2).Width()*(*itL2).Height())) ))
				{
					Nuevas.push_back(RectTemp);
					itL2=Nuevas.erase(itL2);
					itL=Nuevas.erase(itL);
					compacta1=true;
				}
			}
		}
	}while( compacta1==true);
}

std::list<CRect> PALLET::CompactarPerdida2(std::list<CRect> &Nuevas)
{
	std::list<CRect> lista,lista2,aux;
	bool compacta1=false,compacta2=false;
	bool otro=false;
	std::list<CRect>::iterator itL,itL2,itL3,itL4;
	//Primera Pasada
	for(itL=Nuevas.begin();itL!=Nuevas.end();itL++)
	{
		CRect rect1=(*itL);
		compacta1=false;
		otro=false;
		//recorro para ver si ya la he metido
		for (itL4=aux.begin();itL4!=aux.end();itL4++)
		{
			if (((*itL4).BottomRight()==(*itL).BottomRight()) &&
			((*itL4).TopLeft()==(*itL).TopLeft()) )
			{	
				otro=true;
				break;
			}
		}
		if (otro==true) continue;
		compacta2=false;
		for(itL2=Nuevas.begin();itL2!=Nuevas.end() ;itL2++)
		{
			
			if (((*itL2).BottomRight()==(*itL).BottomRight()) &&
			((*itL2).TopLeft()==(*itL).TopLeft()) )
				continue;
			otro=false;
			CRect rect2=(*itL2);

			//recorro para ver si ya la he metido
			for (itL4=aux.begin();itL4!=aux.end();itL4++)
			{
				if (((*itL4).BottomRight()==(*itL2).BottomRight()) &&
				((*itL4).TopLeft()==(*itL2).TopLeft()) )
				{	
					otro=true;
					break;
				}
			}
			if (otro==true) continue;
			if (compacta2!=true)
			{
				CRect RectTemp;
				UnionRect(&RectTemp,&(*itL),(*itL2));	

				if (((RectTemp.Width()*RectTemp.Height())==(((*itL).Width()*(*itL).Height())+((*itL2).Width()*(*itL2).Height())) ))
				{
					lista.push_back(RectTemp);
					compacta1=true;
					compacta2=true;
					aux.push_back((*itL));
					aux.push_back((*itL2));
				}
				else lista.push_back((*itL2));
			}
			else lista.push_back((*itL2));

		}
		if (compacta1!=true)
		{
			lista.push_back((*itL));
			
		}
		
	}
	return lista;
	//Segunda pasada
	/*
	for(itL=lista.begin();itL!=lista.end();itL++)
	{
		compacta=false;
		for(itL2=m_lista_perdidas.begin();itL2!=m_lista_perdidas.end();itL2++)
		{
			CRect RectTemp;
			UnionRect(&RectTemp,&(*itL),(*itL2));

			if (((RectTemp.Width()*RectTemp.Height())==(((*itL).Width()*(*itL).Height())+((*itL2).Width()*(*itL2).Height())) ) && (compacta==false))
			{
				lista2.push_back(RectTemp);
				compacta=true;
			}
			else
			{
				lista2.push_back((*itL2));
			}
	
		}
		if (compacta!=true)
		{
			lista2.push_back((*itL));
			
		}
		
	}
	return lista2;*/
}
/*
void PALLET::CompactarBloques(void)
{
	bool compacta=false;
	std::list<BLOQUE>::iterator itL,itL2,itL3;
	std::list<BLOQUE> lista;
	itL=m_lista_bloques.begin();
	do{
//	for(itL=m_lista_bloques.begin();itL!=m_lista_bloques.end();itL++)
//	{
		if ((*itL).IsRectEmpty()!=0)
		{
			itL=m_lista_bloques.erase(itL);
			continue;
		}
		itL3=itL;
		itL3++;
		if (itL3==m_lista_bloques.end()) break;
		if ((*itL).PuedoMover()==false)
		{
			itL++;
			continue;
		}

		compacta=false;
		itL2=itL;
		do{
//		for(itL2=itL;itL2!=m_lista_bloques.end()&& compacta!=true;itL2++)
//		{
			BLOQUE b1=(*itL);
			BLOQUE b2=(*itL2);
			if ((*itL2).PuedoMover()==false)
			{
				itL2++;
				continue;
			}

			if (((*itL).BottomRight()==(*itL2).BottomRight()) &&
			((*itL).TopLeft()==(*itL2).TopLeft()) && ((*itL).GetTipo()==(*itL2).GetTipo()) )
			{ 
				itL2++;
				continue;
			}
			if ((*itL).GetTipo()!=(*itL2).GetTipo()) 
			{ 
				itL2++;
				continue;
			}

			CRect RectTemp,RectTemp1;
			UnionRect(&RectTemp,&(*itL),(*itL2));
			//si tienen el mismo area que la unión de ambos
			if ((RectTemp.Width()*RectTemp.Height())==(((*itL).Width()*(*itL).Height())+((*itL2).Width()*(*itL2).Height())) && (*itL).GetTipo()==(*itL2).GetTipo())
			{
				BLOQUE b(RectTemp,(*itL2).GetTipo());
				lista.push_back(b);
				compacta=true;
				itL2=m_lista_bloques.erase(itL2);
				continue;
			}
			//si no tienen el mismo area pero existe una perdida que si
			//lo tenga 
			//Primera condición esten a la misma altura
			//muevo las piezas a una partición eficiente
			if (((*itL).TopLeft().y==(*itL2).TopLeft().y) && ((*itL).BottomRight().y==(*itL2).BottomRight().y))
			{
				SubtractRect(&RectTemp1,&RectTemp,&(*itL));
				SubtractRect(&RectTemp1,&RectTemp1,&(*itL2));
				//Si existe la pérdida por la derecha o por la izquierda
				if (Existe_Perdida(RectTemp1,0)==true)
//				if (Existe_Perdida(RectTemp1)==true)
				{
					int diferencia=RectTemp1.Width();
					CRect perdida;
					perdida.top=(*itL).TopLeft().y;
					perdida.bottom=(*itL).BottomRight().y;
					//Pieza 2 a la izquierda de la pieza 1
					if ((*itL).right>(*itL2).right)
					{
						if (ParticionEficienteX((*itL2).left+diferencia)!=true)
						{
							perdida.right=(*itL).right;
							RectTemp.left=(*itL2).left;
							perdida.left=perdida.right-diferencia;
							RectTemp.right=perdida.left;

						}
						else
						{
							perdida.left=(*itL2).left;
							RectTemp.right=(*itL).right;
							perdida.right=perdida.left+diferencia;
							RectTemp.left=perdida.right;

						}

					}
					//Pieza 1 a la izquierda de la pieza 2
					else
					{

						if (ParticionEficienteX((*itL).left+diferencia)!=true)
						{
							perdida.right=(*itL2).right;
							RectTemp.left=(*itL).left;
							perdida.left=perdida.right-diferencia;
							RectTemp.right=perdida.left;

						}
						else
						{
							perdida.left=(*itL).left;
							RectTemp.right=(*itL2).right;
							perdida.right=perdida.left+diferencia;
							RectTemp.left=perdida.right;

						}
					}
					m_lista_perdidas.push_back(perdida);
					BLOQUE b(RectTemp,(*itL2).GetTipo());
					lista.push_back(b);
					compacta=true;
					itL2=m_lista_bloques.erase(itL2);
					continue;

				}

			}
			//Segunda condición coincidan a lo alto
			if (((*itL).TopLeft().x==(*itL2).TopLeft().x) && ((*itL).BottomRight().x==(*itL2).BottomRight().x))
			{
				SubtractRect(&RectTemp1,&RectTemp,&(*itL));
				SubtractRect(&RectTemp1,&RectTemp1,&(*itL2));
				if (Existe_Perdida(RectTemp1,1)==true)
//				if (Existe_Perdida(RectTemp1)==true)
				{
					int diferencia=RectTemp1.Height();
					CRect perdida;
					perdida.left=(*itL).TopLeft().x;
					perdida.right=(*itL).BottomRight().x;
					if ((*itL).bottom>(*itL2).bottom)
					{
						if (ParticionEficienteY((*itL2).top+diferencia)!=true)
						{
							perdida.bottom=(*itL).bottom;
							RectTemp.top=(*itL2).top;
							perdida.top=perdida.bottom-diferencia;
							RectTemp.bottom=perdida.top;	
						}
						else
						{
							perdida.top=(*itL2).top;
							RectTemp.bottom=(*itL).bottom;
							perdida.bottom=perdida.top+diferencia;
							RectTemp.top=perdida.bottom;	

						}
					}
					else
					{
						if (ParticionEficienteY((*itL).top+diferencia)!=true)
						{
							perdida.bottom=(*itL2).bottom;
							RectTemp.top=(*itL).top;
							perdida.top=perdida.bottom-diferencia;
							RectTemp.bottom=perdida.top;	
						}
						else
						{
							perdida.top=(*itL).top;
							RectTemp.bottom=(*itL2).bottom;
							perdida.bottom=perdida.top+diferencia;
							RectTemp.top=perdida.bottom;	

						}

					}
					m_lista_perdidas.push_back(perdida);
					BLOQUE b(RectTemp,(*itL2).GetTipo());
					lista.push_back(b);
					compacta=true;
					itL2=m_lista_bloques.erase(itL2);
					continue;

				}

			}
			itL2++;
		} while(itL2!=m_lista_bloques.end()&& compacta!=true);
		if (compacta==true)
		{
			itL=m_lista_bloques.erase(itL);
			continue;
		}
		itL++;
	}while (itL!=m_lista_bloques.end());

	m_lista_bloques.insert(m_lista_bloques.begin(),lista.begin(),lista.end());


}
void PALLET::Bloques_Hacia_Las_Esquinas(void)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el 
	//*********PEGAR LOQUES
	std::list<BLOQUE> :: iterator itL;

	bool movida_izquierda=false;
	bool movida_abajo=false;
	itL=m_lista_bloques.begin();
	do{
		movida_izquierda=false;
		movida_abajo=false;
		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).PuedoMover()==false)
		{
			itL++;
			continue;
		}

		if ((*itL).left!=0)
		{
			//Pegarla hacia la izquierda
//			if ((m_L-(*itL).right)>((*itL).left) && (ParticionEficienteX((*itL).left)!=true))
//			{
				CRect Rect(0,(*itL).top,(*itL).left,(*itL).bottom);

				//Poner bloque pegado a la izquierda
				if (Existe_Perdida(Rect,0)==true)
				{
					(*itL).left=0;
					(*itL).right=(*itL).right-Rect.right;
					//Nueva perdida
					CRect perdida;
					perdida.left=(*itL).right;
					perdida.right=(*itL).right+Rect.Width();
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					m_lista_perdidas.push_back(perdida);
					movida_izquierda=true;
				}

			//Pegado a la derecha
			if (movida_izquierda==false && (*itL).left!=0)
			{
				CRect Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(Rect,0)==true)
				{
					(*itL).right=m_L;
					(*itL).left=(*itL).left+Rect.Width();
					CRect perdida;
					perdida.left=(*itL).left-Rect.Width();
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					m_lista_perdidas.push_back(perdida);

				}
			}
		}
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).top!=0)
		{
			//Pegarla hacia abajo
//			if ((m_W-(*itL).bottom)>((*itL).top) )
//			{
				CRect Rect((*itL).left,0,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(Rect,1)==true)
				{
					(*itL).top=0;
					(*itL).bottom=(*itL).bottom-Rect.Height();
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=(*itL).bottom+Rect.Height();
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					m_lista_perdidas.push_back(perdida);
					movida_abajo=true;
				}
//			}
			//Pegado a arriba
			if (movida_abajo==false && (*itL).top!=0)
			{
				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(Rect,1)==true)
				{
					(*itL).bottom=m_W;
					(*itL).top=(*itL).top+Rect.Height();
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=(*itL).top-Rect.Height();
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					m_lista_perdidas.push_back(perdida);

				}
			}
		}
		itL++;

	}while(itL!=m_lista_bloques.end());
	//Ahora pegamos las pérdidas pero hacia los lados
	bool seguir=false;
	do
	{
		seguir=false;
	itL=m_lista_bloques.begin();
	do{
		if ((*itL).PuedoMover()==false)
		{
			itL++;
			continue;
		}
		
		//Si el bloque esta pegado a alguna de las cuatro esquinas

		if (((*itL).left==0 && (*itL).top==0) || ((*itL).right==m_L && (*itL).top==0) || ((*itL).right==m_L && (*itL).bottom==m_W) || ((*itL).left==0 && (*itL).bottom==m_W))
		{
			itL++;
			continue;
		}
		BLOQUE b1=(*itL);
		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).left<=(m_L/2) && ((*itL).left!=0) && ((*itL).right!=0))
		{
			int izq=ProximoBloque((*itL),1);
			if (izq>0)
			{
				CRect Rect((*itL).left-izq,(*itL).top,(*itL).left,(*itL).bottom);
				//Poner bloque pegado a la izquierda
				if (Existe_Perdida(Rect,0)==true)
				{
					(*itL).left=(*itL).left-izq;
					(*itL).right=(*itL).right-izq;
					//Nueva perdida
					CRect perdida;
					perdida.left=(*itL).right;
					perdida.right=(*itL).right+izq;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					m_lista_perdidas.push_back(perdida);
					seguir=true;
				}
			}
		}
		if ((*itL).left>(m_L/2) && ((*itL).left!=0) && ((*itL).right!=0))
		{
			int der=ProximoBloque((*itL),2);
			if (der>0)
			{

				CRect Rect((((*itL).right)),(*itL).top,(*itL).right+der,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(Rect,0)==true)
				{
					(*itL).right=(*itL).right+der;
					(*itL).left=(*itL).left+der;
					CRect perdida;
					perdida.left=(*itL).left-der;
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					m_lista_perdidas.push_back(perdida);
					seguir=true;
				}
			}
		}
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if (((*itL).top<=(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=0))
		{
			int aba=ProximoBloque((*itL),3);
			if (aba>0)
			{
				CRect Rect((*itL).left,(*itL).top-aba,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(Rect,1)==true)
				{
					(*itL).top=(*itL).top-aba;
					(*itL).bottom=(*itL).bottom-aba;
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=(*itL).bottom+aba;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					m_lista_perdidas.push_back(perdida);
					seguir=true;
				}
			}
		}
		if (((*itL).top>(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=0))
		{	
			//Lado izquierdo arriba
			int arri=ProximoBloque((*itL),4);
			if (arri>0)
			{

				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,(*itL).bottom+arri);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(Rect,1)==true)
				{
					(*itL).bottom=(*itL).bottom+arri;
					(*itL).top=(*itL).top+arri;
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=(*itL).top-arri;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					m_lista_perdidas.push_back(perdida);
					seguir=true;
				}
			}
		}
		itL++;

	}while(itL!=m_lista_bloques.end());
	}while(seguir!=false);

}*/
bool PALLET::Valida_Optimo(std::list<BLOQUE> &lista)
{
//	return true;
	std::list<BLOQUE> ::iterator itB1;
	int PerdidaSegura=0;
	int PerdidaPer=(m_L*m_W)-((m_solbest+1)*(m_l*m_w));
	if (m_solbest==m_Cota) 	PerdidaPer=(m_L*m_W)-((m_Cota)*(m_l*m_w));
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		//Si tiene bloques
		//Si no es valida para el ancho
		
		if (((m_L-(*itB1).Width())>0) && ((m_L-(*itB1).Width())<m_w))
		{
			if (((m_L-(*itB1).Width())*(*itB1).Height())>PerdidaPer)
				return false;
			else
			{
				PerdidaSegura+=((m_L-(*itB1).Width())*(*itB1).Height());
			}
		}
		//Si no es valida para el alto
		if (((m_W-(*itB1).Height())>0) && ((m_W-(*itB1).Height())<m_w))
		{
			if (((m_W-(*itB1).Height())*(*itB1).Width())>PerdidaPer)
				return false;
			else
			{
				PerdidaSegura+=((m_L-(*itB1).Width())*(*itB1).Height());
			}

		}
		/*
//		else
//		{
			if ((*itB1).GetTipo()=='H')
			{
				if (((*itB1).Width()/m_l)>m_hL)
				{
					PerdidaSegura+=(ParticionPerfecta(m_L-((*itB1).Width()))*((*itB1).Height()));
				}
				if (((*itB1).Height()/m_w)>m_hW)
				{
					PerdidaSegura+=(ParticionPerfecta(m_W-((*itB1).Height()))*((*itB1).Width()));

				}
			}
			if ((*itB1).GetTipo()=='V')
			{
				if (((*itB1).Width()/m_w)>m_vL)
				{
					PerdidaSegura+=(ParticionPerfecta(m_L-((*itB1).Width()))*((*itB1).Height()));
				}
				if (((*itB1).Height()/m_l)>m_vW)
				{
					PerdidaSegura+=(ParticionPerfecta(m_W-((*itB1).Height()))*((*itB1).Width()));

				}
			}
		}*/
		if (PerdidaSegura>(PerdidaPer)) return false;

		//Si tengo una particion que no es eficiente
		//Y me produce ya una perdida segura

	}
	return true;
}
bool PALLET::Es_Eficiente(std::list<BLOQUE> &lista)
{

	std::list<BLOQUE> ::iterator itB1;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		//Si no es valida para el ancho
		if (ParticionEficienteX((*itB1).Width(),(*itB1).GetTipo())==false) return false;
		if (ParticionEficienteY((*itB1).Height(),(*itB1).GetTipo())==false) return false;

		//Si tengo una particion que no es eficiente
		//Y me produce ya una perdida segura

	}
	return true;
}
bool PALLET::Es_Eficiente_Bloque(BLOQUE &B)
{
//	return true;
		//Si no es valida para el ancho
	if (ParticionEficienteX(B.Width(),B.GetTipo())==false) return false;
	if (ParticionEficienteY(B.Height(),B.GetTipo())==false) return false;

		//Si tengo una particion que no es eficiente
		//Y me produce ya una perdida segura
	return true;
}
bool PALLET::Es_Perfecto_Bloque(BLOQUE &B)
{
	std::list<cota> ::iterator itY,itX;
	bool perfecto=false;
	for (itY=m_Eficientes_W.begin();itY!=m_Eficientes_W.end();itY++)
	{
		if (B.GetTipo()=='H')
		{
			if ((*itY).second==(B.Height()/m_w)) perfecto=true;
		}
		if (B.GetTipo()=='V')
		{
			if ((*itY).first==(B.Height()/m_l)) perfecto=true;
		}
	}
	if (perfecto==false) return false;
	perfecto=false;
	for (itX=m_Eficientes_L.begin();itX!=m_Eficientes_L.end();itX++)
	{
		if (B.GetTipo()=='H')
		{
			if ((*itX).first==(B.Width()/m_l)) perfecto=true;
		}
		if (B.GetTipo()=='V')
		{
			if ((*itX).second==(B.Width()/m_w)) perfecto=true;
		}
	}
	if (perfecto==false) return false;
	return true;
}
bool PALLET::Es_Perfecta(int tam,char tipo,char lado)
{
	if (tam==0) return true;
	if (tam==1) return true;
	std::list<cota> ::iterator itY,itX;
//	bool perfecto=false;
	if (lado=='W')
	{
	if (tipo=='H' && (tam/m_w)==1) return true;
	if (tipo=='V' && (tam/m_l)==1) return true;
	for (itY=m_Eficientes_W.begin();itY!=m_Eficientes_W.end();itY++)
	{
		if (tipo=='H')
		{
			if ((*itY).second==(tam/m_w)) return true;
		}
		if (tipo=='V')
		{
			if ((*itY).first==(tam/m_l)) return true;
		}
	}
	}
	if (lado=='L')
	{
	if (tipo=='H' && (tam/m_l)==1) return true;
	if (tipo=='V' && (tam/m_w)==1) return true;

	for (itX=m_Eficientes_L.begin();itX!=m_Eficientes_L.end();itX++)
	{
		if (tipo=='H')
		{
			if ((*itX).first==(tam/m_l)) return true;
		}
		if (tipo=='V')
		{
			if ((*itX).second==(tam/m_w)) return true;
		}
	}
	}
	return false;

}
/*
int PALLET::Es_Eficiente(std::list<BLOQUE> &lista)
{
//	return true;
	int no_efi=0,total=0;
	std::list<BLOQUE> ::iterator itB1;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		total+=2;
		BLOQUE b=(*itB1);
		//Si no es valida para el ancho
		if (ParticionEficienteX((*itB1).Width(),(*itB1).GetTipo())==false) 
			no_efi++;;
		if (ParticionEficienteY((*itB1).Height(),(*itB1).GetTipo())==false)
			no_efi++;

		//Si tengo una particion que no es eficiente
		//Y me produce ya una perdida segura

	}
	if (total>=0 && no_efi!=total)
	{
		int por_efi=(100*(total-no_efi))/(total);
		return por_efi;
	}
	return 0;
}
*/
bool PALLET::Valida_Simetria(std::list<CRect> &lista)
{
	if (m_Simetria==false)	return true;
	double mitadP=0,pricuaP=0,totalP=0,trescuartosP=0;
	std::list<CRect> ::iterator itB1;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		totalP+=((*itB1).Height())*((*itB1).Width());
		if ((*itB1).left<(double)m_L/2)
		{
			if ((*itB1).right<(double)m_L/2)
			{
				mitadP+=(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadP+=(*itB1).Height()*(((double)m_L/2)-(*itB1).left);
			}
			if ((*itB1).top<(double)m_W/2)
			{
				if ((*itB1).bottom<(double)m_W/2)
				{
					if ((*itB1).right<(double)m_W/2)
					{
						pricuaP+=(*itB1).Height()*(*itB1).Width();
					}
					else
					{
						pricuaP+=(*itB1).Height()*(((double)m_L/2)-(*itB1).left);
					}
				}
				else
				{
					if ((*itB1).right<(double)m_W/2)
					{
						pricuaP+=(((double)m_W/2)-(*itB1).top)*(*itB1).Width();
					}
					else
					{
						pricuaP+=(((double)m_W/2)-(*itB1).top)*(((double)m_L/2)-(*itB1).left);
					}
				}
			}
		}
		if (((*itB1).left>(double)m_L/2) )
		{
			if (((*itB1).top<(double)m_L/2))
			{
				if (((*itB1).bottom<(double)m_L/2))
				{
					trescuartosP+=(*itB1).Height()*(*itB1).Width();
				}
				else
				{
					trescuartosP+=(((double)m_W/2)-(*itB1).top)*(*itB1).Width();
				}
			}
		}
/*		else
		{
			if (((*itB1).right>(double)m_L/2) )
			{
				if (((*itB1).top<(double)m_L/2))
				{
					if (((*itB1).bottom<(double)m_L/2))
					{
						trescuartosP+=(*itB1).Height()*(-((double)m_L/2)+(*itB1).right);
					}
					else
					{
						trescuartosP+=(((double)m_W/2)-(*itB1).top)*(-((double)m_L/2)+(*itB1).right);
					}
				}	
			}
		}*/
	}
//	totalP=(m_L*m_W)-((m_solbest+1)*m_l*m_w);
//	if (trescuartosP>ceil(((double)totalP*0.75)-1)) 
//		return false;
	if (pricuaP>((double)totalP/4)) 
		return false;
	if (mitadP>((double)totalP/2))
		return false;
	return true;
}//Compactamos un bloque que hemos creado nuevo
void PALLET::CompactarBloques(MOVE &M1,bool disminuir)
{

	bool compacta=false;
	std::list<BLOQUE>::iterator itL,itL2,itL3;
	std::list<BLOQUE> lista;
	std::list<BLOQUE> listaB;

	compacta=false;	
	//Quito los que sean iguales al antiguo porque ya no los voy a tener
	//Esto solo si el movimiento es de disminuir
//	BLOQUE b1;
	if 	(disminuir==true)
	{
		listaB.insert(listaB.begin(),m_lista_bloques.begin(),m_lista_bloques.end());
		itL=listaB.begin();
		do{
			if ((*itL).IsRectEmpty()!=0)
			{
				itL=listaB.erase(itL);
				continue;
			}
			if ((*itL).EqualRect(M1.GetBloqueAntiguo())) 
			{
				itL=listaB.erase(itL);
				continue;
			}
			itL++;

		}while(itL!=listaB.end());
	}
	listaB.insert(listaB.end(),M1.GetListaBloques().begin(),M1.GetListaBloques().end());
	if ((M1.GetBloqueNuevo().IsRectEmpty()==0) && (disminuir==true))
	listaB.push_back(M1.GetBloqueNuevo());

	//Compacto hasta 4 veces
	int cuenta=0;
	do{
		cuenta++;
		itL=listaB.begin();
		do{

			itL3=itL;
			itL3++;
			if (itL3==listaB.end()) break;
/*		if ((*itL).PuedoMover()==false)
		{
			itL++;
			continue;
		}
*/
			compacta=false;
			itL2=itL3;
			do{
//				BLOQUE b1=(*itL);
//				BLOQUE b2=(*itL2);
/*			if (((*itL2).right==m_L && (*itL).left==0) || ((*itL).right==m_L && (*itL2).left==0) )
			{
				itL2++;
				continue;
			}*/

				if (((*itL).BottomRight()==(*itL2).BottomRight()) &&
				((*itL).TopLeft()==(*itL2).TopLeft()) && ((*itL).GetTipo()==(*itL2).GetTipo()) )
				{
					itL2++;
					continue;
				}
				if ((*itL).GetTipo()!=(*itL2).GetTipo())
				{
					itL2++;
					continue;
				}
				bool mayor=false;
			
				//si no tienen el mismo area pero existe una perdida que si
				//lo tenga 
				//Primera condición esten a la misma altura
				//muevo las piezas a una partición eficiente
				CRect RectTemp,RectTemp1;
				if (((*itL).top==(*itL2).top) && ((*itL).bottom==(*itL2).bottom) && mayor==false)
				{
					//si tienen el mismo area que la unión de ambos
					UnionRect(&RectTemp,&(*itL),(*itL2));
					if ((((*itL).left==(*itL2).right) || ((*itL2).left==(*itL).right)) && mayor==false)
					{

						BLOQUE b(RectTemp,(*itL2).GetTipo());
						listaB.push_back(b);
						compacta=true;
						itL2=listaB.erase(itL2);
						continue;
					}


					SubtractRect(&RectTemp1,&RectTemp,&(*itL));
					SubtractRect(&RectTemp1,&RectTemp1,&(*itL2));
					//Si existe la pérdida por la derecha o por la izquierda
					if (Existe_Perdida(M1.GetListaPerdidas(),RectTemp1,8)==true)
					{
						int diferencia=RectTemp1.Width();
						CRect perdida;
						perdida.top=(*itL).TopLeft().y;
						perdida.bottom=(*itL).BottomRight().y;
						if ((*itL).right>(*itL2).right)
						{
							if (ParticionEficienteX((*itL2).left+diferencia)==true)
							{
								perdida.right=(*itL).right;
								RectTemp.left=(*itL2).left;
								perdida.left=perdida.right-diferencia;
								RectTemp.right=perdida.left;
							}
							else
							{
								perdida.left=(*itL2).left;
								RectTemp.right=(*itL).right;
								perdida.right=perdida.left+diferencia;
								RectTemp.left=perdida.right;
							}
	
						}
						else
						{
							if (ParticionEficienteX((*itL).left+diferencia)==true)
							{
								perdida.right=(*itL2).right;
								RectTemp.left=(*itL).left;
								perdida.left=perdida.right-diferencia;
								RectTemp.right=perdida.left;
							}
							else
							{
								perdida.left=(*itL).left;
								RectTemp.right=(*itL2).right;
								perdida.right=perdida.left+diferencia;
								RectTemp.left=perdida.right;
							}
						}
						M1.GetListaPerdidas().push_back(perdida);
						BLOQUE b(RectTemp,(*itL2).GetTipo());
						listaB.push_back(b);
						compacta=true;
						itL2=listaB.erase(itL2);
						continue;
					}
				}
				//Segunda condición coincidan a lo alto
				if (((*itL).left==(*itL2).left) && ((*itL).right==(*itL2).right) && mayor==false)
				{
					UnionRect(&RectTemp,&(*itL),(*itL2));
					//si tienen el mismo area que la unión de ambos
					if ((((*itL).top==(*itL2).bottom) || ((*itL2).top==(*itL).bottom)) && mayor==false)
					{
						BLOQUE b(RectTemp,(*itL2).GetTipo());
						listaB.push_back(b);
						compacta=true;
						itL2=listaB.erase(itL2);
						continue;
					}

					SubtractRect(&RectTemp1,&RectTemp,&(*itL));
					SubtractRect(&RectTemp1,&RectTemp1,&(*itL2));
					if (Existe_Perdida(M1.GetListaPerdidas(),RectTemp1,9)==true)
					{
						int diferencia=RectTemp1.Height();
						CRect perdida;
						perdida.left=(*itL).TopLeft().x;
						perdida.right=(*itL).BottomRight().x;
						if ((*itL).bottom>(*itL2).bottom)
						{
							if (ParticionEficienteY((*itL2).top+diferencia)==true)
							{
								perdida.bottom=(*itL).bottom;
								RectTemp.top=(*itL2).top;
								perdida.top=perdida.bottom-diferencia;
								RectTemp.bottom=perdida.top;	
							}
							else
							{
								perdida.top=(*itL2).top;
								RectTemp.bottom=(*itL).bottom;
								perdida.bottom=perdida.top+diferencia;
								RectTemp.top=perdida.bottom;	
							}
						}
						else
						{
							if (ParticionEficienteY((*itL).top+diferencia)==true)
							{
								perdida.bottom=(*itL2).bottom;
								RectTemp.top=(*itL).top;
								perdida.top=perdida.bottom-diferencia;
								RectTemp.bottom=perdida.top;	
							}
							else
							{
								perdida.top=(*itL).top;
								RectTemp.bottom=(*itL2).bottom;
								perdida.bottom=perdida.top+diferencia;
								RectTemp.top=perdida.bottom;	
							}
						}
						M1.GetListaPerdidas().push_back(perdida);
						BLOQUE b(RectTemp,(*itL2).GetTipo());
						listaB.push_back(b);
						compacta=true;
						itL2=listaB.erase(itL2);
						continue;
					}
	
				}
				itL2++;
			}while(itL2!=listaB.end()&& compacta!=true);
			if (compacta==true)
			{
				itL=listaB.erase(itL);
				continue;
			}
			itL++;
		}while(itL!=listaB.end());
	}while (compacta==true && cuenta<2);

	M1.GetListaBloques().clear();
	M1.GetListaBloques().insert(M1.GetListaBloques().begin(),listaB.begin(),listaB.end());
}

//La función exite perdida igual o mayor  localiza la perdida y la borra si existe
//ademas crea la nueva
bool  PALLET::Existe_Perdida(CRect &rect,int tipo)
{
	CRect Nuevo1,Nuevo2;
	bool grande=false;
	std::list<CRect> ::iterator itL;
	std::list<CRect> lista;
	for (itL=m_lista_perdidas.begin();itL!=m_lista_perdidas.end() && grande!=true;itL++)
	{
		//Si es justamente la misma que teniamos
		if (((*itL).BottomRight()==rect.BottomRight()) && ((*itL).TopLeft()==rect.TopLeft()))
		{
			itL=m_lista_perdidas.erase(itL);
			return true;
		}
		//Si no es la misma pero es mas grande
		if (((*itL).BottomRight().x>=rect.BottomRight().x) && ((*itL).TopLeft().x<=rect.TopLeft().x)
			&& ((*itL).BottomRight().y>=rect.BottomRight().y) && ((*itL).TopLeft().y<=rect.TopLeft().y))
		{
//			CRect Rect=(*itL);
			//tipo 0 es por la derecha o izquierda
			if (tipo==0)
			{
				//meto dos nuevas perdidas
				//Nuevo1 es la de arriba
				Nuevo1.left=(*itL).left;
				Nuevo1.BottomRight()=(*itL).BottomRight();
				Nuevo1.top=rect.bottom;
				//Nuevo2 es la de abajo
				Nuevo2.right=(*itL).right;
				Nuevo2.TopLeft()=(*itL).TopLeft();
				Nuevo2.bottom=rect.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				//Poner ahora la nueva perdida
				itL=m_lista_perdidas.erase(itL);
				grande=true;
			}
			//tipo 1 es por arriba o abajo
			else
			{
				Nuevo1.right=rect.left;
				Nuevo1.TopLeft()=(*itL).TopLeft();
				Nuevo1.bottom=(*itL).bottom;
				//Nuevo2 es la de abajo
				Nuevo2.BottomRight()=(*itL).BottomRight();
				Nuevo2.left=rect.right;
				Nuevo2.top=rect.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				//Poner ahora la nueva perdida
				itL=m_lista_perdidas.erase(itL);
				grande=true;
			}
		}
	}
	if (grande==true) 
	{
		for (itL=lista.begin();itL!=lista.end();itL++)
		{
			m_lista_perdidas.push_back((*itL));
		}
		return true;
	}
	return false;
}
int  PALLET::ProximoBloque(BLOQUE &B,int tipo)
{
	CRect Nuevo1,Nuevo2;
	int menor=1000;
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
//		BLOQUE b2=(*itB);

		//Si tipo es uno busco el pegado a la izquierda
		if (tipo==1)
		{
			if ((*itB).right<=B.left)
			{
				if ((((*itB).right==B.left) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| (((*itB).right==B.left) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| (((*itB).right==B.left) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| (((*itB).right==B.left) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				return 0;
				if (( ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| ( ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| ( ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| ( ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				{
					if ((B.left-(*itB).right)<menor)
					{
						menor=B.left-(*itB).right;
					}
				}
			}
		}
		//Si tipo es uno busco el pegado a la derecha
		if (tipo==2)
		{
			if ((*itB).left>=B.right)
			{
				if ((((*itB).left==B.right) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| (((*itB).left==B.right) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| (((*itB).left==B.right) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| (((*itB).left==B.right) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				return 0;
				if (( ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| ( ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| ( ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| ( ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				{
					if (((*itB).left-B.right)<menor)
					{
						menor=((*itB).left-B.right);
					}
				}
			}
		}
		//Si tipo es uno busco el pegado a abajo
		if (tipo==3)
		{
			if ((*itB).bottom<=B.top)
			{
				if ((((*itB).bottom==B.top) && ((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).bottom==B.top) && ((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).bottom==B.top) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).bottom==B.top) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
				return 0;
				if ((((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).left>=B.left) && ((*itB).right<=B.right)))
				{
					if ((B.top-(*itB).bottom)<menor)
					{
						menor=(B.top-(*itB).bottom);
					}
				}
			}
		}
		//Si tipo es uno busco el pegado a arriba
		if (tipo==4)
		{
			if ((*itB).top>=B.bottom)
			{
				if ((((*itB).top==B.bottom) && ((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).top==B.bottom) && ((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).top==B.bottom) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).top==B.bottom) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
				return 0;
				if ((((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).left>=B.left) && ((*itB).right<=B.right)))
				{
					if (((*itB).top-B.bottom)<menor)
					{
						menor=((*itB).top-B.bottom);
					}
				}
			}
		}

	}
	if (menor==1000) return 0;
	else return menor;
	return 0;
}
int  PALLET::ProximoBloque(std::list<BLOQUE> &lista,BLOQUE &B,int tipo)
{
	CRect Nuevo1,Nuevo2;
	int menor=1000;
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
//		BLOQUE b2=(*itB);

		//Si tipo es uno busco el pegado a la izquierda
		if (tipo==1)
		{
			if ((*itB).right<=B.left)
			{
				if ((((*itB).right==B.left) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| (((*itB).right==B.left) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| (((*itB).right==B.left) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| (((*itB).right==B.left) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				return 0;
				if (( ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| ( ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| ( ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| ( ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				{
					if ((B.left-(*itB).right)<menor)
					{
						menor=B.left-(*itB).right;
					}
				}
			}
		}
		//Si tipo es uno busco el pegado a la derecha
		if (tipo==2)
		{
			if ((*itB).left>=B.right)
			{
				if ((((*itB).left==B.right) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| (((*itB).left==B.right) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| (((*itB).left==B.right) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| (((*itB).left==B.right) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				return 0;
				if (( ((*itB).top>B.top) && ((*itB).top<B.bottom))
				|| ( ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
				|| ( ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
				|| ( ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
				{
					if (((*itB).left-B.right)<menor)
					{
						menor=((*itB).left-B.right);
					}
				}
			}
		}
		//Si tipo es uno busco el pegado a abajo
		if (tipo==3)
		{
			if ((*itB).bottom<=B.top)
			{
				if ((((*itB).bottom==B.top) && ((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).bottom==B.top) && ((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).bottom==B.top) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).bottom==B.top) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
				return 0;
				if ((((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).left>=B.left) && ((*itB).right<=B.right)))
				{
					if ((B.top-(*itB).bottom)<menor)
					{
						menor=(B.top-(*itB).bottom);
					}
				}
			}
		}
		//Si tipo es uno busco el pegado a arriba
		if (tipo==4)
		{
			if ((*itB).top>=B.bottom)
			{
				if ((((*itB).top==B.bottom) && ((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).top==B.bottom) && ((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).top==B.bottom) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).top==B.bottom) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
				return 0;
				if ((((*itB).left>B.left) && ((*itB).left<B.right))
				|| (((*itB).right>B.left) && ((*itB).right<B.right))
				|| (((*itB).left<=B.left) && ((*itB).right>=B.right))
				|| (((*itB).left>=B.left) && ((*itB).right<=B.right)))
				{
					if (((*itB).top-B.bottom)<menor)
					{
						menor=((*itB).top-B.bottom);
					}
				}
			}
		}

	}
	if (menor==1000) return 0;
	else return menor;
	return 0;
}
void  PALLET::ProximoBloque(std::list<CRect> &listaP,BLOQUE &B,int tipo,CRect &rect)
{
	CRect Nuevo1,Nuevo2;
	int menor=1000;
	std::list<CRect> ::iterator itB;
	for (itB=listaP.begin();itB!=listaP.end();itB++)
	{
		if (tipo==1)
		{
		//Por la izquierda
		//Si a la izquierda
		if (((((*itB).right==B.left) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
		|| (((*itB).right==B.left) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
		|| (((*itB).right==B.left) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
		|| (((*itB).right==B.left) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom))))
		{
			rect=(*itB);
			return;
		}
		}
		if (tipo==2)
		{
		//Si a la derecha
		if (((((*itB).left==B.right) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
		|| (((*itB).left==B.right) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
		|| (((*itB).left==B.right) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
		|| (((*itB).left==B.right) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom))))
		{
			rect=(*itB);
			return;
		}
		}
		if (tipo==3)
		{
		//Si a abajo
		if (((((*itB).bottom==B.top) && ((*itB).left>B.left) && ((*itB).left<B.right))
		|| (((*itB).bottom==B.top) && ((*itB).right>B.left) && ((*itB).right<B.right))
		|| (((*itB).bottom==B.top) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
		|| (((*itB).bottom==B.top) && ((*itB).left>=B.left) && ((*itB).right<=B.right))))
		{
			rect=(*itB);
			return;
		}
		}
		if (tipo==4)
		{
		//Si a arriba
		if (((((*itB).top==B.bottom) && ((*itB).left>B.left) && ((*itB).left<B.right))
		|| (((*itB).top==B.bottom) && ((*itB).right>B.left) && ((*itB).right<B.right))
		|| (((*itB).top==B.bottom) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
		|| (((*itB).top==B.bottom) && ((*itB).left>=B.left) && ((*itB).right<=B.right))))
		{
			rect=(*itB);
			return;
		}
		}

	}
	return ;
}

int PALLET::Rectangulo_menor_estan_perdidas(std::list<CRect> &lista)
{
	std::list<CRect> ::iterator itC;
	CRect Union(0,0,0,0);
	int medida_union=0;

	bool no_quiero_tiene_borde=false;
//	int MasGrande=(((m_W/2)+(m_L/2))*10);
	double multi=100;
	double peso=0.25;
	int suma_huecos=0;
//	int MasGrande=(peso*(multi*((m_W/2)+(m_L/2)))+(1-peso)*(m_L*m_W));
	int MasGrande=(peso*(multi*((m_W/2)+(m_L/2)))+(1-peso)*(m_L*m_W));
	int MasGrande2=2*m_L+2*m_W;
	int MasGrande11=2*pow((m_L/2),3);
	int MasGrande13=m_L*m_W;
	bool prime=false;
	if (m_tipo_rectangulo==1 || m_tipo_rectangulo==2 || m_tipo_rectangulo==3 || m_tipo_rectangulo==15 || m_tipo_rectangulo==5)
	{
		for (itC=lista.begin();itC!=lista.end();itC++)
		{
			if (m_tipo_rectangulo==2) suma_huecos=(*itC).Width()+(*itC).Height()+(m_W-(*itC).top)+(m_L-(*itC).left);
			if ((*itC).left==0 || (*itC).right==m_L || (*itC).top==0 || (*itC).bottom==m_W)
				no_quiero_tiene_borde=true;
//			if (m_tipo_rectangulo!=5 && prime==true) UnionRect(&Union,&(*itC),&Union);
			//Antiguo para mirar lo de eficientes o no
//			if (!((*itC).Height()==m_G4_HuecoV && (*itC).Width()==m_G4_HuecoH) && m_tipo_rectangulo==5  )
//				UnionRect(&Union,&(*itC),&Union);
			//Nuevo
			if (Es_un_huecoG4((*itC).Width(),(*itC).Height())!=true && m_tipo_rectangulo==5)
				UnionRect(&Union,&(*itC),&Union);
			prime=true;
		}

	}
	if (Union.top==0 && Union.bottom==0) return 0;
	if (m_tipo_rectangulo==1)
	{
//		medida_union=abs((m_W/2)-Union.top)+abs((m_W/2)-Union.bottom)+abs((m_L/2)-Union.right)+abs((m_L/2)-Union.left);
		
		medida_union=multi*(abs((m_W/2)-Union.CenterPoint().y)+abs((m_L/2)-Union.CenterPoint().x));
//		if (no_quiero_tiene_borde==true) medida_union+=(m_L*m_W);
		medida_union=(peso*(medida_union)+(1-peso)*(Union.Width()*Union.Height()));
		double temp=(double)medida_union/(double)MasGrande;
		medida_union=temp*m_F_Rectangulo;

	}
	if (m_tipo_rectangulo==5)
	{
//		medida_union=abs((m_W/2)-Union.top)+abs((m_W/2)-Union.bottom)+abs((m_L/2)-Union.right)+abs((m_L/2)-Union.left);
		
		medida_union=multi*(abs((m_W*(0.63))-Union.CenterPoint().y)+abs((m_L*(0.63))-Union.CenterPoint().x));
//		if (no_quiero_tiene_borde==true) medida_union+=(m_L*m_W);
		medida_union=(peso*(medida_union)+(1-peso)*(Union.Width()*Union.Height()));
		double temp=(double)medida_union/(double)MasGrande;
		medida_union=temp*m_F_Rectangulo;
//		medida_union=medida_union;

	}
	//Solo tiene en cuenta el centro del rectángulo
	if (m_tipo_rectangulo==15)
	{
		medida_union=abs((m_W/2)-Union.CenterPoint().y)+abs((m_L/2)-Union.CenterPoint().x);
		if (no_quiero_tiene_borde==true) medida_union+=(m_L*m_W);
		medida_union=(multi*medida_union);
		MasGrande=(((m_W/2)+(m_L/2))*multi);
		double temp=(double)medida_union/(double)MasGrande;
		medida_union=temp*m_F_Rectangulo;

	}

	if (m_tipo_rectangulo==2)
	{
		double temp=(double)suma_huecos/(double)MasGrande2;
		medida_union=temp*m_F_Rectangulo;
	}
	if (m_tipo_rectangulo==3)
	{

		medida_union=4;
		if (Union.top==0)	medida_union--;
		if (Union.bottom==m_W)	medida_union--;
		if (Union.left==0)	medida_union--;
		if (Union.right==m_L)	medida_union--;

	}
	if (m_tipo_rectangulo==4)
	{
		for (itC=lista.begin();itC!=lista.end();itC++)
		{
			if ((*itC).top==0)	medida_union+=(*itC).Height();
			if ((*itC).bottom==m_W)	medida_union+=(*itC).Height();
			if ((*itC).left==0)	medida_union+=(*itC).Width();
			if ((*itC).right==m_L)	medida_union+=(*itC).Width();
		}
		medida_union=100*medida_union;
	}
	if (m_tipo_rectangulo==9)
	{
		for (itC=lista.begin();itC!=lista.end();itC++)
		{
			if ( (*itC).Height()!=m_G4_HuecoH && (*itC).Width()!=m_G4_HuecoV)
			{
				UnionRect(&Union,&(*itC),&Union);	
			}
		}
		medida_union=abs((m_W/2)-Union.top)+abs((m_W/2)-Union.bottom)+abs((m_L/2)-Union.right)+abs((m_L/2)-Union.left);
		medida_union=((10*medida_union)+Union.Width()*Union.Height());
		double temp=(double)medida_union/(double)MasGrande;
		medida_union=temp*m_F_Rectangulo;

	}
//	fprintf(fin,"%d\n",medida_union);

	return medida_union;
}
bool  PALLET::Existe_Perdida(CRect &rect)
{
	std::list<CRect> ::iterator itL;
	for (itL=m_lista_perdidas.begin();itL!=m_lista_perdidas.end() ;itL++)
	{
		//Si es justamente la misma que teniamos
		if (((*itL).BottomRight()==rect.BottomRight()) && ((*itL).TopLeft()==rect.TopLeft()))
		{
			itL=m_lista_perdidas.erase(itL);
			return true;
		}
	}

	return false;
}
bool  PALLET::Existe_Perdida(std::list<CRect> &lista,CRect &rect)
{
	std::list<CRect> ::iterator itL;
	for (itL=lista.begin();itL!=lista.end() ;itL++)
	{
		//Si es justamente la misma que teniamos
		if (((*itL).BottomRight()==rect.BottomRight()) && ((*itL).TopLeft()==rect.TopLeft()))
		{
			itL=lista.erase(itL);
			return true;
		}
	}

	return false;
}
bool  PALLET::Existe_Perdida(std::list<CRect> &listaP,CRect &rect,int tipo)
{
	CRect Nuevo1,Nuevo2;
	bool grande=false;
	std::list<CRect> ::iterator itL;
	std::list<CRect> lista;
	for (itL=listaP.begin();itL!=listaP.end() && grande!=true;itL++)
	{
		CRect cuadra=(*itL);
		//Si es justamente la misma que teniamos
		if (((*itL).BottomRight()==rect.BottomRight()) && ((*itL).TopLeft()==rect.TopLeft()))
		{
			itL=listaP.erase(itL);
			return true;
		}
		//Busco una perdida igual
		if (tipo>=8)
		{
		if (((*itL).right>=rect.right) && ((*itL).left<=rect.left)
			&& ((*itL).bottom>=rect.bottom) && ((*itL).top<=rect.top))
		{
			CRect Rect=(*itL);
			//tipo 0 es por la derecha o izquierda
			if (tipo==8)
			{
				//meto dos nuevas perdidas
				//Nuevo1 es la de arriba
				Nuevo1.left=(*itL).left;
				Nuevo1.BottomRight()=(*itL).BottomRight();
				Nuevo1.top=rect.bottom;
				//Nuevo2 es la de abajo
				Nuevo2.right=(*itL).right;
				Nuevo2.TopLeft()=(*itL).TopLeft();
				Nuevo2.bottom=rect.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				//Poner ahora la nueva perdida
				itL=listaP.erase(itL);
				grande=true;
			}
			//tipo 1 es por arriba o abajo
			else
			{
				Nuevo1.right=rect.left;
				Nuevo1.TopLeft()=(*itL).TopLeft();
				Nuevo1.bottom=(*itL).bottom;
				//Nuevo2 es la de abajo
				Nuevo2.BottomRight()=(*itL).BottomRight();
				Nuevo2.left=rect.right;
				Nuevo2.top=rect.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				//Poner ahora la nueva perdida
				itL=listaP.erase(itL);
				grande=true;
			}
		}
		}
		else
		{
		//Si no es la misma pero es mas grande
		if (((*itL).right==rect.left) && (tipo==1)
			&& ((*itL).bottom>=rect.bottom) && ((*itL).top<=rect.top))
		{
			//tipo 1 es por la izquierda
			//meto dos nuevas perdidas
			//Nuevo1 es la de arriba
			Nuevo1.left=(*itL).left;
			Nuevo1.BottomRight()=(*itL).BottomRight();
			Nuevo1.top=rect.bottom;
			//Nuevo2 es la de abajo
			Nuevo2.right=(*itL).right;
			Nuevo2.TopLeft()=(*itL).TopLeft();
			Nuevo2.bottom=rect.top;
			rect.left=(*itL).left;
			rect.right=rect.right-(*itL).Width();

			if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
			if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			//Poner ahora la nueva perdida
			itL=listaP.erase(itL);
			grande=true;
		}
		//Si no es la misma pero es mas grande
		if (((*itL).left==rect.right) && (tipo==2)
			&& ((*itL).bottom>=rect.bottom) && ((*itL).top<=rect.top))
		{

			//tipo 2 es por la derecha
			//meto dos nuevas perdidas
			//Nuevo1 es la de arriba
			Nuevo1.left=(*itL).left;
			Nuevo1.BottomRight()=(*itL).BottomRight();
			Nuevo1.top=rect.bottom;
			//Nuevo2 es la de abajo
			Nuevo2.right=(*itL).right;
			Nuevo2.TopLeft()=(*itL).TopLeft();
			Nuevo2.bottom=rect.top;
			rect.right=(*itL).right;
			rect.left=rect.left+(*itL).Width();

			if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
			if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			//Poner ahora la nueva perdida
			itL=listaP.erase(itL);
			grande=true;
		}

		//Si no es la misma pero es mas grande
		if (((*itL).right>=rect.right) && ((*itL).left<=rect.left)
			&& ((*itL).bottom==rect.top) && (tipo==3))
		{

			//tipo 3 es por abajo
			//Nuevo 1 es por la izquierda
			Nuevo1.right=rect.left;
			Nuevo1.TopLeft()=(*itL).TopLeft();
			Nuevo1.bottom=(*itL).bottom;
			//Nuevo2 es la de abajo
			Nuevo2.BottomRight()=(*itL).BottomRight();
			Nuevo2.left=rect.right;
			Nuevo2.top=(*itL).top;
			rect.top=(*itL).top;
			rect.bottom=rect.bottom-(*itL).Height();

			if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
			if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			//Poner ahora la nueva perdida
			itL=listaP.erase(itL);
			grande=true;
		}
		//Si no es la misma pero es mas grande
		if (((*itL).right>=rect.right) && ((*itL).left<=rect.left)
			&& ((*itL).top==rect.bottom) && (tipo==4))
		{
			//Tipo 4 es por arriba
			Nuevo1.right=rect.left;
			Nuevo1.TopLeft()=(*itL).TopLeft();
			Nuevo1.bottom=(*itL).bottom;
			//Nuevo2 es la de abajo
			Nuevo2.BottomRight()=(*itL).BottomRight();
			Nuevo2.left=rect.right;
			Nuevo2.top=(*itL).top;
			rect.bottom=(*itL).bottom;
			rect.top=rect.top+(*itL).Height();

			if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
			if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			//Poner ahora la nueva perdida
			itL=listaP.erase(itL);
			grande=true;
		}
		}
		
	}
	if (grande==true) 
	{
		for (itL=lista.begin();itL!=lista.end();itL++)
		{
			listaP.push_back((*itL));
		}
		return true;
	}
	return false;
}


/*
//PAletizar con dos bloques
std::list<BLOQUE> PALLET::Paletizar(std::list<CRect> &lista,char tipo)
{
//	std::list<strg4> ::iterator itg;
	std::list<CRect> ::iterator itL;
	std::list<BLOQUE> lista_bloques;
	BLOQUE B1(0,0,0,0,'H');
	BLOQUE B2(0,0,0,0,'V');
	int l=m_l,w=m_w;
	if (tipo=='H') 
	{
		l=m_w;
		w=m_l;
	}
	bool colocado=false;
	bool continuar=false;
	//Si coloco una en el otro sentido ya es diferente
	bool seguir=true;
	if (tipo=='X') colocado=true;
	if (tipo!='X')
	{
		do{
			continuar=false;

	itL=lista.begin();
	do {

		if ((*itL).IsRectEmpty())
		{
			itL=lista.erase(itL);
			continue;
		}
		if (!(((*itL).Width()>=l) && ((*itL).Height()>=w)) )
		{
			itL++;
			continue;
		}
		if ((*itL).Width()*(*itL).Height()<m_l*m_w) 
		{
			itL++;
			continue;
		}
	//	Val+=Heuristico1Bloque((*itL),tipo);
		//Tengo que colocar el bloque 
		//en la esquina más cercana 
		//Cuatro casos
		//esquina inferior derecha
		//Que esquina está más cercana

		ColocarEsquinaMasCercana(lista,B1,B2,(*itL),tipo);
		//1 esquina inferior izquierda
		//2 esquina superior izquierda
		//3 esquina superior derecha
		//4 esquina inferior derecha
		if (!B1.IsRectEmpty())
		{
			if (lista.size()>1) 	itL=lista.erase(itL);
			else
			{
				lista.clear();
				itL=lista.end();
			}
			colocado=true;
			lista_bloques.push_back(B1);
			if (!B2.IsRectEmpty()) lista_bloques.push_back(B2);
			continuar=true;

			continue;
		}
		itL++;

	}while(itL!=lista.end());
	}while(continuar==true );
	//Si ha colocado alguna ya puedo colocar de la otra manera
	//intento colocar de la forma antigua
	if (lista.size()==0) return lista_bloques;
	}

	if (colocado==true)
	{
		char tipo2='H';
//		lista=CompactarPerdida(lista);
		if (tipo=='H') tipo2='H';
		if (tipo=='V') tipo2='V';
		do
		{
			continuar=false;

			lista=JuntarPerdida(lista,tipo2);
			itL=lista.begin();
			do
			{
				if ((*itL).IsRectEmpty())
				{
					itL=lista.erase(itL);
					continue;
				}
				if (!(((*itL).Width()>=w) && ((*itL).Height()>=l)) && !(((*itL).Width()>=l) && ((*itL).Height()>=w)) )
				{
					itL++;
					continue;
				}
		//Si es mejor colocar verticales que horizontales
		if ((((*itL).Width()/m_w)*((*itL).Height()/m_l))>(((*itL).Width()/m_l)*((*itL).Height()/m_w)))
		{
			if ((*itL).Width()>=m_w && (*itL).Height()>=m_l)
			{
				tipo2='H';
				ColocarEsquinaMasCercana(lista,B1,B2,(*itL),tipo2);
				itL=lista.erase(itL);
				lista_bloques.push_back(B1);
				if (!B2.IsRectEmpty()) lista_bloques.push_back(B2);

				continuar=true;
				continue;
			}
		}
		//En otro caso coloco horizontales
		else
		{
			if ((*itL).Width()>=m_l && (*itL).Height()>=m_w)
			{
				tipo2='V';
				ColocarEsquinaMasCercana(lista,B1,B2,(*itL),tipo2);
				itL=lista.erase(itL);
				lista_bloques.push_back(B1);
				if (!B2.IsRectEmpty()) lista_bloques.push_back(B2);

				continuar=true;
				continue;
			}
		}
			//1 esquina inferior izquierda
			//2 esquina superior izquierda
			//3 esquina superior derecha
			//4 esquina inferior derecha
			itL++;
		}while(itL!=lista.end());
		}while(continuar==true);


	}

	return lista_bloques;
}*/
std::list<BLOQUE> PALLET::Paletizar(std::list<CRect> &lista,char tipo)
{
//	std::list<strg4> ::iterator itg;
	std::vector<strg4> ::iterator itg;
	std::list<CRect> ::iterator itL;
	std::list<BLOQUE> lista_bloques;
	BLOQUE B1(0,0,0,0,'H');
	int l=m_l,w=m_w;
	if (tipo=='H') 
	{
		l=m_w;
		w=m_l;
	}
	bool colocado=false;
	bool continuar=false;
	//Si coloco una en el otro sentido ya es diferente
	bool seguir=true;
	if (tipo=='X') colocado=true;
	if (tipo!='X')
	{
		do{
			continuar=false;

	itL=lista.begin();
	do {
//	for(itL=lista.begin();itL!=lista.end();itL++)
//	{24 13 5 2
		bool G4_recursivo_largo=false;
		bool G4_recursivo=false;
		bool G4_normal=false;

		CRect rec=(*itL);
		if ((*itL).IsRectEmpty())
		{
			itL=lista.erase(itL);
			continue;
		}
//		if (((*itL).Width()<m_w || (*itL).Height()<m_w) || ((*itL).Width()<m_l && (*itL).Height()<m_l)
//			|| ((*itL).Width()<m_l) || ((*itL).Height()<w))
		if (!(((*itL).Width()>=l) && ((*itL).Height()>=w)) )
		{
			itL++;
			continue;
		}
		if ((*itL).Width()*(*itL).Height()<m_l*m_w) 
		{
			itL++;
			continue;
		}
		//Esto es para que si puedo colocar algo que sea horizontal o vertical y va ser 
		//mejor no tengo que explorar estructuras g4
		bool estudiar_g4=false;
		int max_parcial=((*itL).Width())*((*itL).Height())/(m_l*m_w);
		if (((*itL).Width()/l)*((*itL).Height()/w)==max_parcial)
			estudiar_g4=false;
		else
			estudiar_g4=true;
		//Tambien debo intentar quedarme con la mejor estructura G4
		//Función para encontrar la mejor combinación g4 y el tipo
		std::vector<int>::iterator itg4int;
		for (itg4int=m_lista_intG4.begin();itg4int!=m_lista_intG4.end() && G4_normal!=true && G4_recursivo!=true && G4_recursivo_largo!=true && estudiar_g4==true;itg4int++)
		{
			m_G4_TCajas=m_lista_GCuatros[*itg4int].G4_TCajas;
			m_G4_THorizontal=m_lista_GCuatros[*itg4int].G4_THorizontal;
			m_G4_TVertical=m_lista_GCuatros[*itg4int].G4_TVertical;
			m_G4_HuecoH=m_lista_GCuatros[*itg4int].G4_HuecoH;
			m_G4_HuecoV=m_lista_GCuatros[*itg4int].G4_HuecoV;
			m_G4_CajasH=m_lista_GCuatros[*itg4int].G4_CajasH;
			m_G4_CajasV=m_lista_GCuatros[*itg4int].G4_CajasV;
			m_G4_CajasHH=m_lista_GCuatros[*itg4int].G4_CajasHH;
			m_G4_CajasVV=m_lista_GCuatros[*itg4int].G4_CajasVV;
			m_G4_PequeH=m_lista_GCuatros[*itg4int].G4_PequeH;
			m_G4_PequeV=m_lista_GCuatros[*itg4int].G4_PequeV;
			if ((m_G4_HuecoH*m_G4_HuecoV)>m_perdidaCota) continue;

			//Posible estructura G4 encadenado dos formas a lo ancho
			seguir=true;
			int largo=m_G4_CajasHH*m_l,ancho=m_G4_CajasH*m_w;
			if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
			{
				largo=m_w*m_G4_CajasV;
				ancho=m_G4_CajasVV*m_l;
			}

			//Recursivo con diferente número de cajas
			if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV) && (m_iter_actual==-1))
			{
				//No puedo colocar más cajas verticales
				if (m_G4_CajasV+1>m_vL)
				{
					ancho=m_G4_CajasH*m_w;
					largo=m_l*m_G4_CajasVV;
				}
				else
				{
					largo=m_G4_CajasV*m_w;
					ancho=m_l*m_G4_CajasHH;
				}
				if ((((*itL).Width()/(m_G4_THorizontal+largo))>0) && (((*itL).Height()/(m_G4_TVertical+ancho))>0) )
				{

					for (int register i=__min((((*itL).Width()-m_G4_THorizontal)/largo),(((*itL).Height()-m_G4_TVertical)/(ancho)));i>=1 && seguir==true;i--)
					{
						int kk=((((m_G4_THorizontal+(m_l*i))*(m_G4_TVertical+(m_w*i*m_G4_CajasH)))-(i*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w));

						int kk2=((*itL).Width()/m_G4_THorizontal)*(((*itL).Height()/m_G4_TVertical)*m_G4_TCajas);
						//solo una estructura
	//					for(int register j=((*itL).Width()/(m_G4_THorizontal+(largo*i)));((j>=1) && (seguir==true));j--)
//				{
						//Si no existe este G4 en el optimo no lo voy a meter
						if ((i*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
						{
						//Condición para que sea la mejor
						if (((((*itL).Width()/l)*((*itL).Height()/w))<(((((m_G4_TVertical+(largo*i))*(m_G4_THorizontal+(i*ancho)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w)) + (__max(((((*itL).Width()-m_G4_THorizontal+(ancho*i))/w)*(((*itL).Height()-(m_G4_TVertical+(largo*i)))/l)),((((*itL).Width()-m_G4_THorizontal+(ancho*i))/l)*(((*itL).Height()-(m_G4_TVertical+(largo*i)))/w))))))
	//					&& (max_parcial<=(((((m_G4_TVertical+(largo*i))*(m_G4_THorizontal+(i*ancho)))-(i*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))))
						&&(((*itL).Width()/m_G4_THorizontal)*(((*itL).Height()/m_G4_TVertical)*m_G4_TCajas)<(((((m_G4_TVertical+(largo*i))*(m_G4_THorizontal+(i*ancho)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w)))))
						{
							ColocarG4(lista,lista_bloques,(*itL),'a',i,1,1);	
							if (lista.size()>1) 	itL=lista.erase(itL);
							else
							{
								lista.clear();
								itL=lista.end();
							}
							colocado=true;
							seguir=false;
							G4_recursivo=true;
							continuar=true;
	
						}
					}
				}
			}
		

		}
		if ((((*itL).Width()/(m_G4_THorizontal+largo))>0) && (((*itL).Height()/(m_G4_TVertical+ancho))>0) && m_G4_CajasH==m_G4_CajasV )
		{

			for (int register i=__min((((*itL).Width()-m_G4_THorizontal)/largo),(((*itL).Height()-m_G4_TVertical)/(ancho)));i>=1 && seguir==true;i--)
			{
				for(int register j=((*itL).Width()/(m_G4_THorizontal+(largo*i)));((j>=1) && (seguir==true));j--)
				{
					if (((i+1)*j*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
					{

					//Condición para que sea la mejor
					if (((((*itL).Width()/l)*((*itL).Height()/w))<(((((m_G4_TVertical+(largo*i))*(m_G4_THorizontal+(i*ancho)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))*j))
//					 && (max_parcial<=(((((m_G4_TVertical+(largo*i))*(m_G4_THorizontal+(i*ancho)))-(i*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))*j))
					&&(((*itL).Width()/m_G4_THorizontal)*(((*itL).Height()/m_G4_TVertical)*m_G4_TCajas)<(((((m_G4_TVertical+(largo*i))*(m_G4_THorizontal+(i*ancho)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w)))*j))
					{
						ColocarG4(lista,lista_bloques,(*itL),'A',i,j,1);	
						if (lista.size()>1) 	itL=lista.erase(itL);
						else
						{
							lista.clear();
							itL=lista.end();
						}
						colocado=true;
						seguir=false;
						continuar=true;
						G4_recursivo=true;
	
					}
					}
				}
			}
		}
		if (G4_recursivo==true) continue;
		//Posible estructura G4 encadenado dos formas a lo largo
		seguir=true;
		largo=m_G4_CajasVV*m_l,ancho=m_w*m_G4_CajasV;
		if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
		{
			largo=m_G4_CajasH*m_w;
			ancho=m_G4_CajasHH*m_l;
		}

		if ((((*itL).Width()/(m_G4_THorizontal+ancho))>0) && (((*itL).Height()/(m_G4_TVertical+largo))>0) )
		{

			for (int register i=__min((((*itL).Width()-m_G4_THorizontal)/ancho),(((*itL).Height()-m_G4_TVertical)/(largo)));i>=1 && seguir==true;i--)
			{
				for(int register j=((*itL).Width()/(m_G4_THorizontal+(ancho*i)));((j>=1) && (seguir==true));j--)
				{
					if (((i+1)*j*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
					{
					//Condición para que sea la mejor
					if (((((*itL).Width()/l)*((*itL).Height()/w))<((((((m_G4_THorizontal+(ancho*i))*(m_G4_TVertical+(i*largo)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))*j))+((((*itL).Width()-(m_G4_THorizontal+(ancho*i)))/l)*(((*itL).Height()-(m_G4_TVertical+(largo*i)))/w)))
//					&& (max_parcial<=((((((m_G4_THorizontal+(ancho*i))*(m_G4_TVertical+(i*largo)))-(i*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w))*j))+((((*itL).Width()-(m_G4_THorizontal+(ancho*i)))/l)*(((*itL).Height()-(m_G4_TVertical+(largo*i)))/w)))
					&&(((*itL).Width()/m_G4_THorizontal)*(((*itL).Height()/m_G4_TVertical)*m_G4_TCajas)<(((((m_G4_THorizontal+(ancho*i))*(m_G4_TVertical+(i*largo)))-((i+1)*m_G4_HuecoH*m_G4_HuecoV))/(m_l*m_w)))*j))
					{
						ColocarG4(lista,lista_bloques,(*itL),'L',i,j,1);	
						if (lista.size()>1) 	itL=lista.erase(itL);
						else
						{
							lista.clear();
							itL=lista.end();
						}
						colocado=true;
						seguir=false;
						G4_recursivo_largo=true;
						continuar=true;
	
					}
					}
				}
			}
		}
		if (G4_recursivo_largo==true) continue;
		seguir=true;
		//Posible estructura G4 repetidos
		if ((((*itL).Width()/m_G4_THorizontal)>0) && (((*itL).Height()/m_G4_TVertical)>0) )
		{
		for (int register i=((*itL).Width()/m_G4_THorizontal);i>=1 && seguir==true;i--)
		{
			for (int register j=((*itL).Height()/m_G4_TVertical);j>=1 && seguir==true;j--)
			{
				if ((i*j*m_G4_HuecoH*m_G4_HuecoV)<=m_perdidaCota)
				{
				
				if ((((((*itL).Width()/l)*((*itL).Height()/w))<((i*j*m_G4_TCajas))+(((((*itL).Width()-m_G4_THorizontal*i)/l)*(((*itL).Height()-m_G4_TVertical*j)/w)))))
					|| (((((*itL).Width()/l)*((*itL).Height()/w))<((i*j*m_G4_TCajas))+(((((*itL).Width()-m_G4_THorizontal*i)/w)*(((*itL).Height()-m_G4_TVertical*j)/l))))))
//				if (((max_parcial<=((i*j*m_G4_TCajas))+(((((*itL).Width()-m_G4_THorizontal*i)/l)*(((*itL).Height()-m_G4_TVertical*j)/w)))))
//					|| ((max_parcial<=((i*j*m_G4_TCajas))+(((((*itL).Width()-m_G4_THorizontal*i)/w)*(((*itL).Height()-m_G4_TVertical*j)/l))))))
				{
					ColocarG4(lista,lista_bloques,(*itL),'H',i,j,1);	
					if (lista.size()>1) 	itL=lista.erase(itL);
					else
					{
						lista.clear();
						itL=lista.end();
					}
					colocado=true;
					seguir=false;
					G4_normal=true;
					continuar=true;

				}
				}
			}
		}
		}
		if (G4_normal==true) continue;
		}
		//	Val+=Heuristico1Bloque((*itL),tipo);
		//Tengo que colocar el bloque 
		//en la esquina más cercana 
		//Cuatro casos
		//esquina inferior derecha
		//Que esquina está más cercana

		ColocarEsquinaMasCercana(lista,B1,(*itL),tipo);
		if (tipo=='H')  B1.SetTipo('V');
		if (tipo=='V')  B1.SetTipo('H');
		//1 esquina inferior izquierda
		//2 esquina superior izquierda
		//3 esquina superior derecha
		//4 esquina inferior derecha
		if (!B1.IsRectEmpty())
		{
			if (lista.size()>1) 	itL=lista.erase(itL);
			else
			{
				lista.clear();
				itL=lista.end();
			}
			colocado=true;
			lista_bloques.push_back(B1);
			continuar=true;

			continue;
		}
		itL++;

	}while(itL!=lista.end());
	}while(continuar==true );
	//Si ha colocado alguna ya puedo colocar de la otra manera
	//intento colocar de la forma antigua
	if (lista.size()==0) return lista_bloques;
	}

	if (colocado==true)
	{
		char tipo2='H';
//		lista=CompactarPerdida(lista);
		if (tipo=='H') tipo2='H';
		if (tipo=='V') tipo2='V';
		do
		{
			continuar=false;

			lista=JuntarPerdida(lista,tipo2);
			itL=lista.begin();
			do
			{
				CRect rec=(*itL);
				if ((*itL).IsRectEmpty())
				{
					itL=lista.erase(itL);
					continue;
				}
				if (!(((*itL).Width()>=w) && ((*itL).Height()>=l)) && !(((*itL).Width()>=l) && ((*itL).Height()>=w)) )
				{
					itL++;
					continue;
				}
				//	Val+=Heuristico1Bloque((*itL),tipo);
					//Tengo que colocar el bloque 
				//en la esquina más cercana 
					//Cuatro casos
				//esquina inferior derecha
				//Que esquina está más cercana
				//vertical
				//Debería buscar el máximo de todos los posibles que me permitan
				int max=0,huecomin=9999;
				bool g4=false;
				//Estudio los G4 si puedo incluir algo como G4 ya que si lo que voy a meter 
				//es igual que lo que tenia no lo meto?
				for (itg=m_lista_GCuatros.begin();itg!=m_lista_GCuatros.end() && continuar!=true ;itg++)
				{
					if (((*itL).Width()>=(*itg).G4_THorizontal) && ((*itL).Height()>=(*itg).G4_TVertical) 
					&& ((((*itL).Width()/l)*((*itL).Height()/w))<((*itg).G4_TCajas))
					&& ((((*itL).Width()/w)*((*itL).Height()/l))<((*itg).G4_TCajas)) 
					&& (max<=(*itg).G4_TCajas))
					{
						if ((max<(*itg).G4_TCajas) || (huecomin>((*itg).G4_HuecoH)*((*itg).G4_HuecoV)))
						{
							max=(*itg).G4_TCajas;
							huecomin=((*itg).G4_HuecoH)*((*itg).G4_HuecoV);
							m_G4_TCajas=(*itg).G4_TCajas;
							m_G4_THorizontal=(*itg).G4_THorizontal;
							m_G4_TVertical=(*itg).G4_TVertical;
							m_G4_HuecoH=(*itg).G4_HuecoH;
							m_G4_HuecoV=(*itg).G4_HuecoV;
							m_G4_CajasH=(*itg).G4_CajasH;
							m_G4_CajasV=(*itg).G4_CajasV;
							m_G4_CajasHH=(*itg).G4_CajasHH;	
							m_G4_CajasVV=(*itg).G4_CajasVV;
							m_G4_PequeH=(*itg).G4_PequeH;
							m_G4_PequeV=(*itg).G4_PequeV;
							g4=true;

						}

					}
				}
				if (((*itL).Width()>=m_G4_THorizontal) && ((*itL).Height()>=m_G4_TVertical) 
				&& ((((*itL).Width()/l)*((*itL).Height()/w))<(m_G4_TCajas))
				&& ((((*itL).Width()/w)*((*itL).Height()/l))<(m_G4_TCajas))
				&& (g4==true))
				{
					ColocarG4(lista,lista_bloques,(*itL),'H',1,1,1);	
					if (lista.size()>1) 	itL=lista.erase(itL);
					else
					{
						lista.clear();
						itL=lista.end();
					}
					continuar=true;
					continue;

				}
		if (continuar==true)
		{
			itL++;
			continue;
		}
		//Si es mejor colocar verticales que horizontales
		if ((((*itL).Width()/m_w)*((*itL).Height()/m_l))>(((*itL).Width()/m_l)*((*itL).Height()/m_w)))
		{
			if ((*itL).Width()>=m_w && (*itL).Height()>=m_l)
			{
				tipo2='H';
				ColocarEsquinaMasCercana(lista,B1,(*itL),tipo2);
				B1.SetTipo('V');
				itL=lista.erase(itL);
				lista_bloques.push_back(B1);
				continuar=true;
				continue;
			}
		}
		//En otro caso coloco horizontales
		else
		{
			if ((*itL).Width()>=m_l && (*itL).Height()>=m_w)
			{
				tipo2='V';
				ColocarEsquinaMasCercana(lista,B1,(*itL),tipo2);
				B1.SetTipo('H');
				itL=lista.erase(itL);
				lista_bloques.push_back(B1);
				continue;
				continuar=true;
			}
		}
			//1 esquina inferior izquierda
			//2 esquina superior izquierda
			//3 esquina superior derecha
			//4 esquina inferior derecha
			itL++;
		}while(itL!=lista.end());
		}while(continuar==true);


	}

	return lista_bloques;
}
void PALLET::ColocarG4(std::list<CRect> &lista,std::list<BLOQUE> &listablo,CRect &Rect,char tipo,int x,int y,int z)
{
	
//	printf("Tipo %d %c",m_iter_actual,tipo);
	CRect Nuevo1,Nuevo2;
	int posx=0,posy=0;
	if (tipo=='H')
	{
		if (m_iter_actual==617)
			int pp=0;
	if (x>0 && y>0 && tipo!='X')
	{
		//*Lado derecho
		if (Rect.CenterPoint().x>(m_L/2))
		{
	
			//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
			{
				bool meter_per=true;
				//Lado derecho arriba
				for (int i=1;i<=x;i++)
				{
					for (int j=1;j<=y;j++)
					{
						posx=Rect.right-m_G4_THorizontal*i;	
						posy=Rect.bottom-(m_G4_TVertical*j);
						BLOQUE B1(posx,posy,posx+(m_l*m_G4_CajasHH),posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+(m_l*m_G4_CajasHH),B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if ((m_G4_CajasH*m_w)>(m_G4_CajasVV*m_l))
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							Nuevo1.TopLeft()=Rect.TopLeft();
							Nuevo1.right=Rect.right;
							Nuevo1.bottom=B1.top;
							Nuevo2.bottom=Rect.bottom;
							Nuevo2.left=Rect.left;
							Nuevo2.right=B1.left;
							Nuevo2.top=B1.top;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}

				}

			}
			else
			{
				bool meter_per=true;
				//Lado derecho abajo
				for (int i=1;i<=x;i++)
				{
					for (int j=1;j<=y;j++)
					{
					
						posx=Rect.right-m_G4_THorizontal*i;	
						posy=Rect.top+(m_G4_TVertical*(j-1));
						BLOQUE B1(posx,posy,posx+(m_l*m_G4_CajasHH),posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+(m_l*m_G4_CajasHH),B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
//							if (m_G4_CajasV+1>m_vL)
							if ((m_G4_CajasH*m_w)>(m_G4_CajasVV*m_l))
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							Nuevo1.BottomRight()=Rect.BottomRight();
							Nuevo1.left=Rect.left;
							Nuevo1.top=B3.bottom;
							Nuevo2.left=Rect.left;
							Nuevo2.top=Rect.top;
							Nuevo2.bottom=B3.bottom;
							Nuevo2.right=B1.left;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}
				}
			}
		}
		else
		{	//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
			{
				bool meter_per=true;

				for (int i=1;i<=x;i++)
				{
					for (int j=1;j<=y;j++)
					{
						posx=Rect.left+(m_G4_THorizontal*(i-1));
						posy=Rect.bottom-(m_G4_TVertical*j);
						//Lado izquierda arriba
						BLOQUE B1(posx,posy,posx+(m_l*m_G4_CajasHH),posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+(m_l*m_G4_CajasHH),B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if ((m_G4_CajasH*m_w)>(m_G4_CajasVV*m_l))
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							Nuevo1.TopLeft()=Rect.TopLeft();
							Nuevo1.right=Rect.right;
							Nuevo1.bottom=B1.top;
							Nuevo2.BottomRight()=Rect.BottomRight();
							Nuevo2.top=B1.top;
							Nuevo2.left=B2.right;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}
				}
			}
			else
			{
				bool meter_per=true;

				//Lado izquierdo abajo
				for (int i=1;i<=x;i++)
				{
					//Lado izquierdo abajo
					for (int j=1;j<=y;j++)
					{
						posx=Rect.left+(m_G4_THorizontal*(i-1));
						posy=Rect.top+(m_G4_TVertical*(j-1));
						BLOQUE B1(posx,posy,posx+(m_l*m_G4_CajasHH),posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+(m_l*m_G4_CajasVV),'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+(m_l*m_G4_CajasHH),B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if ((m_G4_CajasH*m_w)>(m_G4_CajasVV*m_l))
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							//Meter las perdidas en la lista
							Nuevo1.BottomRight()=Rect.BottomRight();
							Nuevo1.left=Rect.left;
							Nuevo1.top=B3.bottom;
							Nuevo2.right=Rect.right;
							Nuevo2.top=Rect.top;
							Nuevo2.bottom=B3.bottom;
							Nuevo2.left=B2.right;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}

				}
			}

		}

	}
	}
/*	if (tipo=='H')
	{
	if (x>0 && y>0 && tipo!='X')
	{
		//*Lado derecho
		if (Rect.CenterPoint().x>(m_L/2))
		{
	
			//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
			{
				bool meter_per=true;
				//Lado derecho arriba
				for (int i=1;i<=x;i++)
				{
					for (int j=1;j<=y;j++)
					{
						posx=Rect.right-m_G4_THorizontal*i;	
						posy=Rect.bottom-(m_G4_TVertical*j);
						BLOQUE B1(posx,posy,posx+m_l,posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+m_l,'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+m_l,'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+m_l,B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if (m_G4_CajasV+1>m_vL)
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							Nuevo1.TopLeft()=Rect.TopLeft();
							Nuevo1.right=Rect.right;
							Nuevo1.bottom=B1.top;
							Nuevo2.bottom=Rect.bottom;
							Nuevo2.left=Rect.left;
							Nuevo2.right=B1.left;
							Nuevo2.top=B1.top;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}

				}

			}
			else
			{
				bool meter_per=true;
				//Lado derecho abajo
				for (int i=1;i<=x;i++)
				{
					for (int j=1;j<=y;j++)
					{
					
						posx=Rect.right-m_G4_THorizontal*i;	
						posy=Rect.top+(m_G4_TVertical*(j-1));
						BLOQUE B1(posx,posy,posx+m_l,posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+m_l,'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+m_l,'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+m_l,B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if (m_G4_CajasV+1>m_vL)
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							Nuevo1.BottomRight()=Rect.BottomRight();
							Nuevo1.left=Rect.left;
							Nuevo1.top=B3.bottom;
							Nuevo2.left=Rect.left;
							Nuevo2.top=Rect.top;
							Nuevo2.bottom=B3.bottom;
							Nuevo2.right=B1.left;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}
				}
			}
		}
		else
		{	//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
			{
				bool meter_per=true;

				for (int i=1;i<=x;i++)
				{
					for (int j=1;j<=y;j++)
					{
						posx=Rect.left+(m_G4_THorizontal*(i-1));
						posy=Rect.bottom-(m_G4_TVertical*j);
						//Lado izquierda arriba
						BLOQUE B1(posx,posy,posx+m_l,posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+m_l,'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+m_l,'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+m_l,B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if (m_G4_CajasV+1>m_vL)
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							Nuevo1.TopLeft()=Rect.TopLeft();
							Nuevo1.right=Rect.right;
							Nuevo1.bottom=B1.top;
							Nuevo2.BottomRight()=Rect.BottomRight();
							Nuevo2.top=B1.top;
							Nuevo2.left=B2.right;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}
				}
			}
			else
			{
				bool meter_per=true;

				//Lado izquierdo abajo
				for (int i=1;i<=x;i++)
				{
					//Lado izquierdo abajo
					for (int j=1;j<=y;j++)
					{
						posx=Rect.left+(m_G4_THorizontal*(i-1));
						posy=Rect.top+(m_G4_TVertical*(j-1));
						BLOQUE B1(posx,posy,posx+m_l,posy+(m_w*m_G4_CajasH),'H',false);
						BLOQUE B2(B1.right,B1.top,B1.right+(m_w*m_G4_CajasV),B1.top+m_l,'V',false);
						BLOQUE B3(B1.left,B1.bottom,B1.left+(m_w*m_G4_CajasV),B1.bottom+m_l,'V',false);
						BLOQUE B4(B3.right,B2.bottom,B3.right+m_l,B2.bottom+(m_w*m_G4_CajasH),'H',false);
						int bx1=B1.left+m_G4_PequeH;
						int by1=B1.top+m_G4_PequeV;
						if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
						{
							if (m_G4_CajasV+1>m_vL)
							{
								bx1=B1.right;
								by1=B2.bottom;

							}
							else
							{
								bx1=B3.right;
								by1=B1.bottom;

							}
						}
						CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
						lista.push_back(Nuevo3);
						listablo.push_back(B1);
						listablo.push_back(B2);
						listablo.push_back(B3);
						listablo.push_back(B4);
						if (i==x && j==y)
						{
							//Meter las perdidas en la lista
							Nuevo1.BottomRight()=Rect.BottomRight();
							Nuevo1.left=Rect.left;
							Nuevo1.top=B3.bottom;
							Nuevo2.right=Rect.right;
							Nuevo2.top=Rect.top;
							Nuevo2.bottom=B3.bottom;
							Nuevo2.left=B2.right;
							if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
							if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
							meter_per=false;
						}
					}

				}
			}

		}

	}
	}*/
	if (tipo=='L')
	{
		int largo=m_G4_CajasVV*m_l,ancho=m_G4_CajasV*m_w;
		if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
		{
			largo=m_G4_CajasH*m_w;
			ancho=m_G4_CajasHH*m_l;
		}

		int WidthRectUno=(m_G4_THorizontal+(ancho*x));
		int HeightRectUno=(m_G4_TVertical+(x*largo));
		int HeightRect=HeightRectUno*z;
		int WidthRect=WidthRectUno*y;
//		if (Rect.CenterPoint().x>=(m_L/2))
		if (Rect.CenterPoint().x>(m_L/2))
		{
	
			//Arriba o abajo
//			if (Rect.CenterPoint().y>=(m_W/2))
			if (Rect.CenterPoint().y>(m_W/2))
			{
				CRect RectDA;
				RectDA.BottomRight()=Rect.BottomRight();
				RectDA.left=Rect.right-WidthRect;
				RectDA.top=Rect.bottom-HeightRect;
				CRect Rect2;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_largo(lista,listablo,Rect2,x);
					}
				}
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=RectDA.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.right=RectDA.left;
				Nuevo2.top=RectDA.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			else
			{
				CRect RectDA,Rect2;

				RectDA.bottom=Rect.top+HeightRect;
				RectDA.right=Rect.right;
				RectDA.left=Rect.right-WidthRect;
				RectDA.top=Rect.top;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_largo(lista,listablo,Rect2,x);
					}
				}

				//Lado derecho abajo
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=RectDA.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.top=Rect.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.right=RectDA.left;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
		}
		else
		{	//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
			{
				CRect RectDA,Rect2;

				//Lado izquierda arriba
				RectDA.bottom=Rect.bottom;
				RectDA.left=Rect.left;
				RectDA.right=Rect.left+WidthRect;
				RectDA.top=Rect.bottom-HeightRect;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_largo(lista,listablo,Rect2,x);
					}
				}

				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=RectDA.top;
				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=RectDA.top;
				Nuevo2.left=RectDA.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			else
			{
				CRect RectDA,Rect2;

				//Izquierda Abajo
				RectDA.bottom=Rect.top+HeightRect;
				RectDA.left=Rect.left;
				RectDA.right=Rect.left+WidthRect;
				RectDA.top=Rect.top;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_largo(lista,listablo,Rect2,x);
					}
				}

				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=RectDA.bottom;
				Nuevo2.right=Rect.right;
				Nuevo2.top=Rect.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.left=RectDA.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
		}
	}
	//Recursivo a lo ancho
	if (tipo=='A' )
	{
		int largo=m_G4_CajasHH*m_l,ancho=m_G4_CajasH*m_w;
		if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
		{
			largo=m_w*m_G4_CajasV;
			ancho=m_G4_CajasVV*m_l;
		}

		int WidthRectUno=(m_G4_THorizontal+(largo*x));
		int WidthRect=WidthRectUno*y;
		int HeightRectUno=(m_G4_TVertical+(x*ancho));
		int HeightRect=(m_G4_TVertical+(x*ancho))*z;
		if (Rect.CenterPoint().x>(m_L/2))
//		if (Rect.CenterPoint().x>=0)
		{
	
			//Arriba derecha
			if (Rect.CenterPoint().y>(m_W/2))
//			if (Rect.CenterPoint().y>=0)
			{
				CRect RectDA;
				RectDA.BottomRight()=Rect.BottomRight();
				RectDA.left=Rect.right-WidthRect;
				RectDA.top=Rect.bottom-HeightRect;
				CRect Rect2;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_ancho(lista,listablo,Rect2,x);
					}
				}
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=RectDA.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.right=RectDA.left;
				Nuevo2.top=RectDA.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			else
			{
				//Abajo izquierda
				CRect RectDA,Rect2;

				RectDA.bottom=Rect.top+HeightRect;
				RectDA.right=Rect.right;
				RectDA.left=Rect.right-WidthRect;
				RectDA.top=Rect.top;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_ancho(lista,listablo,Rect2,x);
					}
				}
				//Lado derecho abajo
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=RectDA.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.top=Rect.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.right=RectDA.left;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			
			}
		}
		else
		{	
			if (Rect.CenterPoint().y>(m_W/2))
			{
				CRect RectDA,Rect2;

				//Lado izquierda arriba
				RectDA.bottom=Rect.bottom;
				RectDA.left=Rect.left;
				RectDA.right=Rect.left+WidthRect;
				RectDA.top=Rect.bottom-HeightRect;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_ancho(lista,listablo,Rect2,x);
					}
				}

				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=RectDA.top;
				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=RectDA.top;
				Nuevo2.left=RectDA.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			else
			{
				CRect RectDA,Rect2;

				//Izquierda Abajo
				RectDA.bottom=Rect.top+HeightRect;
				RectDA.left=Rect.left;
				RectDA.right=Rect.left+WidthRect;
				RectDA.top=Rect.top;
				for(int kz=1;kz<=z;kz++)
				{
					for (int ki=1;ki<=y;ki++)
					{
						Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
						Rect2.right=RectDA.left+(ki*WidthRectUno);
						Rect2.top=RectDA.top+((kz-1)*HeightRectUno);
						Rect2.bottom=RectDA.top+(kz*HeightRectUno);
						ColocarG4_recursivo_ancho(lista,listablo,Rect2,x);
					}
				}

				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=RectDA.bottom;
				Nuevo2.right=Rect.right;
				Nuevo2.top=Rect.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.left=RectDA.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
		}
	}
	//Si tipo es recursivo a lo ancho con piezas diferentes
	if (tipo=='a' && m_iter_actual==-1)
	{
		if (m_iter_actual==365)
			int pp=0;

		int largo=m_l*m_G4_CajasVV,ancho=m_G4_CajasH*m_w;
		if (m_G4_CajasV+1>m_vL)
		{
			ancho=m_G4_CajasH*m_w;
			largo=m_l*m_G4_CajasVV;
		}
		else
		{
			largo=m_G4_CajasV*m_w;
			ancho=m_l*m_G4_CajasHH;
		}

		int WidthRectUno=(m_G4_THorizontal+(largo*x));
		int WidthRect=WidthRectUno*y;
		int HeightRect=(m_G4_TVertical+(x*ancho));
		if (Rect.CenterPoint().x>(m_L/2))
//		if (Rect.CenterPoint().x>=0)
		{
	
			//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
//			if (Rect.CenterPoint().y>=0)
			{
				CRect RectDA;
				RectDA.BottomRight()=Rect.BottomRight();
				RectDA.left=Rect.right-WidthRect;
				RectDA.top=Rect.bottom-HeightRect;
				CRect Rect2;
				for (int ki=1;ki<=y;ki++)
				{
					Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
					Rect2.right=RectDA.left+(ki*WidthRectUno);
					Rect2.top=RectDA.top;
					Rect2.bottom=RectDA.bottom;
					ColocarG4_recursivo_ancho_varias(lista,listablo,Rect2,x);
				}
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=RectDA.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.right=RectDA.left;
				Nuevo2.top=RectDA.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			else
			{
				CRect RectDA,Rect2;

				RectDA.bottom=Rect.top+HeightRect;
				RectDA.right=Rect.right;
				RectDA.left=Rect.right-WidthRect;
				RectDA.top=Rect.top;
				for (int ki=1;ki<=y;ki++)
				{
					Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
					Rect2.right=RectDA.left+(ki*WidthRectUno);
					Rect2.top=RectDA.top;
					Rect2.bottom=RectDA.bottom;
					ColocarG4_recursivo_ancho_varias(lista,listablo,Rect2,x);
				}

				//Lado derecho abajo
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=RectDA.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.top=Rect.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.right=RectDA.left;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
		}
		else
		{	//Arriba o abajo
			if (Rect.CenterPoint().y>(m_W/2))
			{
				CRect RectDA,Rect2;

				//Lado izquierda arriba
				RectDA.bottom=Rect.bottom;
				RectDA.left=Rect.left;
				RectDA.right=Rect.left+WidthRect;
				RectDA.top=Rect.bottom-HeightRect;
				for (int ki=1;ki<=y;ki++)
				{
					Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
					Rect2.right=RectDA.left+(ki*WidthRectUno);
					Rect2.top=RectDA.top;
					Rect2.bottom=RectDA.bottom;
					ColocarG4_recursivo_ancho_varias(lista,listablo,Rect2,x);
				}

				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=RectDA.top;
				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=RectDA.top;
				Nuevo2.left=RectDA.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			else
			{
				CRect RectDA,Rect2;

				//Izquierda Abajo
				RectDA.bottom=Rect.top+HeightRect;
				RectDA.left=Rect.left;
				RectDA.right=Rect.left+WidthRect;
				RectDA.top=Rect.top;
				for (int ki=1;ki<=y;ki++)
				{
					Rect2.left=RectDA.left+((ki-1)*WidthRectUno);
					Rect2.right=RectDA.left+(ki*WidthRectUno);
					Rect2.top=RectDA.top;
					Rect2.bottom=RectDA.bottom;
					ColocarG4_recursivo_ancho_varias(lista,listablo,Rect2,x);
				}

				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=RectDA.bottom;
				Nuevo2.right=Rect.right;
				Nuevo2.top=Rect.top;
				Nuevo2.bottom=RectDA.bottom;
				Nuevo2.left=RectDA.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
		}
	}
	

}
void PALLET::ColocarG4_recursivo_ancho_varias(std::list<CRect> &lista,std::list<BLOQUE> &listablo,CRect &Rect,int tam)
{
	int bx1,by1;
	int ancho1,largo1,ancho2,largo2;
	char tipoB1='H',tipoB2='V';
	int largo=m_G4_CajasVV*m_l,ancho=m_G4_CajasH*m_w;
	if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
	{
		largo=m_w*m_G4_CajasH;
		ancho=m_G4_CajasVV*m_l;
	}
	if ((m_G4_CajasH*m_G4_CajasHH)!=(m_G4_CajasV*m_G4_CajasVV))
	{
		//No puedo colocar más cajas verticales
		if (m_G4_CajasV+1>m_vL)
		{
			ancho=m_G4_CajasH*m_w;
			ancho1=m_G4_CajasV*m_w;
			largo1=m_G4_CajasH*m_w;
			largo=m_G4_CajasVV*m_l;
			ancho2=m_G4_CajasVV*m_l;
			largo2=m_G4_CajasVV*m_l;
			tipoB1='H';
			tipoB2='V';
		}
		else
		{
			largo1=m_G4_CajasVV*m_l;
			ancho1=m_G4_CajasVV*m_l;
			largo=m_G4_CajasV*m_w;
			ancho=m_G4_CajasVV*m_l;
			ancho2=m_G4_CajasV*m_w;
			largo2=m_G4_CajasH*m_w;
			tipoB1='V';
			tipoB2='H';

		}
	}
	int posx=Rect.right-m_G4_THorizontal;	
	int posy=Rect.bottom-(m_G4_TVertical);
	BLOQUE B1(posx,posy,posx+ancho1,posy+largo2,tipoB2,false);
	BLOQUE B2(B1.right,B1.top,B1.right+ancho2,B1.top+largo1,tipoB1,false);
	BLOQUE B3(B1.left,B1.bottom,B1.left+ancho2,B1.bottom+largo1,tipoB1,false);
	BLOQUE B4(B3.right,B2.bottom,B3.right+ancho1,B2.bottom+largo2,tipoB2,false);
	if (m_G4_CajasV+1>m_vL)
	{
		bx1=B1.right;
		by1=B2.bottom;

	}
	else
	{
		bx1=B3.right;
		by1=B1.bottom;

	}
	CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
	lista.push_back(Nuevo3);
	listablo.push_back(B1);
	listablo.push_back(B2);
	listablo.push_back(B3);
	listablo.push_back(B4);
	for (int i=1;i<=tam;i++)
	{
		posx=Rect.right-m_G4_THorizontal-(largo*i);	
		posy=Rect.bottom-(m_G4_TVertical)-(ancho*i);
		BLOQUE B5(posx,posy,posx+ancho1,posy+largo2,tipoB2,false);
		BLOQUE B6(B5.left,B5.bottom,B5.left+largo,B5.bottom+(ancho*(i+1)),tipoB1,false);
		BLOQUE B7(B5.right,B5.top,B4.right,B5.top+(ancho),tipoB1,false);
		if (m_G4_CajasV+1>m_vL)
		{
			bx1=B5.right;
			by1=B7.bottom;

		}
		else
		{
			bx1=B6.right;
			by1=B5.bottom;

		}
		CRect Nuevo4(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
		lista.push_back(Nuevo4);
		listablo.push_back(B5);
		listablo.push_back(B6);
		listablo.push_back(B7);
	}
	int kk=9;
}
void PALLET::ColocarG4_recursivo_ancho(std::list<CRect> &lista,std::list<BLOQUE> &listablo,CRect &Rect,int tam)
{
	char tipoB1='H',tipoB2='V';
	int largo=m_G4_CajasVV*m_l,ancho=m_G4_CajasV*m_w,largo1=m_G4_CajasH*m_w,ancho1=m_G4_CajasHH*m_l;
	if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
	{
		largo=m_w*m_G4_CajasH;
		ancho=m_G4_CajasHH*m_l;
		largo1=m_l*m_G4_CajasVV;
		ancho1=m_G4_CajasV*m_w;
		tipoB1='V';
		tipoB2='H';
	}

	int posx=Rect.right-m_G4_THorizontal;	
	int posy=Rect.bottom-(m_G4_TVertical);
	BLOQUE B1(posx,posy,posx+(ancho),posy+largo,tipoB2,false);
	BLOQUE B2(B1.right,B1.top,B1.right+ancho1,B1.top+(largo1),tipoB1,false);
	BLOQUE B3(B1.left,B1.bottom,B1.left+ancho1,B1.bottom+(largo1),tipoB1,false);
	BLOQUE B4(B3.right,B2.bottom,B3.right+(ancho),B2.bottom+largo,tipoB2,false);
	CRect Nuevo3(B1.right,B2.bottom,B1.right+m_G4_HuecoH,B2.bottom+m_G4_HuecoV);
	lista.push_back(Nuevo3);
	listablo.push_back(B1);
	listablo.push_back(B2);
	listablo.push_back(B3);
	listablo.push_back(B4);
	for (int i=1;i<=tam;i++)
	{
		posx=Rect.right-m_G4_THorizontal-(ancho1*i);	
		posy=Rect.bottom-(m_G4_TVertical)-(largo1*i);
		BLOQUE B5(posx,posy,posx+(ancho),posy+largo,tipoB2,false);
		BLOQUE B6(B5.left,B5.bottom,B5.left+ancho1,B5.bottom+(largo1*(i+1)),tipoB1,false);
		BLOQUE B7(B5.right,B5.top,B4.right,B5.top+(largo1),tipoB1,false);
		CRect Nuevo4(B5.right,B7.bottom,B5.right+m_G4_HuecoH,B7.bottom+m_G4_HuecoV);
		lista.push_back(Nuevo4);
		listablo.push_back(B5);
		listablo.push_back(B6);
		listablo.push_back(B7);
	}
}
void PALLET::ColocarG4_recursivo_largo(std::list<CRect> &lista,std::list<BLOQUE> &listablo,CRect &Rect,int tam)
{
	char tipoB1='H',tipoB2='V';
	int bx1=0,by1=0;
	int largo=m_G4_CajasVV*m_l,ancho=m_G4_CajasV*m_w,largo1=m_G4_CajasH*m_w,ancho1=m_G4_CajasHH*m_l;
	if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
	{
		largo=m_w*m_G4_CajasH;
		ancho=m_G4_CajasHH*m_l;
		largo1=m_l*m_G4_CajasVV;
		ancho1=m_G4_CajasV*m_w;
		tipoB1='V';
		tipoB2='H';
	}


	int posx=Rect.right-m_G4_THorizontal;	
	int posy=Rect.bottom-(m_G4_TVertical);
	BLOQUE B1(posx,posy,posx+(ancho1),posy+largo1,tipoB1,false);
	BLOQUE B2(B1.right,B1.top,B1.right+ancho,B1.top+(largo),tipoB2,false);
	BLOQUE B3(B1.left,B1.bottom,B1.left+ancho,B1.bottom+(largo),tipoB2,false);
	BLOQUE B4(B3.right,B2.bottom,B3.right+(ancho1),B2.bottom+largo1,tipoB1,false);
/*	if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
	{
		bx1=B1.right;
		by1=B2.bottom;

	}
	else
	{
*/		bx1=B3.right;
		by1=B1.bottom;

//	}

	CRect Nuevo3(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
	lista.push_back(Nuevo3);
	listablo.push_back(B1);
	listablo.push_back(B2);
	listablo.push_back(B3);
	listablo.push_back(B4);
	for (int i=1;i<=tam;i++)
	{
		posx=Rect.right-m_G4_THorizontal-(ancho*i);	
		posy=Rect.bottom-(m_G4_TVertical)-(largo*i);
		BLOQUE B5(posx,posy,posx+(ancho1),posy+largo1,tipoB1,false);
		BLOQUE B6(B5.left,B5.bottom,B5.left+ancho,B5.bottom+(largo*(i+1)),tipoB2,false);
		BLOQUE B7(B5.right,B5.top,B4.right,B5.top+(largo),tipoB2,false);
/*		if ((m_G4_CajasH*m_w)>m_G4_CajasVV*m_l)
		{
			bx1=B5.right;
			by1=B7.bottom;

		}
		else
		{
*/			bx1=B6.right;
			by1=B5.bottom;

//		}
		CRect Nuevo4(bx1,by1,bx1+m_G4_HuecoH,by1+m_G4_HuecoV);
		lista.push_back(Nuevo4);
		listablo.push_back(B5);
		listablo.push_back(B6);
		listablo.push_back(B7);
	}
}


//Numeradas en el sentido de las agujas del reloj
//1 esquina inferior izquierda 
void PALLET::ColocarEsquinaMasCercana(std::list<CRect> &lista,BLOQUE &B1,CRect &Rect,char tipo)
{
	int l=m_l,w=m_w;
	if (tipo=='H')
	{
		l=m_w;
		w=m_l;
	}

	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	CRect Nuevo1,Nuevo2;
	//*Lado derecho
	if (xcenter>(m_L/2))
	{
		B1.right=Rect.right;
		B1.left=B1.right-((Rect.Width()/l)*l);

		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-((Rect.Height()/w)*w);
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;
				Nuevo2.bottom=Rect.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.right=B1.left;
				Nuevo2.top=B1.top;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			//Lado derecho arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+((Rect.Height()/w)*w);	
			if (!B1.IsRectEmpty())
			{
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.right=B1.left;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			//Lado derecho abajo
		}
	}
	//Lado izquierdo
	else
	{
		B1.left=Rect.left;
		B1.right=B1.left+((Rect.Width()/l)*l);
		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-((Rect.Height()/w)*w);
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;
				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=B1.top;
				Nuevo2.left=B1.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}
			//Esquina izquierda arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+((Rect.Height()/w)*w);
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;
				Nuevo2.right=Rect.right;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.left=B1.right;
				if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
			}

			//Esquina izquierda abajo
		}
	}
	
/*	//A la esquina inferior siempre
	B1.left=Rect.left;
	B1.right=B1.left+((Rect.Width()/l)*l);
	B1.top=Rect.top;
	B1.bottom=B1.top+((Rect.Height()/w)*w);
	if (!(B1.IsRectEmpty()))
	{
		Nuevo1.BottomRight()=Rect.BottomRight();
		Nuevo1.left=Rect.left;
		Nuevo1.top=B1.bottom;
		Nuevo2.right=Rect.right;
		Nuevo2.top=B1.top;
		Nuevo2.bottom=B1.bottom;
		Nuevo2.left=B1.right;
		if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
		if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
	}*/


}
//Numeradas en el sentido de las agujas del reloj
//1 esquina inferior izquierda 
//Dos bloques 
void PALLET::ColocarEsquinaMasCercana(std::list<CRect> &lista,BLOQUE &B1,BLOQUE &B2,CRect &Rect,char tipo)
{
	if (Rect.top==0 && Rect.left==27 && Rect.bottom==52 && Rect.right==86 )
		int perro=9;

	if (tipo=='H') 
	{
		B1.SetTipo('V');
		B2.SetTipo('H');
	}
	else
	{
		B1.SetTipo('H');
		B2.SetTipo('V');
	}
	int i,j,segun,prime,max=0;
	int l=m_l,w=m_w;
	if (tipo=='H')
	{
		l=m_w;
		w=m_l;
	}
	//Heurístico de 2 bloque
	for(i=1;i<=Rect.Width()/l;i++)
	{
		for(j=0;i*l+j*w<=Rect.Width();j++)
		{
			if ((i*(Rect.Height()/w)+j*(Rect.Height()/l))>max)
			{
				max=(i*(Rect.Height()/w)+j*(Rect.Height()/l));
				prime=i;
				segun=j;
			}
		}
	}
	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	CRect Nuevo1,Nuevo2,Nuevo3;
	//*Lado derecho
	if (xcenter>(m_L/2))
	{
		B1.right=Rect.right;
		B1.left=B1.right-(l*prime);
		B2.right=B1.left;
		B2.left=B2.right-(w*segun);
		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-((Rect.Height()/w)*w);
			B2.bottom=Rect.bottom;
			B2.top=B2.bottom-((Rect.Height()/l)*l);
			if (!(B1.IsRectEmpty()))
			{
				if (B2.IsRectEmpty())
				{
					Nuevo1.TopLeft()=Rect.TopLeft();
					Nuevo1.right=Rect.right;
					Nuevo1.bottom=B1.top;
					Nuevo2.bottom=Rect.bottom;
					Nuevo2.left=Rect.left;
					Nuevo2.right=B1.left;
					Nuevo2.top=B1.top;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					Nuevo1.TopLeft()=Rect.TopLeft();
					Nuevo1.bottom=Rect.bottom;
					Nuevo1.right=B2.left;
					Nuevo2.top=Rect.top;
					Nuevo2.bottom=B2.top;
					Nuevo2.left=B2.left;
					Nuevo2.right=B2.right;
					Nuevo3.top=Rect.top;
					Nuevo3.bottom=B1.top;
					Nuevo3.left=B1.left;
					Nuevo3.right=B1.right;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo3.IsRectEmpty()) lista.push_back(Nuevo3);
				}
			}
			//Lado derecho arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+((Rect.Height()/w)*w);	
			B2.top=Rect.top;
			B2.bottom=B2.top+((Rect.Height()/l)*l);

			if (!B1.IsRectEmpty())
			{
				if (B2.IsRectEmpty())
				{
					Nuevo1.BottomRight()=Rect.BottomRight();
					Nuevo1.left=Rect.left;
					Nuevo1.top=B1.bottom;
					Nuevo2.left=Rect.left;
					Nuevo2.top=B1.top;
					Nuevo2.bottom=B1.bottom;
					Nuevo2.right=B1.left;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					Nuevo1.TopLeft()=Rect.TopLeft();
					Nuevo1.bottom=Rect.bottom;
					Nuevo1.right=B2.left;
					Nuevo2.top=B2.bottom;
					Nuevo2.bottom=Rect.bottom;
					Nuevo2.left=B2.left;
					Nuevo2.right=B2.right;
					Nuevo3.top=B1.bottom;
					Nuevo3.bottom=Rect.bottom;
					Nuevo3.left=B1.left;
					Nuevo3.right=B1.right;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo3.IsRectEmpty()) lista.push_back(Nuevo3);
				}
			}
			//Lado derecho abajo
		}
	}
	//Lado izquierdo
	else
	{
		B1.left=Rect.left;
		B1.right=B1.left+(l*prime);
		B2.left=B1.right;
		B2.right=B2.left+(w*segun);
		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-((Rect.Height()/w)*w);
			B2.bottom=Rect.bottom;
			B2.top=B2.bottom-((Rect.Height()/l)*l);

			if (!(B1.IsRectEmpty()))
			{
				if (B2.IsRectEmpty())
				{
					Nuevo1.TopLeft()=Rect.TopLeft();
					Nuevo1.right=Rect.right;
					Nuevo1.bottom=B1.top;
					Nuevo2.BottomRight()=Rect.BottomRight();
					Nuevo2.top=B1.top;
					Nuevo2.left=B1.right;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					Nuevo1.left=B2.right;
					Nuevo1.top=Rect.top;
					Nuevo1.BottomRight()=Rect.BottomRight();
					Nuevo2.top=Rect.top;
					Nuevo2.bottom=B2.top;
					Nuevo2.left=B2.left;
					Nuevo2.right=B2.right;
					Nuevo3.top=Rect.top;
					Nuevo3.bottom=B1.top;
					Nuevo3.left=B1.left;
					Nuevo3.right=B1.right;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo3.IsRectEmpty()) lista.push_back(Nuevo3);
				}
			}
			//Esquina izquierda arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+((Rect.Height()/w)*w);
			B2.top=Rect.top;
			B2.bottom=B2.top+((Rect.Height()/l)*l);

			if (!(B1.IsRectEmpty()))
			{
				if (B2.IsRectEmpty())
				{
					Nuevo1.BottomRight()=Rect.BottomRight();
					Nuevo1.left=Rect.left;
					Nuevo1.top=B1.bottom;
					Nuevo2.right=Rect.right;
					Nuevo2.top=B1.top;
					Nuevo2.bottom=B1.bottom;
					Nuevo2.left=B1.right;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					Nuevo1.BottomRight()=Rect.BottomRight();
					Nuevo1.top=Rect.top;
					Nuevo1.left=B2.right;
					Nuevo2.top=B2.bottom;
					Nuevo2.bottom=Rect.bottom;
					Nuevo2.left=B2.left;
					Nuevo2.right=B2.right;
					Nuevo3.top=B1.bottom;
					Nuevo3.bottom=Rect.bottom;
					Nuevo3.left=B1.left;
					Nuevo3.right=B1.right;
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo3.IsRectEmpty()) lista.push_back(Nuevo3);
				}

			}

			//Esquina izquierda abajo
		}
	}
	
/*	//A la esquina inferior siempre
	B1.left=Rect.left;
	B1.right=B1.left+((Rect.Width()/l)*l);
	B1.top=Rect.top;
	B1.bottom=B1.top+((Rect.Height()/w)*w);
	if (!(B1.IsRectEmpty()))
	{
		Nuevo1.BottomRight()=Rect.BottomRight();
		Nuevo1.left=Rect.left;
		Nuevo1.top=B1.bottom;
		Nuevo2.right=Rect.right;
		Nuevo2.top=B1.top;
		Nuevo2.bottom=B1.bottom;
		Nuevo2.left=B1.right;
		if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
		if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
	}*/


}
int PALLET::CuatroBloques(CRect &Rect,char tipo)
{
	std::list<cota> m_Eficientes_X,m_Eficientes_Y;
	std::list<cota> ::iterator itx1,ity1,it2,it3;
	int V,W,a,b,c,d,e,f,g,h,maximo=0;
	V=Rect.Width();
	W=Rect.Height();
//Hacer particiones
		//Particiones del lado X
	int maxim=0;
	int M=V;
	a=m_l;
	b=m_w;
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
			}
			

			
		}
	}
	M=W;
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
			}
			

			
		}
	}
	
	intervalo salida;
	int a1=m_Ancho_Caja;
	int b1=m_Largo_Caja;
	for (itx1=m_Eficientes_X.begin();itx1!=m_Eficientes_X.end();itx1++)
	{
		b=(*itx1).first;
		for (ity1=m_Eficientes_Y.begin();ity1!=m_Eficientes_Y.end();ity1++)
		{
			if (b!=0)
			{
				a=(*ity1).second;//primer Rectangulo a,b
			}
			else a=0;

			for (it2=m_Eficientes_Y.begin();it2!=m_Eficientes_Y.end();it2++)
			{

				c=(*itx1).second;
				d=(*it2).first;
				if (c==0 || d==0) {c=0;d=0;}

				for (it3=m_Eficientes_X.begin();it3!=m_Eficientes_X.end();it3++)
				{
					e=(*it2).second;
					f=(*it3).first;
					h=(*ity1).first;
					g=(*it3).second;
					if (e==0 || f==0) {e=0;f=0;}
					if (h==0 || g==0) {h=0;g=0;}
					//Poner que no puede ser del tipo determinado
					if ((a*b+c*d+e*f+g*h) >= maximo && !((a+e>(W/b1)) && (b+f>(V/a1))) && !((h+d>(W/a1)) && (g+c>(V/b1))))
					if ((tipo=='H' && (a*b+e*f)==0) || (tipo=='V' && (c*d+g*h)==0))
					{
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
	}
	return maximo;
}
int PALLET::Heuristico1Bloque(CRect &Rect,char tipoantiguo)
{
	if (tipoantiguo=='V') return ((Rect.Width()/m_l)+(Rect.Height()/m_w));
	if (tipoantiguo=='H') return ((Rect.Width()/m_w)+(Rect.Height()/m_l));
	return 0;
}
int PALLET::Perdida_Entre_Bloques(BLOQUE &B1,BLOQUE &B2)
{
	return 1;
}

int PALLET::OptimoTipoI(void)		
{
	FILE *salidadatos;
	int X,Y,a,b,Heuri,Cota1,Cota2,Cota3,status;
	salidadatos=fopen("datos.txt","r");
	while (!feof(salidadatos))
	{
		fscanf(salidadatos,"%d %d %d %d %d %d %d %d %d",&status,&Heuri,&Cota1,&Cota2,&Cota3,&X, &Y, &a, &b);
		if ((X==m_Ancho0_Pallet) && (Y==m_Largo0_Pallet) && (a==m_Ancho0_Caja) && (b==m_Largo0_Caja))
		{
			fclose(salidadatos);
			return Heuri;
		}
	}
	fclose(salidadatos);
	return 0;
}
int PALLET::OptimoTipoII(void)		
{
	FILE *salidadatos;
	int X,Y,a,b,Heuri,status;
	salidadatos=fopen("datosG4.txt","r");
	while (!feof(salidadatos))
	{
		fscanf(salidadatos,"%d %d %d %d %d %d ",&X, &Y, &a, &b,&status,&Heuri);
		if ((X==m_Ancho0_Pallet) && (Y==m_Largo0_Pallet) && (a==m_Ancho0_Caja) && (b==m_Largo0_Caja))
		{
			fclose(salidadatos);
			return Heuri;
		}
	}
	fclose(salidadatos);
	return 0;
}	
void Generar_Vector_Aleatorio(std::vector<int> &vec_temp,std::vector<int> &vec_recorrer,int dim )
{
	int valor=0;
	vec_temp.clear();
	vec_recorrer.clear();
	for (register int ki=1;ki<=dim;ki++)
	{
		vec_temp.push_back(ki);
	}
	for (ki=dim-1;ki>=0;ki--)
	{
		valor=get_random(0,ki);		
		vec_recorrer.push_back(vec_temp[valor]);
		vec_temp.erase(vec_temp.begin()+valor);
	}
}
void PALLET::Bloques_Hacia_Las_Esquinas(std::list<BLOQUE> &listaB, std::list<CRect> &listaP)
{
//	return;
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro
	//*********PEGAR BLOQUES
//	return;
	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
/*	fprintf(fin,"Perro\n");
	if (m_iter_actual==8)
	{
		for (itL=M1.GetListaBloques().begin();itL!=M1.GetListaBloques().end();itL++)
		{
			fprintf(fin,"%3d\t%3d\t%3d\t%3dB\n",(*itL).top,(*itL).bottom,(*itL).left,(*itL).right);
		}
		fprintf(fin,"\n");

	}*/
	m_tipo_junta=3;
	
	bool seguir=false;
	
	do {
		seguir=false;
	itL=listaB.begin();
	do{
		bool movida_izquierda=false;
		bool movida_abajo=false;
//		BLOQUE b1=(*itL);
		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).PuedoMover()!=true && m_fijos==true)
		{
			itL++;
			continue;
		}
		
//		if (m_iter_actual==8) fprintf(fin,"%3d\t%3d\t%3d\t%3dE\n",(*itL).top,(*itL).bottom,(*itL).left,(*itL).right);
//		if ((*itL).left!=0 && ((m_L-(*itL).right)>((*itL).left) || (*itL).left<m_w))
		if ((*itL).left!=0 && ((*itL).left<=(m_L/2)) && (*itL).right!=m_L)
		{
			
			//Pegarla hacia la izquierda
//			if ((m_L-(*itL).right)>((*itL).left) && (ParticionEficienteX((*itL).left)!=true))
//			{
			CRect Rect(0,(*itL).top,(*itL).left,(*itL).bottom);
			int m=(*itL).right;
			//Poner bloque pegado a la izquierda
			if (Existe_Perdida(listaP,(*itL),1)==true && (*itL).GetNumero()!=2)
			{
				//Nueva perdida
				CRect perdida;
				perdida.left=(*itL).right;
				perdida.right=m;
				perdida.top=(*itL).top;
				perdida.bottom=(*itL).bottom;
				listaP.push_back(perdida);
				(*itL).SetNumero(1);
				movida_izquierda=true;
				seguir=true;

			}
		}
			//Pegado a la derecha
		if ((*itL).left!=0 && ((*itL).left>(m_L/2)) && movida_izquierda!=true && (*itL).right!=m_L && (*itL).GetNumero()!=1)
		{
			CRect Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
			int m=(*itL).left;
			//Poner bloque pegado a la derecha
			if (Existe_Perdida(listaP,(*itL),2)==true)
			{
				CRect perdida;
				perdida.left=m;
				perdida.right=(*itL).left;
				perdida.top=(*itL).top;
				perdida.bottom=(*itL).bottom;
				listaP.push_back(perdida);
				(*itL).SetNumero(2);
				seguir=true;

			}
		}
	itL++;

	}while(itL!=listaB.end());
	tipo_union='V';
	JuntarPerdida(listaP);
	}while(seguir==true);
	do {
		seguir=false;
	itL=listaB.begin();
	do{
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).PuedoMover()!=true && m_fijos==true)
		{
			itL++;
			continue;
		}
		
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).top!=0 && ((*itL).top<=(m_W/2)) && (*itL).bottom!=m_W && (*itL).GetNumero()!=4)
		{
			//Pegarla hacia abajo
//			if (((*itL).bottom)>(m_W-((*itL).top)) )
//			{
				CRect Rect((*itL).left,0,(*itL).right,(*itL).top);
				int m=(*itL).bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,(*itL),3)==true)
				{
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					(*itL).SetNumero(3);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W/2)) && (*itL).bottom!=m_W && (*itL).GetNumero()!=3)
			{
				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				int m=(*itL).top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,(*itL),4)==true)
				{
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					(*itL).SetNumero(4);

					seguir=true;

				}
			}
//		}
		itL++;

	}while(itL!=listaB.end());
	tipo_union='H';
	JuntarPerdida(listaP);
	}while(seguir==true);
	m_tipo_junta=1;
	tipo_union='X';
	return;
	int hastaL=m_L;
	int hastaW=m_W;
	seguir=false;
	do
	{
	seguir=false;
	itL=listaB.begin();
	do{
/*		if ((*itL).PuedoMover()!=true)
		{
			itL++;
			continue;
		}
*/
		//Si el bloque esta pegado a alguna de las cuatro esquinas
		if (((*itL).left==0 && (*itL).top==0) || ((*itL).right==m_L && (*itL).top==0) || ((*itL).right==m_L && (*itL).bottom==m_W) || ((*itL).left==0 && (*itL).bottom==m_W))
		{
			itL++;
			continue;
		}
//		BLOQUE b1=(*itL);
		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).left<=(m_L/2) && ((*itL).left!=0) && ((*itL).right!=	hastaL))
		{
			int izq=ProximoBloque(listaB,(*itL),1);
			if (izq>0)
			{
				CRect Rect((*itL).left-izq,(*itL).top,(*itL).left,(*itL).bottom);
				//Poner bloque pegado a la izquierda
				int m=(*itL).right;

				if (Existe_Perdida(listaP,(*itL),1)==true)
				{
					//Nueva perdida
					CRect perdida;
					perdida.left=(*itL).right;
					perdida.right=m;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		}
		if ((*itL).left>(m_L/2) && ((*itL).left!=0) && ((*itL).right!=hastaL))
		{
			int der=ProximoBloque(listaB,(*itL),2);
			if (der>0)
			{

				CRect Rect((((*itL).right)),(*itL).top,(*itL).right+der,(*itL).bottom);
				int m=(*itL).left;
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,(*itL),2)==true)
				{
					CRect perdida;
					perdida.left=m;
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		}
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if (((*itL).top<=(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=hastaW))
		{
			int aba=ProximoBloque(listaB,(*itL),3);
			if (aba>0)
			{
				CRect Rect((*itL).left,(*itL).top-aba,(*itL).right,(*itL).top);
				int m=(*itL).bottom;

				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,(*itL),3)==true)
				{
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					seguir=true;

				}

			}
		}
		if (((*itL).top>(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=hastaW))
		{	
			//Lado izquierdo arriba
			int arri=ProximoBloque(listaB,(*itL),4);
			if (arri>0)
			{

				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,(*itL).bottom+arri);
				int m=(*itL).top;
			
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,(*itL),4)==true)
				{
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		}
		itL++;

	}while(itL!=listaB.end());
	}while(seguir!=false);
	m_tipo_junta=1;
}
void PALLET::Bloques_Hacia_Las_Esquinas_Combinar(std::list<BLOQUE> &listaB, std::list<CRect> &listaP)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro
	//*********PEGAR BLOQUES
	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
/*	fprintf(fin,"Perro\n");
	if (m_iter_actual==8)
	{
		for (itL=M1.GetListaBloques().begin();itL!=M1.GetListaBloques().end();itL++)
		{
			fprintf(fin,"%3d\t%3d\t%3d\t%3dB\n",(*itL).top,(*itL).bottom,(*itL).left,(*itL).right);
		}
		fprintf(fin,"\n");

	}*/
	m_tipo_junta=3;
	bool seguir=false;
	
	do {
		seguir=false;
	itL=listaB.begin();
	do{
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).PuedoMover()!=true)
		{
			itL++;
			continue;
		}
		
//		if (m_iter_actual==8) fprintf(fin,"%3d\t%3d\t%3d\t%3dE\n",(*itL).top,(*itL).bottom,(*itL).left,(*itL).right);
//		if ((*itL).left!=0 && ((m_L-(*itL).right)>((*itL).left) || (*itL).left<m_w))
		if ((*itL).left!=0 && ((*itL).left<(m_L/2)))
		{
			
			//Pegarla hacia la izquierda
//			if ((m_L-(*itL).right)>((*itL).left) && (ParticionEficienteX((*itL).left)!=true))
//			{
			CRect Rect(0,(*itL).top,(*itL).left,(*itL).bottom);

			//Poner bloque pegado a la izquierda
			if (Existe_Perdida(listaP,Rect,8)==true)
			{
				(*itL).left=0;
				(*itL).right=(*itL).right-Rect.right;
				//Nueva perdida
				CRect perdida;
				perdida.left=(*itL).right;
				perdida.right=(*itL).right+Rect.Width();
				perdida.top=(*itL).top;
				perdida.bottom=(*itL).bottom;
				listaP.push_back(perdida);
				movida_izquierda=true;
				seguir=true;

			}
		}
			//Pegado a la derecha
			if ((*itL).left!=0 && movida_izquierda!=true )
			{
				CRect Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,8)==true)
				{
					(*itL).right=m_L;
					(*itL).left=(*itL).left+Rect.Width();
					CRect perdida;
					perdida.left=(*itL).left-Rect.Width();
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		itL++;

	}while(itL!=listaB.end());
	tipo_union='V';
	JuntarPerdida(listaP);
	}while(seguir==true);
	do {
		seguir=false;
	itL=listaB.begin();
	do{
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).PuedoMover()!=true)
		{
			itL++;
			continue;
		}
		
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).top!=0 && ((*itL).top<(m_W/2)))
		{
			//Pegarla hacia abajo
//			if (((*itL).bottom)>(m_W-((*itL).top)) )
//			{
				CRect Rect((*itL).left,0,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).top=0;
					(*itL).bottom=(*itL).bottom-Rect.Height();
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=(*itL).bottom+Rect.Height();
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
			if ((*itL).top!=0 && movida_abajo!=true)
			{
				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).bottom=m_W;
					(*itL).top=(*itL).top+Rect.Height();
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=(*itL).top-Rect.Height();
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
//		}
		itL++;

	}while(itL!=listaB.end());
	tipo_union='H';
	JuntarPerdida(listaP);
	}while(seguir==true);
	tipo_union='X';
	seguir=false;
	do
	{
	seguir=false;
	itL=listaB.begin();
	do{
		if ((*itL).PuedoMover()!=true)
		{
			itL++;
			continue;
		}

		//Si el bloque esta pegado a alguna de las cuatro esquinas
		if (((*itL).left==0 && (*itL).top==0) || ((*itL).right==m_L && (*itL).top==0) || ((*itL).right==m_L && (*itL).bottom==m_W) || ((*itL).left==0 && (*itL).bottom==m_W))
		{
			itL++;
			continue;
		}
//7		BLOQUE b1=(*itL);
		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).left<=(m_L/2) && ((*itL).left!=0) && ((*itL).right!=	m_L))
		{
			int izq=ProximoBloque(listaB,(*itL),1);
			if (izq>0)
			{
				CRect Rect((*itL).left-izq,(*itL).top,(*itL).left,(*itL).bottom);
				//Poner bloque pegado a la izquierda
				if (Existe_Perdida(listaP,Rect,8)==true)
				{
					(*itL).left=(*itL).left-izq;
					(*itL).right=(*itL).right-izq;
					//Nueva perdida
					CRect perdida;
					perdida.left=(*itL).right;
					perdida.right=(*itL).right+izq;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;
				}
			}
		}
		if ((*itL).left>(m_L/2) && ((*itL).left!=0) && ((*itL).right!=m_L))
		{
			int der=ProximoBloque(listaB,(*itL),2);
			if (der>0)
			{

				CRect Rect((((*itL).right)),(*itL).top,(*itL).right+der,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,8)==true)
				{
					(*itL).right=(*itL).right+der;
					(*itL).left=(*itL).left+der;
					CRect perdida;
					perdida.left=(*itL).left-der;
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;
				}
			}
		}
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if (((*itL).top<=(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=m_W))
		{
			int aba=ProximoBloque(listaB,(*itL),3);
			if (aba>0)
			{
				CRect Rect((*itL).left,(*itL).top-aba,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).top=(*itL).top-aba;
					(*itL).bottom=(*itL).bottom-aba;
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=(*itL).bottom+aba;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					seguir=true;
				}
			}
		}
		if (((*itL).top>(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=m_W))
		{	
			//Lado izquierdo arriba
			int arri=ProximoBloque(listaB,(*itL),4);
			if (arri>0)
			{

				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,(*itL).bottom+arri);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).bottom=(*itL).bottom+arri;
					(*itL).top=(*itL).top+arri;
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=(*itL).top-arri;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					seguir=true;
				}
			}
		}
		itL++;

	}while(itL!=listaB.end());
	}while(seguir!=false);
	m_tipo_junta=1;
}
///Bloques hacia las esquinas pero pegando piezas por separado se podría probar post
//eriormente
/*
void PALLET::Bloques_Hacia_Las_Esquinas(std::list<BLOQUE> &listaB, std::list<CRect> &listaP)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro
	//*********PEGAR BLOQUES
	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
	m_tipo_junta=3;
	bool seguir=false;
	
	do {
		seguir=false;
	itL=listaB.begin();
	do{
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
//		if (m_iter_actual==8) fprintf(fin,"%3d\t%3d\t%3d\t%3dE\n",(*itL).top,(*itL).bottom,(*itL).left,(*itL).right);
//		if ((*itL).left!=0 && ((m_L-(*itL).right)>((*itL).left) || (*itL).left<m_w))
		if ((*itL).left!=0 && ((*itL).left<(m_L/2)))
		{
			
			//Pegarla hacia la izquierda
//			if ((m_L-(*itL).right)>((*itL).left) && (ParticionEficienteX((*itL).left)!=true))
//			{
			CRect Rect(0,(*itL).top,(*itL).left,(*itL).bottom);

			//Poner bloque pegado a la izquierda
			if (Existe_Perdida(listaP,Rect,0)==true)
			{
				(*itL).left=0;
				(*itL).right=(*itL).right-Rect.right;
				//Nueva perdida
				CRect perdida;
				perdida.left=(*itL).right;
				perdida.right=(*itL).right+Rect.Width();
				perdida.top=(*itL).top;
				perdida.bottom=(*itL).bottom;
				listaP.push_back(perdida);
				movida_izquierda=true;
				seguir=true;

			}
		}
			//Pegado a la derecha
			if ((*itL).left!=0 && movida_izquierda!=true )
			{
				CRect Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,0)==true)
				{
					(*itL).right=m_L;
					(*itL).left=(*itL).left+Rect.Width();
					CRect perdida;
					perdida.left=(*itL).left-Rect.Width();
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		itL++;

	}while(itL!=listaB.end());
	tipo_union='V';
	JuntarPerdida(listaP);
	}while(seguir==true);
	do {
		seguir=false;
	itL=listaB.begin();
	do{
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).top!=0 && ((*itL).top<(m_W/2)))
		{
			//Pegarla hacia abajo
//			if (((*itL).bottom)>(m_W-((*itL).top)) )
//			{
				CRect Rect((*itL).left,0,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,Rect,1)==true)
				{
					(*itL).top=0;
					(*itL).bottom=(*itL).bottom-Rect.Height();
					//Nueva perdida
					CRect perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=(*itL).bottom+Rect.Height();
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
			if ((*itL).top!=0 && movida_abajo!=true)
			{
				CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,1)==true)
				{
					(*itL).bottom=m_W;
					(*itL).top=(*itL).top+Rect.Height();
					CRect perdida;
					perdida.bottom=(*itL).top;
					perdida.top=(*itL).top-Rect.Height();
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
//		}
		itL++;

	}while(itL!=listaB.end());
	tipo_union='H';
	JuntarPerdida(listaP);
	}while(seguir==true);
	tipo_union='X';
	seguir=false;
	int izq=0,aba=0,arr=0,der=0;
	do
	{
	seguir=false;
	itL=listaB.begin();
	do{
		//Si el bloque esta pegado a alguna de las cuatro esquinas
		if (((*itL).left==0 && (*itL).top==0) || ((*itL).right==m_L && (*itL).top==0) || ((*itL).right==m_L && (*itL).bottom==m_W) || ((*itL).left==0 && (*itL).bottom==m_W))
		{
			itL++;
			continue;
		}
		BLOQUE b15=(*itL);
		CRect RectTemp(0,0,0,0);
		int l=m_l;
		int w=m_w;
		if ((*itL).GetTipo()=='V')
		{
			l=m_w;
			w=m_l;
		}

		//Moverla hacia al lado derecho o izquierdo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if ((*itL).left<=(m_L/2) && ((*itL).left!=0) && ((*itL).right!=	m_L))
		{
			ProximoBloque(listaP,(*itL),1,RectTemp);
			izq=(RectTemp.right-RectTemp.left);
			if (m_iter_actual==31)
				int koko=9;
			if (izq>0)
			{
				aba=__max((*itL).top,RectTemp.top);
				arr=__min((*itL).bottom,RectTemp.bottom);
				if (arr-aba>=(*itL).Height())
				{
					CRect Rect((*itL).left-izq,(*itL).top,(*itL).left,(*itL).bottom);
					//Poner bloque pegado a la izquierda
					if (Existe_Perdida(listaP,Rect,0)==true)
					{
						(*itL).left=(*itL).left-izq;
						(*itL).right=(*itL).right-izq;
						//Nueva perdida
						CRect perdida;
						perdida.left=(*itL).right;
						perdida.right=(*itL).right+izq;
						perdida.top=(*itL).top;
						perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
						seguir=true;
					}
				}
				else
				{
					//Tengo que puedo mover solo un trozo de bloque
					if (arr-aba>=w)
					{
						BLOQUE b1=(*itL),b2=(*itL),b3=(*itL);
						//meto
						int change=(arr-aba)/w;
						//b1 arriba
						//b2 en medio 
						//b3 abajo
						if (aba==(*itL).top)
						{
							b1.top=(*itL).top;
							b1.bottom=b1.top+change*w;
							b2.top=b1.bottom;
							b2.bottom=(*itL).bottom;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;

//							if (!b3.IsRectEmpty()) listaB.push_back(b3;
						}
						if (arr==(*itL).bottom)
						{
							b2.bottom=(*itL).bottom;
							b2.top=(*itL).bottom-change*w;
							b1.top=(*itL).top;
							b1.bottom=b2.top;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;
//							if (!b3.IsRectEmpty()) listaB.push_back(b3;

						}
						if (arr!=(*itL).bottom && aba!=(*itL).top)
						{
							int min=ceil((double)(aba-(*itL).top)/(double)w);
							int max=ceil((double)((*itL).bottom-arr)/(double)w);
							if (min+max<((*itL).Height()/w))
							{
								b1.top=(*itL).top;
								b1.bottom=(*itL).top+min*w;
								b2.top=(*itL).bottom-max*w;
								b2.bottom=(*itL).bottom;
								b3.top=b1.bottom;
								b3.bottom=b2.top;
								if (!b1.IsRectEmpty()) listaB.push_back(b1);
								if (!b2.IsRectEmpty()) listaB.push_back(b2);
								if (!b3.IsRectEmpty()) listaB.push_back(b3);
								itL=listaB.erase(itL);

								seguir=true;
								continue;

							}

						}
					}
				}
			}
		}
		if ((*itL).left>(m_L/2) && ((*itL).left!=0) && ((*itL).right!=m_L))
		{
			ProximoBloque(listaP,(*itL),2,RectTemp);
			der=RectTemp.right-RectTemp.left;
			if (der>0)
			{
				aba=__max((*itL).top,RectTemp.top);
				arr=__min((*itL).bottom,RectTemp.bottom);
				if (arr-aba>=(*itL).Height())
				{

					CRect Rect((((*itL).right)),(*itL).top,(*itL).right+der,(*itL).bottom);
				
					//Poner bloque pegado a la derecha
					if (Existe_Perdida(listaP,Rect,0)==true)
					{
						(*itL).right=(*itL).right+der;
						(*itL).left=(*itL).left+der;
						CRect perdida;
						perdida.left=(*itL).left-der;
						perdida.right=(*itL).left;
						perdida.top=(*itL).top;
						perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
						seguir=true;
					}
				}
				else
				{
					//Tengo que puedo mover solo un trozo de bloque
					if (arr-aba>=w)
					{
						BLOQUE b1=(*itL),b2=(*itL),b3=(*itL);
						//meto
						int change=(arr-aba)/w;
						//b1 arriba
						//b2 en medio 
						//b3 abajo
						if (aba==(*itL).top)
						{
							b1.top=(*itL).top;
							b1.bottom=b1.top+change*w;
							b2.top=b1.bottom;
							b2.bottom=(*itL).bottom;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;

//							if (!b3.IsRectEmpty()) listaB.push_back(b3;
						}
						if (arr==(*itL).bottom)
						{
							b2.bottom=(*itL).bottom;
							b2.top=(*itL).bottom-change*w;
							b1.top=(*itL).top;
							b1.bottom=b2.top;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;
//							if (!b3.IsRectEmpty()) listaB.push_back(b3;

						}
						if (arr!=(*itL).bottom && aba!=(*itL).top)
						{
							int min=ceil((double)(aba-(*itL).top)/(double)w);
							int max=ceil((double)((*itL).bottom-arr)/(double)w);
							if (min+max<((*itL).Height()/w))
							{
								b1.top=(*itL).top;
								b1.bottom=(*itL).top+min*w;
								b2.top=(*itL).bottom-max*w;
								b2.bottom=(*itL).bottom;
								b3.top=b1.bottom;
								b3.bottom=b2.top;
								if (!b1.IsRectEmpty()) listaB.push_back(b1);
								if (!b2.IsRectEmpty()) listaB.push_back(b2);
								if (!b3.IsRectEmpty()) listaB.push_back(b3);
								itL=listaB.erase(itL);

								seguir=true;
								continue;

							}

						}
					}
				}

			}
		}
		//Moverla hacia al lado arriba o abajo del pallet
		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if (((*itL).top<=(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=m_W))
		{
			ProximoBloque(listaP,(*itL),3,RectTemp);
			aba=RectTemp.bottom-RectTemp.top;
			if (aba>0)
			{
				izq=__max((*itL).left,RectTemp.left);
				der=__min((*itL).right,RectTemp.right);
				if (der-izq>=(*itL).Width())
				{

					CRect Rect((*itL).left,(*itL).top-aba,(*itL).right,(*itL).top);

					//Poner bloque pegado a abajo
					if (Existe_Perdida(listaP,Rect,1)==true)
					{
						(*itL).top=(*itL).top-aba;
						(*itL).bottom=(*itL).bottom-aba;
						//Nueva perdida
						CRect perdida;
						perdida.top=(*itL).bottom;
						perdida.bottom=(*itL).bottom+aba;
						perdida.left=(*itL).left;
						perdida.right=(*itL).right;
						listaP.push_back(perdida);
						seguir=true;
					}
				}
				else
				{
					//Tengo que puedo mover solo un trozo de bloque
					if (der-izq>=l)
					{
						BLOQUE b1=(*itL),b2=(*itL),b3=(*itL);
						//meto
						int change=(der-izq)/l;
						//b1 arriba
						//b2 en medio 
						//b3 abajo
						if (izq==(*itL).left)
						{
							b1.left=(*itL).left;
							b1.right=b1.left+change*l;
							b2.left=b1.right;
							b2.right=(*itL).right;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;

//							if (!b3.IsRectEmpty()) listaB.push_back(b3;
						}
						if (der==(*itL).right)
						{
							b2.right=(*itL).right;
							b2.left=(*itL).right-change*l;
							b1.left=(*itL).left;
							b1.right=b2.left;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;
//							if (!b3.IsRectEmpty()) listaB.push_back(b3;

						}
						if (der!=(*itL).right && izq!=(*itL).left)
						{
							int min=ceil((double)(izq-(*itL).left)/(double)l);
							int max=ceil((double)((*itL).right-der)/(double)l);
							if (min+max<((*itL).Width()/l))
							{
								b1.left=(*itL).left;
								b1.right=(*itL).left+min*l;
								b2.left=(*itL).right-max*l;
								b2.left=(*itL).right;
								b3.left=b1.right;
								b3.right=b2.left;
								if (!b1.IsRectEmpty()) listaB.push_back(b1);
								if (!b2.IsRectEmpty()) listaB.push_back(b2);
								if (!b3.IsRectEmpty()) listaB.push_back(b3);
								itL=listaB.erase(itL);

								seguir=true;
								continue;

							}

						}
					}

				}
			}
		}
		if (((*itL).top>(m_W/2)) && ((*itL).top!=0) && ((*itL).bottom!=m_W))
		{	
			//Lado izquierdo arriba
			ProximoBloque(listaP,(*itL),4,RectTemp);
			int arri=RectTemp.bottom-RectTemp.top;
			if (arri>0)
			{
				izq=__max((*itL).left,RectTemp.left);
				der=__min((*itL).right,RectTemp.right);
				if (der-izq>=(*itL).Width())
				{

					CRect Rect((((*itL).left)),(*itL).bottom,(*itL).right,(*itL).bottom+arri);
				
					//Poner bloque pegado a la derecha
					if (Existe_Perdida(listaP,Rect,1)==true)
					{
						(*itL).bottom=(*itL).bottom+arri;
						(*itL).top=(*itL).top+arri;
						CRect perdida;
						perdida.bottom=(*itL).top;
						perdida.top=(*itL).top-arri;
						perdida.left=(*itL).left;
						perdida.right=(*itL).right;
						listaP.push_back(perdida);
						seguir=true;
					}
				}
				else
				{
					//Tengo que puedo mover solo un trozo de bloque
					if (der-izq>=l)
					{
						BLOQUE b1=(*itL),b2=(*itL),b3=(*itL);
						//meto
						int change=(der-izq)/l;
						//b1 arriba
						//b2 en medio 
						//b3 abajo
						if (izq==(*itL).left)
						{
							b1.left=(*itL).left;
							b1.right=b1.left+change*l;
							b2.left=b1.right;
							b2.right=(*itL).right;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;

//							if (!b3.IsRectEmpty()) listaB.push_back(b3;
						}
						if (der==(*itL).right)
						{
							b2.right=(*itL).right;
							b2.left=(*itL).right-change*l;
							b1.left=(*itL).left;
							b1.right=b2.left;
							if (!b1.IsRectEmpty()) listaB.push_back(b1);
							if (!b2.IsRectEmpty()) listaB.push_back(b2);
							itL=listaB.erase(itL);
							seguir=true;

							continue;
//							if (!b3.IsRectEmpty()) listaB.push_back(b3;

						}
						if (der!=(*itL).right && izq!=(*itL).left)
						{
							int min=ceil((double)(izq-(*itL).left)/(double)l);
							int max=ceil((double)((*itL).right-der)/(double)l);
							if (min+max<((*itL).Width()/l))
							{
								b1.left=(*itL).left;
								b1.right=(*itL).left+min*l;
								b2.left=(*itL).right-max*l;
								b2.left=(*itL).right;
								b3.left=b1.right;
								b3.right=b2.left;
								if (!b1.IsRectEmpty()) listaB.push_back(b1);
								if (!b2.IsRectEmpty()) listaB.push_back(b2);
								if (!b3.IsRectEmpty()) listaB.push_back(b3);
								itL=listaB.erase(itL);

								seguir=true;
								continue;

							}

						}
					}

				}
			}	
		}
		itL++;

	}while(itL!=listaB.end() && seguir!=true);
	}while(seguir!=false);
	m_tipo_junta=1;
}
*/
int PALLET::BloqueCercaPerdidas(BLOQUE &B,int val)
{
	int largo=0,ancho=0;
	int PerdidaPos=(m_L*m_W)-((m_solbest+1)*m_l*m_w);
	if (m_todas==true) PerdidaPos=0;
	//Los que sean todo el ancho que y que tenga la perdida por arriba 
	// solo se podrían reducir en toda la fila con esto también reducir alguno
	// lo mismo para los que vayan de arriba a abajo
//	return true;
	if (B.Width()==m_L)
	{
		if (val==5 || val==6) val=0;
	}
	if (B.Height()==m_W)
	{
		if (val==1 || val==2) val=0;
	}


	int totalP=(m_L*m_W)-(m_Cota*m_l*m_w);
	int perdi=0;
//	if (val!=0 && (B.Width()==m_l || B.Width()==m_w || B.Height()==m_l || B.Height()==m_w  ))
//		return true;
	std::list<CRect> ::iterator itB;
	for (itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
		//Por la izquierda
		//Si a la izquierda
		if (((((*itB).right==B.left) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
		|| (((*itB).right==B.left) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
		|| (((*itB).right==B.left) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
		|| (((*itB).right==B.left) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
		&& (val==6 || val==8 || val==0))
		{
			//Si es un g4 no quiero reducir solo aumentar
			if (!((B.PuedoMover()!=true) && (val==1 || val==2 || val==5 || val==6 ) && ( (*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH)) )
				perdi+=(*itB).Width()*(*itB).Height();

		}
		//Si a la derecha
		if (((((*itB).left==B.right) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
		|| (((*itB).left==B.right) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
		|| (((*itB).left==B.right) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
		|| (((*itB).left==B.right) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
		&& (val==5 || val==7 || val==0))
		{
			//Si es un g4 no quiero reducir solo aumentar
			if (!((B.PuedoMover()!=true) && (val==1 || val==2 || val==5 || val==6 ) && ( (*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH)) )
				perdi+=(*itB).Width()*(*itB).Height();
		}
		//Si a abajo
		if (((((*itB).bottom==B.top) && ((*itB).left>B.left) && ((*itB).left<B.right))
		|| (((*itB).bottom==B.top) && ((*itB).right>B.left) && ((*itB).right<B.right))
		|| (((*itB).bottom==B.top) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
		|| (((*itB).bottom==B.top) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
		&& (val==2 || val==4 || val==0))
		{
			//Si es un g4 no quiero reducir solo aumentar
			if (!((B.PuedoMover()!=true) && (val==1 || val==2 || val==5 || val==6 ) && ( (*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH)) )
				perdi+=(*itB).Width()*(*itB).Height();
		}
		//Si a arriba
		if (((((*itB).top==B.bottom) && ((*itB).left>B.left) && ((*itB).left<B.right))
		|| (((*itB).top==B.bottom) && ((*itB).right>B.left) && ((*itB).right<B.right))
		|| (((*itB).top==B.bottom) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
		|| (((*itB).top==B.bottom) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
		&& (val==1 || val==3 || val==0))
		{
			//Si es un g4 no quiero reducir solo aumentar
			if (!((B.PuedoMover()!=true) && (val==1 || val==2 || val==5 || val==6 ) && ( (*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH)) )
				perdi+=(*itB).Width()*(*itB).Height();
		}
//		if ((*itB).Width()>largo) largo=(*itB).Width();
//		if ((*itB).Height()>ancho) ancho=(*itB).Height();
		m_tam_perdida=perdi;
//		if (val==0 && perdi>(double)totalP/(double)5) return true;
//		if (val!=0 && perdi>0) return true;
		//Si voy a reducir por arriba o por abajo y no cabe una pieza no reduzco
		if (B.GetTipo()=='H' && (val==1 || val==2) && (*itB).Width()<m_w) perdi=0;
		//Si voy a reducir por derecha o por izquierda y no cabe una pieza no reduzco
		if (B.GetTipo()=='V' && (val==5 || val==6) && (*itB).Height()<m_w) perdi=0;
/*		if (val<=4 && val!=0 && perdi>0 )  return (*itB).Height();
		if (val>=5 && perdi>0 )  return (*itB).Width();

		if (perdi>0 ) return perdi;
*/
		if (val<=4 && val!=0 && perdi>0 && perdi>((double)PerdidaPos/(double)4))  return (*itB).Height();
		if (val>=5 && perdi>0 && perdi>((double)PerdidaPos/(double)4))  return (*itB).Width();

		if (perdi>0 && perdi>((double)PerdidaPos/(double)4)) return perdi;

	}

	return 0;

}
//Las veces que es mas pequeña 
int PALLET::MayorPerdida()
{
	int totalP=(m_L*m_W)-(m_Cota*m_l*m_w);
	int perdi=0;
	std::list<CRect> ::iterator itB;
	for (itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
		if (((*itB).Width()*(*itB).Height())>perdi)
			perdi=((*itB).Width()*(*itB).Height());
	}
	return ceil((double)totalP/(double)perdi);
}
//Lista TabuPerdidas
bool PALLET::EsTabuPerdidas(std::list<CRect> &lista)
{
	return false;
	bool distinta=true,entera=true;
	int bien=0;
	std::list< std::list<CRect> > ::iterator itB;
	std::list<CRect>::iterator itB2,itB3;
	for (itB=m_lista_tabu_perdidas.begin();itB!=m_lista_tabu_perdidas.end();itB++)
	{
		if ((*itB).size()==lista.size())
		{
			distinta=false;
			for(itB2=(*itB).begin();itB2!=(*itB).end() && distinta==false;itB2++)
			{

				distinta=true;
				for(itB3=lista.begin();itB3!=lista.end() && distinta!=false;itB3++)
				{
					if ((*itB3).EqualRect((*itB2))!=0) distinta=false;
				}
				

			}
		}
		if (distinta==true || (*itB).size()!=lista.size()) 
		{
			bien++;
		}
		

	}

	if (bien==m_lista_tabu_perdidas.size()) return false;
	else return true;
}
bool PALLET::EsTabuPerdidasSinLaUltima(std::list<CRect> &lista)
{
	return false;
	bool distinta=true,entera=true;
	int bien=0;
	 int la_primera_no_vale=0;
	std::list< std::list<CRect> > ::iterator itB;
	std::list<CRect>::iterator itB2,itB3;
	for (itB=m_lista_tabu_perdidas.begin();itB!=m_lista_tabu_perdidas.end();itB++)
	{
		la_primera_no_vale++;
		if (la_primera_no_vale==1) continue;
		if ((*itB).size()==lista.size())
		{
			distinta=false;
			for(itB2=(*itB).begin();itB2!=(*itB).end() && distinta==false;itB2++)
			{

				distinta=true;
				for(itB3=lista.begin();itB3!=lista.end() && distinta!=false;itB3++)
				{
					if ((*itB3).EqualRect((*itB2))!=0) distinta=false;
				}
				

			}
		}
		if (distinta==true || (*itB).size()!=lista.size()) 
		{
			bien++;
		}
		

	}

	if (bien==m_lista_tabu_perdidas.size()) return false;
	else return true;
}
void PALLET::Add_Lista_TabuPerdidas(std::list<CRect> &lista)
{
	return;
	CRect RectTemp;

	if (m_lista_tabu.size()>m_tam_tabu_perdidas)
	{
		m_lista_tabu_perdidas.pop_front();
		m_lista_tabu_perdidas.push_back(lista);
	}
	else
	{
		m_lista_tabu_perdidas.push_back(lista);

	}
}
bool  PALLET::TieneRasterPoint(int x, int y, char tipo)
{
	if (m_Raster==false) return true;
	if (x==0 && y==0) return true;
	bool orden=false;
	std::vector< var >::iterator v1;
	if (tipo=='H')
	{
		for (v1=m_VectorDeVarH.begin();v1!=m_VectorDeVarH.end();v1++)
		{
		
			if ((*v1).x==x && (*v1).y==y )
				return true;
			if ((*v1).x==0 && (*v1).y==y )
				orden=true;
			if ((*v1).x!=0 && orden==false)
				return false;
		}
	}
	if (tipo=='V')
	{
		for (v1=m_VectorDeVarV.begin();v1!=m_VectorDeVarV.end();v1++)
		{
		
			if ((*v1).x==x && (*v1).y==y )
				return true;
			if ((*v1).x==0 && (*v1).y==y )
				orden=true;
			if ((*v1).x!=0 && orden==false)
				return false;
		}
	}

	return false;
}
bool  PALLET::TieneRasterPoint(int x, int y, char tipo,int x2,int y2)
{
	bool esq_inferior=false;
	std::vector< var >::iterator v1;
	for (v1=m_VectorDeVar.begin();v1!=m_VectorDeVar.end();v1++)
	{
		
		if ((*v1).x==x && (*v1).y==y && (*v1).orientacion==tipo)
			esq_inferior=true;
		if (esq_inferior==true && (*v1).x==x2 && (*v1).y==y2 && (*v1).orientacion==tipo)
			return true;
	}
	return false;
}

bool  PALLET::TodosTieneRasterPoint(std::list<BLOQUE> &lista)
{

//	return true;
//	if (m_iter_actual>999) return true;
	if ((m_iter_actual>m_tam_tabu) && (m_tam_tabu>m_lista_tabu.size())) return true;
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		int l=m_l;
		int w=m_w;
		if ((*itB).GetTipo()=='V')
		{
			l=m_w;
			w=m_l;
		}
		if (TieneRasterPoint((*itB).left,(*itB).top,(*itB).GetTipo())==false)
			return false;
/*		if (((*itB).Width()/l)>1)
		{
			if (TieneRasterPoint((*itB).right-l,(*itB).top,(*itB).GetTipo())==false)
				return false;
		}
		if (((*itB).Height()/w)>1)
		{
			if (TieneRasterPoint((*itB).left,(*itB).bottom-w,(*itB).GetTipo())==false)
				return false;
		}
		if ((((*itB).Height()/w)>1) && (((*itB).Width()/l)>1))
		{
			if (TieneRasterPoint((*itB).right-l,(*itB).bottom-w,(*itB).GetTipo())==false)
				return false;
		}
*/		/*
		if ((*itB).GetTipo()=='H')
		{
			if (TieneRasterPoint((*itB).left,(*itB).top,(*itB).GetTipo(),(*itB).right-m_l,(*itB).bottom-m_w)==false)
				return false;
		}
		else
		{
			if (TieneRasterPoint((*itB).left,(*itB).top,(*itB).GetTipo(),(*itB).right-m_w,(*itB).bottom-m_l)==false)
				return false;
		}
		*/
	}
	return true;
}
void PALLET::EscribirBloquesPantalla(std::list<BLOQUE> &lista)
{
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		printf("%3d\t%3d\t%3d\t%3d\t%c\n",(*itB).top,(*itB).bottom,(*itB).left,(*itB).right,(*itB).GetTipo());
	}

	//Reta
}
void PALLET::EscribirBloques(std::list<BLOQUE> &lista)
{
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		fprintf(fin,"%3d\t%3d\t%3d\t%3d\t%c\n",(*itB).top,(*itB).bottom,(*itB).left,(*itB).right,(*itB).GetTipo());
	}

	//Reta
}
bool PALLET::EstaBloque(BLOQUE &B,std::list<BLOQUE> lista)
{
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		if (B.left==(*itB).left && B.right==(*itB).right && B.top==(*itB).top && B.bottom==(*itB).bottom && B.GetTipo()==(*itB).GetTipo())
			return true;
	}
	return false;
}
int PALLET::CuantosG4(int Ancho, int Largo)
{
	int maximo=0;
	int maxthis=0;
//	std::list<strg4> ::iterator itg;
	std::vector<strg4> ::iterator itg;
	int cota_parcial=(Ancho*Largo)/ (m_l*m_w);
	for (itg=m_lista_GCuatros.begin();itg!=m_lista_GCuatros.end() && maximo!=cota_parcial;itg++)
	{
		m_G4_TCajas=(*itg).G4_TCajas;
		m_G4_THorizontal=(*itg).G4_THorizontal;
		m_G4_TVertical=(*itg).G4_TVertical;
		m_G4_HuecoH=(*itg).G4_HuecoH;
		m_G4_HuecoV=(*itg).G4_HuecoV;
		m_G4_CajasH=(*itg).G4_CajasH;
		m_G4_CajasV=(*itg).G4_CajasV;
		m_G4_CajasHH=(*itg).G4_CajasHH;
		m_G4_CajasVV=(*itg).G4_CajasVV;
		m_G4_PequeH=(*itg).G4_PequeH;
		m_G4_PequeV=(*itg).G4_PequeV;

	//Solo mira los sencillos
		if (m_G4_THorizontal!=m_G4_TVertical)
		{
			int max1=((Ancho/m_G4_TVertical)*(Largo/m_G4_THorizontal));
			int max2=((Largo/m_G4_TVertical)*(Ancho/m_G4_THorizontal));
			if (max1>max2) maxthis=max1*(m_G4_TCajas);
			else maxthis=max2*(m_G4_TCajas);

		}	
		else
			maxthis=((Ancho/m_G4_TVertical)*(Largo/m_G4_THorizontal))*(m_G4_TCajas);
		if (maxthis>maximo)
			maximo=maxthis;
	}
	return maximo;


}
void PALLET::CrearMatrices(void)
{
//	return;
//	m_matrizH.reserve((m_L/m_l)+1);
	std::vector<short int> temp1((m_W/m_w)+1);
	//Reservo espacio para la matriz
	for (register int jj=0;jj<(m_L/m_l)+1;jj++)
	{
		m_matrizH.push_back(temp1);
	}
//	m_matrizV.reserve((m_L/m_w)+1);
	std::vector<short int> temp2((m_W/m_l)+1);

	//Reservo espacio para la matriz
	for (register int j2=0;j2<(m_L/m_w)+1;j2++)
	{
		m_matrizV.push_back(temp2);;
	}
}
void PALLET::ActualizarMatrices(void)
{
//	return;
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
//		BLOQUE b1=(*itB);
		if ((*itB).GetTipo()=='H') m_matrizH[(*itB).Width()/m_l][(*itB).Height()/m_w]++;
		else m_matrizV[(*itB).Width()/m_w][(*itB).Height()/m_l]++;
	}
}
int PALLET::ContarFrecuencias(std::list<BLOQUE> &lista)
{
//	return;
	int min=200000,val=0;
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
//		BLOQUE b1=(*itB);
//		if ((*itB).GetTipo()=='H') val+=m_matrizH[(*itB).Width()/m_l][(*itB).Height()/m_w];
//		else val+=m_matrizV[(*itB).Width()/m_w][(*itB).Height()/m_l];
		if (Es_Eficiente_Bloque((*itB))==true)
		{
			if ((*itB).GetTipo()=='H') val=m_matrizH[(*itB).Width()/m_l][(*itB).Height()/m_w];
			else val=m_matrizV[(*itB).Width()/m_w][(*itB).Height()/m_l];
			if (val<min) min=val;
		}



	}
	return val;
}
int PALLET::VecesQueHaAparecidoElBloque(BLOQUE &B)
{
	if (B.GetTipo()=='H') return m_matrizH[B.Width()/m_l][B.Height()/m_w];
	else return m_matrizV[B.Width()/m_w][B.Height()/m_l];
}
void PALLET::MostrarFrecuencias(void)
{
//	printf("%d\t",m_matrizH[1,1]);

	printf("Matriz de H\n");

	for (int register j=1;j<=(m_W/m_w);j++)
	{
		for (int register i=1;i<=(m_L/m_l);i++)
		{
			printf("%d\t",m_matrizH[i][j]);

		}
		printf("\n");
	}
	printf("Matriz de V\n");
	for (j=1;j<=(m_W/m_l);j++)
	{
		for (int register i=1;i<=(m_L/m_w);i++)
		{
			printf("%d\t",m_matrizV[i][j]);
		}
		printf("\n");

	}

}
void PALLET::DibujarSolucion(std::list<BLOQUE> &lista_bloques,std::list<CRect> &lista_per,int sol,int perdida)
{
//	if (m_iter_actual<20) return;
	if (m_Dibujar==true)
	{
		DibujarBloques(lista_bloques,lista_per,m_iter_actual,sol,perdida,m_solbest,m_paso_a_paso,m_lista_tabu.size());
	//JMT
		if(m_paso_a_paso)
		{
			MSG msg;
			while(!GetMessage(&msg,m_clientedc->GetWindow()->m_hWnd,WM_KEYFIRST,WM_KEYLAST))
			{
					m_clientedc->GetWindow()->SendMessage(msg.message);
				
				}
				TRACE("%d ",msg.wParam);
				if(msg.wParam==27)
				{
					m_clientedc->GetWindow()->SendMessage(msg.message,msg.wParam,msg.lParam);
					exit(0);
				}
				GetMessage(&msg,m_clientedc->GetWindow()->m_hWnd,WM_KEYFIRST,WM_KEYLAST);
		}
	}
}/*
double PALLET::Porcentaje_Eficiente(BLOQUE &B)
{
	int PerdidaPos=(m_L*m_W)-((m_solbest+1)*m_l*m_w);
	if (ParticionEficienteX(B.Width(),B.GetTipo())==true)
	{
		if (ParticionEficienteY(B.Height(),B.GetTipo())==true) 
		{
			return -5;
		}
		if (ParticionPerfecta(m_W-B.Height())*B.Width()>PerdidaPos)
			return 1;
		else
			return (ParticionPerfecta(m_W-B.Height())*B.Width())/PerdidaPos;
	}
	else
	{
		if (ParticionEficienteY(B.Height(),B.GetTipo())==true) 
		{
			if (ParticionPerfecta(m_L-B.Width())*B.Height()>PerdidaPos)
				return 1;
			else
				return (ParticionPerfecta(m_L-B.Width())*B.Height())/PerdidaPos;
		}
		if ((ParticionPerfecta(m_W-B.Height())*B.Width())+(ParticionPerfecta(m_L-B.Width())*B.Height())>PerdidaPos)
			return 5;
		else
			return ((ParticionPerfecta(m_W-B.Height())*B.Width())+((ParticionPerfecta(m_L-B.Width())*B.Height())))/PerdidaPos;
	}

}*/

double PALLET::Porcentaje_Eficiente(BLOQUE &B)
{
	if (m_Eficientes!=true) return true;
	int PerdidaPos=(m_L*m_W)-((m_solbest+1)*m_l*m_w);
	if (PerdidaPos==0) return 0;
	if (ParticionEficienteX(B.Width(),B.GetTipo())==true)
	{
		if (ParticionEficienteY(B.Height(),B.GetTipo())==true) 
		{
			return -5;
		}
		else return (((ParticionPerfecta(m_W-B.Height())*B.Width())/PerdidaPos));
//		else return 2*(((double)(ParticionPerfecta(m_W-B.Height())*B.Width())/(double)PerdidaPos));
	}
	else
	{
		if (ParticionEficienteY(B.Height(),B.GetTipo())==true) 
		{
			return (((ParticionPerfecta(m_L-B.Width())*B.Height())/PerdidaPos));
//			return 2*(((double)(ParticionPerfecta(m_L-B.Width())*B.Height())/(double)PerdidaPos));
		}
		if ((ParticionPerfecta(m_W-B.Height())*B.Width())+(ParticionPerfecta(m_L-B.Width())*B.Height())>PerdidaPos)
			return 5;
		else
			return 4*((ParticionPerfecta(m_W-B.Height())*B.Width())+((ParticionPerfecta(m_L-B.Width())*B.Height())))/PerdidaPos;
	}

}
long int PALLET::EvaluarMovimiento(MOVE &Movimiento)
{
		long int max_candidatos=0;

//		if (m_iter_actual%10>5) max_candidatos+=Movimiento.GetListaBloques().size()*10000;
//		if (CumpleNumHV(Movimiento.GetListaBloques())==true)
//			max_candidatos+=10000;


		int Contar_Nuevas_H=ContarH(Movimiento.GetListaBloques());
		int Contar_H=ContarH(m_lista_bloques);
//		max_candidatos+=m_tam_perdida*1;
//		if (m_iter_actual>250) max_candidatos+=abs(Contar_Nuevas_H-Contar_H)*CAMBIOTIPO*5;
//		if (m_iter_actual>250 && m_iter_actual%5==0) max_candidatos+=abs(Contar_Nuevas_H-Contar_H)*CAMBIOTIPO*5;
//		if (m_iter_actual>5000) max_candidatos+=abs(Contar_Nuevas_H-Contar_H)*CAMBIOTIPO*5;
		//Forma de ls perdidas si tiene perdidas con mayor anchura del andho no
		//las quiero
		max_candidatos-=abs(PerdidaMayor(Movimiento.GetListaPerdidas())-1)*PERDIDAMAYOR;
		//Si los bloques son eficientes
		//Si todos los bloques eficientes
		//Divido entre 10 lo mejor y despues divido entre 200 a partir de 50000
		if (Es_Eficiente(Movimiento.GetListaBloques())==true ) max_candidatos+=EFICIENTES;
		//Me devuelve mas cuanto menos eficiente fuera el bloque anterior
		max_candidatos+=(EFIBLOQUE)*Porcentaje_Eficiente(Movimiento.GetBloqueAntiguo());
		//Si es un movimiento de quitar piezas sin colocar nada
		if (Movimiento.GetAlgoNuevo()==true) max_candidatos+=NUEVO;
		//Si era tabu2 el movimiento anterior
//		if (EsTabu2(Movimiento.GetBloqueAntiguo())==false) max_candidatos+=TABU2;
		//Si es valida con simetria la solución 
		if (Valida_Simetria(Movimiento.GetListaPerdidas())==true) max_candidatos+=SIMETRIA;
		//Si es valida con el optimo lo que me dice es si existe algún bloque que no puede
		//estar en una solución óptima
		if (Valida_Optimo(Movimiento.GetListaBloques())==true) max_candidatos+=OPTIMO;
		//Forma de las pérdidas pondera que la solución sea simétrica respecto del centro
		//que no tenga pérdidas en las esquinas y que el rectángulo de perdidas sea lo
		// menor posible
/*		if ((Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas()))>m_max_rect)
			m_max_rect=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
		if ((Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas()))<m_min_rect)
			m_min_rect=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());*/
//		if (m_iter_actual%100<=50) max_candidatos+=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
		max_candidatos-=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
/*		int rect_div=10;
//		if (m_iter_actual==
		
//solo me quedan 20
		if (m_iter_actual>=10000) rect_div=50;
		if (m_iter_actual>=20000) rect_div=100;
		if (m_iter_actual>=40000) rect_div=200;
		if (m_iter_actual>=60000) rect_div=300;
		if (m_iter_actual>=80000) rect_div=400;
		int cien=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas())/rect_div;

		max_candidatos-=(cien*50);
*/
//		if (m_iter_actual>=10000) rect_div=50;
//		int cien=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas())/rect_div;

//		max_candidatos-=(cien*50);

//		conjunto_kk.insert(cien*50);
		max_candidatos-=(PerdidaEnLados(Movimiento.GetListaPerdidas()))*PERDIDALADOS;
//		max_candidatos-=ParticionesGrandes(Movimiento.GetListaBloques())*3000;
/*		int per_lados=(PerdidaEnLados(Movimiento.GetListaPerdidas()));
		if (per_lados>=3) 
			max_candidatos-=per_lados*PERDIDALADOS*2;
		else
			max_candidatos-=per_lados*PERDIDALADOS/2;*/
//		max_candidatos-=(PerdidasPequenas(Movimiento.GetListaPerdidas()))*880;
		//Peso de la función objetivo
//		if (BloquesGrandes(Movimiento.GetListaBloques())==true)
//			max_candidatos-=10000;
		max_candidatos+=Movimiento.GetValor()*VALOROPTIMO;
		//Prefiero quitar o poner bloques que han aparecido muchas veces en las mejores soluciones
//		if (m_iter_actual>1000)
//		max_candidatos-=VecesQueHaAparecidoElBloque(Movimiento.GetBloqueAntiguo())*100;
		if (m_utilizar_frecuencias==true)
		max_candidatos+=VecesQueHaAparecidoElBloque(Movimiento.GetBloqueAntiguo())*100;

		//Diversifica contado cuantas veces ha aparecido el bloque en la solución 
		//actual
//		if ((m_iter_actual>=10000) )
/*		if (m_Diversificar==true)
		{
			max_candidatos=ContarFrecuencias(Movimiento.GetListaBloques());
		}
*/		
//		max_candidatos=Movimiento.GetValor()*VALOROPTIMO;

		return max_candidatos;
}
void PALLET::AlgoritmoUnBloque(std::list<BLOQUE> &lista_bloques,std::list<CRect> &lista_perdidas)
{
	int horizontal=((((m_L)/(m_l)))*(((m_W)/m_w)));
	int vertical=((((m_L)/(m_w)))*(((m_W)/m_l)));

	if (horizontal>vertical)
	{
		BLOQUE UnBloqueH(0,0,((m_L)/(m_l))*m_l,((m_W)/m_w)*m_w,'H');
		lista_bloques.push_back(UnBloqueH);
	}
	else
	{
		BLOQUE UnBloqueV(0,0,((m_L)/(m_w))*m_w,((m_W)/m_l)*m_l,'V');
		lista_bloques.push_back(UnBloqueV);

	}
//	intervalo cuatro_blo=Heuristico4Bloques();
//	m_lista_bloques=Construir_Bloques(cuatro_blo);
	CRect PTotal(0,0,m_L,m_W),RectTemp;
	lista_perdidas.push_back(PTotal);
	//Construyo rectángulos de pérdida 
	Actualizar_Perdida(lista_bloques,lista_perdidas);
	//

}
void PALLET::AlgoritmoCuatroBloques(std::list<BLOQUE> &lista_bloques,std::list<CRect> &lista_perdidas)
{
	
	intervalo cuatro_bloques=Heuristico4Bloques();
	int B1x=cuatro_bloques[0];
	int B1y=cuatro_bloques[1];
	int B2x=cuatro_bloques[2];
	int B2y=cuatro_bloques[3];
	int B3x=cuatro_bloques[4];
	int B3y=cuatro_bloques[5];
	int B4x=cuatro_bloques[6];
	int B4y=cuatro_bloques[7];
	if (B1x!=0 && B1y!=0)
	{
		BLOQUE UnBloqueH(0,0,B1x*m_l,B1y*m_w,'H');
		lista_bloques.push_back(UnBloqueH);
	}
	if (B2x!=0 && B2y!=0)
	{
		BLOQUE UnBloqueH(m_L-(B2x*m_w),0,m_L,B2y*m_l,'V');
		lista_bloques.push_back(UnBloqueH);
	}
	if (B3x!=0 && B3y!=0)
	{
		BLOQUE UnBloqueH(m_L-(B3x*m_l),m_W-(B3y*m_w),m_L,m_W,'H');
		lista_bloques.push_back(UnBloqueH);
	}
	if (B4x!=0 && B4y!=0)
	{
		BLOQUE UnBloqueH(0,m_W-(B4y*m_l),B4x*m_w,m_W,'V');
		lista_bloques.push_back(UnBloqueH);
	}
	CRect PTotal(0,0,m_L,m_W),RectTemp;
	lista_perdidas.push_back(PTotal);
	//Construyo rectángulos de pérdida 
	Actualizar_Perdida(lista_bloques,lista_perdidas);
	//

}
//Comp
void PALLET::VerificarSolucion(std::list<BLOQUE> &lista_bloques,std::list<CRect> &lista_perdidas,int lugar)
{
	return;
	int sol=Contar(lista_bloques);
	int perdida=Contar(lista_perdidas);
	if (perdida!=((m_L*m_W)-(sol*m_l*m_w)))
	{
		printf("Problemas en Actualizar Bloques %d Iteracion %d",lugar,m_iter_actual);
		printf("Tamaño del g4 verticales y horizontales %d %d %d %d",m_G4_CajasV,m_G4_CajasVV,m_G4_CajasH,m_G4_CajasHH);
//			for(int register i=0;;i++) printf("Problemas en MejorarBloques 2");
		for(int register i=0;;i++) int j=0;
		exit(3);
	}
	bool intersectan_bloques=ComprobarBloquesNoIntersectan(lista_bloques);
	if (intersectan_bloques==true)
	{
		printf(" Intersectan bloques%d Iteracion %d",lugar,m_iter_actual);
		for(int register i=0;;i++) ;
		exit(3);
	}
	bool intersectan_bloqu_perdi=ComprobarBloquesYPerNoIntersectan(lista_bloques,lista_perdidas);
	if (intersectan_bloqu_perdi==true)
	{
		printf("Intersectan bloques y perdidas %d Iteracion %d",lugar,m_iter_actual);
		for(int register i=0;;i++) ;
		exit(3);
	}

}
bool PALLET::EstaLaPerdida(std::list<CRect> &listaP,CRect &R)
{
	std::list<CRect>::iterator itB;
	for(itB=listaP.begin();itB!=listaP.end();itB++)
	{
		if (((*itB).TopLeft()==R.TopLeft()) && ((*itB).BottomRight()==R.BottomRight()))
		return true;

	}
	return false;
}
bool PALLET::EstaElBloque(std::list<BLOQUE> &listaP,BLOQUE &R)
{
	std::list<BLOQUE>::iterator itB;
	for(itB=listaP.begin();itB!=listaP.end();itB++)
	{
		if (((*itB).TopLeft()==R.TopLeft()) && ((*itB).BottomRight()==R.BottomRight()) && ((*itB).GetTipo()==R.GetTipo()))
		return true;

	}
	return false;
}
int PALLET::PerdidaMayor(std::list<CRect> &listaP)
{
	int perdidaMayor=((double)((double)(m_L*m_W)/(double)(m_l*m_w))-(m_solbest+1))*(m_l*m_w);
	std::list<CRect>::iterator itB;
	int val=0;
	for(itB=listaP.begin();itB!=listaP.end();itB++)
	{
//		if ((((*itB).Width()>m_w) || ((*itB).Height()>m_w)) && !((*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH) && ((*itB).Height()*(*itB).Width()>(double)(perdidaMayor/2)))
		//Si hay pérdidas que son mas anchas que el ancho de una pieza este tipo de perdidas
		//no es el deseado
		if ((((*itB).Width()>m_w) || ((*itB).Height()>m_w)) && !((*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH) )
			val++;
		//No quiero perdidas con desperdidcio mayor del permitido
//		if (((*itB).Width()*(*itB).Height())>perdidaMayor)

	}
//	if (val==0) val=2;
	return val;
}
int PALLET::PerdidasPequenas(std::list<CRect> &listaP)
{
	std::list<CRect>::iterator itB;
	int val=0;
	double perdidaMayor=(double)((m_L*m_W)-((m_solbest+1)*m_l*m_w))/(double)4;
	for(itB=listaP.begin();itB!=listaP.end();itB++)
	{
//		if ((((*itB).Width()>m_w) || ((*itB).Height()>m_w)) && !((*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH) && ((*itB).Height()*(*itB).Width()>(double)(perdidaMayor/2)))
		//Si hay pérdidas que son mas anchas que el ancho de una pieza este tipo de perdidas
		//no es el deseado
//		if ((((*itB).Width()<m_w) && ((*itB).Height()<m_w)) && !((*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH) && (*itB).top!=0 && (*itB).left!=0 && (*itB).right!=m_L && (*itB).bottom!=m_W )
		//No quiero perdidas con desperdidcio mayor del permitido
		if (((*itB).Width()*(*itB).Height())>perdidaMayor)
			val++;

	}
	return ((val*10)/(listaP.size()));
}
int PALLET::PerdidaEnLados(std::list<CRect> &listaP)
{
	std::list<CRect>::iterator itB;
	int val=0;
	for(itB=listaP.begin();itB!=listaP.end();itB++)
	{
//		if ((((*itB).Width()>m_w) || ((*itB).Height()>m_w)) && !((*itB).Height()==m_G4_HuecoV && (*itB).Width()==m_G4_HuecoH) && ((*itB).Height()*(*itB).Width()>(double)(perdidaMayor/2)))
		if ((*itB).top==0 )
			val++;
		if ((*itB).left==0 )
			val++;
		if ((*itB).bottom==m_W)
			val++;
		if ((*itB).right==m_L)
			val++;

	}
//	if (val<2) val=0;
	return val;

}
void PALLET::ActualizarConjuntoReferencia(MOVE &M,int valor)
{
	PATHRE s;
	s.fobjetivo=valor;
	s.num_bloques=M.GetListaBloques().size();
	s.lista_bloques=M.GetListaBloques();
	s.lista_perdidas=M.GetListaPerdidas();
	std::list<pathre>::iterator itB;
	//Miro que no este repetida esta solución en el conjunto de referencia
	bool no_meter=false;
	for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end() && no_meter!=true;itB++)
	{
			if ((*itB).fobjetivo==s.fobjetivo && (*itB).num_bloques==s.num_bloques && (*itB).lista_bloques.size()==s.lista_bloques.size()) 
			{
				if (Lista_de_Perdidas_Iguales((*itB).lista_perdidas,s.lista_perdidas)==true)
					no_meter=true;
			}
	}
	if (no_meter==true) return;
	if (m_conjunto_ref.size()<(1000)) 
	{

		m_conjunto_ref.push_back(s);
		return;
	}
	int minim=MinimoConjuntoRef();
	if (minim>valor) return;
	//Quito el más pequeño
	bool stop=false;
	for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end() && stop!=true;itB++)
	{
			if ((*itB).fobjetivo==minim) 
			{
				if ((*itB).fobjetivo==s.fobjetivo && (*itB).num_bloques<s.num_bloques) 
				{
					itB=m_conjunto_ref.erase(itB);
					stop=true;
					break;
				}
				if ((*itB).fobjetivo<s.fobjetivo)
				{
					itB=m_conjunto_ref.erase(itB);
					stop=true;
					break;
				}
			}
	}
	//Si no he borrado no lo meto
	if (stop==true) m_conjunto_ref.push_back(s);
}
int PALLET::MinimoConjuntoRef(void)
{
	int min=9999999;
	std::list<pathre>::iterator itB;
	for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end();itB++)
	{
		if ((*itB).fobjetivo<min)
			min=(*itB).fobjetivo;
	}
	return min;
}
int PALLET::CombinarSolucionesConjuntoRef()
{
	int i=0;
	int j=0;
	int k=0;
	std::list<pathre>::iterator itB,itB2;
	for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end();itB++)
	{

		itB2=itB;
		i++;
		j=0;
		itB2++;
		if (itB2==m_conjunto_ref.end()) 
		{
			printf("Combinar %d\n", k);
			return 0;
		}
		for(;itB2!=m_conjunto_ref.end();itB2++)
		{
		j++;
		k++;
//		if (j!=15) continue;
//		printf("Fuera %d\n",j);
			
//			PATHRE aux=(*itB);
		//Voy de la solución que tiene menos bloques a la solución
		//que tiene más bloques
			int sol1;
			if ((*itB).lista_bloques.size()>(*itB2).lista_bloques.size())
			{
				sol1=CaminoDeAaB((*itB2),(*itB));
			}
			else sol1=CaminoDeAaB((*itB),(*itB2));

			if (sol1>m_solbest) 
			{
				DibujarSolucion((*itB).lista_bloques,(*itB).lista_perdidas,151,150);
				DibujarSolucion((*itB2).lista_bloques,(*itB2).lista_perdidas,151,150);
				return sol1;
			}
		}
	}
	return 0;
}
int PALLET::CaminoDeAaB(PATHRE A,PATHRE &B)
{
//Tengo que ir metiendo los bloques de la solución B
//en A e ir paletizando cada vez, los bloques de A si que puedo irlos moviendo
	std::list<BLOQUE>::iterator itB;
	//Si quiero hacer la solución simetrica
//	printf("kk");
	DibujarSolucion(A.lista_bloques,A.lista_perdidas,999,150);

	for (itB=A.lista_bloques.begin();itB!=A.lista_bloques.end();itB++)
	{
		int kk=(*itB).Width();
		(*itB).left=m_L-(*itB).left-(*itB).Width();
		(*itB).right=(*itB).left+kk;
		(*itB).SetPuedoMover(true);


	}
	DibujarSolucion(A.lista_bloques,A.lista_perdidas,888,150);
	DibujarSolucion(B.lista_bloques,B.lista_perdidas,777,151);
//	EscribirBloquesPantalla(A.lista_bloques);
	int i=0;
	//Para meter primero las de las esquinas.
	int cuenta=0,cuenta2=0;
	for (itB=B.lista_bloques.begin();itB!=B.lista_bloques.end();itB++)
	{
		//
		//                  -----------------------
		//                  | 3                  4|
		//                  |                     |
		//                  |                     |   
		//                  | 1                  2|
		//                  -----------------------
/*		if ((*itB).top==0 ) cuenta++;
		if ((*itB).right==m_L ) cuenta++;
		if ((*itB).bottom==m_W ) cuenta++;;
		if ((*itB).left==0 ) cuenta++;
		if (cuenta==cuenta2) continue;
		cuenta2=cuenta;
*/
  //		printf(" Meto Bloque %3d\t%3d\t%3d\t%3d\t%c\n",(*itB).top,(*itB).bottom,(*itB).left,(*itB).right,(*itB).GetTipo());
//		BLOQUE b1=(*itB);
		i++;
//		printf(" %d\n",i);
//		if (i==1) 
//			int perro=9;
		MeterBloqueSolucion((*itB),A.lista_bloques);
		(*itB).SetPuedoMover(false);
		A.lista_bloques.push_back((*itB));
		A.lista_perdidas.clear();
		CRect PTotal(0,0,m_L,m_W);
		A.lista_perdidas.push_back(PTotal);
		Actualizar_Perdida(A.lista_bloques,A.lista_perdidas);
		Bloques_Hacia_Las_Esquinas_Combinar(A.lista_bloques,A.lista_perdidas);
		A.lista_perdidas=JuntarPerdida(A.lista_perdidas,'X');
		CompactarPerdida(A.lista_perdidas);
		std::list<BLOQUE> lista=Paletizar(A.lista_perdidas,'X');
		A.lista_bloques.insert(A.lista_bloques.begin(),lista.begin(),lista.end());
		int cont=Contar(A.lista_bloques);
		DibujarSolucion(A.lista_bloques,A.lista_perdidas,cont,150);
		if (cont>m_solbest) 
		{
			VerificarSolucion(A.lista_bloques,A.lista_perdidas,1);
			m_solbest_lista_bloques=A.lista_bloques;
			m_solbest_lista_perdidas=A.lista_perdidas;
//			for (int j=1;j<88888;j++)
//			printf("Conseguido");
			return cont;
		}
	}
	return 0;

}
void PALLET::MeterBloqueSolucion(BLOQUE &B1,std::list<BLOQUE> &listaB)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	//Creo lista de pérdidas nuevas y lista de bloques nueva
	std::list<BLOQUE> lista_aux;
	for (itB=listaB.begin();itB!=listaB.end();itB++)
	{
//		BLOQUE b11=(*itB);
		//Los que esten incluidos dentro del nuevo rectángulo los quito
		if ((((*itB).bottom<=B1.bottom) && ((*itB).top>=B1.top))
		&& (((*itB).right<=B1.right) && ((*itB).left>=B1.left)))
			continue;
		if( (*itB).top>=B1.bottom || B1.top>=(*itB).bottom )
		{
			lista_aux.push_back((*itB));
			continue;
		}
		if( (*itB).left>=B1.right || B1.left>=(*itB).right)
		{
			lista_aux.push_back((*itB));
			continue;
		}

		//Solapa con el bloque nuevo
		//quitar el bloque y crear pérdidas
		cortar_Bloques((*itB),B1,lista_aux);
		

	}
	listaB=lista_aux;
}
void PALLET::cortar_Bloques(BLOQUE &b1,BLOQUE &b2,std::list<BLOQUE> &listaB)
{
	BLOQUE B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
	//Tengo cuatro casos
	//BottomRight cae dentro del anterior
//	CRect B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
	int corta=Restar_Rectangulo(b1,b2,B1,B2,B3,B4);
	//No se cortan
	if (corta!=0)
	{

		B1.SetTipo(b1.GetTipo());
		B2.SetTipo(b1.GetTipo());
		B3.SetTipo(b1.GetTipo());
		B4.SetTipo(b1.GetTipo());
		if (B1.IsRectEmpty()==0) listaB.push_back(B1);
		if (B2.IsRectEmpty()==0) listaB.push_back(B2);
		if (B3.IsRectEmpty()==0) listaB.push_back(B3);
		if (B4.IsRectEmpty()==0) listaB.push_back(B4);
	}

	
}
bool PALLET::CumpleNumHV(std::list<BLOQUE> &listaB)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	int sumH=0,sumV=0;
	for (itB=listaB.begin();itB!=listaB.end();itB++)
	{
		if ((*itB).GetTipo()=='H')
			sumH+=((*itB).Height()/m_w)*((*itB).Width()/m_l);
		if ((*itB).GetTipo()=='V')
			sumV+=((*itB).Height()/m_l)*((*itB).Width()/m_w);

	}

	if (sumH>=m_Hmin && sumH<=m_Hmax && sumV>=m_Vmin && sumV<=m_Vmax )
		return true;
	else return false;

}
//Cambiamos los diferentes valores de la búsqueda
void PALLET::OscilacionEstrategica(void)
{

	m_iter_sin_mejorar=0;
	m_valor_maximo=-50000;
	m_diversificaciones++;
//	NUEVO=70;
//	SIMETRIA=1000;
//	VALOROPTIMO=2500;
//	PERDIDALADOS=3000;
//	OPTIMO=400;
//	VALBLOQUES=0;
//	PERDIDAMAYOR=1000;
//	EFIBLOQUE=25;
	if (m_diversificaciones<=5)
	{
		PERDIDALADOS=3000-(600*m_diversificaciones);
	}
	else 
	{
		if (m_diversificaciones<=10)
		{
			m_F_Rectangulo=5000-(1000*(m_diversificaciones-5));
		}
		else
		{
					if (m_diversificaciones<=15)
					{
						PERDIDAMAYOR=1000-200*(m_diversificaciones-10);
					}
					else
					{
							if (m_diversificaciones<=20)
							{
								EFIBLOQUE=25-(5*(m_diversificaciones-15));

							}
							else
							{
								if (m_diversificaciones<=25)
								{
									OPTIMO=400-(80*(m_diversificaciones-20));
								}
								else
								{
									if (m_diversificaciones<=30)
									{
										EFICIENTES=1000-(300*(m_diversificaciones-25));
									}
								
								}
									
							}


					}


		}
	}
/*
	if (m_diversificaciones>=60)
	{
		//Hago todos los posibles movimientos
		m_Intensificar=true;

	}
	else
	{
		if (m_diversificaciones>=80)
		{
			//No se tienen en cuenta los raster points
			m_Raster=false;
			m_Intensificar=false;
		}
	}
			if (m_diversificaciones<=4)
			{
				//El criterio de perdida mayor lo hago desde el valor a -1000
				m_Raster=true;
//				PERDIDAMAYOR=1000-(m_diversificaciones-2)*500;
				VALOROPTIMO=2500/m_diversificaciones;
//				m_fijos=true;
			}
			else
			{
				if (m_diversificaciones<=6) 	
				{
					VALOROPTIMO=2500;
					m_fijos=false;
					//Tener un bloque eficiente ahora cuenta desde 400 a -100
					PERDIDAMAYOR=1000;
					EFIBLOQUE=1;
				}
				else 
				{
					if (m_diversificaciones<=7)
					{
						//Desde 3000 a -
						PERDIDALADOS=0;
						EFIBLOQUE=400;
					}
					else
					{
						if (m_diversificaciones<=8)
						{
							PERDIDALADOS=3000;
							//El rectangulo desde 5000 a -2000
//							m_F_Rectangulo=5000-(m_diversificaciones-16)*1000;
							m_F_Rectangulo=100;
//							m_fijos=false;
						}
						else
						{
							if (m_diversificaciones<=9)
							{
								//Que tenga todos los bloques eficientes desde
								// a-1000
								m_F_Rectangulo=5000;
								EFICIENTES=1;
							}
							else
							{
								if (m_diversificaciones<=10)
								{
									//No tengo en cuenta la simetria
									EFICIENTES=1500;
									m_Simetria=false;
									m_utilizar_frecuencias=true;
								}
								else
								{
									if (m_diversificaciones<=11)
									{
										m_Simetria=true;
										m_utilizar_frecuencias=false;
									}
									else
									{
										if (m_diversificaciones<=12)
										{
											m_todas=false;
										}
										else
										{
											if (m_diversificaciones<=13)
											{
												m_todas=true;

											}
											else
											{
												if (m_diversificaciones<=14)
												{
													m_tipo_rectangulo=5;
													m_tipo_junta=3;
												}
												else
												{
													m_tipo_junta=1;
													m_Eficientes=false;
												}

											}
										}
									}
								}
							}

						}
					}
			}
		}
*/			
	printf("Diversificar %d\t%d\t%d\t%d\t%d\t%d\n",m_diversificaciones,EFIBLOQUE,PERDIDALADOS,m_F_Rectangulo,EFICIENTES,m_iter_actual);

}
int PALLET::ParticionesGrandes(std::list<BLOQUE> &listaB)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	int maxL=0,maxW;
	if (m_hL>m_vL) maxL=m_hL;
	else maxL=m_vL;
	if (m_hW>m_vW) maxW=m_hW;
	else maxW=m_vW;
	int val=0;
	int l=0,w=0;
	for (itB=listaB.begin();itB!=listaB.end();itB++)
	{
		if ((*itB).GetTipo()=='H')
		{
			l=m_l;
			w=m_w;
		}
		else
		{
			l=m_w;
			w=m_l;
		}
		if (((*itB).Width()/l)==maxL) val++;
		if (((*itB).Height()/w)==maxW) val++;

	}
	return val;

}
bool PALLET::BloquesGrandes(std::list<BLOQUE> &listaB)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	for (itB=listaB.begin();itB!=listaB.end();itB++)
	{
		if ((((*itB).Width())>(m_L/3)) && (((*itB).Height())>(m_W/3)))
		 return true;
	}
	return false;

}
/*
bool MovimientoPosible()
{
	//Por Arriba o por abajo
	//Arriba
	if (tipo_movimiento==1)
	{
		if (PuedeDisminuirse((*itB),0,0,i,0,bloque_nulo)) return true;
	}
					//Abajo
	if (tipo_movimiento==2) 
	{
		if (PuedeDisminuirse((*itB),0,0,0,i,bloque_nulo)) return true;
	}
	//Arriba
	if (tipo_movimiento==3)
	{
		if (PuedeAumentarse((*itB),0,0,i,0)) return true;
	}
	//Abajo
	if (tipo_movimiento==4)
	{
		if (PuedeAumentarse((*itB),0,0,0,i)) return true;
	}
	//Por derecha o izquierda
	//derecha
	if (tipo_movimiento==5)
	{
		if (PuedeDisminuirse((*itB),i,0,0,0,bloque_nulo)) return true;
	}
	//izquierda
	if (tipo_movimiento==6)
	{
		if (PuedeDisminuirse((*itB),0,i,0,0,bloque_nulo)) return true;
	}
	//derecha
	if (tipo_movimiento==7)
	{
		if (PuedeAumentarse((*itB),i,0,0,0)) return true;
	}
	//izquierda
	if (tipo_movimiento==8)
	{
		if (PuedeAumentarse((*itB),0,i,0,0)) return true;
	}


}
MOVE & PALLET::HacerMovimiento()
{
						//Por Arriba o por abajo
					//Arriba
					if (tipo_movimiento==1)	Movimiento=(Disminuir_Bloques((*itB),0,0,i,0));
					//Abajo
					if (tipo_movimiento==2) Movimiento=(Disminuir_Bloques((*itB),0,0,0,i));
					//Arriba
					if (tipo_movimiento==3)	Movimiento=(Aumentar_Bloques((*itB),0,0,i,0));
					//Abajo
					if (tipo_movimiento==4) Movimiento=(Aumentar_Bloques((*itB),0,0,0,i));
					//Por derecha o izquierda
					//derecha
					if (tipo_movimiento==5) Movimiento=(Disminuir_Bloques((*itB),i,0,0,0));
					//izquierda
					if (tipo_movimiento==6)	Movimiento=(Disminuir_Bloques((*itB),0,i,0,0));
					//derecha
					if (tipo_movimiento==7) Movimiento=(Aumentar_Bloques((*itB),i,0,0,0));
					//izquierda
					if (tipo_movimiento==8) Movimiento=(Aumentar_Bloques((*itB),0,i,0,0));


}

bool PALLET::PuedeAumentarse(BLOQUE &B1,int tipo)
{
	//hasta que no llevo algunas iteraciones no meto este criterio
	if (m_iter_actual<10) return false;
	if (m_lista_GCuatros.size()<tipo) return false;
	//Quiero aumentar por el tipo determinado del G4
	//primera condición este en algún G4
	//Si tiene perdida por la derecha
	//Aumentar derecha arriba y derecha abajo
	//Si tiene perdida por la izquierda
	//Aumentar derecha izquierda y izquierda abajo
	//Si tiene perdida por la arriba
	//Aumentar derecha arriba y derecha abajo
	//Si tiene perdida por la abajo
	//Aumentar derecha arriba y derecha abajo
}
*/
bool PALLET::Es_un_huecoG4(int large,int wid)
{
//	std::list<strg4> ::iterator itg;
	std::vector<strg4> ::iterator itg;
	for (itg=m_lista_GCuatros.begin();itg!=m_lista_GCuatros.end() ;itg++)
	{
		if (((*itg).G4_HuecoH==large) && ((*itg).G4_HuecoV==wid))
			return true;
	}
	return false;

}