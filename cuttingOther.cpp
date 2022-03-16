#pragma warning (disable: 4786)
//#define TAM_TABU 21
//tipos.h
#include "Cutting.h"
#include "bouknap.cpp"
int espi=0;
int iter=0;
/*
//Si tienen el mismo valor la más grande
bool operator < (const Pieza& p1, const Pieza& p2)
{
	if ((double)p1.valor/(double)(p1.largo*p1.ancho)==(double)p2.valor/(double)(p2.largo*p2.ancho))
	{
		return (p1.largo*p1.ancho)>(p2.largo*p2.ancho);
	}
	else
	return (double)p1.valor/(double)(p1.largo*p1.ancho)>(double)p2.valor/(double)(p2.largo*p2.ancho);
}*/

//Orden por eficiencia
//Si tienen el mismo valor la más grande
bool operator < (const Pieza& p1, const Pieza& p2)
{
	//Si no son restringidas
	if ((p1.min*p1.valor)==(p2.min*p2.valor))
	{
		//Por la eficiencia
		if (((double)p1.valor/(double)(p1.largo*p1.ancho))==((double)p2.valor/(double)(p2.largo*p2.ancho)))
		{
			return (p1.largo*p1.ancho)>(p2.largo*p2.ancho);
			//(p1.largo*p1.ancho)>(p2.largo*p2.ancho);
		}
		else
			//Por el área de lo que puedo poner
		return ((double)p1.valor/(double)(p1.largo*p1.ancho))>((double)p2.valor/(double)(p2.largo*p2.ancho));//(p1.max*p1.largo*p1.ancho)>(p2.max*p2.largo*p2.ancho);
	}
	else
		return (p1.min*p1.valor)>(p2.min*p2.valor);
}
struct orden_no_posible
{
	bool operator() (const Pieza& p1, const Pieza& p2);
};
bool orden_no_posible::operator() (const Pieza& p1, const Pieza& p2){
	//Si no son restringidas
	if ((p1.min*p1.valor)==(p2.min*p2.valor))
	{
		//Por la eficiencia
		if (p1.valor*p1.max==p2.valor*p2.max)
		{
			return (p1.largo*p1.ancho)>(p2.largo*p2.ancho);
		}
		else
			//Por el área
		return p1.valor*p1.max>p2.valor*p2.max;
	}
	else
		return (p1.min*p1.valor)>(p2.min*p2.valor);

}

struct orden_strip
{
	bool operator() (const Pieza& p1, const Pieza& p2);
};
bool orden_strip::operator() (const Pieza& p1, const Pieza& p2){
	if (p1.ancho==p2.ancho)
			return (p1.largo)>(p2.largo);
			else
			return (p1.ancho)>(p2.ancho);
}
struct orden_strip2
{
	bool operator() (const Pieza& p1, const Pieza& p2);
};
bool orden_strip2::operator() (const Pieza& p1, const Pieza& p2){
	if (p1.largo==p2.largo)
			return (p1.ancho)>(p2.ancho);
			else
			return (p1.largo)>(p2.largo);
}
//CONSTRUCTOR DE UN TABLERO
CUTTING::CUTTING(int L,int W,int numpiezas)
{
	m_Restringido=false;
	m_ValSolucion=0;
	m_L=L;
	m_W=W;
	m_Numpiezas=numpiezas;
	m_Cota=0;
	m_Posible=true;
	m_solbest=0;
	m_MinAncho=0;
	m_MinLargo=0;
	m_FactorAleatorio=0;
	m_EmpiezaPorAqui=0;
	m_Determinista=false; //Si el heurístico es determinista o no

//	m_Nombre=name;
	//Particiones del lado X

}
CUTTING::CUTTING(char *nombre)
{
	m_solbest=0;
	m_HacerMejoraLocal=false;
	m_Restringido=false;
	m_ValSolucion=0;
	m_L=0;
	m_W=0;
	m_Numpiezas=0;
	m_Cota=0;
	m_Posible=true;
	strcpy(m_Nombre,nombre);
	m_FactorAleatorio=0;
	m_EmpiezaPorAqui=0;
	m_Determinista=false; //Si el heurístico es determinista o no

	//Particiones del lado X

}

void CUTTING::Clear()
{
	m_Restringido=false;
	m_ValSolucion=0;
	m_L=0;
	m_W=0;
	m_Numpiezas=0;
	m_Cota=0;
	m_factor=0;
//	strcpy(m_Nombre,"");
	m_Piezas.clear();
	m_lista_perdidas.clear();
	m_lista_bloques.clear();
	m_Posible=false;
	m_Determinista=false; //Si el heurístico es determinista o no


}
//Esta es para el CUTTING
void CUTTING::LeerProblema(char *name)
{
	int maxL=0;

	bool ProblemasHopper=false;
	bool ProblemasLodi=false;
	bool ProblemasHifi=false;
	m_conpesos=true;
	FILE *fin2;
	m_Q=0;
	m_total_valor=0;
	m_total_superficie=0;
	int Largop=0,Anchop=0,minp=0,maxp=0,valp=0,kk=0;
	fin2=fopen(name,"r+");
	if (fin2==NULL)
	{
		printf("Problemas al leer el archivo de problemas, no se encuentra el archivo");
		exit(4);
	}

	fscanf(fin2,"%d",&m_Numpiezas);
	if (m_Numpiezas>9000)
	{
		ProblemasHopper=true;
		m_Numpiezas=m_Numpiezas-9000;
	}
	if (m_Numpiezas==444)
	{
		ProblemasHifi=true;
	}
	fscanf(fin2,"%d %d",&m_L,&m_W);
	if (ProblemasHopper==true)
	{
		m_W=m_L;
		m_L=100000;
	}

	if (ProblemasHifi==true)
	{
		m_Numpiezas=m_W;
		m_W=m_L;
		m_L=100000;
	}
	if (m_W==1) 
	{
		ProblemasLodi=true;
		m_W=m_L;
		m_L=100000;
	}
	m_MinLargo=9999;
	m_MinAncho=9999;
	for (int i=0;i<m_Numpiezas;i++)
	{
		if (ProblemasHopper!=true && ProblemasLodi!=true && ProblemasHifi!=true)
		fscanf(fin2,"%d %d %d %d %d",&Largop,&Anchop,&minp,&maxp,&valp);
		else
		{
			if (ProblemasHopper==true)
			{
				fscanf(fin2,"%d %d",&Anchop,&Largop);
				minp=0;
				maxp=1;
				valp=Largop*Anchop;

			}
			if (ProblemasLodi==true)
			{
				fscanf(fin2,"%d %d %d",&Anchop,&Largop,&kk);
				minp=0;
				maxp=1;
				valp=Largop*Anchop;

			}
			if (ProblemasHifi==true)
			{
				fscanf(fin2,"%d %d %d",&Largop,&Anchop,&maxp);
				minp=0;
				valp=Largop*Anchop;

			}
		}
		//Si alguna pieza es obligatoria
		//tenemos un problema restringido
		if (minp>0)
		{
			m_Restringido=true;
			m_Posible=false;
		}
		m_Q+=maxp;
		if (Largop<m_MinLargo) m_MinLargo=Largop;
		if (Anchop<m_MinAncho) m_MinAncho=Anchop;
		/*
		//buscar si hay una pieza igual
		std::vector<Pieza> ::iterator ITP;
		bool existe=false;
		for (ITP=m_Piezas.begin();ITP!=m_Piezas.end();ITP++)
		{
			if ((*ITP).largo==Largop && (*ITP).ancho==Anchop)
			{
				existe=true;
				(*ITP).max=(*ITP).max+maxp;
			}
		}
		if (existe!=true)
		{
			Pieza p={Largop,Anchop,minp,maxp,valp,0};
			m_Piezas.push_back(p);
		}
		*/
		Pieza p={Largop,Anchop,minp,maxp,valp,0,0};
		m_Piezas.push_back(p);
		m_total_valor+=valp*maxp;
		m_total_superficie+=Largop*Anchop*maxp;
		maxL+=__max(Largop,Anchop)*maxp;



	}

	fclose(fin2);

	if (m_L==100000) m_L=maxL;
	m_Numpiezas=m_Piezas.size();
	//Ordeno las piezas por su eficiencia
//	if (m_Posible!=false)
	if (ProblemasLodi!=true && ProblemasHifi!=true)
	std::sort(m_Piezas.begin(),m_Piezas.end());
	else
	std::sort(m_Piezas.begin(),m_Piezas.end(),orden_strip());
//	std::sort(m_Piezas.begin(),m_Piezas.end(),orden_strip2());
//	JuntarPiezasIguales();

	if (((double)m_Piezas[0].valor/(double)(m_Piezas[0].ancho*m_Piezas[0].largo))==((double)m_Piezas[m_Numpiezas-1].valor/(double)(m_Piezas[m_Numpiezas-1].ancho*m_Piezas[m_Numpiezas-1].largo)))
		m_conpesos=false;
	if (m_total_superficie>(m_L*m_W))  
		m_conpesos=true;
//	CotaSuperior();
//	else
//	std::sort(m_Piezas.begin(),m_Piezas.end(),orden_no_posible());
//	EscribirPiezas();
}
void CUTTING::JuntarPiezasIguales()
{
	bool juntar=false;
	do{
		juntar=false;
	for (register int i=0;juntar!=true && i<m_Numpiezas-1;i++)
	{
		//Juntar piezas iguales
		if (m_Piezas[i].ancho==m_Piezas[i+1].ancho && m_Piezas[i].largo==m_Piezas[i+1].largo)
		{
			m_Piezas[i].max+=m_Piezas[i+1].max;
			juntar=true;
			m_Numpiezas--;
			m_Piezas.erase(&m_Piezas[i+1]);
			
		}
		
	}
	}
	while(juntar==true);

}
//Elije meter la que mejor función objetivo otorgue en caso de empate, 
//mete la que ocupe menor espacio
//Otra posibilidad es que meta la mas valiosa respecto el espacio
	//*********
	//Tipo 1 es elegir meter la más valiosa 
	//************
	//Tipo 2 es elegir meter la mejor para la función objetivo
	//*************
	//Tipo 3 es aleatoriamente aplicar tipo 1 o tipo 2
void CUTTING::ElegirPiezaStrip(BLOQUE &b1,RECTAN &Rect, int tipo,int num)
{
	if ((m_MinLargo>Rect.Width() || m_MinAncho>Rect.Height()) ) return ;

	//Si tenemos un problema restringido al principio
	//voy metiendo solo las obligatorias
	//una vez hecho esto ya continuo
	double max=-9999;
	int numero=0;
	bool necesaria=false,necesaria2=false;
//	if (tipo==5) tipo=get_random(1,2);
//		Ahora si puedo meter esta meto esta
	if (num!=99999)
	{
			
		if (m_PuedenRotarsePiezas==false && m_Piezas[num].largo<=Rect.Width() && m_Piezas[num].ancho<=Rect.Height())
		{
			b1.bottom=m_Piezas[num].ancho;
			b1.right=m_Piezas[num].largo;
			b1.SetNumero(num);
			m_Piezas[b1.GetNumero()].num+=1;
			return;

		}
		//Si se pueden rotar las piezas
		if (m_PuedenRotarsePiezas==true &&  ((m_Piezas[num].largo<=Rect.Width() && m_Piezas[num].ancho<=Rect.Height())|| (m_Piezas[num].ancho<=Rect.Width() && m_Piezas[num].largo<=Rect.Height())))
		{
			if (m_Piezas[num].ancho>m_Piezas[num].largo)
			{
				b1.right=m_Piezas[num].ancho;
				b1.bottom=m_Piezas[num].largo;
			}
			else
			{
				b1.bottom=m_Piezas[num].ancho;
				b1.right=m_Piezas[num].largo;

			}
			b1.SetNumero(num);
			m_Piezas[b1.GetNumero()].num+=1;
			return;

		}
	}
	//Las recorro todas las que se pueden
	for (int i=0;i<m_Numpiezas;i++)
	{
//		Cambio 
//		if (i==num) continue;
//		Ahora si puedo meter esta meto esta
		//Si puede elegir esa pieza
		if (m_Piezas[i].num>=m_Piezas[i].max) continue;
		bool basta=false;
//		for (int j=1;j<=(m_Piezas[i].max-m_Piezas[i].num) && basta!=true;j++)
		for (int j=1;j<=1 && basta!=true;j++)
		{
			//Esta variable me dice si ya no caben más de j
			basta=true;
/*
			//Si puedo poner todas esas piezas en horizontal
			if (m_Piezas[i].largo*j<=Rect.Width() && m_Piezas[i].ancho<=Rect.Height())
			{
				if ((val>max || (val==max && (((m_Piezas[i].largo)>(b1.Width())))) && tipo==3) || 
					(((val>max || (val==max && (((m_Piezas[i].largo*j)*(m_Piezas[i].ancho))>(b1.bottom*b1.right)))) && tipo==1) || 
					((val>max || (val==max && (((m_Piezas[i].largo*j)*(m_Piezas[i].ancho))<(b1.bottom*b1.right)))) && (tipo==2))) ||
					(necesaria==true && necesaria2==false))				
				{
					b1.bottom=m_Piezas[i].ancho;
					b1.right=m_Piezas[i].largo*j;
					b1.SetNumero(i);
					max=val;
					numero=j;
					//Si es necesaria meterla por las restricciones
					necesaria2=necesaria;
				}
				basta=false;
			}
			if (j==1) continue;*/
			//Si puedo poner todas esas piezas en vertical
			if (m_Piezas[i].largo<=Rect.Width() && m_Piezas[i].ancho*j<=Rect.Height())
			{
				//Valor de meter esta pieza
				double val=0;
				//La más ancha
				if (tipo==1) val=m_Piezas[i].ancho*j;
				//La más ancha con algo de lo largo
				if (tipo==2) val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.01;
				//La más ancha con algo de lo largo
				if (tipo==3) val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.1;
				//La más ancha con algo de lo largo
				if (tipo==4) val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.5;
				if (tipo==7) val=m_Piezas[i].ancho*j-m_Piezas[i].largo*0.01;
				int a1=0,a2=0;
				//Para estudiar cual es mejor
				if (m_tipo==5 && Rect.top!=0 && Rect.bottom!=m_W) 
				{
					//altura por abajo
					a1=Altura(Rect.top,0);
					//altura por arriba
					a2=Altura(Rect.bottom,1);
				}

				//La que mejor se acopla
				if (tipo==5) 
				{
					val=m_Piezas[i].ancho*j;
					if (Rect.Height()-m_Piezas[i].ancho<m_MinAncho && Rect.Height()-m_Piezas[i].ancho>0 && (Rect.Height()-m_Piezas[i].ancho)*m_Piezas[i].largo>m_perdida_menor)
						val=0.01;
					if (m_Piezas[i].largo==a1 || m_Piezas[i].largo==a2)	
						val+=m_Piezas[i].largo;
					if (m_Piezas[i].largo>__max(a1,a2)) val-=m_Piezas[i].largo*0.01;
					if (Rect.Height()-m_Piezas[i].ancho<m_MinAncho && Rect.Height()-m_Piezas[i].ancho>0)
						val=val/2;

				}

				//Si es necesaria meterla por las restricciones
				if (m_Piezas[i].min>=(m_Piezas[i].num+j)) 
					necesaria=true;
				else
					necesaria=false;
				//Si tengo una que es necesaria y la que voy a explorar no, seguir
				if (necesaria2==true && necesaria==false) continue;
				if ((val>max || (val==max && (((m_Piezas[i].largo)>(b1.Width())))) && tipo==3) || 
					(((val>max || (val==max && (((m_Piezas[i].largo*j)*(m_Piezas[i].ancho))>(b1.bottom*b1.right)))) && tipo==1) || 
					((val>max || (val==max && (((m_Piezas[i].largo*j)*(m_Piezas[i].ancho))<(b1.bottom*b1.right)))) && (tipo==2))) ||
					(necesaria==true && necesaria2==false))				
				{
					b1.bottom=m_Piezas[i].ancho*j;
					b1.right=m_Piezas[i].largo;
					b1.SetNumero(i);
					max=val;
					numero=j;
					//Si es necesaria meterla por las restricciones
					necesaria2=necesaria;
				}
				basta=false;
			}
			if (m_PuedenRotarsePiezas==true)
			{
				basta=false;
				if (m_Piezas[i].ancho<=Rect.Width() && m_Piezas[i].largo*j<=Rect.Height())
				{
					//Valor de meter esta pieza
					double val=0;
					//La más ancha
					if (tipo==1) val=m_Piezas[i].largo*j;
					//La más ancha con algo de lo largo
					if (tipo==2) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.01;
					//La más ancha con algo de lo largo
					if (tipo==3) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.1;
					//La más ancha con algo de lo largo
					if (tipo==4) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.5;
					if (tipo==7) val=m_Piezas[i].largo*j-m_Piezas[i].ancho*0.01;

					//Si es necesaria meterla por las restricciones
					if (m_Piezas[i].min>=(m_Piezas[i].num+j)) 
						necesaria=true;
					else
						necesaria=false;
					//Si tengo una que es necesaria y la que voy a explorar no, seguir
					if (necesaria2==true && necesaria==false) continue;
					if ((val>max || (val==max && (((m_Piezas[i].ancho)>(b1.Width())))) && tipo==3) || 
						(((val>max || (val==max && (((m_Piezas[i].ancho*j)*(m_Piezas[i].largo))>(b1.bottom*b1.right)))) && tipo==1) || 
						((val>max || (val==max && (((m_Piezas[i].ancho*j)*(m_Piezas[i].largo))<(b1.bottom*b1.right)))) && (tipo==2))) ||
						(necesaria==true && necesaria2==false))				
						{
							b1.bottom=m_Piezas[i].largo*j;
							b1.right=m_Piezas[i].ancho;
							b1.SetNumero(i);
							max=val;
							numero=j;
							//Si es necesaria meterla por las restricciones
						necesaria2=necesaria;
						}
					basta=false;
				}
			}
		}
	}
	m_Piezas[b1.GetNumero()].num+=numero;
}
void CUTTING::CotaSuperior()
{
	//Tengo que mandarle el numpiezas
	int c=m_L*m_W;
	int ctefobj=0,cota;
	int max=0,todas=0;
	int *profit=(int *)calloc(m_Numpiezas,sizeof(int));
	int *weight=(int *)calloc(m_Numpiezas,sizeof(int));
	int *m=(int *)calloc(m_Numpiezas,sizeof(int));
	int *x=(int *)calloc(m_Numpiezas,sizeof(int));
	for (int i=0;i<m_Numpiezas;i++)
	{
		profit[i]=m_Piezas[i].valor;
		weight[i]=m_Piezas[i].largo*m_Piezas[i].ancho;
		m[i]=m_Piezas[i].max-m_Piezas[i].min;
		//maximo es lo ocupan todas las piezas
		max+=m[i]*m_Piezas[i].largo*m_Piezas[i].ancho;
		//El valor de todas las piezas
		todas+=m_Piezas[i].valor*m[i];
		//Si no es obligatoria en la función objetivo
		if (m_Piezas[i].min>0)
		{
			c-=(m_Piezas[i].largo*m_Piezas[i].ancho)*m_Piezas[i].min;
			ctefobj+=m_Piezas[i].valor*m_Piezas[i].min;
		}
	}
	//Si no puede meter todas las piezas en la mochila
	if (max> c) cota=bouknap(m_Numpiezas,profit,weight,m,x,c);
	//si  puedo las meto todas
	else cota=todas;

	m_Cota=cota+ctefobj;
	printf("Todo %d Cota %d Fijo %d\n",cota+ctefobj,cota,ctefobj);
}
int CUTTING::CotaSuperiorArea()
{
	//Tengo que mandarle el numpiezas
	int c=m_L*m_W;
	int ctefobj=0,cota;
	int max=0,todas=0;
	int *profit=(int *)calloc(m_Numpiezas,sizeof(int));
	int *weight=(int *)calloc(m_Numpiezas,sizeof(int));
	int *m=(int *)calloc(m_Numpiezas,sizeof(int));
	int *x=(int *)calloc(m_Numpiezas,sizeof(int));
	for (int i=0;i<m_Numpiezas;i++)
	{
		profit[i]=m_Piezas[i].largo*m_Piezas[i].ancho;
		weight[i]=m_Piezas[i].largo*m_Piezas[i].ancho;
		m[i]=m_Piezas[i].max-m_Piezas[i].min;
		//maximo es lo ocupan todas las piezas
		max+=m[i]*m_Piezas[i].largo*m_Piezas[i].ancho;
		//El valor de todas las piezas
		todas+=m_Piezas[i].valor*m[i];
		//Si no es obligatoria en la función objetivo
		if (m_Piezas[i].min>0)
		{
			c-=(m_Piezas[i].largo*m_Piezas[i].ancho)*m_Piezas[i].min;
			ctefobj+=m_Piezas[i].valor*m_Piezas[i].min;
		}
	}
	//Si no puede meter todas las piezas en la mochila
	if (max> c) cota=bouknap(m_Numpiezas,profit,weight,m,x,c);
	//si  puedo las meto todas
	else cota=todas;

	return cota+ctefobj;
//	printf("Todo %d Cota %d Fijo %d\n",cota+ctefobj,cota,ctefobj);
}
//Elegir Pieza con algo de aleatoriedad 
void CUTTING::ElegirPiezaAleatoriaStrip(BLOQUE &b1,RECTAN &Rect, int tipo,int num)
{
	//Si no cabe ningun rectangulo salir
	if ((m_MinLargo>Rect.Width() || m_MinAncho>Rect.Height()) ) return ;
	std::vector< std::pair<double, candi > > lista_candidatos;
	double suma=0;
	//Si tenemos un problema restringido al principio
	//voy metiendo solo las obligatorias
	//una vez hecho esto ya continuo
	double max=0,min=99999;
	int numero=0;
	bool necesaria=false,necesaria2=false;
	if (tipo==5) tipo=get_random(1,2);
//		Ahora si puedo meter esta meto esta
	if (num!=99999)
	{
			
		if (m_PuedenRotarsePiezas==false && m_Piezas[num].largo<=Rect.Width() && m_Piezas[num].ancho<=Rect.Height())
		{
			b1.bottom=m_Piezas[num].ancho;
			b1.right=m_Piezas[num].largo;
			b1.SetNumero(num);
			m_Piezas[b1.GetNumero()].num+=1;
			return;

		}
		//Si se pueden rotar las piezas
		if (m_PuedenRotarsePiezas==true &&  ((m_Piezas[num].largo<=Rect.Width() && m_Piezas[num].ancho<=Rect.Height())|| (m_Piezas[num].ancho<=Rect.Width() && m_Piezas[num].largo<=Rect.Height())))
		{
			if (m_Piezas[num].ancho>m_Piezas[num].largo)
			{
				b1.right=m_Piezas[num].ancho;
				b1.bottom=m_Piezas[num].largo;
			}
			else
			{
				b1.bottom=m_Piezas[num].ancho;
				b1.right=m_Piezas[num].largo;

			}
			b1.SetNumero(num);
			m_Piezas[b1.GetNumero()].num+=1;
			return;

		}
	}

	int a1=0,a2=0;
	//Para estudiar cual es mejor
	if (m_tipo==5 && Rect.top!=0 && Rect.bottom!=m_W) 
	{
		//altura por abajo
		a1=Altura(Rect.top,0);
		//altura por arriba
		a2=Altura(Rect.bottom,1);
	}
	//Las recorro todas las que se pueden
	for (int i=0;i<m_Numpiezas;i++)
	{
		if (i==num) continue;
		//Si puede elegir esa pieza
		if (m_Piezas[i].num>=m_Piezas[i].max) continue;
		bool basta=false;
		for (int j=1;j<=(m_Piezas[i].max-m_Piezas[i].num) && basta!=true;j++)
//		for (int j=1;j<=1 && basta!=true;j++)
		{
//			if (j>1) continue;

			//Esta variable me dice si ya no caben más de j
			basta=true;
			//Valor de meter esta pieza
			double val=0;
			//Si puedo poner todas esas piezas en horizontal
/*			if (m_Piezas[i].largo*j<=Rect.Width() && m_Piezas[i].ancho<=Rect.Height())
			{
				if (val>max) max=val;
				suma+=val;
				numero=j;
				candi c={j,i,'H'};
				std::pair<double, candi > p(val,c);
				lista_candidatos.push_back(p);
				//Si es necesaria meterla por las restricciones
				necesaria2=necesaria;
				basta=false;
			}
			if (j==1) continue;
*/			//Si puedo poner todas esas piezas en vertical
//			if ((lista_candidatos.size()>0)  && ((Rect.Height()-m_Piezas[i].ancho)<m_MinAncho))
//				continue;
//			if  (j>1 && ((m_Piezas[i].largo*m_Piezas[i].ancho)<(m_total_superficie/30)))
//				continue;
//			if (j>1) continue;
			if ((m_Piezas[i].ancho*j<=Rect.Height()) && (m_Piezas[i].largo<=Rect.Width()))
			{
			//La más larga
//				if (tipo==2) val=m_Piezas[i].largo*j;

				//La más ancha
				if (tipo==1) val=m_Piezas[i].ancho*j;
				//La más ancha con algo de lo largo
				if (tipo==2) 
				{
					val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.01;
//					if (Rect.Height()-m_Piezas[i].ancho<m_MinAncho)
//					{
//						if ((Rect.Height()-m_Piezas[i].ancho)>m_perdida_menor)
//							val=0;
//					}
				}
				//La más ancha con algo de lo largo
				if (tipo==3) val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.1;
				//La más ancha con algo de lo largo
				if (tipo==4) val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.5;
				
				//La que mejor se acopla
				if (tipo==5) 
				{
					val=m_Piezas[i].ancho*j;
					if (Rect.Height()-m_Piezas[i].ancho<m_MinAncho && Rect.Height()-m_Piezas[i].ancho>0 && (Rect.Height()-m_Piezas[i].ancho)*m_Piezas[i].largo>m_perdida_menor)
						val=0.01;
					if (m_Piezas[i].largo==a1 || m_Piezas[i].largo==a2)	
						val+=m_Piezas[i].largo;
					if (m_Piezas[i].largo>__max(a1,a2)) val-=m_Piezas[i].largo*0.01;
					if (Rect.Height()-m_Piezas[i].ancho<m_MinAncho && Rect.Height()-m_Piezas[i].ancho>0)
						val=val/2;

				}
				if (tipo==0)
					val=m_Piezas[i].ancho*j+m_Piezas[i].largo*((double)get_random(1,100)/(double)200);

				//Solo para cuando las piezas se pueden rotar
				if (tipo==6) val=__min(m_Piezas[i].largo*j+m_Piezas[i].ancho*0.01,m_Piezas[i].ancho*j+m_Piezas[i].largo*0.01);
				if (tipo==7) val=m_Piezas[i].ancho*j-m_Piezas[i].largo*0.01;
				//La más ancha con algo de lo largo
				//Si es necesaria meterla por las restricciones
				if (m_Piezas[i].min>=(m_Piezas[i].num+j)) 
					necesaria=true;
				else
					necesaria=false;
				//Si tengo que no es posible solo quiero necesarias
				if (m_Posible==false && necesaria==false)  continue;

				if (val>max) max=val;
				if (val<min) min=val;

				suma+=val;
				numero=j;
				candi c={j,i,'V'};
				std::pair<double, candi > p(val,c);
				lista_candidatos.push_back(p);
				//Si es necesaria meterla por las restricciones
				necesaria2=necesaria;
				basta=false;
			}
			if (m_PuedenRotarsePiezas==true )
			{
				//Esta variable esta puesta ya que al estar ordenados si no entra una 
				//ya no hay que seguir

				basta=false;
				if (m_Piezas[i].largo*j<=Rect.Height() && m_Piezas[i].ancho<=Rect.Width())
				{
					//La más ancha
					if (tipo==1) val=m_Piezas[i].largo*j;
					//La más ancha con algo de lo largo
					if (tipo==2) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.01;
					//La más ancha con algo de lo largo
					if (tipo==3) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.1;
					//La más ancha con algo de lo largo
					if (tipo==4) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.5;
					//La que mejor se acopla
					if (tipo==5) 
					{
						val=m_Piezas[i].largo*j;
						if (m_Piezas[i].ancho==a1 || m_Piezas[i].ancho==a2)	
							val+=m_Piezas[i].ancho*0.01;
						if (m_Piezas[i].ancho>__max(a1,a2)) val-=m_Piezas[i].ancho*0.01;
					}
					//El mínimo de los dos solo para problemas en los que si se puede rotar
					if (tipo==6) val=__min(m_Piezas[i].largo*j+m_Piezas[i].ancho*0.01,m_Piezas[i].ancho*j+m_Piezas[i].largo*0.01);
					if (tipo==7) val=m_Piezas[i].largo*j-m_Piezas[i].ancho*0.01;

					//Si es necesaria meterla por las restricciones
					if (m_Piezas[i].min>=(m_Piezas[i].num+j)) 
						necesaria=true;
					else
						necesaria=false;
					//Si tengo que no es posible solo quiero necesarias
					if (m_Posible==false && necesaria==false)  continue;

					if (val>max) max=val;
					if (val<min) min=val;
	
					suma+=val;
					numero=j;
					candi c={j,i,'H'};
					std::pair<double, candi > p(val,c);
					lista_candidatos.push_back(p);
					//Si es necesaria meterla por las restricciones
					necesaria2=necesaria;
					basta=false;
				}

			}


			if (j==1) continue;

			//Si j es par y es mayyor que 2
			//Puedo meterlas de otras manera por ejemplo
			//en un 2x2 o 3X2 etc..
			if (j>2 && j%2==0 && basta!=false) 
			{
				//
				int alto=Rect.Height()/m_Piezas[i].ancho;
				if (alto>1) 
				{
					if ((j/alto>1) && (j/alto)<=(Rect.Width()/m_Piezas[i].largo))
					{
//						int kk=m_Piezas[i].ancho;
//						int kk2=m_Piezas[i].largo;
						if (val>max) max=val;
						if (val<min) min=val;
						suma+=val;

						numero=j;
						candi c={j,i,'A'};
						std::pair<double, candi > p(val,c);
						lista_candidatos.push_back(p);
						//Si es necesaria meterla por las restricciones
						necesaria2=necesaria;
						basta=false;
					}
					
				}
			}
			if (m_PuedenRotarsePiezas==true && j>2 && j%2==0 && basta!=false) 
			{
				//
				int alto=Rect.Height()/m_Piezas[i].largo;
				if (alto>1) 
				{
					if ((j/alto>1) && (j/alto)<=(Rect.Width()/m_Piezas[i].ancho))
					{
//						int kk=m_Piezas[i].ancho;
//						int kk2=m_Piezas[i].largo;
						if (val>max) max=val;
						if (val<min) min=val;
						suma+=val;

						numero=j;
						candi c={j,i,'A'};
						std::pair<double, candi > p(val,c);
						lista_candidatos.push_back(p);
						//Si es necesaria meterla por las restricciones
						necesaria2=necesaria;
						basta=false;
					}
					
				}
			}
		}
	}
	if (lista_candidatos.size()==0) return;
	int elegido=0;
//	m_tipo_de_lista=get_random(2,4);
//	if (m_tipo_de_lista==3) m_tipo_de_lista=4;
	//Elijo de los posibles con un tanto por ciento 
	if (m_tipo_de_lista==1) elegido=ElegirAleatorioPorCiento(lista_candidatos);
	//Elije de los posibles que este entre max y (1-FAleatorio)*max
	if (m_tipo_de_lista==2)  elegido=ElegirAleatorioPorValor(lista_candidatos,m_FactorAleatorio*max);
	//elige dandole probabilidad dependiendo del valr
	if (m_tipo_de_lista==3) elegido=ElegirAleatorioPorProbabilidad(lista_candidatos,suma);
	//Elije de los posibles que este entre min+(1-FAleatorio)*(max-min)
	if (m_tipo_de_lista==4)  elegido=ElegirAleatorioPorValor(lista_candidatos,min+m_FactorAleatorio*(max-min));
	//Elijo uno del  tengo que poner lo que hago
	//tamaño cuando le paso val cuanto vale
	m_Piezas[lista_candidatos[elegido].second.nump].num+=lista_candidatos[elegido].second.numero;
	b1.SetNumero(lista_candidatos[elegido].second.nump);
	if (lista_candidatos[elegido].second.orienta=='H')
	{
		b1.right=m_Piezas[lista_candidatos[elegido].second.nump].ancho;
		b1.bottom=m_Piezas[lista_candidatos[elegido].second.nump].largo*lista_candidatos[elegido].second.numero;
	}
	if (lista_candidatos[elegido].second.orienta=='V')
	{
		b1.right=m_Piezas[lista_candidatos[elegido].second.nump].largo;
		b1.bottom=m_Piezas[lista_candidatos[elegido].second.nump].ancho*lista_candidatos[elegido].second.numero;
	}
	if (lista_candidatos[elegido].second.orienta=='A')
	{
//		int kk=m_Piezas[lista_candidatos[elegido].second.nump].ancho;
//		int kk2=m_Piezas[lista_candidatos[elegido].second.nump].largo;
		int alto=Rect.Height()/m_Piezas[lista_candidatos[elegido].second.nump].ancho;
		int ancho=lista_candidatos[elegido].second.numero/alto;
		b1.right=m_Piezas[lista_candidatos[elegido].second.nump].largo*ancho;
		b1.bottom=m_Piezas[lista_candidatos[elegido].second.nump].ancho*alto;
//		lista_candidatos[elegido].second.numero
	}

}
//Compactamos un bloque que hemos creado nuevo
void CUTTING::CompactarBloques(MOVE &M1)
{
//	return;
	bool compacta=false;
	std::list<BLOQUE>::iterator itL,itL2,itL3;
	std::list<BLOQUE> lista;
	std::list<BLOQUE> listaB;

	compacta=false;	
	listaB.insert(listaB.end(),M1.GetListaBloques().begin(),M1.GetListaBloques().end());

	//Compacto hasta 4 veces
	int cuenta=0;
	do{
		cuenta++;
		itL=listaB.begin();
		do{

			itL3=itL;
			itL3++;
			if (itL3==listaB.end()) break;
			compacta=false;
			itL2=itL3;
			do{
				if ((*itL).GetNumero()!=(*itL2).GetNumero())
				{
					itL2++;
					continue;
				}

				if (((*itL).BottomRight()==(*itL2).BottomRight()) &&
				((*itL).TopLeft()==(*itL2).TopLeft()) && ((*itL).GetNumero()==(*itL2).GetNumero()) )
				{
					itL2++;
					continue;
				}
/*				if ((*itL).GetTipo()!=(*itL2).GetTipo())
				{
					itL2++;
					continue;
				}
*/				bool mayor=false;
			
				//si no tienen el mismo area pero existe una perdida que si
				//lo tenga 
				//Primera condición esten a la misma altura
				//muevo las piezas a una partición eficiente
				RECTAN RectTemp,RectTemp1;
				if (((*itL).top==(*itL2).top) && ((*itL).bottom==(*itL2).bottom) && mayor==false)
				{
					//si tienen el mismo area que la unión de ambos
					UnionRect(&RectTemp,&(*itL),(*itL2));
					if ((((*itL).left==(*itL2).right) || ((*itL2).left==(*itL).right)) && mayor==false)
					{

						BLOQUE b(RectTemp,(*itL2).GetTipo());
						b.SetNumero((*itL).GetNumero());
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
						RECTAN perdida;
						perdida.top=(*itL).TopLeft().y;
						perdida.bottom=(*itL).BottomRight().y;
						if ((*itL).right>(*itL2).right)
						{
							perdida.left=(*itL2).left;
							RectTemp.right=(*itL).right;
							perdida.right=perdida.left+diferencia;
							RectTemp.left=perdida.right;
						}
						else
						{
							perdida.left=(*itL).left;
							RectTemp.right=(*itL2).right;
							perdida.right=perdida.left+diferencia;
							RectTemp.left=perdida.right;
						}
						M1.GetListaPerdidas().push_back(perdida);
						BLOQUE b(RectTemp,(*itL2).GetTipo());
						b.SetNumero((*itL).GetNumero());

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
						b.SetNumero((*itL).GetNumero());

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
						RECTAN perdida;
						perdida.left=(*itL).TopLeft().x;
						perdida.right=(*itL).BottomRight().x;
						if ((*itL).bottom>(*itL2).bottom)
						{
							perdida.top=(*itL2).top;
							RectTemp.bottom=(*itL).bottom;
							perdida.bottom=perdida.top+diferencia;
							RectTemp.top=perdida.bottom;	
						}
						else
						{
							perdida.top=(*itL).top;
							RectTemp.bottom=(*itL2).bottom;
							perdida.bottom=perdida.top+diferencia;
							RectTemp.top=perdida.bottom;	
						}
						M1.GetListaPerdidas().push_back(perdida);
						BLOQUE b(RectTemp,(*itL2).GetTipo());
						b.SetNumero((*itL).GetNumero());

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

int CUTTING::Tabu2DStrip(bool dibu,bool sol_grasp)
{
	m_empieza_sol_grasp=sol_grasp;
	m_tipo=2;
	if (m_empieza_sol_grasp==false)
	{
		SetDeterminista(true);
		HeuristicoGreedyOrdenStrip(dibu);
		m_solbest=m_ValSolucion;
	}
	else
	{
		SetDeterminista(false);
//		int sol=GraspStrip(false);
	}
	if (m_solbest==0) m_solbest=m_ValSolucion;
	m_Cota=CotaInferiorArchivoStrip();
	if (m_Cota==0)
	m_Cota=__max(ceil((double)m_total_superficie/(double)m_W),m_MaxLargo);
	//Limpio lo conseguido con el heurístico
	for (register int j=0;j<m_Numpiezas;j++)
		m_Piezas[j].num=0;
	ActualizarMinMax();
//	m_solbest=m_ValSolucion;
	int limite_superior=m_solbest-1;
	int limite_inferior=m_Cota;
	int solucion=m_solbest;
	while (limite_inferior<=limite_superior)
	{
		int mitad=(limite_inferior+limite_superior)/2;
		m_L=mitad;
		printf("Buscando Solucion de %d\n",mitad);
		m_empieza_sol_grasp=false;
		int solu=Tabu(dibu);
		if (solu==m_total_superficie)
		{
			solucion=mitad;
			limite_superior=mitad-1;
		}
		else
		{
			limite_inferior=mitad+1;
		}
	}
	m_solbest=solucion;
	
	return m_solbest;
}

int CUTTING::Tabu(bool dibu)
{
	m_iter_solbest=0;
	//El algorimo tabu los vecinos son soluciones con alguna nueva pieza colocada
	//Voy quitando piezas y colocando nuevas 
	//Lo primero tener una solución inicial
	//preprocessing
	m_PathRelinking=false;
	m_noquiero=999999;
	m_Cota=CotaSuperiorArchivo();
	if (m_Cota==0)
		m_Cota=CotaSuperiorArea();
	m_totalmov=0;
	m_movtabu=0;

	m_iter_sin_mejorar=0;
	bool movdismi=false;
	bool movaumen=false;
	bool mejora=true;
	m_Determinista=true;
	srand(1);
	m_movdismi=0;
	m_movaumen=0;
	m_hechomovdismi=0;
	m_hechomovaumen=0;
	BorrarFrecuencias();

	if (m_empieza_sol_grasp==false)
	HeuristicoGreedyOrden(dibu);
	//Para que empieze con la mejor solución encontrada en el Grasp

/*	for (;mejora==true;)
	{
		mejora=false;
		HeuristicoGreedy(dibu);
		int sol=ContarSolucion(m_lista_bloques);
		if (sol>m_solbest)
		{
			mejora=true;
			m_solbest=sol;
			PiezasNoPosiblesEnSolMejor(m_solbest);	
		}

	}
*/	//Tengo una solución inicial
	//necesito ahora 
	std::list<BLOQUE>::iterator itB;
	m_iter_actual=0;
	
	m_solbest=ContarSolucion(m_lista_bloques);
	if (m_Cota==m_solbest) return m_solbest;
	m_sol_actual=m_solbest;
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual,0);

	printf("Solucion inicial %d\n", m_solbest);
	std::vector<int> vec,vec_tipo;
	std::vector<int> ::iterator it,it2;
//	printf("%d",m_Cota);
	int kon=0;
	for (kon=0;kon<m_Numpiezas;kon++) vec.push_back(kon);
	for (kon=0;kon<2;kon++) vec_tipo.push_back(kon);
	//Tama de la lista tabu
	m_tam_tabu=m_Q/2;
	do
	{
		MOVE BestMove,Movimiento;
		m_iter_actual++;
		mejora=false;
//		printf("ITeracion %d\n",m_iter_actual);
//		if (m_iter_actual>800) 
//			SetPasoaPaso(true);

//		printf("%d  %d\n",m_tam_tabu_perdidas, m_lista_tabu_perdidas.size());
		again:;
		m_max_valor=INT_MIN;
		int valempate=INT_MIN;
		int valempate2=INT_MIN;
		int Estabu=-2;
//		if (m_iter_actual%200==0) m_tam_tabu=get_random(0.25*m_Q,1*m_Q);
		if (m_iter_sin_mejorar%250==0 )
		{
			std::list<BLOQUE>::iterator itBlo;
			std::list<RECTAN>::iterator itRec;


			//Hago una solución que es simétrica de los dos ejes
			//Simetrica pero tambien debo hacer simetricas las perdidas
			for (itBlo=m_lista_bloques.begin();itBlo!=m_lista_bloques.end();itBlo++)
			{
				int kk=(*itBlo).Width();
				(*itBlo).left=m_L-(*itBlo).left-(*itBlo).Width();
				(*itBlo).right=(*itBlo).left+kk;
				kk=(*itBlo).Height();
				(*itBlo).top=m_W-(*itBlo).top-(*itBlo).Height();
				(*itBlo).bottom=(*itBlo).top+kk;
			}
			for (itRec=m_lista_perdidas.begin();itRec!=m_lista_perdidas.end();itRec++)
			{
				int kk=(*itRec).Width();
				(*itRec).left=m_L-(*itRec).left-(*itRec).Width();
				(*itRec).right=(*itRec).left+kk;
				kk=(*itRec).Height();
				(*itRec).top=m_W-(*itRec).top-(*itRec).Height();
				(*itRec).bottom=(*itRec).top+kk;

			}

		}
		if (m_iter_sin_mejorar%100==0)
		{
			m_tam_tabu=get_random(0.25*m_Q,0.75*m_Q);
			m_tam_tabu_perdidas=m_tam_tabu;
//			m_tam_tabu=3;

//			m_iter_sin_mejorar=0;
		}
		
		//Hago aleatorio el tipo de movimiento
//		std::random_shuffle(vec.begin(),vec.end());
		for (it2=vec_tipo.begin();it2!=vec_tipo.end() ;it2++)
		{
			if ((*it2)==1)
			{
			//Movimientos de disminuir 
			for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end() ;itB++)
			{
								//Si es una pieza pequeña no pruebo a quitarla ya que se supone que 
				//aparecerá algo mejor
//				if ((*itB).GetNumero()>(m_Numpiezas*0.7)) continue;
				if ((m_conpesos!=true) ) continue;
				//Si es restringido solo intentar quitar las que se puedan
				if ((m_Restringido==true  && (m_Piezas[(*itB).GetNumero()].num-m_Piezas[(*itB).GetNumero()].min)>0) || (m_Restringido==false))
				{
					// printf("Entro 3 ");	
					BLOQUE b2=(*itB);
					int cerca_perdidas=BloqueCercaPerdidas((*itB),0);
//					int cerca_perdidas=1;
					//Si estoy en una solución buena intensifico la busqueda en este rectángulo
					if (cerca_perdidas==1 || (m_sol_actual>=m_solbest) || m_lista_perdidas.size()==0 )
					{
		
						BLOQUE b2=(*itB);
						for (register int an_i=1; an_i<=((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo) ;an_i++)
						{
							for (register int la_j=1;la_j<=((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho) ;la_j++)
							{
								if (m_Restringido==true && ((an_i*la_j)>m_Piezas[(*itB).GetNumero()].num-m_Piezas[(*itB).GetNumero()].min))
									continue;
									int x1=an_i;
									int y1=la_j;
									if (x1==y1) 
									{
										if ((*itB).Width()==m_Piezas[(*itB).GetNumero()].largo) x1=0;
											else y1=0;
									}
									if (x1>y1)
									{
										y1=0;
									}
									if (y1>x1)
									{
										x1=0;
									}
/*									int cerca_perdidas=6;
									if (x1==0) cerca_perdidas=BloqueCercaPerdidas((*itB),10);
									if (y1==0) cerca_perdidas=BloqueCercaPerdidas((*itB),15);
										// printf("Salgo 3 ");
									if (cerca_perdidas==0) continue;
*/
	/*								bool tabu=false;
									for (itB2=m_lista_tabu.begin();itB2!=m_lista_tabu.end() && tabu==false;itB2++)
									{
		
										if (((*itB).GetNumero()==(*itB2).GetNumero()) && (*itB).Height()==(*itB2).Height() && (*itB2).Width()==(*itB).Width())
										tabu=true;
									}
									if (tabu==true) continue;
*/
//									printf("\nDisminuirkk");
								Movimiento=Disminuir_Bloques_Tabu((*itB),x1,y1);
								if (Movimiento.GetAlgoNuevo()!=true)
									continue;
//								VerificarSolucion(Movimiento.GetListaBloques(),Movimiento.GetListaPerdidas(),5);
								//Criterio de aspiración
								int tempM=EvaluarMovimiento(Movimiento);
								int statusTabu=-1;
								if (tempM>=valempate || (Movimiento.GetValor()+m_sol_actual)>m_solbest)
								{
//									statusTabu=EsTabu(Movimiento);
									statusTabu=EsTabuNew(Movimiento);
									if ( (statusTabu==9999  && mejora==false) || (m_sol_actual+Movimiento.GetValor()>m_solbest))
									{
										if ((Movimiento.GetValor()+m_sol_actual)>m_solbest) 
										{
											if (statusTabu!=9999 && m_iter_actual>100) 
											{
//												for (int register j=0;j<100;j++) 
//													printf("ESTESI");
											}
											m_solbest=(Movimiento.GetValor()+m_sol_actual);
											m_iter_solbest=m_iter_actual;
											mejora=true;
											Estabu=9999;
											m_lista_tabu.clear();
											printf("MejorD %d Iter %d Sin mejorar %d\n",m_solbest,m_iter_actual, m_iter_sin_mejorar);
											if (cerca_perdidas==1)
											{
		//									for (int i=0;i<50;i++)
		//										printf("Al disminuir");
	  //                                  	printf("%3d\t%3d\t%3d\t%3d\t%d\n",Movimiento.GetBloqueAntiguo().top,Movimiento.GetBloqueAntiguo().bottom,Movimiento.GetBloqueAntiguo().left,Movimiento.GetBloqueAntiguo().right,Movimiento.GetBloqueAntiguo().GetNumero());
	//										EscribirSolucionLatex(Movimiento.GetListaBloques());
											}
											m_iter_sin_mejorar=0;

										}
										Estabu=statusTabu;
									
										valempate=tempM;
										m_max_valor=valempate;
										BestMove.Igual(Movimiento);
										m_movdismi++;
										movdismi=true;
										movaumen=false;

									}
									else
									{
										if (statusTabu>Estabu && mejora==false)
										{
											if (tempM>=valempate2)
											{
												valempate2=tempM;

												Estabu=statusTabu;
												BestMove.Igual(Movimiento);
												m_movdismi++;
												movdismi=true;
												movaumen=false;

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
			else
			{			//Movimientos de aumentar
				//De los bloques que no estén metidos los meto los posibles
				//Para aleatorizarlo por si hay empates
				//			std::random_shuffle(vec.begin(),vec.end());
				int cont1=0;
				for (it=vec.begin();it!=vec.end() ;it++)
				{
					//Como elijo el movimiento depende de las pérdidas
					//Recorro las pérdidas y meto el bloque que solape con más perdidas
					//Si tengo colocadas todas las que puedo de este tipo
					kon=(*it);
					if (m_conpesos==false && cont1==1) break;
//					if (m_conpesos==true && kon!=rk) continue;
					//Si es un problema doblemente restringido pruebo con todos
					if (m_conpesos==true && (kon>(m_Numpiezas*0.5)) && m_Restringido==false)    break;
//					if ((*it)>(m_Numpiezas*0.75)) continue;

					int dif=m_Piezas[kon].num-m_Piezas[kon].max;
					if ( (dif)<0)
					{
						cont1++;
						//funcion que me dice si voy a mejorar el mejor movimiento metiendo
						//este bloque, ya que si meto el bloque se que ocurre


						//Si la pieza es pequeña no la fuerzo para meter ya que se supone que 
						//entrará sola
//						if (m_Piezas[kon].largo<(m_L/3) && m_Piezas[kon].ancho<(m_W/3))
//							continue;
						for (register int la_i=1; la_i<=((-1)*(dif))  ;la_i++)
						{
							for (register int an_j=1;an_j<=2 ;an_j++)
							{
								char tipo='H';
								if (an_j==2) tipo='V';
								if (la_i==1 && an_j==2) continue;
								//Para vigilar que el bloque no sea 
								//más grande que el ancho o el largo del
								//tablero
								if (tipo=='H')
								{
									if ((m_Piezas[kon].largo*la_i)>m_L)
										continue;
								}
								if (tipo=='V')
								{
									if ((m_Piezas[kon].ancho*la_i)>m_W)
										continue;
								}
/*								bool tabu=false;
								for (itB2=m_lista_tabu.begin();itB2!=m_lista_tabu.end() && tabu==false;itB2++)
								{
		
									if ((kon==(*itB2).GetNumero()) && la_i==1 && (*itB2).Height()==m_Piezas[kon].ancho && (*itB2).Width()==m_Piezas[kon].largo)
										tabu=true;
								}
								if (tabu==true) continue;
*/
								std::list<RECTAN> ::iterator itL;
								//Las esquinas donde se colocan son:
								//1 derecha arriba 
								//2 derecha abajo
								//3 izquierda arriba
								//4 izquierda abajo
								//Intento meter el bloque en la perdida mayor que se pueda solapar
								int cont2=0;
								for (itL=m_lista_perdidas.begin();itL!=m_lista_perdidas.end() ;itL++)
								{
									//NUEVONuevo para que tarde menos en hacer la búsqueda
									if ((m_Piezas[kon].largo*m_Piezas[kon].ancho)>(20*((*itL).Width()*(*itL).Height())))
										continue;
//									if (m_lista_perdidas.size()>=15 && (((*itL).Width()*((*itL).Height()))>(((m_total_superficie-m_sol_actual)*4)/m_lista_perdidas.size()))) 
			
//									if (m_conpesos==true && cont2==1 && m_iter_actual%1==0) break;
									if ( m_conpesos==true && cont2==1) break;
									if (m_Restringido==true && cont2==1) break;

//									for (int register esq=1;esq<=4;esq++)
									for (int register esq=1;esq<2;esq++)
									{
										//NUEVONuevo para que tarde menos en hacer la búsqueda
										esq=get_random(1,4);

//										if (m_conpesos==true && esq==2) break;
										if ( m_conpesos==true && cont2==1 && m_Restringido==false)  break;
										if (m_Restringido==true && cont2==1) break;
										if (((*itL).left==0 && (esq==1 || esq==2)) && m_conpesos==false) continue;
										if (((*itL).top==0 && (esq==1 || esq==3))&& m_conpesos==false)  continue;
										if (((*itL).bottom==m_L && (esq==2 || esq==4))&& m_conpesos==false)  continue;
										if (((*itL).right==m_W && (esq==3 && esq==4))&& m_conpesos==false)  continue;
										cont2++;
									//si la pieza es igual de ancha que el hueco solo a un lado
//									if ((esq==1 || esq==2) && (*itL).right!=m_W && (*itL).Width()==m_Piezas[kon].largo  ) 
//										continue;
									//si la pieza es igual de alta solo arriba
//									if ((esq==2 || esq==4) && (*itL).bottom!=m_L && (*itL).Height()==m_Piezas[kon].ancho  ) 
//											continue;

//									printf("\nAumentar B %d  P %d Tama %d",cont1,cont2,m_lista_perdidas.size());

		//							if (get_random(0,2)<=1) continue;
									if (m_conpesos==false)
									Movimiento=Aumentar_Bloques(kon,la_i,tipo,(*itL),esq);
									if (m_conpesos==true)
									{
					//					if (m_iter_actual%1==0)
										//Busco la mayor perdida y meto el bloque
										Movimiento=Aumentar_Bloques_UnaPerdida(kon,la_i,tipo);

					//					else
					//						Movimiento=Aumentar_Bloques_Esquina(kon,la_i,tipo,(*itL));
									}
//									Movimiento=Aumentar_Bloques_Esquina(kon,la_i,tipo,(*itL));
//									Movimiento=Aumentar_Bloques(kon,la_i,tipo,(*itL));
									if (Movimiento.GetAlgoNuevo()!=true) continue;
						//			VerificarSolucion(Movimiento.GetListaBloques(),Movimiento.GetListaPerdidas(),111);
									int tempM=EvaluarMovimiento(Movimiento);
									int statusTabu=-1;
									if (tempM>=valempate || (Movimiento.GetValor()+m_sol_actual)>m_solbest)
									{
//										statusTabu=EsTabu(Movimiento);
										statusTabu=EsTabuNew(Movimiento);
										if ( (statusTabu==9999  && mejora==false) || (m_sol_actual+Movimiento.GetValor()>m_solbest))
										{
											if (statusTabu!=9999 && m_iter_actual>100) 
											{
//												for (int register j=0;j<100;j++) 
//													printf("ESTESI");
											}

											if ((Movimiento.GetValor()+m_sol_actual)>m_solbest) 
											{
												Estabu=9999;
												m_solbest=(Movimiento.GetValor()+m_sol_actual);
												m_iter_solbest=m_iter_actual;

												mejora=true;
												m_lista_tabu.clear();
//												printf("MejorA %d Iter %d Sin mejorar %d\n",m_solbest,m_iter_actual, m_iter_sin_mejorar);
												m_iter_sin_mejorar=0;

											}
											Estabu=statusTabu;
											valempate=tempM;
											m_max_valor=valempate;
											BestMove.Igual(Movimiento);
											m_movaumen++;
											movdismi=false;
											movaumen=true;
	

										}
										else
										{
											if (statusTabu>Estabu  && mejora==false)
											{
												if (tempM>=valempate2)
												{
													valempate2=tempM;

													Estabu=statusTabu;
													BestMove.Igual(Movimiento);
													m_movaumen++;
													movdismi=false;
													movaumen=true;

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
			}
		}

		m_max_valor=__max(valempate,valempate2);
		m_iter_sin_mejorar++;
//		if (m_iter_actual==500)
//		{
//			PintarPiezas(); 
//		}
		//Ya tengo elegido uno ahora tengo que actualizar la solución
//		if (m_lista_tabu.size()>0 && m_max_valor==(INT_MIN) ) 
		if ((m_lista_tabu_new.size()>0 && valempate==(INT_MIN) && valempate2!=(INT_MIN) ) ||m_max_valor==(INT_MIN)) 
		{
			if (m_max_valor!=INT_MIN)
			{
			int tamlista=m_lista_tabu_new.size();
			for (int register i=0;i<=(tamlista-Estabu);i++)
				m_lista_tabu_new.pop_front();
//			m_lista_tabu_aumen.pop_front();
			printf("\nTengo que borraR %d TamLista %d %d",m_iter_actual,m_lista_tabu_new.size(),m_iter_sin_mejorar);
			goto again;
			}
			else
			{
				printf("\nTengo que borrar %d TamLista %d %d",m_iter_actual,m_lista_tabu_new.size(),m_iter_sin_mejorar);
				m_lista_tabu_new.pop_front();
				goto again;


			}
		}
		if (m_max_valor==(INT_MIN) && m_lista_tabu_new.size()==0)
		{
			printf("No puedo hacer ningún movimiento");
			printf("\n %d TamLista %d %d",m_iter_actual,m_lista_tabu_new.size(),m_iter_sin_mejorar);

			exit(5);
		}

		if (movdismi==true) m_hechomovdismi++;
		if (movaumen==true) m_hechomovaumen++;
//		if (m_iter_actual==512)
//			int ppepep=9;
			//Si movimiento es de aumentar no pongo nada en la lista
//		if (!((BestMove.GetBloqueAntiguo().TopLeft()==BestMove.GetBloqueNuevo().TopLeft()) && 
//			(BestMove.GetBloqueAntiguo().BottomRight()==BestMove.GetBloqueNuevo().BottomRight())))
		

//		Add_Lista_Tabu(BestMove.GetBloqueAntiguo());
		//Antiguo
//		if (mejora!=true)
//		Add_Lista_Tabu(BestMove);
		//nuevo
//		EscribirSolucionLatex(m_lista_bloques);

		Actualizar_Lista_Bloques(BestMove);
		Add_Lista_TabuNew(BestMove.GetListaPerdidas());
//		VerificarSolucion(BestMove.GetBloquesNuevos(),BestMove.GetListaPerdidas(),212);
		m_lista_perdidas.clear();
		if (m_iter_actual==1000000)
		{
			FILE *fin;
			fin=fopen("Tabu.txt","a");

			std::list< etabu > ::iterator itBt;
			for (itBt=m_lista_tabu_new.begin();itBt!=m_lista_tabu_new.end();itBt++)
			{

				fprintf(fin,"(%d,%d)(%d,%d)\t%d\n",(*itBt).Union.left,(*itBt).Union.top,(*itBt).Union.right,(*itBt).Union.bottom,(*itBt).area);
//				printf("(%d,%d)(%d,%d)\t%d\t%d\t%d\n",BestMove.GetBloqueNuevo().left,BestMove.GetBloqueNuevo().top,BestMove.GetBloqueNuevo().right,BestMove.GetBloqueNuevo().bottom,m_Piezas[BestMove.GetBloqueNuevo().GetNumero()].largo,m_Piezas[BestMove.GetBloqueNuevo().GetNumero()].ancho,m_Piezas[BestMove.GetBloqueNuevo().GetNumero()].valor);
//				EscribirBloquesPantalla(BestMove.GetListaBloques());
			}
			fclose(fin);
		}
//		Bloques_Hacia_Las_Esquinas(BestMove.GetBloquesNuevos(),BestMove.GetListaPerdidas());

		m_lista_perdidas.insert(m_lista_perdidas.begin(),BestMove.GetListaPerdidas().begin(),BestMove.GetListaPerdidas().end());
//		printf("Numero de perdidas %d\n",m_lista_perdidas.size());
//		VerificarSolucion(m_lista_bloques,m_lista_perdidas,3);
	//	EscribirSolucion(m_lista_bloques);
		m_sol_actual=ContarSolucion(m_lista_bloques);
		ActualizarFrecuencias();
//		if (m_iter_actual%250==0)

//		VerificarSolucion(m_lista_bloques,m_lista_perdidas,4);
//		if (m_iter_actual==100)
//		if (m_sol_actual>=m_solbest)
		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual,0);
		if (mejora==true && m_conpesos==true)
		{
		
			int temp=m_Q;
			PiezasNoPosiblesEnSolMejor(m_solbest);	
			if (m_Q!=temp)
			{
				vec.clear();
				for (kon=0;kon<m_Numpiezas;kon++) vec.push_back(kon);
				HeuristicoGreedy(dibu);
				m_sol_actual=ContarSolucion(m_lista_bloques);
			}
		}
		if (m_PathRelinking==true )
		{

//				m_valor_maximo=max_candi_actual-(m_max_valor*VALOROPTIMO)-((EFIBLOQUE/10)*Porcentaje_Eficiente(BestMove.GetBloqueAntiguo()));
//				if (Es_Eficiente(BestMove.GetListaBloques())==true ) m_valor_maximo-=EFICIENTES;
//				if (Movimiento.GetAlgoNuevo()==true) m_valor_maximo-=NUEVO;
//				if (m_utilizar_frecuencias==true) m_valor_maximo=VecesQueHaAparecidoElBloque(BestMove.GetBloqueAntiguo())*20;
			ActualizarConjuntoReferencia(BestMove,m_sol_actual);
//			else printf("%d\t%d\t%d\n",m_sol_actual,Valida_Simetria(m_lista_perdidas),Valida_Optimo(m_lista_bloques));
			if (m_iter_actual%100==0)
			{
				std::list<pathre>::iterator itBB;
				printf("Tama %d",m_conjunto_ref.size());
				for(itBB=m_conjunto_ref.begin();itBB!=m_conjunto_ref.end();itBB++)
				{
					DibujarSolucion((*itBB).lista_bloques,(*itBB).lista_perdidas,777,(*itBB).fobjetivo);
				}
				int solcomb=CombinarSolucionesConjuntoRef();
				if (solcomb==m_Cota) 
					return solcomb;
				if (solcomb>=m_solbest) 
					printf("Buena al juntar");
				m_conjunto_ref.clear();
			}
		}
		if (m_Cota==m_solbest && movaumen==false)
		{
			for (int i=0;i<50;i++)
			printf("Al disminuir");
//			EscribirSolucionLatex(m_lista_bloques);
		}
//	printf("Iter %d Best %d\n",m_iter_actual,m_solbest);
	}while((m_iter_sin_mejorar<10000) && (m_iter_actual<m_max_iteraciones) && (m_solbest!=m_Cota) && (m_max_valor!=(INT_MIN)));

	printf("Total movimiento %d Movimientos no Tabu %d",m_totalmov, m_movtabu);
	printf("Iter %d Sol %d Cota %d ",m_iter_actual,m_solbest, m_Cota);
	return m_solbest;
}
MOVE CUTTING::Aumentar_Bloques_UnaPerdida(int num,int cuantos,char sentido)
{
	int largo1,ancho1;
	int largo=m_Piezas[num].largo;
	int ancho=m_Piezas[num].ancho;
	if (sentido=='H')
	{
		largo1=cuantos*largo;
		ancho1=ancho;
	}
	else
	{
		largo1=largo;
		ancho1=cuantos*ancho;
	}
	BLOQUE B1(0,0,0,0),B1Aumen(0,0,largo1,ancho1);
	B1.SetNumero(num);
	B1Aumen.SetNumero(num);
	B1.SetTipo('A');
	B1Aumen.SetTipo('A');
	RECTAN RectTemp,RectTemp2,RectMax;
	std::list<RECTAN> ::iterator itL;
	int min=99999,min2=99999;
	//Intento meter el bloque en la perdida mayor que se pueda solapar
	for (itL=m_lista_perdidas.begin();itL!=m_lista_perdidas.end();itL++)
	{
		RECTAN RectTemp2(0,0,(*itL).Width(),(*itL).Height());
		SubtractRect(&RectTemp,&B1Aumen,&RectTemp2);
		if (RectTemp.Width()*RectTemp.Height()<=min)
		{
			//Si las dos tienen en común la misma 
			//área me quedo con la pérdida
			//más pequeña
			if (RectTemp.Width()*RectTemp.Height()==min && (*itL).Width()*(*itL).Height()<min2)
			{
				RectMax=(*itL);
				min=RectTemp.Width()*RectTemp.Height();
				min2=(*itL).Width()*(*itL).Height();
			}
			else
			{
				RectMax=(*itL);
				min=RectTemp.Width()*RectTemp.Height();
				min2=(*itL).Width()*(*itL).Height();

			}
		}


	}
	ColocarEsquinaMasCercana(RectMax,B1Aumen);
	int Quito=m_sol_actual;	

	B1=B1Aumen;
	MOVE movimiento(B1,B1Aumen,0);

	movimiento.GetListaPerdidas().clear();
	RECTAN PTotal(0,0,m_L,m_W);

	movimiento.GetListaPerdidas().push_back(PTotal);
	AumentarBloque(movimiento);
	movimiento.GetListaBloques().push_back(B1Aumen);
//	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());

//	m_Piezas[num].num+=(B1Aumen.Width()*B1Aumen.Height())/(largo*ancho);
	ColocarNumeros(movimiento.GetListaBloques());

	Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);
//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),7);
//	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
	JuntarPerdida(movimiento.GetListaPerdidas(),'P');
//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),25);
	std::list<BLOQUE> lista;
	Rellenar(lista,movimiento.GetListaPerdidas(),99999);

	movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);

//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),251);
	int Meto=ContarSolucion(movimiento.GetListaBloques());

//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),2514);
	ColocarNumeros(m_lista_bloques);
	movimiento.SetValor(Meto-Quito);
	int temporal=EvaluarMovimiento(movimiento);
	if (temporal<m_max_valor )
	{
		movimiento.SetAlgoNuevo(false);
		return movimiento;
	}



	return movimiento;
}

void CUTTING::Aumentar_Bloques_UnaPerdidaStrip(int num,int cuantos)
{
	int largo1,ancho1;
	int largo=m_Piezas[num].largo;
	int ancho=m_Piezas[num].ancho;
	largo1=largo;
	ancho1=cuantos*ancho;
	BLOQUE B1(0,0,0,0),B1Aumen(0,0,largo1,ancho1);
	B1.SetNumero(num);
	B1Aumen.SetNumero(num);
	B1.SetTipo('A');
	B1Aumen.SetTipo('A');
	RECTAN RectTemp,RectTemp2,RectMax;
	std::list<RECTAN> ::iterator itL;
	int min=99999,min2=99999;
	//Intento meter el bloque en la perdida mas hacia la izquierda 
	for (itL=m_lista_perdidas.begin();itL!=m_lista_perdidas.end();itL++)
	{
		if ((*itL).right==m_L) continue;
		if ((*itL).left<min)
		{
			RectMax=(*itL);
			min=(*itL).left;
		}

		//Antiguo
/*
		RECTAN RectTemp2(0,0,(*itL).Width(),(*itL).Height());
		//Rectángulo coincide
		RECTAN RectTemp(0,0,__min((*itL).right,B1Aumen.Width()),__min((*itL).bottom,B1Aumen.Height()));
		if (RectTemp.Width()*RectTemp.Height()<=min)
		{
			//Si las dos tienen en común la misma 
			//área me quedo con la pérdida
			//más pequeña
			if (RectTemp.Width()*RectTemp.Height()==min && (*itL).left<min2)
			{
				RectMax=(*itL);
				min=RectTemp.Width()*RectTemp.Height();
				min2=(*itL).left;
			}
			else
			{
				RectMax=(*itL);
				min=RectTemp.Width()*RectTemp.Height();
				min2=(*itL).left;

			}
		}
*/

	}
	ColocarEsquinaMasCercanaStrip(RectMax,B1Aumen);

	B1=B1Aumen;

	m_lista_perdidas.clear();
	RECTAN PTotal(0,0,m_L,m_W);

	m_lista_perdidas.push_back(PTotal);
//	FILE *fin;
//	fin=fopen("Solcut.txt","a+");

//	fprintf(fin,"Bloque meto (%d,%d)(%d,%d)\t%d\t%d\t%d\n",B1.top,B1.left,B1.top+m_Piezas[B1.GetNumero()].ancho,B1.left+m_Piezas[B1.GetNumero()].largo,m_Piezas[B1.GetNumero()].largo,m_Piezas[B1.GetNumero()].ancho,m_Piezas[B1.GetNumero()].valor);
//	fclose(fin);
	AumentarBloque(B1);
	m_lista_bloques.push_back(B1Aumen);
//	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());

//	m_Piezas[num].num+=(B1Aumen.Width()*B1Aumen.Height())/(largo*ancho);
	ColocarNumeros(m_lista_bloques);

	Actualizar_Perdida(m_lista_bloques,m_lista_perdidas);
	//Llamo a función bloques hacia las esquinas
	Bloques_Hacia_Las_EsquinasStrip(m_lista_bloques,m_lista_perdidas,0);
	JuntarPerdida(m_lista_perdidas,'H');

	DibujarSolucion(m_lista_bloques,m_lista_perdidas,888,888);
//	VerificarSolucion(m_lista_bloques,m_lista_perdidas,7);
//	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());

}

//Aumentar bloques

MOVE CUTTING::Aumentar_Bloques_Esquina(int num,int cuantos,char sentido, RECTAN &Rect1)
{
	int largo1,ancho1;
	int largo=m_Piezas[num].largo;
	int ancho=m_Piezas[num].ancho;
	if (sentido=='H')
	{
		largo1=cuantos*largo;
		ancho1=ancho;
	}
	else
	{
		largo1=largo;
		ancho1=cuantos*ancho;
	}
	BLOQUE B1(0,0,0,0),B1Aumen(0,0,largo1,ancho1);
	B1.SetNumero(num);
	B1Aumen.SetNumero(num);
	B1.SetTipo('A');
	B1Aumen.SetTipo('A');

	ColocarEsquinaMasCercana(Rect1,B1Aumen);
	int Quito=m_sol_actual;	

	B1=B1Aumen;
	MOVE movimiento(B1,B1Aumen,0);

	movimiento.GetListaPerdidas().clear();
	RECTAN PTotal(0,0,m_L,m_W);

	movimiento.GetListaPerdidas().push_back(PTotal);
	AumentarBloque(movimiento);
	movimiento.GetListaBloques().push_back(B1Aumen);
	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());

//	m_Piezas[num].num+=(B1Aumen.Width()*B1Aumen.Height())/(largo*ancho);
	ColocarNumeros(movimiento.GetListaBloques());

	Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);
//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),7);
//	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
	JuntarPerdida(movimiento.GetListaPerdidas(),'P');
//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),25);
	std::list<BLOQUE> lista;
	Rellenar(lista,movimiento.GetListaPerdidas(),99999);

	movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);

//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),251);
	int Meto=ContarSolucion(movimiento.GetListaBloques());

//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),2514);
	ColocarNumeros(m_lista_bloques);
	movimiento.SetValor(Meto-Quito);
	int temporal=EvaluarMovimiento(movimiento);
	if (temporal<m_max_valor )
	{
		movimiento.SetAlgoNuevo(false);
		return movimiento;
	}

	movimiento.SetValor(Meto-Quito);

//	bool fin=false;
	//Mierda
/*	for (itLK=movimiento.GetBloquesNuevos().begin();itLK!=movimiento.GetBloquesNuevos().end() && fin!=true;itLK++)
	{
		//Si tienen el mismo numero
		if ((*itLK).GetNumero()==B1.GetNumero())
		{
			bool igual=false;
			for (itLK2=m_lista_bloques.begin();itLK2!=m_lista_bloques.end() && igual!=true;itLK2++)
			{
				if ((*itLK).top==(*itLK2).top && (*itLK).bottom==(*itLK2).bottom && (*itLK).left==(*itLK2).left && (*itLK).right==(*itLK2).right && (*itLK).GetNumero()==(*itLK2).GetNumero()) 
					igual=true;

			}
			if (igual==false) fin=true;
		}
		itLK++;

	}
*/
//	JuntarPerdida(movimiento.GetListaPerdidas(),'X');
//	CompactarBloques(movimiento);
//	JuntarPerdida(movimiento.GetListaPerdidas(),'X');
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),555,555);
	
//	VerificarSolucion(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),8);

	return movimiento;
}

MOVE CUTTING::Aumentar_Bloques(int num,int cuantos,char sentido, RECTAN &Rect1,int esq)
{
	int largo1,ancho1;
	int largo=m_Piezas[num].largo;
	int ancho=m_Piezas[num].ancho;
	if (sentido=='H')
	{
		largo1=cuantos*largo;
		ancho1=ancho;
	}
	else
	{
		largo1=largo;
		ancho1=cuantos*ancho;
	}
	BLOQUE B1(0,0,0,0),B1Aumen(0,0,largo1,ancho1);
	B1.SetNumero(num);
	B1Aumen.SetNumero(num);
	B1.SetTipo('A');
	B1Aumen.SetTipo('A');
	ColocarEsquinaMasCercana(Rect1,B1Aumen,esq);

	B1=B1Aumen;
	MOVE movimiento(B1,B1Aumen,0);
//	if ((Rect1.Widht()*Rect1.Height())<)
	//Para reducir el número de bloques si la pérdida produce un solapamiento menor
	//que el 10% no lo examino

	std::list<RECTAN> ::iterator itL;
	RECTAN RectTemp;
//	double vale=0.255;
	/*
	double vale=0.0;
	int area_intersecta=0;
	if (Rect1.Width()==B1Aumen.Width() || Rect1.Height()==B1Aumen.Height() || (Rect1.Height()*Rect1.Width())>=(B1Aumen.Width()*B1Aumen.Height()*vale))
		area_intersecta=9999999;
	for (itL=m_lista_perdidas.begin();itL!=m_lista_perdidas.end() && area_intersecta==0;itL++)
	{
		RECTAN RectTemp2((*itL).left,(*itL).top,(*itL).right,(*itL).bottom);
		IntersectRect(&RectTemp,&B1Aumen,&RectTemp2);
		if (!RectTemp.IsRectEmpty())
		{
			area_intersecta+=RectTemp.Width()*RectTemp.Height();
		}
	}
		

	if (area_intersecta<((B1Aumen.Width()*B1Aumen.Height())*vale) && m_sol_actual<m_solbest)
	{
		movimiento.SetAlgoNuevo(false);
		return movimiento;
	}
	*/
	int Quito=m_sol_actual;	
	movimiento.GetListaPerdidas().clear();
	RECTAN PTotal(0,0,m_L,m_W);

	movimiento.GetListaPerdidas().push_back(PTotal);
	AumentarBloque(movimiento);
	movimiento.GetListaBloques().push_back(B1Aumen);
//	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());

//	m_Piezas[num].num+=(B1Aumen.Width()*B1Aumen.Height())/(largo*ancho);
	ColocarNumeros(movimiento.GetListaBloques());

	Actualizar_Perdida(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);
//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),7);
//	if (m_sol_actual>=m_solbest
	Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
	JuntarPerdida(movimiento.GetListaPerdidas(),'P');
//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),25);
	std::list<BLOQUE> lista;
	Rellenar(lista,movimiento.GetListaPerdidas(),99999);

	movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista.begin(),lista.end());
//	DibujarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),888,888);

//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),251);
	int Meto=ContarSolucion(movimiento.GetListaBloques());

//	VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),2514);
	ColocarNumeros(m_lista_bloques);
	movimiento.SetValor(Meto-Quito);
	int temporal=EvaluarMovimiento(movimiento);
	if (temporal<m_max_valor  && (m_sol_actual+movimiento.GetValor()<m_solbest))
	{
		movimiento.SetAlgoNuevo(false);
		return movimiento;
	}

	movimiento.SetValor(Meto-Quito);
//	VerificarSolucion(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),81);
	//Intensifico la búsqueda
	if (m_sol_actual+movimiento.GetValor()>=m_solbest)
	{
		Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//		printf("Paso POR AQUI");

		ColocarNumeros(movimiento.GetBloquesNuevos());
		JuntarPerdida(movimiento.GetListaPerdidas(),'P');
		Rellenar(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),99999);

		int Meto2=ContarSolucion(movimiento.GetListaBloques());
		VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),2514);
		ColocarNumeros(m_lista_bloques);
		movimiento.SetValor(Meto2-Quito);


	}
	return movimiento;
}
/*
int CUTTING::Grasp(bool dibu)
{
	m_solbest=0;
	m_iter_actual=0;
	bool posi=false;
	int inicio=2;
	//Inicializamos la semilla
	srand(1);
	int maxPosible=0;
	std::vector<int> vec_veces(10);
	std::vector<int> vec_buenas(10),vec_valor(10);
	int alea=0,hastavalor=0,indice=0;
	double total=0;
	int peorSolucion=999999999;
	m_Cota=CotaSuperiorArchivo();
	for (int ik=0;ik<5;ik++)


	//***************************************
	//Maximo posible para 
	//***************************************
	for (register int j=0;j<m_Numpiezas;j++)
		maxPosible+=m_Piezas[j].max*m_Piezas[j].valor;
//	for (register int iter=0;iter<m_max_iteracionesGrasp;iter++)
	for (m_iter_actual=0;m_iter_actual<m_max_iteracionesGrasp;m_iter_actual++)
	{	
//		m_FactorAleatorio=(double)get_random(25,75)/(double)100;
		if (m_tipo_aleatoriedad==1) 
			m_FactorAleatorio=(double)get_random(40,90)/(double)100;
		if (m_tipo_aleatoriedad==3) 
			m_FactorAleatorio=(double)get_random(25,75)/(double)100;

		if (m_tipo_aleatoriedad==2) 
		{
			if (m_iter_actual==0)
			{
				m_FactorAleatorio=0.5;
			}
			else
			{
				if (m_iter_actual%200==0)
				m_FactorAleatorio+=0.1;
			}
		}
		if (m_tipo_aleatoriedad==5)
		{
			if (m_iter_actual%100==0 && m_iter_actual>0)
			{
				total=0;
				hastavalor=0;
				for (int ix=inicio;ix<10 ;ix++)
				{	
					if (vec_veces[ix]!=0 )
					{
		//				total+=m_solbest-((double)vec_valor[ix]/(double)vec_veces[ix]);
//Tipo1	
//						total+=pow((double)m_solbest/(double)((double)vec_valor[ix]/(double)vec_veces[ix]),10);
//Tipo 2
						
						double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);
						total+=pow((double)(meanix-peorSolucion)/(double)(m_solbest-peorSolucion),2);
						
					}
				}
				for (ix=inicio;ix<10 ;ix++)
				{
					if (vec_veces[ix]!=0 )
					{
//					vec_buenas[ix]=((double)10/(double)((m_solbest-((double)vec_valor[ix]/(double)vec_veces[ix]))))*(double)total;
//Tipo1					
					//	vec_buenas[ix]=((double)total/(double)(pow((double)m_solbest/(double)((double)vec_valor[ix]/(double)vec_veces[ix]),10)));
//Tipo2
						
						double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);

						double evalix=pow((double)(meanix-peorSolucion)/(double)(m_solbest-peorSolucion),2);
						vec_buenas[ix]=((double)evalix/(double)total)*100;
					//	
						hastavalor+=vec_buenas[ix];
					}
				}

			}

			if (m_iter_actual<100)
			{
				alea=get_random(inicio,9);
				m_FactorAleatorio=(double)alea/(double)10;

			}
			else
			{
				alea=get_random(1,hastavalor);
				//busco cual es el que corresponde
				int suma=0;
				for (int ix=inicio;ix<10 && suma<alea;ix++)
				{	
					suma+=vec_buenas[ix];
					m_FactorAleatorio=(double)ix/(double)10;
				}
			}
			indice=m_FactorAleatorio*10;
		}
		HeuristicoGreedy(dibu);
		VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);

//		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//En lugar de que solo mejore las que esten al 90 por ciento de la mejor

//		printf("\n%d",iter);
		//Si no es la cota superior 
		//Sabemos que cuanto mayor es el número de piezas más probable es acercarnos a la cota
		//superior o a la mejor solución encontrada, por lo tanto este valor debería estar cerca 
		//si la solución es parecida
		if (m_ValSolucion!=maxPosible && (m_ValSolucion>((double)0.9*(double)m_solbest)) || (posi==false))
		{	
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);

//			VerificarSolucion(m_lista_bloques,m_lista_perdidas,5);
//			if (m_ValSolucion!=m_Cota)
//			{
//				if (iter==244 || iter==246 || iter==552000)
//				{
//					DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//					EscribirSolucionLatex(m_lista_bloques);
//				}
//					if (iter==277) DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//				MejoraLocalRapida();
				if (m_tipo_mejora==1 ||  m_tipo_mejora==2)
					MejoraLocal();
				if (m_tipo_mejora==3)
					MejoraLocalRapida();
//				if (m_ValSolucion==m_Cota) 
//				{
//					for (int ki=4; ;ki++)
//					printf("Logrado con la mejor");
//				if (iter==244 ||iter==246 || iter==552000)
//				{

//					EscribirSolucionLatex(m_lista_bloques);
//					if (m_ValSolucion==m_Cota || iter==277) 
//					{
//						printf("Aquiiiiii  %d %d",iter,m_ValSolucion);
//						exit(5);
//						DibujarSolucion(m_lista_bloques,m_lista_perdidas,iter,0);
//					}
//				}
//				}
//				}

//			}

//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);

		}
		//El reactive lo pongo después de hacer la mejora local
		if (m_ValSolucion<peorSolucion)
			peorSolucion=m_ValSolucion;
		if (m_tipo_aleatoriedad==5)
		{
			vec_veces[indice]++;
			vec_valor[indice]+=m_ValSolucion;
		}

//		printf("%d \n",m_ValSolucion);
		Posible();
		if ((m_ValSolucion>m_solbest && m_Posible==true) || (posi==false && m_Posible==true))
		{
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

//			if (m_ValSolucion>30000)
//				int perro=9;
			m_solbest=m_ValSolucion;
//			printf("Iter %d Sol %d",m_iter_actual,m_solbest);
			posi=m_Posible;
			VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);
			PiezasNoPosiblesEnSolMejor(m_ValSolucion);
//			EscribirSolucionLatex(m_lista_bloques);
			if (m_solbest==m_Cota) return m_solbest;
//			EscribirSolucion(m_lista_bloques);


		}

		m_lista_perdidas.clear();
		m_lista_bloques.clear();

		
	}
	if (posi==true) m_Posible=true;
	printf("Numero de Piezas %d %d",m_Numpiezas,m_iter_actual);
//	printf("%d",m_solbest);

	return m_solbest;
}
*/
int CUTTING::Grasp(bool dibu)
{
	m_noquiero=999999;

	m_NumPiezasBestSol=0;
	m_NumBloques=0;
//	printf("kk");
	m_solbest=0;
	m_iter_actual=0;
	bool posi=false;
	int inicio=2;
	//Inicializamos la semilla
	srand(1);
	int maxPosible=0;
	std::vector<int> vec_veces(10);
	std::vector<int> vec_buenas(10),vec_valor(10);
	int alea=0,hastavalor=0,indice=0;
	double total=0;
	int peorSolucion=999999999;
	m_Cota=CotaSuperiorArchivo();
	for (int ik=0;ik<5;ik++)


	//***************************************
	//Maximo posible para 
	//***************************************
	for (register int j=0;j<m_Numpiezas;j++)
		maxPosible+=m_Piezas[j].max*m_Piezas[j].valor;
//	for (register int iter=0;iter<m_max_iteracionesGrasp;iter++)
	for (m_iter_actual=0;m_iter_actual<m_max_iteracionesGrasp;m_iter_actual++)
	{	
//		m_FactorAleatorio=(double)get_random(25,75)/(double)100;
		if (m_tipo_aleatoriedad==1) 
			m_FactorAleatorio=(double)get_random(40,90)/(double)100;
		if (m_tipo_aleatoriedad==3) 
			m_FactorAleatorio=(double)get_random(25,75)/(double)100;

		if (m_tipo_aleatoriedad==2) 
		{
			if (m_iter_actual==0)
			{
				m_FactorAleatorio=0.5;
			}
			else
			{
				if (m_iter_actual%200==0)
				m_FactorAleatorio+=0.1;
			}
		}
		if (m_tipo_aleatoriedad==5)
		{
			if (m_iter_actual%100==0 && m_iter_actual>0 && m_solbest!=0)
			{
				total=0;
				hastavalor=0;
				for (int ix=inicio;ix<10 ;ix++)
				{	
					if (vec_veces[ix]!=0 && m_solbest!=0)
					{
		//				total+=m_solbest-((double)vec_valor[ix]/(double)vec_veces[ix]);
//Tipo1	
//						total+=pow((double)m_solbest/(double)((double)vec_valor[ix]/(double)vec_veces[ix]),10);
//Tipo 2
						
						double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);
						total+=pow((double)(meanix-peorSolucion)/(double)(m_solbest-peorSolucion),2);
						
					}
				}
				for (ix=inicio;ix<10 ;ix++)
				{
					if (vec_veces[ix]!=0 && m_solbest!=0)
					{
//					vec_buenas[ix]=((double)10/(double)((m_solbest-((double)vec_valor[ix]/(double)vec_veces[ix]))))*(double)total;
//Tipo1					
					//	vec_buenas[ix]=((double)total/(double)(pow((double)m_solbest/(double)((double)vec_valor[ix]/(double)vec_veces[ix]),10)));
//Tipo2
						
						double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);

						double evalix=pow((double)(meanix-peorSolucion)/(double)(m_solbest-peorSolucion),2);
						vec_buenas[ix]=((double)evalix/(double)total)*100;
					//	
						hastavalor+=vec_buenas[ix];
					}
				}

			}

	/*		if (m_iter_actual%100==0 && m_iter_actual>0 )
			{
				for (int ix=2;ix<10 ;ix++)
				{
					if (vec_veces[ix]!=0)
					printf("%d %d %d %f\n",ix,vec_veces[ix],vec_valor[ix],((double)vec_valor[ix]/(double)vec_veces[ix]));
				}

			}
			if (m_iter_actual%100==1 && m_iter_actual>1)
			{
				for (int ix=2;ix<10 ;ix++)
				{
					printf("%d %d\n",ix,vec_buenas[ix]);
				}

			}
*/
			if (m_iter_actual<100 || m_solbest==0)
			{
				alea=get_random(inicio,9);
				m_FactorAleatorio=(double)alea/(double)10;

			}
			else
			{
				alea=get_random(1,hastavalor);
				//busco cual es el que corresponde
				int suma=0;
				for (int ix=inicio;ix<10 && suma<alea;ix++)
				{	
					suma+=vec_buenas[ix];
					m_FactorAleatorio=(double)ix/(double)10;
				}
			}
			indice=m_FactorAleatorio*10;
		}
//		HeuristicoGreedyOrden(dibu);
		HeuristicoGreedy(dibu);
//		VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);
/*		if (m_ValSolucion>((double)7.95*(double)m_solbest))
		{
			vec_buenas[m_FactorAleatorio*10]++;
			total++;
		}
		
  */

//		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//En lugar de que solo mejore las que esten al 90 por ciento de la mejor

//		printf("\n%d",iter);
		//Si no es la cota superior 
		//Sabemos que cuanto mayor es el número de piezas más probable es acercarnos a la cota
		//superior o a la mejor solución encontrada, por lo tanto este valor debería estar cerca 
		//si la solución es parecida
//		int solantes=m_ValSolucion;
//		EscribirSolucionLatex(m_lista_bloques);

		if (m_ValSolucion!=maxPosible && (m_ValSolucion>((double)0.9*(double)m_solbest)) && m_HacerMejoraLocal==true)
		{	
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);

//			VerificarSolucion(m_lista_bloques,m_lista_perdidas,5);
//			if (m_ValSolucion!=m_Cota)
//			{
//				if (iter==244 || iter==246 || iter==552000)
//				{
//					DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//					EscribirSolucionLatex(m_lista_bloques);
//				}
//					if (iter==277) DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//				MejoraLocalRapida();
				if (m_tipo_mejora==1 ||  m_tipo_mejora==2)
					MejoraLocal();
				if (m_tipo_mejora==3)
					MejoraLocalRapida();
//				if (iter==244 ||iter==246 || iter==552000)
//				{

//					EscribirSolucionLatex(m_lista_bloques);
//					if (m_ValSolucion==m_Cota || iter==277) 
//					{
//						printf("Aquiiiiii  %d %d",iter,m_ValSolucion);
//						exit(5);
//						DibujarSolucion(m_lista_bloques,m_lista_perdidas,iter,0);
//					}
//				}
//				}
//				}

//			}

//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);

		}
		//El reactive lo pongo después de hacer la mejora local
		if (m_ValSolucion<peorSolucion)
			peorSolucion=m_ValSolucion;
		vec_veces[indice]++;
		vec_valor[indice]+=m_ValSolucion;

//		printf("%d %d\n",m_ValSolucion,j);
			Posible();
		if ((m_ValSolucion>m_solbest && m_Posible==true) || (posi==false && m_Posible==true))
		{
//			if (m_ValSolucion>30000)
//				int perro=9;
			m_solbest=m_ValSolucion;
//			printf("Iter %d Sol %d",m_iter_actual,m_solbest);
			posi=m_Posible;
//			VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);
			PiezasNoPosiblesEnSolMejor(m_ValSolucion);
			m_NumPiezasBestSol=ContarPiezas(m_lista_bloques);
			m_NumBloques=m_lista_bloques.size();
			if (m_solbest==m_Cota) 
			{
//				EscribirSolucionLatex(m_lista_bloques);

//				if (m_solbest-solantes>0) 
//					printf("Este puede valer");
				return m_solbest;
			}
//			EscribirSolucion(m_lista_bloques);
//			EscribirSolucionLatex(m_lista_bloques);


		}

		m_lista_perdidas.clear();
		m_lista_bloques.clear();

		
	}
	if (posi==true) m_Posible=true;
	printf("Numero de Piezas %d %d",m_Numpiezas,m_iter_actual);
//	printf("%d",m_solbest);

	return m_solbest;
}
int CUTTING::GraspStrip(bool dibu)
{
	m_noquiero=999999;
	m_perdida_menor=0;
	m_NumPiezasBestSol=0;
	m_NumBloques=0;
//	printf("kk");
	m_solbest=1000000;
 	m_iter_actual=0;
	bool posi=false;
	bool Reactive=false,ReactiveMejora=false;
	bool m_ReactiveMejora=true;
	if (m_tipo_mejora==5) 
		m_ReactiveMejora=true;
	else
		m_ReactiveMejora=false;
	//Inicializamos la semilla
	srand(1);
	int maxPosible=0;
	//Para hacer el reactive de 0.5 a 0.95 de 0.05
/*	std::vector<int> vec_veces(20);
	std::vector<int> vec_buenas(20),vec_valor(20);
	int inicio=10;
	int fin=19;
	int paso=20;
*/	//Para hacer el reactive de 0.2 a 0.9 de 

	std::vector<int> vec_veces(10);
	std::vector<int> vec_buenas(10),vec_valor(10);
	std::vector<int> vec_vecesMejora(5);
	std::vector<int> vec_buenasMejora(5),vec_valorMejora(5);
	int inicio=2;
	int fin=10;
	int paso=10;
	int alea=0,hastavalor=0,indice=0,hastavalorM=0;
	double total=0;
	int peorSolucion=0;
	int kk=ActualizarMinMax();
	if (m_PuedenRotarsePiezas==false)
	m_Cota=CotaInferiorArchivoStrip();

	if (m_Cota==0)
	m_Cota=__max(ceil((double)m_total_superficie/(double)m_W),m_MaxLargo);


	//***************************************
	//Maximo posible para 
	//***************************************
	for (register int j=0;j<m_Numpiezas;j++)
		maxPosible+=m_Piezas[j].max*m_Piezas[j].valor;
//	for (register int iter=0;iter<m_max_iteracionesGrasp;iter++)
	for (m_iter_actual=0;m_iter_actual<m_max_iteracionesGrasp;m_iter_actual++)
	{	
//		m_FactorAleatorio=(double)get_random(25,75)/(double)100;
		if (m_tipo_aleatoriedad==1) 
			m_FactorAleatorio=(double)get_random(40,90)/(double)100;
		if (m_tipo_aleatoriedad==3) 
			m_FactorAleatorio=(double)get_random(25,75)/(double)100;

		if (m_tipo_aleatoriedad==2) 
		{
			if (m_iter_actual==0)
			{
				m_FactorAleatorio=0.5;
			}
			else
			{
				if (m_iter_actual%200==0)
				m_FactorAleatorio+=0.1;
			}
		}
		
		if (m_tipo_aleatoriedad==5)
		{
			if (m_iter_actual%100==0 && m_iter_actual>0 && m_solbest!=0 && m_solbest!=peorSolucion)
			{
				Reactive=true;
				total=0;
				hastavalor=0;
				for (int ix=inicio;ix<fin ;ix++)
				{	
					if (vec_veces[ix]!=0 && m_solbest!=0)
					{
		//				total+=m_solbest-((double)vec_valor[ix]/(double)vec_veces[ix]);
//Tipo1	
//						total+=pow((double)m_solbest/(double)((double)vec_valor[ix]/(double)vec_veces[ix]),10);
//Tipo 2
						double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);
//						total+=pow((double)(meanix-peorSolucion)/(double)(m_solbest-peorSolucion),2);
						//Problema de maximizar
						total+=pow((double)(peorSolucion-meanix)/(double)(-m_solbest+peorSolucion),2);
						
					}
				}
				for (ix=inicio;ix<fin ;ix++)
				{
					if (vec_veces[ix]!=0 && m_solbest!=0)
					{
//					vec_buenas[ix]=((double)10/(double)((m_solbest-((double)vec_valor[ix]/(double)vec_veces[ix]))))*(double)total;
//Tipo1					
					//	vec_buenas[ix]=((double)total/(double)(pow((double)m_solbest/(double)((double)vec_valor[ix]/(double)vec_veces[ix]),10)));
//Tipo2
						
						double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);

						double evalix=pow((double)(peorSolucion-meanix)/(double)(-m_solbest+peorSolucion),2);
						vec_buenas[ix]=((double)evalix/(double)total)*100;
					//	
						hastavalor+=vec_buenas[ix];
					}
				}

			}

/*			if (m_iter_actual%999==0 && m_iter_actual>0 )
			{
				for (int ix=inicio;ix<fin ;ix++)
				{
					if (vec_veces[ix]!=0)
					printf("%d %d %d %f\n",ix,vec_veces[ix],vec_valor[ix],((double)vec_valor[ix]/(double)vec_veces[ix]));
				}

			}*/
/*			if (m_iter_actual%100==1 && m_iter_actual>1)
			{
				for (int ix=2;ix<10 ;ix++)
				{
					printf("%d %d\n",ix,vec_buenas[ix]);
				}

			}
*/
			m_perdida_menor=m_W*(m_solbest-1)-m_total_superficie;
			if (Reactive!=true)
			{
				alea=get_random(inicio,fin-1);
				m_FactorAleatorio=(double)alea/(double)paso;

			}
			else
			{
				alea=get_random(1,hastavalor);
				//busco cual es el que corresponde
				int suma=0;
				for (int ix=inicio;ix<fin && suma<alea;ix++)
				{	
					suma+=vec_buenas[ix];
					m_FactorAleatorio=(double)ix/(double)paso;
				}
			}
			indice=m_FactorAleatorio*paso;
		}
//		HeuristicoGreedyOrden(dibu);
		if (GetPuedenRotarsePiezasGrasp()==false)
		HeuristicoGreedyOrdenStrip(dibu);
		else
			HeuristicoGreedyOrdenStripRotacion(dibu);
//		HeuristicoGreedyStrip(dibu);
		if (m_ValSolucion<m_solbest)
		{
			m_solbest=m_ValSolucion;
			m_solbest_lista_bloques=m_lista_bloques;
			m_solbest_lista_perdidas=m_lista_perdidas;
			m_perdida_menor=(m_solbest*m_W)-m_total_superficie;
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			if (m_solbest==m_Cota) 
			{
				return m_solbest;

			}

		}
//		VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);
/*		if (m_ValSolucion>((double)7.95*(double)m_solbest))
		{
			vec_buenas[m_FactorAleatorio*10]++;
			total++;
		}
		
  */

//		DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
//En lugar de que solo mejore las que esten al 90 por ciento de la mejor

//		printf("\n%d",m_iter_actual);
		//Si no es la cota superior 
		//Sabemos que cuanto mayor es el número de piezas más probable es acercarnos a la cota
		//superior o a la mejor solución encontrada, por lo tanto este valor debería estar cerca 
		//si la solución es parecida
//		int solantes=m_ValSolucion;
//		EscribirSolucionLatex(m_lista_bloques);
				//El reactive lo pongo antés de hacer la mejora local
		if (m_ValSolucion>peorSolucion)
			peorSolucion=m_ValSolucion;
		vec_veces[indice]++;
		vec_valor[indice]+=m_ValSolucion;
//		EscribirSolucionStripLatex(m_lista_bloques);
/*		if (m_solbest==33) 
		{
			printf("Aqui Iter %d Solucion %d ", m_iter_actual, m_ValSolucion);
			for(int i=0;;);

		}
*/		int kkk=m_ValSolucion;
		if (m_ValSolucion!=maxPosible && (m_ValSolucion<=(m_solbest+((double)0.5*(double)(peorSolucion-m_solbest)))) && m_HacerMejoraLocal==true)
		{	
		if (m_ReactiveMejora==true)
		{
			if (m_iter_actual%100==0 && m_iter_actual>0 && m_solbest!=0 && m_solbest!=peorSolucion)
			{
				ReactiveMejora=true;
				total=0;
				hastavalorM=0;
				for (int ix=1;ix<5 ;ix++)
				{	
					if (vec_vecesMejora[ix]!=0 && m_solbest!=0)
					{
						double meanix=((double)vec_valorMejora[ix]/(double)vec_vecesMejora[ix]);
						//Problema de maximizar
						total+=pow((double)(peorSolucion-meanix)/(double)(-m_solbest+peorSolucion),6);
						
					}
				}
				for (ix=1;ix<5 ;ix++)
				{
					if (vec_vecesMejora[ix]!=0 && m_solbest!=0)
					{
						
						double meanix=((double)vec_valorMejora[ix]/(double)vec_vecesMejora[ix]);
						double evalix=pow((double)(peorSolucion-meanix)/(double)(-m_solbest+peorSolucion),6);
						vec_buenasMejora[ix]=((double)evalix/(double)total)*100;
						hastavalorM+=vec_buenasMejora[ix];
					}
				}

			}

			if (ReactiveMejora!=true)
			{
				m_tipo_mejora=get_random(1,4);
				

			}
			else
			{
				double v_alea=get_random(1,hastavalorM);
				//busco cual es el que corresponde
				int suma=0;
				for (int ix=1;ix<5 && suma<v_alea;ix++)
				{	
					suma+=vec_buenasMejora[ix];
					m_tipo_mejora=ix;
				}
			}
		}
//				m_tipo_mejora=get_random(1,4);
				if (m_tipo_mejora==1 )
					MejoraLocalRapidaTabuStrip();
				if (m_tipo_mejora==2 )
					MejoraLocalRapidaEPCStrip();
				if (m_tipo_mejora==3 )
					MejoraLocalRapidaStrip();
				if (m_tipo_mejora==4)
					MejoraLocalRapidaTrozoStrip();
				if (m_ValSolucion>peorSolucion)
					peorSolucion=m_ValSolucion;
				vec_vecesMejora[m_tipo_mejora]++;
				vec_valorMejora[m_tipo_mejora]+=m_ValSolucion;

//				if (iter==244 ||iter==246 || iter==552000)
//				{

//					EscribirSolucionLatex(m_lista_bloques);
//					if (m_ValSolucion==m_Cota || iter==277) 
//					{
//						printf("Aquiiiiii  %d %d",iter,m_ValSolucion);
//						exit(5);
//						DibujarSolucion(m_lista_bloques,m_lista_perdidas,iter,0);
//					}
//				}
//				}
//				}

//			}

//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

// 				VerificarSolucion(m_lista_bloques,m_lista_perdidas,m_iter_actual);

		}
//		if (m_iter_actual%250==0) printf("Iter %d\n",m_iter_actual);
//		if (kkk-m_ValSolucion<0)
//			printf(" Empeora o Igual %d\t%d\t%d\t%d\n",kkk,m_ValSolucion,m_iter_actual,kkk-m_ValSolucion);
/*		if (m_iter_actual%100==0 && m_iter_actual>0 )
		{
			for (int ix=1;ix<5 ;ix++)
			{
				if (vec_vecesMejora[ix]!=0)
				printf("%d %d %d %f\n",ix,vec_vecesMejora[ix],vec_valorMejora[ix],((double)vec_valorMejora[ix]/(double)vec_vecesMejora[ix]));
			}

		}

*/		if (m_ValSolucion<=m_solbest )
		{
			m_perdida_menor=(m_solbest*m_W)-m_total_superficie;
			m_solbest=m_ValSolucion;
			m_solbest_lista_bloques=m_lista_bloques;
			m_solbest_lista_perdidas=m_lista_perdidas;
			m_NumPiezasBestSol=ContarPiezas(m_lista_bloques);
			m_NumBloques=m_lista_bloques.size();
//			printf("SOLBEST\t%d\t%d\n",m_solbest,m_iter_actual);
			if (m_solbest==m_Cota) 
			{
				return m_solbest;

			}
		}
/*		if (m_solbest==33) 
		{
			printf("Aqui en la Mejora");
			for(int i=0;;);

		}
*/
		m_lista_perdidas.clear();
		m_lista_bloques.clear();

		
	}
	if (posi==true) m_Posible=true;
	printf("Aqui");
	printf("Numero de Piezas %d  W %d %d  Cota %d Mejor Solucion %d",m_Numpiezas,m_W,m_iter_actual,m_Cota,m_solbest);
//	EscribirSolucionStripLatex(m_solbest_lista_bloques);
//	printf("%d",m_solbest);
//	m_conpesos=false;
//	Tabu2DStrip(false,false);
	return m_solbest;
}
//Quita los ultimos rectángulo es intenta colocar algo con la función rapida
void CUTTING::MejoraLocalRapida()
{
	int num_bloques=(double)(0.5)*m_lista_bloques.size();
	//quito los num_bloques últimos
	std::list<BLOQUE>::iterator itB;
	int contador=0;
	itB=m_lista_bloques.begin();
	do{
		contador++;
		if (contador>num_bloques)
		{
			CRect Rect((*itB));
			//Meto la nueva pérdida
			m_lista_perdidas.push_back(Rect);
			//Quito el bloque viejo
			m_ValSolucion-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho))*(m_Piezas[(*itB).GetNumero()].valor);
			m_Piezas[(*itB).GetNumero()].num-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho));
			itB=m_lista_bloques.erase(itB);
		}
		else itB++;
	}while (itB!=m_lista_bloques.end());
	//LLamos a la función determinista del heurístico
	JuntarPerdida(m_lista_perdidas,'P');
	Rellenar(m_lista_bloques,m_lista_perdidas,99999);
	
	int sol=ContarSolucion(m_lista_bloques);
	if (sol>m_solbest) m_ValSolucion=sol;
}
/*
//Quita el último rectángulo y lo cambia por otro igual de ancho pero más pequeño
void CUTTING::MejoraLocalRapidaIntercambio()
{
	int num_bloques=(double)(0.5)*m_lista_bloques.size();
	//quito los num_bloques últimos
	std::list<BLOQUE>::iterator itB;
	int contador=0;
	itB=m_lista_bloques.begin();
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
		if ((*itB).right==m_ValSolucion)
		{
			CRect Rect((*itB));
			contador++;
		}
	}
	if (contador==1)
	{
	//LLamos a la función determinista del heurístico
	JuntarPerdida(m_lista_perdidas,'P');
	Rellenar(m_lista_bloques,m_lista_perdidas,99999);
	
	int sol=ContarSolucion(m_lista_bloques);
	if (sol>m_solbest) m_ValSolucion=sol;
}*/
//Quita los ultimos rectángulo es intenta colocar algo con la función rapida
void CUTTING::MejoraLocalRapidaStrip()
{
	
	int min=99999;
	int sol4=0;
	//quito los num_bloques últimos si no es mejor quito más bloques
	std::list<BLOQUE>::iterator itB;
	do
	{
	int num_bloques=(double)(0.6)*m_lista_bloques.size();
	int contador=0,contador2=0;
	itB=m_lista_bloques.begin();
	do{
		contador++;
		if (contador>num_bloques)
		{
			CRect Rect((*itB));
			if (Rect.right<min) min=Rect.right;
			//Meto la nueva pérdida
			m_lista_perdidas.push_back(Rect);
			contador2++;
			//Quito el bloque viejo
	//		m_ValSolucion-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho))*(m_Piezas[(*itB).GetNumero()].valor);
			m_Piezas[(*itB).GetNumero()].num-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho));
			itB=m_lista_bloques.erase(itB);
		}
		else itB++;

	}while (itB!=m_lista_bloques.end());
//	printf("quito %d de %d\n",contador2,kk);
	sol4=ContarSolucionStrip(m_lista_bloques);
//Cambiar
	}while (sol4>=m_solbest);
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	
	//Llamo a función bloques hacia las esquinas
//	Bloques_Hacia_Las_EsquinasStrip(m_lista_bloques,m_lista_perdidas,min);
	//LLamos a la función determinista del heurístico
	int guartipo=m_tipo;
	JuntarPerdida(m_lista_perdidas,'H');
	if (ContarPerdidaSegura(m_lista_perdidas)>((m_solbest-1)*m_W-m_total_superficie)) 
		return;
	m_tipo=2;
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	RellenarStrip();
	m_tipo=guartipo;
	int sol=ContarSolucionStrip(m_lista_bloques);
	if (sol<m_solbest) 
	{
		m_solbest=sol;
		m_ValSolucion=sol;
	}
}
//Otra mejora quito los últimos y intento meter todas las piezas en un rectángulo cerrado 
//más pequeño de la solución actual
//Quita los ultimos rectángulo es intenta colocar algo con la función rapida
void CUTTING::MejoraLocalRapidaTabuStrip()
{
	
	int min=99999;
	int sol4=0;
	//quito los num_bloques últimos si no es mejor quito más bloques
	std::list<BLOQUE>::iterator itB;
	int contador2=0;
	bool conseguido=false;
	do
	{
		conseguido=false;
	do
	{
	int num_bloques=(double)(0.8)*m_lista_bloques.size();
	int contador=0;
	itB=m_lista_bloques.begin();
	do{
		contador++;
		if (contador>num_bloques)
		{
			CRect Rect((*itB));
			if (Rect.right<min) min=Rect.right;
			//Meto la nueva pérdida
			m_lista_perdidas.push_back(Rect);
			contador2++;
			//Quito el bloque viejo
	//		m_ValSolucion-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho))*(m_Piezas[(*itB).GetNumero()].valor);
			m_Piezas[(*itB).GetNumero()].num-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho));
			itB=m_lista_bloques.erase(itB);
		}
		else itB++;

	}while (itB!=m_lista_bloques.end());
	sol4=ContarSolucionStrip(m_lista_bloques);

	}while (sol4>=m_solbest);

	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	JuntarPerdida(m_lista_perdidas,'H');
	if (ContarPerdidaSegura(m_lista_perdidas)>((m_solbest-1)*m_W-m_total_superficie)) 
		return;

	ActualizarMinMax();

	//Llamo a función bloques hacia las esquinas
//	Bloques_Hacia_Las_EsquinasStrip(m_lista_bloques,m_lista_perdidas,min);
	//LLamos a la función determinista del heurístico
//	printf("quito %d de %d\n",contador2,kk);

	std::list<RECTAN> ::iterator it;
	it=m_lista_perdidas.begin();
	do{

		if ((*it).right==m_L ||(*it).right>(m_solbest-1)) 
			(*it).right=(m_solbest-1);
		if ((*it).left==(m_solbest-1))
			it=m_lista_perdidas.erase(it);
		else it++;
	}while (it!=m_lista_perdidas.end());
	int mLguardo=m_L;
	int tipoguardo=m_tipo;
	m_tipo=4;
	m_L=m_solbest-1;
//	Bloques_Hacia_Las_Esquinas(m_lista_bloques,m_lista_perdidas);
	JuntarPerdida(m_lista_perdidas,'P');
	m_Determinista=true;
	Rellenar(m_lista_bloques,m_lista_perdidas,99999);
	m_Determinista=false;
	m_L=mLguardo;
	m_tipo=tipoguardo;
	int sol=ContarSolucion(m_lista_bloques);
//	EscribirSolucionStripLatex(m_lista_bloques);
//	printf("Iter %d Sol %d Cota %d\n",m_iter_actual,sol,m_total_superficie);
	if (sol==m_total_superficie)
	{
		m_ValSolucion=m_solbest-1;
		m_solbest--;
		conseguido=true;
	}
	}while(conseguido==true);
//	m_ValSolucion=ContarSolucion(m_lista_bloques);
}
//Quita los ultimos rectángulo es intenta colocar algo con la función rapida
void CUTTING::MejoraLocalRapidaTrozoStrip()
{
	
	int min=99999;
	int sol4=0;
	//quito los num_bloques últimos si no es mejor quito más bloques
	std::list<BLOQUE>::iterator itB;
	//BUENO
//	int tope=(0.8)*m_solbest;
	int tope=(0.6)*m_solbest;
	
	//Todo lo que se encuentre en esta franja lo quito
	int contador=0;
	itB=m_lista_bloques.begin();
	do{
		if ((*itB).right>=tope)
		{
			CRect Rect((*itB));
			if (Rect.right<min) min=Rect.right;
			//Meto la nueva pérdida
			m_lista_perdidas.push_back(Rect);
			contador++;
			//Quito el bloque viejo
	//		m_ValSolucion-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho))*(m_Piezas[(*itB).GetNumero()].valor);
			m_Piezas[(*itB).GetNumero()].num-=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho));
			itB=m_lista_bloques.erase(itB);
		}
		else itB++;

	}while (itB!=m_lista_bloques.end());
	sol4=ContarSolucionStrip(m_lista_bloques);
//	printf("quito %d de %d\n",contador,kk);

	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

	//Llamo a función bloques hacia las esquinas
//	Bloques_Hacia_Las_EsquinasStrip(m_lista_bloques,m_lista_perdidas,min);
	//LLamos a la función determinista del heurístico

	JuntarPerdida(m_lista_perdidas,'H');
	if (ContarPerdidaSegura(m_lista_perdidas)>((m_solbest-1)*m_W-m_total_superficie)) 
		return;

	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	RellenarStrip();
	
	int sol=ContarSolucionStrip(m_lista_bloques);
	if (sol<m_solbest) 
	{
		m_solbest=sol;
		m_ValSolucion=sol;
	}
}
//tienen que  pérdidas cerradas
void CUTTING::MejoraLocalRapidaEPCStrip()
{
	
	bool existepc=false;
	std::list<RECTAN>::iterator itB;
	std::list<BLOQUE>::iterator itBlo;
	std::list<RECTAN>::iterator itRec;

	for(itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
		if ((*itB).right!=m_L) 
		{
			existepc=true;
			break;
		}
	}
	//Si no existe pérdida hago una simetría y seguro que existira
	if (existepc!=true)
	{
		//Hago una solución que es simétrica de los dos ejes
		//Simetrica pero tambien debo hacer simetricas las perdidas
		for (itBlo=m_lista_bloques.begin();itBlo!=m_lista_bloques.end();itBlo++)
		{
			int kk=(*itBlo).Width();
			(*itBlo).left=m_ValSolucion-(*itBlo).left-(*itBlo).Width();
			(*itBlo).right=(*itBlo).left+kk;
		}
		for (itRec=m_lista_perdidas.begin();itRec!=m_lista_perdidas.end();itRec++)
		{
			if ((*itRec).right!=m_L)
			{
			int kk=(*itRec).Width();
			(*itRec).left=m_ValSolucion-(*itRec).left-(*itRec).Width();
			(*itRec).right=(*itRec).left+kk;
			}
			else
			{
			int kk=(*itRec).Width()-(m_L-m_ValSolucion);
			(*itRec).left=m_ValSolucion-(*itRec).left-kk;
			(*itRec).right=(*itRec).left+kk;
			}

		}
		RECTAN PTotal(m_ValSolucion,0,m_L,m_W);
		m_lista_perdidas.push_back(PTotal);

		
	}
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	//Llamo a función bloques hacia las esquinas
//	Bloques_Hacia_Las_EsquinasStrip(m_lista_bloques,m_lista_perdidas,0);
	//LLamos a la función determinista del heurístico

	JuntarPerdida(m_lista_perdidas,'H');
	if (ContarPerdidaSegura(m_lista_perdidas)>(m_solbest*m_W-m_total_superficie)) 
		return;

	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	int maxBloqueAncho=0,bloque_seleccionado=0,cuans=0;
	//Busco el bloque mayor para meterlo en el hueco
	for (itBlo=m_lista_bloques.begin();itBlo!=m_lista_bloques.end();itBlo++)
	{
		if ((*itBlo).right==m_ValSolucion)
		{
			if ((*itBlo).Width()>maxBloqueAncho)
			{
				maxBloqueAncho=(*itBlo).Width();
				bloque_seleccionado=(*itBlo).GetNumero();
				cuans=(*itBlo).Height()/m_Piezas[(*itBlo).GetNumero()].ancho;


			}
		}

	}
	m_Piezas[bloque_seleccionado].num-=cuans;
	for (itBlo=m_lista_bloques.begin();itBlo!=m_lista_bloques.end();itBlo++)
	{
		if ((*itBlo).GetNumero()==bloque_seleccionado && (*itBlo).right==m_ValSolucion)
		{
			CRect Rect((*itBlo));
			//Meto la nueva pérdida
			m_lista_perdidas.push_back(Rect);
			itBlo=m_lista_bloques.erase(itBlo);
			break;
		}
	}
	JuntarPerdida(m_lista_perdidas,'H');
	Aumentar_Bloques_UnaPerdidaStrip(bloque_seleccionado,cuans);
//	EscribirSolucionStripLatex(m_lista_bloques);
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	RellenarStrip();
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
	int sol=ContarSolucionStrip(m_lista_bloques);
	if (sol<m_solbest) 
	{
		m_solbest=sol;
		printf("Mejora EPC");
		m_ValSolucion=sol;
	}

}
void CUTTING::MejoraLocal()
{
//	if (m_HacerMejoraLocal!=true) return;
	//Vamos a intentar mejorar localmente los resultados de cada iteración mediante 
	//la eliminación de una pieza e intentar colocar alguna de las restantes en la solución
//	++;
//	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

	std::list<BLOQUE>::iterator itB;
	bool he_metido_algo=false;
	int cuenta=0,max=0;
	do
	{
		cuenta=0;
		he_metido_algo=false;
		for(itB=m_lista_bloques.begin();he_metido_algo!=true && itB!=m_lista_bloques.end();itB++)
		{
		 cuenta++;
//		 BLOQUE b1=(*itB);
		 
//			if (cuenta<=max) continue;
//			printf("%d",cont);
			//Solo voy a quitar de las menos valiosas 
//			if ((*itB).GetNumero()<=(0.2*m_Numpiezas)) continue;
			//Si es restringido solo intentar quitar las que se puedan
			if ((m_Restringido==true && (m_Piezas[(*itB).GetNumero()].num-m_Piezas[(*itB).GetNumero()].min)>=0) || (m_Restringido==false))
			{
				// printf("Entro 3 ");

				int cerca_perdidas=BloqueCercaPerdidas((*itB),0);
							// printf("Salgo 3 ");
				if (cerca_perdidas==1)
				{

					BLOQUE b2=(*itB);
					for (register int i=1;he_metido_algo!=true && i<=((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo) ;i++)
					{
						for (register int j=1;he_metido_algo!=true && j<=((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho) ;j++)
						{
//							printf("%d %d ",i,j);
							// printf("Entro 1 ");
							he_metido_algo=Disminuir_Bloques((*itB),i,j);
							if (he_metido_algo==true) max=cuenta;
/*							if (he_metido_algo==true )
							{
								int sol=ContarSolucion(m_lista_bloques);
								if (sol>m_solbest)
								{

									FILE *fin;
									fin=fopen("Solcut.txt","a+");


									if (m_iter_actual>10)
		
										fprintf(fin,"\n%d %d %d %d %d",m_ValSolucion-solanterior,m_iter_actual,b1.Width(),b1.Height(),b1.GetNumero());
									int casa=10;
									fclose(fin);
								}
							}
*/
//							VerificarSolucion(m_lista_bloques,m_lista_perdidas,8);
							// printf("Salgo 1 ");
						}
					}
				}
//				else
//					int perro=6;
			}
		}
	}while(he_metido_algo==true);
	
}
void CUTTING::PiezasNoPosiblesEnSolMejor(int sb)
{
	if (m_Restringido==true) return;
	//Dada una solución es posible eliminar algunas piezas ya que ellas producirán una
	//solución peor que la mejor encontrada ya
	double PiezaMaxValiosa=(double)m_Piezas[0].valor/(double)(m_Piezas[0].largo*m_Piezas[0].ancho);
	double PiezaMinValiosa=(double)m_Piezas[m_Numpiezas-1].valor/(double)(m_Piezas[m_Numpiezas-1].largo*m_Piezas[m_Numpiezas-1].ancho);
	if (PiezaMaxValiosa==PiezaMinValiosa) return;
	printf("perro");
	//Si pudiera llenar todo el tablero con piezas de las mas valiosas
	int llenar=(m_L*m_W)*PiezaMaxValiosa;
	std::vector<PIEZA> ::iterator it;
	for (it=m_Piezas.begin();it!=m_Piezas.end();it++)
	{
		bool no_borra=false;
		//Si no es una pieza necesaria
		if ((*it).min==0)
		{
			double valpieza=(double)(*it).valor/(double)((*it).largo*(*it).ancho);
			if (valpieza<PiezaMaxValiosa )
			{
	//			También sirve para hacer reducciones en las cotas parciales			
				for (register int k=1;k<=(*it).max;k++)
				{
					if ((llenar-(((*it).largo*(*it).ancho*k)*(PiezaMaxValiosa-(valpieza))))<=sb)
					{
						if (k==1)
						{
							m_Q-=(*it).max;
							it=m_Piezas.erase(it);
							no_borra=true;
							m_Numpiezas--;
							break;
						}
						else
						{
							m_Q--;
							(*it).max=k-1;
							break;
						}
						
					}
				}

			}
		}
		if (it==m_Piezas.end()) break;
		if (no_borra==true) it--;

	}
}
int CUTTING::CotaInferiorArchivoStrip(void)		
{
	FILE *salidadatos;
	char nombre[60];
	int Cota1;
//	printf("%s",m_Nombre);
	salidadatos=fopen("CotaInferiorStrip.txt","r");
	if (salidadatos==NULL)
	{
		printf("Problemas al leer el archivo de la cota inferior");
//		exit(4);
		return 0;
	}
	while (!feof(salidadatos))
	{
		fscanf(salidadatos,"%s %d",nombre,&Cota1);
		if (_stricmp(nombre,m_Nombre)==0) 
		{
			fclose(salidadatos);
			return Cota1;
		}
	}
	fclose(salidadatos);
	return 0;
}
int CUTTING::CotaSuperiorArchivo(void)		
{
	FILE *salidadatos;
	char nombre[30];
	int Cota1;
//	printf("%s",m_Nombre);
	salidadatos=fopen("CotaSuperior.txt","r");
	if (salidadatos==NULL)
	{
		printf("Problemas al leer el archivo de la cota superior");
		exit(4);
	}
	while (!feof(salidadatos))
	{
		fscanf(salidadatos,"%s %d",nombre,&Cota1);
		if (_stricmp(nombre,m_Nombre)==0) 
		{
			fclose(salidadatos);
			return Cota1;
		}
	}
	fclose(salidadatos);
	return 0;
}
bool CUTTING::Disminuir_Bloques(BLOQUE &B1,int x,int y)
{
	BLOQUE B1Dismi(0,0,0,0,B1.GetTipo());
	//Estudio por donde es mejor dividirlo derecha o izquierda o 
	//arriba o abajo
	//Según donde termine el bloque lo disminuyo 
	//para un lado o para el otro
	BLOQUE B2(B1);
	B2.SetNumero(B1.GetNumero());
	int l,w;
	std::list<RECTAN> NuevasPerdidas;
	std::list<BLOQUE> Lista_Bloques;
	RECTAN RectTemp;
	int Quito=0,Meto=0;	
	l=m_Piezas[B1.GetNumero()].largo;
	w=m_Piezas[B1.GetNumero()].ancho;
	if (x==y) 
	{
		if (B1.Width()==l) x=0;
		else y=0;
	}
	if (x>y)
	{
		y=0;
	}
	if (y>x)
	{
		x=0;
	}

	B1Dismi.BottomRight()=B1.BottomRight();
	B1Dismi.TopLeft()=B1.TopLeft();
	B1Dismi.SetTipo(B1.GetTipo());
	B1Dismi.SetNumero(B1.GetNumero());
	if (x==0 || y==0)
	{
		if (x>0)
		{
			Quito=x*(m_Piezas[B1.GetNumero()].valor*(B1.Height()/m_Piezas[B1.GetNumero()].ancho));
			B1Dismi.BottomRight().x=B1.BottomRight().x-(x*l);
		}
		if (y>0)
		{
			Quito=y*(m_Piezas[B1.GetNumero()].valor*(B1.Width()/m_Piezas[B1.GetNumero()].largo));

			B1Dismi.BottomRight().y=B1.BottomRight().y-(y*w);
		}
	}

	SubtractRect(&RectTemp,&B1,&B1Dismi);
	if (!RectTemp.IsRectEmpty()) NuevasPerdidas.push_back(RectTemp);
	
	std::list<RECTAN>::iterator itC;
	std::list<BLOQUE> lista_temp_bloques;
	std::list<BLOQUE> :: iterator itLK;
	lista_temp_bloques.insert(lista_temp_bloques.begin(),m_lista_bloques.begin(),m_lista_bloques.end());

	if (!B1Dismi.IsRectEmpty()) lista_temp_bloques.push_back(B1Dismi);
	itLK=lista_temp_bloques.begin();
	do{
		if ((*itLK).top==B1.top && (*itLK).bottom==B1.bottom && (*itLK).left==B1.left && (*itLK).right==B1.right) 
		{
			itLK=lista_temp_bloques.erase(itLK);
			continue;
		}
		itLK++;

	}while(itLK!=lista_temp_bloques.end());
	NuevasPerdidas.insert(NuevasPerdidas.end(),m_lista_perdidas.begin(),m_lista_perdidas.end());
//	int kk4=ContarSolucion(lista_temp_bloques);

// Antiguo más costoso
	if (m_tipo_mejora==1)
	{
		Bloques_Hacia_Las_Esquinas(lista_temp_bloques,NuevasPerdidas);
	//	DibujarSolucion(lista_temp_bloques,NuevasPerdidas,m_ValSolucion,0);
		JuntarPerdida(NuevasPerdidas,'X');
	}
	else
	{
		//Nuevo menos costoso

		int num=JuntarPerdida(NuevasPerdidas,B2,'P');
		//Si no he jutado para colocar alguna pieza mayor  en importancia
		//entonces no junto ni intento rellenar
		int imp=B2.GetNumero();
		int imp2=MAX_IMPORTANCIA;
		if ((imp2 - imp)>num)
			return false;
	}
	// printf("Entro 4");
	Rellenar(Lista_Bloques,NuevasPerdidas,B1.GetNumero());
	// printf("Salgo 4");

	Meto=ContarSolucion(Lista_Bloques);
	if ((Meto-Quito)>0) 
	{

		m_ValSolucion+=(Meto-Quito);
		//Poner el numero correcto de este tipo
		m_Piezas[B1.GetNumero()].num-=(x+y);
		m_lista_perdidas.clear();
		m_lista_perdidas.insert(m_lista_perdidas.begin(),NuevasPerdidas.begin(),NuevasPerdidas.end());
		Bloques_Hacia_Las_Esquinas(lista_temp_bloques,m_lista_perdidas);
		m_lista_bloques.clear();
		m_lista_bloques.insert(m_lista_bloques.begin(),Lista_Bloques.begin(),Lista_Bloques.end());
		m_lista_bloques.insert(m_lista_bloques.begin(),lista_temp_bloques.begin(),lista_temp_bloques.end());

//		VerificarSolucion(m_lista_bloques,m_lista_perdidas,9);
		return true;
	}
	else
	{

		//Poner los números correctos de piezas de estos tipos
		RepararNumeros(Lista_Bloques);
		return false;
	}
}
MOVE CUTTING::Disminuir_Bloques_Tabu(BLOQUE &B1,int x,int y)
{
	BLOQUE B1Dismi(0,0,0,0,B1.GetTipo());
	B1Dismi.SetTipo('D');
	B1.SetTipo('D');
	//Estudio por donde es mejor dividirlo derecha o izquierda o 
	//arriba o abajo
	//Según donde termine el bloque lo disminuyo 
	//para un lado o para el otro
	BLOQUE B2(B1);
	B2.SetNumero(B1.GetNumero());
	int l,w;
	std::list<RECTAN> NuevasPerdidas;
	std::list<BLOQUE> Lista_Bloques;
	RECTAN RectTemp;
	int PiezasQuito=0,Quito=0,Meto=0;	
	l=m_Piezas[B1.GetNumero()].largo;
	w=m_Piezas[B1.GetNumero()].ancho;
	if (x==y) 
	{
		if (B1.Width()==l) x=0;
		else y=0;
	}
	if (x>y)
	{
		y=0;
	}
	if (y>x)
	{
		x=0;
	}

	B1Dismi.BottomRight()=B1.BottomRight();
	B1Dismi.TopLeft()=B1.TopLeft();
	B1Dismi.SetTipo(B1.GetTipo());
	B1Dismi.SetNumero(B1.GetNumero());

	if (x==0 || y==0)
	{
		if (x>0)
		{
			PiezasQuito=x*(B1.Height()/m_Piezas[B1.GetNumero()].ancho);
			Quito=PiezasQuito*(m_Piezas[B1.GetNumero()].valor);
			B1Dismi.BottomRight().x=B1.BottomRight().x-(x*l);
		}
		if (y>0)
		{
			PiezasQuito=y*(B1.Width()/m_Piezas[B1.GetNumero()].largo);
			Quito=PiezasQuito*(m_Piezas[B1.GetNumero()].valor);

			B1Dismi.BottomRight().y=B1.BottomRight().y-(y*w);
		}

	}

	SubtractRect(&RectTemp,&B1,&B1Dismi);
	if (!RectTemp.IsRectEmpty()) NuevasPerdidas.push_back(RectTemp);
	
	std::list<RECTAN>::iterator itC;
	std::list<BLOQUE> lista_temp_bloques;
	std::list<BLOQUE> :: iterator itLK;
	NuevasPerdidas.insert(NuevasPerdidas.end(),m_lista_perdidas.begin(),m_lista_perdidas.end());
	if (!B1Dismi.IsRectEmpty()) 
	{
		lista_temp_bloques.push_back(B1Dismi);
//		Bloques_Hacia_Las_Esquinas(lista_temp_bloques,NuevasPerdidas);
	}

	lista_temp_bloques.insert(lista_temp_bloques.begin(),m_lista_bloques.begin(),m_lista_bloques.end());

	itLK=lista_temp_bloques.begin();
	do{
		if ((*itLK).top==B1.top && (*itLK).bottom==B1.bottom && (*itLK).left==B1.left && (*itLK).right==B1.right) 
		{
			itLK=lista_temp_bloques.erase(itLK);
			continue;
		}
		itLK++;

	}while(itLK!=lista_temp_bloques.end());
//	int kk4=ContarSolucion(lista_temp_bloques);
//	if ((B1.top==9 && B1.bottom==40 && B1.left==60 && B1.right==70) &&
//	(B1Dismi.top==9 && B1Dismi.bottom==9 && B1Dismi.left==60 && B1Dismi.right==70) && m_iter_actual==89)
//		int perro=9;
// Antiguo más costoso
//Costosa
//	DibujarSolucion(lista_temp_bloques,NuevasPerdidas,0,0);
	int alea=get_random(0,4);
	if (alea<=3)
	Bloques_Hacia_Las_Esquinas(lista_temp_bloques,NuevasPerdidas);
	//Puedo decir que si el bloque esta pegado a alguna de las esquinas junte bien
/*
	if ((B1.top==0 && B1.left==0) &&
		(B1.bottom==m_W && B1.left==0) &&
		(B1.top==0 && B1.right==m_L) &&
		(B1.bottom==m_W && B1.right==m_L) )
	m_noquiero=99999;
	else */
	Quito=m_sol_actual;

	m_noquiero=B1.GetNumero();
	int suer=get_random(0,1);
	if (suer<=0)
		JuntarPerdida(NuevasPerdidas,'P');
//	DibujarSolucion(lista_temp_bloques,NuevasPerdidas,1,1);
	if (suer==1)
		JuntarPerdida(NuevasPerdidas,'X');
	// printf("Entro 4");
/*	if ((B1.top==0 && B1.left==0) &&
		(B1.bottom==m_W && B1.left==0) &&
		(B1.top==0 && B1.right==m_L) &&
		(B1.bottom==m_W && B1.right==m_L) )
	Rellenar(Lista_Bloques,NuevasPerdidas,99999);
	else*/
		Rellenar(Lista_Bloques,NuevasPerdidas,B1.GetNumero());
	std::list<BLOQUE>::iterator itB2;
	bool metida=false;
	if (Lista_Bloques.size()>0)
	{  // printf("Si puede meter1");
/*		std::list<BLOQUE> Lista_Bloques2;
		m_noquiero=999999;
		JuntarPerdida(NuevasPerdidas,'P');

		Rellenar(Lista_Bloques2,NuevasPerdidas,99999);
		if (Lista_Bloques2.size()>0) printf("Si puede meter");
		Lista_Bloques.insert(Lista_Bloques.begin(),Lista_Bloques2.begin(),Lista_Bloques2.end());
*/		metida=true;
	}
	MOVE movimiento(B1,B1Dismi,Lista_Bloques,(Meto-Quito),NuevasPerdidas);
	m_noquiero=99999;
	RepararNumeros(movimiento.GetListaBloques());
	Meto=ContarSolucion(movimiento.GetListaBloques())+ContarSolucion(lista_temp_bloques);
	movimiento.SetValor(Meto-Quito);
	movimiento.GetListaBloques().insert(movimiento.GetListaBloques().begin(),lista_temp_bloques.begin(),lista_temp_bloques.end());
	int temporal=0;
	temporal=EvaluarMovimiento(movimiento);
	if (temporal<m_max_valor && (m_sol_actual+movimiento.GetValor()<m_solbest))
	{
		movimiento.SetAlgoNuevo(false);
		return movimiento;
	}
//Costosa
	if (m_sol_actual+movimiento.GetValor()>=m_solbest)
	{
		Bloques_Hacia_Las_Esquinas(movimiento.GetListaBloques(),movimiento.GetListaPerdidas());
//		printf("Paso POR AQUI");
		ColocarNumeros(movimiento.GetBloquesNuevos());
		if (metida==false)
		{
			m_noquiero=B1.GetNumero();
		}
		JuntarPerdida(movimiento.GetListaPerdidas(),'P');
		if (metida==true) Rellenar(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),99999);
		if (metida==false) Rellenar(movimiento.GetBloquesNuevos(),movimiento.GetListaPerdidas(),B1.GetNumero());
		m_noquiero=99999;

		int Meto2=ContarSolucion(movimiento.GetListaBloques());
//		VerificarSolucion(movimiento.GetListaBloques(),movimiento.GetListaPerdidas(),2514);
		ColocarNumeros(m_lista_bloques);
		movimiento.SetValor(Meto2-Quito);


	}//	CompactarBloques(movimiento);
	//Intensificar cuando estemos cerca de la solución intento ajustar más

	return movimiento;

}
void CUTTING::Actualizar_Lista_Bloques(MOVE &BestMove)
{
	//SI es de Aumentar incluir también el 
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

	m_lista_bloques.clear();
//	printf("AB2 %3d",BestMove.GetListaBloques().size());
	m_lista_bloques.insert(m_lista_bloques.begin(),BestMove.GetListaBloques().begin(),BestMove.GetListaBloques().end());
//	printf("AB3");
	for (int ki=0;ki<m_Numpiezas;ki++) 
		m_Piezas[ki].num=0;
	//Actualizar números
	for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
		//Reponemos los números de las piezas
		m_Piezas[(*itB).GetNumero()].num+=((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho);
	}

}
void CUTTING::Add_Lista_Tabu(BLOQUE &B1)
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
void CUTTING::Add_Lista_Tabu(MOVE &M1)
{
/*
	bool mov_aumentar=false;
	if ((M1.GetBloqueAntiguo().TopLeft()==M1.GetBloqueNuevo().TopLeft()) && 
	(M1.GetBloqueAntiguo().BottomRight()==M1.GetBloqueNuevo().BottomRight()))
		mov_aumentar=true;
	if (mov_aumentar==true)
	{
		std::list<BLOQUE> ::iterator itB;
		if (m_lista_tabu_aumen.size()>m_tam_tabu)
		{
			m_lista_tabu_aumen.pop_front();
			m_lista_tabu_aumen.push_back(M1.GetBloqueAntiguo());
		}
		else
		{
			m_lista_tabu_aumen.push_back(M1.GetBloqueAntiguo());

		}
	}
	else
	{
		std::list<BLOQUE> ::iterator itB;
		if (m_lista_tabu.size()>m_tam_tabu)
		{
			m_lista_tabu.pop_front();
			m_lista_tabu.push_back(M1.GetBloqueAntiguo());
		}
		else
		{
			m_lista_tabu.push_back(M1.GetBloqueAntiguo());

		}

	}*/
		std::list<BLOQUE> ::iterator itB;
		if (m_lista_tabu.size()>m_tam_tabu)
		{
			m_lista_tabu.pop_front();
			m_lista_tabu.push_back(M1.GetBloqueAntiguo());
		}
		else
		{
			m_lista_tabu.push_back(M1.GetBloqueAntiguo());

		}

}
int CUTTING::EsTabu(MOVE &M1)
{
//	return false;
	m_totalmov++;
	if (m_lista_tabu.size()==0) return 9999;

	//Si movimiento es de aumentar 
	
	//no quiero que haya sido un bloque reducido


//	return 9999;
	//Quiero que todos los movimientos aparecido sigan en la solución
	//si el movimiento es de disminuir 
	//no quiero que sea un movimiento de aumentar
	std::list<BLOQUE> ::iterator itB,itB1;
	int max=m_lista_tabu.size()+1;
	bool es_tabu=false;
	int mayor=9999;
	for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
	{
		max--;
		if ((*itB).GetTipo()=='D') continue;
		BLOQUE b=(*itB);
		bool esta=false;
		for (itB1=M1.GetListaBloques().begin();itB1!=M1.GetListaBloques().end() ;itB1++)
		{
			
			//Si el bloque es de ancho o largo como el pallet entonces solo importa el
			//tamaño para ser tabu
			if ((*itB1).GetNumero()==(*itB).GetNumero()) 
					esta=true;
		}
		if (esta==false) 
		{
			es_tabu=true;
			if (max<mayor) 	mayor=max;
		}
	}			
	if (es_tabu==true) return mayor;
//	for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
	max=m_lista_tabu.size();
	for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end() && M1.GetBloqueAntiguo().GetTipo()=='A' ;itB++)
	{
		
		//Lo quite porque puede volver a aparecer el mismo sustituiendose
//		if ((*itB).GetTipo()==M1.GetBloqueAntiguo().GetTipo()) continue;
//		if (((*itB).GetNumero()==M1.GetBloqueAntiguo().GetNumero()) && (*itB).Height()==M1.GetBloqueAntiguo().Height() && M1.GetBloqueAntiguo().Width()==(*itB).Width())
//			return max;
//		if (((*itB).GetNumero()==M1.GetBloqueAntiguo().GetNumero()) && (*itB).Height()==M1.GetBloqueAntiguo().Height() && M1.GetBloqueAntiguo().Width()==(*itB).Width())
//			return max;
		if (((*itB).GetNumero()==M1.GetBloqueAntiguo().GetNumero()) && (*itB).TopLeft()==M1.GetBloqueAntiguo().TopLeft() && M1.GetBloqueAntiguo().BottomRight()==(*itB).BottomRight())
			return max;
		max--;
	}
/*	if (M1.GetBloqueAntiguo().GetTipo()=='A')
	{
		m_movtabu++;
		return 9999;
	}*/
/*	for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
	{
		if ((*itB).GetTipo()=='D') continue;
		if (((*itB).GetNumero()==M1.GetBloqueAntiguo().GetNumero()) && (*itB).TopLeft()==M1.GetBloqueAntiguo().TopLeft() && M1.GetBloqueAntiguo().BottomRight()==(*itB).BottomRight())
			return true;
	}*/
//	max=m_lista_tabu.size();
	//No quiero disminuir un bloque que ya he aumentado o disminuido
/*	for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end() && M1.GetBloqueNuevo().GetTipo()=='D';itB++)
	{
		
		//Lo quite porque puede volver a aparecer el mismo sustituiendose
//		if ((*itB).GetTipo()=='A') continue;
		if (((*itB).GetNumero()==M1.GetBloqueAntiguo().GetNumero()) && (*itB).Height()==M1.GetBloqueAntiguo().Height() && M1.GetBloqueAntiguo().Width()==(*itB).Width())
			return max;
		max--;
	}
*/
	//Tampoco quiero que pueda aparecer uno de los que he disminuido
	//Puede ser que al mover los bloques hacia
	//las esquinas aparezca uno que no
	//quería que apareciese, que hago????
	
	for (itB1=M1.GetListaBloques().begin();itB1!=M1.GetListaBloques().end();itB1++)
	{
		max=m_lista_tabu.size()+1;
		for (itB=m_lista_tabu.begin();itB!=m_lista_tabu.end();itB++)
		{
			max--;
			if ((*itB).GetTipo()=='A') continue;
			BLOQUE b1=(*itB1);
			BLOQUE b2=(*itB);

			//Si el bloque es de ancho o largo como el pallet entonces solo importa el
			//tamaño para ser tabu
			if ((*itB1).Width()==m_L || (*itB1).Height()==m_W)
			{
				if (((*itB1).GetNumero()==(*itB).GetNumero()) && ((*itB1).Width()==(*itB).Width()) && ((*itB1).Height()==(*itB).Height()))
					return max;
			}
			else
			{
				//No quiero que aparezca por la misma zona
	/*			if ((*itB1).GetNumero()==(*itB).GetNumero() && (*itB1).Width()==(*itB).Width() && (*itB1).Height()==(*itB).Height())
				{
					if ((*itB1).top<=((*itB).top+(m_L/200)) && (*itB1).top>=((*itB).top-(m_L/200)))
					{
						if ((*itB1).left<=((*itB).left+(m_W/200)) && (*itB1).left>=((*itB).left-(m_W/200)))
						{
							return max;

						}
					}
				}
*/
				if (((*itB1).GetNumero()==(*itB).GetNumero()) && (*itB1).TopLeft()==(*itB).TopLeft() && (*itB1).BottomRight()==(*itB).BottomRight())
					return max;
			}

		}
	}
	m_movtabu++;

//	m_movtabu++;
	return 9999;
}
//Es este procedimiento la idea es ir metiendo bloques de los ás eficientes en la solución
/*
bool CUTTING::AumentarBloques()
{
	return true;
}
*/
void CUTTING::Rellenar(std::list<BLOQUE> &listaB,std::list<RECTAN> &lista,int con_este_numero_no)
{
	/*
	//Tengo que rellenar otra vez ese rectángulo pero con piezas diferentes
	//de la que he quitado 
	//Contador desde donde debe empezar a mirar meter alguna
	//Coloca la variable para dibujar o no las soluciones
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	//Limpio la lista de perdidas
	//Al principio todo el tablero es perdida

	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;
		
		//Construyo rectángulos de pérdida 
		for (it=lista.begin();pueda_meter_piezas!=true && it!=lista.end() ;it++)
		{

			BLOQUE b1(0,0,0,0);
				// printf("Entro 5");
	//		if (m_Determinista==true)
//			int alea=get_random(0,1);
//			if (alea==1) ElegirPieza(b1,(*it),2,con_este_numero_no);
//			else ElegirPieza(b1,(*it),1,con_este_numero_no);
			if (m_tipo==1) ElegirPieza(b1,(*it),1,con_este_numero_no);
			if (m_tipo==2) ElegirPieza(b1,(*it),2,con_este_numero_no);
			if (!b1.IsRectEmpty())
			{
				con_este_numero_no=99999;
				//Colocamos la pieza lo más a la esquina posible
				ColocarEsquinaMasCercana(lista,b1,(*it),b1.Width(),b1.Height());
				//borro esa perdida
				it=lista.erase(it);
				//Movemos los bloques hacia las esquinas
				Bloques_Hacia_Las_Esquinas(b1,lista);
				//Introduzco el bloque en la lista de bloques
				listaB.push_back(b1);
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				JuntarPerdida(lista,'P');
				pueda_meter_piezas=true;
			}
	// printf("Salgo 5");

		}

	}
	*/

	RECTAN rect1(0,0,0,0);
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;

		primera=true;
		RECTAN rect1(0,0,0,0);
		//Construyo rectángulos de pérdida 
		Elijo_Menor_Lista(rect1,rect1,1,lista);
		DibujarSolucion(m_lista_bloques,m_lista_perdidas,0,0);

		//Elijo el menor rectángulo, en relación a la distancia a la esquina
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			if (pueda_meter_piezas==false && primera==false)	
				Elijo_Menor_Lista(rect1,rect1,1,lista);
			primera=false;

			BLOQUE b1(0,0,0,0);
//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
			ElegirPieza(b1,rect1,m_tipo,con_este_numero_no);

	//			if (m_tipo==1)	ElegirPiezaAleatoria(b1,rect1,1,99999);
	//			if (m_tipo==2)	ElegirPiezaAleatoria(b1,rect1,2,99999);
			if (!b1.IsRectEmpty())
			{
				con_este_numero_no=99999;
				m_noquiero=con_este_numero_no;

				//Colocamos la pieza lo más a la esquina posible
				ColocarEsquinaMasCercana(lista,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				BorrarListaPerdidas(rect1,lista);

				//Movemos los bloques hacia las esquinas

				Bloques_Hacia_Las_Esquinas(b1,lista);
				//Introduzco el bloque en la lista de bloques
				listaB.push_back(b1);
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
//				if (suer<=0)
//					JuntarPerdida(lista,'P');
//				if (suer==1)
//					JuntarPerdida(lista,'X');
				if (m_Determinista==true)
				JuntarPerdida(lista,'P');
				else
				{
					if (m_Posible==true && m_Restringido==true)
					{

					}
					if (m_Posible==false && m_Restringido==true)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(lista,'V');
						if (suer==1)
							JuntarPerdida(lista,'H');
					}
					if (m_Restringido==false)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(lista,'P');

						if (suer==1)
						JuntarPerdida(lista,'X');
					}

				}
				pueda_meter_piezas=true;
			}	

		}

	}


}
void CUTTING::RellenarStrip()
{
	/*
	//Tengo que rellenar otra vez ese rectángulo pero con piezas diferentes
	//de la que he quitado 
	//Contador desde donde debe empezar a mirar meter alguna
	//Coloca la variable para dibujar o no las soluciones
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	//Limpio la lista de perdidas
	//Al principio todo el tablero es perdida

	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;
		
		//Construyo rectángulos de pérdida 
		for (it=lista.begin();pueda_meter_piezas!=true && it!=lista.end() ;it++)
		{

			BLOQUE b1(0,0,0,0);
				// printf("Entro 5");
	//		if (m_Determinista==true)
//			int alea=get_random(0,1);
//			if (alea==1) ElegirPieza(b1,(*it),2,con_este_numero_no);
//			else ElegirPieza(b1,(*it),1,con_este_numero_no);
			if (m_tipo==1) ElegirPieza(b1,(*it),1,con_este_numero_no);
			if (m_tipo==2) ElegirPieza(b1,(*it),2,con_este_numero_no);
			if (!b1.IsRectEmpty())
			{
				con_este_numero_no=99999;
				//Colocamos la pieza lo más a la esquina posible
				ColocarEsquinaMasCercana(lista,b1,(*it),b1.Width(),b1.Height());
				//borro esa perdida
				it=lista.erase(it);
				//Movemos los bloques hacia las esquinas
				Bloques_Hacia_Las_Esquinas(b1,lista);
				//Introduzco el bloque en la lista de bloques
				listaB.push_back(b1);
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				JuntarPerdida(lista,'P');
				pueda_meter_piezas=true;
			}
	// printf("Salgo 5");

		}

	}
	*/

	RECTAN rect1(0,0,0,0);
	//Actualizo Min max aunque ya vienen de la lectura por si tengo que meter alguno al principio
	int pieza_mayor2=ActualizarMinMax();
	if (m_MinAncho==99999)
		return;
	int solmax=ContarSolucionStrip(m_lista_bloques);
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	int meter_pieza=MAX_IMPORTANCIA;

	//Variable para seguir metiendo piezas
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;

		primera=true;
		RECTAN rect1(0,0,0,0);
		//Construyo rectángulos de pérdida 
		//Elijo el menor rectángulo, en relación a la distancia a la esquina

		Elijo_Menor_ListaStrip(rect1,rect1,2,false);
		//Si tengo un rectrángulo que es más pequeño
		//Tengo que cerrarlo y juntar pérdidas
		if (rect1.Height()<m_MinAncho)
		{
			//Cortamos hasta el más cercano
			//el rectángulo
			int a1=0,a2=0;
			//anchura de los de abajo
			if (rect1.top==0) a1=m_L;
			else a1=Altura(rect1.top,0);
			//anchura de los de arriba
			if (rect1.bottom==m_W) a2=m_L;
			else a2=Altura(rect1.bottom,1);
			BorrarListaPerdidas(rect1);	
			if (a2>a1)
			{
				rect1.right=a1;
			}
			else
			{
				rect1.right=a2;
			}
			RECTAN rect2(0,0,0,0);
			rect2.top=rect1.top;
			rect2.bottom=rect1.bottom;
			rect2.right=m_L;
			rect2.left=rect1.right;
			if (!rect1.IsRectEmpty())
			m_lista_perdidas.push_back(rect1);
			m_lista_perdidas.push_back(rect2);
			JuntarPerdidaStrip(m_lista_perdidas,'S');
			pueda_meter_piezas=true;
			
		}
		//Si tengo un rectrángulo que es más pequeño
		//Tengo que cerrarlo y juntar pérdidas
	
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			if (pueda_meter_piezas==false && primera==false)	
				Elijo_Menor_ListaStrip(rect1,rect1,2,false);
			primera=false;

			BLOQUE b1(0,0,0,0);
			if (meter_pieza!=99999 && m_Piezas[meter_pieza].max==m_Piezas[meter_pieza].num)
			{
				meter_pieza=99999;
			}

//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else

			int pieza=PiezaMayorEsteRectangulo(rect1);
			ElegirPiezaStrip(b1,rect1,m_tipo,meter_pieza);
			//Evaluo si hace falta meterla
			bool meto_larga=false;
			double estimacion=1.0;


			if (pieza!=b1.GetNumero() && pieza!=99999 )
			{
				//Si se pueden rotar las piezas
				int pieza_largo=m_Piezas[pieza].largo;
				int pieza_ancho=m_Piezas[pieza].ancho;
				if (m_PuedenRotarsePiezas==true)
				{
					//Solo en este caso habrá que rotarlas
					if (pieza_ancho>pieza_largo)
					{
						int kk=pieza_ancho;
						pieza_ancho=pieza_largo;
						pieza_largo=kk;

					}
				}


//				int quedan_gran=__min(m_Piezas[pieza].max-m_Piezas[pieza].num,rect1.Height()/m_Piezas[pieza].ancho);
				int quedan_gran=1;
				//el maximo de la que voy a poner y la que queda
				if (rect1.left+pieza_largo>solmax)
				{
					int areaqueda=AreaRestante(rect1.left+pieza_largo);
					if ((areaqueda)>=(estimacion*m_AreaTotalRestante))
					{
						meto_larga=true;
					}
					else
					{
						if ((rect1.Height()-b1.Height())<pieza_ancho*quedan_gran)//piezas pocas
						{
							if (rect1.left+b1.Width()+pieza_largo>solmax)
							{
								int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),pieza_ancho*quedan_gran,pieza_largo);
								if ((areaquedasig)>=estimacion*m_AreaTotalRestante)
								{
									meto_larga=true;
								}
							}
						}
					}

				}
				else
				{
					if ((rect1.Height()-b1.Height())<pieza_ancho*quedan_gran)//piezas pocas
					{
						if (rect1.left+b1.Width()+pieza_largo>solmax)
						{
							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),m_Piezas[pieza].ancho*quedan_gran,pieza_largo);
							if ((areaquedasig)>=estimacion*m_AreaTotalRestante)
							{
								meto_larga=true;
							}
						}
					}
				}

				if (meto_larga==true)
				{
					m_Piezas[b1.GetNumero()].num-=(b1.Width()*b1.Height())/(m_Piezas[b1.GetNumero()].largo*m_Piezas[b1.GetNumero()].ancho);

					b1.right=pieza_largo;
					b1.bottom=pieza_ancho*quedan_gran;
					b1.SetNumero(pieza);
					m_Piezas[b1.GetNumero()].num+=quedan_gran;

				}

			}
			if (!b1.IsRectEmpty())
			{
				//Colocamos la pieza seghún Monaci
				int pieza_mayor=ActualizarMinMax();
				ColocarEsquinaMonaciStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				if (b1.right>solmax) 
					solmax=b1.right;
				BorrarListaPerdidas(rect1);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				if (m_MinAncho==99999)
					break;

				pueda_meter_piezas=true;
			}	
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);


		}

	}
	//Valor de la solucion
	m_ValSolucion=ContarSolucionStrip(m_lista_bloques);
//	EscribirSolucion(m_lista_bloques);
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);


}


int CUTTING::BloqueCercaPerdidas(BLOQUE &B,int val)
{
	std::list<RECTAN> ::iterator itB;
	for (itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
		//Por la izquierda
		//Si a la izquierda
		if (((((*itB).right==B.left) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
		|| (((*itB).right==B.left) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
		|| (((*itB).right==B.left) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
		|| (((*itB).right==B.left) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
		&& (val==6 || val==8 || val==0 || val==15))
		{
			return 1;

		}
		//Si a la derecha
		if (((((*itB).left==B.right) && ((*itB).top>B.top) && ((*itB).top<B.bottom))
		|| (((*itB).left==B.right) && ((*itB).bottom>B.top) && ((*itB).bottom<B.bottom))
		|| (((*itB).left==B.right) && ((*itB).top<=B.top) && ((*itB).bottom>=B.bottom))
		|| (((*itB).left==B.right) && ((*itB).top>=B.top) && ((*itB).bottom<=B.bottom)))
		&& (val==5 || val==7 || val==0 || val==15))
		{
			return 1;

		}
		//Si a abajo
		if (((((*itB).bottom==B.top) && ((*itB).left>B.left) && ((*itB).left<B.right))
		|| (((*itB).bottom==B.top) && ((*itB).right>B.left) && ((*itB).right<B.right))
		|| (((*itB).bottom==B.top) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
		|| (((*itB).bottom==B.top) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
		&& (val==2 || val==4 || val==0 || val==10))
		{
			return 1;

		}
		//Si a arriba
		if (((((*itB).top==B.bottom) && ((*itB).left>B.left) && ((*itB).left<B.right))
		|| (((*itB).top==B.bottom) && ((*itB).right>B.left) && ((*itB).right<B.right))
		|| (((*itB).top==B.bottom) && ((*itB).left<=B.left) && ((*itB).right>=B.right))
		|| (((*itB).top==B.bottom) && ((*itB).left>=B.left) && ((*itB).right<=B.right)))
		&& (val==1 || val==3 || val==0 || val==10))
		{
			return 1;

		}
//		if (perdi>0) return perdi;

	}

	return 0;

}
bool CUTTING::BloqueCercaPerdida(BLOQUE &B,RECTAN &Rect)
{
		//Por la izquierda
		//Si a la izquierda
		if ((((Rect.right==B.left) && (Rect.top>B.top) && (Rect.top<B.bottom))
		|| ((Rect.right==B.left) && (Rect.bottom>B.top) && (Rect.bottom<B.bottom))
		|| ((Rect.right==B.left) && (Rect.top<=B.top) && (Rect.bottom>=B.bottom))
		|| ((Rect.right==B.left) && (Rect.top>=B.top) && (Rect.bottom<=B.bottom))))
		{
			return true;

		}
		//Si a la derecha
		if ((((Rect.left==B.right) && (Rect.top>B.top) && (Rect.top<B.bottom))
		|| ((Rect.left==B.right) && (Rect.bottom>B.top) && (Rect.bottom<B.bottom))
		|| ((Rect.left==B.right) && (Rect.top<=B.top) && (Rect.bottom>=B.bottom))
		|| ((Rect.left==B.right) && (Rect.top>=B.top) && (Rect.bottom<=B.bottom))))
		{
			return true;

		}
		//Si a abajo
		if ((((Rect.bottom==B.top) && (Rect.left>B.left) && (Rect.left<B.right))
		|| ((Rect.bottom==B.top) && (Rect.right>B.left) && (Rect.right<B.right))
		|| ((Rect.bottom==B.top) && (Rect.left<=B.left) && (Rect.right>=B.right))
		|| ((Rect.bottom==B.top) && (Rect.left>=B.left) && (Rect.right<=B.right))))
		{
			return true;

		}
		//Si a arriba
		if ((((Rect.top==B.bottom) && (Rect.left>B.left) && (Rect.left<B.right))
		|| ((Rect.top==B.bottom) && (Rect.right>B.left) && (Rect.right<B.right))
		|| ((Rect.top==B.bottom) && (Rect.left<=B.left) && (Rect.right>=B.right))
		|| ((Rect.top==B.bottom) && (Rect.left>=B.left) && (Rect.right<=B.right))))
		{
			return true;

		}
//		if (perdi>0) return perdi;


	return false;

}
/*
void CUTTING::HeuristicoGreedyStrip(bool dibu)
{
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;


		//Elijo el menor rectángulo, en relación a la distancia a la esquina
		for (it=m_lista_perdidas.begin();pueda_meter_piezas!=true && it!=m_lista_perdidas.end() ;it++)
		{
			BLOQUE b1(0,0,0,0);
//*********
			RECTAN r=(*it);
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else
			if (m_Determinista==false)
			{
				if (m_tipo==1)	ElegirPiezaAleatoria(b1,(*it),1,99999);
				if (m_tipo==2)	ElegirPiezaAleatoria(b1,(*it),2,99999);
			}
			else
			{
				if (m_tipo==1)	ElegirPieza(b1,(*it),1,99999);
				if (m_tipo==2)	ElegirPieza(b1,(*it),2,99999);
			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
				ColocarEsquinaMasCercanaStrip(m_lista_perdidas,b1,(*it),b1.Width(),b1.Height());
//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				it=m_lista_perdidas.erase(it);
				//Movemos los bloques hacia las esquinas
				//Solo he metido un bloque solo intento mover un bloque
				Bloques_Hacia_Las_EsquinasStrip(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
//				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				if (m_Determinista==true)
				JuntarPerdida(m_lista_perdidas,'P');
				else
				{
					if (m_Posible==true && m_Restringido==true)
					{

						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'P');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'X');
					}
					if (m_Posible==false && m_Restringido==true)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'V');
						if (suer==1)
							JuntarPerdida(m_lista_perdidas,'H');
					}
					if (m_Restringido==false)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'P');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'X');
					}

				}
//				if (suer==6)
//				JuntarPerdida(m_lista_perdidas,'V');
//				if (suer==7)
//				JuntarPerdida(m_lista_perdidas,'H');
//				EscribirSolucionLatex(m_lista_bloques);
				pueda_meter_piezas=true;
			}	
//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);

		}

	}
	//Valor de la solucion
	m_ValSolucion=ContarSolucionStrip(m_lista_bloques);
	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}*/
//NUEVO

void CUTTING::HeuristicoGreedyOrdenStripRotacion(bool dibu)
{
	m_Posible=true;
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Actualizo Min max aunque ya vienen de la lectura por si tengo que meter alguno al principio
	int pieza_mayor2=ActualizarMinMax();
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	int meter_pieza=MAX_IMPORTANCIA;
	int solmax=0;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;

		primera=true;
		RECTAN rect1(0,0,0,0);
		//Construyo rectángulos de pérdida 
		//Elijo el menor rectángulo, en relación a la distancia a la esquina

		Elijo_Menor_ListaStrip(rect1,rect1,2,false);
		//Si tengo un rectrángulo que es más pequeño
		//Tengo que cerrarlo y juntar pérdidas
		if (rect1.Height()<m_MinAncho)
		{
			int a1=0,a2=0;
			//anchura de los de abajo
			if (rect1.top==0) a1=m_L;
			else a1=Altura(rect1.top,0);
			//anchura de los de arriba
			if (rect1.bottom==m_W) a2=m_L;
			else a2=Altura(rect1.bottom,1);
			BorrarListaPerdidas(rect1);	
			RECTAN rect2(0,0,0,0);

			if (a2>a1)
			{
				rect1.right=a1;
				rect2.top=rect1.top;
				rect2.bottom=rect1.bottom;

				//Mirar si abajo hay alguna pieza que empieze
				//en rect1.top y si existe intentar cambiarla por otra
				Existe_Bloque(rect1,1);
			}
			else
			{
				rect1.right=a2;
				rect2.top=rect1.top;
				rect2.bottom=rect1.bottom;
				Existe_Bloque(rect1,2);
			}
			rect2.right=m_L;
			rect2.left=rect1.right;

			if (!rect1.IsRectEmpty()) 
				m_lista_perdidas.push_back(rect1);
//			else
//				printf("algo anda mal");

//			m_lista_perdidas.push_back(rect2);
			JuntarRectangulo(rect2);
//			JuntarPerdidaStrip(m_lista_perdidas,'S');
			pueda_meter_piezas=true;
			
		}
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			if (pueda_meter_piezas==false && primera==false)	
				Elijo_Menor_ListaStrip(rect1,rect1,2,false);
			primera=false;

			BLOQUE b1(0,0,0,0);
			if (meter_pieza!=99999 && m_Piezas[meter_pieza].max==m_Piezas[meter_pieza].num)
			{
				meter_pieza=99999;
			}

//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else
			//Miro cual es la pieza más grande que cabe en 
			//el rectángulo ya que si no la incluyo la deberé meter luego
			//Cuando se pueden rotar es mucho más dificil por lo que no hago 
			//nada

			int pieza=PiezaMayorEsteRectangulo(rect1);
//			if (m_PuedenRotarsePiezas==true) pieza=99999;
			if (m_Determinista==false )
			{
				ElegirPiezaAleatoriaStrip(b1,rect1,m_tipo,meter_pieza);
			}
			else
			{
				ElegirPiezaStrip(b1,rect1,m_tipo,meter_pieza);
			}
			//Debería hacer algo para que se puedan cerrar huecos sin poner nada
			//Evaluo si hace falta meterla
			bool meto_larga=false;
			double estimacion;
			if (m_Determinista==true) estimacion=1.0;
			else 
			{
				estimacion=(double)get_random(90,160)/(double)100;
//				estimacion=2;
//				estimacion=(double)get_random(100-(1-m_FactorAleatorio)*100,100+(1-m_FactorAleatorio)*100)/(double)100;
			}
			int pieza_largo=m_Piezas[pieza].largo;
			int pieza_ancho=m_Piezas[pieza].ancho;
			if (m_iter_actual==0 || m_Determinista==true) m_solbest=99999;
			int maxsol=__min(solmax,m_solbest-1);
			//Si se pueden rotar las piezas
			if (m_PuedenRotarsePiezas==true)
			{
					
				if (pieza_ancho<=rect1.Height())
				{
					if (pieza_largo<=rect1.Height())
					{
						if (pieza_ancho<pieza_largo) 
						{
							int kk=pieza_ancho;
							pieza_ancho=pieza_largo;
							pieza_largo=kk;
						}
					}
				}
				else
				{
					int kk=pieza_ancho;
					pieza_ancho=pieza_largo;
					pieza_largo=kk;
				}
		
			}
			//Estima si tengo que meter la pieza cuando no es posible meterla de otra manera
			//es decir para las piezas fijas
			if (pieza!=99999 && pieza!=b1.GetNumero() )
			{

				
			
				int quedan_gran=__min(m_Piezas[pieza].max-m_Piezas[pieza].num,rect1.Height()/pieza_ancho);
				if (m_Determinista!=true) 
					quedan_gran=get_random(1,quedan_gran);
				int maxperdi=0;
				if (m_PuedenRotarsePiezas==true && pieza_largo<=m_W)
				{

					if (rect1.left+pieza_largo>maxsol+pieza_ancho)
					{
						pieza_largo=0;
						pieza_ancho=0;
					}
				}
//				int kl=rect1.left+m_Piezas[pieza].largo;

				//Para hacer que la estimación dependa de la cota
				//inferior
				if (m_Determinista!=true )
				{
					maxperdi=((m_W*m_Cota)-m_total_superficie)/4;
	//				maxperdi=get_random(0,maxperdi);

				}
				//el maximo de la que voy a poner y la que queda
				if (rect1.left+pieza_largo>maxsol)
				{
					int areaqueda=AreaRestante(rect1.left+pieza_largo);
					if ((areaqueda)>=(estimacion*(m_AreaTotalRestante+maxperdi)))
					{
						meto_larga=true;
					}
					else
					{
						if ((rect1.Height()-b1.Height())<pieza_ancho*quedan_gran)//piezas pocas
						{
							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),pieza_ancho*quedan_gran,pieza_largo);
//							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),b1.Height(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
							if ((areaquedasig)>=estimacion*(m_AreaTotalRestante+maxperdi))
							{
								meto_larga=true;
							}
						}
					}

				}
				else
				{
					if ((rect1.Height()-b1.Height())<pieza_ancho*quedan_gran)//piezas pocas
					{
						if (rect1.left+b1.Width()+pieza_largo>maxsol)
						{
							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),pieza_ancho*quedan_gran,pieza_largo);
//							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),b1.Height(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);

							if ((areaquedasig)>=estimacion*m_AreaTotalRestante)
							{
								meto_larga=true;
							}
						}
					}
				}


				if (meto_larga==true)
				{
//					if (m_iter_actual==729)
//					EscribirSolucionStripLatex(m_lista_bloques);

					m_Piezas[b1.GetNumero()].num-=(b1.Width()*b1.Height())/(m_Piezas[b1.GetNumero()].largo*m_Piezas[b1.GetNumero()].ancho);

					b1.right=pieza_largo;
					b1.bottom=pieza_ancho*quedan_gran;
					b1.SetNumero(pieza);
					m_Piezas[b1.GetNumero()].num+=quedan_gran;

				}

			}
			//si pasa esta condición me conviene cerrar ese rectángulo y ponerlas en horizontal
			//si es mejor colocar todas las piezas a lo ancho que meter esta pieza en vertical
			//cierro el rectángulo y vuelvo a elegir meter otra pieza
			if (m_PuedenRotarsePiezas==true && rect1.left+b1.Width()>(solmax+m_TotalAncho))
			{
				int a1=0,a2=0;
				//anchura de los de abajo
				if (rect1.top==0) a1=m_L;
				else a1=Altura(rect1.top,0);
				//anchura de los de arriba
				if (rect1.bottom==m_W) a2=m_L;
				else a2=Altura(rect1.bottom,1);
				BorrarListaPerdidas(rect1);	
				if (a2>a1)
				{
					rect1.right=a1;
				}
				else
				{
					rect1.right=a2;
				}
				RECTAN rect2(0,0,0,0);
				rect2.top=rect1.top;
				rect2.bottom=rect1.bottom;
				rect2.right=m_L;
				rect2.left=rect1.right;
				m_lista_perdidas.push_back(rect1);
				m_lista_perdidas.push_back(rect2);
				JuntarPerdidaStrip(m_lista_perdidas,'S');
				pueda_meter_piezas=true;
				m_Piezas[b1.GetNumero()].num-=(b1.Width()*b1.Height())/(m_Piezas[b1.GetNumero()].largo*m_Piezas[b1.GetNumero()].ancho);
				b1.top=b1.bottom;
				pieza=99999;
			
			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
//				ColocarEsquinaMasCercanaStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//Colocamos la pieza seghún Monaci
				int pieza_mayor=ActualizarMinMax();
				ColocarEsquinaMonaciStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				if (b1.right>solmax)
					solmax=b1.right;
//				if (m_iter_actual==729 && meto_larga==true)
//					EscribirSolucionStripLatex(m_lista_bloques);

//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				BorrarListaPerdidas(rect1);
				//Hacer estimación
				//Movemos los bloques hacia las esquinas
			
				//Solo he metido un bloque solo intento mover un bloque
//				Bloques_Hacia_Las_EsquinasStrip(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				if (m_MinAncho==99999)
					break;
				pueda_meter_piezas=true;
			}	
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);

//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);

		}

	}
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);
//	EscribirSolucionStripLatex(m_lista_bloques);
	//Valor de la solucion
	m_ValSolucion=solmax;
//	EscribirSolucion(m_lista_bloques);
//	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}

void CUTTING::HeuristicoGreedyOrdenStrip(bool dibu)
{
	m_Posible=true;
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
//	double tempFalea=m_FactorAleatorio;
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Actualizo Min max aunque ya vienen de la lectura por si tengo que meter alguno al principio
	int pieza_mayor2=ActualizarMinMax();
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	int meter_pieza=MAX_IMPORTANCIA;
	int solmax=0;
	int maxperdi=0;

	//Para hacer que la estimación dependa de la cota
	//inferior
	if (m_Determinista!=true )
	{
		maxperdi=((m_W*m_Cota)-m_total_superficie)/4;
//				maxperdi=get_random(0,maxperdi);

	}

//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;

		primera=true;
		RECTAN rect1(0,0,0,0);
		//Construyo rectángulos de pérdida 
		//Elijo el menor rectángulo, en relación a la distancia a la esquina

		Elijo_Menor_ListaStrip(rect1,rect1,2,false);
		//Si tengo un rectrángulo que es más pequeño
		//Tengo que cerrarlo y juntar pérdidas
		//También tengo que mirar si existe algúno que pueda cambiar
		if (rect1.Height()<m_MinAncho )
		{
			int a1=0,a2=0;
			//anchura de los de abajo
			if (rect1.top==0) a1=m_L;
			else a1=Altura(rect1.top,0);
			//anchura de los de arriba
			if (rect1.bottom==m_W) a2=m_L;
			else a2=Altura(rect1.bottom,1);
			BorrarListaPerdidas(rect1);	
			RECTAN rect2(0,0,0,0);

			if (a2>a1)
			{
				rect1.right=a1;
				rect2.top=rect1.top;
				rect2.bottom=rect1.bottom;

				//Mirar si abajo hay alguna pieza que empieze
				//en rect1.top y si existe intentar cambiarla por otra
				Existe_Bloque(rect1,1);
			}
			else
			{
				rect1.right=a2;
				rect2.top=rect1.top;
				rect2.bottom=rect1.bottom;
				Existe_Bloque(rect1,2);
			}
			rect2.right=m_L;
			rect2.left=rect1.right;

			if (!rect1.IsRectEmpty()) 
				m_lista_perdidas.push_back(rect1);
//			else
//				printf("algo anda mal");

//			m_lista_perdidas.push_back(rect2);
			JuntarRectangulo(rect2);
//			JuntarPerdidaStrip(m_lista_perdidas,'S');
			pueda_meter_piezas=true;
			
		}
		//Mientra no 
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			if (pueda_meter_piezas==false && primera==false)	
				Elijo_Menor_ListaStrip(rect1,rect1,2,false);
			primera=false;

			BLOQUE b1(0,0,0,0);
			if (meter_pieza!=99999 && m_Piezas[meter_pieza].max==m_Piezas[meter_pieza].num)
			{
				meter_pieza=99999;
			}

//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else

			if (m_Determinista==false )
			{
				ElegirPiezaAleatoriaStrip(b1,rect1,m_tipo,meter_pieza);
			}
			else
			{
				ElegirPiezaStrip(b1,rect1,m_tipo,meter_pieza);
			}
			//Evaluo si hace falta meterla
			bool meto_larga=false;
			double estimacion=1,estimacion1=1;
			int maxsol=__min(solmax,m_solbest-2);
			if (rect1.left+b1.Width()+m_MaxLargo>solmax )
			{
				if (m_Determinista==true) estimacion=1.0;
				else 
				{
					estimacion=(double)get_random(85,125)/(double)100;
					estimacion1=estimacion;
					estimacion1=(double)get_random(90,110)/(double)100;
//					alea=(double)get_random(5,50)/(double)100;
				}
				int pieza=PiezaMayorEsteRectangulo(rect1,b1.GetNumero());
				if (pieza!=b1.GetNumero() && pieza!=99999)
				{
					int quedan_gran=__min(m_Piezas[pieza].max-m_Piezas[pieza].num,rect1.Height()/m_Piezas[pieza].ancho);
					if (m_Determinista!=true) 
						quedan_gran=get_random(1,quedan_gran);
					if (m_solbest!=0 && rect1.left+m_Piezas[pieza].largo>(m_solbest-2) )
					{
						meto_larga=true;
					}
					else
					{
						//el maximo de la que voy a poner y la que queda
						if (rect1.left+m_Piezas[pieza].largo>maxsol )
						{
							int areaqueda=AreaRestante(rect1.left+m_Piezas[pieza].largo);
							if ((areaqueda)>=(estimacion1*(m_AreaTotalRestante+maxperdi)))
							{
								meto_larga=true;
							}
							else
							{
								if ((rect1.Height()-b1.Height())<m_Piezas[pieza].ancho*quedan_gran)//piezas pocas
								{
									int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
	//								int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),b1.Height(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
									if ((areaquedasig)>=estimacion*(m_AreaTotalRestante+maxperdi))
									{
										meto_larga=true;
									}
								}
							}

						}
					
						else
						{
							//Si no cabe la mayor en el hueco que voy a dejar
							if ((rect1.Height()-b1.Height())<m_Piezas[pieza].ancho*quedan_gran)//piezas pocas
							{
								//Si además me puede producir una solución peor
								if (rect1.left+b1.Width()+m_Piezas[pieza].largo>maxsol)
								{	
									//Si va a dejarme fuera mucho
									int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
	//								int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),b1.Height(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
									if ((areaquedasig)>=estimacion*m_AreaTotalRestante)
									{
										meto_larga=true;
									}
								}
							}
						}
					}

					if (meto_larga==true)
					{
						m_Piezas[b1.GetNumero()].num-=(b1.Width()*b1.Height())/(m_Piezas[b1.GetNumero()].largo*m_Piezas[b1.GetNumero()].ancho);	
						b1.right=m_Piezas[pieza].largo;
						b1.bottom=m_Piezas[pieza].ancho*quedan_gran;
						b1.SetNumero(pieza);
						m_Piezas[b1.GetNumero()].num+=quedan_gran;

					}

				}
			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
//				ColocarEsquinaMasCercanaStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//Colocamos la pieza seghún Monaci
//				if (m_lista_bloques.size()==5 && m_iter_actual==73)
//					int koil=4;
//				m_FactorAleatorio=((1-m_FactorAleatorio)/(double)m_Numpiezas)*(double)m_lista_bloques.size()+tempFalea;
				int pieza_mayor=ActualizarMinMax();
//				if (meto_larga!=true)
//				if (meto_larga!=true)
					ColocarEsquinaMonaciStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
//				else
//					ColocarEsquinaMonaciModiStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				if (b1.right>solmax)
					solmax=b1.right;
//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				//Hacer estimación
/*				double estimacion;
				if (m_Determinista==true) estimacion=1.25;
				else 
					estimacion=(double)get_random(50,200)/(double)100;

				if (pieza_mayor!=99999)
				{
					if (estimacion*(m_MaxLargo*(m_W-m_Piezas[pieza_mayor].ancho))>(m_AreaTotalRestante-(m_Piezas[pieza_mayor].ancho*m_MaxLargo)))
					{
						meter_pieza=pieza_mayor;
					}
				}
				else
					meter_pieza=MAX_IMPORTANCIA;
					*/
				//Movemos los bloques hacia las esquinas
			
				//Solo he metido un bloque solo intento mover un bloque
//				Bloques_Hacia_Las_EsquinasStrip(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				VerificarSolucion(m_lista_bloques,m_lista_perdidas,1);

				if (m_MinAncho==99999)
					break;
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
//				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
//				JuntarPerdidaStrip(m_lista_perdidas,'S');

//				EscribirSolucionLatex(m_lista_bloques);
				pueda_meter_piezas=true;
			}	
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);

//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);

		}

	}
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);

	//Valor de la solucion
	m_ValSolucion=solmax;
//	m_FactorAleatorio=tempFalea;
//	EscribirSolucion(m_lista_bloques);
//	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}

void CUTTING::HeuristicoGreedyStrip(bool dibu)
{
	m_Posible=true;
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
//	double tempFalea=m_FactorAleatorio;
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Actualizo Min max aunque ya vienen de la lectura por si tengo que meter alguno al principio
	int pieza_mayor2=ActualizarMinMax();
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	int meter_pieza=MAX_IMPORTANCIA;
	int solmax=0;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;



		primera=true;
		//Construyo rectángulos de pérdida 
		//Elijo el menor rectángulo, en relación a la distancia a la esquina
		for (it=m_lista_perdidas.begin();pueda_meter_piezas!=true && it!=m_lista_perdidas.end() && m_MinAncho!=99999;it++)
		{
			if ((*it).right!=m_L) continue;
		RECTAN rect1(0,0,0,0);
			RECTAN rect3=(*it);
		Elijo_Menor_ListaStrip(rect1,rect1,2,false);
		//Si tengo un rectrángulo que es más pequeño
		//Tengo que cerrarlo y juntar pérdidas
		if (rect1.Height()<m_MinAncho && rect1.EqualRect((*it))==1)
		{
			int a1=0,a2=0;
			//anchura de los de abajo
			if (rect1.top==0) a1=m_L;
			else a1=Altura(rect1.top,0);
			//anchura de los de arriba
			if (rect1.bottom==m_W) a2=m_L;
			else a2=Altura(rect1.bottom,1);
			BorrarListaPerdidas(rect1);	
			if (a2>a1)
			{
				rect1.right=a1;
			}
			else
			{
				rect1.right=a2;
			}
			RECTAN rect2(0,0,0,0);
			rect2.top=rect1.top;
			rect2.bottom=rect1.bottom;
			rect2.right=m_L;
			rect2.left=rect1.right;

			m_lista_perdidas.push_back(rect1);
			m_lista_perdidas.push_back(rect2);
			JuntarPerdidaStrip(m_lista_perdidas,'S');
			pueda_meter_piezas=true;
			
		}
		else
		{
			if (rect3.Height()<m_MinAncho) 
				continue;
		}
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			primera=false;

			BLOQUE b1(0,0,0,0);
			if (meter_pieza!=99999 && m_Piezas[meter_pieza].max==m_Piezas[meter_pieza].num)
			{
				meter_pieza=99999;
			}

//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else

			int pieza=PiezaMayorEsteRectangulo(rect3);
			if (m_Determinista==false )
			{
				ElegirPiezaAleatoriaStrip(b1,rect3,m_tipo,meter_pieza);
			}
			else
			{
				ElegirPiezaStrip(b1,rect3,m_tipo,meter_pieza);
			}
			//Evaluo si hace falta meterla
			bool meto_larga=false;
			double estimacion;
			if (m_Determinista==true) estimacion=1.0;
			else 
			{
				estimacion=(double)get_random(90,160)/(double)100;
//				estimacion=2;
//				estimacion=(double)get_random(100-(1-m_FactorAleatorio)*100,100+(1-m_FactorAleatorio)*100)/(double)100;
/*				int suerte=get_random(0,10);
				if (suerte<=10) estimacion=(double)get_random(180,480)/(double)100;
				if (suerte<=9) estimacion=(double)get_random(160,180)/(double)100;
				if (suerte<=8) estimacion=(double)get_random(90,160)/(double)100;
*/			}

			if (pieza!=b1.GetNumero() && pieza!=99999 &&  rect1.EqualRect((*it))==1)
			{
				int maxsol=__min(solmax,m_solbest);
				int quedan_gran=__min(m_Piezas[pieza].max-m_Piezas[pieza].num,rect1.Height()/m_Piezas[pieza].ancho);
				if (m_Determinista!=true) 
					quedan_gran=get_random(1,quedan_gran);
				int maxperdi=0;

				//Para hacer que la estimación dependa de la cota
				//inferior
				if (m_Determinista!=true )
				{
					maxperdi=((m_W*m_Cota)-m_total_superficie)/4;
	//				maxperdi=get_random(0,maxperdi);

				}
				//el maximo de la que voy a poner y la que queda
				if (rect1.left+m_Piezas[pieza].largo>maxsol)
				{
					int areaqueda=AreaRestante(rect1.left+m_Piezas[pieza].largo);
					if ((areaqueda)>=(estimacion*(m_AreaTotalRestante+maxperdi)))
					{
						meto_larga=true;
					}
					else
					{
						if ((rect1.Height()-b1.Height())<m_Piezas[pieza].ancho*quedan_gran)//piezas pocas
						{
							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
//							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),b1.Height(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
							if ((areaquedasig)>=estimacion*(m_AreaTotalRestante+maxperdi))
							{
								meto_larga=true;
							}
						}
					}

				}
				else
				{
					if ((rect1.Height()-b1.Height())<m_Piezas[pieza].ancho*quedan_gran)//piezas pocas
					{
						if (rect1.left+b1.Width()+m_Piezas[pieza].largo>maxsol)
						{
							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);
//							int areaquedasig=AreaRestanteSiguiente(rect1,b1.Width(),b1.Height(),m_Piezas[pieza].ancho*quedan_gran,m_Piezas[pieza].largo);

							if ((areaquedasig)>=estimacion*m_AreaTotalRestante)
							{
								meto_larga=true;
							}
						}
					}
				}


				if (meto_larga==true)
				{
					m_Piezas[b1.GetNumero()].num-=(b1.Width()*b1.Height())/(m_Piezas[b1.GetNumero()].largo*m_Piezas[b1.GetNumero()].ancho);

					b1.right=m_Piezas[pieza].largo;
					b1.bottom=m_Piezas[pieza].ancho*quedan_gran;
					b1.SetNumero(pieza);
					m_Piezas[b1.GetNumero()].num+=quedan_gran;

				}

			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
//				ColocarEsquinaMasCercanaStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//Colocamos la pieza seghún Monaci
//				if (m_lista_bloques.size()==3 && m_iter_actual==142)
//					int koil=4;
//				m_FactorAleatorio=((1-m_FactorAleatorio)/(double)m_Numpiezas)*(double)m_lista_bloques.size()+tempFalea;
				int pieza_mayor=ActualizarMinMax();
				ColocarEsquinaMonaciStrip(m_lista_perdidas,b1,rect3,b1.Width(),b1.Height());
//				ColocarEsquinaMonaciModiStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				if (b1.right>solmax)
					solmax=b1.right;
//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				BorrarListaPerdidas(rect3);
				//Hacer estimación
/*				double estimacion;
				if (m_Determinista==true) estimacion=1.25;
				else 
					estimacion=(double)get_random(50,200)/(double)100;

				if (pieza_mayor!=99999)
				{
					if (estimacion*(m_MaxLargo*(m_W-m_Piezas[pieza_mayor].ancho))>(m_AreaTotalRestante-(m_Piezas[pieza_mayor].ancho*m_MaxLargo)))
					{
						meter_pieza=pieza_mayor;
					}
				}
				else
					meter_pieza=MAX_IMPORTANCIA;
					*/
				//Movemos los bloques hacia las esquinas
			
				//Solo he metido un bloque solo intento mover un bloque
//				Bloques_Hacia_Las_EsquinasStrip(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				VerificarSolucion(m_lista_bloques,m_lista_perdidas,1);

				if (m_MinAncho==99999)
					break;
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
//				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				if (m_Determinista==true)
					JuntarPerdidaStrip(m_lista_perdidas,'S');
				else
				{
					if (m_Posible==true && m_Restringido==true)
					{

						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdidaStrip(m_lista_perdidas,'S');


						if (suer==1)
							JuntarPerdidaStrip(m_lista_perdidas,'S');

					}
					if (m_Posible==false && m_Restringido==true)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdidaStrip(m_lista_perdidas,'S');
						if (suer==1)
							JuntarPerdidaStrip(m_lista_perdidas,'S');
					}
					if (m_Restringido==false)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdidaStrip(m_lista_perdidas,'S');

						if (suer==1)
						JuntarPerdidaStrip(m_lista_perdidas,'S');
					}

				}
//				if (suer==6)
//				JuntarPerdida(m_lista_perdidas,'V');
//				if (suer==7)
//				JuntarPerdida(m_lista_perdidas,'H');
//				EscribirSolucionLatex(m_lista_bloques);
				pueda_meter_piezas=true;
			}	
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);

//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);
			}

		}

	}
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,solmax,0);

	//Valor de la solucion
	m_ValSolucion=solmax;
//	m_FactorAleatorio=tempFalea;
//	EscribirSolucion(m_lista_bloques);
//	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}
//Función antigua
/*
void CUTTING::HeuristicoGreedyOrdenStrip(bool dibu)
{
	m_Posible=true;
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Actualizo Min max aunque ya vienen de la lectura por si tengo que meter alguno al principio
	int pieza_mayor2=ActualizarMinMax();
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
	int meter_pieza=MAX_IMPORTANCIA;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;

		primera=true;
		RECTAN rect1(0,0,0,0);
		//Construyo rectángulos de pérdida 
		Elijo_Menor_ListaStrip(rect1,rect1,2);

		//Elijo el menor rectángulo, en relación a la distancia a la esquina
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			if (pueda_meter_piezas==false && primera==false)	
				Elijo_Menor_ListaStrip(rect1,rect1,2);
			primera=false;

			BLOQUE b1(0,0,0,0);
			if (meter_pieza!=99999 && m_Piezas[meter_pieza].max==m_Piezas[meter_pieza].num)
			{
				meter_pieza=99999;
			}

//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else
			if (m_Determinista==false )
			{
				ElegirPiezaAleatoria(b1,rect1,m_tipo,meter_pieza);
			}
			else
			{
				ElegirPieza(b1,rect1,m_tipo,meter_pieza);
			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
//				ColocarEsquinaMasCercanaStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//Colocamos la pieza seghún Monaci
				ColocarEsquinaMonaciStrip(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				BorrarListaPerdidas(rect1);
				int pieza_mayor=ActualizarMinMax();
				double estimacion;
				if (m_Determinista==true) estimacion=1.25;
				else 
					estimacion=(double)get_random(50,200)/(double)100;

				if (pieza_mayor!=99999)
				{
					if (estimacion*(m_MaxLargo*(m_W-m_Piezas[pieza_mayor].ancho))>(m_AreaTotalRestante-(m_Piezas[pieza_mayor].ancho*m_MaxLargo)))
					{
						meter_pieza=pieza_mayor;
					}
				}
				else
					meter_pieza=MAX_IMPORTANCIA;
				//Movemos los bloques hacia las esquinas
			
				//Solo he metido un bloque solo intento mover un bloque
//				Bloques_Hacia_Las_EsquinasStrip(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				if (m_MinAncho==99999)
					break;
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
//				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				if (m_Determinista==true)
				JuntarPerdida(m_lista_perdidas,'S');
				else
				{
					if (m_Posible==true && m_Restringido==true)
					{

						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'S');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'S');
					}
					if (m_Posible==false && m_Restringido==true)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'S');
						if (suer==1)
							JuntarPerdida(m_lista_perdidas,'S');
					}
					if (m_Restringido==false)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'S');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'S');
					}

				}
//				if (suer==6)
//				JuntarPerdida(m_lista_perdidas,'V');
//				if (suer==7)
//				JuntarPerdida(m_lista_perdidas,'H');
//				EscribirSolucionLatex(m_lista_bloques);
				pueda_meter_piezas=true;
			}	
			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);

		}

	}
	//Valor de la solucion
	m_ValSolucion=ContarSolucionStrip(m_lista_bloques);
//	EscribirSolucion(m_lista_bloques);
	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);

	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}
*/
void CUTTING::HeuristicoGreedy(bool dibu)
{
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;


		//Elijo el menor rectángulo, en relación a la distancia a la esquina
		for (it=m_lista_perdidas.begin();pueda_meter_piezas!=true && it!=m_lista_perdidas.end() ;it++)
		{
			BLOQUE b1(0,0,0,0);
//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else
			if (m_Determinista==false)
			{
				if (m_tipo==1)	ElegirPiezaAleatoria(b1,(*it),1,99999);
				if (m_tipo==2)	ElegirPiezaAleatoria(b1,(*it),2,99999);
			}
			else
			{
				if (m_tipo==1)	ElegirPieza(b1,(*it),1,99999);
				if (m_tipo==2)	ElegirPieza(b1,(*it),2,99999);
			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
				ColocarEsquinaMasCercana(m_lista_perdidas,b1,(*it),b1.Width(),b1.Height());
//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				it=m_lista_perdidas.erase(it);
				//Movemos los bloques hacia las esquinas
/*
				m_lista_bloques.push_back(b1);

				Bloques_Hacia_Las_Esquinas(m_lista_bloques,m_lista_perdidas);
*/			
				//Solo he metido un bloque solo intento mover un bloque
				Bloques_Hacia_Las_Esquinas(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				if (m_Determinista==true)
				JuntarPerdida(m_lista_perdidas,'P');
				else
				{
					if (m_Posible==true && m_Restringido==true)
					{

						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'P');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'X');
					}
					if (m_Posible==false && m_Restringido==true)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'V');
						if (suer==1)
							JuntarPerdida(m_lista_perdidas,'H');
					}
					if (m_Restringido==false)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'P');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'X');
					}

				}
//				if (suer==6)
//				JuntarPerdida(m_lista_perdidas,'V');
//				if (suer==7)
//				JuntarPerdida(m_lista_perdidas,'H');
//				EscribirSolucionLatex(m_lista_bloques);
				pueda_meter_piezas=true;
			}	
//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);

		}

	}
	//Valor de la solucion
	m_ValSolucion=ContarSolucion(m_lista_bloques);
	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}
void CUTTING::HeuristicoGreedyOrden(bool dibu)
{
	RECTAN rect1(0,0,0,0);
	//Contador desde donde debe empezar a mirar meter alguna
	m_EmpiezaPorAqui=0;
//	if (get_random(0,1)==1) modo=1;
//	else
//		modo=2;
	//Limpiar los numeros de las piezas elegidas
	for (register int x=0;x<m_Numpiezas;x++)
		m_Piezas[x].num=0;
		//Limpio la lista de perdidas
	m_lista_perdidas.clear();
	//Al principio todo el tablero es perdida
	RECTAN PTotal(0,0,m_L,m_W);
	m_lista_perdidas.push_back(PTotal);
	//
	m_lista_bloques.clear();
	//Coloca la variable para dibujar o no las soluciones
	m_Dibujar=dibu;
	//Variable para seguir metiendo piezas
	bool pueda_meter_piezas=true;
//	Posible();
//	int temp=m_FactorAleatorio;
	//Mientra pueda meter piezas
	std::list<RECTAN> ::iterator it;

	bool primera=false;
	while (pueda_meter_piezas==true)
	{
		pueda_meter_piezas=false;

		primera=true;
		RECTAN rect1(0,0,0,0);
		//Construyo rectángulos de pérdida 
		Elijo_Menor_Lista(rect1,rect1,2);

		//Elijo el menor rectángulo, en relación a la distancia a la esquina
		while (rect1.IsRectEmpty()==0 && pueda_meter_piezas!=true)
		{
			if (pueda_meter_piezas==false && primera==false)	
				Elijo_Menor_Lista(rect1,rect1,2);
			primera=false;

/*
		for (it=m_lista_perdidas.begin();pueda_meter_piezas!=true && it!=m_lista_perdidas.end() ;it++)
		{
*/
			BLOQUE b1(0,0,0,0);
//*********
			//Tipo 1: más valiosa
			//Tipo 2: mayor en función objetivo
//*********
//			ElegirPieza(b1,(*it),2,99999);
//			DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
			//al principio con tipo 1 luego tipo 2
//			if (m_lista_bloques.size()<=(m_Numpiezas/3))
//				ElegirPiezaAleatoria(b1,(*it),1,99999);
//			else
			if (m_Determinista==false)
			{
				if (m_tipo==1)	ElegirPiezaAleatoria(b1,rect1,1,99999);
				if (m_tipo==2)	ElegirPiezaAleatoria(b1,rect1,2,99999);
			}
			else
			{
				if (m_tipo==1)	ElegirPieza(b1,rect1,1,99999);
				if (m_tipo==2)	ElegirPieza(b1,rect1,2,99999);
			}
			if (!b1.IsRectEmpty())
			{
	//			espi++;
				//Colocamos la pieza lo más a la esquina posible
				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
//				ColocarEsquinaMasCercana(m_lista_perdidas,b1,rect1,b1.Width(),b1.Height());
				//borro esa perdida
				BorrarListaPerdidas(rect1);
//				it=m_lista_perdidas.erase(it);
				//Movemos los bloques hacia las esquinas
/*
				m_lista_bloques.push_back(b1);

				Bloques_Hacia_Las_Esquinas(m_lista_bloques,m_lista_perdidas);
*/			
				//Solo he metido un bloque solo intento mover un bloque
				Bloques_Hacia_Las_Esquinas(b1,m_lista_perdidas);
				//Introduzco el bloque en la lista de bloques
				m_lista_bloques.push_back(b1);
				//Juntar las perdidas el criterio que deje los rectángulos
				//más grandes posibles.
				//Miramos si tenemos una solución posible o no
				Posible();
				//Juntamos las pérdidas para que quepa la siguiente pieza en importancia
				if (m_Determinista==true)
				JuntarPerdida(m_lista_perdidas,'P');
				else
				{
					if (m_Posible==true && m_Restringido==true)
					{

						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'P');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'X');
					}
					if (m_Posible==false && m_Restringido==true)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'V');
						if (suer==1)
							JuntarPerdida(m_lista_perdidas,'H');
					}
					if (m_Restringido==false)
					{
						int suer=get_random(0,1);
						if (suer<=0)
							JuntarPerdida(m_lista_perdidas,'P');

						if (suer==1)
						JuntarPerdida(m_lista_perdidas,'X');
					}

				}
//				if (suer==6)
//				JuntarPerdida(m_lista_perdidas,'V');
//				if (suer==7)
//				JuntarPerdida(m_lista_perdidas,'H');
//				EscribirSolucionLatex(m_lista_bloques);
				pueda_meter_piezas=true;
			}	
//			printf("%d\t%c",m_lista_bloques.size(),pueda_meter_piezas);

		}

	}
	//Valor de la solucion
	m_ValSolucion=ContarSolucion(m_lista_bloques);
	//Si es para pintar solo el greedy lo pinto
//	if (m_FactorAleatorio==0) 	DibujarSolucion(m_lista_bloques,m_lista_perdidas,m_ValSolucion,0);
}
void CUTTING::BorrarListaPerdidas(RECTAN &R)
{
	std::list<RECTAN> ::iterator it;
	for (it=m_lista_perdidas.begin();it!=m_lista_perdidas.end() ;it++)
	{
		if (R.top==(*it).top && R.bottom==(*it).bottom && R.left==(*it).left && R.right==(*it).right)
		{
			it=m_lista_perdidas.erase(it);
			return;
		}


	}

}
void CUTTING::BorrarListaPerdidas(RECTAN &R, std::list<RECTAN> &lista)
{
	std::list<RECTAN> ::iterator it;
	for (it=lista.begin();it!=lista.end() ;it++)
	{
		if (R.top==(*it).top && R.bottom==(*it).bottom && R.left==(*it).left && R.right==(*it).right)
		{
			it=lista.erase(it);
			return;
		}


	}

}

void CUTTING::Elijo_Menor_Lista(RECTAN R, RECTAN &resultante, int tipo_orden, std::list<RECTAN> &lista)
{
	//Si tipo de orden es uno
	//es el más cercano a la esquina en otro caso

	//es el menor en área
	RECTAN r1(0,0,0,0);
	std::list<RECTAN> ::iterator it;
	int minimo=999999,maximo=0,minimoEste=0;
	int esqii=0,esqid=0,esqsd=0,esqsi=0;
	if (R.IsRectEmpty()==0 )
	{
		if (tipo_orden==1)
		{
			esqii=pow(R.top,2)+pow(R.left,2);
			esqid=pow(R.top,2)+pow(m_L-R.right,2);
			esqsi=pow(m_W-R.bottom,2)+pow(R.left,2);
			esqsd=pow(m_W-R.bottom,2)+pow(m_L-R.right,2);

			maximo=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			maximo=R.Width()*R.Height();
		}
	}

	for (it=lista.begin();it!=lista.end() ;it++)
	{
		if (R.top==(*it).top && R.bottom==(*it).bottom && R.left==(*it).left && R.right==(*it).right)
			continue;
		if (tipo_orden==1)
		{
		//minimo de la distancia a las esquinas
			esqii=pow((*it).top,2)+pow((*it).left,2);
			esqid=pow((*it).top,2)+pow(m_L-(*it).right,2);
			esqsi=pow(m_W-(*it).bottom,2)+pow((*it).left,2);
			esqsd=pow(m_W-(*it).bottom,2)+pow(m_L-(*it).right,2);

			minimoEste=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			minimoEste=((*it).Width())*((*it).Height());
		}
		//Si es menor y mayor que el que tenía
		if (minimoEste<=minimo && minimoEste>=maximo)
		{
			if (R.IsRectEmpty()!=0)
			{
				if (minimoEste==minimo)
				{
					if (((*it).Height()*(*it).Width())<=(r1.Height()*r1.Width()))
					{
						if (((*it).Height()*(*it).Width())==(r1.Height()*r1.Width()))
						{
							if ((*it).Height()<r1.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=minimoEste;
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=minimoEste;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=minimoEste;
				}
			}
			else
			{
				if (minimoEste==maximo)
				{
					if (((*it).Height()*(*it).Width())>=(R.Height()*R.Width()))
					{
						if (((*it).Height()*(*it).Width())==(R.Height()*R.Width()))
						{
							if ((*it).Height()>R.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=minimoEste;
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=minimoEste;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=minimoEste;
				}
			}
		}
	}
	if (r1.IsRectEmpty()!=0)
	{
		resultante.top=0;
		resultante.bottom=0;
		resultante.left=0;
		resultante.right=0;
	}
	else
	{
		resultante.top=r1.top;
		resultante.bottom=r1.bottom;
		resultante.left=r1.left;
		resultante.right=r1.right;

	}
}

void CUTTING::Elijo_Menor_ListaStrip(RECTAN R, RECTAN &resultante, int tipo_orden, std::list<RECTAN> &lista)
{
	//Si tipo de orden es uno
	//es el más cercano a la esquina en otro caso

	//es el más cercano su lado izquierdo a 0
	RECTAN r1(0,0,0,0);
	std::list<RECTAN> ::iterator it;
	int minimo=99999,maximo=0,minimoEste=0;
	int esqii=0,esqid=0,esqsd=0,esqsi=0;
	//Si no es un rectángulo nulo, es decir, ya he elegido otro rectángulo
	if (R.IsRectEmpty()==0 )
	{
		if (tipo_orden==1)
		{
			esqii=pow(R.top,2)+pow(R.left,2);
			esqid=pow(R.top,2)+pow(m_L-R.right,2);
			esqsi=pow(m_W-R.bottom,2)+pow(R.left,2);
			esqsd=pow(m_W-R.bottom,2)+pow(m_L-R.right,2);

			maximo=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			maximo=R.left;
		}
	}

	for (it=lista.begin();it!=lista.end() ;it++)
	{
		if (R.top==(*it).top && R.bottom==(*it).bottom && R.left==(*it).left && R.right==(*it).right)
			continue;
		if (tipo_orden==1)
		{
		//minimo de la distancia a las esquinas
			esqii=pow((*it).top,2)+pow((*it).left,2);
			esqid=pow((*it).top,2)+pow(m_L-(*it).right,2);
			esqsi=pow(m_W-(*it).bottom,2)+pow((*it).left,2);
			esqsd=pow(m_W-(*it).bottom,2)+pow(m_L-(*it).right,2);

			minimoEste=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			minimoEste=(*it).left;
		}
		//Si es menor y mayor que el que tenía
		//Si es menor y mayor que el que tenía
		if (minimoEste<=minimo && minimoEste>=maximo)
		{
			if (R.IsRectEmpty()!=0)
			{
				if (minimoEste==minimo)
				{
					if (((*it).left)<=(r1.left))
					{
						if (((*it).left)==(r1.left))
						{
							if ((*it).Height()<r1.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=minimoEste;
							}
							//elegir el más pqegado a una esquina
							if ((*it).Height()==r1.Height() )
							{
								if ((*it).top<(m_W-r1.bottom) || r1.top<(m_W-(*it).bottom) )
								{
									r1.top=(*it).top;
									r1.bottom=(*it).bottom;
									r1.left=(*it).left;
									r1.right=(*it).right;
									minimo=minimoEste;
								}
								
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=minimoEste;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=minimoEste;
				}
			}
			else
			{
				if (minimoEste==maximo)
				{
					if (((*it).left)>=(R.left))
					{
						if (((*it).left)==(R.left))
						{
							if ((*it).Height()>R.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=minimoEste;
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=minimoEste;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=minimoEste;
				}
			}
		}
	}
	if (r1.IsRectEmpty()!=0)
	{
		resultante.top=0;
		resultante.bottom=0;
		resultante.left=0;
		resultante.right=0;
	}
	else
	{
		resultante.top=r1.top;
		resultante.bottom=r1.bottom;
		resultante.left=r1.left;
		resultante.right=r1.right;

	}
}
void CUTTING::Elijo_Menor_Lista(RECTAN R, RECTAN &resultante, int tipo_orden)
{
	//Si tipo de orden es uno
	//es el más cercano a la esquina en otro caso

	//es el menor en área
	RECTAN r1(0,0,0,0);
	std::list<RECTAN> ::iterator it;
	int minimo=999999,maximo=0,minimoEste=0;
	int esqii=0,esqid=0,esqsd=0,esqsi=0;
	if (R.IsRectEmpty()==0 )
	{
		if (tipo_orden==1)
		{
			esqii=pow(R.top,2)+pow(R.left,2);
			esqid=pow(R.top,2)+pow(m_L-R.right,2);
			esqsi=pow(m_W-R.bottom,2)+pow(R.left,2);
			esqsd=pow(m_W-R.bottom,2)+pow(m_L-R.right,2);

			maximo=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			maximo=R.Width()*R.Height();
		}
	}

	for (it=m_lista_perdidas.begin();it!=m_lista_perdidas.end() ;it++)
	{
		if (R.top==(*it).top && R.bottom==(*it).bottom && R.left==(*it).left && R.right==(*it).right)
			continue;
		if (tipo_orden==1)
		{
		//minimo de la distancia a las esquinas
			esqii=pow((*it).top,2)+pow((*it).left,2);
			esqid=pow((*it).top,2)+pow(m_L-(*it).right,2);
			esqsi=pow(m_W-(*it).bottom,2)+pow((*it).left,2);
			esqsd=pow(m_W-(*it).bottom,2)+pow(m_L-(*it).right,2);

			minimoEste=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			minimoEste=((*it).Width())*((*it).Height());
		}
		//Si es menor y mayor que el que tenía
		if (minimoEste<=minimo && minimoEste>=maximo)
		{
			if (R.IsRectEmpty()!=0)
			{
				if (minimoEste==minimo)
				{
					if (((*it).Height()*(*it).Width())<=(r1.Height()*r1.Width()))
					{
						if (((*it).Height()*(*it).Width())==(r1.Height()*r1.Width()))
						{
							if ((*it).Height()<r1.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=minimoEste;
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=minimoEste;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=minimoEste;
				}
			}
			else
			{
				if (minimoEste==maximo)
				{
					if (((*it).Height()*(*it).Width())>=(R.Height()*R.Width()))
					{
						if (((*it).Height()*(*it).Width())==(R.Height()*R.Width()))
						{
							if ((*it).Height()>R.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=minimoEste;
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=minimoEste;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=minimoEste;
				}
			}
		}
	}
	if (r1.IsRectEmpty()!=0)
	{
		resultante.top=0;
		resultante.bottom=0;
		resultante.left=0;
		resultante.right=0;
	}
	else
	{
		resultante.top=r1.top;
		resultante.bottom=r1.bottom;
		resultante.left=r1.left;
		resultante.right=r1.right;

	}
}
void CUTTING::Elijo_Menor_ListaStrip(RECTAN R, RECTAN &resultante, int tipo_orden,bool all)
{
	//Si tipo de orden es uno
	//es el más cercano a la esquina en otro caso

	//es el menor en área
	RECTAN r1(0,0,0,0);
	std::list<RECTAN> ::iterator it;
	int minimo=999999,maximo=0,minimoEste=0;
	int esqii=0,esqid=0,esqsd=0,esqsi=0;
	if (R.IsRectEmpty()==0 )
	{
		if (tipo_orden==1)
		{
			esqii=pow(R.top,2)+pow(R.left,2);
			esqid=pow(R.top,2)+pow(m_L-R.right,2);
			esqsi=pow(m_W-R.bottom,2)+pow(R.left,2);
			esqsd=pow(m_W-R.bottom,2)+pow(m_L-R.right,2);

			maximo=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			maximo= R.left;
		}
	}

	for (it=m_lista_perdidas.begin();it!=m_lista_perdidas.end() ;it++)
	{
		if (R.top==(*it).top && R.bottom==(*it).bottom && R.left==(*it).left && R.right==(*it).right)
			continue;
		if ((*it).right!=m_L && all==false) continue;
		if (tipo_orden==1)
		{
		//minimo de la distancia a las esquinas
			esqii=pow((*it).top,2)+pow((*it).left,2);
			esqid=pow((*it).top,2)+pow(m_L-(*it).right,2);
			esqsi=pow(m_W-(*it).bottom,2)+pow((*it).left,2);
			esqsd=pow(m_W-(*it).bottom,2)+pow(m_L-(*it).right,2);

			minimoEste=__min(__min(esqii,esqid),__min(esqsi,esqsd));
		}
		else
		{
			minimoEste=(*it).left;
		}
		//Si es menor y mayor que el que tenía
		if (minimoEste<=minimo && minimoEste>=maximo)
		{
			if (R.IsRectEmpty()!=0)
			{
				if (minimoEste==minimo)
				{
					if (((*it).Height()*(*it).Width())<=(r1.Height()*r1.Width()))
					{
						if (((*it).Height()*(*it).Width())==(r1.Height()*r1.Width()))
						{
							if ((*it).Height()<r1.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=(*it).left;
							}
							//elegir el más pqegado a una esquina
							if ((*it).Height()==r1.Height() )
							{
								if ((*it).top<(m_W-r1.bottom) || r1.top<(m_W-(*it).bottom) )
								{
									r1.top=(*it).top;
									r1.bottom=(*it).bottom;
									r1.left=(*it).left;
									r1.right=(*it).right;
									minimo=minimoEste;
								}
								
							}


						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=(*it).left;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=(*it).left;
				}
			}
			else
			{
				if (minimoEste==maximo)
				{
					if (((*it).Height()*(*it).Width())>=(R.Height()*R.Width()))
					{
						if (((*it).Height()*(*it).Width())==(R.Height()*R.Width()))
						{
							if ((*it).Height()>R.Height() )
							{
								r1.top=(*it).top;
								r1.bottom=(*it).bottom;
								r1.left=(*it).left;
								r1.right=(*it).right;
								minimo=(*it).left;
							}

						}
						else
						{
							r1.top=(*it).top;
							r1.bottom=(*it).bottom;
							r1.left=(*it).left;
							r1.right=(*it).right;
							minimo=(*it).left;
						}
					}

				}
				else
				{
					r1.top=(*it).top;
					r1.bottom=(*it).bottom;
					r1.left=(*it).left;
					r1.right=(*it).right;
					minimo=(*it).left;
				}
			}
		}
	}
	if (r1.IsRectEmpty()!=0)
	{
		resultante.top=0;
		resultante.bottom=0;
		resultante.left=0;
		resultante.right=0;
	}
	else
	{
		resultante.top=r1.top;
		resultante.bottom=r1.bottom;
		resultante.left=r1.left;
		resultante.right=r1.right;

	}
}
//Cuenta lo que vale la solución a partir de los bloques que tiene
int CUTTING::ContarSolucion(std::list<BLOQUE> &listaT)
{
	int Val=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=listaT.begin();itB!=listaT.end();itB++)
	{
		//No se en el bloque cuantas piezas hay se el número del bloque
        Val+=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho))*(m_Piezas[(*itB).GetNumero()].valor);
	}
	//Resto una cantidad por las incompatibilidades
	if (m_Restringido==true)
	{
		for(register int kcon=0;kcon<m_Numpiezas;kcon++)
		{
			//No se en el bloque cuantas piezas hay se el número del bloque
		    Val-=__max(0,m_Piezas[kcon].min-m_Piezas[kcon].num)*10000;
			//Por como las ordeno
			if (m_Piezas[kcon].min==0) return Val;
		}
	}
	return Val;
}
//Cuenta lo que vale la solución a partir de los bloques que tiene
int CUTTING::ContarSolucionStrip(std::list<BLOQUE> &listaT)
{
	int max=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=listaT.begin();itB!=listaT.end();itB++)
	{
		//No se en el bloque cuantas piezas hay se el número del bloque
        if ((*itB).right>max)
			max=(*itB).right;
	}
	return max;
}
int CUTTING::ContarPiezas(std::list<BLOQUE> &listaT)
{
	int Val=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=listaT.begin();itB!=listaT.end();itB++)
	{
		//No se en el bloque cuantas piezas hay se el número del bloque
        Val+=(((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho));
	}
	return Val;
}


void CUTTING::AumentarBloque(MOVE &M1)
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
		//No lo meto tengo que cambiar los números
		m_Piezas[(*itB).GetNumero()].num-=((*itB).Width()*(*itB).Height())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho);

	}
}

void CUTTING::AumentarBloque(BLOQUE &M1)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	std::list<BLOQUE> lista_aux;
	//Creo lista de pérdidas nuevas y lista de bloques nueva
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
//		BLOQUE b11=(*itB);
		//Los que esten incluidos dentro del nuevo rectángulo los quito
		if ((((*itB).bottom<=M1.bottom) && ((*itB).top>=M1.top))
		&& (((*itB).right<=M1.right) && ((*itB).left>=M1.left)))
			continue;
		if( (*itB).top>=M1.bottom || M1.top>=(*itB).bottom )
		{
			lista_aux.push_back((*itB));
			continue;
		}
		if( (*itB).left>=M1.right || M1.left>=(*itB).right)
		{
			lista_aux.push_back((*itB));
			continue;
		}
		//Solapa con el bloque nuevo
		//No lo meto tengo que cambiar los números
		m_Piezas[(*itB).GetNumero()].num-=((*itB).Width()*(*itB).Height())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho);

	}
	m_lista_bloques.clear();
	m_lista_bloques.insert(m_lista_bloques.begin(),lista_aux.begin(),lista_aux.end());
}
//Coloca el bloque lo más a la esquina posible dependiendo donde esta el rectángulo
//de pérdida los nuevos rectángulos de pérdida no se ponen siempre en el mismo orden
//para que la lista tenga algo de aleatoriedad.
void CUTTING::ColocarEsquinaMasCercanaStrip(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho)
{
	int k=get_random(0,1);
	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	RECTAN Nuevo1,Nuevo2;
	//*Lado derecho

		B1.left=Rect.left;
		B1.right=B1.left+largo;
		RECTAN rectA(Rect.left,Rect.top,Rect.right,Rect.bottom-ancho);
		bool puede_ser=true;
		if (ycenter>(m_W/2) && CabeAlgunaAncho(rectA)==0)
			puede_ser=false;

		//Arriba o abajo
		if (ycenter>(m_W/2) && puede_ser==false)
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
			
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;
				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=B1.top;
				Nuevo2.left=B1.right;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}
			//Esquina izquierda arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;
				Nuevo2.right=Rect.right;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.left=B1.right;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}

			//Esquina izquierda abajo
		}
}

//coloca la pieza según la lo hace monaci
//Coloca el bloque lo más a la esquina posible dependiendo donde esta el rectángulo
//de pérdida los nuevos rectángulos de pérdida no se ponen siempre en el mismo orden
//para que la lista tenga algo de aleatoriedad.
//También actualiza ya la lista de rectángulos a cortar
void CUTTING::ColocarEsquinaMonaciStrip(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho)
{
//	int k=get_random(0,1);
	int k=1;
	RECTAN Nuevo1,Nuevo2;
	//*Lado derecho

		B1.left=Rect.left;
		B1.right=B1.left+largo;
		int coloco=DondeColocoMonaci(Rect,B1);

		//Arriba o abajo
		if (coloco==1)
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
			
			if (!(B1.IsRectEmpty()))
			{
				//El de abajo
				//que no se va a poder juntar 
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;
				//el de al lado

				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=B1.top;
				Nuevo2.left=B1.right;
				BorrarListaPerdidas(Rect);

				//Si no es vacio
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty())
					{
						
						lista.push_back(Nuevo1);
					}
					if (!Nuevo2.IsRectEmpty()) 
					{
						//busco una función rápida que me junte este rectángulo
						JuntarRectangulo(Nuevo2);
					}
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) 
					{
						//busco una función rápida que me junte este rectángulo
						JuntarRectangulo(Nuevo2);
					}
					if (!Nuevo1.IsRectEmpty())
					{
						
						lista.push_back(Nuevo1);
					}
				}

			}
			//Esquina izquierda arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;
			if (!(B1.IsRectEmpty()))
			{
				//El de arriba
				//que no se va a poder juntar 
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;
				//El de al lado

				Nuevo2.right=Rect.right;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.left=B1.right;
				BorrarListaPerdidas(Rect);

				//Si no es vacio
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty())
					{
						
						lista.push_back(Nuevo1);
					}
					if (!Nuevo2.IsRectEmpty()) 
					{
						//busco una función rápida que me junte este rectángulo
						JuntarRectangulo(Nuevo2);
					}
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) 
					{
						//busco una función rápida que me junte este rectángulo
						JuntarRectangulo(Nuevo2);
					}
					if (!Nuevo1.IsRectEmpty())
					{
						
						lista.push_back(Nuevo1);
					}

				}
			}

			//Esquina izquierda abajo
		}
}
//Coloco se´gun Monaci 0--abajo; 1--arriba
int CUTTING::DondeColocoMonaci(RECTAN &Rect, BLOQUE &B)
{
	//CAMBIO
//	if (Rect.top==0) return 0;
	if (Rect.top==0 && Rect.bottom==m_W) return get_random(0,1);
	//anchura de los de abajo
	int a1=0;
//	if ((Rect.top)<m_MinAncho) a1=0;
//	if ((Rect.top)<m_MinAncho) return 0;
//	else a1=Altura(Rect.top,0);
	//CAMBIO
//	if (a1>=Rect.left+B.Width()) return 0;
	if (Rect.top==0) return 0;
	if (Rect.bottom==m_W) return 1;
	//anchura de los de arriba
	int a2=0;
//	if ((m_W-Rect.bottom)<m_MinAncho) return 1;
//	else a2=Altura(Rect.bottom,1);
	a1=Altura(Rect.top,0);
	a2=Altura(Rect.bottom,1);
//	if (a2>=Rect.left+B.Width()) return 1;
//CAMBIO
	//
//	if (a1>=a2) return 0;
//	else return 1;
//	if (m_Determinista==true || get_random(0,1)==1)
//	{

	if (a1>a2)
	{
		if (a2==Rect.left+B.Width()) return 1;

		return 0;
	}
	if (a2>a1) 
	{
		if (a1==Rect.left+B.Width()) return 0;
		return 1;
	}
	if (a1==a2)
	{
		if (Rect.top<(m_W-Rect.bottom)) return 0;
		if (Rect.top>(m_W-Rect.bottom)) return 1;
	}
	return get_random(0,1);
/*	}
	else
	{
	if (Rect.top<(m_W-Rect.bottom)) return 0;
	if (Rect.top>(m_W-Rect.bottom)) return 1;
	if (Rect.top==(m_W-Rect.bottom))
	{
		if (a1>a2) return 0;
		if (a2>a1) return 1;
	}
	return get_random(0,1);

	}
	return get_random(0,1);*/
}
//coloca la pieza según la lo hace monaci
//Coloca el bloque lo más a la esquina posible dependiendo donde esta el rectángulo
//de pérdida los nuevos rectángulos de pérdida no se ponen siempre en el mismo orden
//para que la lista tenga algo de aleatoriedad.
//También actualiza ya la lista de rectángulos a cortar
void CUTTING::ColocarEsquinaMonaciModiStrip(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho)
{
//	int k=get_random(0,1);
	int k=1;
	RECTAN Nuevo1,Nuevo2;
	//*Lado derecho

		B1.left=Rect.left;
		B1.right=B1.left+largo;
		int coloco=DondeColocoMonaciModi(Rect,B1);

		//Arriba o abajo
		if (coloco==1)
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
			
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;


				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=B1.top;
				Nuevo2.left=B1.right;
				//Si no es vacio
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}
			//Esquina izquierda arriba
		}
		if (coloco==0)
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;

				Nuevo2.right=Rect.right;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.left=B1.right;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}

			//Esquina izquierda abajo
		}
		//Arriba
		std::list<BLOQUE>::iterator itB;
		if (coloco==3)
		{
			BLOQUE B2;
			int top=0;
			//Actualizar bloque
			for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
			{
				if (B1.bottom==(*itB).bottom && B1.left==(*itB).left)
				{
					int ankk=(*itB).Height();

					(*itB).bottom=B1.top;
					(*itB).top=(*itB).bottom-ankk;
					top=(*itB).top;
					B2=(*itB);
				}
			}
			Actualizar_Perdida_Simetria(B1,1,B2.right);
			if (!(B1.IsRectEmpty()))
			{
				//Rectángulo de abajo
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B2.top;

				//Rectángulo de al lado
				Nuevo2.bottom=B1.top;
				Nuevo2.right=m_L;

				Nuevo2.top=Nuevo1.bottom;
				Nuevo2.left=B2.right;
				//Si no es vacio
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}
		}
		//Abajo
		if (coloco==2)
		{
			BLOQUE B2;
			int bottom=0;
			//Actualizar bloque
			for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
			{
				if (B1.top==(*itB).top && B1.left==(*itB).left)
				{
					int ankk=(*itB).Height();

					(*itB).top=B1.bottom;
					(*itB).bottom=(*itB).top+ankk;
					bottom=(*itB).bottom;
					B2=(*itB);
				}
			}
			Actualizar_Perdida_Simetria(B1,0,B2.right);
			if (!(B1.IsRectEmpty()))
			{
				//Rectángulo de arriba
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B2.bottom;
				//De al lado
				Nuevo2.right=Rect.right;
				Nuevo2.top=B2.top;
				Nuevo2.bottom=B2.bottom;
				Nuevo2.left=B2.right;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}

			//Esquina izquierda abajo
		}

}
void CUTTING::Actualizar_Perdida_Simetria(BLOQUE &B1,int movido,int min)
{
	std::list<RECTAN> ::iterator itL;
	//Actualizar pérdida
	bool stop=false;
	for(itL=m_lista_perdidas.begin();stop!=true && itL!=m_lista_perdidas.end();itL++)
	{
		RECTAN R=((*itL));
		if ((*itL).right!=m_L) continue;
		if (B1.bottom>=(*itL).bottom && B1.top<=(*itL).top)
		{
			RECTAN R1;
			R1.top=B1.top;
			R1.left=B1.right;
			R1.right=m_L;
			R1.bottom=B1.bottom;
			if (R1.Height()==0)
				int koil=9;
			m_lista_perdidas.push_back(R1);
			itL=m_lista_perdidas.erase(itL);
			stop=true;
		}
		if ((B1.bottom<(*itL).bottom && B1.top>=(*itL).top)|| (B1.bottom<=(*itL).bottom && B1.top>(*itL).top) ||
			(B1.bottom<(*itL).bottom && B1.bottom>(*itL).top && movido==1) || (B1.top<(*itL).bottom && B1.top>(*itL).top && movido==0))
		{
			if (B1.bottom<(*itL).bottom && movido!=0)
			{
				RECTAN R;
				R.top=B1.bottom;
				R.left=(*itL).left;
				R.right=(*itL).right;
				R.bottom=(*itL).bottom;
				m_lista_perdidas.push_back(R);
				stop=true;
			}
			if (B1.top>(*itL).top && movido!=1)
			{
				RECTAN R;
				R.top=(*itL).top;
				R.left=(*itL).left;
				R.right=(*itL).right;
				R.bottom=B1.top;
				m_lista_perdidas.push_back(R);
				stop=true;
			}
			RECTAN R1;
			R1.top=B1.top;
			R1.left=B1.right;
			R1.right=m_L;
			R1.bottom=B1.bottom;
			m_lista_perdidas.push_back(R1);
			itL=m_lista_perdidas.erase(itL);
			stop=true;
		}

	}

}
//Coloco se´gun Monaci 0--abajo; 1--arriba
int CUTTING::DondeColocoMonaciModi(RECTAN &Rect, BLOQUE &B)
{
	if (Rect.top==0) return 0;
	BLOQUE b0,b1;
	if (Rect.top==0 && Rect.bottom==m_W) return get_random(0,1);
	//anchura de los de abajo
	int a1=0;
//	if ((Rect.top)<m_MinAncho) a1=0;
//	if ((Rect.top)<m_MinAncho) return 0;
//	else a1=Altura(Rect.top,0);
	//CAMBIO
//	if (a1>=Rect.left+B.Width()) return 0;
	if (Rect.top==0) return 0;
	if (Rect.bottom==m_W) return 1;

	int altura_abajo=0;
	altura_abajo=Altura(Rect.top,0,b0);
	if (altura_abajo>=Rect.left+B.Width()) return 1;
	int altura_arriba=0;
	altura_arriba=Altura(Rect.bottom,1,b1);
	if (altura_arriba>=Rect.left+B.Width()) return 1;
	//Hago una simetría pero no se de cuantás 
	//suponer que haya dos iguales pero es muy dificil porque
	//tendría que mirar que la anterior también empieza en el mismo sitio
	int anchotemp=B.Height();
	if (altura_abajo>=altura_arriba && b0.left==B.left)
	{
		B.top=b0.top;
		B.bottom=B.top+anchotemp;
		return 2;
	}

	if (altura_abajo<altura_arriba && b1.left==B.left)
	{
		B.bottom=b1.bottom;
		B.top=B.bottom-anchotemp;
		return 3;
	}
	if (b0.left==B.left)
	{
		B.top=b0.top;
		B.bottom=B.top+anchotemp;
		return 2;
	}

	if (b1.left==B.left)
	{
		B.bottom=b1.bottom;
		B.top=B.bottom-anchotemp;
		return 3;
	}

	if (altura_abajo>=altura_arriba) return 0;
	else return 1;


}
int CUTTING::Altura(int A,int tipo)
{
	int max=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{

		if (tipo==0)
		{
			if ((*itB).bottom==A)
			{
			     if ((*itB).right>max)
					max=(*itB).right;
			}
		}
		else
		{
			if ((*itB).top==A)
			{
				 if ((*itB).right>max)
					max=(*itB).right;
			}
		}
	}
	return max;

}

int CUTTING::Altura(int A,int tipo,BLOQUE &B)
{
	int max=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{

		if (tipo==0)
		{
			if ((*itB).bottom==A)
			{
			     if ((*itB).right>max)
				 {
					max=(*itB).right;
					B=(*itB);
				 }
			}
		}
		else
		{
			if ((*itB).top==A)
			{
				 if ((*itB).right>max)
				 {
					max=(*itB).right;
					B=(*itB);
				 }
			}
		}
	}
	return max;

}
int CUTTING::AreaRestante(int A)
{
	int max=0;
	std::list<RECTAN>::iterator itB;
	for(itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
		if ((*itB).right!=m_L) continue;
		else
		{
			if ((*itB).left<A)
			{
				max+=(A-(*itB).left)*((*itB).Height());
			}

		}
/*		if ((*itB).left<A)
		{
			if ((*itB).right!=m_L)
			max+=((*itB).Width())*((*itB).Height());
			else
			max+=(A-(*itB).left)*((*itB).Height());
		}
*/
	}

	return max;

}
int CUTTING::AreaRestanteSiguiente(RECTAN &rectan,int largo_bloque,int ancho_bloque,int ancho_pieza, int long_pieza)
{
	int sobra=rectan.Height()-ancho_bloque;
	BLOQUE B1(0,0,0,0);
	bool arriba=false;
	if (sobra<m_MinAncho)
	{
	B1.top=0;
	B1.bottom=ancho_bloque;
	B1.left=rectan.left;
	B1.right=B1.left+largo_bloque;
	int coloco=DondeColocoMonaci(rectan,B1);
	if (coloco==1) arriba=true;
	else arriba=false;
	}
	int max=0;
	std::list<RECTAN>::iterator itB;
	for(itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
		if ((*itB).Height()>=ancho_pieza)
		{
			max+=(*itB).left;
		}
		else
		{
			if (sobra<m_MinAncho)
			{
				if ((*itB).bottom==rectan.top && arriba==true && (*itB).Height()+sobra>=ancho_pieza)
				{
					max+=(*itB).left;
				}
				if ((*itB).top==rectan.bottom && arriba==false && (*itB).Height()+sobra>=ancho_pieza)
				{
					max+=(*itB).left;
				}
			}
		}

	}
	//Tengo en max el maximo 
	if (max==0) 
	{
		max=rectan.left+largo_bloque;
	}
	else
	{
		max=__min(max,rectan.left+largo_bloque);
	}
//	if (m_Determinista!=true && (max)>=m_solbest) 
	if (m_Determinista!=true && (max+long_pieza)>=m_solbest) 
		return 4*m_total_superficie;
	return AreaRestante(max+long_pieza);

}
int CUTTING::AreaRestanteSiguiente(RECTAN &Rect, int largo_suple,int ancho_pieza, int long_pieza)
{

	//Busco el último rectángulo donde lo puedo meter
	int max=99999;
	std::list<RECTAN>::iterator itB;
	for(itB=m_lista_perdidas.begin();itB!=m_lista_perdidas.end();itB++)
	{
//cambiar		if ( (*itB).Height()>=ancho_pieza)
		if (((*itB).left>Rect.left || ((*itB).left==Rect.left && (*itB).top!=Rect.top)) && (*itB).Height()>=ancho_pieza)
		{
			if ((*itB).left<max) max=(*itB).left;
		}
	}

	//Tengo en max el maximo 
	if (max==99999) 
	{
		max=Rect.left+largo_suple;
	}
	else
	{
		max=__min(max,Rect.left+largo_suple);
	}
	//¿EStaría mal tendría que poner si se pasa de vueltas?
	if (m_Determinista!=true && max+long_pieza>m_solbest) return 2*m_AreaTotalRestante;
	return AreaRestante(max+long_pieza);

}
//Coloca el bloque lo más cerca de alguna de las esquinas del tablero
//dependiendo donde esta el rectángulo
//de pérdida los nuevos rectángulos de pérdida no se ponen siempre en el mismo orden
//para que la lista tenga algo de aleatoriedad.
void CUTTING::ColocarEsquinaMasCercana(RECTAN &Rect,BLOQUE &B1)
{
	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	int largo=B1.Width();
	int ancho=B1.Height();

	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	RECTAN Nuevo1,Nuevo2;
	//*Lado derecho
	if (xcenter>(m_L/2))
	{
		if (Rect.left+B1.Width()>m_L)
		{
			B1.right=Rect.right;
			B1.left=B1.right-largo;
		}
		else
		{
			int alea=get_random(0,1);
			if (alea==0)
			{
				B1.left=Rect.left;
				B1.right=B1.left+largo;
			}
			else
			{
				B1.right=Rect.right;
				B1.left=B1.right-largo;
			}

		}
		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			if (Rect.top+B1.Height()>m_W)
			{
				B1.bottom=Rect.bottom;
				B1.top=B1.bottom-ancho;
			}
			else
			{
				int alea=get_random(0,1);
				if (alea==0)
				{
					B1.top=Rect.top;
					B1.bottom=B1.top+ancho;
				}
				else
				{
					B1.bottom=Rect.bottom;
					B1.top=B1.bottom-ancho;
				}

			}
		}
		else
		{
			if (Rect.bottom-B1.Height()<0)
			{
				B1.top=Rect.top;
				B1.bottom=B1.top+ancho;
			}
			else
			{
				int alea=get_random(0,1);
				if (alea==0)
				{
					B1.top=Rect.top;
					B1.bottom=B1.top+ancho;
				}
				else
				{
					B1.bottom=Rect.bottom;
					B1.top=B1.bottom-ancho;
				}

			}
		}
	}
	//Lado izquierdo
	else
	{
		if (Rect.right-B1.Width()<0)
		{
			B1.left=Rect.left;
			B1.right=B1.left+largo;
		}
		else
		{
			int alea=get_random(0,1);
			if (alea==0)
			{
				B1.left=Rect.left;
				B1.right=B1.left+largo;
			}
			else
			{
				B1.right=Rect.right;
				B1.left=B1.right-largo;
			}

		}

		//Arriba o abajo
		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			if (Rect.top+B1.Height()>m_W)
			{
				B1.bottom=Rect.bottom;
				B1.top=B1.bottom-ancho;
			}
			else
			{
				int alea=get_random(0,1);
				if (alea==0)
				{
					B1.top=Rect.top;
					B1.bottom=B1.top+ancho;
				}
				else
				{
					B1.bottom=Rect.bottom;
					B1.top=B1.bottom-ancho;
				}

			}
		}
		else
		{
			if (Rect.bottom-B1.Height()<0)
			{
				B1.top=Rect.top;
				B1.bottom=B1.top+ancho;
			}
			else
			{
				int alea=get_random(0,1);
				if (alea==0)
				{
					B1.top=Rect.top;
					B1.bottom=B1.top+ancho;
				}
				else
				{
					B1.bottom=Rect.bottom;
					B1.top=B1.bottom-ancho;
				}

			}
		}

	}
	//Si la pieza es muy grande para que no 
	//tenga que empezar ni terminar donde hemos dicho
	if (B1.top<0) 
	{
		B1.bottom-=B1.top;
		B1.top=0;
	}
	if (B1.left<0) 
	{
		B1.right-=B1.left;
		B1.left=0;
	}
	if (B1.bottom>m_W) 
	{
		B1.top+=(m_W-B1.bottom);
		B1.bottom=m_W;
	}
	if (B1.right>m_L) 
	{
		B1.left+=(m_L-B1.right);
		B1.right=m_L;
	}

}

//Coloca el bloque lo más cerca de alguna de las esquinas del tablero
//dependiendo donde esta el rectángulo
//de pérdida los nuevos rectángulos de pérdida no se ponen siempre en el mismo orden
//para que la lista tenga algo de aleatoriedad.
void CUTTING::ColocarEsquinaMasCercanaStrip(RECTAN &Rect,BLOQUE &B1)
{
	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	int largo=B1.Width();
	int ancho=B1.Height();

	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	RECTAN Nuevo1,Nuevo2;
	//lado izquierdo
	B1.left=Rect.left;
	B1.right=B1.left+largo;
	B1.top=Rect.top;
	B1.bottom=B1.top+ancho;



	//Si la pieza es muy grande para que no 
	//tenga que empezar ni terminar donde hemos dicho
	if (B1.top<0) 
	{
		B1.bottom-=B1.top;
		B1.top=0;
	}
	if (B1.left<0) 
	{
		B1.right-=B1.left;
		B1.left=0;
	}
	if (B1.bottom>m_W) 
	{
		B1.top+=(m_W-B1.bottom);
		B1.bottom=m_W;
	}
	if (B1.right>m_L) 
	{
		B1.left+=(m_L-B1.right);
		B1.right=m_L;
	}

}
void CUTTING::ColocarEsquinaMasCercana(RECTAN &Rect,BLOQUE &B1,int esq)
{
	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	int largo=B1.Width();
	int ancho=B1.Height();

	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	RECTAN Nuevo1,Nuevo2;
	//*Lado derecho
								//1 derecha arriba 
								//2 derecha abajo
								//3 izquierda arriba
								//4 izquierda abajo

	if (esq==1 ||esq==2)
	{
		B1.right=Rect.right;
		B1.left=B1.right-largo;
		//Arriba o abajo
		if (esq==1)
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;
		}
	}
	//Lado izquierdo
	else
	{
		B1.left=Rect.left;
		B1.right=B1.left+largo;

		//Arriba o abajo
		//Arriba o abajo
		if (esq==3)
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;
		}
	}
	//Si la pieza es muy grande para que no 
	//tenga que empezar ni terminar donde hemos dicho
	if (B1.top<0) 
	{
		B1.bottom-=B1.top;
		B1.top=0;
	}
	if (B1.left<0) 
	{
		B1.right-=B1.left;
		B1.left=0;
	}
	if (B1.bottom>m_W) 
	{
		B1.top+=(m_W-B1.bottom);
		B1.bottom=m_W;
	}
	if (B1.right>m_L) 
	{
		B1.left+=(m_L-B1.right);
		B1.right=m_L;
	}

}
void CUTTING::DibujarSolucion(std::list<BLOQUE> &lista_bloques,std::list<RECTAN> &lista_per,int sol,int perdida)
{
//	if (m_ValSolucion!=m_solbest || m_lista_bloques.size()!=m_Numpiezas) return;
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
}
void CUTTING::DibujarSolucion(std::list<BLOQUE> &lista_bloques,std::list<RECTAN> &lista_per,int sol,int perdida, BLOQUE &B)
{
//	if (m_ValSolucion!=m_solbest && m_lista_bloques.size()!=m_Numpiezas) return;
	if (m_Dibujar==true)
	{
		DibujarBloques(lista_bloques,lista_per,m_iter_actual,sol,perdida,m_solbest,m_paso_a_paso,m_lista_tabu.size(),B);
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
}
//Esta es la que dibuja en el strip
void CUTTING::DibujarBloques(std::list<BLOQUE> &lista_bloques,std::list<RECTAN> &lista_per,int contador,int sol,int perdida,int solbest, bool parar, int veces)
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
	CString ss,ss1,ss2,ss3,ss4,ss5,ss6;
	char pallet[120],buff[20],vecesc[5];
	strcpy(pallet,m_Nombre);
	strcat(pallet," Tablero ");
	
	itoa(m_L,buff,10);
	strcat(pallet,buff);
	strcat(pallet,"X");
	itoa(m_W,buff,10);
	strcat(pallet,buff);
	strcat(pallet," Piezas ");
	itoa(m_Numpiezas,buff,10);
	strcat(pallet,buff);
//	strcat(pallet," ");
//	itoa(m_l,buff,10);
//	strcat(pallet,buff);
//	strcat(pallet," ");
//	itoa(m_w,buff,10);
//	strcat(pallet,buff);
//	strcat(pallet," ");
	itoa(perdida,buff,10);
	itoa(veces,vecesc,10);
	ss6.Format("%s","    ");
	ss4.Format("%s",pallet);
	ss.Format("%d",contador);
	ss1.Format("%d",sol);
	ss2.Format("%d",m_iter_actual);
	ss3.Format("%d",m_solbest);
	m_clientedc->TextOut((m_factor*m_L/5),(-m_factor*(m_W))*(1.1),ss4);
//	m_clientedc->TextOut( m_factor*m_L, -m_factor*m_W,ss );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.75), ss6 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.75), ss1 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.5), ss2 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.25), ss3 );
//	m_clientedc->TextOut( m_factor*m_L, 0, ss5 );
	
	int L,w;
	std::list<BLOQUE> ::iterator itB;
	std::list<RECTAN> ::iterator itL;
//	m_clientedc->SetBkMode(TRANSPARENT);
//	m_clientedc->SetPolyFillMode(ALTERNATE);
	m_clientedc->SelectObject(brushclaro);

	for (itL=lista_per.begin();itL!=lista_per.end();itL++)
	{
		
		m_clientedc->Rectangle(m_factor*((*itL).left),-m_factor*((*itL).top),m_factor*((*itL).right),-m_factor*((*itL).bottom));
	}
//	m_clientedc->SetBkColor(RGB(255,255,255));
//	m_clientedc->SetBkMode(OPAQUE);
	int kk=0;
	for (itB=lista_bloques.begin();itB!=lista_bloques.end();itB++)
	{
		m_clientedc->SelectObject(brushblanco);
		kk+=3;
		L=m_Piezas[(*itB).GetNumero()].largo;
		w=m_Piezas[(*itB).GetNumero()].ancho;
		if (m_PuedenRotarsePiezas==true)
		{
			div_t div_result1,div_result2;

			div_result1 = div( (*itB).Width(), m_Piezas[(*itB).GetNumero()].largo );
			div_result2 = div( (*itB).Height(), m_Piezas[(*itB).GetNumero()].ancho );
			if (div_result1.rem!=0 || div_result2.rem!=0)
			{
				m_clientedc->SelectObject(brushrojo);

				w=m_Piezas[(*itB).GetNumero()].largo;
				L=m_Piezas[(*itB).GetNumero()].ancho;

			}
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
	int y1=0;

/*	if (m_L<=m_W)
	{
		m_clientedc->Rectangle(m_factor*-(0.75*m_L),-m_factor*0,m_factor*(0),-m_factor*(m_W));
		for (register int i=0;i<m_Numpiezas;i++)
		{
			int x1=-(0.5*m_L);
			if (m_Piezas[i].num<m_Piezas[i].max)
			{
					m_clientedc->Rectangle(m_factor*x1,-m_factor*y1,m_factor*(x1+(m_Piezas[i].largo)),-m_factor*(y1+(m_Piezas[i].ancho)));
					y1=y1+m_Piezas[i].ancho+2;
			}
		}
	}
	else
	{
		m_clientedc->Rectangle(m_factor*(0),-m_factor*(0),m_factor*(m_L),-m_factor*(-m_W));
		int x1=0;
		for (register int i=0;i<m_Numpiezas;i++)
		{
			int y1=-(0.3*m_W);
			if (m_Piezas[i].num<m_Piezas[i].max)
			{
					m_clientedc->Rectangle(m_factor*x1,-m_factor*y1,m_factor*(x1+(m_Piezas[i].largo)),-m_factor*(y1+(m_Piezas[i].ancho)));
					x1=x1+m_Piezas[i].largo+2;
			}
		}
	}
*/

}
void CUTTING::DibujarBloques(std::list<BLOQUE> &lista_bloques,std::list<RECTAN> &lista_per,int contador,int sol,int perdida,int solbest, bool parar, int veces, BLOQUE &B)
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
	CString ss,ss1,ss2,ss3,ss4,ss5,ss6;
	char pallet[120],buff[20],vecesc[5];
	strcpy(pallet,m_Nombre);
	strcat(pallet," Tablero ");
	
	itoa(m_L,buff,10);
	strcat(pallet,buff);
	strcat(pallet,"X");
	itoa(m_W,buff,10);
	strcat(pallet,buff);
	strcat(pallet," Piezas ");
	itoa(m_Numpiezas,buff,10);
	strcat(pallet,buff);
//	strcat(pallet," ");
//	itoa(m_l,buff,10);
//	strcat(pallet,buff);
//	strcat(pallet," ");
//	itoa(m_w,buff,10);
//	strcat(pallet,buff);
//	strcat(pallet," ");
	itoa(perdida,buff,10);
	itoa(veces,vecesc,10);
	ss4.Format("%s",pallet);
	ss6.Format("%s","    ");

	ss.Format("%d",contador);
	ss1.Format("%d",sol);
	ss2.Format("%d",m_iter_actual);
	ss3.Format("%d",m_solbest);
	m_clientedc->TextOut((m_factor*m_L/5),(-m_factor*(m_W))*(1.1),ss4);
//	m_clientedc->TextOut( m_factor*m_L, -m_factor*m_W,ss );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.75), ss6 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.75), ss1 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.5), ss2 );
	m_clientedc->TextOut( m_factor*m_L, (-m_factor*(m_W))*(0.25), ss3 );
//	m_clientedc->TextOut( m_factor*m_L, 0, ss5 );
	
	int L,w;
	std::list<BLOQUE> ::iterator itB;
	std::list<RECTAN> ::iterator itL;
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
	int kk=0;
	for (itB=lista_bloques.begin();itB!=lista_bloques.end();itB++)
	{
		kk+=3;
//		BLOQUE b1=(*itB);
		L=m_Piezas[(*itB).GetNumero()].largo;
		w=m_Piezas[(*itB).GetNumero()].ancho;
		if ((*itB).TopLeft()==B.TopLeft() && (*itB).BottomRight()==B.BottomRight())
			m_clientedc->SelectObject(brushrojo);
		else
			m_clientedc->SelectObject(brushblanco);
		
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
	int y1=0;
	m_clientedc->SelectObject(brushblanco);
/*
	if (m_L<=m_W)
	{
		m_clientedc->Rectangle(m_factor*-(0.75*m_L),-m_factor*0,m_factor*(0),-m_factor*(m_W));
		for (register int i=0;i<m_Numpiezas;i++)
		{
			int x1=-(0.5*m_L);
			if (m_Piezas[i].num<m_Piezas[i].max)
			{
					m_clientedc->Rectangle(m_factor*x1,-m_factor*y1,m_factor*(x1+(m_Piezas[i].largo)),-m_factor*(y1+(m_Piezas[i].ancho)));
					y1=y1+m_Piezas[i].ancho+2;
			}
		}
	}
	else
	{
		m_clientedc->Rectangle(m_factor*(0),-m_factor*(0),m_factor*(m_L),-m_factor*(-m_W));
		int x1=0;
		for (register int i=0;i<m_Numpiezas;i++)
		{
			int y1=-(0.3*m_W);
			if (m_Piezas[i].num<m_Piezas[i].max)
			{
					m_clientedc->Rectangle(m_factor*x1,-m_factor*y1,m_factor*(x1+(m_Piezas[i].largo)),-m_factor*(y1+(m_Piezas[i].ancho)));
					x1=x1+m_Piezas[i].largo+2;
			}
		}
	}

*/
}
void CUTTING::Actualizar_Perdida(std::list<BLOQUE> &listaBlo,std::list<RECTAN> &listaPer)
{
	std::list<BLOQUE> ::iterator itB;
	std::list<RECTAN> ::iterator itL;
	RECTAN RectTemp;
	//Construyo rectangulos de pérdida con los bordes
	for (itB=listaBlo.begin();itB!=listaBlo.end();itB++)
	{
//		BLOQUE bloque=(*itB);
		itL=listaPer.begin();
		do{
//			RECTAN Perdida=(*itL);
			RECTAN B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
			RECTAN b1=(*itL);
//			RECTAN b2=(*itB);
			int corta=Restar_Rectangulo(b1,(*itB),B1,B2,B3,B4);
			//No se cortan
			if (corta!=0)
			{
	//Quito el bloque entero siempre
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
void CUTTING::Actualizar_Perdida(BLOQUE &b1,std::list<RECTAN> &listaPer)
{
	std::list<BLOQUE> ::iterator itB;
	std::list<RECTAN> ::iterator itL;
	RECTAN RectTemp;
	// printf("Entro 7");
	itL=listaPer.begin();
	do{
		printf("%d",listaPer.size());

		RECTAN B1(0,0,0,0),B2(0,0,0,0),B3(0,0,0,0),B4(0,0,0,0);
		RECTAN b2=(*itL);
		int corta=Restar_Rectangulo(b2,b1,B1,B2,B3,B4);
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

		// printf("Salgo 8");

		itL++;
	}while(itL!=listaPer.end());
	// printf("Salgo 7");


}
int CUTTING::Restar_Rectangulo(RECTAN &b1,BLOQUE &b2,RECTAN &B1,RECTAN &B2,RECTAN &B3,RECTAN &B4)
{
	RECTAN RectTemp;
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
//Tipo me dice como quiero juntar 
//H si quiero juntar en horizontal
// V en vertical
// P para meter más piezas

void CUTTING::JuntarPerdida(std::list<RECTAN> &lista, char tipo)
{
	if (lista.size()<=1) return ;
	if (tipo=='P') m_EmpiezaPorAqui=0;
	
	bool juntar=false;
	bool seguir=false;
	std::list<RECTAN> ::iterator itL1,itL2,itL3;
	std::list<RECTAN> nueva_lista;
	RECTAN Nuevo1,Nuevo2,Nuevo3,RectTemp;
	int cuenta=0;
	for (itL1=lista.begin();itL1!=lista.end();itL1++)
	{
		(*itL1).SetNumero(0);
	}
	int num=0;
	do
	{

		cuenta++;
		seguir=false;
		nueva_lista.clear();
		itL1=lista.begin();
		do{
			juntar=false;
			itL3=itL1;
			itL3++;
			if (itL3==lista.end()) break;
			itL2=itL3;
			do
			{
				num++;
				juntar=false;
//				RECTAN Rect1=(*itL1),Rect2=(*itL2);
//				Rect1.SetNumero((*itL1).GetNumero());
//				Rect2.SetNumero((*itL2).GetNumero());
//				if (((*itL2).Width()<m_w) && ((*itL2).Height()<m_w)) continue;
				//Si no se tocan ni en horizontal ni en vertical  teniendo parte en común continue
				if (!((*itL1).right==(*itL2).left) && !((*itL1).left==(*itL2).right)
						&& !((*itL1).top==(*itL2).bottom) && !((*itL1).bottom==(*itL2).top)) 
				{
					itL2++;
					continue;
				}
				if (((*itL1).top>(*itL2).bottom) || ((*itL2).top>(*itL1).bottom))
				{
					itL2++;
					continue;
				}
				if (((*itL1).left>(*itL2).right) || ((*itL2).left>(*itL1).right))
				{
					itL2++;
					continue;
				}
				if ((*itL1).GetNumero()==(*itL2).GetNumero() && (*itL1).GetNumero()!=0)
				{
					itL2++;
					continue;
				}
				if (((*itL1).BottomRight()==(*itL2).BottomRight()) &&
				((*itL1).TopLeft()==(*itL2).TopLeft()) )
				{
					itL2++;
					continue;
				}
				//Si coinciden en horizontal
				//voy a saber que una debajo de otra;
				(*itL1).SetNumero(num);
				(*itL2).SetNumero(num);
//				espi++;
				UnionRect(&RectTemp,&(*itL1),&(*itL2));	
				if (((RectTemp.Width()*RectTemp.Height())==(((*itL1).Width()*(*itL1).Height())+((*itL2).Width()*(*itL2).Height())) ))
				{
					RectTemp.SetNumero(num);
					nueva_lista.push_back(RectTemp);
					itL2=lista.erase(itL2);
					seguir=true;
					juntar=true;
					continue;
				}
				else
				{
	//				(*itL1).SetNumero(num);
	//				(*itL2).SetNumero(num);

					juntar=JuntarDosRectangulos(Nuevo1,Nuevo2,Nuevo3,(*itL1),(*itL2),tipo);
					if (juntar==true)
					{	
/*						int a=(*itL1).GetNumero();
						int b=(*itL2).GetNumero();
						if ((*itL1).GetNumero()==(*itL2).GetNumero() && (*itL1).GetNumero()!=0 && (*itL1).GetNumero()!=num)
						{
							printf("Mierda");
						}
*/						if (!Nuevo1.IsRectEmpty()) 
						{
							Nuevo1.SetNumero(num);
							nueva_lista.push_back(Nuevo1);
						}
						if (!Nuevo2.IsRectEmpty()) 
						{
							Nuevo2.SetNumero(num);
							nueva_lista.push_back(Nuevo2);
						}
						if (!Nuevo3.IsRectEmpty()) 
						{
							Nuevo3.SetNumero(num);
							nueva_lista.push_back(Nuevo3);
						}
						itL2=lista.erase(itL2);
						seguir=true;
						continue;
					}
				}
				itL2++;
			}while((juntar!=true) && (itL2!=lista.end()) );
			if (juntar==true) 
			{
				itL1=lista.erase(itL1);
				continue;
			}
			itL1++;
		}while(itL1!=lista.end());
	lista.insert(lista.begin(),nueva_lista.begin(),nueva_lista.end());
	DibujarSolucion(m_lista_bloques,lista,m_ValSolucion,0);

	} while (seguir==true );
}
/*
void CUTTING::JuntarRectangulo(RECTAN &rect)
{
	bool JUNtar=false;
	std::list<RECTAN> ::iterator itL1,itL2,itL3;
	for (itL1=m_lista_perdidas.begin();itL1!=m_lista_perdidas.end();itL1++)
	{
			RECTAN rect4=(*itL1);

		if ((*itL1).left==rect.left && (*itL1).right==rect.right)
		{
			if ((*itL1).top==rect.bottom)
			{
				rect.bottom=(*itL1).bottom;
				RECTAN rect2=(*itL1);
				itL1=m_lista_perdidas.erase(itL1);
				RECTAN rect7=(*itL1);

				if (itL1!=m_lista_perdidas.begin()) 
					itL1--;

				RECTAN rect5=(*itL1);

				
			}
			else
			{
			if ((*itL1).bottom==rect.top)
			{
				rect.top=(*itL1).top;
				RECTAN rect2=(*itL1);

				itL1=m_lista_perdidas.erase(itL1);
				if (itL1!=m_lista_perdidas.begin()) itL1--;
				RECTAN rect5=(*itL1);

				


			}
			}
		}
	}
	m_lista_perdidas.push_back(rect);



}*/
void CUTTING::JuntarRectangulo(RECTAN &rect)
{
	std::list<RECTAN> ::iterator itL1,itL2,itL3;
	itL1=m_lista_perdidas.begin();
	do
	{
		

		RECTAN rect4=(*itL1);

		if ((*itL1).left==rect.left && (*itL1).right==rect.right)
		{
			if ((*itL1).top==rect.bottom)
			{
				rect.bottom=(*itL1).bottom;
				RECTAN rect2=(*itL1);
				itL1=m_lista_perdidas.erase(itL1);
				RECTAN rect5=(*itL1);

				
			}
			else
			{
				if ((*itL1).bottom==rect.top)
				{
					rect.top=(*itL1).top;
					RECTAN rect2=(*itL1);
					itL1=m_lista_perdidas.erase(itL1);
					RECTAN rect5=(*itL1);
				}
				else
				{
					itL1++;
				}
					
			}
		}
		else
		{
			itL1++;
		}


	}while(itL1!=m_lista_perdidas.end());
	m_lista_perdidas.push_back(rect);



}


void CUTTING::JuntarPerdidaStrip(std::list<RECTAN> &lista, char tipo)
{
	if (lista.size()<=1) return ;
	bool juntar=false;
	bool seguir=false;
	std::list<RECTAN> ::iterator itL1,itL2,itL3;
	std::list<RECTAN> nueva_lista;
	RECTAN Nuevo1,Nuevo2,Nuevo3,RectTemp;
	int cuenta=0;
	int num=0;
	do
	{

		cuenta++;
		seguir=false;
		nueva_lista.clear();
		itL1=lista.begin();
		do{
			juntar=false;
			itL3=itL1;
			itL3++;
			if (itL3==lista.end()) break;
			itL2=itL3;
			do
			{
				num++;
				juntar=false;
//				RECTAN Rect1=(*itL1),Rect2=(*itL2);
//				Rect1.SetNumero((*itL1).GetNumero());
//				Rect2.SetNumero((*itL2).GetNumero());
//				if (((*itL2).Width()<m_w) && ((*itL2).Height()<m_w)) continue;
				//Si no se tocan ni en horizontal ni en vertical  teniendo parte en común continue
				if ((*itL1).right!=m_L || (*itL2).right!=m_L || (*itL1).left!=(*itL2).left)
				{
					itL2++;
					continue;
				}

				
				UnionRect(&RectTemp,&(*itL1),&(*itL2));	
				if (((RectTemp.Width()*RectTemp.Height())==(((*itL1).Width()*(*itL1).Height())+((*itL2).Width()*(*itL2).Height())) ))
				{
					RectTemp.SetNumero(num);
					nueva_lista.push_back(RectTemp);
					itL2=lista.erase(itL2);
					seguir=true;
					juntar=true;
					continue;
				}

				itL2++;
			}while((juntar!=true) && (itL2!=lista.end()) );
			if (juntar==true) 
			{
				itL1=lista.erase(itL1);
				continue;
			}
			itL1++;
		}while(itL1!=lista.end());
	lista.insert(lista.begin(),nueva_lista.begin(),nueva_lista.end());

	} while (seguir==true  );
}
//Solo junta las pérdidas que esten al lado de bloque
//Devuelve la importancia de la pérdida mayor que puede colocar
int  CUTTING::JuntarPerdida(std::list<RECTAN> &lista,BLOQUE &B, char tipo)
{
	if (lista.size()<=1) return 0;
	bool juntar=false;
	bool seguir=false;
	int max=0;
	std::list<RECTAN> ::iterator itL1,itL2,itL3;
	std::list<RECTAN> nueva_lista;
	RECTAN Nuevo1,Nuevo2,Nuevo3,RectTemp;
	int cuenta=0;
	for (itL1=lista.begin();itL1!=lista.end();itL1++)
	{
		(*itL1).SetNumero(0);
	}
	short int num=0;
	do
	{

		cuenta++;
		seguir=false;
		nueva_lista.clear();
		itL1=lista.begin();
		do{
			if (BloqueCercaPerdida(B,(*itL1))==false)
			{
				itL1++;
				continue;
			}
			juntar=false;
			itL3=itL1;
			itL3++;
			if (itL3==lista.end()) break;
			itL2=itL3;
			do
			{
				num++;
				if (BloqueCercaPerdida(B,(*itL2))==false)
				{
					itL2++;
					continue;
				}

				juntar=false;
				if ((*itL1).GetNumero()==(*itL2).GetNumero() && (*itL1).GetNumero()!=0)
				{
					itL2++;
					continue;
				}
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
				if (((*itL1).top>(*itL2).bottom) || ((*itL2).top>(*itL1).bottom))
				{
					itL2++;
					continue;
				}
				if (((*itL1).left>(*itL2).right) || ((*itL2).left>(*itL1).right))
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
					max=MAX_IMPORTANCIA;
					continue;
				}
				else
				{
	//				(*itL1).SetNumero(num);
	//				(*itL2).SetNumero(num);

					int num_junta=JuntarDosRectangulosImportancia(Nuevo1,Nuevo2,Nuevo3,(*itL1),(*itL2),tipo);
					if (num_junta!=0)
					{	
						if (max<num_junta) max=num_junta;
						juntar=true;
						if (!Nuevo1.IsRectEmpty()) 
						{
							Nuevo1.SetNumero(num);
							nueva_lista.push_back(Nuevo1);
						}
						if (!Nuevo2.IsRectEmpty()) 
						{
							Nuevo2.SetNumero(num);
							nueva_lista.push_back(Nuevo2);
						}
						if (!Nuevo3.IsRectEmpty()) 
						{
							Nuevo3.SetNumero(num);
							nueva_lista.push_back(Nuevo3);
						}
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
//	DibujarSolucion(m_lista_bloques,nueva_lista,m_ValSolucion,0);

	} while (seguir==true );
	return max;
}
bool CUTTING::JuntarDosRectangulos(RECTAN &Nuevo1,RECTAN &Nuevo2,RECTAN &Nuevo3,RECTAN &rect1,RECTAN &rect2,char tipo)
{
//Cambio por 1	
	int deben_juntarse=0;
//	int deben_juntarse=1;
	bool juntar=false;
	RECTAN Pdown,Pup,Pleft,Pright;
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
	if (tipo=='H')
	{
			if (((Nuevo1.Width())<(rect1.Width())) || ((Nuevo1.Width())<(rect2.Width())))
				return false;
			else
				return true;

	}
	if (tipo=='V')
	{
		if (((Nuevo1.Height())<(rect1.Height())) || ((Nuevo1.Height())<(rect2.Height())))
			return false;
		else
			return true;
	}
	if (tipo=='X')
	{
		if (((Nuevo1.Width()*Nuevo1.Height())>(rect1.Width()*rect1.Height())) && ((Nuevo1.Width()*Nuevo1.Height())>(rect2.Width()*rect2.Height())))
			return true;
		else
			return false;
	}
	if (tipo=='S')
	{
		//Ya lo hace la función de juntar pérdida
//		if (rect1.top==rect2.top && rect1.bottom==rect2.bottom) return true;
//		if (rect1.left==rect2.left && rect1.right==rect2.right) return true;
		int CaRect1=0,CaRect2=0;
		if (rect1.left<rect2.left)
		{
//&& rect1.Width()>m_MinLargo
			CaRect1=CabeAlgunaAncho(rect1) ;
			if (CaRect1==0 )
			{
				if ((Nuevo1.Height()>=(rect1.Height()+rect2.Height()))  )
					return true;
				else 
					return false;
			}
			else
			{
				if (Nuevo1.left<=rect1.left && Nuevo1.left<=rect2.left && ((Nuevo1.Height()>=(rect1.Height()+rect2.Height()))  || (rect1.Height()==rect2.Height())) ) return true;
					else return false;
			}
//			if (CaRect1==0 && CabeAlguna(rect2,0)>0) return true;
		}
		if (rect1.left>rect2.left)
		{
			CaRect2=CabeAlgunaAncho(rect2);
			if (CaRect2==0)
			{
				if ((Nuevo1.Height()>=(rect1.Height()+rect2.Height()))  ) 
					return true;
				else
					return false;
			}
//			if (CaRect2==0 && CabeAlguna(rect1,0)>0) return true;
			else
			{
				if (Nuevo1.left<=rect1.left && Nuevo1.left<=rect2.left && CabeAlgunaAncho(Nuevo1)>0) return true;
					else return false;
			}
		}
		if (rect1.left==rect2.left)
		{
		//Si el nuevo esta a la izquierda entonces si

//		if (Nuevo1.left<=rect1.left && Nuevo1.left<=rect2.left && (Nuevo1.Width()>(rect1.Width()+rect2.Width()))) return true;
		if (Nuevo1.left<=rect1.left && Nuevo1.left<=rect2.left ) return true;
		else return false;
		}
	}
/*
	int respuesta=RespuestaAJuntar(Nuevo1,rect1,rect2);
	if (respuesta==0) return false;
	if (respuesta==1) return true;
*/

	int CabeGrande=CabeAlguna(Nuevo1,0);
	int CabeRect1=CabeAlguna(rect1,CabeGrande);
	//Si en el nuevo no cabe ninguna pieza y en los otros si que se junte
	if (CabeRect1>CabeGrande)
		return false;
	int CabeRect2=CabeAlguna(rect2,CabeGrande);
	if ( CabeRect2>CabeGrande) 
		return false;
	if (CabeGrande>CabeRect1 && CabeGrande>CabeRect2) return true;

/*	int respuesta=RespuestaAJuntar(Nuevo1,rect1,rect2);

	int CabeGrande=CabeAlguna(Nuevo1,0);
	int CabeRect1=CabeAlguna(rect1,CabeGrande);
	//Si en el nuevo no cabe ninguna pieza y en los otros si que se junte
	if (CabeRect1>CabeGrande && respuesta!=0) 
		int algo_mal=1;
	int CabeRect2=CabeAlguna(rect2,CabeGrande);
	if ( CabeRect2>CabeGrande && respuesta!=0)
		int algo_mal=2;
	if (CabeGrande>CabeRect1 && CabeGrande>CabeRect2 && respuesta!=1) 
		int algo_mal=3;
	CabeGrande=CabeAlguna(Nuevo1,0);
	CabeRect1=CabeAlguna(rect1,CabeGrande);
	//Si en el nuevo no cabe ninguna pieza y en los otros si que se junte
	if (CabeRect1>CabeGrande) return false;
	CabeRect2=CabeAlguna(rect2,CabeGrande);
	if ( CabeRect2>CabeGrande) return false;
	if (CabeGrande>CabeRect1 && CabeGrande>CabeRect2) return true;
	if (respuesta!=2)
		int algo_mal=4;
*/	
	
	
	//Este es el caso trivial pero se puede complicar mucho más
	if (((Nuevo1.Width()*Nuevo1.Height())>(rect1.Width()*rect1.Height())) && ((Nuevo1.Width()*Nuevo1.Height())>(rect2.Width()*rect2.Height())))
	{
		return true;
	}
	return false;
}
int CUTTING::JuntarDosRectangulosImportancia(RECTAN &Nuevo1,RECTAN &Nuevo2,RECTAN &Nuevo3,RECTAN &rect1,RECTAN &rect2,char tipo)
{
//Cambio por 1	
	int deben_juntarse=0;
//	int deben_juntarse=1;
	bool juntar=false;
	RECTAN Pdown,Pup,Pleft,Pright;
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
	if (tipo=='H')
	{
			if (((Nuevo1.Width())<(rect1.Width())) || ((Nuevo1.Width())<(rect2.Width())))
				return 0;
			else
				return 1;

	}
	if (tipo=='V')
	{
		if (((Nuevo1.Height())<(rect1.Height())) || ((Nuevo1.Height())<(rect2.Height())))
			return 0;
		else
			return 1;
	}
	if (tipo=='X')
	{
		if (((Nuevo1.Width()*Nuevo1.Height())>(rect1.Width()*rect1.Height())) && ((Nuevo1.Width()*Nuevo1.Height())>(rect2.Width()*rect2.Height())))
			return 1;
		else
			return 0;
	}
	if (tipo=='S')
	{
		//Si el nuevo esta a la izquierda entonces si
		if (Nuevo1.left<=rect1.left && Nuevo1.left<=rect2.left) return true;
	}



/*
	int respuesta=RespuestaAJuntar(Nuevo1,rect1,rect2);
	if (respuesta==0) return false;
	if (respuesta==1) return true;
*/

	int CabeGrande=CabeAlguna(Nuevo1,0);
	int CabeRect1=CabeAlguna(rect1,CabeGrande);
	//Si en el nuevo no cabe ninguna pieza y en los otros si que se junte
	if (CabeRect1>CabeGrande) return 0;
	int CabeRect2=CabeAlguna(rect2,CabeGrande);
	if ( CabeRect2>CabeGrande) return 0;
	if (CabeGrande>CabeRect1 && CabeGrande>CabeRect2) 
	{
		return CabeGrande;
	}

/*	int respuesta=RespuestaAJuntar(Nuevo1,rect1,rect2);

	int CabeGrande=CabeAlguna(Nuevo1,0);
	int CabeRect1=CabeAlguna(rect1,CabeGrande);
	//Si en el nuevo no cabe ninguna pieza y en los otros si que se junte
	if (CabeRect1>CabeGrande && respuesta!=0) 
		int algo_mal=1;
	int CabeRect2=CabeAlguna(rect2,CabeGrande);
	if ( CabeRect2>CabeGrande && respuesta!=0)
		int algo_mal=2;
	if (CabeGrande>CabeRect1 && CabeGrande>CabeRect2 && respuesta!=1) 
		int algo_mal=3;
	CabeGrande=CabeAlguna(Nuevo1,0);
	CabeRect1=CabeAlguna(rect1,CabeGrande);
	//Si en el nuevo no cabe ninguna pieza y en los otros si que se junte
	if (CabeRect1>CabeGrande) return false;
	CabeRect2=CabeAlguna(rect2,CabeGrande);
	if ( CabeRect2>CabeGrande) return false;
	if (CabeGrande>CabeRect1 && CabeGrande>CabeRect2) return true;
	if (respuesta!=2)
		int algo_mal=4;
*/	
	
	
	//Este es el caso trivial pero se puede complicar mucho más
	if (((Nuevo1.Width()*Nuevo1.Height())>(rect1.Width()*rect1.Height())) && ((Nuevo1.Width()*Nuevo1.Height())>(rect2.Width()*rect2.Height())))
	{
		return CabeGrande;
	}
	return 0;
}
//Me dice si en este rectángulo cabe alguna pieza
//Si tengo un problema restringido si el problema no es posible 
//Tengo que pensar solo en las que quiero meter
int CUTTING::RespuestaAJuntar(RECTAN &RectGrande,RECTAN &Rect1,RECTAN &Rect2)
{
//	return true;
	bool prime=true;
	bool CabeGrande=false,CabeRect1=false,CabeRect2=false;
	if (((m_MinLargo>RectGrande.Width() || m_MinAncho>RectGrande.Height()) ) 
		&& ((m_MinLargo>Rect1.Width() || m_MinAncho>Rect1.Height()) ) 
		&& ((m_MinLargo>Rect2.Width() || m_MinAncho>Rect2.Height()) ) )
		return 2;
	for (register int i=m_EmpiezaPorAqui;i<m_Numpiezas;i++)
	{

		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && (m_Piezas[i].max>m_Piezas[i].num) && ((m_Piezas[i].min>m_Piezas[i].num))))
		{
			if (prime==true) 
			{
				m_EmpiezaPorAqui=i;
				prime=false;
			}
			if (m_Piezas[i].largo<=RectGrande.Width() && m_Piezas[i].ancho<=RectGrande.Height())
				CabeGrande=true;
			if (m_Piezas[i].largo<=Rect1.Width() && m_Piezas[i].ancho<=Rect1.Height())
				CabeRect1=true;
			if (m_Piezas[i].largo<=Rect2.Width() && m_Piezas[i].ancho<=Rect2.Height())
				CabeRect2=true;
			if (CabeRect1==true && CabeGrande==false) return 0;
			if (CabeRect2==true && CabeGrande==false) return 0;
			if (CabeGrande==true && CabeRect1==false && CabeRect2==false) return 1;
			if (CabeGrande==true) return 2;
		}
	}
	return 2;
}
//Me dice si en este rectángulo cabe alguna pieza
//Si tengo un problema restringido si el problema no es posible 
//Tengo que pensar solo en las que quiero meter
int CUTTING::CabeAlguna(RECTAN &Rect,int importancia_anterior)
{
//	return true;
//	espi++;	
//	m_EmpiezaPorAqui=0;
	int importancia=MAX_IMPORTANCIA;
	bool prime=true;
//	int largo=10000,ancho=10000;
	if ((m_MinLargo>Rect.Width() || m_MinAncho>Rect.Height()) ) return 0;
	for (register int i=m_EmpiezaPorAqui;i<m_Numpiezas;i++)
	{
		if (i==m_noquiero) continue;
//		int km=m_Piezas[i].max;
//		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
		{
			if (prime==true) 
			{
				m_EmpiezaPorAqui=i;
				prime=false;
			}
			importancia--;
			if (importancia<importancia_anterior) return 0;
			if (m_Piezas[i].largo<=Rect.Width() && m_Piezas[i].ancho<=Rect.Height())
				return importancia;
			
		}
	}
	return 0;
}
//Me dice si en este rectángulo cabe alguna pieza
//Si tengo un problema restringido si el problema no es posible 
//Tengo que pensar solo en las que quiero meter
int CUTTING::CabeAlgunaAncho(RECTAN &Rect)
{
//	return true;
//	espi++;	
//	m_EmpiezaPorAqui=0;
	int importancia=MAX_IMPORTANCIA;
//	int largo=10000,ancho=10000;
	if (( m_MinAncho>Rect.Height()) ) return 0;
	for (register int i=m_Piezas.size();i>=0;i--)
	{
//		int km=m_Piezas[i].max;
//		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
		{
			importancia--;
			if ( m_Piezas[i].ancho<=Rect.Height())
				return importancia;
			
		}
	}
	return 0;
}
//Actualiza todos los máximos después de meter cada pieza y devuelve para el que se da el max
int CUTTING::ActualizarMinMax(void)
{
//	return true;
//	espi++;	
//	m_EmpiezaPorAqui=0;
//	int largo=10000,ancho=10000;
	m_MaxLargo=0;
	m_MaxAncho=0;
	m_MinLargo=99999;
	m_MinAncho=99999;
	m_AreaTotalRestante=0;
	int pieza_max=MAX_IMPORTANCIA;
	if (m_PuedenRotarsePiezas==false)
	{
		for (register int i=0;i<m_Numpiezas;i++)
		{
			if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
			{

				//si todavia es valida esa pieza
				if (m_Piezas[i].largo<m_MinLargo) m_MinLargo=m_Piezas[i].largo;		
				if (m_Piezas[i].ancho<m_MinAncho) m_MinAncho=m_Piezas[i].ancho;		
				if (m_Piezas[i].largo>m_MaxLargo)
				{
					m_MaxLargo=m_Piezas[i].largo;
					pieza_max=i;
				}
				if (m_Piezas[i].ancho>m_MaxAncho) m_MaxAncho=m_Piezas[i].ancho;		
				m_AreaTotalRestante+=m_Piezas[i].largo*m_Piezas[i].ancho*(m_Piezas[i].max-m_Piezas[i].num);
			
			}
		}
	}
	else
	{
		m_TotalAncho=0;
		for (register int i=0;i<m_Numpiezas;i++)
		{
			if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
			{
				int minLarAncho=__min(m_Piezas[i].largo,m_Piezas[i].ancho);
				int maxLarAncho=__max(m_Piezas[i].largo,m_Piezas[i].ancho);

				//si todavia es valida esa pieza
				if (minLarAncho<m_MinLargo) m_MinLargo=minLarAncho;	
				if (m_Piezas[i].largo>m_MaxLargo) m_MaxLargo=m_Piezas[i].largo;
				if (m_Piezas[i].ancho>m_MaxAncho) m_MaxAncho=m_Piezas[i].ancho;
				if (maxLarAncho<=m_W)
				m_TotalAncho+=minLarAncho*(m_Piezas[i].max-m_Piezas[i].num);
				else
					m_TotalAncho+=maxLarAncho;
				if (minLarAncho>m_MaxAncho)
				{
					m_MaxAncho=minLarAncho;
					
				}
				if (maxLarAncho>=m_MaxLargo)
				{
					pieza_max=i;
				}
				m_AreaTotalRestante+=m_Piezas[i].largo*m_Piezas[i].ancho*(m_Piezas[i].max-m_Piezas[i].num);
			
			}
		}
		if (m_MaxLargo<=m_W)
		m_MaxLargo=__min(m_MaxLargo,m_MaxAncho);
		
		m_MinAncho=m_MinLargo;
//		m_MaxAncho=m_MaxLargo;

	}

	return pieza_max;
}
int CUTTING::PiezaMayorEsteRectangulo(RECTAN &R)
{
//	return true;
//	espi++;	
//	m_EmpiezaPorAqui=0;
//	int largo=10000,ancho=10000;
	int maxLargo=0,maxAncho=0;
	int pieza_max=MAX_IMPORTANCIA;
	if (m_PuedenRotarsePiezas==false)
	{
//		int km=m_Piezas[i].max;
//		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
		for (register int i=0;i<m_Numpiezas;i++)
		{
			if (((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num)))) && (m_Piezas[i].ancho<=R.Height()))
			{
				//si todavia es valida esa pieza
				if (m_Piezas[i].largo>=maxLargo)
				{
					if (m_Piezas[i].largo>maxLargo)
					{
						maxLargo=m_Piezas[i].largo;
						maxAncho=m_Piezas[i].ancho;
						pieza_max=i;
					}
					else
					{
						if (m_Piezas[i].ancho>maxAncho)
						{
							maxAncho=m_Piezas[i].ancho;
							pieza_max=i;
						}

					}
				}
			
			}
		}
	}
	else
	{
		//En este caso pueden rotarse piezas
		//por lo que busco el minímo de los dos máximos
		for (register int i=0;i<m_Numpiezas;i++)
		{
			if (((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num)))) && ((m_Piezas[i].ancho<=R.Height())||(m_Piezas[i].largo<=R.Height())))
			{
				
				int maxLarAn=__max(m_Piezas[i].largo,m_Piezas[i].ancho);
				int minLarAn=0;
				minLarAn=__min(m_Piezas[i].largo,m_Piezas[i].ancho);
				if (maxLarAn>m_W)
				{
					minLarAn=maxLarAn;
				}
					//si todavia es valida esa pieza
				if (minLarAn>=maxLargo)
				{
					if (minLarAn>maxLargo)
					{
						maxLargo=minLarAn;
						maxAncho=maxLarAn;
						pieza_max=i;
					}
					else
					{
						if (maxLarAn>maxAncho)
						{
							maxLargo=minLarAn;
							maxAncho=maxLarAn;
							pieza_max=i;
						}
					}
				}
//				else
//				{
//				}
			
			}
		}
	
	}


	return pieza_max;
}
int CUTTING::PiezaMayorEsteRectangulo(RECTAN &R,int este)
{
//	return true;
//	espi++;	
//	m_EmpiezaPorAqui=0;
//	int largo=10000,ancho=10000;
	int maxLargo=0,maxAncho=0;
	int pieza_max=MAX_IMPORTANCIA;
	if (m_PuedenRotarsePiezas==false)
	{
//		int km=m_Piezas[i].max;
//		if ((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))))
		for (register int i=0;i<m_Numpiezas;i++)
		{
			if (((m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num))) || (i==este)) && (m_Piezas[i].ancho<=R.Height()))
			{
				//si todavia es valida esa pieza
				if (m_Piezas[i].largo>=maxLargo)
				{
					if (m_Piezas[i].largo>maxLargo)
					{
						maxLargo=m_Piezas[i].largo;
						maxAncho=m_Piezas[i].ancho;
						pieza_max=i;
					}
					else
					{
						if (m_Piezas[i].ancho>maxAncho)
						{
							maxAncho=m_Piezas[i].ancho;
							pieza_max=i;
						}

					}
				}
			
			}
		}
	}
	else
	{
		//En este caso pueden rotarse piezas
		//por lo que busco el minímo de los dos máximos
		for (register int i=0;i<m_Numpiezas;i++)
		{
			if (((i==este)||(m_Piezas[i].max>m_Piezas[i].num && m_Posible==true) || (m_Posible==false && ((m_Piezas[i].min>m_Piezas[i].num)))) && ((m_Piezas[i].ancho<=R.Height())||(m_Piezas[i].largo<=R.Height())))
			{
				
				int maxLarAn=__max(m_Piezas[i].largo,m_Piezas[i].ancho);
				int minLarAn=0;
				minLarAn=__min(m_Piezas[i].largo,m_Piezas[i].ancho);
				if (maxLarAn>m_W)
				{
					minLarAn=maxLarAn;
				}
					//si todavia es valida esa pieza
				if (minLarAn>=maxLargo)
				{
					if (minLarAn>maxLargo)
					{
						maxLargo=minLarAn;
						maxAncho=maxLarAn;
						pieza_max=i;
					}
					else
					{
						if (maxLarAn>maxAncho)
						{
							maxLargo=minLarAn;
							maxAncho=maxLarAn;
							pieza_max=i;
						}
					}
				}
//				else
//				{
//				}
			
			}
		}
	
	}


	return pieza_max;
}
void CUTTING::Bloques_Hacia_Las_Esquinas(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP)
{
//		return;

	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro

	//Voy a tener unas variables que me dicen si pruebo o no a cambiar las pérdidas
	std::list<RECTAN> ::iterator itC;
	CRect Union(0,0,0,0);
	for (itC=listaP.begin();itC!=listaP.end();itC++)
	{
		UnionRect(&Union,&(*itC),&Union);
	}

	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
	
	bool seguir=false;
	
	do {
		seguir=false;
		JuntarPerdida(listaP,'V');

	itL=listaB.begin();
	do{
		if ((*itL).left!=0 && (*itL).right!=m_L )
		{
//			JuntarPerdida(listaP,'V');

			bool movida_izquierda=false;
			bool movida_abajo=false;
		
//			if ((*itL).left!=0 && ((*itL).left<=(m_L/2)) && (*itL).right!=m_L)
			if ((*itL).left!=0 && ((*itL).left<=(m_L-(*itL).right)) && (*itL).right!=m_L && (*itL).left>Union.left)
			{
			
				RECTAN Rect(0,(*itL).top,(*itL).left,(*itL).bottom);
				int m=(*itL).right;
				if (Existe_Perdida(listaP,(*itL),1)==true )
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.left=(*itL).right;
					perdida.right=m;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
					movida_izquierda=true;
					seguir=true;

				}
			}
			//Pegado a la derecha
//			if ((*itL).left!=0 && ((*itL).left>(m_L/2)) && movida_izquierda!=true && (*itL).right!=m_L )
			if ((*itL).left!=0 && ((*itL).left>(m_L-(*itL).right)) && movida_izquierda!=true && (*itL).right!=m_L && (*itL).right<Union.right)
			{
				RECTAN Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				int m=(*itL).left;
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,(*itL),2)==true)
				{
					RECTAN perdida;
					perdida.left=m;
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		}
		itL++;

		}while(itL!=listaB.end());
	}while(seguir==true);
	do {
		seguir=false;
		JuntarPerdida(listaP,'H');

	itL=listaB.begin();
	do{
		if ((*itL).top!=0 && (*itL).bottom!=m_W)
		{

//		JuntarPerdida(listaP,'H');
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Por los dos lados esta mál colocada la  pego al lado más cercano
//		if ((*itL).top!=0 && ((*itL).top<=(m_W/2)) && (*itL).bottom!=m_W )
		if ((*itL).top!=0 && ((*itL).top<=(m_W-(*itL).bottom)) && (*itL).bottom!=m_W && (*itL).top>Union.top)
		{
				RECTAN Rect((*itL).left,0,(*itL).right,(*itL).top);
				int m=(*itL).bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,(*itL),3)==true)
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
//			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W/2)) && (*itL).bottom!=m_W )
			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W-(*itL).bottom)) && (*itL).bottom!=m_W && (*itL).bottom<Union.bottom)
			{
				RECTAN Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				int m=(*itL).top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,(*itL),4)==true)
				{
					RECTAN perdida;
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
	}while(seguir==true);
	return;
}
//Coloca el bloque lo más a la esquina posible dependiendo donde esta el rectángulo
//de pérdida los nuevos rectángulos de pérdida no se ponen siempre en el mismo orden
//para que la lista tenga algo de aleatoriedad.
void CUTTING::ColocarEsquinaMasCercana(std::list<RECTAN> &lista,BLOQUE &B1,RECTAN &Rect,int largo,int ancho)
{
	int k=get_random(0,1);
	double xcenter=Rect.CenterPoint().x;
	double ycenter=Rect.CenterPoint().y;
	//Si quiero hacer aleatorio donde coloco el bloque
//	xcenter=get_random(Rect.left,Rect.right);
//	ycenter=get_random(Rect.top,Rect.bottom);
	RECTAN Nuevo1,Nuevo2;
	//*Lado derecho
	if (xcenter>(m_L/2))
	{
		B1.right=Rect.right;
		B1.left=B1.right-largo;

		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;
				Nuevo2.bottom=Rect.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.right=B1.left;
				Nuevo2.top=B1.top;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}
			//Lado derecho arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;	
			if (!B1.IsRectEmpty())
			{
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;
				Nuevo2.left=Rect.left;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.right=B1.left;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}
			//Lado derecho abajo
		}
	}
	//Lado izquierdo
	else
	{
		B1.left=Rect.left;
		B1.right=B1.left+largo;
		//Arriba o abajo
		if (ycenter>(m_W/2))
		{
			B1.bottom=Rect.bottom;
			B1.top=B1.bottom-ancho;
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.TopLeft()=Rect.TopLeft();
				Nuevo1.right=Rect.right;
				Nuevo1.bottom=B1.top;
				Nuevo2.BottomRight()=Rect.BottomRight();
				Nuevo2.top=B1.top;
				Nuevo2.left=B1.right;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}
			//Esquina izquierda arriba
		}
		else
		{
			B1.top=Rect.top;
			B1.bottom=B1.top+ancho;
			if (!(B1.IsRectEmpty()))
			{
				Nuevo1.BottomRight()=Rect.BottomRight();
				Nuevo1.left=Rect.left;
				Nuevo1.top=B1.bottom;
				Nuevo2.right=Rect.right;
				Nuevo2.top=B1.top;
				Nuevo2.bottom=B1.bottom;
				Nuevo2.left=B1.right;
				if (k==0)
				{
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
				}
				else
				{
					if (!Nuevo2.IsRectEmpty()) lista.push_back(Nuevo2);
					if (!Nuevo1.IsRectEmpty()) lista.push_back(Nuevo1);
				}
			}

			//Esquina izquierda abajo
		}
	}
}
void CUTTING::Bloques_Hacia_Las_EsquinasStrip(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP)
{
//		return;

	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro

	//Voy a tener unas variables que me dicen si pruebo o no a cambiar las pérdidas
	std::list<RECTAN> ::iterator itC;
	CRect Union(0,0,0,0);
	for (itC=listaP.begin();itC!=listaP.end();itC++)
	{
		UnionRect(&Union,&(*itC),&Union);
	}

	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
	
	bool seguir=false;
	

	do {
		seguir=false;
		JuntarPerdida(listaP,'H');

	itL=listaB.begin();
	do{
		if ((*itL).top!=0 && (*itL).bottom!=m_W)
		{

//		JuntarPerdida(listaP,'H');
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Por los dos lados esta mál colocada la  pego al lado más cercano
//		if ((*itL).top!=0 && ((*itL).top<=(m_W/2)) && (*itL).bottom!=m_W )
		if ((*itL).top!=0 && ((*itL).top<=(m_W-(*itL).bottom)) && (*itL).bottom!=m_W && (*itL).top>Union.top)
		{
				RECTAN Rect((*itL).left,0,(*itL).right,(*itL).top);
				int m=(*itL).bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,(*itL),3)==true)
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
//			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W/2)) && (*itL).bottom!=m_W )
			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W-(*itL).bottom)) && (*itL).bottom!=m_W && (*itL).bottom<Union.bottom)
			{
				RECTAN Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				int m=(*itL).top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,(*itL),4)==true)
				{
					RECTAN perdida;
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
	}while(seguir==true);
		do {
		seguir=false;
		JuntarPerdida(listaP,'V');

	itL=listaB.begin();
	do{
		if ((*itL).left!=0 && (*itL).right!=m_L )
		{
//			JuntarPerdida(listaP,'V');

			bool movida_izquierda=false;
			bool movida_abajo=false;
		
//			if ((*itL).left!=0 && ((*itL).left<=(m_L/2)) && (*itL).right!=m_L)
			if ((*itL).left!=0 )
			{
			
				RECTAN Rect(0,(*itL).top,(*itL).left,(*itL).bottom);
				int m=(*itL).right;
				if (Existe_Perdida(listaP,(*itL),1)==true )
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.left=(*itL).right;
					perdida.right=m;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
					movida_izquierda=true;
					seguir=true;

				}
			}
		}
		itL++;

		}while(itL!=listaB.end());
	}while(seguir==true);
	return;
}
void CUTTING::Bloques_Hacia_Las_EsquinasStrip(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP,int min)
{
//		return;

	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro

	//Voy a tener unas variables que me dicen si pruebo o no a cambiar las pérdidas
	std::list<RECTAN> ::iterator itC;
	CRect Union(0,0,0,0);
	for (itC=listaP.begin();itC!=listaP.end();itC++)
	{
		UnionRect(&Union,&(*itC),&Union);
	}

	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
	
	bool seguir=false;
	


		do {
		seguir=false;
		JuntarPerdida(listaP,'V');

	itL=listaB.begin();
	do{
		if ((*itL).left!=0 && (*itL).right!=m_L && (*itL).left>=min)
		{
//			JuntarPerdida(listaP,'V');

			bool movida_izquierda=false;
			bool movida_abajo=false;
		
//			if ((*itL).left!=0 && ((*itL).left<=(m_L/2)) && (*itL).right!=m_L)
			if ((*itL).left!=0 )
			{
			
				RECTAN Rect(0,(*itL).top,(*itL).left,(*itL).bottom);
				int m=(*itL).right;
				if (Existe_Perdida(listaP,(*itL),1)==true )
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.left=(*itL).right;
					perdida.right=m;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
					movida_izquierda=true;
					seguir=true;

				}
			}
		}
		itL++;

		}while(itL!=listaB.end());
	}while(seguir==true);

	return;
}

void CUTTING::Bloques_Hacia_Las_Esquinas_Combinar(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro

	//Voy a tener unas variables que me dicen si pruebo o no a cambiar las pérdidas
	std::list<RECTAN> ::iterator itC;
	CRect Union(0,0,0,0);
	for (itC=listaP.begin();itC!=listaP.end();itC++)
	{
		UnionRect(&Union,&(*itC),&Union);
	}

	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
	
	bool seguir=false;
	
	do {
		seguir=false;
		JuntarPerdida(listaP,'V');

	itL=listaB.begin();
	do{
		if ((*itL).left!=0 && (*itL).right!=m_L && (*itL).PuedoMover()!=false)
		{
//			JuntarPerdida(listaP,'V');

			bool movida_izquierda=false;
			bool movida_abajo=false;
		
//			if ((*itL).left!=0 && ((*itL).left<=(m_L/2)) && (*itL).right!=m_L)
			if ((*itL).left!=0 && ((*itL).left<=(m_L-(*itL).right)) && (*itL).right!=m_L && (*itL).left>Union.left)
			{
			
				RECTAN Rect(0,(*itL).top,(*itL).left,(*itL).bottom);
				int m=(*itL).right;
				if (Existe_Perdida(listaP,(*itL),1)==true )
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.left=(*itL).right;
					perdida.right=m;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
					movida_izquierda=true;
					seguir=true;

				}
			}
			//Pegado a la derecha
//			if ((*itL).left!=0 && ((*itL).left>(m_L/2)) && movida_izquierda!=true && (*itL).right!=m_L )
			if ((*itL).left!=0 && ((*itL).left>(m_L-(*itL).right)) && movida_izquierda!=true && (*itL).right!=m_L && (*itL).right<Union.right)
			{
				RECTAN Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				int m=(*itL).left;
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,(*itL),2)==true)
				{
					RECTAN perdida;
					perdida.left=m;
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		}
		itL++;

		}while(itL!=listaB.end());
	}while(seguir==true);
	do {
		seguir=false;
		JuntarPerdida(listaP,'H');

	itL=listaB.begin();
	do{
		if ((*itL).top!=0 && (*itL).bottom!=m_W && (*itL).PuedoMover()!=false)
		{

//		JuntarPerdida(listaP,'H');
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Por los dos lados esta mál colocada la  pego al lado más cercano
//		if ((*itL).top!=0 && ((*itL).top<=(m_W/2)) && (*itL).bottom!=m_W )
		if ((*itL).top!=0 && ((*itL).top<=(m_W-(*itL).bottom)) && (*itL).bottom!=m_W && (*itL).top>Union.top)
		{
				RECTAN Rect((*itL).left,0,(*itL).right,(*itL).top);
				int m=(*itL).bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,(*itL),3)==true)
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
//			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W/2)) && (*itL).bottom!=m_W )
			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W-(*itL).bottom)) && (*itL).bottom!=m_W && (*itL).bottom<Union.bottom)
			{
				RECTAN Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				int m=(*itL).top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,(*itL),4)==true)
				{
					RECTAN perdida;
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
	}while(seguir==true);
	return;
}

//Antigua
/*
void CUTTING::Bloques_Hacia_Las_Esquinas(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro
	if (listaB.size()==0) return;
	std::list<BLOQUE> :: iterator itL;
	
	bool seguir=false;
	
	do {
		seguir=false;
		JuntarPerdida(listaP,'V');

	itL=listaB.begin();
	do{
		if ((*itL).left!=0 && (*itL).right!=m_L)
		{
//			JuntarPerdida(listaP,'V');

			bool movida_izquierda=false;
			bool movida_abajo=false;
		
//			if ((*itL).left!=0 && ((*itL).left<=(m_L/2)) && (*itL).right!=m_L)
			if ((*itL).left!=0 && ((*itL).left<=(m_L-(*itL).right)) && (*itL).right!=m_L)
			{
			
				RECTAN Rect(0,(*itL).top,(*itL).left,(*itL).bottom);
				int m=(*itL).right;
				if (Existe_Perdida(listaP,(*itL),1)==true )
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.left=(*itL).right;
					perdida.right=m;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
						listaP.push_back(perdida);
					movida_izquierda=true;
					seguir=true;

				}
			}
			//Pegado a la derecha
//			if ((*itL).left!=0 && ((*itL).left>(m_L/2)) && movida_izquierda!=true && (*itL).right!=m_L )
			if ((*itL).left!=0 && ((*itL).left>(m_L-(*itL).right)) && movida_izquierda!=true && (*itL).right!=m_L )
			{
				RECTAN Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				int m=(*itL).left;
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,(*itL),2)==true)
				{
					RECTAN perdida;
					perdida.left=m;
					perdida.right=(*itL).left;
					perdida.top=(*itL).top;
					perdida.bottom=(*itL).bottom;
					listaP.push_back(perdida);
					seguir=true;

				}
			}
		}
		itL++;

		}while(itL!=listaB.end());
	}while(seguir==true);
	do {
		seguir=false;
		JuntarPerdida(listaP,'H');

	itL=listaB.begin();
	do{
		if ((*itL).top!=0 && (*itL).bottom!=m_W)
		{

//		JuntarPerdida(listaP,'H');
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Por los dos lados esta mál colocada la  pego al lado más cercano
//		if ((*itL).top!=0 && ((*itL).top<=(m_W/2)) && (*itL).bottom!=m_W )
		if ((*itL).top!=0 && ((*itL).top<=(m_W-(*itL).bottom)) && (*itL).bottom!=m_W )
		{
				RECTAN Rect((*itL).left,0,(*itL).right,(*itL).top);
				int m=(*itL).bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,(*itL),3)==true)
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.top=(*itL).bottom;
					perdida.bottom=m;
					perdida.left=(*itL).left;
					perdida.right=(*itL).right;
					listaP.push_back(perdida);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
//			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W/2)) && (*itL).bottom!=m_W )
			if ((*itL).top!=0 && movida_abajo!=true && ((*itL).top>(m_W-(*itL).bottom)) && (*itL).bottom!=m_W )
			{
				RECTAN Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				int m=(*itL).top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,(*itL),4)==true)
				{
					RECTAN perdida;
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
	}while(seguir==true);
	return;
}*/
void CUTTING::Bloques_Hacia_Las_Esquinas(BLOQUE &B, std::list<RECTAN> &listaP)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro
	bool seguir=false;
	if (B.left!=0 && B.right!=m_L)
	{
	
	do {
		JuntarPerdida(listaP,'V');
		seguir=false;
		bool movida_izquierda=false;
		bool movida_abajo=false;
		
		if (B.left!=0 && (B.left<=(m_L/2)) && B.right!=m_L)
		{
			
			RECTAN Rect(0,B.top,B.left,B.bottom);
			int m=B.right;
			if (Existe_Perdida(listaP,B,1)==true )
			{
				//Nueva perdida
				RECTAN perdida;
				perdida.left=B.right;
				perdida.right=m;
				perdida.top=B.top;
				perdida.bottom=B.bottom;
				listaP.push_back(perdida);
				movida_izquierda=true;
				seguir=true;

			}
		}
			//Pegado a la derecha
		if (B.left!=0 && (B.left>(m_L/2)) && movida_izquierda!=true && B.right!=m_L )
		{
			RECTAN Rect(((B.right)),B.top,m_L,B.bottom);
			int m=B.left;
			//Poner bloque pegado a la derecha
			if (Existe_Perdida(listaP,B,2)==true)
			{
				RECTAN perdida;
				perdida.left=m;
				perdida.right=B.left;
				perdida.top=B.top;
				perdida.bottom=B.bottom;
				listaP.push_back(perdida);
				seguir=true;

			}
		}
	}while(seguir==true);
	}
	if (B.top!=0 && B.bottom!=m_W)
	{
	do {
		JuntarPerdida(listaP,'H');

		seguir=false;
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if (B.top!=0 && (B.top<=(m_W/2)) && B.bottom!=m_W )
		{
				RECTAN Rect(B.left,0,B.right,B.top);
				int m=B.bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,B,3)==true)
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.top=B.bottom;
					perdida.bottom=m;
					perdida.left=B.left;
					perdida.right=B.right;
					listaP.push_back(perdida);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
			if (B.top!=0 && movida_abajo!=true && (B.top>(m_W/2)) && B.bottom!=m_W )
			{
				RECTAN Rect(((B.left)),B.bottom,B.right,m_W);
				int m=B.top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,B,4)==true)
				{
					RECTAN perdida;
					perdida.bottom=B.top;
					perdida.top=m;
					perdida.left=B.left;
					perdida.right=B.right;
					listaP.push_back(perdida);

					seguir=true;

				}
			}
//		}
	}while(seguir==true);
	}
	return;
}

void CUTTING::Bloques_Hacia_Las_EsquinasStrip(BLOQUE &B, std::list<RECTAN> &listaP)
{
	//Ahora pego los bloques a las esquinas
	//Lo que hago es si algún bloque se ha quedado en medio moverlo hacia
	//las esquinas vamos desplzar las piezas hacia las esquinas y las 
	//pérdidas hacia el centro
	bool seguir=false;
	if (B.left!=0 && B.right!=m_L)
	{
	
	do {
		JuntarPerdida(listaP,'V');
		seguir=false;
		bool movida_izquierda=false;
		bool movida_abajo=false;
		
		if (B.left!=0 )
		{
			
			RECTAN Rect(0,B.top,B.left,B.bottom);
			int m=B.right;
			if (Existe_Perdida(listaP,B,1)==true )
			{
				//Nueva perdida
				RECTAN perdida;
				perdida.left=B.right;
				perdida.right=m;
				perdida.top=B.top;
				perdida.bottom=B.bottom;
				listaP.push_back(perdida);
				movida_izquierda=true;
				seguir=true;

			}
		}
	}while(seguir==true);
	}
	if (B.top!=0 && B.bottom!=m_W)
	{
	do {
		JuntarPerdida(listaP,'H');

		seguir=false;
		bool movida_izquierda=false;
		bool movida_abajo=false;

		//Por los dos lados esta mál colocada la  pego al lado más cercano
		if (B.top!=0 && (B.top<=(m_W/2)) && B.bottom!=m_W )
		{
				RECTAN Rect(B.left,0,B.right,B.top);
				int m=B.bottom;
				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,B,3)==true)
				{
					//Nueva perdida
					RECTAN perdida;
					perdida.top=B.bottom;
					perdida.bottom=m;
					perdida.left=B.left;
					perdida.right=B.right;
					listaP.push_back(perdida);

					movida_abajo=true;
					seguir=true;

				}
			}
			//Pegado a arriba
			if (B.top!=0 && movida_abajo!=true && (B.top>(m_W/2)) && B.bottom!=m_W )
			{
				RECTAN Rect(((B.left)),B.bottom,B.right,m_W);
				int m=B.top;
				//Poner bloque pegado a arriba
				if (Existe_Perdida(listaP,B,4)==true)
				{
					RECTAN perdida;
					perdida.bottom=B.top;
					perdida.top=m;
					perdida.left=B.left;
					perdida.right=B.right;
					listaP.push_back(perdida);

					seguir=true;

				}
			}
//		}
	}while(seguir==true);
	}
	if (B.left!=0 && B.right!=m_L)
	{
	
	do {
		JuntarPerdida(listaP,'V');
		seguir=false;
		bool movida_izquierda=false;
		bool movida_abajo=false;
		
		if (B.left!=0 )
		{
			
			RECTAN Rect(0,B.top,B.left,B.bottom);
			int m=B.right;
			if (Existe_Perdida(listaP,B,1)==true )
			{
				//Nueva perdida
				RECTAN perdida;
				perdida.left=B.right;
				perdida.right=m;
				perdida.top=B.top;
				perdida.bottom=B.bottom;
				listaP.push_back(perdida);
				movida_izquierda=true;
				seguir=true;

			}
		}
	}while(seguir==true);
	}

	return;
}
bool CUTTING::Existe_Perdida(std::list<RECTAN> &listaP,RECTAN &rect,int tipo)
{
	RECTAN Nuevo1,Nuevo2;
	bool grande=false;
	std::list<RECTAN> ::iterator itL;
	std::list<RECTAN> lista;
	for (itL=listaP.begin();itL!=listaP.end() && grande!=true;itL++)
	{
		RECTAN cuadra=(*itL);
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
			RECTAN Rect=(*itL);
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
bool CUTTING::Existe_Bloque(RECTAN &rect,int tipo)
{
	int pieza=99999;
	bool parar=false;
	std::list<BLOQUE> ::iterator itL;
	for (itL=m_lista_bloques.begin();itL!=m_lista_bloques.end() && parar!=true;itL++)
	{
		int max_alto=(*itL).Height()+rect.Height();
		if (tipo==1 && (*itL).bottom==rect.top && rect.left==(*itL).left && rect.right==(*itL).right)
		{
			//Buscar si existe una pieza igual de ancha pero más larga
			pieza=Buscar_Pieza_No_Metida(rect.Width(),(*itL).Height(),(*itL).Height()+rect.Height());
			parar=true;
			// Cambiar bloque
			if (pieza!=99999)
			{
				//Cambio bloque 
				BLOQUE Recta=(*itL);
//				printf("Meto");
				m_Piezas[(*itL).GetNumero()].num-=(*itL).Height()/m_Piezas[(*itL).GetNumero()].ancho;
				(*itL).SetNumero(pieza);
				if (m_PuedenRotarsePiezas==false || (m_Piezas[pieza].ancho!=(*itL).Width()))
				{
					(*itL).bottom=((max_alto/m_Piezas[pieza].ancho)*m_Piezas[pieza].ancho)+(*itL).top;
					m_Piezas[(*itL).GetNumero()].num+=max_alto/m_Piezas[pieza].ancho;
					rect.top=(*itL).bottom;
				}
				else
				{
					(*itL).bottom=((max_alto/m_Piezas[pieza].largo)*m_Piezas[pieza].largo)+(*itL).top;
					m_Piezas[(*itL).GetNumero()].num+=max_alto/m_Piezas[pieza].largo;
					rect.top=(*itL).bottom;
				}
				return true;
			}

		}
		if (tipo==0 && (*itL).top==rect.bottom && rect.left==(*itL).left && rect.right==(*itL).right)
		{
			//Buscar si existe una pieza igual de ancha pero más larga
			pieza=Buscar_Pieza_No_Metida(rect.Width(),(*itL).Height(),(*itL).Height()+rect.Height());
			parar=true;
			// Cambiar bloque
			if (pieza!=99999)
			{
//				printf("Meto");

				m_Piezas[(*itL).GetNumero()].num-=(*itL).Height()/m_Piezas[(*itL).GetNumero()].ancho;
				(*itL).SetNumero(pieza);
				if (m_PuedenRotarsePiezas==false || (m_Piezas[pieza].ancho!=(*itL).Width()))
				{

				(*itL).top=(*itL).bottom-((max_alto/m_Piezas[pieza].ancho)*(m_Piezas[pieza].ancho));
				m_Piezas[(*itL).GetNumero()].num+=max_alto/m_Piezas[pieza].ancho;
				rect.bottom=(*itL).top;
				}
				else
				{
				(*itL).top=(*itL).bottom-((max_alto/m_Piezas[pieza].largo)*(m_Piezas[pieza].largo));
				m_Piezas[(*itL).GetNumero()].num+=max_alto/m_Piezas[pieza].largo;
				rect.bottom=(*itL).top;

				}
				return true;

			}

		}

	}
	return false;
}
int CUTTING::Buscar_Pieza_No_Metida(int largo,int alto,int max_alto)
{
	int pieza=99999,max=0;
	for (register int i=0;i<m_Numpiezas;i++)
	{
		if (m_PuedenRotarsePiezas==false)
		{
			if ((m_Piezas[i].max>m_Piezas[i].num ) && (m_Piezas[i].largo==largo) 
				&& (m_Piezas[i].ancho<=max_alto) && (m_Piezas[i].ancho>alto))
			{
				if (m_Piezas[i].ancho>max)
				{
					max=m_Piezas[i].ancho;
					pieza=i;
				}
			}
		}
		else
		{
			if ((m_Piezas[i].max>m_Piezas[i].num ) && (m_Piezas[i].largo==largo) 
				&& (m_Piezas[i].ancho<=max_alto) && (m_Piezas[i].ancho>alto))
			{
				if (m_Piezas[i].ancho>max)
				{
					max=m_Piezas[i].ancho;
					pieza=i;
				}
			}
			if ((m_Piezas[i].max>m_Piezas[i].num ) && (m_Piezas[i].ancho==largo) 
				&& (m_Piezas[i].largo<=max_alto) && (m_Piezas[i].largo>alto))
			{
				if (m_Piezas[i].largo>max)
				{
					max=m_Piezas[i].largo;
					pieza=i;
				}
			}
		}
	}
	return pieza;
}
void CUTTING::Posible()
{
	
	if (m_Restringido==false) 
	{
		m_Posible=true;
		return;
	}
//	if (m_Posible==true) return;
	for (register int i=0;i<m_Numpiezas;i++)
	{
		if (m_Piezas[i].num<m_Piezas[i].min) 
		{
			m_Posible=false;
			return;
		}
	}
	m_Posible=true;
	

}
bool CUTTING::EsPosible()
{
	
	if (m_Restringido==false) 
	{
		return true;
	}
//	if (m_Posible==true) return;
	for (register int i=0;i<m_Numpiezas;i++)
	{
		if (m_Piezas[i].num<m_Piezas[i].min) 
		{
			return false;
		}
	}
	return true;
	

}
int CUTTING::ElegirAleatorioPorCiento(std::vector< std::pair<double, candi > > &lista_candidatos)
{
	//Me quedo con uno de los n mejores
	if (lista_candidatos.size()<=1) return 0;

	int n=__max(ceil((1-m_FactorAleatorio)*(lista_candidatos.size()-1)),1);
	std::vector< std::pair<double,int> > vec_aux;
	std::vector< std::pair<double,int> > ::iterator it;
	double minimo=5000000;
	int numminimo=0;
	for (int register i=0;i<lista_candidatos.size();i++)
	{
		//Si tengo menos de los que quiero lo meto
		if (vec_aux.size()<n) 
		{
			std::pair<double,int> p(lista_candidatos[i].first,i);
			vec_aux.push_back(p);
			if (lista_candidatos[i].first<minimo) 
			{
				minimo=lista_candidatos[i].first;
				numminimo=i;
			}
			continue;
		}
		//Si el minimo que tengo es mayor que el nuevo valor no lo meto
		if (minimo>=lista_candidatos[i].first) continue;
		else minimo=9999999;
		//Si es mayor quitar el minimo y actualizar el minimo y tengo que meterlo, 
		int cont=0;
		for (it=vec_aux.begin();it!=vec_aux.end();it++)
		{
			cont++;
			if ((*it).second==numminimo)
			{
				//Quitar el minimo
				it=vec_aux.erase(it);
				if (cont==n) break;
			}
			else
			{
				if ((*it).first<minimo)
				{
					minimo=(*it).first;
					numminimo=(*it).second;
				}
			}
		}
//
		if (lista_candidatos[i].first<minimo) 
		{
			minimo=lista_candidatos[i].first;
			numminimo=i;
		}

		std::pair <double,int> p(lista_candidatos[i].first,i);
		vec_aux.push_back(p);
	}
	return vec_aux[get_random(0,vec_aux.size()-1)].second;
}
//Se leige con probabilidad el que más peso tiene más probabilidad tiene de ser elegido

int CUTTING::ElegirAleatorioPorProbabilidad(std::vector< std::pair<double, candi > > &lista_candidatos,double total)
{
	//Me quedo con uno de los n mejores
	double suma=0;
	if (lista_candidatos.size()<=1) return 0;
	int elegido=get_random(0,total);
	std::vector< std::pair<double,int> > vec_aux;
	for (int register i=0;i<lista_candidatos.size();i++)
	{
		suma+=lista_candidatos[i].first;
		if (suma>= elegido) return i;

	}
	return 0;
//	return vec_aux[get_random(0,vec_aux.size()-1)].second;
}
//En esta función elijo el siguiente teniendo en cuenta que
//no debe estar más del 10% del valor que quiero
int CUTTING::ElegirAleatorioPorValor(std::vector< std::pair<double, candi > > &lista_candidatos,double min)
{
	//Me quedo con uno de los n mejores
	if (lista_candidatos.size()<=1) return 0;
	std::vector< std::pair<double,int> > vec_aux;
	for (int register i=0;i<lista_candidatos.size();i++)
	{

		if (lista_candidatos[i].first>=min )
		{
			std::pair <double,int> p(lista_candidatos[i].first,i);
			vec_aux.push_back(p);
		}

	}
	return vec_aux[get_random(0,vec_aux.size()-1)].second;
}
void CUTTING::EscribirSolucion(std::list<BLOQUE> &lista)
{
	FILE *fin;
	fin=fopen("Solcut.txt","a");

	std::list<BLOQUE> ::iterator itB;
	fprintf(fin,"solucion %d\n", m_lista_bloques.size());
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
//		fprintf(fin,"(%3d,%3d)(%3d,%3d)\t%d\t%d\t%d\n",(*itB).left,(*itB).top,(*itB).right,(*itB).bottom,m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].valor);
		fprintf(fin,"(%d,%d)(%d,%d)\t%d\t%d\t%d\n",(*itB).left,(*itB).top,(*itB).right,(*itB).bottom,m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].valor);
	}
	fclose(fin);
	//Reta
}
void CUTTING::EscribirSolucionLatex(std::list<BLOQUE> &lista)
{
	FILE *fin;
	fin=fopen("Solcut.txt","a+");

	std::list<BLOQUE> ::iterator itB;
	int vals=ContarSolucion(lista);
	fprintf(fin,"solucion: %d Iter %d\n",vals,m_iter_actual);
	fprintf(fin,"L %d W %d Núm Piezas %d\n",m_L,m_W,m_Numpiezas);
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		for (register int ix=1;ix<=((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo);ix++)
		{
			for (register int iy=1;iy<=((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho);iy++)
			{
//		fprintf(fin,"(%3d,%3d)(%3d,%3d)\t%d\t%d\t%d\n",(*itB).left,(*itB).top,(*itB).right,(*itB).bottom,m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].valor);
				fprintf(fin,"(%d,%d)(%d,%d)\t%d\t%d\t%d\n",(*itB).left+(ix-1)*m_Piezas[(*itB).GetNumero()].largo,(*itB).top+(iy-1)*m_Piezas[(*itB).GetNumero()].ancho,(*itB).left+(ix)*m_Piezas[(*itB).GetNumero()].largo,(*itB).top+(iy)*m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].valor);
			}
		}
	}
	fclose(fin);
	//Reta
}
void CUTTING::EscribirSolucionStripLatex(std::list<BLOQUE> &lista)
{
	FILE *fin;
	fin=fopen("Solcut.txt","a+");

	std::list<BLOQUE> ::iterator itB;
	int vals=ContarSolucion(lista);
	fprintf(fin,"solucion: %d Iter %d\n",vals,m_iter_actual);
	fprintf(fin,"W %d L %d Núm Piezas %d\n",m_L,m_W,m_Numpiezas);
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		for (register int ix=1;ix<=((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo);ix++)
		{
			for (register int iy=1;iy<=((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho);iy++)
			{
//		fprintf(fin,"(%3d,%3d)(%3d,%3d)\t%d\t%d\t%d\n",(*itB).left,(*itB).top,(*itB).right,(*itB).bottom,m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].valor);
				fprintf(fin,"(%d,%d)(%d,%d)\t%d\t%d\t%d\n",(*itB).top+(iy-1)*m_Piezas[(*itB).GetNumero()].ancho,(*itB).left+(ix-1)*m_Piezas[(*itB).GetNumero()].largo,(*itB).top+(iy)*m_Piezas[(*itB).GetNumero()].ancho,(*itB).left+(ix)*m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].largo,m_Piezas[(*itB).GetNumero()].ancho,m_Piezas[(*itB).GetNumero()].valor);
			}
		}
	}
	fclose(fin);
	//Reta
}
void CUTTING::EscribirPiezas()
{
	FILE *fin;
	fin=fopen("Solcut.txt","a+");

	fprintf(fin,"Piezas\n");
	for (int register i=0;i<m_Numpiezas;i++)
	{
		fprintf(fin,"%3d\t%3d\t%3d\t%3d\t%d\t%f\n",m_Piezas[i].largo,m_Piezas[i].ancho,m_Piezas[i].min,m_Piezas[i].max,m_Piezas[i].valor,(double)m_Piezas[i].valor/(double)(m_Piezas[i].largo*m_Piezas[i].ancho));
	}
	fclose(fin);
	//Reta
}
void CUTTING::PintarPiezas()
{
	printf("\nPiezas\n");
	for (int register i=0;i<m_Numpiezas;i++)
	{
		printf("%3d\t%3d\t%3d\t%3d\t%d\t%f\n",m_Piezas[i].largo,m_Piezas[i].ancho,m_Piezas[i].min,m_Piezas[i].max,m_Piezas[i].valor,(double)m_Piezas[i].valor/(double)(m_Piezas[i].largo*m_Piezas[i].ancho));
	}
}

void CUTTING::VerificarSolucion(std::list<BLOQUE> &lista_bloques,std::list<RECTAN> &lista_perdidas,int lugar)
{
//	return;
	int sol=Contar(lista_bloques);
	int perdida=Contar(lista_perdidas);
/*	if (perdida!=((m_L*m_W)-sol))
	{
		printf("Problemas diferente perdida que solucion %d, lugar %d, valor %d TamLisTabu %d", m_iter_actual,lugar,m_max_valor,m_lista_tabu.size());
//			for(int register i=0;;i++) printf("Problemas en MejorarBloques 2");
		for(int register i=0;;i++) int j=0;
		exit(3);
	}*/
	//Que este en los rangos de los posibles
	for (register int x=0;x<m_Numpiezas;x++)
	{
		if (m_Piezas[x].num>m_Piezas[x].max)
		{
			printf("Problemas con rangos de piezas, %d  Lugar %d  Pieza %d Min %d Max %d Num %d", m_iter_actual,lugar,x,m_Piezas[x].min,m_Piezas[x].max,m_Piezas[x].num);
//			for(int register i=0;;i++) printf("Problemas en MejorarBloques 2");
			for(int register i=0;;i++) int j=0;
			exit(3);
		}

	}
	//Que cumpla la solución
	std::list<BLOQUE>::iterator itB1;
	for (x=0;x<m_Numpiezas;x++)
	{
		if (m_Piezas[x].num==0) continue;
		int val1=0;
		for(itB1=lista_bloques.begin();itB1!=lista_bloques.end();itB1++)
		{
			if ((*itB1).GetNumero()==x)
			val1+=((*itB1).Width()*(*itB1).Height())/(m_Piezas[(*itB1).GetNumero()].largo*m_Piezas[(*itB1).GetNumero()].ancho);
		}
		if (val1!=m_Piezas[x].num)
		{
			printf("Problemas con rangos de piezas pero no es por maximo, %d  Lugar %d  Pieza %d Min %d Max %d Num %d Cuento %d", m_iter_actual,lugar,x,m_Piezas[x].min,m_Piezas[x].max,m_Piezas[x].num,val1);
//			for(int register i=0;;i++) printf("Problemas en MejorarBloques 2");
			for(int register i=0;;i++) int j=0;
			exit(3);
		}


	}

	bool intersectan_bloques=ComprobarBloquesNoIntersectan(lista_bloques);
	if (intersectan_bloques==true)
	{
		printf(" Intersectan bloques %d %d", m_iter_actual,lugar);
		for(int register i=0;;i++) ;
		exit(3);
	}
	bool intersectan_bloqu_perdi=ComprobarBloquesYPerNoIntersectan(lista_bloques,lista_perdidas);
	if (intersectan_bloqu_perdi==true)
	{
		printf("Intersectan bloques y perdidas %d",lugar);
		for(int register i=0;;i++) ;
		exit(3);
	}

}
int CUTTING::Contar(std::list<RECTAN> &lista)
{
	int Val=0;
	std::list<RECTAN>::iterator itB;
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		Val+=((*itB).Height()*(*itB).Width());
	}
	return Val;
}
int CUTTING::ContarPerdidaSegura(std::list<RECTAN> &lista)
{
//	return 0;
	int Val=0;
	std::list<RECTAN>::iterator itB;
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		if ((*itB).right==m_L) continue;
		Val+=((*itB).Height()*(*itB).Width());
	}
	return Val;
}
int CUTTING::Contar(std::list<BLOQUE> &lista)
{
	int Val=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		Val+=((*itB).Height()*(*itB).Width());
	}
	return Val;
}
void CUTTING::RepararNumeros(std::list<BLOQUE> &lista)
{
	std::list<BLOQUE>::iterator itB;
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		//Reponemos los números de las piezas
		m_Piezas[(*itB).GetNumero()].num-=((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho);
	}
}
void CUTTING::ColocarNumeros(std::list<BLOQUE> &lista)
{
	for (int kin=0;kin<m_Numpiezas;kin++)
		m_Piezas[kin].num=0;
	std::list<BLOQUE>::iterator itB;
	for(itB=lista.begin();itB!=lista.end();itB++)
	{
		//Reponemos los números de las piezas
		m_Piezas[(*itB).GetNumero()].num+=((*itB).Height()*(*itB).Width())/(m_Piezas[(*itB).GetNumero()].largo*m_Piezas[(*itB).GetNumero()].ancho);
	}
}
bool CUTTING::ComprobarBloquesYPerNoIntersectan(std::list<BLOQUE> &lista,std::list<RECTAN> &lista2)
{
	std::list<BLOQUE>::iterator itB1;
	std::list< RECTAN >::iterator itB3;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		for(itB3=lista2.begin();itB3!=lista2.end();itB3++)
		{
			BLOQUE b1=(*itB1);
			RECTAN b2=(*itB3);
			if( (*itB1).top>=(*itB3).bottom || (*itB3).top>=(*itB1).bottom )
				continue;
			if( (*itB1).left>=(*itB3).right || (*itB3).left>=(*itB1).right)
				continue;	
			return true;

		}
	}
	return false;
}
bool CUTTING::ComprobarBloquesNoIntersectan(std::list<BLOQUE> &lista)
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
void CUTTING::EscribirBloquesPantalla(std::list<BLOQUE> &lista)
{
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		printf("%3d\t%3d\t%3d\t%3d\t%d\n",(*itB).top,(*itB).bottom,(*itB).left,(*itB).right,(*itB).GetNumero());
	}

	//Reta
}
int CUTTING::EvaluarMovimiento(MOVE &Movimiento)
{
//		return 0;
		int max_candidatos=0;
		if (m_conpesos==true)
		{
			max_candidatos=Movimiento.GetValor();
			if (EsPosible()==false)
			{
				max_candidatos-=m_Cota*10;
			}
			//Para las frecuencias
//			if (m_iter_sin_mejorar%400<100 && m_iter_sin_mejorar>=400)
//			max_candidatos-=ContarFrecuencias(Movimiento.GetListaBloques());
//			if (Valida_Simetria(Movimiento.GetListaPerdidas())==false)
//				max_candidatos-=5000;
			return max_candidatos;
		}
		int oscil=1;
		if (m_iter_sin_mejorar>=30000)
		{
			oscil=(m_iter_sin_mejorar-600)/100;
		}

		if (Valida_Simetria(Movimiento.GetListaPerdidas())==false)
			max_candidatos-=m_Cota*oscil;
		max_candidatos+=Movimiento.GetValor();
		//Para las frecuencias
//		if (m_iter_sin_mejorar%400<100 && m_iter_sin_mejorar>=400)
//		max_candidatos-=ContarFrecuencias(Movimiento.GetListaBloques());

		//Para intentar tener siempre pocas perdidas
		max_candidatos-=((Movimiento.GetListaPerdidas().size())*(m_Cota/2));
//		if (m_iter_sin_mejorar>1000)
//			max_candidatos-=(Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas())*5)/(m_L*m_W);
//		if (m_iter_sin_mejorar>1000)
//			max_candidatos-=Perdida_Mitad(Movimiento.GetListaPerdidas());
		//Diversificar
//		if (m_iter_sin_mejorar%500<=40 && m_iter_sin_mejorar>40)
//		max_candidatos=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
		//Devuelve el tanto por mil de perdida en el cuadrante
		if (m_iter_sin_mejorar==0) return max_candidatos;
		if (m_iter_sin_mejorar%50==0) 
		max_candidatos-=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
		//Oscilación estrategica
		//una vez que llevo más de x iteraciones sin mejorar
		//Cambio los valores de la función objetivo
		//Oscilación estratégica
		if (m_iter_sin_mejorar>10000)
		{
			int caso=(m_iter_sin_mejorar-100)/100;
			switch (caso)
			{
				case 2:
				{
					max_candidatos-=Perdida_Mitad(Movimiento.GetListaPerdidas())*25;
					break;
				}
				case 1:
				{
					max_candidatos-=((Movimiento.GetListaPerdidas().size()))*10;
					break;
				}
				case 0:
				{
					max_candidatos-=Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
					break;
				}
				case 3:
				{
					max_candidatos-=(int)((Movimiento.GetListaPerdidas().size()));
					break;
				}
				case 4:
				{
					max_candidatos=-Rectangulo_menor_estan_perdidas(Movimiento.GetListaPerdidas());
					break;
				}
//			   default:
//			   doDefault( );
			}

		}
		return max_candidatos;
//		return 0;
}
int CUTTING::PerdidaEnLados(std::list<RECTAN> &listaP)
{
	std::list<RECTAN>::iterator itB;
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
int CUTTING::Rectangulo_menor_estan_perdidas(std::list<RECTAN> &lista)
{
	std::list<RECTAN> ::iterator itC;
	CRect Union(0,0,0,0);
	int medida_union=0;

//	bool no_quiero_tiene_borde=false;
//	int MasGrande=(((m_W/2)+(m_L/2))*10);
	double multi=100;
	double peso=0.25;
//	int suma_huecos=0;
//	int MasGrande=(peso*(multi*((m_W/2)+(m_L/2)))+(1-peso)*(m_L*m_W));
//	int MasGrande=(peso*(multi*((m_W/2)+(m_L/2)))+(1-peso)*(m_L*m_W));
	bool prime=false;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		UnionRect(&Union,&(*itC),&Union);
	}
	if (Union.top==0 && Union.bottom==0) return 0;
		
//	medida_union=multi*(abs((m_W*(0.5))-Union.CenterPoint().y)+abs((m_L*(0.5))-Union.CenterPoint().x));
//	medida_union=(peso*(medida_union)+(1-peso)*(Union.Width()*Union.Height()));
	medida_union=Union.Width()*Union.Height();
//	double temp=(double)medida_union/(double)MasGrande;

//	double temp=(double)medida_union/(double)MasGrande;
//	medida_union=temp;
//	fprintf(fin,"%d\n",medida_union);

	return medida_union;
}
int CUTTING::Perdida_Mitad(std::list<RECTAN> &lista)
{
//	if (m_Simetria==false)	return true;
	int mitadPH=0,mitadPV=0;
	std::list<RECTAN> ::iterator itB1;
	double mitadL=(double)m_L/2;
	double mitadW=(double)m_W/2;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		if ((*itB1).left<mitadL)
		{
			if ((*itB1).right<mitadL)
			{
				mitadPV+=(int)(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadPV+=(int)(*itB1).Height()*(int)(mitadL-(*itB1).left);
			}
		}
		if ((*itB1).top<mitadW)
		{
			if ((*itB1).bottom<mitadW)
			{
				mitadPH+=(int)(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadPH+=(int)(*itB1).Width()*(int)(mitadW-(*itB1).top);
			}
		}
	}
//	if (m_iter_actual%200<=100) return ((mitadPV*1000)/(mitadL*mitadW));
//	else return ((mitadPH*1000)/(mitadL*mitadW));

	if (m_L>m_W)
		return ((mitadPV*1000)/(mitadL*mitadW));
	if (m_W>m_L)
		return ((mitadPH*1000)/(mitadL*mitadW));
	return ((mitadPH*1000)/(mitadL*mitadW));
}
bool CUTTING::Valida_Simetria(std::list<RECTAN> &lista)
{
//	if (m_Simetria==false)	return true;
	int mitadPH=0,mitadPV=0,totalP=0;
	std::list<RECTAN> ::iterator itB1;
	double mitadL=(double)m_L/2;
	double mitadW=(double)m_W/2;
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		totalP+=(*itB1).Width()*(*itB1).Height();
		if ((*itB1).left<mitadL)
		{
			if ((*itB1).right<mitadL)
			{
				mitadPV+=(int)(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadPV+=(int)(*itB1).Height()*(int)(mitadL-(*itB1).left);
			}
		}
		if ((*itB1).top<mitadW)
		{
			if ((*itB1).bottom<mitadW)
			{
				mitadPH+=(int)(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadPH+=(int)(*itB1).Width()*(int)(mitadW-(*itB1).top);
			}
		}
	}
//	if (m_iter_actual%200<=100) return ((mitadPV*1000)/(mitadL*mitadW));
//	else return ((mitadPH*1000)/(mitadL*mitadW));
	if (m_L>=m_W)
	{
		if (mitadPV>(double)totalP/(double)2)
			return false;
	}
	if (m_W>m_L)
	{
		if (mitadPH>(double)totalP/(double)2)
			return false;
	}
	return true;
}
void CUTTING::ActualizarConjuntoReferencia(MOVE &M,int valor)
{
//	return;
//	if (valor<m_solbest && m_lista_bloques.size()<(m_Numpiezas-2)) 
//		return;
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
//				if (Lista_de_Perdidas_Iguales((*itB).lista_perdidas,s.lista_perdidas)==true)
					no_meter=true;
			}
	}
	if (no_meter==true) return;
	if (m_conjunto_ref.size()<(10)) 
	{

		m_conjunto_ref.push_back(s);
		return;
	}
	int maxim=MaximoConjuntoRefPerdidas();
	if (maxim<s.lista_perdidas.size()) return;
	//Quito el más pequeño
	bool stop=false;
	//Quito el más pequeño en pérdidas
	for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end() && stop!=true;itB++)
	{
			if ((*itB).lista_perdidas.size()==maxim) 
			{
				if ((*itB).lista_perdidas.size()==s.lista_perdidas.size() && (*itB).fobjetivo>s.fobjetivo) 
				{
					itB=m_conjunto_ref.erase(itB);
					stop=true;
					break;
				}
				if ((*itB).lista_perdidas.size()>s.lista_perdidas.size())
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
int CUTTING::MinimoConjuntoRef(void)
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
int CUTTING::MaximoConjuntoRefPerdidas(void)
{
	int maxim=0;
	int maxim2=0;
	std::list<pathre>::iterator itB;
	for(itB=m_conjunto_ref.begin();itB!=m_conjunto_ref.end();itB++)
	{
		if ((*itB).lista_perdidas.size()>=maxim)
		{
			if ((*itB).lista_perdidas.size()==maxim)
			{
				if ((*itB).fobjetivo<maxim2)
				{
					maxim=(*itB).lista_perdidas.size();
					maxim2=(*itB).fobjetivo;

				}
			}
			else
			{
				maxim=(*itB).lista_perdidas.size();
				maxim2=(*itB).fobjetivo;
			}


		}
	}
	return maxim;
}
int CUTTING::CombinarSolucionesConjuntoRef()
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
//			if ((*itB).lista_bloques.size()>(*itB2).lista_bloques.size())
			if (get_random(0,1)==0)
			{
				sol1=CaminoDeAaB((*itB2),(*itB));
			}
			else sol1=CaminoDeAaB((*itB),(*itB2));

			if (sol1>=m_solbest) 
			{
				EscribirSolucionLatex((*itB).lista_bloques);
				EscribirSolucionLatex((*itB2).lista_bloques);
				EscribirSolucionLatex(m_solbest_lista_bloques);
				DibujarSolucion((*itB).lista_bloques,(*itB).lista_perdidas,151,150);
				DibujarSolucion((*itB2).lista_bloques,(*itB2).lista_perdidas,151,150);
				return sol1;
			}
		}
	}
	return 0;
}
int CUTTING::CaminoDeAaB(PATHRE A,PATHRE &B)
{
//Tengo que ir metiendo los bloques de la solución B
//en A e ir paletizando cada vez, los bloques de A si que puedo irlos moviendo
	std::list<BLOQUE>::iterator itB,itBB;
	std::list<RECTAN>::iterator itR;
	//Si quiero hacer la solución simetrica
//	printf("kk");
	DibujarSolucion(A.lista_bloques,A.lista_perdidas,999,150);
	//Hago una solución que es simétrica de los dos ejes
	//Simetrica pero tambien debo hacer simetricas las perdidas
	for (itB=A.lista_bloques.begin();itB!=A.lista_bloques.end();itB++)
	{
		int kk=(*itB).Width();
		(*itB).left=m_L-(*itB).left-(*itB).Width();
		(*itB).right=(*itB).left+kk;
//		kk=(*itB).Height();
//		(*itB).top=m_W-(*itB).top-(*itB).Height();
//		(*itB).bottom=(*itB).top+kk;
		(*itB).SetPuedoMover(true);
	}
	for (itR=A.lista_perdidas.begin();itR!=A.lista_perdidas.end();itR++)
	{
		int kk=(*itR).Width();
		(*itR).left=m_L-(*itR).left-(*itR).Width();
		(*itR).right=(*itR).left+kk;
//		kk=(*itR).Height();
//		(*itR).top=m_W-(*itR).top-(*itR).Height();
//		(*itR).bottom=(*itR).top+kk;

	}
	FILE *fin;
	fin=fopen("Solcut.txt","a+");

	fprintf(fin," Simetrica ");
	fclose(fin);

	EscribirSolucionLatex(A.lista_bloques);
	DibujarSolucion(A.lista_bloques,A.lista_perdidas,888,150);
	DibujarSolucion(B.lista_bloques,B.lista_perdidas,777,151);
//	EscribirBloquesPantalla(A.lista_bloques);
	int i=0;
	//Para meter primero las de las esquinas.
	for (itB=B.lista_bloques.begin();itB!=B.lista_bloques.end();itB++)
	{
		if (!((*itB).top==0 || (*itB).bottom==m_W || (*itB).right==m_L || (*itB).left==0))
			continue;
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
//		VerificarSolucion(A.lista_bloques,A.lista_perdidas,8888);
		//Si esta ya en la solución seguir poner que no se mueva y seguir
		bool es_nuevo=true;
		for (itBB=A.lista_bloques.begin();itBB!=A.lista_bloques.end() && es_nuevo==true;itBB++)
		{
			if ((*itBB).top==(*itB).top && (*itBB).left==(*itB).left
				&& (*itBB).right==(*itB).right && (*itBB).bottom==(*itB).bottom)
			{
				es_nuevo=false;
				(*itB).SetPuedoMover(false);
			}


		}
		if (es_nuevo==false) continue;
		ColocarNumeros(A.lista_bloques);		

		MeterBloqueSolucion((*itB),A.lista_bloques);

		(*itB).SetPuedoMover(false);
		A.lista_bloques.push_back((*itB));
		A.lista_perdidas.clear();
		RECTAN PTotal(0,0,m_L,m_W);
		A.lista_perdidas.push_back(PTotal);
		Actualizar_Perdida(A.lista_bloques,A.lista_perdidas);
//		VerificarSolucion(A.lista_bloques,A.lista_perdidas,5879);
//		Bloques_Hacia_Las_Esquinas_Combinar(A.lista_bloques,A.lista_perdidas);
		Bloques_Hacia_Las_Esquinas_Combinar(A.lista_bloques,A.lista_perdidas);
		JuntarPerdida(A.lista_perdidas,'P');
//		CompactarPerdida(A.lista_perdidas);
		std::list<BLOQUE> lista;
		Rellenar(lista,A.lista_perdidas,9999);
		A.lista_bloques.insert(A.lista_bloques.begin(),lista.begin(),lista.end());
			FILE *fin;
	fin=fopen("Solcut.txt","a+");

	fprintf(fin," %d PPP",i);
	fclose(fin);
		EscribirSolucionLatex(A.lista_bloques);
		int cont=Contar(A.lista_bloques);
//		VerificarSolucion(A.lista_bloques,A.lista_perdidas,978);
		DibujarSolucion(A.lista_bloques,A.lista_perdidas,cont,150,(*itB));
//		printf("%d ",cont);
		if (cont>=m_solbest) 
		{
//			VerificarSolucion(A.lista_bloques,A.lista_perdidas,1);
			m_solbest_lista_bloques=A.lista_bloques;
			m_solbest_lista_perdidas=A.lista_perdidas;
			m_solbest=cont;
//			for (int j=1;j<88888;j++)
			DibujarSolucion(A.lista_bloques,A.lista_perdidas,cont,150,(*itB));
			m_iter_solbest=m_iter_actual;
			for (int i=0;i<50;i++)
			printf("Conseguido Solución de %d",cont);
			ColocarNumeros(m_lista_bloques);		
			if (cont==m_solbest) return cont;
		}
	}
	ColocarNumeros(m_lista_bloques);		

	return 0;

}
void CUTTING::MeterBloqueSolucion(BLOQUE &B1,std::list<BLOQUE> &listaB)
{
	std::list<BLOQUE> ::iterator itB,itB1;
	//Creo lista de pérdidas nuevas y lista de bloques nueva
	std::list<BLOQUE> lista_aux;
	int piezasB1=((B1.Width()/m_Piezas[B1.GetNumero()].largo)*(B1.Height()/m_Piezas[B1.GetNumero()].ancho));
	m_Piezas[B1.GetNumero()].num+=piezasB1;
	for (itB=listaB.begin();itB!=listaB.end();itB++)
	{
//		BLOQUE b11=(*itB);
		//Los que son el mismo número y pasa las capacidades del problema los quito
		if ((*itB).GetNumero()==(B1.GetNumero()) && ((m_Piezas[B1.GetNumero()].num)>m_Piezas[B1.GetNumero()].max))
		{
			int piezasBloque=(((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo)*((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho));

			m_Piezas[B1.GetNumero()].num=m_Piezas[B1.GetNumero()].num-piezasBloque;
			continue;
		}
		//Los que esten incluidos dentro del nuevo rectángulo los quito
		
		if ((((*itB).bottom<=B1.bottom) && ((*itB).top>=B1.top))
		&& (((*itB).right<=B1.right) && ((*itB).left>=B1.left)))
		{
			int piezasBloque=(((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo)*((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho));

			m_Piezas[(*itB).GetNumero()].num=m_Piezas[(*itB).GetNumero()].num-piezasBloque;
			continue;
		}
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
		int piezasBloquek=(((*itB).Width()/m_Piezas[(*itB).GetNumero()].largo)*((*itB).Height()/m_Piezas[(*itB).GetNumero()].ancho));

		m_Piezas[(*itB).GetNumero()].num=m_Piezas[(*itB).GetNumero()].num-piezasBloquek;

		//Solapa con el bloque nuevo
		//quitar el bloque y crear pérdidas
//		cortar_Bloques((*itB),B1,lista_aux);
		

	}
	listaB=lista_aux;
}
bool CUTTING::Lista_de_Perdidas_Iguales(std::list<RECTAN> &lista,std::list<RECTAN> &lista2)
{
	std::list<RECTAN> ::iterator itL,itL2;
	bool esta_perdida=false;
	if (lista.size()!=lista2.size()) return false;
	for (itL=lista.begin();itL!=lista.end();itL++)
	{
		esta_perdida=false;
		for (itL2=lista2.begin();itL2!=lista2.end();itL2++)
		{
			if ((*itL2).GetNumero()==(*itL).GetNumero() && (*itL).Width()==(*itL2).Width())
			{
				esta_perdida=true;
//				if ((*itL2).EqualRect((*itL))!=0) esta_perdida=true;
			}
			
		}
		if (esta_perdida==false) return false;
	}
	return true;

}
/*
void CUTTING::Bloques_Hacia_Las_Esquinas_Combinar(std::list<BLOQUE> &listaB, std::list<RECTAN> &listaP)
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
			RECTAN Rect(0,(*itL).top,(*itL).left,(*itL).bottom);

			//Poner bloque pegado a la izquierda
			if (Existe_Perdida(listaP,Rect,8)==true)
			{
				(*itL).left=0;
				(*itL).right=(*itL).right-Rect.right;
				//Nueva perdida
				RECTAN perdida;
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
				RECTAN Rect((((*itL).right)),(*itL).top,m_L,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,8)==true)
				{
					(*itL).right=m_L;
					(*itL).left=(*itL).left+Rect.Width();
					RECTAN perdida;
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
	//tipo_union='V';
	JuntarPerdida(listaP,'V');
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
				RECTAN Rect((*itL).left,0,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).top=0;
					(*itL).bottom=(*itL).bottom-Rect.Height();
					//Nueva perdida
					RECTAN perdida;
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
				RECTAN Rect((((*itL).left)),(*itL).bottom,(*itL).right,m_W);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).bottom=m_W;
					(*itL).top=(*itL).top+Rect.Height();
					RECTAN perdida;
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
//	tipo_union='H';
	JuntarPerdida(listaP,'H');
	}while(seguir==true);
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
				RECTAN Rect((*itL).left-izq,(*itL).top,(*itL).left,(*itL).bottom);
				//Poner bloque pegado a la izquierda
				if (Existe_Perdida(listaP,Rect,8)==true)
				{
					(*itL).left=(*itL).left-izq;
					(*itL).right=(*itL).right-izq;
					//Nueva perdida
					RECTAN perdida;
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

				RECTAN Rect((((*itL).right)),(*itL).top,(*itL).right+der,(*itL).bottom);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,8)==true)
				{
					(*itL).right=(*itL).right+der;
					(*itL).left=(*itL).left+der;
					RECTAN perdida;
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
				RECTAN Rect((*itL).left,(*itL).top-aba,(*itL).right,(*itL).top);

				//Poner bloque pegado a abajo
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).top=(*itL).top-aba;
					(*itL).bottom=(*itL).bottom-aba;
					//Nueva perdida
					RECTAN perdida;
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

				RECTAN Rect((((*itL).left)),(*itL).bottom,(*itL).right,(*itL).bottom+arri);
				
				//Poner bloque pegado a la derecha
				if (Existe_Perdida(listaP,Rect,9)==true)
				{
					(*itL).bottom=(*itL).bottom+arri;
					(*itL).top=(*itL).top+arri;
					RECTAN perdida;
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
}*/
void CUTTING::cortar_Bloques(BLOQUE &b1,BLOQUE &b2,std::list<BLOQUE> &listaB)
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
int  CUTTING::ProximoBloque(BLOQUE &B,int tipo)
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

//Al primer bloque le quito lo que tiene en común con 
// el segundo
int CUTTING::Restar_Rectangulo(BLOQUE &b1,BLOQUE &b2,RECTAN &B1,RECTAN &B2,RECTAN &B3,RECTAN &B4)
{
	//A b1 le quito lo que tiene en común con el segundo
	int l=2;
	int w=2;
	if (b1.GetTipo()=='V')
	{
//		l=m_w;
//		w=m_l;
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
int  CUTTING::ProximoBloque(std::list<BLOQUE> &lista,BLOQUE &B,int tipo)
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
//Lista TabuPerdidas
int CUTTING::EsTabuPerdidas(MOVE &M1)
{
	m_totalmov++;

//	return false;
	bool distinta=true;
	std::list< std::list<RECTAN> > ::iterator itB;
	std::list<RECTAN>::iterator itB2,itB3;
	int max=m_lista_tabu_perdidas.size()+1;
	int cuenta1=Contar(M1.GetListaPerdidas());
	CRect Union2(0,0,0,0);
	for(itB3=	M1.GetListaPerdidas().begin();itB3!=	M1.GetListaPerdidas().end() && distinta!=false;itB3++)
	{
		UnionRect(&Union2,&(*itB3),&Union2);
	}

	for (itB=m_lista_tabu_perdidas.begin();itB!=m_lista_tabu_perdidas.end();itB++)
	{
		max--;
		int cuenta2=Contar((*itB));
		if (cuenta1!=cuenta2 ) continue;
		CRect Union(0,0,0,0);

		for(itB2=(*itB).begin();itB2!=(*itB).end() ;itB2++)
		{
			UnionRect(&Union,&(*itB2),&Union);
		}
		if (Union2.top==Union.top && Union2.bottom==Union.bottom  &&
			Union2.left==Union.left && Union2.right==Union.right )
		{
//			int permi1=Perdida_Mitad((*itB));
//			int permi2=Perdida_Mitad(M1.GetListaPerdidas());
//			if (permi1==permi2)
				return max;
//			else
//				int perro=6;
		}
		//	return max;


		

	}
	m_movtabu++;
	return 9999;
//	if (bien==m_lista_tabu_perdidas.size()) return 0;
//	else return 9999;
}
void CUTTING::Add_Lista_TabuPerdidas(std::list<RECTAN> &lista)
{
//	return;
	
	
	if (m_lista_tabu_perdidas.size()>m_tam_tabu_perdidas)
	{
		m_lista_tabu_perdidas.pop_front();
		m_lista_tabu_perdidas.pop_front();
		m_lista_tabu_perdidas.push_back(lista);
	}
	else
	{
		m_lista_tabu_perdidas.push_back(lista);

	}
}
void CUTTING::Add_Lista_TabuNew(std::list<RECTAN> &lista)
{
//	return;
	std::list< RECTAN> ::iterator itB;
	int cuenta1=ContarSolucion(m_lista_bloques);
//	int cuenta2=Contar(lista);
//	if ((cuenta1+cuenta2)!=(m_L*m_W))
//		printf("Mierdecilla");
	CRect Union(0,0,0,0);
	for(itB=lista.begin();itB!=lista.end() ;itB++)
	{
		UnionRect(&Union,&(*itB),&Union);
	}
	ETABU kk;
	kk.area=cuenta1;
	kk.Union=Union;
	kk.num=0;
//	kk.num=Perdida_Mitad(lista,Union);
	
	if (m_lista_tabu_new.size()>m_tam_tabu_perdidas)
	{
		m_lista_tabu_new.pop_front();
		m_lista_tabu_new.pop_front();
		m_lista_tabu_new.push_back(kk);
	}
	else
	{
		m_lista_tabu_new.push_back(kk);

	}
}
//Lista TabuPerdidas
int CUTTING::EsTabuNew(MOVE &M1)
{
	m_totalmov++;

//	return false;
//	int bien=0;
	std::list< etabu > ::iterator itB;
	std::list<RECTAN>::iterator itB2,itB3;
	CRect Union(0,0,0,0);
	int max=m_lista_tabu_new.size()+1;
	int area1=ContarSolucion(M1.GetListaBloques());
//	int area2=Contar(M1.GetListaPerdidas());
//	if ((area1+area2)!=(m_L*m_W))
//		printf("Mierdecilla");

	for(itB2=M1.GetListaPerdidas().begin();itB2!=M1.GetListaPerdidas().end() ;itB2++)
	{
		UnionRect(&Union,&(*itB2),&Union);
	}
//	int permi1=Perdida_Mitad(M1.GetListaPerdidas(),Union);
	for (itB=m_lista_tabu_new.begin();itB!=m_lista_tabu_new.end();itB++)
	{
		max--;
		if (area1!=(*itB).area ) continue;
//		if (permi1!=(*itB).num) continue;

		CRect Union2(0,0,0,0);

		if ((*itB).Union.top==Union.top && (*itB).Union.bottom==Union.bottom  &&
			(*itB).Union.left==Union.left && (*itB).Union.right==Union.right )
		{
//			int permi1=Perdida_Mitad((*itB));
//			int permi2=Perdida_Mitad(M1.GetListaPerdidas());
//			if (permi1==permi2)
				return max;
//			else
//				int perro=6;
		}
		//	return max;


		

	}
	m_movtabu++;
	return 9999;
//	if (bien==m_lista_tabu_perdidas.size()) return 0;
//	else return 9999;
}
int CUTTING::Perdida_Mitad(std::list<RECTAN> &lista, CRect &rect)
{
//	if (m_Simetria==false)	return true;
	int mitadPH=0,mitadPV=0;
	std::list<RECTAN> ::iterator itB1;
	double mitadL=rect.right-((double)rect.Width()/2);
	double mitadW=rect.bottom-((double)rect.Height()/2);
	for (itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		if ((*itB1).left<mitadL)
		{
			if ((*itB1).right<mitadL)
			{
				mitadPV+=(int)(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadPV+=(int)(*itB1).Height()*(int)(mitadL-(*itB1).left);
			}
		}
		if ((*itB1).top<mitadW)
		{
			if ((*itB1).bottom<mitadW)
			{
				mitadPH+=(int)(*itB1).Height()*(*itB1).Width();
			}
			else
			{
				mitadPH+=(int)(*itB1).Width()*(int)(mitadW-(*itB1).top);
			}
		}
	}
//	if (m_iter_actual%200<=100) return ((mitadPV*1000)/(mitadL*mitadW));
//	else return ((mitadPH*1000)/(mitadL*mitadW));

	if (rect.Width()<rect.Height())
		return ((mitadPV*1000)/(mitadL*mitadW));
	else
		return ((mitadPH*1000)/(mitadL*mitadW));
	return ((mitadPH*1000)/(mitadL*mitadW));
}
int CUTTING::ContarFrecuencias(std::list<BLOQUE> &lista)
{
	int val=0;
	std::list<BLOQUE> ::iterator itB;
	for (itB=lista.begin();itB!=lista.end();itB++)
	{
		val+=(m_iter_actual)-m_Piezas[(*itB).GetNumero()].frecuencia;
	}
	return val;
}
void CUTTING::ActualizarFrecuencias(void)
{
	std::list<BLOQUE> ::iterator itB;
	for (itB=m_lista_bloques.begin();itB!=m_lista_bloques.end();itB++)
	{
		int i=(*itB).GetNumero();
		m_Piezas[i].frecuencia+=((*itB).Width()*(*itB).Height())/(m_Piezas[i].largo*m_Piezas[i].ancho);
	}
}
void CUTTING::BorrarFrecuencias(void)
{
	for (int i=0;i<m_Numpiezas;i++)
		m_Piezas[i].frecuencia=0;
}
	//*********
	//Tipo 1 es elegir meter la más valiosa 
	//************
	//Tipo 2 es elegir meter la mejor para la función objetivo
	//*************
	//Tipo 3 es aleatoriamente aplicar tipo 1 o tipo 2
void CUTTING::ElegirPieza(BLOQUE &b1,RECTAN &Rect, int tipo,int num)
{
	if ((m_MinLargo>Rect.Width() || m_MinAncho>Rect.Height()) ) return ;

	//Si tenemos un problema restringido al principio
	//voy metiendo solo las obligatorias
	//una vez hecho esto ya continuo
	double max=0;
	int numero=0;
	bool necesaria=false,necesaria2=false;
//	if (tipo==3) tipo=get_random(1,2);
	//Las recorro todas las que se pueden
	for (int i=0;i<m_Numpiezas;i++)
	{
		if (i==num) continue;

		//Si puede elegir esa pieza
		if (m_Piezas[i].num>=m_Piezas[i].max) continue;
		bool basta=false;
		for (int j=1;j<=(m_Piezas[i].max-m_Piezas[i].num) && basta!=true;j++)
		{
			//Esta variable me dice si ya no caben más de j
			basta=true;
			//Valor de meter esta pieza
			double val=0;
			//La más valiosa
			if (tipo==1) val=(double)m_Piezas[i].valor/(double)(m_Piezas[i].largo*m_Piezas[i].ancho);
			//Mejor función objetivo
			if (tipo==2) val=m_Piezas[i].valor*j;
			//Mas largo
			if (tipo==3) val=m_Piezas[i].largo*j+m_Piezas[i].ancho*0.01;
			if (tipo==4) val=m_Piezas[i].ancho*j+m_Piezas[i].largo*0.01;

			//Si es necesaria meterla por las restricciones
			if (m_Piezas[i].min>=(m_Piezas[i].num+j)) 
				necesaria=true;
			else
				necesaria=false;
			//Si tengo una que es necesaria y la que voy a explorar no, seguir
			if (necesaria2==true && necesaria==false) continue;
			//Si puedo poner todas esas piezas en horizontal
			if (m_Piezas[i].largo*j<=Rect.Width() && m_Piezas[i].ancho<=Rect.Height())
			{
				if (((((val>max || (val==max && (((m_Piezas[i].largo*j)*(m_Piezas[i].ancho))>(b1.bottom*b1.right)) )) && (tipo==1 ||tipo==3)) || ((val>max || (val==max && (((m_Piezas[i].largo*j)*(m_Piezas[i].ancho))<(b1.bottom*b1.right)) )) && (tipo==2))) || (necesaria==true && necesaria2==false))|| (tipo==4 && val>max))
				{
					b1.bottom=m_Piezas[i].ancho;
					b1.right=m_Piezas[i].largo*j;
					b1.SetNumero(i);
					max=val;
					numero=j;
					//Si es necesaria meterla por las restricciones
					necesaria2=necesaria;
				}
				basta=false;
			}
			if (j==1) continue;
			//Si puedo poner todas esas piezas en vertical
			if (m_Piezas[i].largo<=Rect.Width() && m_Piezas[i].ancho*j<=Rect.Height())
			{
				if ((((val>max || (val==max && (((m_Piezas[i].largo)*(m_Piezas[i].ancho*j))>(b1.bottom*b1.right)) )) && (tipo==1)) || ((val>max || (val==max && (((m_Piezas[i].largo)*(m_Piezas[i].ancho*j))<(b1.bottom*b1.right)) )) && tipo==2)) || (necesaria==true && necesaria2==false))
				{
					b1.bottom=m_Piezas[i].ancho*j;
					b1.right=m_Piezas[i].largo;
					b1.SetNumero(i);
					max=val;
					numero=j;
					//Si es necesaria meterla por las restricciones
					necesaria2=necesaria;
				}
				basta=false;
			}
		}
	}
	m_Piezas[b1.GetNumero()].num+=numero;
}
//Elegir Pieza con algo de aleatoriedad 
void CUTTING::ElegirPiezaAleatoria(BLOQUE &b1,RECTAN &Rect, int tipo,int num)
{
	if ((m_MinLargo>Rect.Width() || m_MinAncho>Rect.Height()) ) return ;
	std::vector< std::pair<double, candi > > lista_candidatos;
	double suma=0;
	//Si tenemos un problema restringido al principio
	//voy metiendo solo las obligatorias
	//una vez hecho esto ya continuo
	double max=0;
	int numero=0;
	bool necesaria=false,necesaria2=false;
	//Las recorro todas las que se pueden
	for (int i=0;i<m_Numpiezas;i++)
	{
		if (i==num) continue;
		//Si puede elegir esa pieza
		if (m_Piezas[i].num>=m_Piezas[i].max) continue;
		bool basta=false;
		for (int j=1;j<=(m_Piezas[i].max-m_Piezas[i].num) && basta!=true;j++)
		{
			//Esta variable me dice si ya no caben más de j
			basta=true;
			//Valor de meter esta pieza
			double val=0;
			//La más valiosa
			if (tipo==1) val=(double)m_Piezas[i].valor/(double)(m_Piezas[i].largo*m_Piezas[i].ancho);
			//Mejor función objetivo
			if (tipo==2 || tipo==3) val=m_Piezas[i].valor*j;

			//Si es necesaria meterla por las restricciones
			if (m_Piezas[i].min>=(m_Piezas[i].num+j)) 
				necesaria=true;
			else
				necesaria=false;
			//Si tengo que no es posible solo quiero necesarias
			if (m_Posible==false && necesaria==false)  continue;
			//Si puedo poner todas esas piezas en horizontal
			if (m_Piezas[i].largo*j<=Rect.Width() && m_Piezas[i].ancho<=Rect.Height())
			{
				if (val>max) max=val;
				suma+=val;
				numero=j;
				candi c={j,i,'H'};
				std::pair<double, candi > p(val,c);
				lista_candidatos.push_back(p);
				//Si es necesaria meterla por las restricciones
				necesaria2=necesaria;
				basta=false;
			}
			if (j==1) continue;
			//Si puedo poner todas esas piezas en vertical
			if (m_Piezas[i].largo<=Rect.Width() && m_Piezas[i].ancho*j<=Rect.Height())
			{
				if (val>max) max=val;
				suma+=val;
				numero=j;
				candi c={j,i,'V'};
				std::pair<double, candi > p(val,c);
				lista_candidatos.push_back(p);
				//Si es necesaria meterla por las restricciones
				necesaria2=necesaria;
				basta=false;
			}
			//Si j es par y es mayyor que 2
			//Puedo meterlas de otras manera por ejemplo
			//en un 2x2 o 3X2 etc..
			if (j>2 && j%2==0 && basta!=false) 
			{
				//
				int alto=Rect.Height()/m_Piezas[i].ancho;
				if (alto>1) 
				{
					if ((j/alto>1) && (j/alto)<=(Rect.Width()/m_Piezas[i].largo))
					{
//						int kk=m_Piezas[i].ancho;
//						int kk2=m_Piezas[i].largo;
						if (val>max) max=val;
						suma+=val;

						numero=j;
						candi c={j,i,'A'};
						std::pair<double, candi > p(val,c);
						lista_candidatos.push_back(p);
						//Si es necesaria meterla por las restricciones
						necesaria2=necesaria;
						basta=false;
					}
					
				}
			}
		}
	}
	if (lista_candidatos.size()==0) return;
	int elegido=0;
	//Elijo de los posibles con un tanto por ciento 
	if (m_tipo_de_lista==1) elegido=ElegirAleatorioPorCiento(lista_candidatos);
	//Elije de los posibles que este entre max y (1-FAleatorio)*max
	if (m_tipo_de_lista==2)  elegido=ElegirAleatorioPorValor(lista_candidatos,m_FactorAleatorio*max);
	//elige dandole probabilidad dependiendo del valr
	if (m_tipo_de_lista==3) elegido=ElegirAleatorioPorProbabilidad(lista_candidatos,suma);
	//Elijo uno del  tengo que poner lo que hago
	//tamaño cuando le paso val cuanto vale
	m_Piezas[lista_candidatos[elegido].second.nump].num+=lista_candidatos[elegido].second.numero;
	b1.SetNumero(lista_candidatos[elegido].second.nump);
	if (lista_candidatos[elegido].second.orienta=='H')
	{
		b1.right=m_Piezas[lista_candidatos[elegido].second.nump].largo*lista_candidatos[elegido].second.numero;
		b1.bottom=m_Piezas[lista_candidatos[elegido].second.nump].ancho;
	}
	if (lista_candidatos[elegido].second.orienta=='V')
	{
		b1.right=m_Piezas[lista_candidatos[elegido].second.nump].largo;
		b1.bottom=m_Piezas[lista_candidatos[elegido].second.nump].ancho*lista_candidatos[elegido].second.numero;
	}
	if (lista_candidatos[elegido].second.orienta=='A')
	{
//		int kk=m_Piezas[lista_candidatos[elegido].second.nump].ancho;
//		int kk2=m_Piezas[lista_candidatos[elegido].second.nump].largo;
		int alto=Rect.Height()/m_Piezas[lista_candidatos[elegido].second.nump].ancho;
		int ancho=lista_candidatos[elegido].second.numero/alto;
		b1.right=m_Piezas[lista_candidatos[elegido].second.nump].largo*ancho;
		b1.bottom=m_Piezas[lista_candidatos[elegido].second.nump].ancho*alto;
//		lista_candidatos[elegido].second.numero
	}

}