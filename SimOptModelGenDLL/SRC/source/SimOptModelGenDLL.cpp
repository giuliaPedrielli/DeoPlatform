// SimOptModelGenDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SimOptModelGenDLL.h"
#include <gpProbabilityDLL.h>
#include <fstream>

namespace SIMOPTGEN{
using namespace std;
using namespace OptimizationModel;
using namespace productionSystem;
using namespace stochasticProperty;
#define __PARAM_MAX 5

// This is an example of an exported variable
SIMOPTMODELGENDLL_API int nSimOptModelGenDLL=0;

// This is an example of an exported function.
SIMOPTMODELGENDLL_API int fnSimOptModelGenDLL(void)
{
	return 42;
}
SIMOPTMODELGENDLL_API std::vector<double> vectorSort(std::vector<double> vec,int a, int b)
{
	cout << "SONO IN VECTOR SORT! " << endl;
	/*int i(a+1);
	int j(b-1);
	bool sorted = false;
	while(sorted==false)
	{
		int k=i;
		while(i<=j)
		{
			while(vec[j]>vec[a])
				j--;
			while(vec[k]<= vec[a] && i<=j)
			{
				i++;
				if(i<=j)
					k++;
			}
			if(i<j)
			{
				double temp=vec[i];
				double temp1=vec[j];
				vec[i]=temp1;
				vec[j]=temp;
				i++;
				j--;
			}
			else if(vec[a]>vec[j])
			{
				double temp=vec[a];
				double temp1=vec[j];
				vec[a]=temp1;
				vec[j]=temp;
			}
			else
			{
				sorted = true;
			}
		}
		i=a+1;
		j=b-1;
	} */

	int i,j;
	double temp;
	for(i=vec.size()-1;i>0;i--)
	{
		for(j=1;j<=i;j++)
		{
			if(vec[j-1] > vec[j])
			{
				temp = vec[j-1];
				vec[j-1] = vec[j];
				vec[j] = temp;
			}
		}
	}
	//cout << "HO ORDINATO IL VETTORE di dimensione" << vec.size() << endl;
	/*getchar();*/
	/*for(int l=0;l<vec.size();l++)
	{
		cout << vec[l] << endl;
	}*/
	return vec;
	/*getchar();*/
}
SIMOPTMODELGENDLL_API OptimizationModel::App_OpModel* createOptimizationModel(std::ifstream & in_dimensions, 
						  productionSystem::gpProductionSystem* Sys/*,
						  std::ifstream & in_processTime, std::ifstream & in_arrivalTime*/)
{
	string str;
	
	int i;

	double I;		//  # parts
	/*double J;*/		//  # machines
	double d;		//  # warmup
	double K_max;		//  # MaxCapacityRange
	double p_max;	//	# MaxPallet
	/*bool pType;*/ // type of problem: 0- buffer allocation, 1- Pallet Allocation
	double rt(0); //requested time
	double sr(0); //service rate this is an input parameter
	int ObjFuncType(0); //Asks for the type of objective function
	int R(0);//number of replicates
	int AlgType(0); //0-multiple replicates 1-increase sample path length
	double tolerance(0.0); //Tolerance makes sense iff AlgType is 2
	int pInit(0);//Initial number of customers
	int modelType(0); //for BAP (now) if (0) the constraints are defined over all k=1,...,K
					  //the objective function is defined for k=c[j] on
					//if equal to (1) both constraints and obj funct are defined starting from c[j]
					//if equal to (2) constraints are defined starting form c[j] but the objective function is for all k
					//if equal to (3) both constraints and objective function start from k=1 (normal version)
	double delta_feasibility(0.0);
	double alpha(0.0);
	int toChange; //if equal to 0 change nothing if 1 the processing times if 2 the target
	double step; //the step at which you change
	int iterations; //number of iterations varying the processing time and stuff

	int at_distribution(0);
	double at_p1,at_p2,at_p3,at_p4,at_p5;
	int systemType(0); //0 if the system of interest is a manufacturing system
					   //1) if the system of interest is a supply chain


	try
	{
		if(!in_dimensions)
			cout<<"Non leggo il file"<<endl;
		else
		{
			in_dimensions>>str;
			in_dimensions>>I;
			/*in_dimensions>>str;
			in_dimensions>>J;*/
			in_dimensions>>str;
			in_dimensions>>d;
			in_dimensions>>str;
			in_dimensions>>K_max;
			in_dimensions>>str;
			in_dimensions>>p_max;
			/*in_dimensions>>str;
			in_dimensions>>pType;*/
			in_dimensions>>str;
			in_dimensions>>sr;
			in_dimensions>>str;
			in_dimensions>>ObjFuncType; // 0 if minimize s and 1 if minimize b
			in_dimensions>>str;
			in_dimensions>>R;
			in_dimensions>>str;
			in_dimensions>>AlgType;
			in_dimensions>>str;
			in_dimensions>>tolerance;
			in_dimensions>>str;
			in_dimensions>>pInit;
			in_dimensions>>str;
			in_dimensions>>modelType;
			in_dimensions>>str;
			in_dimensions>>delta_feasibility;
			in_dimensions>>str;
			in_dimensions>>alpha;
			in_dimensions>>str;
			in_dimensions>>toChange;
			in_dimensions>>str;
			in_dimensions>>step;
			in_dimensions>>str;
			in_dimensions>>iterations;

			///CUSTOMERS DATA
			in_dimensions >> str; 
			in_dimensions >> at_distribution;
			in_dimensions >> str;
			in_dimensions >> at_p1;
			in_dimensions >> str;
			in_dimensions >> at_p2;
			in_dimensions >> str;
			in_dimensions >> at_p3;
			in_dimensions >> str;
			in_dimensions >> at_p4;
			in_dimensions >> str;
			in_dimensions >> at_p5;

			cout<<"I "<< I<<endl;
			/*cout<<"J "<< J<<endl;*/
			cout<<"d "<< d<<endl;
			cout<<"MaxCapacityRange "<< K_max<<endl;
			/*cout<<"Problem Type: "<< pType <<endl;*/
			cout <<"Requested Time: " << rt << endl;
			cout << "Objective function type: " << ObjFuncType << endl;
			cout << "Number of Replications: "<< R << endl;
			cout << "Type of Algorithm: " << endl;
			cout << "0) multiple replicates" << endl;
			cout << "1) increase SP length" << endl;
			cout << "2) Adaptive with stop condition: " << endl;
			cout << "Value you chose: " << AlgType << endl;
			cout << "Initial -lower bound- number of customers in the system: " << pInit << endl;
			cout << "Type of model: " << modelType << endl;
			cout << "Coefficient in feasibility: " << delta_feasibility << endl;
			cout << "Coefficient alpha for SL: " << alpha << endl;
			cout << "Value for To change: " << toChange << endl;
			cout << "Step you choose: " << step << endl;
			cout << "Number of iterations to perform: " << iterations << endl;
			cout << "Customers arrival distribution: " << at_distribution << endl;
			cout << "p1: " << at_p1 << endl;
			cout << "p2: " << at_p2 << endl;
			cout << "p3: " << at_p3 << endl;
			cout << "p4: " << at_p4 << endl;
			cout << "p5: " << at_p5 << endl;
			in_dimensions >> str;
			in_dimensions >> systemType; //0 if manufacturing 1 if supplychain
			cout << "Category of system: (0) if manufacturing system, (1) if supply chain: " << systemType << endl;
			
		}

		
		std::vector<double> at;
		std::vector<std::vector<double> > pt;
		
		if(at_distribution==3)
		{
			Sys->atDistDEF=false;		
		}
		else
		{
			cout << "Distribution defined for arrivals" << endl;
			/*getchar();*/
			Sys->mycustomer->arrDef = true;
			Sys->atDistDEF = true;
			
			if(at_distribution==0)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::EXPO,at_p1);
			else if(at_distribution==1)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::UNIFORM,at_p1,at_p2);
			else if(at_distribution==2)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::NORMAL,at_p1,at_p2);
			else if(at_distribution==3)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::COSTANT,0.0);
			else if(at_distribution==4)
			{
				cout << "Constant time has been defined by the user " << endl;
					Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::COSTANT,at_p1);
			}
			else if(at_distribution==5)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::TRIANGULAR,at_p1,at_p2,at_p3);
			else if(at_distribution==6)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::LOGNORMAL,at_p1,at_p2);
			else if(at_distribution==7)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::WEIBULL,at_p1,at_p2);
			else if(at_distribution==8)
				Sys->mycustomer->arr_description = new stochasticProperty::gpDistribution(stochasticProperty::GAMMA,at_p1,at_p2);

			else throw "Didn't receive legal argument for arrivals";

			at.resize((int)(I));
			
			at[0]=0.0;
			for(i=1;i<at.size();i++)
				at[i]=at[i-1]+at[i];
		}			
		
		if((Sys->psMachines[0]->DistribDef!=false))
		{
		
			cout << "Generating porcessing times from the specified distribution" << endl;
			int psMachSize(0);
			psMachSize = Sys->psMachines.size();
			Sys->ptDistDEF = true;
			pt.resize(int(I));
			for(size_t k=0;k<int(I);k++)
				pt[k].resize(psMachSize);
			if(Sys->sysType == CLOSEDLOOP)
			{
				for(int i=0;i<int(I);i++)
				{
					pt[i].resize(psMachSize+1);
					pt[i][psMachSize]=0.0;
				}
			}
		}

		if(pt.size()>0)
			cout<<"Process Times Generated" << endl;
		if(at.size()>0)
			cout <<"Arrival Times generated" << endl;
		cout << "SONO NELLA NUOVA LIB" << endl;
		
		cout << "Input arrivals are stochastic: " << Sys->mycustomer->arrDef << endl;
		
		OptimizationModel::App_OpModel* myMod = new OptimizationModel::App_OpModel(Sys,sr,int(I),int(d),pt,at);
		
		if(Sys->mycustomer->arrDef==true)
		{
			cout << "Sys customer distribution: " << Sys->mycustomer->arr_description->myType << endl;
			myMod->_GPmys->mycustomer = new productionSystem::gpCustomer(Sys->mycustomer);
			myMod->_GPmys->mycustomer->arrDef=true;
		}
		if(myMod->_GPmys->mycustomer->arrDef==true)
			cout << "Distribution of Arrivals: " << myMod->_GPmys->mycustomer->arr_description->myType << endl;
		else
			cout << "No distribution defined for arrivals" << endl;

		
		myMod->mycap.resize(Sys->psBuff.size());		

		cout << "Default Model Generated!" << endl;

		myMod->delta_feasibility = delta_feasibility;
		myMod->alpha = alpha;
		myMod->I = int(I);

		myMod->d = int(d);

		myMod->replications  = R;

		if(systemType==1)
		{
			myMod->_GPmys->sysType=SUPPLYCHAIN;
			myMod->_optObj=SIM_EXTENDED_KANBAN;
			cout << "Performing the optimziation of a supply chain" << endl;
		}		
		if(myMod->_GPmys->sysType == CLOSEDLOOP)
		{
			myMod->_GPmys->psBuff[myMod->_GPmys->psBuff.size()-1]->capacity = 
			myMod->_GPmys->psBuff[myMod->_GPmys->psBuff.size()-1]->capacity - 1;
		}
		else
		{
			cout << "The Model is a flow Line " << endl;
		}
		in_dimensions >> str; //want to simply simulate the system?
		int mod_type(0);
		in_dimensions >> mod_type;
		if(mod_type == 1)
			myMod->_optObj = SIM_KANBAN;
		else if(mod_type ==2)
			myMod->_optObj = SIM_BASESTOCK;
		else if(mod_type == 3)
			myMod->_optObj = SIM_EXTENDED_KANBAN;
		else if(mod_type == 4)
			myMod->_optObj = SIMULATION;
		else if(mod_type==5)
			myMod->_optObj=EXACT_SIM_KBS;
		else if(mod_type==6)
			myMod->_optObj=KANBAN;
		else if(mod_type==7)
			myMod->_optObj=BASESTOCK;
		else if(mod_type==8)
			myMod->_optObj=EXACT_SIM;
		else if(mod_type==9)
			myMod->_optObj=EXACT_SIM_KCS;
		else if(mod_type==10)
			myMod->_optObj=EXACT_SIM_BS;
		else if(mod_type==11)
			myMod->_optObj=EXACT_OPT_BSC;
		else if(mod_type==12)
			myMod->_optObj=EXACT_OPT_KSC;
		else if(mod_type==13)
			myMod->_optObj=EXACT_OPT_EKCS;
		else if(mod_type==14)
			myMod->_optObj=EXTENDED_KANBAN;
		else if(mod_type==15)
			myMod->_optObj=EXACT_OPT;
		else if(mod_type==16)
			myMod->_optObj=APP_SIM_TBCS;
		else if(mod_type==17)
			myMod->_optObj=APP_OPT_TBCS;
				
		in_dimensions >> str; 
		in_dimensions >> mod_type;
		if(mod_type==0)
			myMod->_deoScope=ONLYSIMULATION;
		else if(mod_type==1)
		{
			myMod->_deoScope=ONLYOPTIMIZATION;
		}
		else if(mod_type==2)
		{
			myMod->_deoScope=SIMOPT;
		}
		else if(mod_type==3)
		{
			myMod->_deoScope=DOE_SIMOPT;
		}
		else if(mod_type==4)
		{
			myMod->_deoScope=EXP_SIMOPT;
		}

		if(ObjFuncType==0)
			myMod->_myOFtype = MIN_s;
		else if(ObjFuncType==2)
			myMod->_myOFtype = MIN_WT;
		else if(ObjFuncType==3)
			myMod->_myOFtype = MIN_TT;
		else if(ObjFuncType==4)
			myMod->_myOFtype = MIN_ML;
		else
			myMod->_myOFtype = MIN_b;
		if(ObjFuncType==0)
		{
			cout << "The OF type selected by the user is to minimize s " << endl;
		}
		else if(myMod->_myOFtype == MIN_WT)
			cout << "The OF type selected by the user is to minimize the average waiting times " << endl;
		else
		{
			if(Sys->sysType == FLOWLINE && myMod->_optObj!=EXTENDED_KANBAN && myMod->_optObj!=KANBAN && myMod->_optObj!=BASESTOCK)
				throw "The minimization of b is not allowed in case of flow line";
			else
				cout << "The OF type selected by the user is to minimize b" << endl;
		}
	
		if(AlgType==0)
			myMod->myAlg = PARrep;
		else if(AlgType==1)
			myMod->myAlg = INCsp;
		else if(AlgType==2)
			myMod->myAlg = INCspwTOL;
		if(modelType==0)
		{
			myMod->mymodType=REDUCED_OF;
		}
		if(modelType==1)
		{
			myMod->mymodType=REDUCED_FULL;
		}
		if(modelType==2)
		{
			myMod->mymodType=REDUCED_CONSTR;
		}
		if(modelType==3)
		{
			myMod->mymodType=FULL;
		}

		if(iterations>0)
		{
			myMod->myItern = iterations;
		}
		if(step>0)
		{
			myMod->myStep = step;
		}
		if(toChange==1)
		{
			myMod->_rhsChange = CHANGE_T;
		}
		else if(toChange==3)
		{
			myMod->_rhsChange = CHANGE_N;
		}
		if(Sys->sysType==CLOSEDLOOP)
		{
			int myCapSize(0);
			myCapSize = myMod->mycap.size();
			for(i=0;i<myCapSize;i++)
			{
				myMod->mycap[i]=myMod->_GPmys->psBuff[i]->capacity;
			}
		}
		if((myMod->_GPmys->sysType==FLOWLINE || myMod->_GPmys->sysType==SUPPLYCHAIN) && (K_max>0))
		{
			int myCapSize(0);
			myCapSize = myMod->mycap.size();
			for(i=0;i<myCapSize;i++)
			{
				myMod->mycap[i]=int(K_max);
			}
		}
		else if((Sys->sysType==CLOSEDLOOP) && (p_max>0) && (p_max < myMod->myPal))
			myMod->myPal = int(p_max);

		//OPTIMALITY CUTS
		in_dimensions >> str;
		int OCut;
		in_dimensions >> OCut;
		if(OCut>0)
			myMod->optCUTS=true;
		else
			myMod->optCUTS=false;
		myMod->boundWTval = 0.0;

		//TIME BUFFER CUTS
		in_dimensions >> str;
		int TBCut;
		in_dimensions >> TBCut;
		if(TBCut>0)
			myMod->tbCUTS=true;
		else
			myMod->tbCUTS=false;

		//SEQUENTIAL MODEL
		in_dimensions >> str;
		int SeqMod;
		in_dimensions >> SeqMod;
		if(SeqMod>0)
			myMod->SeqModel=true;
		else
			myMod->SeqModel=false;
		
		//WAITING TIME CUTS
		in_dimensions >> str;
		int WtCuts;
		in_dimensions >> WtCuts;
		if(WtCuts>0)
			myMod->WT_cuts=true;
		else
			myMod->WT_cuts=false;

		Sys->gpDeleteElements();
		free(Sys);

		

		cout << "MODEL SUCCESSFULLY GENERATED " << endl;

		if(myMod->_GPmys->psMachines[0]->DistribDef==true)
			cout << "Distribution of pt: " << myMod->_GPmys->psMachines[0]->pDistribution->myType << endl;
		else
			cout << "No distribution defined for arrivals" << endl;

		if(myMod->_GPmys->mycustomer->arrDef==true)
		{
			cout << "Distribution of Arrivals: " << myMod->_GPmys->mycustomer->arr_description->myType << endl;
			cout << "Value of the first Parameter: " << myMod->_GPmys->mycustomer->arr_description->m1 << endl;
		}
		else
			cout << "No distribution defined for arrivals" << endl;

		//typeSampling myinALGO;
		in_dimensions >> str;
		int myAlgoSample(0);
		in_dimensions >> myAlgoSample;
		if(myAlgoSample==0)
			myMod->mySampleAlgo=MONTECARLO;
		else if(myAlgoSample==1)
			myMod->mySampleAlgo=LATINHYPERCUBE;
		else
			myMod->mySampleAlgo=DESCRIPTIVESAMPLING;
		in_dimensions >> str;
		double alphaLexicographic(0.0);
		in_dimensions >> alphaLexicographic;
		myMod->alphaLessi=alphaLexicographic;
		double cost(0.0);
		in_dimensions >> str;
		in_dimensions >> cost;
		if(cost>0)
		{
			if(myMod->_GPmys->sysType==SUPPLYCHAIN)
			{
				for(int i=0;i<myMod->_GPmys->psMachines.size();i++)
				{
					in_dimensions >> str;
					in_dimensions >> cost;
					myMod->cost_stage.push_back(cost);
				}
			}
			else
			{
				for(int i=0;i<myMod->_GPmys->psMachines.size()-1;i++)
				{
					in_dimensions >> str;
					in_dimensions >> cost;
					myMod->cost_stage.push_back(cost);
				}
			}
		}

		double boundS(0.0);
		in_dimensions >> str;
		in_dimensions >> myMod->boundS;
		myMod->contRowFirstTBconst=0;
		myMod->contRowLastTBconst=0;
		in_dimensions >> str;
		in_dimensions >> myMod->makeSA;
		in_dimensions >> str;
		in_dimensions >> myMod->makesimNatwithCosts;
		return myMod;
		
	}
	catch(char* str)
	{
			cout<<"  Couldn't create the optimization model "<< str <<endl;
	}
}
SIMOPTMODELGENDLL_API void createSystem(productionSystem::gpProductionSystem* Sys, std::ifstream & in_mach,
				  std::ifstream & in_buff)
{
	try
	{
		cout << "CREATING SYSTEM" << endl;
		std::vector<productionSystem::gpWorkstation*> myWset;
		std::vector<productionSystem::gpBuffer*> myBset;
		std::vector<productionSystem::gpBuffer*> myBSset;
		std::vector<productionSystem::gpBuffer*> myKset;
		productionSystem::gpCustomer* myCustomer = new productionSystem::gpCustomer();
		bool stochasticPT=false;
		bool stochasticAT = false;
		/*cout << "SONO ENTRATO" << endl;*/

		if(!in_mach)
		{
			throw "Cannot read machines file";
		}
		else
		{			
			int j(0);
			while(!in_mach.eof())
			{
				myWset.resize(j+1);
				int id(0);
				int prec(0);
				int succ(0);
				int num_par(0);

				in_mach >> id;
				in_mach >> prec;
				in_mach >> succ;
				in_mach >> num_par;

				productionSystem::gpWorkstation* myW = 
					new productionSystem::gpWorkstation(id,prec,succ);

				cout << "Workstation number: " << id << " succeffully created" << endl;

				if(num_par>0)
				{
					stochasticPT = true;
					cout << "Numbr of Parameters: " << num_par << endl;
					int disType(0);
					in_mach >> disType;
					cout << "Distribution Type: " << disType << endl;
					double par1(0);
					double par2(0);
					double par3(0);
					double par4(0);
					double par5(0);
					std::vector<double> allPar;//(__PARAM_MAX);
					allPar.resize(__PARAM_MAX);
					

					for(int indPar=0;indPar<__PARAM_MAX;indPar++)
					{
						allPar.push_back(0.0);	
					}

					//cout << "Number of parameters: " << allPar.size() << endl;

					for(int indPar=0;indPar<num_par;indPar++)
					{
						in_mach >> allPar[indPar];						
					}
					par1=allPar[0];
					cout << "par1: " << par1 << endl;
					par2=allPar[1];
					cout << "par2: " << par2 << endl;
					par3=allPar[2];
					cout << "par3: " << par3 << endl;
					par4=allPar[3];
					cout << "par4: " << par4 << endl;
					par5=allPar[4];
					cout << "par5: " << par5 << endl;

					myW->DistribDef=true;
					switch(disType)
					{
					case 0: 
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::EXPO,par1);
						break;
					case 1:
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::UNIFORM,par1,par2);
						break;
					case 2:
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::NORMAL,par1,par2);
						break;
					case 3:
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::COSTANT,par1);
					case 4:
						cout << "Constant time has been defined by the user " << endl;
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::COSTANT,par1);
						break;
					case 5:
						cout << "Triangular time has been defined by the user " << endl;
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::TRIANGULAR,par1,par2,par3);
						break;
					case 6:
						cout << "LogNormal time has been defined by the user " << endl;
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::LOGNORMAL,par1,par2);
						break;
					case 7:
						cout << "Weibull time has been defined by the user " << endl;
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::WEIBULL,par1,par2);
						break;
					case 8:
						cout << "Gamma time has been defined by the user " << endl;
						myW->pDistribution = new stochasticProperty::gpDistribution(stochasticProperty::GAMMA,par1,par2);
						break;
					default: std::cout << "Didn't receive legal argument" << std::endl;

					}

					cout << "probability distribution defined for machine: " << id << endl;
				}
				else
					myW->DistribDef=false;
				
				myWset[j] = new productionSystem::gpWorkstation(myW);
				cout << "Workstation added to the system" << endl;
				if(!in_mach.eof())
					j++;
				delete(myW);
				/*getchar();*/
			}
		}
		if(!in_buff)
		{
			throw "Cannot read buffers file";
		}
		else
		{
			int j=0;
			int temp(0);
			int numBuff(0);
			
			while(!in_buff.eof())
			{
				in_buff >> temp;
				if(temp>0){
				/*in_buff >> myBset[j]->bId;*/
					myBset.resize(j+1);
					myBset[j] = new productionSystem::gpBuffer();
					myBset[j]->bId=temp;
					in_buff >> myBset[j]->inputMach;
					in_buff >> myBset[j]->outputMachine;
					in_buff >> myBset[j]->capacity;
					numBuff++;
				}
				else
				{
					//start reading basestock
					j=0;
					while(j<numBuff)
					{
						in_buff >> temp;
						myBSset.resize(j+1);
						myBSset[j] = new productionSystem::gpBuffer();
						myBSset[j]->capacity=temp;
						j++;
					}
					j=0;
					while(j<numBuff)
					{
						in_buff >> temp;
						myKset.resize(j+1);
						myKset[j] = new productionSystem::gpBuffer();
						myKset[j]->capacity=temp;
						j++;
					}
				}

				if(!in_buff.eof())
				{
					j++;
				}
			}
		}	

		productionSystem::gpProductionSystem* SysCopy = new productionSystem::gpProductionSystem(myWset,myBset,myCustomer);
		Sys->copyProductionSystem(SysCopy);
		bool isPullSystem(false);
		if(myBSset.size()>0)
		{
			for(int j=0;j<myBSset.size();j++)
			{
				Sys->psBaseStock.push_back(myBSset[j]);
				if(myBSset[j]>0)
					isPullSystem=true;
			}
		}
		if(myKset.size()>0)
		{
			for(int j=0;j<myKset.size();j++)
			{
				Sys->psKanban.push_back(myKset[j]);
				if(myKset[j]>0)
					isPullSystem=true;
			}
		}
		delete(SysCopy);

		if(isPullSystem==true)
			Sys->sysType=SUPPLYCHAIN;

		cout << "Probability Distrib Data: " << endl;
		for(size_t i=0;i<Sys->psMachines.size();i++)
		{
			cout << Sys->psMachines[i]->IdMach << endl;
		}
		for(size_t i=0;i<Sys->psMachines.size();i++)
		{
			if(Sys->psMachines[i]->DistribDef==true)
			{
				cout << "Distribution Type for station " << Sys->psMachines[i]->IdMach << " " << Sys->psMachines[i]->pDistribution->myType << endl;
			}
			else
			{
				cout << "no distrib defined for station" << " " << Sys->psMachines[i]->IdMach << endl;
			}
		}

		if(stochasticPT==true)
			Sys->ptDistDEF=true;
		
		delete(myCustomer);
		int i(0);
		int myWsetSize(0);
		myWsetSize = myWset.size();
		for(i=0;i<myWsetSize;i++)
		{
			delete(myWset[i]);
		}
		myWset.clear();
		int myBsetSize(0);
		myBsetSize = myBset.size();
		for(i=0;i<myBsetSize;i++)
		{
			delete(myBset[i]);
		}
		myBset.clear();
		
		/*Sys->seTSysType();*/
	}
	catch(char* str)
	{
			cout<<"  Couldn't create the system "<< str <<endl;
	}
}
SIMOPTMODELGENDLL_API bool GenFailures(std::ifstream & in_failFile,
											std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > & _FailureMDescr)
{
	int i(0);
	while(!in_failFile.eof())
	{
		int numfM(0);
		int idMach(0);
		in_failFile >> idMach;
		in_failFile >> numfM;
		_FailureMDescr[int(i)].clear();
		std::pair<double,stochasticProperty::gpDistribution*> tempPairfm;
		for(size_t j=0;j<numfM;j++)
		{
			std::string unitMeasure;
			in_failFile >> unitMeasure;
			double convFactor(1.0);
			if(unitMeasure == "SECONDS")
				convFactor=double(1)/double(3600);
			else if(unitMeasure == "MINUTES")
				convFactor=double(1)/double(60);
			int numParam(0);
			double p_fail(0.0);
			in_failFile >> p_fail;
			tempPairfm.first = p_fail;
			in_failFile >> numParam;
			int disType;
			in_failFile >> disType;
			double par1(convFactor);
			double par2(convFactor);
			double par3(convFactor);
			double par4(convFactor);
			double par5(convFactor);

			double tempVal(0.0);
			for(size_t k=0;k<numParam;k++)
			{
				if(k==0){
					in_failFile >> tempVal;
					par1=tempVal*convFactor;
				}
				else if(k==1){
					in_failFile >> tempVal;
					par2=tempVal*convFactor;
				}
				else if(k==2){
					in_failFile >> tempVal;
					par3=tempVal*convFactor;
				}
				else if(k==3){
					in_failFile >> tempVal;
					par4=tempVal*convFactor;
				}
				else{
					in_failFile >> tempVal;
					par5 = tempVal*convFactor;
			}
			gpDistribution* tempdistrib;
			switch(disType)
			{
				case 0: 
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::EXPO,par1);
					break;
				case 1:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::UNIFORM,par1,par2);
					break;
				case 2:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::NORMAL,par1,par2);
					break;
				case 3:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::COSTANT,par1);
				case 4:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::COSTANT,par1);
					break;
				case 5:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::TRIANGULAR,par1,par2,par3);
					break;
				case 6:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::LOGNORMAL,par1,par2);
					break;
				case 7:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::WEIBULL,par1,par2);
					break;
				case 8:
					tempdistrib = new stochasticProperty::gpDistribution(stochasticProperty::GAMMA,par1,par2);
					break;
				default: std::cout << "Didn't receive legal argument" << std::endl;

			}
				tempPairfm.second = tempdistrib;
				_FailureMDescr[int(i)].push_back(tempPairfm);
			}
		}
		i++;
	}
	return true;

}

SIMOPTMODELGENDLL_API void SolveModel(const char* & failFile,const char* & in_machf, const char* & in_bufff, 
									  const char* & in_dimensionsf,
									  const char* & out_thf, const char* & out_tbf,
									  const char* & out_boundsf,const char* & out_rep,const char* & out_fo,const char* & out_appSol,
									  const char* & in_procTfs, const char* & in_arrTimefs)
{
		std::vector<productionSystem::gpWorkstation*> myWset;
		std::vector<productionSystem::gpBuffer*> myBset;
		productionSystem::gpProductionSystem* mySystem = new productionSystem::gpProductionSystem();
		productionSystem::gpCustomer* myCustomer = new productionSystem::gpCustomer();
		std::ifstream in_dimensions(in_dimensionsf);//("INPUT/dimensions.txt");
		std::ifstream in_machines(in_machf);
		std::ifstream in_buffers(in_bufff);
		std::ifstream in_processTime(in_procTfs);
		std::ifstream in_arrivalTime(in_arrTimefs);
		std::ifstream in_failFile(failFile);

		std::ofstream out_throughput;
		std::ofstream out_tb;
		std::ofstream out_bounds;
		std::ofstream out_repReport;
		std::ofstream out_funzioneObiettivo;
		std::ofstream out_solApprossimata;

		out_funzioneObiettivo.open(out_fo);
		out_throughput.open(out_thf);
		
		out_bounds.open(out_boundsf);
		out_repReport.open(out_rep);
		out_solApprossimata.open(out_appSol);
		/*std::ofstream outpp;
		outpp.open("D:/Ph.D/gpMPRrun_32/Test/Testing/GPsimopt/OUTPUT/ppts.txt");*/
		
		createSystem(mySystem,in_machines,in_buffers);		

		OptimizationModel::App_OpModel* myModel = createOptimizationModel(in_dimensions,mySystem/*,
			in_processTime,in_arrivalTime*/);	
		
		std::cout << endl;

		std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _failDescr;
		if(GenFailures(in_failFile,_failDescr))
			cout << "Failure Modes Description has been correctly generated" << endl;
		in_failFile.close();
		cout << endl;
		if(myModel->_deoScope==SIMOPT)
		{
			out_tb.open(out_tbf);
			if(myModel->replications>0)
				myModel->SIMOPT(_failDescr,out_throughput,out_tb,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime,myModel->replications);//,rep);
			else
				myModel->SIMOPT(_failDescr,out_throughput,out_tb,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime);//,myModel->replications);//,rep);
		}
		else if(myModel->_deoScope==DOE_SIMOPT || myModel->_deoScope==EXP_SIMOPT)
		{
			out_tb.open(out_tbf);
			if(myModel->replications>0)
				myModel->DEOsimOpt(_failDescr,out_throughput,out_tb,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime,myModel->replications);//,rep);
			else
				myModel->DEOsimOpt(_failDescr,out_throughput,out_tb,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime);//,myModel->replications);//,rep);
		}
		
		else if(myModel->_deoScope==ONLYSIMULATION)
		{
			std::ifstream in_timeBuffers(out_tbf);
			myModel->SIMonly(_failDescr,out_throughput,in_timeBuffers,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime,myModel->replications);
			in_timeBuffers.close();
		}
		else if(myModel->_deoScope==ONLYOPTIMIZATION)
		{
			out_tb.open(out_tbf);
			if(myModel->replications>0)
				myModel->OPTonly(_failDescr,out_throughput,out_tb,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime,myModel->replications);
			else
				myModel->OPTonly(_failDescr,out_throughput,out_tb,out_bounds,out_repReport,out_funzioneObiettivo,
					out_solApprossimata,in_processTime,in_arrivalTime);
		}
			
		/*}*/
		out_throughput.close();
		out_tb.close();
		out_bounds.close();
		out_funzioneObiettivo.close();
		out_repReport.close();
		in_machines.close();
		in_buffers.close();
		in_processTime.close();
		in_dimensions.close();
		in_arrivalTime.close();
		
		/*std::ofstream out_seed;
		out_seed.open("D:/Ph.D/gpMPRrun_32/Test/Testing/GPsimopt/OUTPUT/SEED.txt");
		out_seed << seed << endl;
		out_seed.close();*/
		out_solApprossimata.close();
		//in_processTime.close();
		
		/*return true;*/
		
}
//SIMOPTMODELGENDLL_API void OutputStatistics(OptimizationModel::App_OpModel* myModel,std::ofstream & out_resultsFile, int rep)
//{
//	//ENTITY STATISTICS
//	out_resultsFile << "ENTITY STATISTICS" <<endl;
//	double av_systemTime(0.0);
//	double min_systemTime(0.0);
//	double max_systemTime(0.0);
//
//	double av_waitingTime(0.0);
//	double min_waitingTime(0.0);
//	double max_waitingTime(0.0);
//
//	int num_entity_processed(0);
//	int numST=myModel->_GPmys->psMachines.size();
//	double temp_y_cum(0.0);
//	double temp_y(0.0);
//	for(size_t i=0;i<myModel->I;i++)
//	{
//		temp_y = myModel->cplex.getValue(myModel->y[i][numST-1]) - myModel->cplex.getValue(myModel->y[i][0]);
//		if(max_systemTime<=temp_y)
//			max_systemTime = temp_y;
//		if((min_systemTime == 0.0) || (min_systemTime>0.0 && temp_y <= min_systemTime))
//			min_systemTime = temp_y;
//		temp_y_cum = temp_y_cum + temp_y;
//	}
//	av_systemTime = temp_y_cum/double(myModel->I);
//
//	//WRITING...
//	out_resultsFile << "		   " << "		   " << "AVERAGE" << "		   " << "MIN" << "		   " << "MAX" << endl;
//	out_resultsFile << endl;
//	out_resultsFile << "System Time" << "		   " << av_systemTime << "		   " << min_systemTime << "		   " << max_systemTime << endl;
//
//
//	temp_y = 0.0;
//	temp_y_cum = 0.0;
//	for(size_t i=0;i<myModel->I;i++)
//	{
//		for(size_t j=0;j<numST-1;j++)
//		{
//			temp_y = temp_y + myModel->cplex.getValue(myModel->y[i][j+1]) - myModel->cplex.getValue(myModel->y[i][j]);
//		}
//		if(max_waitingTime<=temp_y)
//			max_waitingTime = temp_y;
//		if((min_waitingTime == 0.0) || (min_waitingTime>0.0 && temp_y <= min_waitingTime))
//			min_waitingTime = temp_y;
//		temp_y_cum = temp_y_cum + temp_y;
//	}
//	av_waitingTime = temp_y_cum/double(myModel->I);
//
//	out_resultsFile << endl;
//	out_resultsFile << "Waiting Time" << "		   " << av_waitingTime << "		   " << min_waitingTime << "		   " << max_waitingTime << endl;
//
//	temp_y=0.0;
//	size_t k=0;
//	bool found = false;
//	while(found==false && k < myModel->I)
//	{
//		temp_y = myModel->cplex.getValue(myModel->y[k][numST-1]);
//		if(temp_y>=140)
//		{
//			found = true;
//			out_resultsFile << endl;
//			out_resultsFile << "Parts Processed" << "		   " << k << endl;
//		}
//		k++;
//	}
//}
//SIMOPTMODELGENDLL_API bool SimulationModel(const char* & in_machf, const char* & in_bufff, const char* & in_dimensionsf,
//										  const char* & out_thf, const char* & out_xf, const char* & out_yf,const char* & out_reportf,
//									  const char*  & in_procTf, const char* & in_arrTimef)
//{
//	std::vector<productionSystem::gpWorkstation*> myWset;
//	std::vector<productionSystem::gpBuffer*> myBset;
//	productionSystem::gpProductionSystem* mySystem = new productionSystem::gpProductionSystem();
//	productionSystem::gpCustomer* myCustomer = new productionSystem::gpCustomer();
//	
//	/*std::ifstream in_dim(in_dimensions.c_str());*/
//	std::ifstream in_dim(in_dimensionsf);//("INPUT/dimensions.txt");
//	std::ifstream in_machines(in_machf);
//	std::ifstream in_buffers(in_bufff);
//	std::ifstream in_processTime(in_procTf);
//	std::ifstream in_arrivalTime(in_arrTimef);
//	createSystem(mySystem,in_machines,in_buffers);
//
//	std::ofstream out_throughput;
//	std::ofstream out_x;
//	std::ofstream out_y;
//	std::ofstream out_resultsFile;
//	
//	out_throughput.open(out_thf);
//	out_x.open(out_xf);
//	out_y.open(out_yf);
//	out_resultsFile.open(out_reportf);
//	
//	OptimizationModel::App_OpModel* myModel = createOptimizationModel(in_dim,mySystem,
//		in_processTime,in_arrivalTime);	
//
//	in_dim.close();
//	in_machines.close();
//	in_buffers.close();
//	try{
//		myModel->_optObj = EXACT_SIM;
//		int seedPT = 12345;
//		int seedAT = 13245;
//
//		stochasticProperty::RandomNumberGenerator gen(12345);
//
//		int myServerSize(0);
//		myServerSize = myModel->_GPmys->psMachines.size();
//		//std::ofstream out_resultsFile;
//		//out_resultsFile.open("C:/PHD/Opt_VffDM_Integration/VirtualFactoryFramework4/gpMPRrun_32/Test/Testing/GPsimopt/OUTPUT/OutputStatistics.txt");
//
//		for(int rep=0;rep<myModel->replications;rep++)
//		{
//			/*if(myModel->_GPmys->sysType == CLOSEDLOOP)
//				cout << "The system is a closed loop" << endl;
//			else
//				cout << "The system is a flow line" << endl;
//			getchar();
//			cout << "BUFFERS: " << endl;*/
//			for(int i=0;i<myModel->_GPmys->psBuff.size();i++)
//			{
//				cout << "Buffer: " << i+1 << " : " << myModel->_GPmys->psBuff[i]->capacity << endl;
//			}
//			if(rep>0)
//			{
//				
//				myModel->processTimes.clear();
//				myModel->processTimes.resize(myModel->I);
//				
//				int parts(0);
//				for(parts=0;parts<myModel->I;parts++)
//					myModel->processTimes[parts].resize(myServerSize);
//				if(myModel->_GPmys->psMachines[0]->DistribDef==false)
//				{
//					if(!in_processTime)
//						throw "No distribution and no input file were given for processing times!";
//					else
//					{
//						for(parts=0;parts<myModel->I;parts++)
//						{
//							for(int servers=0;servers<myServerSize;servers++)
//							{
//								if(myModel->_GPmys->psMachines[servers]->DistribDef==false)
//									in_processTime >> myModel->processTimes[parts][servers];
//							}
//						}
//					}
//				}
//				else
//				{
//					cout << "Generating a new sample path of processing times" << endl;
//					/*getchar();*/
//					for(size_t i=0;i<myServerSize;i++)
//					{
//						seedPT = seedPT+10000000;
//						std::vector<double> tempPT;
//						tempPT.resize(int(myModel->I));
//						if(myModel->_GPmys->psMachines[i]->pDistribution->myType==0)
//							tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpExpoDataGeneration(gen,int(myModel->I),seedPT,gen);
//						else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==1)
//							tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpUniformDataGeneration(int(myModel->I),seedPT);
//						else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==2)
//							tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpNormalDataGenerator(int(myModel->I),seedPT);
//						else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==3)
//							cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
//						else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==4)
//							tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpConstantDataGeneration(int (myModel->I));
//						else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==5)
//							tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpTriangularDataGenerator(int (myModel->I),seedPT);
//
//
//						for(size_t j=0;j<int(myModel->I);j++)
//							myModel->processTimes[j][i]=tempPT[j];
//						
//						seedPT = seedPT+myModel->I;
//						/*cout << seedPT << endl;*/
//						///*getchar();*/
//					}	
//				}
//
//
//				//ARRIVAL TIMES
//				myModel->arrivalTimes.clear();
//				myModel->arrivalTimes.resize(myModel->I);
//				if(myModel->_GPmys->mycustomer->arrDef==false)
//				{
//					cout << "No probability defined for arrival times " << endl;
//					/*getchar();*/
//					if(!in_arrivalTime)
//						throw "No distribution and no input file were given for interarrival times!";
//					
//					else
//					{
//						for(parts=0;parts<myModel->I;parts++)
//						{
//							if(!in_arrivalTime.eof())
//								in_arrivalTime >> myModel->arrivalTimes[parts];
//							else
//								myModel->arrivalTimes[parts]=0.0;
//						}
//					}
//				}
//				else
//				{
//					cout << "Generating a new sample path of arrival times" << endl;
//					/*getchar();*/
//					std::vector<double> tempAT;
//					tempAT.resize(int(myModel->I));
//					if(myModel->_GPmys->mycustomer->arr_description->myType==0)
//						tempAT=myModel->_GPmys->mycustomer->arr_description->gpExpoDataGeneration(int(myModel->I),seedAT,gen);
//					else if(myModel->_GPmys->mycustomer->arr_description->myType==1)
//						tempAT=myModel->_GPmys->mycustomer->arr_description->gpUniformDataGeneration(int(myModel->I),seedAT);
//					else if(myModel->_GPmys->mycustomer->arr_description->myType==2)
//						tempAT=myModel->_GPmys->mycustomer->arr_description->gpNormalDataGenerator(int(myModel->I),seedAT);
//					else if(myModel->_GPmys->mycustomer->arr_description->myType==3)
//						cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
//					else if(myModel->_GPmys->mycustomer->arr_description->myType==4)
//						tempAT=myModel->_GPmys->mycustomer->arr_description->gpConstantDataGeneration(int (myModel->I));
//
//					
//					//Interarrival generation
//					myModel->arrivalTimes = vectorSort(tempAT,0,int(myModel->I));
//					//Arrival generation
//					myModel->arrivalTimes[0] = 0.0;
//					for(size_t m=1;m<myModel->arrivalTimes.size();m++)
//						myModel->arrivalTimes[m] = myModel->arrivalTimes[m-1]+myModel->arrivalTimes[m];
//
//					/*if(myModel->arrivalTimes.size
//					{*/
//					/*for(int m=0;m<myModel->I;m++)
//					{
//						cout << myModel->arrivalTimes[m] << endl;
//					}*/
//					/*}*/
//					/*getchar();*/
//					
//					/*for(size_t j=0;j<int(myModel->I);j++)
//						myModel->arrivalTimes[j]=tempAT[j];	*/
//					seedAT = seedAT+myModel->I;
//				}
//
//				if(myModel->_GPmys->sysType == CLOSEDLOOP)
//				{
//					for(int parts=0;parts<myModel->I;parts++)
//					{
//						myModel->processTimes[parts].resize(myModel->_GPmys->psMachines.size()+1);
//						myModel->processTimes[parts][myModel->processTimes[parts].size()-1] = 0.0;
//					}
//				}
//			}
//			/*cout << "PROCESS TIMES " << endl;
//			for(int i=0;i<myModel->I;i++)
//			{
//				for(int j=0;j<myServerSize;j++)
//				{
//					std::cout << myModel->processTimes[i][j] << " ";
//				}
//				std::cout << endl;
//			}
//			cout << "ARRIVAL TIMES " << endl;
//			for(int i=0;i<myModel->I;i++)
//			{
//				std::cout << myModel->arrivalTimes[i] << std::endl;
//			}*/
//			/*myModel->App_Solve(out_throughput,out_tb,out_bounds);*/
//			myModel->Simulate(out_throughput,out_x,out_y,out_resultsFile,rep);
//			/*OutputStatistics(myModel,out_resultsFile,rep);*/
//		}
//	}
//	catch(char* str)
//	{
//		std::cerr << "Simulation Model cannot be created: " << str << endl;
//	}
//	in_processTime.close();
//	in_arrivalTime.close();
//	out_throughput.close();
//	out_x.close();
//	out_y.close();
//	out_resultsFile.close();
//
//	return true;
//	/*out_resultsFile.close();*/
//}
//SIMOPTMODELGENDLL_API bool SimulationModel(std::string in_mach, std::string in_buff, std::string in_dim,
//										   std::string out_throug, std::string out_xx, std::string out_yy,
//										   std::string out_rep,std::string  in_procTime, std::string in_arrT)
//{
//	try
//	{
//		cout << "Provo a generare i file" << endl;
//		
//		std::vector<productionSystem::gpWorkstation*> myWset;
//		std::vector<productionSystem::gpBuffer*> myBset;
//		productionSystem::gpProductionSystem* mySystem = new productionSystem::gpProductionSystem();
//		productionSystem::gpCustomer* myCustomer = new productionSystem::gpCustomer();
//
//		cout << "Provo a aprire i file" << endl;
//		//std::ifstream in_machines(in_mach.c_str());
//		//std::ifstream in_buffers(in_buff.c_str());
//		//std::ifstream in_dimensions(in_dim.c_str());
//		/*std::ifstream in_processTime("INPUT/processTime");*/
//		//std::ifstream in_arrivalTime(in_arrT.c_str());
//
//		cout << "Provo a aprire i file" << endl;
//
//
//		
//		//if(!in_machines)
//		//	throw "Cannot open Machine File Info";
//		//if(!in_buffers)
//		//	throw "Cannot open buffer file information";
//		//if(!in_dimensions)
//		//	throw "Cannot open Initialization file for simulation";
//
//		cout << "Ho superato gli if" << endl;
//
//
//		/*createSystem(mySystem,in_machines,in_buffers);		
//
//		
//
//		OptimizationModel::App_OpModel* myModel = createOptimizationModel(in_dimensions,mySystem,
//			in_processTime,in_arrivalTime);	
//
//		myModel->_optObj = EXACT_SIM;
//		int seedPT = 12345;
//		int seedAT = 13245;
//
//		int myServerSize(0);
//		myServerSize = myModel->_GPmys->psMachines.size();*/
//		//std::ofstream out_resultsFile;
//		//out_resultsFile.open("C:/PHD/Opt_VffDM_Integration/VirtualFactoryFramework4/gpMPRrun_32/Test/Testing/GPsimopt/OUTPUT/OutputStatistics.txt");
//		cout << "Provo a chiudere gli input file" << endl;
//
//		//in_machines.close();
//		//in_buffers.close();
//		//in_dimensions.close();
//		
//		cout << "ho chiuso gli input file" << endl;
//
//		cout << "Provo a generare gli output files" << endl;
//
//		//std::ofstream out_throughput;
//		//std::ofstream out_x;
//		//std::ofstream out_y;
//		//std::ofstream out_resultsFile;
//
//		cout << "Provo ad aprire gli output files" << endl;
//
//		//out_throughput.open(out_throug.c_str());
//		//out_x.open(out_xx.c_str());
//		//out_y.open(out_yy.c_str());
//		//out_resultsFile.open(out_rep.c_str());
//
//		//for(int rep=0;rep<myModel->replications;rep++)
//		//{
//		//	cout << "BUFFERS: " << endl;
//		//	for(int i=0;i<myModel->_GPmys->psBuff.size();i++)
//		//	{
//		//		cout << "Buffer: " << i+1 << " : " << myModel->_GPmys->psBuff[i]->capacity << endl;
//		//	}
//		//	if(rep>0)
//		//	{
//		//		
//		//		myModel->processTimes.clear();
//		//		myModel->processTimes.resize(myModel->I);
//		//		
//		//		int parts(0);
//		//		for(parts=0;parts<myModel->I;parts++)
//		//			myModel->processTimes[parts].resize(myServerSize);
//		//		if(myModel->_GPmys->psMachines[0]->DistribDef==false)
//		//		{
//		//			for(parts=0;parts<myModel->I;parts++)
//		//			{
//		//				for(int servers=0;servers<myServerSize;servers++)
//		//				{
//		//					if(myModel->_GPmys->psMachines[servers]->DistribDef==false)
//		//						in_processTime >> myModel->processTimes[parts][servers];
//		//				}
//		//			}
//		//		}
//		//		else
//		//		{
//		//			cout << "Generating a new sample path of processing times" << endl;
//		//			/*getchar();*/
//		//			for(size_t i=0;i<myServerSize;i++)
//		//			{
//		//				seedPT = seedPT+10000000;
//		//				std::vector<double> tempPT;
//		//				tempPT.resize(int(myModel->I));
//		//				if(myModel->_GPmys->psMachines[i]->pDistribution->myType==0)
//		//					tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpExpoDataGeneration(int(myModel->I),seedPT);
//		//				else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==1)
//		//					tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpUniformDataGeneration(int(myModel->I),seedPT);
//		//				else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==2)
//		//					tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpNormalDataGenerator(int(myModel->I),seedPT);
//		//				else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==3)
//		//					cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
//		//				else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==4)
//		//					tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpConstantDataGeneration(int (myModel->I));
//		//				else if(myModel->_GPmys->psMachines[i]->pDistribution->myType==5)
//		//					tempPT=myModel->_GPmys->psMachines[i]->pDistribution->gpTriangularDataGenerator(int (myModel->I),seedPT);
//
//
//		//				for(size_t j=0;j<int(myModel->I);j++)
//		//					myModel->processTimes[j][i]=tempPT[j];
//		//				
//		//				seedPT = seedPT+myModel->I;
//		//				cout << seedPT << endl;
//		//				///*getchar();*/
//		//			}	
//		//		}
//
//
//		//		//ARRIVAL TIMES
//		//		myModel->arrivalTimes.clear();
//		//		myModel->arrivalTimes.resize(myModel->I);
//		//		if(myModel->_GPmys->mycustomer->arrDef==false)
//		//		{
//		//			cout << "No probability defined for arrival times " << endl;
//		//			/*getchar();*/
//		//			for(parts=0;parts<myModel->I;parts++)
//		//			{
//		//				if(!in_arrivalTime.eof())
//		//					in_arrivalTime >> myModel->arrivalTimes[parts];
//		//				else
//		//					myModel->arrivalTimes[parts]=0.0;
//		//			}
//		//		}
//		//		else
//		//		{
//		//			cout << "Generating a new sample path of arrival times" << endl;
//		//			/*getchar();*/
//		//			std::vector<double> tempAT;
//		//			tempAT.resize(int(myModel->I));
//		//			if(myModel->_GPmys->mycustomer->arr_description->myType==0)
//		//				tempAT=myModel->_GPmys->mycustomer->arr_description->gpExpoDataGeneration(int(myModel->I),seedAT);
//		//			else if(myModel->_GPmys->mycustomer->arr_description->myType==1)
//		//				tempAT=myModel->_GPmys->mycustomer->arr_description->gpUniformDataGeneration(int(myModel->I),seedAT);
//		//			else if(myModel->_GPmys->mycustomer->arr_description->myType==2)
//		//				tempAT=myModel->_GPmys->mycustomer->arr_description->gpNormalDataGenerator(int(myModel->I),seedAT);
//		//			else if(myModel->_GPmys->mycustomer->arr_description->myType==3)
//		//				cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
//		//			else if(myModel->_GPmys->mycustomer->arr_description->myType==4)
//		//				tempAT=myModel->_GPmys->mycustomer->arr_description->gpConstantDataGeneration(int (myModel->I));
//
//		//			myModel->arrivalTimes = vectorSort(tempAT,0,int(myModel->I));
//		//			/*if(myModel->arrivalTimes.size
//		//			{*/
//		//			for(int m=0;m<myModel->I;m++)
//		//			{
//		//				cout << myModel->arrivalTimes[m] << endl;
//		//			}
//		//			/*}*/
//		//			getchar();
//		//			
//		//			for(size_t j=0;j<int(myModel->I);j++)
//		//				myModel->arrivalTimes[j]=tempAT[j];	
//		//			seedAT = seedAT+myModel->I;
//		//		}
//
//		//		if(myModel->_GPmys->sysType == CLOSEDLOOP)
//		//		{
//		//			for(int parts=0;parts<myModel->I;parts++)
//		//			{
//		//				myModel->processTimes[parts].resize(myModel->_GPmys->psMachines.size()+1);
//		//				myModel->processTimes[parts][myModel->processTimes[parts].size()-1] = 0.0;
//		//			}
//		//		}
//		//	}
//		//	cout << "PROCESS TIMES " << endl;
//		//	for(int i=0;i<myModel->I;i++)
//		//	{
//		//		for(int j=0;j<myServerSize;j++)
//		//		{
//		//			std::cout << myModel->processTimes[i][j] << " ";
//		//		}
//		//		std::cout << endl;
//		//	}
//		//	cout << "ARRIVAL TIMES " << endl;
//		//	for(int i=0;i<myModel->I;i++)
//		//	{
//		//		std::cout << myModel->arrivalTimes[i] << std::endl;
//		//	}
//		//	/*myModel->App_Solve(out_throughput,out_tb,out_bounds);*/
//		//	
//		//	myModel->Simulate(out_throughput,out_x,out_y,out_resultsFile,rep);
//		//	/*OutputStatistics(myModel,out_resultsFile,rep);*/
//		//}
//
//		
//		cout << "Provo a chiudere gli output files" << endl;
//
//		/*in_processTime.close();*/
//		/*in_arrivalTime.close();
//
//		out_throughput.close();
//		out_x.close();
//		out_y.close();
//		out_resultsFile.close();*/
//
//		cout << "Ho chiuso gli output files" << endl;
//		return true;
//
//	}
//	catch(char* str)
//	{
//		std::cerr << "Cannot perform Simulation because: " << str << endl;
//		return false;
//	}
//	/*out_resultsFile.close();*/
//}
//
//SIMOPTMODELGENDLL_API void SolveOptModel(std::ifstream & in_machines, std::ifstream & in_buffers,std::ifstream & in_dimensions,
//										 std::ofstream & out_throughput, std::ofstream out_tb,std::ofstream & out_bounds,
//										 std::ifstream & in_processTime, std::ifstream & in_arrivalTime)
//{
//		//std::vector<productionSystem::gpWorkstation*> myWset;
//		//std::vector<productionSystem::gpBuffer*> myBset;
//		//productionSystem::gpProductionSystem* mySystem = new productionSystem::gpProductionSystem();
//		//productionSystem::gpCustomer* myCustomer = new productionSystem::gpCustomer();
//
//		//createSystem(mySystem,in_machines,in_buffers);		
//
//		//OptimizationModel::App_OpModel* myModel = createOptimizationModel(in_dimensions,mySystem,
//		//	in_processTime,in_arrivalTime);		
//
//		/*for(int rep=0;rep<myModel->replications;rep++)
//		{
//			if(rep>0)
//			{
//				myModel->processTimes.clear();
//				myModel->processTimes.resize(myModel->I);
//				int myServerSize(0);
//				for(int parts=0;parts<myModel->I;parts++)
//				{
//					myServerSize = myModel->_GPmys->psMachines.size();
//					myModel->processTimes[parts].resize(myServerSize);
//					for(int servers=0;servers<myServerSize;servers++)
//					{
//						in_processTime >> myModel->processTimes[parts][servers];
//					}
//				}
//				if(myModel->_GPmys->sysType == CLOSEDLOOP)
//				{
//					for(int parts=0;parts<myModel->I;parts++)
//					{
//						myModel->processTimes[parts].resize(myModel->_GPmys->psMachines.size()+1);
//						myModel->processTimes[parts][myModel->processTimes[parts].size()-1] = 0.0;
//					}
//				}
//			}
//			myModel->App_Solve(out_throughput,out_tb,out_bounds);
//		}*/
//}
// This is the constructor of a class that has been exported.
// see SimOptModelGenDLL.h for the class definition
CSimOptModelGenDLL::CSimOptModelGenDLL()
{
	return;
}
}