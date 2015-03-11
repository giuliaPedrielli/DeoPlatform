// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GPSYSDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GPSYSDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifndef GPPRODUCTION_SYSTEM__HH
#define GPPRODUCTION_SYSTEM__HH

#ifdef GPSYSDLL_EXPORTS
#define GPSYSDLL_API __declspec(dllexport)
#else
#define GPSYSDLL_API __declspec(dllimport)
#endif

#include "gpProbabilityDLL.h"
enum SYSTYPE{
FLOWLINE,
CLOSEDLOOP,
ASSEMBLY,
DISASSEMBLY,
MERGE,
SPLIT,
SUPPLYCHAIN,
};
enum STATE
{
IDLE,
BUSY,
};
typedef enum SYSTYPE typeSys;
template class GPSYSDLL_API std::allocator<double>;
template class GPSYSDLL_API std::vector<double>;
namespace productionSystem{
using namespace stochasticProperty;
class GPSYSDLL_API gpProcess{
public:
	gpProcess();
	friend class gpWprkstation;
	friend class gpProductionSystem;
	~gpProcess();
};

class GPSYSDLL_API gpWorkstation{
public:
	
	int IdMach;
	stochasticProperty::gpDistribution* pDistribution;//stochastic information	
	bool DistribDef; 
	int inputPort; //NULL if the machine is the first of the line
	int outputPort; //NULL if the machine is the exit point

	double avBlockingTime;
	double MaxBlockTime;
	double avSTarvationTime;
	double maxStarvationTime;
	STATE machState;

public:
	gpWorkstation();
	//costruttore di copia
	gpWorkstation(gpWorkstation *);
	gpWorkstation(const int ,const int ,const int );
	gpWorkstation(const int a, const int b,const int c, typeDistribution dtipo,
		const double p1,const double p2=0.0,const double p3=0.0,
		const double p4=0.0, const double p5=0.0);

	~gpWorkstation();
};

class GPSYSDLL_API gpBuffer{
	public:
	int inputMach; //NULL if it is the first element of the system
	int outputMachine; //NULL if it is the last element of the system
	int bId;

	int capacity;
	int level;

	double AvNumCutomers;
	double AvWaitingTime;
	int MaxNumCutomers;
	int MaxWtime;
	int MinNumCustomers;
	int MinWtime;
	double VarNumCust;
	double VarWtime;

public:
	gpBuffer();
	gpBuffer(const int, const int, const int,const int);
	gpBuffer(gpBuffer *);
	~gpBuffer();
};

class GPSYSDLL_API gpCustomer{
public:

	typedef stochasticProperty::gpDistribution* atDistr; //distribution describing the arrival time of customers
	stochasticProperty::gpDistribution* arr_description;
	bool arrDef;
	gpCustomer();
	//costruttore di copia
	gpCustomer(gpCustomer* );
	gpCustomer(const stochasticProperty::typeDistribution dtipo,
		const double p1,const double p2=0.0,const double p3=0.0,
		const double p4=0.0, const double p5=0.0);
	/*gpProcess pProc;*/
	~gpCustomer();
};
// This class is exported from the gpSYSDLL.dll
//GPSYSDLL_API typedef std::vector<std::vector<double> > psTopology;
GPSYSDLL_API typedef std::vector<std::vector<double> > v2;
GPSYSDLL_API typedef std::vector<double> v1;

template class GPSYSDLL_API std::allocator<productionSystem::gpWorkstation*>;
template class GPSYSDLL_API std::vector<productionSystem::gpWorkstation*>;
template class GPSYSDLL_API std::allocator<productionSystem::gpBuffer*>;
template class GPSYSDLL_API std::vector<productionSystem::gpBuffer*>;
//template class GPSYSDLL_API std::allocator<std::allocator<double> >;

//template class GPSYSDLL_API std::vector<std::vector<double> >;
//GPSYSDLL_API std::vector<productionSystem::gpBuffer*> psBuff;
//GPSYSDLL_API std::vector<std::vector<double> > TB_cap;

class GPSYSDLL_API gpProductionSystem {
public:

	int J;//number of workstations
	typeSys sysType;
	/*psTopology sysTopo;*/
	std::vector<productionSystem::gpWorkstation*> psMachines;
	std::vector<productionSystem::gpBuffer*> psBuff;
	std::vector<productionSystem::gpBuffer*> psKanban;
	std::vector<productionSystem::gpBuffer*> psBaseStock;
	//std::vector<std::vector<double> > TB_cap; //in case of approximate simulation
	v2 TB_cap;
	gpCustomer* mycustomer;

	gpProductionSystem();
	//costruttore di copia
	gpProductionSystem(productionSystem::gpProductionSystem *sysCopy);
	gpProductionSystem(const int , const int );
	gpProductionSystem(std::vector<productionSystem::gpWorkstation*> ws,std::vector<productionSystem::gpBuffer*> sb,
		productionSystem::gpCustomer* cs,v2 TB_in=v2());
	//come un costruttore di copia ma non alloca memoria all'oggetto
	//in quanto l'oggetto è stato già istanziato
	void copyProductionSystem(productionSystem::gpProductionSystem *sysCopy);
	bool ptDistDEF;
	bool atDistDEF;
	
	/*void setTopology(void);*/
	void seTSysType(void);
	
	void gpDeleteElements();
	~gpProductionSystem();


};

extern GPSYSDLL_API int ngpSYSDLL;

GPSYSDLL_API int fngpSYSDLL(void);
}
#endif