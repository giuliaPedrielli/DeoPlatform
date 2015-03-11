// gpSYSDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gpSYSDLL.h"


// This is an example of an exported variable
GPSYSDLL_API int ngpSYSDLL=0;
namespace productionSystem{
// This is an example of an exported function.
GPSYSDLL_API int fngpSYSDLL(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see gpSYSDLL.h for the class definition
gpWorkstation::gpWorkstation()
{
	this->DistribDef = false;
}
gpWorkstation::gpWorkstation(productionSystem::gpWorkstation *Wcopy)
{
	this->IdMach=Wcopy->IdMach;
	if(Wcopy->DistribDef==true)
		this->pDistribution = new stochasticProperty::gpDistribution(Wcopy->pDistribution);
	else
		this->pDistribution = new stochasticProperty::gpDistribution();
	this->DistribDef = Wcopy->DistribDef; 
	this->inputPort = Wcopy->inputPort; //NULL if the machine is the first of the line
	this->outputPort = Wcopy->outputPort;
}
gpWorkstation::gpWorkstation(const int id, const int inPort, const int outPort){
this->IdMach  = id;
this->inputPort = inPort;
this->outputPort = outPort;
this->DistribDef=false;
}

gpWorkstation::gpWorkstation(const int id, const int inPort, 
							 const int outPort,const stochasticProperty::typeDistribution dtipo,
							 const double p1,const double p2,const double p3,
							 const double p4, const double p5)
{
	this->IdMach = id;
	this->inputPort = inPort;
	this->outputPort = outPort;
	this->pDistribution = new stochasticProperty::gpDistribution(dtipo,p1,p2,p3,p4,p5);
	this->DistribDef = true;
}

gpWorkstation::~gpWorkstation()
{
	if(this->DistribDef==true) 
		delete(this->pDistribution);
}

gpBuffer::gpBuffer()
{
}

gpBuffer::gpBuffer(const int id, const int inPort, const int outPort, const int cap)
{
	this->bId = id;
	this->inputMach = inPort;
	this->outputMachine = outPort;
	this->capacity = cap;
}

gpBuffer::gpBuffer(productionSystem::gpBuffer* bCopy)
{
	this->bId = bCopy->bId;
	this->capacity = bCopy->capacity;
	this->inputMach = bCopy->inputMach;
	this->outputMachine = bCopy->outputMachine;
}

gpBuffer::~gpBuffer()
{
}

gpProcess::gpProcess()
{
}

gpProcess::~gpProcess()
{
}

gpCustomer::gpCustomer()
{
	this->arrDef=false;
}
gpCustomer::gpCustomer(const stochasticProperty::typeDistribution dtipo,
					   const double p1,const double p2,const double p3,
					   const double p4, const double p5)
{
	this->arr_description = new stochasticProperty::gpDistribution(dtipo,p1,p2,p3,p4,p5);
	this->arrDef=true;
}
gpCustomer::gpCustomer(productionSystem::gpCustomer* myC)
{
	if(myC->arrDef==true)
	{
		this->arr_description = new stochasticProperty::gpDistribution();

		this->arr_description->myType = myC->arr_description->myType;
		this->arr_description->m1 = myC->arr_description->m1;
		this->arr_description->m2 = myC->arr_description->m2;
		this->arr_description->m3 = myC->arr_description->m3;
		this->arr_description->m4 = myC->arr_description->m4;
		this->arr_description->m5 = myC->arr_description->m5;
	}
	else
		this->arrDef=myC->arrDef;
}
gpCustomer::~gpCustomer()
{
	if(this->arrDef==true)
		delete(this->arr_description);
}


gpProductionSystem::gpProductionSystem()
{
	this->atDistDEF = false;
	this->ptDistDEF = false;
}
gpProductionSystem::gpProductionSystem(const int numSt, const int numBuff)
{	
	this->J=numSt;
	int sizeref(0);
	sizeref = numSt;
	this->psMachines.resize(sizeref);
	this->psBuff.resize(numBuff);
	this->atDistDEF = false;
	this->ptDistDEF = false;
	this->seTSysType();
}
gpProductionSystem::gpProductionSystem(gpProductionSystem* sysCopy)
{
	this->J=sysCopy->J;
	this->sysType = sysCopy->sysType;
	/*this->sysTopo = sysCopy->sysTopo;*/
	int dim(0);
	dim = sysCopy->psMachines.size();
	this->psMachines.resize(dim);
	for(int i=0;i<dim;i++)
	{
		this->psMachines[i] = new productionSystem::gpWorkstation(sysCopy->psMachines[i]);
	}
	int dim2(0);
	dim2 = sysCopy->psBuff.size();
	this->psBuff.resize(dim2);
	for(int i=0;i<dim2;i++)
	{
		this->psBuff[i] = new productionSystem::gpBuffer(sysCopy->psBuff[i]);
	}
	dim2 = sysCopy->psBaseStock.size();//->psBuff.size();
	this->psBaseStock.resize(dim2);
	for(int i=0;i<dim2;i++)
	{
		this->psBaseStock[i] = new productionSystem::gpBuffer(sysCopy->psBaseStock[i]);
	}
	dim2 = sysCopy->psKanban.size();//->psBuff.size();
	this->psKanban.resize(dim2);
	for(int i=0;i<dim2;i++)
	{
		this->psKanban[i] = new productionSystem::gpBuffer(sysCopy->psKanban[i]);
	}
	
	this->mycustomer = new productionSystem::gpCustomer(sysCopy->mycustomer);
	/*this->seTSysType();*/
}

gpProductionSystem::gpProductionSystem(std::vector<productionSystem::gpWorkstation*> myW,
									   std::vector<productionSystem::gpBuffer*> myB,
									   productionSystem::gpCustomer* myC,v2 TB_in)
{
	this->J = myW.size();
	if(myC->arrDef==true)
	{
		this->mycustomer = new gpCustomer(myC);
		this->atDistDEF = true;

	}
	else
	{
		this->mycustomer = new gpCustomer();
		this->atDistDEF = false;
	}
	this->psBuff.resize(myB.size());
	int myBsize(0);
	myBsize = myB.size();
	for(int i=0;i < myBsize;i++)
	{
		this->psBuff[i]= new productionSystem::gpBuffer(myB[i]);
	}

	this->psMachines.resize(myW.size());
	int myWsize(0);
	myWsize = myW.size();
	for(int i=0;i < myWsize;i++)
	{
		if(myW[i]->DistribDef==true)
		{
			this->psMachines[i]=new gpWorkstation(myW[i]);
				/*(myW[i]->IdMach,myW[i]->inputPort,
				myW[i]->outputPort,myW[i]->pDistribution->myType,myW[i]->pDistribution->m1,
				myW[i]->pDistribution->m2,myW[i]->pDistribution->m3,myW[i]->pDistribution->m4,
				myW[i]->pDistribution->m5);*/
			this->ptDistDEF = true;
		}
		else
		{
			this->psMachines[i]=new gpWorkstation(myW[i]);
			/*this->psMachines[i]=new gpWorkstation(myW[i]->IdMach,myW[i]->inputPort,
				myW[i]->outputPort);*/
			this->ptDistDEF = false;
		}
	}
	this->seTSysType();
	if(TB_cap.size()>0)
	{
		this->TB_cap.resize(TB_in.size());
		
		if(this->sysType==CLOSEDLOOP)
		{
			int TB_insize(0);
			int psBuffsize(0);
			TB_insize = TB_in.size();
			for(int k=0;k < TB_insize;k++)
			{
				this->TB_cap[k].resize(1);
				psBuffsize = this->psBuff.size();
				for(int j=0;j < psBuffsize;j++)
				{
					this->TB_cap[k][0] = TB_in[k][0];
				}
			}
		}
		else
		{
			int TB_capsize(0);
			TB_capsize = TB_in.size();
			for(int k=0;k < TB_capsize;k++)
			{
				this->TB_cap[k].resize(this->psBuff.size());
				TB_capsize = this->psBuff.size();
				for(int j=0;j < TB_capsize;j++)
				{
					this->TB_cap[k][j] = TB_in[k][j];
				}
			}
		}
	}
}

void gpProductionSystem::copyProductionSystem(productionSystem::gpProductionSystem* sysCopy)
{
	this->J=sysCopy->J;
	this->sysType = sysCopy->sysType;
	/*this->sysTopo = sysCopy->sysTopo;*/
	int dim(0);
	dim = sysCopy->psMachines.size();
	this->psMachines.resize(dim);
	for(int i=0;i<dim;i++)
	{
		this->psMachines[i] = new productionSystem::gpWorkstation(sysCopy->psMachines[i]);
	}
	int dim2(0);
	dim2 = sysCopy->psBuff.size();
	this->psBuff.resize(dim2);
	for(int i=0;i<dim2;i++)
	{
		this->psBuff[i] = new productionSystem::gpBuffer(sysCopy->psBuff[i]);
	}
	dim2 = sysCopy->psBaseStock.size();//->psBuff.size();
	this->psBaseStock.resize(dim2);
	for(int i=0;i<dim2;i++)
	{
		this->psBaseStock[i] = new productionSystem::gpBuffer(sysCopy->psBaseStock[i]);
	}
	dim2 = sysCopy->psKanban.size();//->psBuff.size();
	this->psKanban.resize(dim2);
	for(int i=0;i<dim2;i++)
	{
		this->psKanban[i] = new productionSystem::gpBuffer(sysCopy->psKanban[i]);
	}
	this->mycustomer = new productionSystem::gpCustomer(sysCopy->mycustomer);
	this->seTSysType();
}
void gpProductionSystem::seTSysType(void)
{
	if(this->psMachines.size() == this->psBuff.size())
		this->sysType = CLOSEDLOOP;
	else
	{
		this->sysType = FLOWLINE;
	}
}

void gpProductionSystem::gpDeleteElements()
{
	for(int i=0;i<this->J;i++)
		{
			delete(this->psMachines[i]);
		}
		this->psMachines.clear();
		int dimBuff(0);
		dimBuff = this->psBuff.size();
		for(int i=0;i<dimBuff;i++)
			delete(this->psBuff[i]);
		this->psBuff.clear();
	delete(this->mycustomer);
	gpProductionSystem::~gpProductionSystem();
}
gpProductionSystem::~gpProductionSystem()
{
	
}
}
