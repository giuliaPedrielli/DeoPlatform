#include "StdAfx.h"
#include "App_OpModel.h"

namespace OptimizationModel{
	using namespace stochasticProperty;

App_OpModel::App_OpModel()
{
	std::cout << "Created the Model" << std::endl;
}
App_OpModel::App_OpModel(productionSystem::gpProductionSystem* s, double servRate,
						 int numParts, int transient,
						 std::vector<std::vector<double> > & pt,std::vector<double> & at)
{
	try
	{
		//std::ofstream ofile;
		//ofile.open("OUTPUT/OUTPUT.txt");
		if(s->TB_cap.size()>0 && this->_optObj!=EXACT_SIM_KBS && 
			this->_optObj!=EXACT_SIM_KCS&&this->_optObj!=EXACT_SIM_BS)
		{
			this->_optObj = SIMULATION;
			std::cout << "Default MPR objective has been set to SIMULATION" << std::endl;
		}
		else
		{
			if(this->_optObj!=EXACT_SIM_KBS &&
						this->_optObj!=EXACT_SIM_KCS&&this->_optObj!=EXACT_SIM_BS){
				this->_optObj = OPTIMIZATION;
			}
			std::cout << "Default MPR objective has been set to OPTIMIZATION" << std::endl;
		}
		
		this->I = numParts;
		std::cout << "The default number of parts is: " << this->I << std::endl;
		this->_GPmys = new productionSystem::gpProductionSystem(s);
		//this->_GPmys->mycustomer = new productionSystem::gpCustomer(s->mycustomer);
		if(this->_GPmys->mycustomer->arrDef)
			cout << "The customer is stochastic: " << this->_GPmys->mycustomer->arr_description->myType << endl;
		else
			cout << "No distribution defined for the customer" << endl;
		/*getchar();*/
		//this->_GPmys = s;
		this->d = transient;
		std::cout << "The default transitory period is 2000" << std::endl;
		this->sr = servRate;
		this->replications = 1;
		std::cout << "The default number of replicates is 1" << std::endl;
		this->delta_feasibility = 10000;
		std::cout << "The default delta feasibility is 1000000" << std::endl;
		/*this->out_th = ofile;
		std::cout << "The default output directory is ""OUTPUT/OUTPUT.txt" << std::endl;*/
		this->_rhsChange = NOT_CHANGE;
		std::cout << "The default right hand side change is NOT_CHANGE" << std::endl;
		this->myAlg = PARrep;
		std::cout << "The default algorithm type is Multiple Replications " << std::endl;
		this->myTol = 0.0;
		std::cout << "the default tolerance is 0.0" << std::endl;
		this->mymodType = FULL;
		std::cout << "The default model type is FULL" << std::endl;

		if(this->_GPmys->mycustomer->arrDef)
			cout << "The customer is stochastic: " << this->_GPmys->mycustomer->arr_description->myType << endl;
		else
			cout << "No distribution defined for the customer" << endl;
		/*getchar();*/

		if(this->_GPmys->sysType==CLOSEDLOOP)
		{
			this->_myOFtype = MIN_s;
			std::cout<< "The default objective function is minimization of s " << std::endl;
			this->myp0 = 1;
			std::cout<< "The default base number of pallets is 1" << std::endl;
			int value(0);
			int PSbUFFdIM(0);
			PSbUFFdIM = this->_GPmys->psBuff.size();
			for(int k=0;k<PSbUFFdIM;k++)
				value = value + this->_GPmys->psBuff[k]->capacity;
			
			this->myPal = value - 1;

			std::cout << "The default maximum number of pallets in the line is set to the sum of capacities: "<<
				this->myPal << std::endl;
		}
		else if(this->_GPmys->sysType == FLOWLINE || this->_GPmys->sysType == SUPPLYCHAIN)
		{
			this->myk0.resize(this->_GPmys->psBuff.size());
			this->mycap.resize(this->_GPmys->psBuff.size());
			int psBuffSize(0);
			psBuffSize = this->_GPmys->psBuff.size();
			for(int i=0;i<psBuffSize;i++)
			{
				this->myk0[i]=0;
				this->mycap[i] = I;
			}
			std::cout<< "The default starting capacity is set to 0" << std::endl;
			std::cout << "The default maximum capacity is set to " << I << std::endl;
		}
		//------------------------------------------------------------------//
		//--------------------RHS generation--------------------------------//
		//----------------------------------------------------------------//
		if(this->_GPmys->mycustomer->arrDef)
			cout << "The customer is stochastic: " << this->_GPmys->mycustomer->arr_description->myType << endl;
		else
			cout << "No distribution defined for the customer" << endl;
		/*getchar();*/

		this->processTimes.resize(pt.size());
		int dimmin= pt.size();
		cout << "Generating Processing Times..." << endl;
		/*getchar();*/
		for(int i=0; i < dimmin;i++)
		{
			this->processTimes[i].resize(pt[i].size());
			for(int j=0;j<pt[i].size();j++)
			{
				this->processTimes[i][j]=pt[i][j];
			}
		}
		cout << "Generating the arrival process..." << endl;
		this->arrivalTimes.resize(at.size());
		for(int i=0;i<at.size();i++)
		{
			this->arrivalTimes[i] = at[i];	
			/*cout << this->arrivalTimes[i] << endl;*/
		}
		/*getchar();*/

		cout << "Process Times and Arrival Times Generated" << endl;

		if(this->_GPmys->mycustomer->arrDef)
			cout << "The customer is stochastic: " << this->_GPmys->mycustomer->arr_description->myType << endl;
		else
			cout << "No distribution defined for the customer" << endl;

		this->myStep = 0.0;
		std::cout << "The default step size is set to 0.0" << std::endl;
		this->myItern = 1;
		std::cout << "The default iteration number is set to 1" << std::endl;

		std::cout << std::endl;
		
		/*std::cout << "Type Y if the initialization worked fine for you N otherwise: " << std::endl;		
		std::string confirm;
		std::cin >> confirm;*/
		
		if(this->_GPmys->mycustomer->arrDef)
			cout << "The customer is stochastic: " << this->_GPmys->mycustomer->arr_description->myType << endl;
		else
			cout << "No distribution defined for the customer" << endl;
		/*getchar();*/

		
		/*if(confirm.c_str()=="N")
			throw "Something went wrong during the inizialization process: User exception";
		else*/
		std::cout << "MODEL SUCCEFULLY CREATED WITH DEFAULT PARAMETERS" << std::endl;


	}
	catch(char* str)
	{
		cout<<"  The model was not created "<< str <<endl;
	}
};

bool App_OpModel::generateDOEcondition(std::vector<std::vector<double> > & factDOE)
{
	std::string in_DOEdescr;
	in_DOEdescr = "INPUT\\DOE.txt";
	std::ifstream in_DOE;
	in_DOE.open(in_DOEdescr.c_str());
	double deltaPT(0.0);
	double deltaSR(0.0);
	double deltaVar(0.0);
	int conditions = 27;
	int fact2=0;
	int contCond=0;
	while(!in_DOE.eof())
	{
		in_DOE >> deltaSR;
		in_DOE >> deltaPT;
		in_DOE >> deltaVar;
	}
	
	factDOE.resize(conditions);
	int k=0;
	for(int i=0;i<conditions*3;i++)
	{
		if(i<9)
		{
			factDOE[k].resize(3);
			factDOE[k][0]=-deltaSR;
			k++;
		}
		if(i>=9 && i<18)
		{
			factDOE[k].resize(3);
			factDOE[k][0]=0.0;
			k++;
		}
		if(i>=18 && i<27)
		{
			factDOE[k].resize(3);
			factDOE[k][0]=deltaSR;
			k++;
		}
		if(i>=27 && i<54)
		{
			if(i==27)
				k=0;
			if(fact2<9)
			{
				
				if(k<3)
				{
					factDOE[k][1]=-deltaPT;
				}
				if(k>=3 && k<6)
					factDOE[k][1]=0.0;
				if(k>=6 && k<9)
					factDOE[k][1]=deltaPT;
				k++;
				fact2++;
			}
			if(fact2>=9 && fact2<18)
			{
				if(fact2==9)
					k=0;
				if(k<3)
				{
					factDOE[fact2][1]=-deltaPT;
				}
				if(k>=3 && k<6)
					factDOE[fact2][1]=0.0;
				if(k>=6 && k<9)
					factDOE[fact2][1]=deltaPT;
				k++;
				fact2++;
			}
			if(fact2>=18 && fact2<27)
			{
				if(fact2==18)
					k=0;
				if(k<3)
				{
					factDOE[fact2][1]=-deltaPT;
				}
				if(k>=3 && k<6)
					factDOE[fact2][1]=0.0;
				if(k>=6 && k<9)
					factDOE[fact2][1]=deltaPT;
				k++;
				fact2++;
			}
		}
		
		
		if(i>=54 && i<81)
		{
			if(i%3==0)
			{
				fact2=0;
				factDOE[contCond][2]=-deltaVar;
				contCond++;
			}
			else
			{
				if(fact2==0)
					factDOE[contCond][2]=0.0;
				else
					factDOE[contCond][2]=deltaVar;
				fact2++;
				contCond++;
			}
		}
	}

	if(factDOE.size()>0)
		return true;
	else
		return false;
}
void App_OpModel::BuildModel(int a)
{
	string label;                           
	char tempstr[10]; 
	char temp[10]; 
	int i(0);
	int j(0);
	int k(0);
	double rt(0.0);
	rt = sr*I;
	
	int J(0);

	if(_GPmys->sysType==CLOSEDLOOP || _GPmys->sysType==SUPPLYCHAIN)
		J= _GPmys->J+1;
	else
		J= _GPmys->J;


	if(this->_rhsChange == CHANGE_T)
	{
	 for(i=0;i<I;i++)
	 {
		for(j=0;j<J;j++)
		{
			this->processTimes[i][j]=this->processTimes[i][j]+myStep*a;
		}
	 }
	}
	
	if((this->myAlg == INCsp || this->myAlg == INCspwTOL) && (a > 0))
	{
		I = I+this->myStep;
		rt = I*sr;
	}

	
	if(this->_GPmys->sysType==SUPPLYCHAIN)
	{
		if((this->_optObj==BASESTOCK || this->_optObj==KANBAN || this->_optObj == EXTENDED_KANBAN || this->_optObj == APP_OPT_TBCS) ||
			(this->_optObj==SIM_BASESTOCK || this->_optObj==SIM_KANBAN || this->_optObj == SIM_EXTENDED_KANBAN || this->_optObj == APP_SIM_TBCS))
			this->BuildSupplyChainApproximateModel(a);
		else if((this->_optObj==EXACT_OPT_BSC || this->_optObj==EXACT_OPT_KSC || this->_optObj == EXACT_OPT_EKCS) ||
			(this->_optObj==EXACT_SIM_BS || this->_optObj==EXACT_SIM_KCS || this->_optObj == EXACT_SIM_BS))
			this->BuildSupplyChainExactModel(a);
	}
	else
	{
		if((this->_optObj==OPTIMIZATION || this->_optObj==SIMULATION))
			this->BuildTandemLineApproximateModel(a);
		else if((this->_optObj==EXACT_OPT || this->_optObj==EXACT_SIM))
			this->BuildTandemLineExactModel(a);
	}		
}

void App_OpModel::BuildTandemLineExactModel(int a)
{
	string label;                           
	char tempstr[10]; 
	char temp[10]; 
	int i(0);
	int j(0);
	int k(0);
	double rt(0.0);
	rt = sr*I;
	int transitory(0);
	if(d>0)
		transitory=d;
	else
		transitory=1;
	int J(0);

	if(_GPmys->sysType==CLOSEDLOOP)
		J= _GPmys->J+1;
	else
		J= _GPmys->J;

	y = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		y[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "y_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			y[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	
	x_s_b = NumVarMatrix(env,mycap[0]);
	z_buf = BoolVarMatrix(env,mycap[0]);
	z_pal = IloIntVarArray(env,myPal);
	x_s_k = NumVarMatrix(env,mycap[0]);

	for(i=0;i<mycap[0];i++)
	{
		x_s_b[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_s_b_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_s_b[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		z_buf[i] = IloIntVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "z_buf_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);
			z_buf[i].add(IloIntVar(env,0,1,label.c_str()));
		}
	}

	z_pal = IloIntVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "z_pal_";
		label += itoa(i+1,temp,10);
		z_pal[i]=IloIntVar(env,0,1,label.c_str());
	}

	x_s_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_s_p_";
		label += itoa(i+1,temp,10);

		x_s_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());
	}
	
	x_b_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_b_p_";
		label += itoa(i+1,temp,10);

		x_b_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	}
	
	label = "epsilon";			
	epsilon=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	std::cout<<" Obj"<< std::endl;
	obj=IloNumExpr(env);
	if(this->_optObj==EXACT_OPT)
	{
		if( _GPmys->sysType==CLOSEDLOOP)
		{									
			for (i = 0; i < myPal; ++i)
			{
				obj += i*z_pal[i];
			}
		}
		else
		{
			for(j=0;j<J-1;j++)
			{
				for (i = 0; i < mycap[0];++i)
				{
					obj += i*z_buf[i][j];
				}
			}
		}
	}
	else
	{
		cout << "Minimizing the sum of Processing Times" << endl;
		
		if(this->_optObj==EXACT_SIM)
		{
			cout << "Performing Exact Simulation" << endl;
			for(i=0;i<this->I;i++)
			{
				for(j=0;j<J-1;j++)
					obj += y[i][j];
			}
		}

	}
		
	mod = IloModel(env);
	//////////////////////////////////////////////////////////////////////////////////*
	mod.add(IloMinimize(env,obj)); 

	//******************************************************************************************
	//******************************************************************************************
	//|     CONSTRAINTS     |*******************************************************************
	//******************************************************************************************
	//******************************************************************************************
	range = IloRangeArray(env);
	int controw(0);

	for(i=0;i<I;i++)
	{
		IloNumExpr expr(env);
		expr += y[i][0];
		
		label = "c_a_";
		label += itoa(i+1,tempstr,10);
		range.add(IloRange(env, this->arrivalTimes[i]+ this->processTimes[i][0],expr,+IloInfinity));
		range[controw].setName(label.c_str());
		controw++;
		expr.end();
	}

	//Disjunctive constraint for each part
	for(i=0;i<I;++i)
	{
		if(i==0)
			cout << "WRITING DISJ CONSTRAINTS" << endl;
		for(j=0;j < J - 1;++j)
		{
			IloNumExpr expr(env);
			expr += y[i][j+1];
			expr -= y[i][j];
			label = "c_dis_part_";
			label += itoa(i+1,tempstr,10);
			label += "_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env, this->processTimes[i][j+1],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
	}

	for(i=0;i<I;++i)
	{
		if(i==0)
		{
			cout << "WRITING DUMMIES CONSTRAINTS" << endl;
			cout << J << endl;
		}
		for(j=1;j < J;++j)
		{
			IloNumExpr expr(env);
			expr += y[i][j];
			expr -= this->processTimes[i][j];
			expr -= y[i][j-1];
			label = "c_dis_part_DUMMIES_";
			label += itoa(i+1,tempstr,10);
			label += "_";
			label += itoa(j,tempstr,10);

			range.add(IloRange(env, 0.0,expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
	}
	
	//Disjunctive constraint for each machine
	for(j=0;j < J;++j)
	{
		for(i=0;i < I - 1;++i)
		{
			IloNumExpr expr(env);
			expr += y[i+1][j];
			expr -= y[i][j];

			label = "c_dis_mach_";
			label += itoa(i+1,tempstr,10);
			label += "_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env, this->processTimes[i+1][j],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
	}

	//Individuate constraints related to the modelling of pallet/buffer capacity
	//in the manufacturing line

	if(_GPmys->sysType==CLOSEDLOOP)
	{	
		for(j=0;j < J - 1;++j)
		{
			for(i=0;i < I - _GPmys->psBuff[j]->capacity;++i)
			{
				IloNumExpr expr(env);
				expr += y[i + _GPmys->psBuff[j]->capacity][j];
				expr -= y[i][j+1];
				
				label = "c_cap_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i+ _GPmys->psBuff[j]->capacity][j],
					expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		if(this->_optObj == EXACT_OPT)
		{
			for(k=0;k<myPal;k++)
			{
				IloNumExpr expr(env);
				expr += z_pal[k];

				label = "c_defZ_PAP_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,1));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

			int bigMM(0);
			for(i=0;i<I;i++)
			{
				for(j=0;j<J-1;j++)
					bigMM += (int)(this->processTimes[i][j]);
			}
			bigMM = bigMM*I;

			cout << "WRITING PALLET CONSTRAINTS" << endl;
			for(k=myp0;k<=myPal;k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += y[i+k][0];
					expr -= y[i][J-1];
					expr -= bigMM*z_pal[k-1];
					label = "c_pallet_a_";
					label += itoa(k,tempstr,10);
					label += "_";
					label += itoa(i+1,tempstr,10);

					range.add(IloRange(env, this->processTimes[i+k][0]-bigMM,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
			IloNumExpr exprPalZ(env);
			for(k=0;k<myPal;k++)
			{
				exprPalZ += z_pal[k];
			}
			label = "c_Pal_IPconsistency_";

			range.add(IloRange(env,1,exprPalZ,1));
			range[controw].setName(label.c_str());
			controw++;
			exprPalZ.end();
			
			for(k = myp0; k<= myPal; ++k)
			{
				for(i=0;i < I-k+1;++i)
				{
					IloNumExpr expr(env);
					expr += y[i][J-1];
					expr -= y[i+k-1][0];
					expr -= bigMM*z_pal[k-1];

					label = "c_pallet_b_";
					label += itoa(k,tempstr,10);
					label += "_";
					label += itoa(i+1,tempstr,10);

					range.add(IloRange(env,-bigMM,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}

		else if(this->_optObj == EXACT_SIM)
		{
			for(i=0;i < I-this->myPal;++i)
			{
				IloNumExpr expr(env);
				expr += y[i+this->myPal][0];
				expr -= y[i][J-1];

				label = "c_pallet_s_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(this->myPal,tempstr,10);

				range.add(IloRange(env, this->processTimes[i+this->myPal][0],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

			for(i=0;i < I-this->myPal+1;++i)
			{
				IloNumExpr expr(env);
				expr += y[i][J-1];
				expr -= y[i+this->myPal-1][0];

				label = "c_pallet_b_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(this->myPal,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
	}
	else if(_GPmys->sysType==FLOWLINE)
	{
		if(this->_optObj == EXACT_OPT)
		{
			for(j=0;j < J - 1;++j)
			{
				for(k=0;k<mycap[j];k++)
				{
					IloNumExpr expr(env);
					expr += z_buf[k][j];

					label = "c_defZ_BAP_";
					label += itoa(k+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					range.add(IloRange(env,0,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}

			int bigMM(0);
			for(i=0;i<I;i++)
			{
				for(j=0;j<J-1;j++)
					bigMM += (int)(this->processTimes[i][j]);
			}
			bigMM = bigMM*I;

			cout << "WRITING BUFFER CONSTRAINTS" << endl;
			for(j=0;j < J - 1;++j)
			{
				for(k=1;k<=mycap[j];k++)
				{
					for(i=0;i < I - k;++i)
					{
						IloNumExpr expr(env);
						expr += y[i+k][j];
						expr -= y[i][j+1];
						expr -= bigMM*z_buf[k-1][j];
						label = "c_CapBuf_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env, this->processTimes[i+k][j]-bigMM,expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
					}
				}
			}
			
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr exprBufZ(env);
				for(k=0;k< mycap[j];k++)
				{
					exprBufZ += z_buf[k][j];
				}
				
				label = "c_Buf_IPconsistency_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env,1,exprBufZ,1));
				range[controw].setName(label.c_str());
				controw++;
				exprBufZ.end();
			}
			
		}		
		else if(this->_optObj == EXACT_SIM)
		{
			int numBuff = this->_GPmys->psBuff.size();
			for(j=0;j < numBuff;++j)
			{
				int cap = this->_GPmys->psBuff[j]->capacity;
				for(i=0;i < I - cap;++i)
				{
					IloNumExpr expr(env);
					expr += y[i+cap][j];
					expr -= y[i][j+1];

					label = "c_cap_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(cap,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);

					range.add(IloRange(env,this->processTimes[i+cap][j],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
					
				}
			}
		}

	}
	if(this->_optObj == EXACT_OPT)
	{
		IloNumExpr expr2(env);
		double factor(0.0);
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			num = i+1;
			factor = (double)(1)/((double)(num));
			factor = (double)(factor)/((double)(I-d));
			expr2 += factor*y[i][J-1];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_throughput";

		rt=(rt/(I));
		range.add(IloRange(env,-IloInfinity,expr2,rt));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();

		if(delta_feasibility==0)
		{
			IloNumExpr exprEps(env);
			exprEps += epsilon;
			label = "c_epsilon";

			range.add(IloRange(env,0,exprEps,0));
			range[controw].setName(label.c_str());
			controw++;
			exprEps.end();
		}
	}
	mod.add(range);
}

void App_OpModel::BuildTandemLineApproximateModel(int a)
{
	string label;                           
	char tempstr[10]; 
	char temp[10]; 
	int i(0);
	int j(0);
	int k(0);
	double rt(0.0);
	rt = sr*I;
	int transitory(0);
	if(d>0)
		transitory=d;
	else
		transitory=1;
	
	int J(0);

	if(_GPmys->sysType==CLOSEDLOOP)
		J= _GPmys->J+1;
	else
		J= _GPmys->J;

	y = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		y[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "y_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			y[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	
	x_s_b = NumVarMatrix(env,mycap[0]);
	z_buf = BoolVarMatrix(env,mycap[0]);
	z_pal = IloIntVarArray(env,myPal);
	x_s_k = NumVarMatrix(env,mycap[0]);

	for(i=0;i<mycap[0];i++)
	{
		x_s_b[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_s_b_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_s_b[i].add(IloNumVar(env,this->boundS,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		z_buf[i] = IloIntVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "z_buf_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);
			z_buf[i].add(IloIntVar(env,0,1,label.c_str()));
		}
	}

	z_pal = IloIntVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "z_pal_";
		label += itoa(i+1,temp,10);
		z_pal[i]=IloIntVar(env,0,1,label.c_str());
	}

	x_s_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_s_p_";
		label += itoa(i+1,temp,10);

		x_s_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());
	}
	
	x_b_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_b_p_";
		label += itoa(i+1,temp,10);

		x_b_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	}
	
	label = "epsilon";			
	epsilon=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	std::cout<<" Obj"<< std::endl;
	obj=IloNumExpr(env);
	if(this->_optObj == OPTIMIZATION)
	{
		if( _GPmys->sysType==CLOSEDLOOP)
		{
			if(this->delta_feasibility>0)
				obj += delta_feasibility*epsilon;
		for (i = myp0-1; i < myPal; ++i)
		{
			if(this->_myOFtype == MIN_s)
				obj += x_s_p[i];
			else
				obj += x_b_p[i];
		}
		}
		else
		{
			//The basic idea is that we do not minize buffer already given			
			if(this->delta_feasibility>0)
				obj += delta_feasibility*epsilon;
			int sizeCost(0);
			sizeCost=this->cost_stage.size();
			for(j=0;j<J-1;j++)
			{
				if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
				{
					for (i = myk0[j]; i < mycap[j];++i)
					{
						obj += x_s_b[i][j];
					}
				}
				else
				{
					for (i = 0; i < mycap[j];++i)
					{
						if(this->alphaLessi>0 && sizeCost==0)
							obj += (this->alphaLessi*(1+this->myStep*a))*x_s_b[i][j];
						
						else if(sizeCost==0)
							obj += x_s_b[i][j];
					}
				}
			}
			if(this->alphaLessi>0&& this->cost_stage.size()==0)
			{
				for(i=0;i<this->I;i++)
				{
					for(j=0;j<J;j++)
						obj += y[i][j];
				}
			}
			else if(this->cost_stage.size()>0)
			{
				/*obj += this->cost_stage[0]*y[(this->I)-1][0];*/
				if(this->makesimNatwithCosts==0)
				{
					for(i=0;i<this->I-1;i++)
					{
						/*obj += this->cost_stage[0]*y[i][0];*/
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(y[i+1][j-1]-y[i][j-1]);
							/*obj += this->cost_stage[j]*(y[i][j]-y[i-1][j]+x_s_b[0][j-1]);*/
							/*obj += this->cost_stage[j]*(y[i][j+1]-y[i-1][j+1]+x_s_b[0][j]);*/
							/*obj += -(this->cost_stage[j]-this->cost_stage[j-1])*(y[i+1][j-1]+x_s_b[0][j-1]);*/
					}
					for(i=0;i<this->I-1;i++)
					{
						/*obj += this->cost_stage[0]*y[i][0];*/
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(x_s_b[0][j-1]);
							/*obj += this->cost_stage[j]*(y[i][j]-y[i-1][j]+x_s_b[0][j-1]);*/
							/*obj += this->cost_stage[j]*(y[i][j+1]-y[i-1][j+1]+x_s_b[0][j]);*/
							/*obj += -(this->cost_stage[j]-this->cost_stage[j-1])*(y[i+1][j-1]+x_s_b[0][j-1]);*/
					}
				}
				else
				{
					for(i=0;i<this->I;i++)
					{
						/*obj += this->cost_stage[0]*y[i][0];*/
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(y[i][j]-y[i][j-1]);
					}
				}
				//for(i=0;i<this->I;i++)
				//{
				//	/*obj += (this->cost_stage[0]-this->cost_stage[1])*y[i][0];*/
				//	obj += this->cost_stage[J-1]*(y[i][J-2]+x_s_b[0][J-2]);
				//}
			}
		}
	}
	else
	{
		cout << "Minimizing the sum of Processing Times" << endl;
		
		if(this->_optObj==SIMULATION)
		{
			//if(this->cost_stage.size()>0 && this->makesimNatwithCosts==0)
			//{
			//	/*obj += this->cost_stage[0]*y[(this->I)-1][0];*/
			//	/*for(i=0;i<this->I;i++)*/
			//	for(i=0;i<this->I;i++)
			//	{
			//		/*obj += this->cost_stage[0]*y[i][0];*/
			//		for(j=1;j<J;j++)
			//			obj += this->cost_stage[j-1]*(y[i][j]-y[i][j-1]);
			//	}
			//}
			//
			//else
			//{
			for(i=0;i<this->I;i++)
			{
				for(j=0;j<J;j++)
					obj += y[i][j];
			}
			/*}*/
		}

	}
	mod = IloModel(env);
	//////////////////////////////////////////////////////////////////////////////////*
	mod.add(IloMinimize(env,obj)); // NOT GENERAL ******* ATT'N: MIN or MAX ??????? //*
	//////////////////////////////////////////////////////////////////////////////////*

	//******************************************************************************************
	//******************************************************************************************
	//|     CONSTRAINTS     |*******************************************************************
	//******************************************************************************************
	//******************************************************************************************
	range = IloRangeArray(env);
	int controw(0);

	for(i=0;i<I;i++)
	{
		IloNumExpr expr(env);
		expr += y[i][0];
		
		label = "c_a_";
		label += itoa(i+1,tempstr,10);
		range.add(IloRange(env, this->arrivalTimes[i]+ this->processTimes[i][0],expr,+IloInfinity));
		range[controw].setName(label.c_str());
		controw++;
		expr.end();
	}

	//Disjunctive constraint for each part
	for(i=0;i<I;++i)
	{
		if(i==0)
			cout << "WRITING DISJ CONSTRAINTS" << endl;
		for(j=0;j < J - 1;++j)
		{
			IloNumExpr expr(env);
			expr += y[i][j+1];
			expr -= y[i][j];
			label = "c_dis_part_";
			label += itoa(i+1,tempstr,10);
			label += "_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env, this->processTimes[i][j+1],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
	}

	for(i=0;i<I;++i)
	{
		if(i==0)
		{
			cout << "WRITING DUMMIES CONSTRAINTS" << endl;
			cout << J << endl;
		}
		for(j=1;j < J;++j)
		{
			IloNumExpr expr(env);
			expr += y[i][j];
			expr -= this->processTimes[i][j];
			expr -= y[i][j-1];
			label = "c_dis_part_DUMMIES_";
			label += itoa(i+1,tempstr,10);
			label += "_";
			label += itoa(j,tempstr,10);

			range.add(IloRange(env, 0.0,expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
	}
	
	//Disjunctive constraint for each machine
	for(j=0;j < J;++j)
	{
		for(i=0;i < I - 1;++i)
		{
			IloNumExpr expr(env);
			expr += y[i+1][j];
			expr -= y[i][j];

			label = "c_dis_mach_";
			label += itoa(i+1,tempstr,10);
			label += "_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env, this->processTimes[i+1][j],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
	}

	//Individuate constraints related to the modelling of pallet/buffer capacity
	//in the manufacturing line

	if(_GPmys->sysType==CLOSEDLOOP)
	{	
		for(j=0;j < J - 1;++j)
		{
			for(i=0;i < I - _GPmys->psBuff[j]->capacity;++i)
			{
				IloNumExpr expr(env);
				expr += y[i + _GPmys->psBuff[j]->capacity][j];
				expr -= y[i][j+1];
				
				label = "c_cap_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i+ _GPmys->psBuff[j]->capacity][j],
					expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		if(this->_optObj == OPTIMIZATION)
		{
			for(k=0;k<myPal;k++)
			{
				IloNumExpr expr(env);
				expr += x_s_p[k];

				label = "c_defS_PAP_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

			for(k=0;k<myPal;k++)
			{
				IloNumExpr expr(env);
				expr += x_b_p[k];

				label = "c_defB_PAP_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

			for (k=myp0;k <= myPal;++k)
			{
				for(i=0;i < I-k;++i)
				{
					IloNumExpr expr(env);
					expr += y[i+k][0];
					expr -= y[i][J-1];
					expr += x_s_p[k-1];

					label = "c_pallet_s_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(k,tempstr,10);

					range.add(IloRange(env, this->processTimes[i+k][0],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
			
			for(k = myp0; k<= myPal; ++k)
			{
				for(i=0;i < I-k+1;++i)
				{
					IloNumExpr expr(env);
					expr += y[i][J-1];
					expr -= y[i+k-1][0];
					expr += x_b_p[k-1];

					label = "c_pallet_b_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(k,tempstr,10);

					range.add(IloRange(env,0,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		else if(this->_optObj == SIMULATION && this->_myOFtype == MIN_s)
		{
			for(k=0;k<myPal;k++)
			{
				IloNumExpr expr(env);
				expr += x_b_p[k];

				label = "c_defB_PAP_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
			for (k=myp0;k <= myPal;++k)
			{
				for(i=0;i < I-k;++i)
				{
					IloNumExpr expr(env);
					expr += y[i+k][0];
					expr -= y[i][J-1];

					label = "c_pallet_s_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(k,tempstr,10);

					range.add(IloRange(env, this->processTimes[i+k][0] - this->_GPmys->TB_cap[k-1][0],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
			
			for(k = myp0; k<= myPal; ++k)
			{
				for(i=0;i < I-k+1;++i)
				{
					IloNumExpr expr(env);
					expr += y[i][J-1];
					expr -= y[i+k-1][0];
					expr += x_b_p[k-1];

					label = "c_pallet_b_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(k,tempstr,10);

					range.add(IloRange(env,0,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		else if(this->_optObj == SIMULATION && this->_myOFtype == MIN_b)
		{
			for(k=0;k<myPal;k++)
			{
				IloNumExpr expr(env);
				expr += x_s_p[k];

				label = "c_defS_PAP_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

			for (k=myp0;k <= myPal;++k)
			{
				for(i=0;i < I-k;++i)
				{
					IloNumExpr expr(env);
					expr += y[i+k][0];
					expr -= y[i][J-1];
					expr += x_s_p[k-1];

					label = "c_pallet_s_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(k,tempstr,10);

					range.add(IloRange(env, this->processTimes[i+k][0],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
			
			for(k = myp0; k<= myPal; ++k)
			{
				for(i=0;i < I-k+1;++i)
				{
					IloNumExpr expr(env);
					expr += y[i][J-1];
					expr -= y[i+k-1][0];

					label = "c_pallet_b_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(k,tempstr,10);

					range.add(IloRange(env,- this->_GPmys->TB_cap[k-1][0],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
	}
	else if(_GPmys->sysType==FLOWLINE)
	{
		if((this->_optObj == OPTIMIZATION))
		{
			for(j=0;j < J - 1;++j)
			{
				for(k=0;k<mycap[j];k++)
				{
					IloNumExpr expr(env);
					expr += x_s_b[k][j];

					label = "c_defTB_BAP_";
					label += itoa(k+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					range.add(IloRange(env,0,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		
		if((this->_optObj == OPTIMIZATION) && ((mymodType==REDUCED_OF)||(mymodType==FULL)))
		{
			for(j=0;j < J - 1;++j)
			{
				
				for(k=1;k<=mycap[j];k++)
				{
					for(i=0;i < I - k;++i)
					{
						IloNumExpr expr(env);
						expr += y[i+k][j];
						expr -= y[i][j+1];
						expr += x_s_b[k-1][j];

						label = "c_cap_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(k,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);

						range.add(IloRange(env,this->processTimes[i+k][j],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
					}
				}
			}
		}
		else if((this->_optObj == OPTIMIZATION) && ((mymodType!=REDUCED_OF)&&(mymodType!=FULL)))
		{
			for(j=0;j < J - 1;++j)
			{
				for(k=myk0[j];k<=mycap[j];k++)
				{
					for(i=0;i < I - k;++i)
					{
						IloNumExpr expr(env);
						expr += y[i+k][j];
						expr -= y[i][j+1];
						expr += x_s_b[k-1][j];

						label = "c_cap_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(k,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);

						range.add(IloRange(env, this->processTimes[i+k][j],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
					}
				}
			}
		}
		else if(this->_optObj==SIMULATION)
		{
			int numBuff = this->mycap.size();
			this->ptRHStbCuts.clear();
			this->contRowFirstTBconst=controw;
			for(j=0;j < numBuff;++j)
			{					
				for(k=1;k<=this->mycap[j];k++)
				{
					for(i=0;i < I - k;++i)
					{
						IloNumExpr expr(env);
						expr += y[i+k][j];
						expr -= y[i][j+1];

						label = "c_cap_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(k,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);

						range.add(IloRange(env,this->processTimes[i+k][j] - this->_GPmys->TB_cap[k-1][j],
							expr,+IloInfinity));
						this->ptRHStbCuts.push_back(this->processTimes[i+k][j]);
						this->tbRHStbCuts.push_back(this->_GPmys->TB_cap[k-1][j]);
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}
			this->contRowLastTBconst=controw-1;
			cout << "Time buffer constraints written!" << endl;
		}
	}
	if(this->_optObj == OPTIMIZATION)
	{
		IloNumExpr expr2(env);
		double factor(0.0);
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			num = i+1;
			factor = (double)(1)/((double)(num));
			factor = (double)(factor)/((double)(I-d));
			expr2 += factor*y[i][J-1];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_throughput";

		rt=(rt/(I));
		range.add(IloRange(env,-IloInfinity,expr2,rt));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();

		if(delta_feasibility==0)
		{
			IloNumExpr exprEps(env);
			exprEps += epsilon;
			label = "c_epsilon";

			range.add(IloRange(env,0,exprEps,0));
			range[controw].setName(label.c_str());
			controw++;
			exprEps.end();
		}
	}
	mod.add(range);
}
void App_OpModel::BuildSupplyChainApproximateModel(int a)
{
	string label;                           
	char tempstr[10]; 
	char temp[10]; 
	int i(0);
	int j(0);
	int k(0);
	double rt(0.0);
	rt = sr*I;
	int transitory(0);
	if(d>0)
		transitory=d;
	else
		transitory=1;
	
	int J(0);

	if(_GPmys->sysType==SUPPLYCHAIN)
		J= _GPmys->J+1;
	else
		J= _GPmys->J;


	

	y = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		y[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "y_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			y[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	st = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		st[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "s_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			st[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	rTime = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		rTime[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "rTime_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			rTime[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	if((this->_optObj==BASESTOCK || this->_optObj==EXACT_OPT_BSC || 
		this->_optObj==EXACT_OPT_EKCS || this->_optObj==EXTENDED_KANBAN) && a==0)
	{
		for(j=0;j<J-2;j++)
		{
			for(int l=j+1;l<J-1;l++)
			{
				this->mycap[j] = this->mycap[j]+this->mycap[l];
			}
		}
	}
	else if(this->_optObj==EXACT_OPT_KSC && a==0)
	{
		int maxK(0);
		for(j=0;j<J-1;j++)
		{
			maxK += this->mycap[j];
		}
		/*for(j=0;j<J-1;j++)
		{
			this->mycap[j] = maxK;
		}*/
	}
	x_s_b = NumVarMatrix(env,mycap[0]);
	z_bs = BoolVarMatrix(env,mycap[0]);
	z_ks = BoolVarMatrix(env,mycap[0]);
	x_s_k = NumVarMatrix(env,mycap[0]);
	x_ip_s = NumVarMatrix(env,mycap[0]);

	for(i=0;i<mycap[0];i++)
	{
		x_s_b[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_s_b_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_s_b[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		z_bs[i]=IloIntVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "z_bs_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			z_bs[i].add(IloIntVar(env,0,1,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		z_ks[i]=IloIntVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "z_ks_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			z_ks[i].add(IloIntVar(env,0,1,label.c_str()));
		}
	}

	//time buffer dedicate to kanban modelling	
	for(i=0;i<mycap[0];i++)
	{
		x_s_k[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_s_k_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_s_k[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		x_ip_s[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_ip_s_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_ip_s[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	x_s_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_s_p_";
		label += itoa(i+1,temp,10);

		x_s_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());
	}
	
	x_b_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_b_p_";
		label += itoa(i+1,temp,10);

		x_b_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	}
	
	label = "epsilon";			
	epsilon=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	std::cout<<" Obj"<< std::endl;
	obj=IloNumExpr(env);
	if(this->_optObj==EXTENDED_KANBAN)
	{
		if(this->_myOFtype == MIN_s)
		{
			int sizeCost(0);
			sizeCost=this->cost_stage.size();
			for(j=0;j<J-1;j++)
			{
				if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
				{
					for (i = myk0[j]; i < mycap[j];++i)
					{
						obj += x_s_k[i][j];
						obj += x_s_b[i][j];
					}
				}
				else
				{
					if(this->alphaLessi>0 && sizeCost==0)
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += (this->alphaLessi*(1+this->myStep*a))*x_s_k[i][j];
							obj += (this->alphaLessi*(1+this->myStep*a))*x_s_b[i][j];
						}
					}
					else if(sizeCost==0 || makesimNatwithCosts==3)
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += x_s_k[i][j];
							obj += x_s_b[i][j];
						}
					}
				}
			}
			
			if(this->alphaLessi>0&& this->cost_stage.size()==0)
			{
				for(i=0;i<this->I;i++)
				{
					for(j=0;j<J-1;j++)
						obj += y[i][j];
				}
			}
			else if(this->cost_stage.size()>0)
			{
				if(this->makesimNatwithCosts==0)
				{
					for(i=0;i<this->I-1;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(rTime[i+1][j-1]-rTime[i][j-1]);
					}
					for(i=0;i<this->I-1;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(x_s_k[0][j-1]+x_s_b[0][j-1]);
					}
				}
				else if(this->makesimNatwithCosts==1.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(rTime[i][j]-rTime[i][j-1]);
					}
				}
				else if(this->makesimNatwithCosts==2.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=0;j<J-1;j++)
						{
							obj += y[i][j];
							obj += st[i][j];
							obj += rTime[i][j];
						}
						obj += rTime[i][J-1];
					}
				}
				else if(this->makesimNatwithCosts==4.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=1;j<J;j++)
							obj += (rTime[i][j]-rTime[i][j-1]);
					}
				}
			}
			
		}
		
		if(this->delta_feasibility>0)
			obj += this->delta_feasibility*epsilon;
		
	}
	else if(this->_optObj==KANBAN || this->_optObj==APP_OPT_TBCS)
	{
		if(this->_myOFtype == MIN_s)
		{
			int sizeCost(0);
			sizeCost=this->cost_stage.size();
			for(j=0;j<J-1;j++)
			{
				if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
				{
					for (i = myk0[j]; i < mycap[j];++i)
					{
						obj += x_s_k[i][j];
					}
				}
				else
				{
					if(this->alphaLessi>0 && sizeCost==0)
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += (this->alphaLessi*(1+this->myStep*a))*x_s_k[i][j];
						}
					}
					else if(sizeCost==0 || makesimNatwithCosts==3)
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += x_s_k[i][j];
						}
					}
						
					/*obj += (this->alphaLessi*(1+this->myStep*a))*x_s_b[i][j];*/
						
						
					/*for (i = 0; i < mycap[0];++i)
					{
						obj += x_s_k[i][j];
					}
					if(this->delta_feasibility>0)
						obj += this->delta_feasibility*epsilon;*/
				}
			}
			if(this->delta_feasibility>0)
				obj += this->delta_feasibility*epsilon;
			if(this->alphaLessi>0&& this->cost_stage.size()==0)
			{
				for(i=0;i<this->I;i++)
				{
					for(j=0;j<J-1;j++)
						obj += y[i][j];
				}
			}
			else if(this->cost_stage.size()>0)
			{
				if(this->makesimNatwithCosts==0)
				{
					for(i=0;i<this->I-1;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(rTime[i+1][j-1]-rTime[i][j-1]);
					}
					for(i=0;i<this->I-1;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(x_s_k[0][j-1]);
					}
				}
				else if(this->makesimNatwithCosts==1.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(rTime[i][j]-rTime[i][j-1]);
					}
				}
				else if(this->makesimNatwithCosts==2.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=0;j<J-1;j++)
						{
							obj += y[i][j];
							obj += st[i][j];
							obj += rTime[i][j];
						}
						obj += rTime[i][J-1];
					}
				}
				else if(this->makesimNatwithCosts==4.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=1;j<J;j++)
							obj += (rTime[i][j]-rTime[i][j-1]);
					}
				}
			}
			
		}
		else if(this->_myOFtype == MIN_WT)
		{
			for(i=0;i<I;i++)
			{
				for (j = 0; j < J-1;++j)
				{
					obj += rTime[i][j+1];
					obj -= y[i][j];
					obj += st[i][j];
					obj -= rTime[i][j];
				}
			}
		}
		else if(this->_myOFtype == MIN_TT)
		{
			for(i=0;i<I;i++)
			{
				for (j = 0; j < J-1;++j)
				{
					obj += rTime[i][j+1];
					obj += y[i][j];
					obj += st[i][j];
					obj += rTime[i][j];
				}
			}
		}
		else if(this->_myOFtype == MIN_ML)
		{
			for(i=0;i<I;i++)
			{
				obj += rTime[i][J-1];
			}
		}
	}
	else if(this->_optObj==BASESTOCK)
	{
		if(this->_myOFtype == MIN_s)
		{
			int sizeCost(0);
			sizeCost=this->cost_stage.size();
			for(j=0;j<J-1;j++)
			{
				if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
				{
					for (i = myk0[j]; i < mycap[j];++i)
					{
						obj += x_s_b[i][j];
					}
				}
				else
				{
					if(this->alphaLessi>0 && sizeCost==0)
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += (this->alphaLessi*(1+this->myStep*a))*x_s_b[i][j];
						}
					}
					else if(sizeCost==0 || makesimNatwithCosts==3)
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += x_s_b[i][j];
						}
					}
				}
			}
			if(this->delta_feasibility>0)
				obj += this->delta_feasibility*epsilon;
			if(this->alphaLessi>0&& this->cost_stage.size()==0)
			{
				for(i=0;i<this->I;i++)
				{
					for(j=0;j<J-1;j++)
						obj += y[i][j];
				}
			}
			else if(this->cost_stage.size()>0)
			{
				if(this->makesimNatwithCosts==0)
				{
					for(i=0;i<this->I-1;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(rTime[i+1][j-1]-rTime[i][j-1]);
					}
					for(i=0;i<this->I-1;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(x_s_b[0][j-1]);
					}
				}
				else if(this->makesimNatwithCosts==1.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=1;j<J;j++)
							obj += this->cost_stage[j-1]*(rTime[i][j]-rTime[i][j-1]);
					}
				}
				else if(this->makesimNatwithCosts==2.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=0;j<J-1;j++)
						{
							obj += y[i][j];
							obj += st[i][j];
							obj += rTime[i][j];
						}
						obj += rTime[i][J-1];
					}
				}
				else if(this->makesimNatwithCosts==4.0)
				{
					for(i=0;i<this->I;i++)
					{
						for(j=1;j<J;j++)
							obj += (rTime[i][j]-rTime[i][j-1]);
					}
				}

			}
			
		}
		
	}
	else
	{
			
		if(this->_optObj==SIM_KANBAN && this->makesimNatwithCosts==1)
		{
			for(i=0;i<this->I;i++)
			{
				for(j=1;j<J;j++)
					obj += this->cost_stage[j-1]*(rTime[i][j]-rTime[i][j-1]);
			}
		}
		else
		{
			for(i=0;i<this->I;i++)
			{
				for(j=0;j<J-1;j++)
				{
					obj += y[i][j];
					obj += st[i][j];
					obj += rTime[i][j];
				}
				obj += rTime[i][J-1];
			}
		}

	}
	
	mod = IloModel(env);
	//////////////////////////////////////////////////////////////////////////////////*
	mod.add(IloMinimize(env,obj));
	//******************************************************************************************
	range = IloRangeArray(env);
	int controw(0);

	if(this->_optObj==KANBAN)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= st[i][j];
				
				label = "c_seq_xTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += y[i+1][j];
				expr -= y[i][j];
				
				label = "c_seq_yTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i+1][j];
				expr -= rTime[i][j];
				
				label = "c_seq_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		for(i=0;i<mycap[0];i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += x_s_k[i][j];
				
				label = "c_pos_tb_kanban_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PARTS SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING START DEPARTURE CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
				
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			cout << "WRITING KANBAN CONSTRAINTS" << endl;			
			for(k=1;k<=mycap[0];k++)
			{
				for(j=0;j < J-1 ;j++)
				{
					for(i=0;i<I-k;++i)
					{				
						IloNumExpr expr(env);
						
						expr += rTime[i+k][j];
						expr += x_s_k[k-1][j];
						expr -= rTime[i][j+1];
													
						label = "c_Kanban_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env,0,expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}
		}
		if(this->_myOFtype==MIN_WT && this->SeqModel==true)
		{
			if(this->TB_kan.size()>0)
			{
				if(this->TB_kan[0].size()>0)
				{
					if(this->TB_kan[0][0]>0.0)
					{
						cout << "WRITING KANBAN CONSTRAINTS" << endl;
						for(k=0;k<mycap[0];k++)
						{
							for(j=0;j < J-1 ;j++)
							{			
								IloNumExpr expr(env);
								
								expr += x_s_k[k][j];
															
								label = "c_Kanban_UB_";
								label += itoa(i+1,tempstr,10);
								label += "_";
								label += itoa(j+1,tempstr,10);
								label += "_";
								label += itoa(k+1,tempstr,10);

								range.add(IloRange(env,0,expr,this->TB_kan[k][j]));
								range[controw].setName(label.c_str());
								controw++;
								expr.end();
							}
						}
					}
				}
			}
		}
		else if(this->_myOFtype==MIN_s && this->SeqModel==true)
		{
			if(this->boundWTval > 0.0)
			{
				IloNumExpr exprWT(env);
				for(i=0;i<I;i++)
				{
					for (j = 0; j < J-1;++j)
					{
						exprWT += rTime[i][j+1];
						exprWT -= y[i][j];
						exprWT += st[i][j];
						exprWT -= rTime[i][j];
					}
				}
				label = "c_WT_av_CUT";
				range.add(IloRange(env,0,exprWT,this->boundWTval*I));
				range[controw].setName(label.c_str());
				controw++;
				exprWT.end();
			}
		}

		if(this->_myOFtype != MIN_ML)
		{
			IloNumExpr expr2(env);
			
			double num(0.0);

			for(i=transitory-1;i<I;i++)
			{
				expr2 += rTime[i][J-1];
				num += demandProcess[i];
			}
			if(delta_feasibility>0)
			expr2 += -epsilon;

			label = "c_ServiceLevel";

			range.add(IloRange(env,-IloInfinity,expr2,this->alpha*(this->I-d)+num));
			range[controw].setName(label.c_str());
			controw++;
			expr2.end();
		}
	}
	else if(this->_optObj==APP_OPT_TBCS)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		for(i=0;i<mycap[0];i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += x_s_k[i][j];
				
				label = "c_pos_tb_kanban_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PARTS SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING START DEPARTURE CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
				
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			cout << "WRITING KANBAN CONSTRAINTS (1)" << endl;			
			for(k=0;k<mycap[0];k++)
			{
				for(j=1;j < J ;j++)
				{
					for(i=0;i<I-k-1;++i)
					{				
						IloNumExpr expr(env);
						
						expr -= rTime[i][j];
						expr += x_s_k[k][j-1];
						expr += rTime[i+k+1][j-1];
													
						label = "c_Kanban_(1)_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env,0,expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}

			/*cout << "WRITING KANBAN CONSTRAINTS (2)" << endl;			
			for(k=1;k<=mycap[0];k++)
			{
				for(j=0;j < J-1 ;j++)
				{
					for(i=0;i<I-k;++i)
					{				
						IloNumExpr expr(env);
						
						expr += rTime[i+k][j];
						expr -= x_s_k[k-1][j];
						expr -= rTime[i][j];
													
						label = "c_Kanban_(2)_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env,0,expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}*/
		}

		if(this->_myOFtype != MIN_ML)
		{
			IloNumExpr expr2(env);
			
			double num(0.0);

			for(i=transitory-1;i<I;i++)
			{
				expr2 += rTime[i][J-1];
				num += demandProcess[i];
			}
			if(delta_feasibility>0)
			expr2 += -epsilon;

			label = "c_ServiceLevel";

			range.add(IloRange(env,-IloInfinity,expr2,this->alpha*(this->I-d)+num));
			range[controw].setName(label.c_str());
			controw++;
			expr2.end();
		}
	}
	else if(this->_optObj == BASESTOCK)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];
		for(i=0;i<I;i++)
		{
			if(i==0)
				cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
			for(i=maxBSTOT;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
				
		cout << "WRITING BASE STOCK CONSTRAINTS(1)" << endl;
		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			for(j=0;j < J-1 ;++j)
			{
				for(k=1;k<=mycap[0];k++)
				{
					for(i=0;i< I-k;++i)
					{
						IloNumExpr expr(env);
						expr += rTime[i+k][j];
						expr += x_s_b[k-1][j];
						label = "c_BaseStock(1)_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
					}
				}
			}
		}
		
		IloNumExpr expr2(env);
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			expr2 += rTime[i][J-1];
			num += demandProcess[i];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_ServiceLevel";

		range.add(IloRange(env,0,expr2,this->alpha*(this->I-d)+num));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();

		int echBS(0);
		//Disjunctive constraint for each machine
		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			for(j=0;j < J-1;++j)
			{
				if(j==0)
					cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT)" << endl;
				for(i=0; i< this->mycap[0];++i)
				{
					IloNumExpr expr(env);
					expr -= st[i][j];
					expr += y[i][j];
					expr += x_s_b[i][j];

					label = "c_dis_ech_init_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);

					range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}

		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT2)" << endl;
			for(i=0; i< maxBSTOT;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
	}
	else if(this->_optObj==EXTENDED_KANBAN)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PARTS SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (1)" << endl;
		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			for(j=0;j < J-1;++j)
			{
				for(i=0; i< this->mycap[0];++i)
				{
					IloNumExpr expr(env);
					expr -= st[i][j];
					expr += y[i][j];
					expr += x_s_b[i][j];

					label = "c_dis_ech_init_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);

					range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		cout << "WRITING START DEPARTURE CONSTRAINTS (2)" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=this->mycap[0];i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
				
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		
		cout << "WRITING BASE STOCK CONSTRAINTS" << endl;
		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			for(j=0;j < J-1 ;++j)
			{
				for(k=1;k<=mycap[0];k++)
				{
					for(i=0;i< I-k;++i)
					{
						IloNumExpr expr(env);
						expr += rTime[i+k][j];
						expr += x_s_b[k-1][j];
						label = "c_BaseStock(1)_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
					}
				}
			}

			cout << "WRITING KANBAN CONSTRAINTS" << endl;			
			for(k=0;k<mycap[0];k++)
			{
				for(j=0;j < J-1 ;j++)
				{
					for(i=0;i<I-k;++i)
					{				
						IloNumExpr expr(env);
						
						expr += rTime[i+k][j];
						expr += x_s_k[k][j];
						expr -= rTime[i][j+1];
													
						label = "c_Kanban_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env,0,expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}
		}

		IloNumExpr expr2(env);
		
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			expr2 += rTime[i][J-1];
			num += demandProcess[i];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_ServiceLevel";

		range.add(IloRange(env,-IloInfinity,expr2,this->alpha*(this->I-d)+num));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();

		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];

		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT2)" << endl;
		for(j=0;j < J-1;++j)
		{	
			for(i=0; i< maxBSTOT;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
	}

	else if(this->_optObj==SIM_KANBAN)
	{
		cout << "z positivity" << endl;
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= st[i][j];
				
				label = "c_seq_xTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += y[i+1][j];
				expr -= y[i][j];
				
				label = "c_seq_yTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i+1][j];
				expr -= rTime[i][j];
				
				label = "c_seq_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "x positivity" << endl;
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += st[i][j];
				
				label = "c_pos_startTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "y positivity" << endl;
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += y[i][j];
				
				label = "c_pos_finishTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, 0,expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_rel_finish_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PART SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_startfinish_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_start_finish_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();					
		}
		
		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			cout << "WRITING KANBAN CONSTRAINTS" << endl;
			for(k=1;k<=mycap[0];k++)
			{
				for(j=0;j < J-1 ;j++)
				{
					for(i=0;i<I-k;++i)
					{				
						IloNumExpr expr(env);
						
						expr += rTime[i+k][j];
						expr -= rTime[i][j+1];
													
						label = "c_Kanban_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env,-this->TB_kan[k-1][j],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}
		}
		
		if(this->optCUTS==true)
		{
			IloNumExpr exprML(env);
			double num(0.0);

			for(i=d;i<I;i++)
			{
				exprML += rTime[i][J-1];
				num += demandProcess[i];
			}
			label = "c_MeanLateness";

			range.add(IloRange(env,0,exprML,this->alpha*(this->I)+num));
			range[controw].setName(label.c_str());
			controw++;
			exprML.end();
		}
		if(this->boundWTval > 0.0 && this->WT_cuts==true)
		{
			IloNumExpr exprWT(env);
			for(i=0;i<I;i++)
			{
				for (j = 0; j < J-1;++j)
				{
					exprWT += rTime[i][j+1];
					exprWT -= y[i][j];
					exprWT += st[i][j];
					exprWT -= rTime[i][j];
				}
			}
			label = "c_WT_av_CUT";
			range.add(IloRange(env,0,exprWT,this->boundWTval*I));
			range[controw].setName(label.c_str());
			controw++;
			exprWT.end();
		}
	}
	else if(this->_optObj==APP_SIM_TBCS)
	{
		cout << "z positivity" << endl;
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "x positivity" << endl;
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += st[i][j];
				
				label = "c_pos_startTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "y positivity" << endl;
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += y[i][j];
				
				label = "c_pos_finishTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, 0,expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_rel_finish_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PART SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_startfinish_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_start_finish_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();					
		}
		
		if(this->tbCUTS==true || this->_myOFtype==MIN_s)
		{
			cout << "WRITING KANBAN CONSTRAINTS (1)" << endl;
			/*for(k=0;k<mycap[0];k++)
			{
				for(j=1;j < J ;j++)
				{
					for(i=0;i<I-k-1;++i)
					{				
						IloNumExpr expr(env);
						
						expr -= rTime[i][j];
						expr += rTime[i+k+1][j-1];
													
						label = "c_Kanban_(1)_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env, this->TB_kan[k][j-1],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}*/
			int countKK(0);
			bool written=false;
			
			for(j=1;j < J ;j++)
			{
				written=false;
				for(k=0;k<mycap[0];k++)
				{					
					for(i=0;i<I-k-1;++i)
					{
						if((k<mycap[0]-1) && (this->TB_kan[k][j-1]>0.0) && (this->TB_kan[k+1][j-1]==0.0))
						{
							IloNumExpr expr(env);
							expr -= rTime[i][j];
							expr += rTime[i+k+1][j-1];
													
							label = "c_Kanban_(1)_";
							label += itoa(i+1,tempstr,10);
							label += "_";
							label += itoa(j+1,tempstr,10);
							label += "_";
							label += itoa(k+1,tempstr,10);

							range.add(IloRange(env, this->TB_kan[k][j-1],expr,+IloInfinity));
							range[controw].setName(label.c_str());
							controw++;
							expr.end();
							written=true;
						}
						else if(k==0 && this->TB_kan[k][j-1]==0 && written==false)
						{
							IloNumExpr expr(env);
							expr -= rTime[i][j];
							expr += rTime[i+k+1][j-1];
													
							label = "c_Kanban_(1)_";
							label += itoa(i+1,tempstr,10);
							label += "_";
							label += itoa(j+1,tempstr,10);
							label += "_";
							label += itoa(k+1,tempstr,10);

							range.add(IloRange(env, this->TB_kan[k][j-1],expr,+IloInfinity));
							range[controw].setName(label.c_str());
							controw++;
							expr.end();
							written=true;
						}
						else if(countKK==mycap[0] && written == false)
						{
							IloNumExpr expr(env);
							expr -= rTime[i][j];
							expr += rTime[i+k+1][j-1];
													
							label = "c_Kanban_(1)_";
							label += itoa(i+1,tempstr,10);
							label += "_";
							label += itoa(j+1,tempstr,10);
							label += "_";
							label += itoa(k+1,tempstr,10);

							range.add(IloRange(env, this->TB_kan[k][j-1],expr,+IloInfinity));
							range[controw].setName(label.c_str());
							controw++;
							expr.end();
							written=true;
						}
						else
							countKK++;
						
					}
				}
			}
			/*cout << "WRITING KANBAN CONSTRAINTS (2)" << endl;
			for(k=1;k<=mycap[0];k++)
			{
				for(j=0;j < J-1 ;j++)
				{
					for(i=0;i<I-k;++i)
					{				
						IloNumExpr expr(env);
						
						expr += rTime[i+k][j];
						expr -= rTime[i][j];
													
						label = "c_Kanban_(2)_";
						label += itoa(i+1,tempstr,10);
						label += "_";
						label += itoa(j+1,tempstr,10);
						label += "_";
						label += itoa(k+1,tempstr,10);

						range.add(IloRange(env,+this->TB_kan[k-1][j],expr,+IloInfinity));
						range[controw].setName(label.c_str());
						controw++;
						expr.end();
						
					}
				}
			}*/
		}
		
		if(this->optCUTS==true)
		{
			IloNumExpr exprML(env);
			double num(0.0);

			for(i=d;i<I;i++)
			{
				exprML += rTime[i][J-1];
				num += demandProcess[i];
			}
			label = "c_MeanLateness";

			range.add(IloRange(env,0,exprML,this->alpha*(this->I)+num));
			range[controw].setName(label.c_str());
			controw++;
			exprML.end();
		}
		if(this->boundWTval > 0.0 && this->WT_cuts==true)
		{
			IloNumExpr exprWT(env);
			for(i=0;i<I;i++)
			{
				for (j = 0; j < J-1;++j)
				{
					exprWT += rTime[i][j+1];
					exprWT -= y[i][j];
					exprWT += st[i][j];
					exprWT -= rTime[i][j];
				}
			}
			label = "c_WT_av_CUT";
			range.add(IloRange(env,0,exprWT,this->boundWTval*I));
			range[controw].setName(label.c_str());
			controw++;
			exprWT.end();
		}
	}
	else if(this->_optObj==SIM_BASESTOCK)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];
		for(i=0;i<I;i++)
		{
			if(i==0)
				cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
			for(i=maxBSTOT;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
				
		cout << "WRITING BASE STOCK CONSTRAINTS(1)" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(k=1;k<=mycap[0];k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += rTime[i+k][j];
					label = "c_BaseStock(1)_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env, demandProcess[i]-this->TB_bs[k-1][j],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}

		////////////////////////////////////////////////
		//********************************************//
		//***************INITIALIZATION***************//
		//********************************************//
		////////////////////////////////////////////////

		int echBS(0);
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT)" << endl;
			for(i=0; i< this->mycap[0];++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j]-this->TB_bs[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT2)" << endl;
			for(i=0; i< maxBSTOT;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

	}
	else if(this->_optObj==SIM_EXTENDED_KANBAN)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PART SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (1)" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0; i< this->mycap[0];++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j]-this->TB_bs[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=maxBSTOT;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();					
		}
		cout << "WRITING BASE STOCK CONSTRAINTS" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(k=1;k<=mycap[0];k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += rTime[i+k][j];
					label = "c_BaseStock(1)_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env, demandProcess[i]-this->TB_bs[k-1][j],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		cout << "WRITING KANBAN CONSTRAINTS" << endl;
		for(k=0;k<mycap[0];k++)
		{
			for(j=0;j < J-1 ;j++)
			{
				for(i=0;i<I-k;++i)
				{				
					IloNumExpr expr(env);
					
					expr += rTime[i+k][j];
					expr -= rTime[i][j+1];
												
					label = "c_Kanban_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env,-this->TB_kan[k][j],expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
					
				}
			}
		}

		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT2)" << endl;
			for(i=0; i< maxBSTOT;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
	
	}
	mod.add(range);
}
void App_OpModel::BuildSupplyChainExactModel(int a)
{
	string label;                           
	char tempstr[10]; 
	char temp[10]; 
	int i(0);
	int j(0);
	int k(0);
	double rt(0.0);
	rt = sr*I;
	int transitory(0);
	if(d>0)
		transitory=d;
	else
		transitory=1;
	
	int J(0);

	if(_GPmys->sysType==SUPPLYCHAIN)
		J= _GPmys->J+1;
	else
		J= _GPmys->J;


	

	y = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		y[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "y_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			y[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	st = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		st[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "s_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			st[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	rTime = NumVarMatrix(env,I);
	for (i=0;i<I;i++){
		rTime[i]=IloNumVarArray(env);
		for (j=0;j<J;j++){
			label = "rTime_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			rTime[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	if((this->_optObj==BASESTOCK || this->_optObj==EXACT_OPT_BSC || 
		this->_optObj==EXACT_OPT_EKCS || this->_optObj==EXTENDED_KANBAN) && a==0)
	{
		for(j=0;j<J-2;j++)
		{
			for(int l=j+1;l<J-1;l++)
			{
				this->mycap[j] = this->mycap[j]+this->mycap[l];
			}
		}
	}
	else if(this->_optObj==EXACT_OPT_KSC && a==0)
	{
		int maxK(0);
		for(j=0;j<J-1;j++)
		{
			maxK += this->mycap[j];
		}
		/*for(j=0;j<J-1;j++)
		{
			this->mycap[j] = maxK;
		}*/
	}
	x_s_b = NumVarMatrix(env,mycap[0]);
	z_bs = BoolVarMatrix(env,mycap[0]);
	z_ks = BoolVarMatrix(env,mycap[0]);
	x_s_k = NumVarMatrix(env,mycap[0]);
	x_ip_s = NumVarMatrix(env,mycap[0]);

	for(i=0;i<mycap[0];i++)
	{
		x_s_b[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_s_b_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_s_b[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		z_bs[i]=IloIntVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "z_bs_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			z_bs[i].add(IloIntVar(env,0,1,label.c_str()));
		}
	}

	

	for(i=0;i<mycap[0];i++)
	{
		z_ks[i]=IloIntVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "z_ks_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			z_ks[i].add(IloIntVar(env,0,1,label.c_str()));
		}
	}

	//time buffer dedicate to kanban modelling	
	for(i=0;i<mycap[0];i++)
	{
		x_s_k[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_s_k_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_s_k[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}

	for(i=0;i<mycap[0];i++)
	{
		x_ip_s[i]=IloNumVarArray(env);
		int psBufSize(0);
		psBufSize = _GPmys->psBuff.size();
		for(j=0;j<psBufSize;j++)
		{
			label = "x_ip_s_";
			label += itoa(i+1,temp,10);
			label += "_";
			label += itoa(j+1,temp,10);

			x_ip_s[i].add(IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str()));
		}
	}
	x_s_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_s_p_";
		label += itoa(i+1,temp,10);

		x_s_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());
	}
	
	x_b_p = IloNumVarArray(env,myPal);
	for(i=0;i<myPal;i++){
		label = "x_b_p_";
		label += itoa(i+1,temp,10);

		x_b_p[i]=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	}
	
	label = "epsilon";			
	epsilon=IloNumVar(env,0,+IloInfinity,ILOFLOAT,label.c_str());

	std::cout<<" Obj"<< std::endl;
	obj=IloNumExpr(env);
	
	if(this->_optObj==EXACT_OPT_BSC)
	{
		for(j=0;j<J-1;j++)
		{
			if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
			{
				for (i = myk0[j]; i < mycap[0];++i)
				{
					obj += z_bs[i][j]*i;		
				}
			}
			else
			{
				for (i = 0; i < mycap[0];++i)
				{
					obj += z_bs[i][j]*i;
				}
				if(this->delta_feasibility>0)
					obj += this->delta_feasibility*epsilon;
			}
		}
	}
	else if(this->_optObj==EXACT_OPT_KSC)
	{
		if(this->delta_feasibility>0)
			obj += this->delta_feasibility*epsilon;
		if(this->_myOFtype == MIN_s)
		{
			for(j=0;j<J-1;j++)
			{
				if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
				{
					for (i = myk0[j]; i < mycap[0];++i)
					{
						obj += z_ks[i][j]*i;		
					}
				}
				else
				{
					if(this->makesimNatwithCosts==1.0)
					{
						for(i=0;i<this->I;i++)
						{
							for(j=1;j<J;j++)
								obj += this->cost_stage[j-1]*(rTime[i][j]-rTime[i][j-1]);
						}
					}
					else
					{
						for (i = 0; i < mycap[0];++i)
						{
							obj += z_ks[i][j]*i;
						}
					}
				}
			}
		}
		else if(this->_myOFtype == MIN_WT)
		{
			for(i=0;i<I;i++)
			{
				for (j = 0; j < J-1;++j)
				{
					obj += rTime[i][j+1];
					obj -= y[i][j];
					obj += st[i][j];
					obj -= rTime[i][j];
				}
			}
		}
		else if(this->_myOFtype == MIN_TT)
		{
			for(i=0;i<I;i++)
			{
				for (j = 0; j < J-1;++j)
				{
					obj += rTime[i][j+1];
					obj += y[i][j];
					obj += st[i][j];
					obj += rTime[i][j];
				}
			}
		}
	}
	else if(this->_optObj==EXACT_OPT_EKCS)
	{
		for(j=0;j<J-1;j++)
		{
			if(mymodType==REDUCED_OF||mymodType==REDUCED_FULL)
			{
				for (i = myk0[j]; i < mycap[0];++i)
				{
					obj += z_ks[i][j]*i;
					obj += z_bs[i][j]*i;		
				}
			}
			else
			{
				for (i = 0; i < mycap[0];++i)
				{
					obj += z_ks[i][j]*i;
					obj += z_bs[i][j]*i;
				}
				if(this->delta_feasibility>0)
						obj += this->delta_feasibility*epsilon;
			}
		}
	}

	else
	{
		cout << "Performing Exact Simulation" << endl;	
		for(i=0;i<this->I;i++)
		{
			for(j=0;j<J-1;j++)
			{
				obj += y[i][j];
				obj += st[i][j];
				obj += rTime[i][j];
			}
			obj += rTime[i][J-1];
		}

	}
	mod = IloModel(env);
	//////////////////////////////////////////////////////////////////////////////////*
	mod.add(IloMinimize(env,obj));
	//******************************************************************************************
	range = IloRangeArray(env);
	int controw(0);

	
	if(this->_optObj == EXACT_OPT_BSC)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];

		for(i=0;i<I;i++)
		{
			if(i==0)
				cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
			for(i=maxBSTOT;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
				
		int bigMM(0);
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
				bigMM += (int)(this->processTimes[i][j]);
		}
		/*bigMM = bigMM*I;*/
		bigMM = I;

		cout << "WRITING BASE STOCK CONSTRAINTS(1)" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(k=1;k<=mycap[0];k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += rTime[i+k][j];
					for(int h=0;h<k;h++)
						expr -= bigMM*z_bs[h][j];
					label = "c_BaseStock(1)_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env, demandProcess[i]-bigMM,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		IloNumExpr expr2(env);
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			expr2 += rTime[i][J-1];
			num += demandProcess[i];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_ServiceLevel";

		range.add(IloRange(env,0,expr2,this->alpha*(this->I-d)+num));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();

		int echBS(0);
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT)" << endl;
			for(i=0; i< this->mycap[0];++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];
				for(int h=0;h<i;h++)
					expr += bigMM*z_bs[i][j];

				label = "c_dis_ech_init_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j] - bigMM,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT2)" << endl;
			for(i=0; i< maxBSTOT;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		
		for(j=0;j < J-1 ;++j)
		{
			IloNumExpr expr3(env);
			for(k=0;k<mycap[0];k++)
			{
				expr3 += z_bs[k][j];
			}
			label = "c_BS_IPconsistency_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env,1,expr3,1));
			range[controw].setName(label.c_str());
			controw++;
			expr3.end();
		}
		
	}

	else if(this->_optObj == EXACT_OPT_KSC)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= st[i][j];
				
				label = "c_seq_xTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += y[i+1][j];
				expr -= y[i][j];
				
				label = "c_seq_yTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i+1][j];
				expr -= rTime[i][j];
				
				label = "c_seq_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];

		for(i=0;i<I;i++)
		{
			if(i==0)
				cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
			for(i=0;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		for(i=0;i<I;++i)
		{
			if(i==0)
				cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
				
		int bigMM(0);
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
				bigMM += (int)(this->processTimes[i][j]);
		}
		/*bigMM = bigMM*I;*/
		bigMM = I;

		cout << "WRITING KANBAN CONSTRAINTS" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(k=1;k<=mycap[0];k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += rTime[i+k][j];
					expr -= rTime[i][j+1];
					expr -= bigMM*z_ks[k-1][j];
					label = "c_kanban_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env, -bigMM,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		IloNumExpr expr2(env);
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			expr2 += rTime[i][J-1];
			num += demandProcess[i];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_ServiceLevel";

		range.add(IloRange(env,0,expr2,this->alpha*(this->I - d)+num));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();

		/*for(j=0;j < J-1 ;++j)
		{
			IloNumExpr expr3(env);
			for(k=0;k<mycap[0];k++)
			{
				expr3 += z_ks[k][j];
			}
			label = "c_KC_IPconsistency_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env,-IloInfinity,expr3,1));
			range[controw].setName(label.c_str());
			controw++;
			expr3.end();
		}*/
		for(j=0;j < J-1 ;++j)
		{
			IloNumExpr expr3(env);
			for(k=0;k<mycap[0];k++)
			{
				expr3 += z_ks[k][j];
			}
			label = "c_KC_IPconsistency_2_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env,1,expr3,1));
			range[controw].setName(label.c_str());
			controw++;
			expr3.end();
		}
		
	}

	else if(this->_optObj == EXACT_OPT_EKCS)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}

		int maxBSTOT(0);
		maxBSTOT += this->mycap[0];

		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PARTS SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{	
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		int bigMM(0);
		for(i=0;i<I;i++)
		{
			for(j=0;j<J-1;j++)
				bigMM += (int)(this->processTimes[i][j]);
		}
		/*bigMM = bigMM*I;*/
		bigMM = I;
		
		//Disjunctive constraint for each machine
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (1)" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0; i< this->mycap[0];++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];
				for(int h=0;h<i;h++)
					expr += bigMM*z_bs[i][j];

				label = "c_dis_ech_init_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j] - bigMM,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=maxBSTOT;i < I;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		cout << "WRITING BASE STOCK CONSTRAINTS" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(k=1;k<=mycap[0];k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += rTime[i+k][j];
					for(int h=0;h<k;h++)
						expr -= bigMM*z_bs[h][j];
					label = "c_BaseStock(1)_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env, demandProcess[i]-bigMM,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		cout << "WRITING KANBAN CONSTRAINTS" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(k=1;k<=mycap[0];k++)
			{
				for(i=0;i< I-k;++i)
				{
					IloNumExpr expr(env);
					expr += rTime[i+k][j];
					expr -= rTime[i][j+1];
					expr -= bigMM*z_ks[k-1][j];
					label = "c_kanban_";
					label += itoa(i+1,tempstr,10);
					label += "_";
					label += itoa(j+1,tempstr,10);
					label += "_";
					label += itoa(k+1,tempstr,10);

					range.add(IloRange(env, -bigMM,expr,+IloInfinity));
					range[controw].setName(label.c_str());
					controw++;
					expr.end();
				}
			}
		}
		IloNumExpr expr2(env);
		double num(0.0);

		for(i=transitory-1;i<I;i++)
		{
			expr2 += rTime[i][J-1];
			num += demandProcess[i];
		}
		if(delta_feasibility>0)
			expr2 += -epsilon;
		label = "c_ServiceLevel";

		range.add(IloRange(env,0,expr2,this->alpha*(this->I-d)+num));
		range[controw].setName(label.c_str());
		controw++;
		expr2.end();
		
		for(j=0;j < J-1 ;++j)
		{
			IloNumExpr expr3(env);
			for(k=0;k<mycap[0];k++)
			{
				expr3 += z_bs[k][j];
			}
			label = "c_BS_IPconsistency_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env,1,expr3,1));
			range[controw].setName(label.c_str());
			controw++;
			expr3.end();
		}

		for(j=0;j < J-1 ;++j)
		{
			IloNumExpr expr4(env);
			for(k=0;k<mycap[0];k++)
			{
				expr4 += z_ks[k][j];
			}
			label = "c_KC_IPconsistency_";
			label += itoa(j+1,tempstr,10);

			range.add(IloRange(env,1,expr4,1));
			range[controw].setName(label.c_str());
			controw++;
			expr4.end();
		}

		for(j=0;j < J-1;++j)
		{
			if(j==0)
				cout << "WRITING STARTING DEPARTURE CONSTRAINTS (INIT2)" << endl;
			for(i=0; i< maxBSTOT;++i)
			{
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		
	}
	else if(this->_optObj==EXACT_SIM_KCS )
	{
	
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= st[i][j];
				
				label = "c_seq_xTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J-1;j++)
			{
				IloNumExpr expr(env);
				expr += y[i+1][j];
				expr -= y[i][j];
				
				label = "c_seq_yTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		for(i=0;i<I-1;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i+1][j];
				expr -= rTime[i][j];
				
				label = "c_seq_rTime_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{	
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PARRT SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I;++i)
			{
				
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING START RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		cout << "WRITING KANBAN CONSTRAINTS" << endl;
		for(j=0;j < J-1 ;j++)
		{	
			for(i=0;i<I-this->_GPmys->psKanban[j]->capacity;++i)
			{				
				IloNumExpr expr(env);
				
				expr += rTime[i+this->_GPmys->psKanban[j]->capacity][j];
				expr -= rTime[i][j+1];
				
				label = "c_Kanban_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				label += "_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}		
	}

	else if(this->_optObj==EXACT_SIM_BS)
	{
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		int totBaseStock(0);
		for(i=0;i<I;i++)
		{
			if(i==totBaseStock)
				cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}

		
		for(j=0;j<J-1;++j)
		{
			if(j==0)
				cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
			for(i=0;i < I;++i)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();					
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();

				
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
		for(j=0;j < J-1;++j)
		{	
			for(i=this->_GPmys->psBaseStock[0]->capacity;i < I;++i)
			{
				
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();

				
			}
		}
		cout << "WRITING STARTING RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{	
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
			
		cout << "WRITING BASE STOCK CONSTRAINTS(1)" << endl;
		int minK(0);
		totBaseStock=0;
		for(j=0;j < J-1 ;++j)
		{
			for(i=0;i< I - this->_GPmys->psBaseStock[j]->capacity;++i)
			{
				IloNumExpr expr(env);
				expr += rTime[i+this->_GPmys->psBaseStock[j]->capacity][j];
				label = "c_BaseStock(1)_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		//******************************//
		//**INIZIALIZATION CONSTRAINTS**//
		//******************************//

		cout << "WRITING STARTING DEPARTURE CONSTRAINTS" << endl;
		for(j=1;j < J-1 ;++j)
		{
			for(i=this->_GPmys->psBaseStock[j]->capacity;i<this->_GPmys->psBaseStock[0]->capacity;i++)
			{					
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}

		for(j=0;j < J-1 ;++j)
		{
			for(i=0;i< this->_GPmys->psBaseStock[0]->capacity;++i)
			{
				
				IloNumExpr expr(env);
				/*expr += rTime[i+totBaseStock][j];*/
				expr += y[i][j];
				expr -= st[i][j];
				
				label = "c_st_yt_(1)_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
	}
	else if(this->_optObj==EXACT_SIM_KBS)
	{	
		for(i=0;i<I;i++)
		{
			for(j=0;j<J;j++)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j];
				
				label = "c_pos_rTime";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}

		}
		cout << "WRITING ARRIVALS CONSTRAINTS" << endl;
		for(i=0;i<I;i++)
		{
			IloNumExpr expr(env);
			expr += rTime[i][0];
			
			label = "c_a_";
			label += itoa(i+1,tempstr,10);
			range.add(IloRange(env, this->arrivalTimes[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		
		cout << "WRITING RELEASE COMPLETION CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			for(j=0;j < J - 1;++j)
			{
				IloNumExpr expr(env);
				expr += rTime[i][j+1];
				expr -= y[i][j];
				label = "c_dis_part_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine
		cout << "WRITING PARTS SEQUENCING CONSTRAINTS" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=0;i < I - 1;++i)
			{				
				IloNumExpr expr(env);
				expr += st[i+1][j];
				expr -= y[i][j];

				label = "c_dis_mach_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		//Disjunctive constraint for each machine			
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (1)" << endl;
		for(j=1;j < J-1 ;++j)
		{
			for(i=this->_GPmys->psBaseStock[j]->capacity;i<this->_GPmys->psBaseStock[0]->capacity;i++)
			{					
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_init_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING STARTING DEPARTURE CONSTRAINTS (2)" << endl;
		for(j=0;j < J-1;++j)
		{
			for(i=this->_GPmys->psBaseStock[0]->capacity;i < I;++i)
			{
				
				IloNumExpr expr(env);
				expr -= st[i][j];
				expr += y[i][j];

				label = "c_dis_ech_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, this->processTimes[i][j],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();					
			}
		}
		cout << "WRITING START RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			for(j=0;j < J-1 ;++j)
			{
				IloNumExpr expr(env);
				expr -= rTime[i][j];
				expr += st[i][j];
				label = "c_dis_part2_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING DEMAND RELEASE CONSTRAINTS" << endl;
		for(i=0;i<I;++i)
		{
			IloNumExpr expr(env);
			expr += rTime[i][J-1];
			label = "c_demand_";
			label += itoa(i+1,tempstr,10);

			range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
			range[controw].setName(label.c_str());
			controw++;
			expr.end();
		}
		cout << "WRITING BASE STOCK CONSTRAINTS" << endl;
		for(j=0;j < J-1 ;++j)
		{
			for(i=0;i< I - this->_GPmys->psBaseStock[j]->capacity;++i)
			{
				IloNumExpr expr(env);
				expr += rTime[i+this->_GPmys->psBaseStock[j]->capacity][j];
				label = "c_BaseStock_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);

				range.add(IloRange(env, demandProcess[i],expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		cout << "WRITING KANBAN CONSTRAINTS - j=1,...,J-2" << endl;
		std::vector<int> installBS;//this represents the installation base stock at each stage BS(j)=E_BS(j)-E_BS(j+1)
		//installBS.resize(this->_GPmys->psBaseStock.size());
		for(int l=0;l<this->_GPmys->psBaseStock.size()-1;l++)
		{
			installBS.push_back(this->_GPmys->psBaseStock[l]->capacity-this->_GPmys->psBaseStock[l+1]->capacity);
		}
		installBS.push_back(this->_GPmys->psBaseStock[J-2]->capacity);

		for(j=0;j < J-1 ;j++)
		{	
			
			for(i=0;i<I-this->_GPmys->psKanban[j]->capacity;++i)
			{				
				IloNumExpr expr(env);
				
				expr += rTime[i+this->_GPmys->psKanban[j]->capacity][j];
				expr -= rTime[i][j+1];
				
				label = "c_Kanban_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				label += "_";
				label += itoa(k+1,tempstr,10);

				range.add(IloRange(env,0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
		for(j=0;j < J-1 ;++j)
		{
			for(i=0;i< I;++i)
			{
				
				IloNumExpr expr(env);
				expr += y[i][j];
				expr -= st[i][j];
				
				label = "c_st_yt_(1)_";
				label += itoa(i+1,tempstr,10);
				label += "_";
				label += itoa(j+1,tempstr,10);
				

				range.add(IloRange(env, 0,expr,+IloInfinity));
				range[controw].setName(label.c_str());
				controw++;
				expr.end();
			}
		}
	}
	mod.add(range);
}
void App_OpModel::Optimize(void)
{
	
	try {
   		/*IloCplex cplex(env);*/
		cplex=IloCplex(mod);
		/*std::ofstream fileout2;
		fileout2.open("OUTPUT/ModelloB.LP");*/
		//cplex.exportModel("OUTPUT/ModelloB.LP");
		cplex.setParam(IloCplex::EpRHS,0.000000001);
		cplex.setParam(IloCplex::RootAlg,IloCplex::Barrier);
		cplex.setParam(IloCplex::Threads,1);
		cplex.solve();
	} 
	catch (IloException& e) {
		std::cerr << "IloException: " << e << std::endl;
	} 
	catch (std::exception& e) 
	{
		std::cerr << "Standard exception: " << e.what() << std::endl;
	}/* catch {
		std::cerr << "Some other exception!" << std:.endl;
	}*/
}


void App_OpModel::writeOutput(std::ofstream & out_file, std::ofstream & out_TB,std::ofstream & outSumYSumS)//,/*, std::ofstream &fout2, std::ofstream &fout3*/IloCplex &cplex)
{
	int I(0);
	I=y.getSize();
	int J(0);
	J=y[0].getSize();
	int transitory(0);
	if(d>0)
		transitory=d;
	else
		transitory=1;

	if(this->_optObj==SIMULATION||this->_optObj==EXACT_SIM)
	{
		/*out_file << cplex.getValue(y[I-1][J-1]-y[d-1][J-1])/(I-d)<< endl;*/
		
		std::cout << std::endl;
		std::cout << "SERVICE RATE OBTAINED: " << cplex.getValue(y[I-1][J-1]-y[transitory-1][J-1])/(I-d) << std::endl;
		std::cout << "SERVICE RATE REQUESTED: " << this->sr << std::endl;
		/*std::cout << "Epsilon: " << cplex.getValue(epsilon) << endl;*/
		double res(0.0);
		float factor(0.0);
		float a(0.0);
		float b(0.0);
		for(int i=transitory-1;i<I;i++)
		{
			a=float(i+1);
			b=1/a;
			
			res = res + b*cplex.getValue(y[i][J-1]);
 		//	std::cout << b*cplex.getValue(y[i][J-1]) << std::endl;
			//std::cout << cplex.getValue(y[i][J-1]) << std::endl;
			//std::cout << b << std::endl;
		}
		res = res/(I-d);
		std::cout<< "Value of the service rate SAA: " << res << std::endl;
		/*for(int k=0;k<I;k++)
		{
			for(int j=0;j<J;j++)
			{
				out_file << cplex.getValue(y[k][j]) << " ";
			}
			out_file << std::endl;
		}*/
		out_file << res << endl;
		out_file << "Values of starting times: " << endl;
		int dimCostStages(0);
		/*if(iterationIndex==0)
		{
			std::ofstream outSumYSumS;
			outSumYSumS.open("OUTPUT\\sumYsumS.txt");
		}*/
		dimCostStages=this->cost_stage.size();
		/*if(dimCostStages>0)
		{
			*/
		double sumY(0.0);
		for(int i=0;i<this->I;i++)
		{
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				sumY=sumY+this->cplex.getValue(this->y[i][j]);
			}
		}
		outSumYSumS << sumY << " " << res << endl;
		/*}
		else
		{*/
		for(int i=0;i<this->I;i++)
		{
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				out_file << this->cplex.getValue(this->y[i][j])- this->processTimes[i][j] << " ";
			}
			out_file << endl;
		}
		/*}*/

		std::vector<double> yvec1;
		std::vector<double> yvec2;
		std::vector<int> zInfeas;
		std::vector<double> ptime;
		double avgWIP(0.0);
		std::vector<double> SimulatedQueue;
		for(int j=1;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(y[i][j-1]));
				yvec2.push_back(this->cplex.getValue(y[i][j]));
				ptime.push_back(this->processTimes[i][j]);

			}
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			out_file << avgWIP << " ";
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
		}

		out_file << std::endl;
		

	}
	if(this->_optObj==SIM_EXTENDED_KANBAN || this->_optObj==SIM_KANBAN || this->_optObj==SIM_BASESTOCK || this->_optObj==APP_SIM_TBCS || this->makesimNatwithCosts==1.0 || this->makesimNatwithCosts==4.0)
	{
		double res(0.0);
		double dem(0.0);
		double relTime(0.0);

		std::vector<double> wtIN;
		std::vector<double>wtOUT;
		double cycleTime(0.0);
		double systemTime(0.0);
		int countwtIN(0);
		wtIN.resize(this->_GPmys->psMachines.size());
		wtOUT.resize(this->_GPmys->psMachines.size());
		for(size_t i=transitory-1;i<this->I;i++)
		{
			res += cplex.getValue(rTime[i][J-1])-this->demandProcess[i];
			relTime += cplex.getValue(rTime[i][J-1]);
			dem += this->demandProcess[i];
			cycleTime = cycleTime + this->cplex.getValue(y[i][J-2]) - this->cplex.getValue(st[i][0]);
			systemTime = systemTime + this->cplex.getValue(rTime[i][J-1]) - this->cplex.getValue(rTime[i][0]);
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			for(int i=0;i<this->I;i++)
			{
				wtIN[j] = wtIN[j] + this->cplex.getValue(this->st[i][j])-this->cplex.getValue(this->rTime[i][j]);
				wtOUT[j] = wtOUT[j] + this->cplex.getValue(this->rTime[i][j+1])-this->cplex.getValue(this->y[i][j]);
			}
			wtIN[j] = (double(wtIN[j])/(double(this->I)));
			wtOUT[j] = (double(wtOUT[j])/(double(this->I)));
		}
		std::cout << std::endl;
		std::cout << "TOTAL LATENESS: " << res << std::endl;
		std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
		/*out_file << "TOTAL LATENESS: " << "AVERAGE LATENESS" << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTin_" << j+1 << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTOUT_" << j+1 << " ";
		}
		out_file << endl;*/
		int custOutLate=0;
		double ServiceLevel(0.0);
		int numparts(0);
		for(size_t i=transitory-1;i<this->I;i++)
		{
			if (cplex.getValue(rTime[i][J-1])-this->demandProcess[i] >0)
				custOutLate++;
			numparts++;
		}
		ServiceLevel=1-((double)(custOutLate))/((double)(numparts));
		out_file << ServiceLevel << " ";
		out_file << res << "    "  << res/(double(this->I-d)) << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtIN[j] << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtOUT[j] << " ";
		}
		
		std::vector<double> yvec1;
		std::vector<double> yvec2;
		std::vector<double> ptime;
		std::vector<int> zInfeas;
		std::vector<int> totInfeas;
		std::vector<std::vector<double> > QLevelSys;
		std::vector<std::vector<double> > QLevelStage;
		std::vector<double> SimulatedQueue;
		totInfeas.resize(this->_GPmys->psMachines.size()+1);
		/*std::vector<double> yvec11;
		std::vector<double> yvec21;
		std::vector<double> ptime1;*/
		double avgWIP(0.0);
		/*double avgWIP1(0.0);*/
		int numDataQueue(0);

		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			/*avgWIP1=0.0;*/
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(rTime[i][j]));
				yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));
				ptime.push_back(0.0);

				/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
				yvec21.push_back(this->cplex.getValue(y[i][j]));
				ptime1.push_back(this->processTimes[i][j]);*/

			}
			
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			if(SimulatedQueue.size()>numDataQueue)
				numDataQueue=SimulatedQueue.size();
			
			QLevelStage.resize(numDataQueue);
			for(int ll=0;ll<SimulatedQueue.size();ll++)
			{
				QLevelStage[ll].resize(j+1);
				QLevelStage[ll][j]=SimulatedQueue[ll];
			}
			this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
			QLevelSys.resize(QLevelStage.size());
			for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
			{
				int newSize=QLevelSys[qlInd].size()+2;
				QLevelSys[qlInd].resize(newSize);
				QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
				QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
			}
			/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/

			out_file << avgWIP << " ";
			if(j<this->_GPmys->psMachines.size()-1)
				totInfeas[j]=zInfeas[0];
			else
			{
				totInfeas[j]=zInfeas[0];
				totInfeas[j+1]=zInfeas[1];
			}
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
			QLevelStage.clear();

		}
		/*for(int zI=0;zI<totInfeas.size();zI++)
		{
			out_file << totInfeas[zI] << " ";
		}
		
		out_file << "CYCLE TIME: " << cycleTime/((double)(this->I)) << endl;
		out_file << "SYSTEM TIME: " << systemTime/((double)(this->I)) << endl;
		out_file << " ";*/
		if(this->cost_stage.size()>0)
		{
			double WTfunctCost(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->cplex.getValue(rTime[i][j-1]));
				}
			}
			out_file << " " << WTfunctCost << " ";
		}
		std::ofstream out_QueueL;
		out_QueueL.open("OUTPUT\\QUEUElevel.txt");
		for(int ll=0;ll<QLevelSys.size();ll++)
		{
			for(int mm=0;mm<QLevelSys[ll].size();mm++)
			{
				out_QueueL << QLevelSys[ll][mm] << " ";
			}
			out_QueueL << endl;
		}

		
		out_file << endl;
		out_QueueL.close();
		totInfeas.clear();
		yvec1.clear();
		yvec2.clear();
		ptime.clear();
		QLevelSys.clear();
		
		//double foVal(0.0);
		//for(int i=0;i<I;i++)
		//{
		//	for (int j = 0; j < rTime[0].getSize()-1;++j)
		//	{
		//		/*std::cout << this->cplex.getValue(this->rTime[i][j]) << " ";
		//		std::cout << this->cplex.getValue(this->st[i][j]) << " ";
		//		std::cout << this->cplex.getValue(this->y[i][j]) << " ";
		//		std::cout << this->cplex.getValue(this->rTime[i][j+1]) << " ";*/
		//		foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
		//	}
		//}
		//std::cout << foVal/I << endl;
		/*}*/
		/*std::cout << "Epsilon: " << cplex.getValue(epsilon) << endl;*/
		/*for(int k=0;k<I;k++)
		{
			for(int j=0;j<J;j++)
			{
				out_file << cplex.getValue(y[k][j]) << " ";
			}
			out_file << std::endl;
		}*/

	}
	if(this->_optObj==EXACT_SIM_KBS || this->_optObj==EXACT_SIM_KCS || this->_optObj==EXACT_SIM_BS)
	{
		double res(0.0);
		double dem(0.0);
		double relTime(0.0);
		std::vector<double> wtIN;
		std::vector<double>wtOUT;
		double cycleTime(0.0);
		double systemTime(0.0);
		int countwtIN(0);
		wtIN.resize(this->_GPmys->psMachines.size());
		wtOUT.resize(this->_GPmys->psMachines.size());
		for(size_t i=transitory-1;i<this->I;i++)
		{
			res += cplex.getValue(rTime[i][J-1])-this->demandProcess[i];
			relTime += cplex.getValue(rTime[i][J-1]);
			dem += this->demandProcess[i];
			cycleTime = cycleTime + this->cplex.getValue(y[i][J-2])-this->cplex.getValue(st[i][0]);
			systemTime = systemTime + this->cplex.getValue(rTime[i][J-1])-this->cplex.getValue(rTime[i][0]);
			
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			for(int i=0;i<this->I;i++)
			{
				wtIN[j] = wtIN[j] + this->cplex.getValue(this->st[i][j])-this->cplex.getValue(this->rTime[i][j]);
				wtOUT[j] = wtOUT[j] + this->cplex.getValue(this->rTime[i][j+1])-this->cplex.getValue(this->y[i][j]);
			}
			wtIN[j] = (double(wtIN[j])/(double(this->I)));
			wtOUT[j] = (double(wtOUT[j])/(double(this->I)));
		}
		std::cout << std::endl;
		std::cout << "TOTAL LATENESS: " << res << std::endl;
		std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
		/*out_file << "TOTAL LATENESS: " << "AVERAGE LATENESS" << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTin_" << j+1 << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTOUT_" << j+1 << " ";
		}
		out_file << endl;*/
		int custOutLate=0;
		double ServiceLevel(0.0);
		int numparts(0);
		for(size_t i=transitory-1;i<this->I;i++)
		{
			if (cplex.getValue(rTime[i][J-1])-this->demandProcess[i] >0)
				custOutLate++;
			numparts++;
		}
		ServiceLevel=1-((double)(custOutLate))/((double)(numparts));
		out_file << ServiceLevel << " ";
		out_file << res << "    "  << res/(double(this->I-d)) << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtIN[j] << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtOUT[j] << " ";
		}
		
		std::vector<double> yvec1;
		std::vector<double> yvec2;
		std::vector<double> ptime;
		std::vector<int> zInfeas;
		std::vector<int> totInfeas;
		std::vector<std::vector<double> > QLevelSys;
		std::vector<std::vector<double> > QLevelStage;
		std::vector<double> SimulatedQueue;
		totInfeas.resize(this->_GPmys->psMachines.size()+1);
		/*std::vector<double> yvec11;
		std::vector<double> yvec21;
		std::vector<double> ptime1;*/
		double avgWIP(0.0);
		/*double avgWIP1(0.0);*/

		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			/*avgWIP1=0.0;*/
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(rTime[i][j]));
				yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));
				ptime.push_back(0.0);

				/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
				yvec21.push_back(this->cplex.getValue(y[i][j]));
				ptime1.push_back(this->processTimes[i][j]);*/

			}
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
			QLevelSys.resize(QLevelStage.size());
			for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
			{
				int newSize=QLevelSys[qlInd].size()+2;
				QLevelSys[qlInd].resize(newSize);
				QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
				QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
			}
			/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/

			out_file << avgWIP << " ";
			
			if(j<this->_GPmys->psMachines.size()-1)
				totInfeas[j]=zInfeas[0];
			else
			{
				totInfeas[j]=zInfeas[0];
				totInfeas[j+1]=zInfeas[1];
			}
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
			QLevelStage.clear();

		}
		/*for(int zI=0;zI<totInfeas.size();zI++)
		{
			out_file << totInfeas[zI] << " ";
		}
		
		out_file << "CYCLE TIME: " << cycleTime/((double)(this->I)) << " ";
		out_file << "SYSTEM TIME: " << systemTime/((double)(this->I)) << " ";*/
		

		if(this->cost_stage.size()>0)
		{
			double WTfunctCost(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->cplex.getValue(rTime[i][j-1]));
				}
			}
			out_file << " " << WTfunctCost << " ";
		}
		std::ofstream out_QueueL;
		out_QueueL.open("OUTPUT\\QUEUElevel.txt");
		for(int ll=0;ll<QLevelSys.size();ll++)
		{
			for(int mm=0;mm<QLevelSys[ll].size();mm++)
			{
				out_QueueL << QLevelSys[ll][mm] << " ";
			}
			out_QueueL << endl;
		}

		out_file << std::endl;
		out_QueueL.close();
		totInfeas.clear();
		yvec1.clear();
		yvec2.clear();
		ptime.clear();
		QLevelSys.clear();

		
		/*out_file << res/(double(this->I-d)) << " " << (relTime-dem)/(double(this->I-d)) << endl;*/
		/*if(this->myItern<2)
		{*/
		/*for(int j=0; j<J-1;j++)
		{
			out_file << "z" << j+1 << " x" << j+1 << " y" << j+1 << " ";	
		}
		out_file <<  "z" << J << " D" << endl;
		for(int i=0;i<this->I;i++)
		{
			for(int j=0;j<J;j++)
			{
				if(j<J-1)
				{
					out_file << this->cplex.getValue(this->rTime[i][j]) << " ";
					out_file << this->cplex.getValue(this->st[i][j]) << " ";
					out_file << this->cplex.getValue(this->y[i][j]) << " ";
				}
				else
				{
					out_file << this->cplex.getValue(this->rTime[i][j]) << " ";
					out_file << this->demandProcess[i] << endl;
				}
			}
		}*/
	}

	
	if(this->_GPmys->sysType == FLOWLINE)
	{
		if(this->_optObj==OPTIMIZATION)
		{
			/*std::ofstream outSumYSumS;
			outSumYSumS.open("OUTPUT\\sumYsumS.txt");*/
			int myCapSize0(0);
			int myCapSize(0);
			double sumTB(0.0);
			myCapSize0 = this->mycap[0];
			for(int k=0;k<myCapSize0;k++)
			{
				myCapSize = this->mycap.size(); 
				for(int j=0;j<myCapSize;j++)
				{
					out_TB << cplex.getValue(x_s_b[k][j]) << " ";
					cout << this->cplex.getValue(x_s_b[k][j]) << " ";
					sumTB=sumTB+this->cplex.getValue(x_s_b[k][j]);
				}
				out_TB << endl;
				cout << endl;
			}
			int dimCostStages(0);
			dimCostStages=this->cost_stage.size();
			/*if(this->alphaLessi>0||dimCostStages>0)
			{*/
			double sumY(0.0);
			outSumYSumS << sumTB << " ";
			for(int i=0;i<this->I;i++)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
					sumY=sumY+this->cplex.getValue(y[i][j]);
			}
			double res(0.0);
			float factor(0.0);
			float a(0.0);
			float b(0.0);
			for(int i=transitory-1;i<I;i++)
			{
				a=float(i+1);
				b=1/a;
				
				res = res + b*cplex.getValue(y[i][J-1]);
 			//	std::cout << b*cplex.getValue(y[i][J-1]) << std::endl;
				//std::cout << cplex.getValue(y[i][J-1]) << std::endl;
				//std::cout << b << std::endl;
			}
			res = res/(I-d);
			outSumYSumS << sumY << " " << res; 
			/*outSumYSumS << endl;*/
			/*}*/
			double WTfunct(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<this->_GPmys->psMachines.size();j++)
				{
					WTfunct = WTfunct + this->cplex.getValue(y[i][j])-this->cplex.getValue(y[i][j-1]);
				}
			}
			outSumYSumS << " " << WTfunct;
			if(this->cost_stage.size()>0)
			{
				double WTfunctCost(0.0);
				for(int i=0;i<this->I;i++)
				{
					for(int j=1;j<this->_GPmys->psMachines.size();j++)
					{
						WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(y[i][j])-this->cplex.getValue(y[i][j-1]));
					}
				}
				outSumYSumS << " " << WTfunctCost;
			}
			outSumYSumS << endl;
			
		}
		else if(this->_optObj==EXACT_OPT)
		{
			int myCapSize0(0);
			int myCapSize(0);
			double sumTB(0.0);
			myCapSize0 = this->mycap[0];
			for(int k=0;k<myCapSize0;k++)
			{
				myCapSize = this->mycap.size(); 
				for(int j=0;j<myCapSize;j++)
				{
					if(cplex.getValue(this->z_buf[k][j])>0.001)
						sumTB=sumTB+(k+1);
					
				}
			}
			int dimCostStages(0);
			dimCostStages=this->cost_stage.size();
			/*if(this->alphaLessi>0||dimCostStages>0)
			{*/
			double sumY(0.0);
			outSumYSumS << sumTB << " ";
			for(int i=0;i<this->I;i++)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
					sumY=sumY+this->cplex.getValue(y[i][j]);
			}
			double res(0.0);
			float factor(0.0);
			float a(0.0);
			float b(0.0);
			for(int i=transitory-1;i<I;i++)
			{
				a=float(i+1);
				b=1/a;
				
				res = res + b*cplex.getValue(y[i][J-1]);
 			//	std::cout << b*cplex.getValue(y[i][J-1]) << std::endl;
				//std::cout << cplex.getValue(y[i][J-1]) << std::endl;
				//std::cout << b << std::endl;
			}
			res = res/(I-d);
			outSumYSumS << sumY << " " << res; 
			/*outSumYSumS << endl;*/
			/*}*/
			double WTfunct(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<this->_GPmys->psMachines.size();j++)
				{
					WTfunct = WTfunct + this->cplex.getValue(y[i][j])-this->cplex.getValue(y[i][j-1]);
				}
			}
			outSumYSumS << " " << WTfunct;
			if(this->cost_stage.size()>0)
			{
				double WTfunctCost(0.0);
				for(int i=0;i<this->I;i++)
				{
					for(int j=1;j<this->_GPmys->psMachines.size();j++)
					{
						WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(y[i][j])-this->cplex.getValue(y[i][j-1]));
					}
				}
				outSumYSumS << " " << WTfunctCost;
			}
			outSumYSumS << endl;
		}
	}
	if(this->_GPmys->sysType == CLOSEDLOOP)
	{
		if(this->_optObj==OPTIMIZATION)
		{
			for(int k=0;k<this->myPal;k++)
			{
				if(this->_myOFtype == MIN_s)
				{
					out_TB << cplex.getValue(x_s_p[k]) << " ";
					cout << this->cplex.getValue(x_s_p[k]) << " ";
				}
				else
					out_TB << cplex.getValue(x_b_p[k]) << " ";
			}
			out_TB << std::endl;
			cout << endl;
		}
	}
	if(this->_optObj==EXTENDED_KANBAN || this->_optObj==KANBAN || this->_optObj==BASESTOCK || APP_OPT_TBCS)
	{
		int myCapSize0(0);
		int myCapSize(0);
		myCapSize0 = this->mycap[0];
		if(this->_optObj==EXTENDED_KANBAN||this->_optObj==BASESTOCK)
		{
			out_TB << "BASESTOCK" << endl;
			
			for(int k=0;k<myCapSize0;k++)
			{
				myCapSize = this->mycap.size(); 
				for(int j=0;j<myCapSize;j++)
				{
					/*if(j<myCapSize-1)
					{
						out_TB << cplex.getValue(x_s_b[k][j]) - cplex.getValue(x_s_b[k][j+1]) << " ";
						cout << this->cplex.getValue(x_s_b[k][j]) - cplex.getValue(x_s_b[k][j+1]) << " ";
					}
					else
					{*/
					out_TB << cplex.getValue(x_s_b[k][j]) << " ";
					cout << this->cplex.getValue(x_s_b[k][j]) << " ";
					/*}*/
				}
				out_TB << std::endl;
				cout << endl;
			}
			out_TB <<endl;
			if(this->TB_kan.size()>0)
			{
				if(this->TB_kan[0].size()>0)
				{
					out_TB << "Auxuliary Time Buffer" << endl;
			
					for(int k=0;k<myCapSize0;k++)
					{
						myCapSize = this->mycap.size(); 
						for(int j=0;j<myCapSize;j++)
						{
							out_TB << cplex.getValue(x_s_k[k][j]) << " ";
							cout << this->cplex.getValue(x_s_k[k][j]) << " ";
						}
						out_TB << std::endl;
						cout << endl;
					}
					out_TB <<endl;
				}
			}
		}
		if(this->_optObj==EXTENDED_KANBAN||this->_optObj==KANBAN||this->_optObj==APP_OPT_TBCS)
		{
			out_TB << "KANBAN" << endl;
			double TBtot(0.0);
			double TTBtot(0.0);
			for(int k=0;k<myCapSize0;k++)
			{
				myCapSize = this->mycap.size(); 
				for(int j=0;j<myCapSize;j++)
				{
					out_TB << cplex.getValue(x_s_k[k][j]) << " ";
					cout << this->cplex.getValue(x_s_k[k][j]) << " ";
				}
				out_TB << std::endl;
				cout << endl;
			}
			/*if(this->makesimNatwithCosts!=4.0 && this->makesimNatwithCosts!=1.0)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{				
					TBtot=0.0;
					for(int k=0;k<myCapSize0;k++)
					{
						TBtot = TBtot + cplex.getValue(x_s_k[k][j]);
						TTBtot = TTBtot + cplex.getValue(x_s_k[k][j]);
					}
					out_file << TBtot << " ";
				}
				out_file << TTBtot;
			}
			out_file << endl;*/
		}
		if(this->_optObj==KANBAN)
		{
			int dimCostStages(0);
			dimCostStages=this->cost_stage.size();
			
			double sumTB(0.0);
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{				
				for(int k=0;k<myCapSize0;k++)
				{
					sumTB = sumTB + cplex.getValue(x_s_k[k][j]);
				}
			}
			double sumY(0.0);
			outSumYSumS << sumTB << " ";
			for(int i=0;i<this->I;i++)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
					sumY=sumY+this->cplex.getValue(y[i][j]);
			}
			
			double res(0.0);
			int custLate(0);
			for(int i=transitory-1;i<I;i++)
			{
				res = res + (cplex.getValue(rTime[i][J-1])-demandProcess[i]);
				if(cplex.getValue(rTime[i][J-1])-demandProcess[i]>0)
					custLate = custLate++;
			}
			res = res/((double)(I-transitory));
			outSumYSumS << sumY << " " << res << " " << (1.00-((double)(custLate))/((double)(I-transitory+1)))*100; 
			/*outSumYSumS << sumY << " " << res;*/ 
			
			double WTfunct(0.0);
			double WTptfunct(0.0);
			double minWT(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunct = WTfunct + this->cplex.getValue(rTime[i][j]) -this->cplex.getValue(rTime[i][j-1]);
					WTptfunct = WTptfunct + (this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]));
					if((this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]))<minWT)
						minWT=(this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]));
				}
			}
			outSumYSumS << " " << WTfunct << " " << WTptfunct << " " << minWT;
			outSumYSumS << " " << WTfunct/((double)(this->I)) << " " << WTptfunct/((double)(this->I));
			if(this->cost_stage.size()>0)
			{
				double WTfunctCost(0.0);
				for(int i=0;i<this->I;i++)
				{
					for(int j=1;j<J;j++)
					{
						WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->processTimes[i][j-1]-this->cplex.getValue(rTime[i][j-1]));
					}
				}
				outSumYSumS << " " << WTfunctCost;
			}
			outSumYSumS << endl;
			/*std::vector<double> wtIN;
			std::vector<double> wtOUT;
			wtIN.resize(this->_GPmys->psMachines.size());
			wtOUT.resize(this->_GPmys->psMachines.size());
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				for(int i=0;i<this->I;i++)
				{
					wtIN[j] = wtIN[j] + this->cplex.getValue(this->st[i][j])-this->cplex.getValue(this->rTime[i][j]);
					wtOUT[j] = wtOUT[j] + this->cplex.getValue(this->rTime[i][j+1])-this->cplex.getValue(this->y[i][j]);
				}
				wtIN[j] = (double(wtIN[j])/(double(this->I)));
				outSumYSumS << " " << wtIN[j];
				wtOUT[j] = (double(wtOUT[j])/(double(this->I)));
				outSumYSumS << " " << wtOUT[j];
			}*/
			/*for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << this->cplex.getValue(y[i][j]) << " ";
				}
				outSumYSumS << endl;
			}*/
			
		}
		if(this->_optObj==BASESTOCK)
		{
			int dimCostStages(0);
			dimCostStages=this->cost_stage.size();
			
			double sumTB(0.0);
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{				
				for(int k=0;k<myCapSize0;k++)
				{
					sumTB = sumTB + cplex.getValue(x_s_b[k][j]);
				}
			}
			double sumY(0.0);
			outSumYSumS << sumTB << " ";
			for(int i=0;i<this->I;i++)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
					sumY=sumY+this->cplex.getValue(y[i][j]);
			}
			
			double res(0.0);
			int custLate(0);
			for(int i=transitory-1;i<I;i++)
			{
				res = res + (cplex.getValue(rTime[i][J-1])-demandProcess[i]);
				if(cplex.getValue(rTime[i][J-1])-demandProcess[i]>0)
					custLate = custLate++;
			}
			res = res/((double)(I-transitory));
			outSumYSumS << sumY << " " << res << " " << (1.00-((double)(custLate))/((double)(I-transitory+1)))*100; 
			/*outSumYSumS << sumY << " " << res;*/ 
			std::vector<int> initCap;
			int tempinitCap=0;
			int maxCap=0;
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{	
				tempinitCap=0;
				for(int k=0;k<myCapSize0;k++)
				{
					if(cplex.getValue(x_s_b[k][j])>0)
						tempinitCap = tempinitCap + 1;
				}
				initCap.push_back(tempinitCap);
				if (tempinitCap>maxCap)
					maxCap=tempinitCap;
			}
			double WTfunct(0.0);
			double WTptfunct(0.0);
			double minWT(0.0);
			for(int i=maxCap;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunct = WTfunct + this->cplex.getValue(rTime[i][j]) -this->cplex.getValue(rTime[i][j-1]);
					WTptfunct = WTptfunct + (this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]));
					if((this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]))<minWT)
						minWT=(this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]));
				}
			}
			outSumYSumS << " " << WTfunct << " " << WTptfunct << " " << minWT;
			outSumYSumS << " " << WTfunct/((double)(this->I-maxCap)) << " " << WTptfunct/((double)(this->I-maxCap));
			if(this->cost_stage.size()>0)
			{
				double WTfunctCost(0.0);
				for(int i=0;i<this->I;i++)
				{
					for(int j=1;j<J;j++)
					{
						WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->processTimes[i][j-1]-this->cplex.getValue(rTime[i][j-1]));
					}
				}
				outSumYSumS << " " << WTfunctCost;
			}
			outSumYSumS << endl;
			//for(int i=0;i<this->I;i++)
			//{
			//	for(int j=0;j<this->_GPmys->psMachines.size();j++)
			//	{
			//		outSumYSumS << this->cplex.getValue(y[i][j]) << " ";
			//	}
			//	outSumYSumS << this->cplex.getValue(rTime[i][J-1]) << endl;
			//	//outSumYSumS << endl;
			//}
			
		}
		if(this->_optObj==EXTENDED_KANBAN)
		{
			int dimCostStages(0);
			dimCostStages=this->cost_stage.size();
			
			double sumTB(0.0);
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{				
				for(int k=0;k<myCapSize0;k++)
				{
					sumTB = sumTB + cplex.getValue(x_s_b[k][j]);
				}
			}
			outSumYSumS << sumTB << " ";
			sumTB=0.0;
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{				
				for(int k=0;k<myCapSize0;k++)
				{
					sumTB = sumTB + cplex.getValue(x_s_k[k][j]);
				}
			}
			outSumYSumS << sumTB << " ";
			double sumY(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
					sumY=sumY+this->cplex.getValue(y[i][j]);
			}
			
			double res(0.0);
			int custLate(0);
			for(int i=transitory-1;i<I;i++)
			{
				res = res + (cplex.getValue(rTime[i][J-1])-demandProcess[i]);
				if(cplex.getValue(rTime[i][J-1])-demandProcess[i]>0)
					custLate = custLate++;
			}
			res = res/((double)(I-transitory));
			outSumYSumS << sumY << " " << res << " " << (1.00-((double)(custLate))/((double)(I-transitory+1)))*100; 
			/*outSumYSumS << sumY << " " << res;*/ 
			
			std::vector<int> initCap;
			int tempinitCap=0;
			int maxCap=0;
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{	
				tempinitCap=0;
				for(int k=0;k<myCapSize0;k++)
				{
					if(cplex.getValue(x_s_b[k][j])>0)
						tempinitCap = tempinitCap + 1;
				}
				initCap.push_back(tempinitCap);
				if (tempinitCap>maxCap)
					maxCap=tempinitCap;
			}
			double WTfunct(0.0);
			double WTptfunct(0.0);
			double minWT(0.0);
			for(int i=maxCap;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunct = WTfunct + this->cplex.getValue(rTime[i][j]) -this->cplex.getValue(rTime[i][j-1]);
					WTptfunct = WTptfunct + (this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]));
					if((this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]))<minWT)
						minWT=(this->cplex.getValue(rTime[i][j]) - this->processTimes[i][j-1] - this->cplex.getValue(rTime[i][j-1]));
				}
			}
			outSumYSumS << " " << WTfunct << " " << WTptfunct << " " << minWT;
			outSumYSumS << " " << WTfunct/((double)(this->I-maxCap)) << " " << WTptfunct/((double)(this->I-maxCap));
			if(this->cost_stage.size()>0)
			{
				double WTfunctCost(0.0);
				for(int i=0;i<this->I;i++)
				{
					for(int j=1;j<J;j++)
					{
						WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->processTimes[i][j-1]-this->cplex.getValue(rTime[i][j-1]));
					}
				}
				outSumYSumS << " " << WTfunctCost;
			}
			outSumYSumS << endl;
			/*for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << this->cplex.getValue(y[i][j])-this->processTimes[i][j]-this->cplex.getValue(y[i][j-1]) << " ";
				}
				outSumYSumS << endl;
			}*/
			
		}
	}
	if(this->_optObj==EXACT_OPT_BSC)
	{
		int myCapSize0(0);
		int myCapSize(0);
		myCapSize0 = this->mycap[0];

		//out_TB << "BASESTOCK" << endl;
		
		myCapSize = this->mycap.size();
		for(int j=0;j<myCapSize;j++)
		{ 
			for(int k=0;k<myCapSize0;k++)
			{
				if(cplex.getValue(z_bs[k][j])>0.001)
				{
					out_TB << k << " ";
					cout << k << " ";
				}
				
			}
			//out_TB << std::endl;
		}
		out_TB << std::endl;
		cout << endl;
	}
	if(this->_optObj==EXACT_OPT_KSC)
	{
		int myCapSize0(0);
		int myCapSize(0);
		myCapSize0 = this->mycap[0];

		//out_TB << "KANBAN" << endl;
		
		myCapSize = this->mycap.size();
		for(int j=0;j<myCapSize;j++)
		{ 
			for(int k=0;k<myCapSize0;k++)
			{
				if(cplex.getValue(z_ks[k][j])>0.001)
				{
					out_TB << k+1 << " ";
					cout << k+1 << " ";
				}
				
			}
			//out_TB << std::endl;
		}
		out_TB << std::endl;
		cout << endl;
		
		int dimCostStages(0);
		dimCostStages=this->cost_stage.size();
		
		double sumTB(0.0);
		for(int j=0;j<myCapSize;j++)
		{ 
			for(int k=0;k<myCapSize0;k++)
			{
				if(cplex.getValue(z_ks[k][j])>0.001)
				{
					sumTB = sumTB + (k+1);
				}				
			}
		}
		double sumY(0.0);
		outSumYSumS << sumTB << " ";
		for(int i=0;i<this->I;i++)
		{
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
				sumY=sumY+this->cplex.getValue(y[i][j]);
		}
		double res(0.0);
		int custLate(0);
		for(int i=transitory-1;i<I;i++)
		{
			res = res + (cplex.getValue(rTime[i][J-1])-demandProcess[i]);
			if(cplex.getValue(rTime[i][J-1])-demandProcess[i]>0)
				custLate = custLate++;
		}
		res = res/((double)(I-transitory));
		outSumYSumS << sumY << " " << res << " " << ((double)(custLate))/((double)(I-transitory));
		
		double WTfunct(0.0);
		for(int i=0;i<this->I;i++)
		{
			for(int j=1;j<J;j++)
			{
				WTfunct = WTfunct + this->cplex.getValue(rTime[i][j])-this->cplex.getValue(rTime[i][j-1]);
			}
		}
		outSumYSumS << " " << WTfunct;
		if(this->cost_stage.size()>0)
		{
			double WTfunctCost(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->cplex.getValue(rTime[i][j-1]));
				}
			}
			outSumYSumS << " " << WTfunctCost;
		}
		outSumYSumS << endl;
		
	}
	if(this->_optObj==EXACT_OPT_EKCS)
	{
		int myCapSize0(0);
		int myCapSize(0);
		myCapSize0 = this->mycap[0];

		out_TB << "KANBAN" << endl;
		
		myCapSize = this->mycap.size();
		for(int j=0;j<myCapSize;j++)
		{ 
			for(int k=0;k<myCapSize0;k++)
			{
				if(cplex.getValue(z_ks[k][j])>0.001)
				{
					out_TB << k << " ";
					cout << k << " ";
				}
				
			}
			out_TB << std::endl;
		}
		out_TB << std::endl;
		cout << endl;

		out_TB << "BASESTOCK" << endl;
		
		myCapSize = this->mycap.size();
		for(int j=0;j<myCapSize;j++)
		{ 
			for(int k=0;k<myCapSize0;k++)
			{
				if(cplex.getValue(z_bs[k][j])>0.001)
				{
					out_TB << k << " ";
					cout << k << " ";
				}
				
			}
			out_TB << std::endl;
		}
		out_TB << std::endl;
		cout << endl;
	}
	/*out_file << " SOLUTION TIME: "<< this->cplex.getTime() << endl;*/
	
	//if(this->_deoScope==ONLYOPTIMIZATION)
	//{
	//	int appSol(0);
	//	bool appsolFound=false;
	//	std::vector<int> appSolVec;
	//	if(this->TB_bs.size()>0)
	//	{
	//		for(size_t k=0;k<this->TB_bs[0].size();k++)
	//		{								
	//			size_t l=0;
	//			appsolFound=false;
	//			while(appsolFound==false && l < this->TB_bs.size())
	//			{
	//				if(this->TB_bs[l][k]==0)
	//				{
	//					appSol = l;
	//					appSolVec.push_back(l);
	//					appsolFound=true;
	//				}
	//				else
	//					l++;
	//			}
	//		}
	//		for(int l=0;l<appSolVec.size();l++)
	//		{
	//			if(l<appSolVec.size()-1)
	//			{
	//				out_of << appSolVec[l] - appSolVec[l+1] << " ";
	//			}
	//			else
	//			{
	//				out_of << appSolVec[l] << " ";
	//			}
	//		}
	//	}
	//	appsolFound = false;
	//	if(this->_GPmys->sysType==FLOWLINE)
	//	{
	//		for(size_t k=0;k<this->_GPmys->TB_cap[0].size();k++)
	//		{								
	//			size_t l=0;
	//			appsolFound=false;
	//			while(appsolFound==false && l < this->_GPmys->TB_cap.size())
	//			{
	//				if(this->_GPmys->TB_cap[l][k]==0)
	//				{
	//					appSol = l+1;
	//					appSolVec.push_back(l);
	//					appsolFound=true;
	//				}
	//				else
	//					l++;
	//			}
	//		}
	//		for(int l=0;l<appSolVec.size();l++)
	//		{
	//			out_of << appSolVec[l] << " ";
	//		}
	//	}
	//	appsolFound = false;
	//	if(this->_GPmys->sysType==CLOSEDLOOP)
	//	{								
	//		size_t l=0;
	//		appsolFound=false;
	//		while(appsolFound==false && l < this->_GPmys->TB_cap.size())
	//		{
	//			if(this->_GPmys->TB_cap[l][0]==0)
	//			{
	//				appSol = l+1;
	//				appsolFound=true;
	//			}
	//			else
	//				l++;
	//		}
	//		
	//		out_of << appSol << " ";
	//	}
	//	appsolFound = false;

	//	int l=0;
	//	if(this->TB_kan.size()>0)
	//	{
	//		for(size_t k=0;k<this->TB_kan[0].size();k++)
	//		{
	//			appsolFound=false;
	//			while(appsolFound==false && l < this->TB_kan.size())
	//			{
	//				if(this->TB_kan[l][k]==0)
	//				{
	//					appSol = l+1;
	//					appsolFound=true;
	//					out_of << appSol << " ";
	//				}
	//				else
	//					l++;
	//			}
	//		}
	//	}
	//	/*}*/
	//	out_of << endl;
	//}
}
bool App_OpModel::verifySolution()
{
	int dimX(0);
	int dimY(0);
	dimX = this->rTime[0].getSize();
	dimY = this->rTime.getSize();
	bool verifFAILED=false;
	int i(0);
	int j(0);
	double zVal(0.0);
	double xVal(0.0);
	double yVal(0.0);

	while(i<dimY && verifFAILED==false)
	{
		j=0;
		while(j<dimX && verifFAILED==false)
		{
			zVal=this->cplex.getValue(rTime[i][j]);
			if(j<dimX-1)
			{
				xVal=this->cplex.getValue(st[i][j]);
				yVal=this->cplex.getValue(y[i][j]);
			}
			else
			{
				xVal=0.0;
				yVal=0.0;
			}
			if(zVal<0.0 || xVal<0.0 || yVal<0.0)
				verifFAILED = true;
			else
				j++;
		}
		i++;
	}

	if(verifFAILED==true)
		return true;
	else
		return false;
}
void App_OpModel::writeOutputSimulation(std::ofstream & out_file, std::ofstream & outSumYSumS)
{
	int I(0);
	I=y.getSize();
	int J(0);
	J=y[0].getSize();
	int transitory(0);
	if(d>0)
		transitory=d;
	else
		transitory=1;
	if(this->_optObj==SIMULATION||this->_optObj==EXACT_SIM)
	{
		/*out_file << cplex.getValue(y[I-1][J-1]-y[d-1][J-1])/(I-d)<< endl;*/
		
		std::cout << std::endl;
		std::cout << "SERVICE RATE OBTAINED: " << cplex.getValue(y[I-1][J-1]-y[transitory-1][J-1])/(I-d) << std::endl;
		std::cout << "SERVICE RATE REQUESTED: " << this->sr << std::endl;
		/*std::cout << "Epsilon: " << cplex.getValue(epsilon) << endl;*/
		double res(0.0);
		float factor(0.0);
		float a(0.0);
		float b(0.0);
		for(int i=transitory-1;i<I;i++)
		{
			a=float(i+1);
			b=1/a;
			
			res = res + b*cplex.getValue(y[i][J-1]);
 		//	std::cout << b*cplex.getValue(y[i][J-1]) << std::endl;
			//std::cout << cplex.getValue(y[i][J-1]) << std::endl;
			//std::cout << b << std::endl;
		}
		res = res/(I-d);
		std::cout<< "Value of the service rate SAA: " << res << std::endl;
		/*for(int k=0;k<I;k++)
		{
			for(int j=0;j<J;j++)
			{
				out_file << cplex.getValue(y[k][j]) << " ";
			}
			out_file << std::endl;
		}*/
		out_file << res << endl;
		out_file << "Values of starting times: " << endl;
		
		for(int i=0;i<this->I;i++)
		{
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				out_file << this->cplex.getValue(this->y[i][j])- this->processTimes[i][j] << " ";
			}
			out_file << endl;
		}
		/*std::ofstream outSumYSumS;
		outSumYSumS.open("OUTPUT\\sumYsumS.txt");*/
		double sumY(0.0);

		for(int i=0;i<this->I;i++)
		{
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				sumY=sumY+this->cplex.getValue(this->y[i][j]);
			}
		}
		outSumYSumS << sumY << " " << res;
		double WTfunct(0.0);
		for(int i=0;i<this->I;i++)
		{
			for(int j=1;j<this->_GPmys->psMachines.size();j++)
			{
				WTfunct = WTfunct + this->cplex.getValue(y[i][j])-this->cplex.getValue(y[i][j-1]);
			}
		}
		outSumYSumS << " " << WTfunct;
		if(this->cost_stage.size()>0)
		{
			double WTfunctCost(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<this->_GPmys->psMachines.size();j++)
				{
					WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(y[i][j])-this->cplex.getValue(y[i][j-1]));
				}
			}
			outSumYSumS << " " << WTfunctCost;
		}

		outSumYSumS << endl;
		if(this->makeSA==1)
		{
			IloNumArray rHSlow(env);
			IloNumArray rHSUp(env);
			this->cplex.getRHSSA(rHSlow,rHSUp,this->range);
			for(int k=this->contRowFirstTBconst;k<=this->contRowLastTBconst;k++)
			{
				outSumYSumS << this->ptRHStbCuts[k-this->contRowFirstTBconst] << " " << this->tbRHStbCuts[k-this->contRowFirstTBconst] << " " << rHSlow[k] << " " << rHSUp[k] << endl;
			}
		}


		std::vector<double> yvec1;
		std::vector<double> yvec2;
		std::vector<double> ptime;
		std::vector<double> SimulatedQueue;
		std::vector<int> zInfeas;
		double avgWIP(0.0);
		for(int j=1;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(y[i][j-1]));
				yvec2.push_back(this->cplex.getValue(y[i][j]));
				ptime.push_back(this->processTimes[i][j]);
			}
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			out_file << avgWIP << " ";
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
		}
	}
	if(this->_optObj==SIM_EXTENDED_KANBAN || this->_optObj==SIM_KANBAN || this->_optObj==SIM_BASESTOCK || this->_optObj==APP_SIM_TBCS)
	{
		double res(0.0);
		double dem(0.0);
		double relTime(0.0);
		std::vector<double> wtIN;
		std::vector<double>wtOUT;
		int countwtIN(0);
		wtIN.resize(this->_GPmys->psMachines.size());
		wtOUT.resize(this->_GPmys->psMachines.size());
		for(size_t i=transitory-1;i<this->I;i++)
		{
			res += cplex.getValue(rTime[i][J-1])-this->demandProcess[i];
			relTime += cplex.getValue(rTime[i][J-1]);
			dem += this->demandProcess[i];
			
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			for(int i=0;i<this->I;i++)
			{
				wtIN[j] = wtIN[j] + this->cplex.getValue(this->st[i][j])-this->cplex.getValue(this->rTime[i][j]);
				wtOUT[j] = wtOUT[j] + this->cplex.getValue(this->rTime[i][j+1])-this->cplex.getValue(this->y[i][j]);
			}
			wtIN[j] = (double(wtIN[j])/(double(this->I)));
			wtOUT[j] = (double(wtOUT[j])/(double(this->I)));
		}
		std::cout << std::endl;
		std::cout << "TOTAL LATENESS: " << res << std::endl;
		std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
		/*out_file << "TOTAL LATENESS: " << "AVERAGE LATENESS" << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTin_" << j+1 << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTOUT_" << j+1 << " ";
		}
		out_file << endl;*/
		int custOutLate=0;
		double ServiceLevel(0.0);
		int numparts(0);
		for(size_t i=transitory-1;i<this->I;i++)
		{
			if (cplex.getValue(rTime[i][J-1])-this->demandProcess[i] >0)
				custOutLate++;
			numparts++;
		}
		ServiceLevel=1-((double)(custOutLate))/((double)(numparts));
		out_file << ServiceLevel << " ";
		out_file << res << "    "  << res/(double(this->I-d)) << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtIN[j] << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtOUT[j] << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << wtIN[j]+wtOUT[j] << " ";
		}
		
		std::vector<double> yvec1;
		std::vector<double> yvec2;
		std::vector<double> ptime;
		std::vector<int> zInfeas;
		std::vector<double> SimulatedQueue;
		/*
		std::vector<int> totInfeas;
		std::vector<std::vector<double> > QLevelSys;
		std::vector<std::vector<double> > QLevelStage;*/
		/*totInfeas.resize(this->_GPmys->psMachines.size()+1);*/
		/*std::vector<double> yvec11;
		std::vector<double> yvec21;
		std::vector<double> ptime1;*/
		double avgWIP(0.0);
		/*double avgWIP1(0.0);*/

		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			/*avgWIP1=0.0;*/
			for(int i=0;i<this->I;i++)
			{
				/*yvec1.push_back(this->cplex.getValue(rTime[i][j]));*/
				yvec1.push_back(this->cplex.getValue(rTime[i][j]));
				yvec2.push_back(this->cplex.getValue(st[i][j]));
				/*yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));*/
				ptime.push_back(0.0);

				/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
				yvec21.push_back(this->cplex.getValue(y[i][j]));
				ptime1.push_back(this->processTimes[i][j]);*/

			}
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			out_file << avgWIP << " ";
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
			/*this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
			QLevelSys.resize(QLevelStage.size());
			for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
			{
				int newSize=QLevelSys[qlInd].size()+2;
				QLevelSys[qlInd].resize(newSize);
				QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
				QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
			}*/
			/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/
			/*if(j<this->_GPmys->psMachines.size()-1)
				totInfeas[j]=zInfeas[0];
			else
			{
				totInfeas[j]=zInfeas[0];
				totInfeas[j+1]=zInfeas[1];
			}
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			
			QLevelStage.clear();*/

		}
		
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			/*avgWIP1=0.0;*/
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(y[i][j]));
				yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));
				ptime.push_back(0.0);

				/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
				yvec21.push_back(this->cplex.getValue(y[i][j]));
				ptime1.push_back(this->processTimes[i][j]);*/

			}
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			/*this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
			QLevelSys.resize(QLevelStage.size());
			for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
			{
				int newSize=QLevelSys[qlInd].size()+2;
				QLevelSys[qlInd].resize(newSize);
				QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
				QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
			}*/
			/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/

			out_file << avgWIP << " ";
			/*if(j<this->_GPmys->psMachines.size()-1)
				totInfeas[j]=zInfeas[0];
			else
			{
				totInfeas[j]=zInfeas[0];
				totInfeas[j+1]=zInfeas[1];
			}*/
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
			/*zInfeas.clear();
			QLevelStage.clear();*/

		}
		/*std::vector<double> SimulatedQueue;*/
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			/*avgWIP1=0.0;*/
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(rTime[i][j]));
				yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));
				ptime.push_back(0.0);

				/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
				yvec21.push_back(this->cplex.getValue(y[i][j]));
				ptime1.push_back(this->processTimes[i][j]);*/

			}
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			/*this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
			QLevelSys.resize(QLevelStage.size());
			for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
			{
				int newSize=QLevelSys[qlInd].size()+2;
				QLevelSys[qlInd].resize(newSize);
				QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
				QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
			}*/
			/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/

			out_file << avgWIP << " ";
			/*if(j<this->_GPmys->psMachines.size()-1)
				totInfeas[j]=zInfeas[0];
			else
			{
				totInfeas[j]=zInfeas[0];
				totInfeas[j+1]=zInfeas[1];
			}*/
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
			/*zInfeas.clear();
			QLevelStage.clear();*/

		}
		std::vector<double> zVec;
		ServiceLevel=0.0;
		for(int zV=0;zV<this->rTime.getSize();zV++)
		{
			zVec.push_back(this->cplex.getValue(rTime[zV][this->_GPmys->psMachines.size()]));
		}		
		ServiceLevel = this->computeServiceLevel(zVec,this->demandProcess);
		out_file << ServiceLevel << " ";

		/*for(int zI=0;zI<totInfeas.size();zI++)
		{
			out_file << totInfeas[zI] << " ";
		}*/
		
		/*std::ofstream out_QueueL;
		out_QueueL.open("OUTPUT\\QUEUElevel.txt");
		for(int ll=0;ll<QLevelSys.size();ll++)
		{
			for(int mm=0;mm<QLevelSys[ll].size();mm++)
			{
				out_QueueL << QLevelSys[ll][mm] << " ";
			}
			out_QueueL << endl;
		}*/

		/*out_file << std::endl;*/
		/*out_QueueL.close();
		totInfeas.clear();*/
		yvec1.clear();
		yvec2.clear();
		ptime.clear();
		zInfeas.clear();
		/*QLevelSys.clear();*/
		zVec.clear();
		SimulatedQueue.clear();

		if(this->_optObj==SIM_KANBAN || this->_optObj==SIM_BASESTOCK || this->_optObj==SIM_EXTENDED_KANBAN)
		{
			double res(0.0);
			double dem(0.0);
			double relTime(0.0);
			std::vector<double> wtIN;
			std::vector<double>wtOUT;
			double cycleTime(0.0);
			double systemTime(0.0);
			int countwtIN(0);
			wtIN.resize(this->_GPmys->psMachines.size());
			wtOUT.resize(this->_GPmys->psMachines.size());
			for(size_t i=transitory-1;i<this->I;i++)
			{
				res += cplex.getValue(rTime[i][J-1])-this->demandProcess[i];
				relTime += cplex.getValue(rTime[i][J-1]);
				dem += this->demandProcess[i];
				cycleTime = cycleTime + this->cplex.getValue(y[i][J-2])-this->cplex.getValue(st[i][0]);
				systemTime = systemTime + this->cplex.getValue(rTime[i][J-1])-this->cplex.getValue(rTime[i][0]);
				
			}
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				for(int i=0;i<this->I;i++)
				{
					wtIN[j] = wtIN[j] + this->cplex.getValue(this->st[i][j])-this->cplex.getValue(this->rTime[i][j]);
					wtOUT[j] = wtOUT[j] + this->cplex.getValue(this->rTime[i][j+1])-this->cplex.getValue(this->y[i][j]);
				}
				wtIN[j] = (double(wtIN[j])/(double(this->I)));
				wtOUT[j] = (double(wtOUT[j])/(double(this->I)));
			}
			std::cout << std::endl;
			std::cout << "TOTAL LATENESS: " << res << std::endl;
			std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
			/*out_file << "TOTAL LATENESS: " << "AVERAGE LATENESS" << " ";
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				out_file << "WTin_" << j+1 << " ";
			}
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				out_file << "WTOUT_" << j+1 << " ";
			}
			out_file << endl;*/
			int custOutLate=0;
			double ServiceLevel(0.0);
			int numparts(0);
			for(size_t i=transitory-1;i<this->I;i++)
			{
				if (cplex.getValue(rTime[i][J-1])-this->demandProcess[i] >0)
					custOutLate++;
				numparts++;
			}
			ServiceLevel=1-((double)(custOutLate))/((double)(numparts));
			outSumYSumS << ServiceLevel << " ";
			outSumYSumS << res << "    "  << res/(double(this->I-d)) << " ";
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				outSumYSumS << wtIN[j] << " ";
			}
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				outSumYSumS << wtOUT[j] << " ";
			}
			
			std::vector<double> yvec1;
			std::vector<double> yvec2;
			std::vector<double> ptime;
			std::vector<int> zInfeas;
			std::vector<int> totInfeas;
			std::vector<std::vector<double> > QLevelSys;
			std::vector<std::vector<double> > QLevelStage;
			std::vector<double> SimulatedQueue;
			totInfeas.resize(this->_GPmys->psMachines.size()+1);
			/*std::vector<double> yvec11;
			std::vector<double> yvec21;
			std::vector<double> ptime1;*/
			double avgWIP(0.0);
			/*double avgWIP1(0.0);*/

			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				avgWIP=0.0;
				/*avgWIP1=0.0;*/
				for(int i=0;i<this->I;i++)
				{
					yvec1.push_back(this->cplex.getValue(rTime[i][j]));
					yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));
					ptime.push_back(0.0);

					/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
					yvec21.push_back(this->cplex.getValue(y[i][j]));
					ptime1.push_back(this->processTimes[i][j]);*/

				}
				
				avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
				this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
				QLevelSys.resize(QLevelStage.size());
				for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
				{
					int newSize=QLevelSys[qlInd].size()+2;
					QLevelSys[qlInd].resize(newSize);
					QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
					QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
				}
				/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/

				outSumYSumS << avgWIP << " ";
				
				if(j<this->_GPmys->psMachines.size()-1)
					totInfeas[j]=zInfeas[0];
				else
				{
					totInfeas[j]=zInfeas[0];
					totInfeas[j+1]=zInfeas[1];
				}
				yvec1.clear();
				yvec2.clear();
				ptime.clear();
				zInfeas.clear();
				QLevelStage.clear();

			}
			/*for(int zI=0;zI<totInfeas.size();zI++)
			{
				out_file << totInfeas[zI] << " ";
			}
			
			out_file << "CYCLE TIME: " << cycleTime/((double)(this->I)) << " ";
			out_file << "SYSTEM TIME: " << systemTime/((double)(this->I)) << " ";*/
			

			if(this->cost_stage.size()>0)
			{
				double WTfunctCost(0.0);
				for(int i=0;i<this->I;i++)
				{
					for(int j=1;j<J;j++)
					{
						WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->cplex.getValue(rTime[i][j-1]));
					}
				}
				outSumYSumS << " " << WTfunctCost << " ";
			}
			std::ofstream out_QueueL;
			out_QueueL.open("OUTPUT\\QUEUElevel.txt");
			for(int ll=0;ll<QLevelSys.size();ll++)
			{
				for(int mm=0;mm<QLevelSys[ll].size();mm++)
				{
					out_QueueL << QLevelSys[ll][mm] << " ";
				}
				out_QueueL << endl;
			}

			outSumYSumS << std::endl;
			out_QueueL.close();
			totInfeas.clear();
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			QLevelSys.clear();
		}

	}
	if(this->_optObj==EXACT_SIM_KBS || this->_optObj==EXACT_SIM_KCS || this->_optObj==EXACT_SIM_BS)
	{
		double res(0.0);
		double dem(0.0);
		double relTime(0.0);
		std::vector<double> wtIN;
		std::vector<double>wtOUT;
		double cycleTime(0.0);
		double systemTime(0.0);
		int countwtIN(0);
		wtIN.resize(this->_GPmys->psMachines.size());
		wtOUT.resize(this->_GPmys->psMachines.size());
		for(size_t i=transitory-1;i<this->I;i++)
		{
			res += cplex.getValue(rTime[i][J-1])-this->demandProcess[i];
			relTime += cplex.getValue(rTime[i][J-1]);
			dem += this->demandProcess[i];
			cycleTime = cycleTime + this->cplex.getValue(y[i][J-2])-this->cplex.getValue(st[i][0]);
			systemTime = systemTime + this->cplex.getValue(rTime[i][J-1])-this->cplex.getValue(rTime[i][0]);
			
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			for(int i=0;i<this->I;i++)
			{
				wtIN[j] = wtIN[j] + this->cplex.getValue(this->st[i][j])-this->cplex.getValue(this->rTime[i][j]);
				wtOUT[j] = wtOUT[j] + this->cplex.getValue(this->rTime[i][j+1])-this->cplex.getValue(this->y[i][j]);
			}
			wtIN[j] = (double(wtIN[j])/(double(this->I)));
			wtOUT[j] = (double(wtOUT[j])/(double(this->I)));
		}
		std::cout << std::endl;
		std::cout << "TOTAL LATENESS: " << res << std::endl;
		std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
		/*out_file << "TOTAL LATENESS: " << "AVERAGE LATENESS" << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTin_" << j+1 << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			out_file << "WTOUT_" << j+1 << " ";
		}
		out_file << endl;*/
		int custOutLate=0;
		double ServiceLevel(0.0);
		int numparts(0);
		for(size_t i=transitory-1;i<this->I;i++)
		{
			if (cplex.getValue(rTime[i][J-1])-this->demandProcess[i] >0)
				custOutLate++;
			numparts++;
		}
		ServiceLevel=1-((double)(custOutLate))/((double)(numparts));
		outSumYSumS << ServiceLevel << " ";
		outSumYSumS << res << "    "  << res/(double(this->I-d)) << " ";
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			outSumYSumS << wtIN[j] << " ";
		}
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			outSumYSumS << wtOUT[j] << " ";
		}
		
		std::vector<double> yvec1;
		std::vector<double> yvec2;
		std::vector<double> ptime;
		std::vector<int> zInfeas;
		std::vector<int> totInfeas;
		std::vector<std::vector<double> > QLevelSys;
		std::vector<std::vector<double> > QLevelStage;
		std::vector<double> SimulatedQueue;
		totInfeas.resize(this->_GPmys->psMachines.size()+1);
		/*std::vector<double> yvec11;
		std::vector<double> yvec21;
		std::vector<double> ptime1;*/
		double avgWIP(0.0);
		/*double avgWIP1(0.0);*/

		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			avgWIP=0.0;
			/*avgWIP1=0.0;*/
			for(int i=0;i<this->I;i++)
			{
				yvec1.push_back(this->cplex.getValue(rTime[i][j]));
				yvec2.push_back(this->cplex.getValue(rTime[i][j+1]));
				ptime.push_back(0.0);

				/*yvec11.push_back(this->cplex.getValue(rTime[i][j]));
				yvec21.push_back(this->cplex.getValue(y[i][j]));
				ptime1.push_back(this->processTimes[i][j]);*/

			}
			
			avgWIP = this->computeAvgQueue(yvec2,yvec1,ptime,zInfeas,SimulatedQueue);
			this->AnalyzeQlevel(yvec2,yvec1,ptime,zInfeas,QLevelStage);
			QLevelSys.resize(QLevelStage.size());
			for(int qlInd=0;qlInd<QLevelStage.size();qlInd++)
			{
				int newSize=QLevelSys[qlInd].size()+2;
				QLevelSys[qlInd].resize(newSize);
				QLevelSys[qlInd][newSize-2]=QLevelStage[qlInd][0];
				QLevelSys[qlInd][newSize-1]=QLevelStage[qlInd][1];
			}
			/*avgWIP1 = this->computeAvgQueue(yvec21,yvec11,ptime1);*/

			outSumYSumS << avgWIP << " ";
			
			if(j<this->_GPmys->psMachines.size()-1)
				totInfeas[j]=zInfeas[0];
			else
			{
				totInfeas[j]=zInfeas[0];
				totInfeas[j+1]=zInfeas[1];
			}
			yvec1.clear();
			yvec2.clear();
			ptime.clear();
			zInfeas.clear();
			QLevelStage.clear();

		}
		/*for(int zI=0;zI<totInfeas.size();zI++)
		{
			out_file << totInfeas[zI] << " ";
		}
		
		out_file << "CYCLE TIME: " << cycleTime/((double)(this->I)) << " ";
		out_file << "SYSTEM TIME: " << systemTime/((double)(this->I)) << " ";*/
		

		if(this->cost_stage.size()>0)
		{
			double WTfunctCost(0.0);
			for(int i=0;i<this->I;i++)
			{
				for(int j=1;j<J;j++)
				{
					WTfunctCost = WTfunctCost + this->cost_stage[j-1]*(this->cplex.getValue(rTime[i][j])-this->cplex.getValue(rTime[i][j-1]));
				}
			}
			outSumYSumS << " " << WTfunctCost << " ";
		}
		std::ofstream out_QueueL;
		out_QueueL.open("OUTPUT\\QUEUElevel.txt");
		for(int ll=0;ll<QLevelSys.size();ll++)
		{
			for(int mm=0;mm<QLevelSys[ll].size();mm++)
			{
				out_QueueL << QLevelSys[ll][mm] << " ";
			}
			out_QueueL << endl;
		}

		outSumYSumS << std::endl;
		out_QueueL.close();
		totInfeas.clear();
		yvec1.clear();
		yvec2.clear();
		ptime.clear();
		QLevelSys.clear();
	}
	//if(this->_deoScope==ONLYSIMULATION && this->_GPmys->sysType==SUPPLYCHAIN)
	//{
	//	if(this->myItern<2)
	//	{
	//		for(int j=0; j<J-1;j++)
	//		{
	//			out_file << "z" << j+1 << " x" << j+1 << " y" << j+1 << " ";	
	//		}
	//		/*for(int j=0; j<this->TB_kan.size();j++)
	//		{
	//			for(int k=0;k<this->TB_kan[j].size();k++)
	//			{
	//				if(this->TB_kan[j][k]>0)
	//					out_file << "z(i+" << j << k << ")+s" << j << " "; 
	//			}	
	//		}*/
	//		
	//		for(int indMach=0;indMach<J-1;indMach++)
	//		{
	//			for(int j=0; j<this->TB_kan.size();j++)
	//			{			
	//				if(this->TB_kan[j][indMach]>0)
	//					out_file <<"s(" << j+1 << "," << indMach <<")";	
	//			}
	//		}
	//		for(int indMach=0;indMach<J-1;indMach++)
	//		{
	//			for(int j=0; j<this->TB_kan.size();j++)
	//			{			
	//				if(this->TB_kan[j][indMach]>0)
	//					out_file <<"z(i+" << j <<"," << indMach << ")+s(" << j+1 << "," << indMach << ") "; 	
	//			}
	//		}
	//		
	//		out_file <<  "z" << J << " ";	
	//		out_file << " D" << endl;
	//	}
	//	else
	//		out_file << endl;
	//	for(int i=0;i<this->I;i++)
	//	{
	//		for(int j=0;j<J;j++)
	//		{
	//			if(j<J-1)
	//			{
	//				out_file << this->cplex.getValue(this->rTime[i][j]) << " ";
	//				out_file << this->cplex.getValue(this->st[i][j]) << " ";
	//				out_file << this->cplex.getValue(this->y[i][j]) << " ";
	//			}
	//			else
	//			{
	//				
	//				for(int indMach=0;indMach<J-1;indMach++)
	//				{
	//					for(int j=0; j<this->TB_kan.size();j++)
	//					{
	//						if(this->TB_kan[j][indMach]>0)
	//							out_file << this->TB_kan[j][indMach] << " ";
	//	
	//					}
	//				}
	//				for(int indMach=0;indMach<J-1;indMach++)
	//				{
	//					for(int j=0; j<this->TB_kan.size();j++)
	//					{
	//						if(this->TB_kan[j][indMach]>0 && (i+j+1<this->I))
	//							out_file << this->cplex.getValue(rTime[i+j+1][0])+this->TB_kan[j][indMach] << " ";
	//	
	//					}
	//				}
	//				out_file << this->cplex.getValue(this->rTime[i][J-1]) << " ";
	//				out_file << this->demandProcess[i] << endl;
	//			}
	//		}
	//	}
	//}
	//if(this->_optObj==SIMULATION)
	//{
	//	out_file << cplex.getValue(y[I-1][J-1]-y[transitory-1][J-1])/(I-(transitory-1))<< endl;
	//	std::cout << std::endl;
	//	std::cout << "SERVICE RATE OBTAINED: " << cplex.getValue(y[I-1][J-1]-y[transitory-1][J-1])/(I-d) << std::endl;
	//	std::cout << "SERVICE RATE REQUESTED: " << this->sr << std::endl;
	//	/*std::cout << "Epsilon: " << cplex.getValue(epsilon) << endl;*/
	//	double res(0.0);
	//	float factor(0.0);
	//	float a(0.0);
	//	float b(0.0);
	//	for(int i=transitory-1;i<I;i++)
	//	{
	//		a=float(i+1);
	//		b=1/a;
	//		
	//		res = res + b*cplex.getValue(y[i][J-1]);
	//	}
	//	res = res/(I-d);
	//	std::cout<< "Value of the service rate SAA: " << res << std::endl;
	//	/*if(I<=1000)
	//	{*/
	//	cout << "Writing x and y" << endl;
	//	for(int l=0;l<I;l++)
	//	{
	//		for(int m=0;m<J;m++)
	//		{
	//			out_file << cplex.getValue(y[l][m])-this->processTimes[l][m] << " ";
	//		}
	//		/*out_file<< endl;*/
	//		for(int m=0;m<J;m++)
	//		{
	//			out_file << cplex.getValue(y[l][m]) << " ";
	//		}
	//		out_file << endl;
	//	}
	//}
	///*}*/
	//if(this->_optObj==SIM_EXTENDED_KANBAN || this->_optObj==SIM_KANBAN || this->_optObj==SIM_BASESTOCK ||
	//	this->_optObj==EXACT_SIM_KBS || this->_optObj == EXACT_SIM_BS || this->_optObj == EXACT_SIM_KCS)
	//{
	//	double res(0.0);
	//	double dem(0.0);
	//	double relTime(0.0);
	//	for(size_t i=transitory-1;i<this->I;i++)
	//	{
	//		res += cplex.getValue(rTime[i][J-1])-this->demandProcess[i];
	//		relTime += cplex.getValue(rTime[i][J-1]);
	//		dem += this->demandProcess[i];
	//	}
	//	std::cout << std::endl;
	//	std::cout << "TOTAL LATENESS: " << res << std::endl;
	//	std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
	//	/*if(this->myItern<2)
	//	{*/
	//	if(!this->verifySolution())
	//	{
	//		out_file << res/(double(this->I-d)) << " " << (relTime-dem)/(double(this->I)) << endl;
	//		out_file << "z     " << "x       " << "y      "<< endl;
	//		for(int i=0;i<this->I;i++)
	//		{
	//			for(int j=0;j<this->_GPmys->psMachines.size();j++)
	//			{
	//				/*if(j<this->_GPmys->psMachines.size())
	//				{*/
	//				out_file << this->cplex.getValue(this->rTime[i][j]) << " ";
	//				out_file << this->cplex.getValue(this->st[i][j]) << " ";
	//				out_file << this->cplex.getValue(this->y[i][j]) << " ";
	//				/*}*/
	//				/*else
	//				{*/
	//				/*}*/
	//			}
	//			out_file << this->cplex.getValue(this->rTime[i][J-1]) << " ";
	//			out_file << this->demandProcess[i] << endl;

	//		}
	//	}
	//	/*}*/
	//	/*std::cout << "Epsilon: " << cplex.getValue(epsilon) << endl;*/
	//	/*for(int k=0;k<I;k++)
	//	{
	//		for(int j=0;j<J;j++)
	//		{
	//			out_file << cplex.getValue(y[k][j]) << " ";
	//		}
	//		out_file << std::endl;
	//	}*/
	//}
	///*if(this->_optObj==EXACT_SIM_KBS || this->_optObj==SIM_KANBAN || this->_optObj==SIM_BASESTOCK ||
	//	this->_optObj == EXACT_SIM_BS || this->_optObj == EXACT_SIM_KCS)
	//{
	//	for(int i=0;i<this->I;i++)
	//	{
	//		for(int j=0;j<this->_GPmys->psMachines.size();j++)
	//		{
	//			if(j<this->_GPmys->psMachines.size()-1)
	//			{
	//				out_file << this->cplex.getValue(this->rTime[i][j]) << " ";
	//				out_file << this->cplex.getValue(this->st[i][j]) << " ";
	//				out_file << this->cplex.getValue(this->y[i][j]) << " ";
	//			}
	//			else
	//			{
	//				out_file << this->cplex.getValue(this->rTime[i][j]) << " ";
	//				out_file << this->demandProcess[i] << endl;
	//			}
	//		}
	//	}
	//}*/
	//else if(this->_optObj==EXACT_SIM)
	//{
	//	for(int i=0;i<this->I;i++)
	//	{
	//		for(int j=0;j<this->_GPmys->psMachines.size();j++)
	//		{
	//			out_file << this->cplex.getValue(this->y[i][j])-this->processTimes[i][j] << " ";
	//			out_file << this->cplex.getValue(this->y[i][j]) << " ";
	//		}
	//		out_file << endl;
	//	}
	//	
	//}
}
void App_OpModel::writeReplicateResults(std::ofstream &out_resultsFile, int rep)
{
	out_resultsFile << "ENTITY STATISTICS" <<endl;
	out_resultsFile << "Relication: " << rep+1 << endl;
	double av_systemTime(0.0);
	double min_systemTime(0.0);
	double max_systemTime(0.0);

	double av_waitingTime(0.0);
	double min_waitingTime(1.0);
	double max_waitingTime(0.0);

	double av_throughput(0.0);

	int num_entity_processed(0);
	int numST(0);
	if(this->_optObj!=SIM_EXTENDED_KANBAN&&this->_optObj!=EXACT_SIM_KBS &&
		this->_optObj!=EXACT_SIM_KCS && this->_optObj!=EXACT_SIM_BS)
		numST=this->_GPmys->psMachines.size();
	else
		numST=this->_GPmys->psMachines.size()-1;

	/*cout << this->I << endl;
	getchar();*/
	
	double temp_y_cum(0.0);
	double temp_y(0.0);
	
	for(size_t i=0;i<this->I;i++)
	{
		//cout << this->cplex.getValue(this->y[0][2]) << endl;
		temp_y = this->cplex.getValue(this->y[i][numST-1]) - (this->cplex.getValue(this->y[i][0])-this->processTimes[i][0]);
		if(max_systemTime<=temp_y)
			max_systemTime = temp_y;
		if((min_systemTime == 0.0) || (temp_y <= min_systemTime))
			min_systemTime = temp_y;
		temp_y_cum = temp_y_cum + temp_y;
	}
	av_systemTime = temp_y_cum/double(this->I);

	//WRITING...
	out_resultsFile << "		   " << "		   " << "AVERAGE" << "		   " << "MIN" << "		   " << "MAX" << endl;
	out_resultsFile << endl;
	out_resultsFile.precision(5);
	out_resultsFile << "System Time" << "		   " << fixed << av_systemTime << "		   " << min_systemTime << "		   " << max_systemTime << endl;
	
	temp_y = 0.0;
	temp_y_cum = 0.0;
	max_waitingTime=0.0;
	min_waitingTime=0.0;
	av_waitingTime=0.0;
	double idleTime = 0.0;
	double busyTime = 0.0;
	double pbusyTime = 0.0;
	double pidleTime = 0.0;

	for(size_t j=0;j<numST;j++)
	{
		temp_y=0.0;
		temp_y_cum = 0.0;
		max_waitingTime=0.0;
		min_waitingTime=0.0;
		av_waitingTime=0.0;
		idleTime = 0.0;
		busyTime = 0.0;
		pidleTime = 0.0;
		pbusyTime = 0.0;
		/*cout << this->I << endl;
		getchar();*/

		for(size_t i=0;i<this->I;i++)
		{
			temp_y = this->processTimes[i][j];
			if(max_waitingTime<=temp_y)
				max_waitingTime = temp_y;
			if(temp_y <= min_waitingTime || min_waitingTime==0.0)
				min_waitingTime = temp_y;
			if(i<this->I-1)
			{
				//cout << this->cplex.getValue(y[i+1][j]) << endl;
				//cout << this->processTimes[i+1][j] << endl;
				//cout << this->cplex.getValue(y[i][j]) << endl;
				//cout << this->cplex.getValue(y[i+1][j])-this->processTimes[i+1][j] - this->cplex.getValue(y[i][j]) << endl;
				//if(this->cplex.getValue(y[i+1][j])-this->processTimes[i+1][j] > this->cplex.getValue(y[i][j]))
				idleTime = idleTime + this->cplex.getValue(y[i+1][j])-this->processTimes[i+1][j] -
					this->cplex.getValue(y[i][j]);
				/*getchar();*/
			}

			temp_y_cum = temp_y_cum + temp_y;
		}
		pidleTime = idleTime/(this->cplex.getValue(y[this->I-1][numST-1]))*100.00;
		/*cout << this->I << endl;
		cout << idleTime << endl;
		cout << this->cplex.getValue(y[this->I-1][numST-1]) << endl;
		cout << pidleTime << endl;
		getchar();*/

		av_waitingTime = temp_y_cum/(double(this->I));
		//WRITING...
		out_resultsFile.precision(5);
		out_resultsFile << endl;
		out_resultsFile << "Station " << j << "		   " << fixed << av_waitingTime << "		   " << min_waitingTime << "		   " << max_waitingTime << endl;
		out_resultsFile << endl;
		out_resultsFile << "IDLE TIME " << idleTime << "		" << "%IDLE TIME " << pidleTime << "%" << endl;
		busyTime = this->cplex.getValue(y[this->I-1][numST-1])-idleTime;
		pbusyTime = 100.00-pidleTime;
		out_resultsFile << "BUSY TIME " << busyTime << "		" << "%BUSY TIME " << pbusyTime << "%" << endl;
		//out_resultsFile.precision(1);
		//std::fixed(std::ios_base::dec
	}
	
	temp_y = 0.0;
	temp_y_cum = 0.0;
	av_waitingTime=0.0;
	min_waitingTime=0.0;
	max_waitingTime=0.0;

	for(size_t i=0;i<this->I;i++)
	{
		temp_y=0.0;
		for(size_t j=0;j<numST-1;j++)
		{
			temp_y = temp_y + this->cplex.getValue(this->y[i][j+1])-this->processTimes[i][j+1] - this->cplex.getValue(this->y[i][j]);
		}
		if(max_waitingTime<=temp_y)
			max_waitingTime = temp_y;
		if(temp_y <= min_waitingTime && temp_y>0)
			min_waitingTime = temp_y;
		if(temp_y >0)
			temp_y_cum = temp_y_cum + temp_y;
	}
	av_waitingTime = temp_y_cum/double(this->I);
	out_resultsFile.precision(5);
	out_resultsFile << endl;
	out_resultsFile << "Waiting Time" << "		   " << fixed << av_waitingTime << "		   " << min_waitingTime << "		   " << max_waitingTime << endl;
	

	temp_y = 0.0;
	temp_y_cum = 0.0;
	av_waitingTime=0.0;
	min_waitingTime=0.0;
	max_waitingTime=0.0;

	for(size_t j=0;j<numST-1;j++)
	{
		temp_y=0.0;
		temp_y_cum=0.0;
		max_waitingTime=0.0;
		min_waitingTime=0.0;
		av_waitingTime=0.0;
		for(size_t i=0;i<this->I;i++)
		{
			temp_y = this->cplex.getValue(this->y[i][j+1])-this->processTimes[i][j+1] - this->cplex.getValue(this->y[i][j]);
			if(max_waitingTime<=temp_y)
				max_waitingTime = temp_y;
			if(temp_y <= min_waitingTime && temp_y >0)
				min_waitingTime = temp_y;
			if(temp_y>0)
				temp_y_cum = temp_y_cum + temp_y;
		}
		if(temp_y_cum>=0)
			av_waitingTime = temp_y_cum/(double(this->I));
		else
			av_waitingTime = 0.0;
		//WRITING...
		out_resultsFile << endl;
		out_resultsFile.precision(5);
		out_resultsFile << "Buffer " << j+1 << "		   " << fixed << av_waitingTime << "		   " << min_waitingTime << "		   " << max_waitingTime << endl;
	}


	temp_y=0.0;
	size_t k=0;
	bool found = false;
	double temp_x = 0.0;
	while(found==false && k < this->I)
	{
		temp_x = this->cplex.getValue(this->y[k][0])-this->processTimes[k][0];
		if(temp_x>=120)
		{
			found = true;
			out_resultsFile << endl;
			out_resultsFile << "Parts entered" << "		   " << k << endl;
		}
		k++;
	}
	

	k=0;
	found=false;
	while(found==false && k < this->I)
	{
		temp_y = this->cplex.getValue(this->y[k][numST-1]);
		if(temp_y>=120)
		{
			found = true;
			out_resultsFile << endl;
			out_resultsFile << "Parts processed" << "		   " << k << endl;
		}
		k++;
	}

	temp_y = 0.0;
	temp_y_cum = 0.0;
	for(size_t i=0;i<this->I-1;i++)
	{
		temp_y = this->cplex.getValue(this->y[i+1][numST-1])-this->cplex.getValue(this->y[i][numST-1]);
		temp_y_cum = temp_y_cum + temp_y;
	}
	double InvTempy_cum = double(this->I)/temp_y_cum;
	av_throughput = InvTempy_cum;

	out_resultsFile << endl;
	out_resultsFile.precision(5);
	out_resultsFile << "Average Throughput" << "		   " << fixed << av_throughput << endl;


	out_resultsFile << endl;
	out_resultsFile << "-----------------------------------------------------------" << endl;
	out_resultsFile << "-----------------------------------------------------------" << endl;
	out_resultsFile << "-----------------------------------------------------------" << endl;
}
void App_OpModel::ClearCplexElements(void)
{
	this->env.end();
}
void App_OpModel::createEnvironment(void)
{
	this->env = IloEnv();
}
void App_OpModel::computeBounds(std::ofstream & f3,std::ofstream & out_of)
{
	postProcess::BoundsCalculation* boundsComp = new postProcess::BoundsCalculation();
	//-------------------------------------------------------------------------------------//
	//-------------------------------BOUNDS CALCULATION------------------------------------//
	//-------------------------------------------------------------------------------------//
	if(this->_GPmys->sysType == FLOWLINE && this->_optObj!=SIM_EXTENDED_KANBAN&&
		this->_optObj!=SIM_KANBAN && this->_optObj!=SIM_BASESTOCK && this->_optObj!=EXACT_SIM)
	{
		std::vector<int> upperBound;
		/*upperBound.resize(this->_GPmys->psBuff.size());*/
		upperBound.clear();
		std::vector<int> lowerBound;
		/*lowerBound.resize(this->_GPmys->psBuff.size());*/
		lowerBound.clear();
		std::vector<double> x_j;
		/*x_j.resize(this->I);*/
		std::vector<double> TB;

		int myBuffSize(0);
		myBuffSize = this->_GPmys->psBuff.size();
		for(int k=0;k<myBuffSize;k++)
		{
			/*TB.resize(this->mycap[k]);*/
			TB.clear();
			x_j.clear();
			for(int i=0;i<this->I;i++)
			{
				/*x_j[i]=this->cplex.getValue(this->y[i][k]) - this->processTimes[i][k];*/
				x_j.push_back(this->cplex.getValue(this->y[i][k]) - this->processTimes[i][k]);
			}
			cout << "vector of x: done!" << endl;
			for(int i=0;i<this->mycap[k];i++){
				/*TB[i] = this->_GPmys->TB_cap[i][k];*/
				TB.push_back(this->_GPmys->TB_cap[i][k]);
			}
			cout << "time buffer: done!" << endl;
			bool LowFound=false;
			int temp;
			int tempLow=1;
			int p=0;
			
			while (LowFound==false && p<this->mycap[k])
			{
				temp = boundsComp->computeLowerBound(x_j,TB,this->I,p,this->d,
					this->_GPmys->sysType, MIN_s);
				cout << "try lower" << endl;
				if(/*temp>=lowerBound[k]*/temp>=tempLow){
					tempLow=temp;
					p++;
					/*lowerBound[k]=temp;*/
				}
				else
					LowFound = true;
				/*p++;*/
			}
			lowerBound.push_back(tempLow);
			bool UpFound=false;
			temp=0;
			int tempUp=mycap[k];
			p=mycap[k];
			while (UpFound==false && p>0)
			{
				temp = boundsComp->computeUpperBound(x_j,TB,this->I,p,this->d,
					this->_GPmys->sysType, MIN_s);
				cout << "try upper" << endl;
				/*if(temp<=upperBound[k])*/
				if(temp < tempUp || p==mycap[k]){
					/*upperBound[k]=temp;*/
					tempUp = temp;
					p--;					
				}
				else{
					/*UpFound = true;*/
					UpFound=true;					
				}
				/*p++;*/
			}
			upperBound.push_back(tempUp);
			/*if(UpFound==false)
				upperBound[k]=mycap[k];*/
			cout << "Bounds Computed! " << endl;
			f3 << lowerBound[k] << " " << upperBound[k] << " ";
		}
		f3 << endl;
	}
	else if(this->_GPmys->sysType == CLOSEDLOOP && this->_optObj!=SIM_EXTENDED_KANBAN &&
		this->_optObj!=SIM_KANBAN && this->_optObj!=SIM_BASESTOCK &&  this->_optObj!=EXACT_SIM)
	{
		int upperBound(this->myPal);
		int lowerBound(1);
		vector<double> x_j(this->I);
		vector<double> TB;
		TB.resize(this->myPal);

		for(int i=0;i<this->I;i++)
		{
			x_j[i]=this->cplex.getValue(this->y[i][0])-this->processTimes[i][0];
		}
		for(int i=0;i<this->myPal;i++)
		{
			TB[i] = this->_GPmys->TB_cap[i][0];
		}
		bool LowFound=false;
		int temp;
		int p=0;
		
		while (LowFound==false && p<this->myPal)
		{
			temp = boundsComp->computeLowerBound(x_j,TB,this->I,p,this->d,
					this->_GPmys->sysType, this->_myOFtype);
			if(temp>=lowerBound)
				lowerBound=temp;
			else
				LowFound = true;
			p++;
		}
		bool UpFound=false;
		temp=0;
		p=0;
		while (UpFound==false && p<this->myPal)
		{
			temp = boundsComp->computeUpperBound(x_j,TB,this->I,p,this->d,
					this->_GPmys->sysType, this->_myOFtype);
			if(temp<=upperBound)
			{
				upperBound=temp;
				UpFound = true;
			}
			else
				p++;
		}

		f3 << lowerBound << " " << upperBound << std::endl;
	}
	else if(this->_optObj == SIM_EXTENDED_KANBAN || this->_optObj == SIM_BASESTOCK || this->_optObj == SIM_KANBAN)
	{
		//------------------------------------------------------------
		//------------------------------------------------------------
		//-------------------BASE STOCK BOUNDS------------------------
		//------------------------------------------------------------
		std::vector<int> upperBound;
		std::vector<int> lowerBound;
		std::vector<double> x_j;
		std::vector<double> TB;
		bool LowFound=false;
		int temp;
		int tempLow=1;
		int p=0;
		bool UpFound=false;
		int tempUp=0;

		int myBuffSize(0);
		myBuffSize = this->_GPmys->psBuff.size();
		if(this->TB_bs.size()>0)
		{
			f3 << "BASESTOCK BOUNDS" << endl;
			
			upperBound.clear();			
			lowerBound.clear();
			
			for(int k=0;k<myBuffSize;k++)
			{
				TB.clear();
				x_j.clear();
				for(int i=0;i<this->I;i++)
				{
					x_j.push_back(this->cplex.getValue(this->rTime[i][k]));
				}
				cout << "vector of x: done!" << endl;
				for(int i=0;i<this->TB_bs.size();i++){
					TB.push_back(this->TB_bs[i][k]);
				}
				cout << "time buffer: done!" << endl;
				
				while (LowFound==false && p<this->mycap[0])
				{
					temp = boundsComp->computeLowerBound(x_j,TB,this->I,p,this->d,
						this->_GPmys->sysType, MIN_s);
					cout << "try lower" << endl;
					if(temp>=tempLow){
						tempLow=temp;
						p++;
					}
					else
						LowFound = true;
				}
				lowerBound.push_back(tempLow);
				temp=0;
				tempUp=mycap[0];
				p=mycap[0];
				while (UpFound==false && p>0)
				{
					temp = boundsComp->computeUpperBound(x_j,TB,this->I,p,this->d,
						this->_GPmys->sysType, MIN_s);
					cout << "try upper" << endl;
					if(temp < tempUp || p==mycap[0]){
						tempUp = temp;
						p--;					
					}
					else{
						UpFound=true;					
					}
				}
				upperBound.push_back(tempUp);
				
				cout << "Bounds Computed! " << endl;
				f3 << lowerBound[k] << " " << upperBound[k] << " ";
			}
			f3 << endl;
		}

		if(this->TB_kan.size()>0)
		{
			if(this->TB_kan[0].size()>0)
			{
				f3 << "KANBAN BOUNDS" << endl;
				
				upperBound.clear();
				
				lowerBound.clear();
				
				myBuffSize = this->_GPmys->psBuff.size();
				for(int k=0;k<myBuffSize;k++)
				{
					TB.clear();
					x_j.clear();
					for(int i=0;i<this->I;i++)
					{
						x_j.push_back(this->cplex.getValue(this->rTime[i][k]));
					}
					cout << "vector of x: done!" << endl;
					for(int i=0;i<this->TB_kan.size();i++){
						TB.push_back(this->TB_kan[i][k]);
					}
					cout << "time buffer: done!" << endl;
					LowFound=false;
					tempLow=1;
					p=0;				
					while (LowFound==false && p<this->mycap[k])
					{
						temp = boundsComp->computeLowerBound(x_j,TB,this->I,p,this->d,
							this->_GPmys->sysType, MIN_s);
						cout << "try lower" << endl;
						if(temp>=tempLow){
							tempLow=temp;
							p++;
						}
						else
							LowFound = true;
					}
					lowerBound.push_back(tempLow);
					UpFound=false;
					temp=0;
					tempUp=mycap[k];
					p=mycap[k];
					while (UpFound==false && p>0)
					{
						temp = boundsComp->computeUpperBound(x_j,TB,this->I,p,this->d,
							this->_GPmys->sysType, MIN_s);
						cout << "try upper" << endl;
						if(temp < tempUp || p==mycap[k]){
							tempUp = temp;
							p--;					
						}
						else{
							UpFound=true;					
						}
					}
					upperBound.push_back(tempUp);
					cout << "Bounds Computed! " << endl;
					f3 << lowerBound[k] << " " << upperBound[k] << " ";
				}
				f3 << endl;
			}
		}
		}

		int appSol(0);
		/*std::vector<double> yj;
		std::vector<double> yjp1;
		postProcess::AppSolAlg* appSolObj = new postProcess::AppSolAlg();
		if(this->_optObj!=SIM_EXTENDED_KANBAN && this->_optObj!=SIM_KANBAN &&
				this->_optObj!=SIM_BASESTOCK && this->_optObj!=EXACT_SIM)
		{
			for(size_t k=0;k<this->_GPmys->psMachines.size()-1;k++)
			{
				
					yj.clear();
					yjp1.clear();
					for(size_t l=0;l < this->I;l++)
					{
						yj.push_back(this->cplex.getValue(this->y[l][k]));
						yjp1.push_back(this->cplex.getValue(this->y[l][k+1]));
					}
					appSol = appSolObj->calcCapApp(yj,yjp1,this->I);
					out_of << appSol << " ";
			}
		}*/
		/*else
		{*/
		if(this->_optObj==EXACT_SIM)
		{
			if(this->_GPmys->sysType==FLOWLINE)
			{
				for(int i=0;i<this->_GPmys->psBuff.size();i++)
				{
					out_of << this->_GPmys->psBuff[i]->capacity << " ";
				}
				out_of << endl;
			}
			if(this->_GPmys->sysType==CLOSEDLOOP)
			{
				out_of << this->myPal << endl;
			}
		}
		else
		{
			bool appsolFound=false;
			std::vector<int> appSolVec;
			if(this->TB_bs.size()>0)
			{
				for(size_t k=0;k<this->TB_bs[0].size();k++)
				{								
					size_t l=0;
					appsolFound=false;
					while(appsolFound==false && l < this->TB_bs.size())
					{
						if(this->TB_bs[l][k]==0)
						{
							appSol = l;
							appSolVec.push_back(l);
							appsolFound=true;
						}
						else
							l++;
					}
				}
				for(int l=0;l<appSolVec.size();l++)
				{
					if(l<appSolVec.size()-1)
					{
						out_of << appSolVec[l] - appSolVec[l+1] << " ";
					}
					else
					{
						out_of << appSolVec[l] << " ";
					}
				}
			}
			appsolFound = false;
			if(this->_GPmys->sysType==FLOWLINE)
			{
				for(size_t k=0;k<this->_GPmys->TB_cap[0].size();k++)
				{								
					size_t l=0;
					appsolFound=false;
					while(appsolFound==false && l < this->_GPmys->TB_cap.size())
					{
						if(this->_GPmys->TB_cap[l][k]==0)
						{
							appSol = l+1;
							appSolVec.push_back(l);
							appsolFound=true;
						}
						else
							l++;
					}
				}
				for(int l=0;l<appSolVec.size();l++)
				{
					out_of << appSolVec[l] << " ";
				}
			}
			appsolFound = false;
			if(this->_GPmys->sysType==CLOSEDLOOP)
			{								
				size_t l=0;
				appsolFound=false;
				while(appsolFound==false && l < this->_GPmys->TB_cap.size())
				{
					if(this->_GPmys->TB_cap[l][0]==0)
					{
						appSol = l+1;
						appsolFound=true;
					}
					else
						l++;
				}
				
				out_of << appSol << " ";
			}
			appsolFound = false;

			int l=0;
			if(this->TB_kan.size()>0)
			{
				for(size_t k=0;k<this->TB_kan[0].size();k++)
				{
					appsolFound=false;
					while(appsolFound==false && l < this->TB_kan.size())
					{
						if(this->TB_kan[l][k]==0)
						{
							appSol = l+1;
							appsolFound=true;
							out_of << appSol << " ";
						}
						else
							l++;
					}
				}
			}
		}
		/*}*/
		out_of << endl;
		/*delete(appSolObj);*/
		delete(boundsComp);	
}
void App_OpModel::GenProcessTime(std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _FailureMDescr,
							 stochasticProperty::base_generator_type & gen,int iterationIndex,int i)
{
	std::vector<std::vector<double> > tempPT_expo;
	tempPT_expo.clear();
	if(this->_rhsChange == CHANGE_N && iterationIndex>0)
	{
		tempPT_expo.resize(int(this->myStep));
		if(this->_GPmys->psMachines[i]->pDistribution->myType==0)
			this->_GPmys->psMachines[i]->pDistribution->gpExpoDataGeneration(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==1)
			this->_GPmys->psMachines[i]->pDistribution->gpUniformDataGeneration(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==2)
			this->_GPmys->psMachines[i]->pDistribution->gpNormalDataGenerator(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==3)
			cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==4)
			this->_GPmys->psMachines[i]->pDistribution->gpConstantDataGeneration(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==5)
			this->_GPmys->psMachines[i]->pDistribution->gpTriangularDataGenerator(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==6)
			this->_GPmys->psMachines[i]->pDistribution->gpLogNDataGenerator(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==7)
			this->_GPmys->psMachines[i]->pDistribution->gpWeibullDataGenerator(gen,tempPT_expo,
				int(this->myStep));
	
		for(size_t j=(int)(this->I-this->myStep);j<int(this->I);j++)
		{
			this->processTimes[j][i]=tempPT_expo[j-(int)(this->I-this->myStep)][0];
		}
		if(_FailureMDescr[int(i)].size()>0)
		{
			//generate a random number
			std::vector<std::vector<double> > genFailTime;
			stochasticProperty::gpDistribution* rnGen = new stochasticProperty::gpDistribution(UNIFORM,0.0,1.0);
			for(size_t fp=(int)(this->I-this->myStep);fp<this->I;fp++)
			{
				if(rnGen->gpUniformDataGeneration(gen,genFailTime)){
					bool deltaProc=false;
					int fmI(0);
					while (deltaProc==false && fmI<_FailureMDescr[int(i)].size()){
						if(genFailTime[0][0]<_FailureMDescr[int(i)][fmI].first){
							genFailTime.clear();
							switch(_FailureMDescr[int(i)][fmI].second->myType)
							{
								case 0: 
									_FailureMDescr[int(i)][fmI].second->gpExpoDataGeneration(gen,genFailTime);
									break;
								case 1:
									_FailureMDescr[int(i)][fmI].second->gpUniformDataGeneration(gen,genFailTime);
									break;
								case 2:
									_FailureMDescr[int(i)][fmI].second->gpNormalDataGenerator(gen,genFailTime);
									break;
								case 3:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
								case 4:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
									break;
								case 5:
									_FailureMDescr[int(i)][fmI].second->gpTriangularDataGenerator(gen,genFailTime);
									break;
								case 6:
									_FailureMDescr[int(i)][fmI].second->gpLogNDataGenerator(gen,genFailTime);
									break;
								case 7:
									_FailureMDescr[int(i)][fmI].second->gpWeibullDataGenerator(gen,genFailTime);
									break;
								default: std::cout << "Didn't receive legal argument" << std::endl;

							}
							this->processTimes[fp][i]=this->processTimes[fp][i]+genFailTime[0][0];
							deltaProc=true;
						}
						else
							fmI++;
					}
				}
			}
		}
	}
	else
	{
		tempPT_expo.clear();
		tempPT_expo.resize(int(this->I));
		if(this->_GPmys->psMachines[i]->pDistribution->myType==0)
		{
			this->_GPmys->psMachines[i]->pDistribution->gpExpoDataGeneration(gen,tempPT_expo,
				int(this->I));
		}
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==1)
			this->_GPmys->psMachines[i]->pDistribution->gpUniformDataGeneration(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==2)
			this->_GPmys->psMachines[i]->pDistribution->gpNormalDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==3)
			cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==4)
			this->_GPmys->psMachines[i]->pDistribution->gpConstantDataGeneration(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==5)
			this->_GPmys->psMachines[i]->pDistribution->gpTriangularDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==6)
			this->_GPmys->psMachines[i]->pDistribution->gpLogNDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==7)
			this->_GPmys->psMachines[i]->pDistribution->gpWeibullDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==8)
			this->_GPmys->psMachines[i]->pDistribution->gpGammaDataGenerator(gen,tempPT_expo,
				int(this->I));
		for(size_t j=0;j<int(this->I);j++)
		{
			this->processTimes[j][i]=tempPT_expo[j][0];
		}
		if(_FailureMDescr[int(i)].size()>0)
		{
			//generate a random number
			std::vector<std::vector<double> > genFailTime;
			stochasticProperty::gpDistribution* rnGen = new stochasticProperty::gpDistribution(UNIFORM,0.0,1.0);
			
			for(size_t fp=0;fp<this->I;fp++)
			{
				if(rnGen->gpUniformDataGeneration(gen,genFailTime)){
					bool deltaProc=false;
					int fmI(0);
					while (deltaProc==false && fmI<_FailureMDescr[int(i)].size()){
						if(genFailTime[0][0]<_FailureMDescr[int(i)][fmI].first){
							genFailTime.clear();
							switch(_FailureMDescr[int(i)][fmI].second->myType)
							{
								case 0: 
									_FailureMDescr[int(i)][fmI].second->gpExpoDataGeneration(gen,genFailTime);
									break;
								case 1:
									_FailureMDescr[int(i)][fmI].second->gpUniformDataGeneration(gen,genFailTime);
									break;
								case 2:
									_FailureMDescr[int(i)][fmI].second->gpNormalDataGenerator(gen,genFailTime);
									break;
								case 3:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
								case 4:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
									break;
								case 5:
									_FailureMDescr[int(i)][fmI].second->gpTriangularDataGenerator(gen,genFailTime);
									break;
								case 6:
									_FailureMDescr[int(i)][fmI].second->gpLogNDataGenerator(gen,genFailTime);
									break;
								case 7:
									_FailureMDescr[int(i)][fmI].second->gpWeibullDataGenerator(gen,genFailTime);
									break;
								case 8:
									_FailureMDescr[int(i)][fmI].second->gpGammaDataGenerator(gen,genFailTime);
									break;
								default: std::cout << "Didn't receive legal argument" << std::endl;

							}
							this->processTimes[fp][i]=this->processTimes[fp][i]+genFailTime[0][0];
							deltaProc=true;
						}
						else
							fmI++;
					}
				}
			}
		}
	}
}
void App_OpModel::GenLHSProcessTime(std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _FailureMDescr,
							 stochasticProperty::base_generator_type & gen,int iterationIndex,int i)
{
	std::vector<std::vector<double> > tempPT_expo;
	tempPT_expo.clear();
	if(this->_rhsChange == CHANGE_N && iterationIndex>0)
	{
		tempPT_expo.resize(int(this->myStep));
		if(this->_GPmys->psMachines[i]->pDistribution->myType==0)
			this->_GPmys->psMachines[i]->pDistribution->gpLHSExpoDataGeneration(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==1)
			this->_GPmys->psMachines[i]->pDistribution->gpUniformDataGeneration(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==2)
			this->_GPmys->psMachines[i]->pDistribution->gpNormalDataGenerator(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==3)
			cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==4)
			this->_GPmys->psMachines[i]->pDistribution->gpConstantDataGeneration(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==5)
			this->_GPmys->psMachines[i]->pDistribution->gpTriangularDataGenerator(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==6)
			this->_GPmys->psMachines[i]->pDistribution->gpLogNDataGenerator(gen,tempPT_expo,
				int(this->myStep));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==7)
			this->_GPmys->psMachines[i]->pDistribution->gpWeibullDataGenerator(gen,tempPT_expo,
				int(this->myStep));
	
		for(size_t j=(int)(this->I-this->myStep);j<int(this->I);j++)
		{
			this->processTimes[j][i]=tempPT_expo[j-(int)(this->I-this->myStep)][0];
		}
		if(_FailureMDescr[int(i)].size()>0)
		{
			//generate a random number
			std::vector<std::vector<double> > genFailTime;
			stochasticProperty::gpDistribution* rnGen = new stochasticProperty::gpDistribution(UNIFORM,0.0,1.0);
			for(size_t fp=(int)(this->I-this->myStep);fp<this->I;fp++)
			{
				if(rnGen->gpUniformDataGeneration(gen,genFailTime)){
					bool deltaProc=false;
					int fmI(0);
					while (deltaProc==false && fmI<_FailureMDescr[int(i)].size()){
						if(genFailTime[0][0]<_FailureMDescr[int(i)][fmI].first){
							genFailTime.clear();
							switch(_FailureMDescr[int(i)][fmI].second->myType)
							{
								case 0: 
									_FailureMDescr[int(i)][fmI].second->gpExpoDataGeneration(gen,genFailTime);
									break;
								case 1:
									_FailureMDescr[int(i)][fmI].second->gpUniformDataGeneration(gen,genFailTime);
									break;
								case 2:
									_FailureMDescr[int(i)][fmI].second->gpNormalDataGenerator(gen,genFailTime);
									break;
								case 3:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
								case 4:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
									break;
								case 5:
									_FailureMDescr[int(i)][fmI].second->gpTriangularDataGenerator(gen,genFailTime);
									break;
								case 6:
									_FailureMDescr[int(i)][fmI].second->gpLogNDataGenerator(gen,genFailTime);
									break;
								case 7:
									_FailureMDescr[int(i)][fmI].second->gpWeibullDataGenerator(gen,genFailTime);
									break;
								default: std::cout << "Didn't receive legal argument" << std::endl;

							}
							this->processTimes[fp][i]=this->processTimes[fp][i]+genFailTime[0][0];
							deltaProc=true;
						}
						else
							fmI++;
					}
				}
			}
		}
	}
	else
	{
		tempPT_expo.clear();
		tempPT_expo.resize(int(this->I));
		if(this->_GPmys->psMachines[i]->pDistribution->myType==0)
		{
			this->_GPmys->psMachines[i]->pDistribution->gpLHSExpoDataGeneration(gen,tempPT_expo,
				int(this->I));
		}
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==1)
			this->_GPmys->psMachines[i]->pDistribution->gpUniformDataGeneration(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==2)
			this->_GPmys->psMachines[i]->pDistribution->gpNormalDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==3)
			cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==4)
			this->_GPmys->psMachines[i]->pDistribution->gpConstantDataGeneration(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==5)
			this->_GPmys->psMachines[i]->pDistribution->gpTriangularDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==6)
			this->_GPmys->psMachines[i]->pDistribution->gpLogNDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==7)
			this->_GPmys->psMachines[i]->pDistribution->gpWeibullDataGenerator(gen,tempPT_expo,
				int(this->I));
		else if(this->_GPmys->psMachines[i]->pDistribution->myType==8)
			this->_GPmys->psMachines[i]->pDistribution->gpGammaDataGenerator(gen,tempPT_expo,
				int(this->I));
		for(size_t j=0;j<int(this->I);j++)
		{
			this->processTimes[j][i]=tempPT_expo[j][0];
		}
		if(_FailureMDescr[int(i)].size()>0)
		{
			//generate a random number
			std::vector<std::vector<double> > genFailTime;
			stochasticProperty::gpDistribution* rnGen = new stochasticProperty::gpDistribution(UNIFORM,0.0,1.0);
			
			for(size_t fp=0;fp<this->I;fp++)
			{
				if(rnGen->gpUniformDataGeneration(gen,genFailTime)){
					bool deltaProc=false;
					int fmI(0);
					while (deltaProc==false && fmI<_FailureMDescr[int(i)].size()){
						if(genFailTime[0][0]<_FailureMDescr[int(i)][fmI].first){
							genFailTime.clear();
							switch(_FailureMDescr[int(i)][fmI].second->myType)
							{
								case 0: 
									_FailureMDescr[int(i)][fmI].second->gpExpoDataGeneration(gen,genFailTime);
									break;
								case 1:
									_FailureMDescr[int(i)][fmI].second->gpUniformDataGeneration(gen,genFailTime);
									break;
								case 2:
									_FailureMDescr[int(i)][fmI].second->gpNormalDataGenerator(gen,genFailTime);
									break;
								case 3:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
								case 4:
									_FailureMDescr[int(i)][fmI].second->gpConstantDataGeneration(gen,genFailTime);
									break;
								case 5:
									_FailureMDescr[int(i)][fmI].second->gpTriangularDataGenerator(gen,genFailTime);
									break;
								case 6:
									_FailureMDescr[int(i)][fmI].second->gpLogNDataGenerator(gen,genFailTime);
									break;
								case 7:
									_FailureMDescr[int(i)][fmI].second->gpWeibullDataGenerator(gen,genFailTime);
									break;
								case 8:
									_FailureMDescr[int(i)][fmI].second->gpGammaDataGenerator(gen,genFailTime);
									break;
								default: std::cout << "Didn't receive legal argument" << std::endl;

							}
							this->processTimes[fp][i]=this->processTimes[fp][i]+genFailTime[0][0];
							deltaProc=true;
						}
						else
							fmI++;
					}
				}
			}
		}
	}
}
void App_OpModel::GenArrivals(stochasticProperty::base_generator_type & gen)
{
	std::vector<std::vector<double> > tempAT_expo;
	tempAT_expo.resize(this->I);
	/*stochasticProperty::RandomNumberGenerator gen(seed);*/
	if(this->_GPmys->mycustomer->arr_description->myType==0)
		this->_GPmys->mycustomer->arr_description->gpExpoDataGeneration(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==1)
		this->_GPmys->mycustomer->arr_description->gpUniformDataGeneration(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==2)
		this->_GPmys->mycustomer->arr_description->gpNormalDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==3)
		cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
	else if(this->_GPmys->mycustomer->arr_description->myType==4)
		this->_GPmys->mycustomer->arr_description->gpConstantDataGeneration(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==5)
		this->_GPmys->mycustomer->arr_description->gpTriangularDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==6)
		this->_GPmys->mycustomer->arr_description->gpLogNDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==7)
		this->_GPmys->mycustomer->arr_description->gpWeibullDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==8)
		this->_GPmys->mycustomer->arr_description->gpGammaDataGenerator(gen,tempAT_expo,int(this->I));
	

	/*cout << at[0] << endl;*/
	/*cout << I << endl;*/
	/*Generation of interarrivals*/
	/*at = vectorSort(tempAT,0,I);*/
	this->arrivalTimes.clear();
	this->arrivalTimes.resize(tempAT_expo.size());
	for(size_t i=0;i<tempAT_expo.size();i++)
	{
		this->arrivalTimes[i] = tempAT_expo[i][0];
	}
	
	//Arrivals generation
	this->arrivalTimes[0]=0.0;
	for(size_t i=1;i<this->arrivalTimes.size();i++)
	{
		if(this->_optObj==EXTENDED_KANBAN||this->_optObj==SIM_EXTENDED_KANBAN||
		this->_optObj==SIM_KANBAN|| this->_optObj==SIM_BASESTOCK|| this->_optObj==APP_SIM_TBCS ||
		this->_optObj==EXACT_SIM_KBS ||
		this->_optObj==KANBAN || this->_optObj==BASESTOCK || this->_optObj==APP_OPT_TBCS ||
		this->_optObj==EXACT_SIM_KCS||this->_optObj==EXACT_SIM_BS || this->_optObj==EXACT_OPT_BSC ||
		this->_optObj==EXACT_OPT_KSC || this->_optObj==EXACT_OPT_EKCS)
			this->arrivalTimes[i]=0;
		else
			this->arrivalTimes[i]=this->arrivalTimes[i-1]+this->arrivalTimes[i];
	}
/*}*/
	if(this->_optObj==EXTENDED_KANBAN||this->_optObj==SIM_EXTENDED_KANBAN||
		this->_optObj==SIM_KANBAN|| this->_optObj==SIM_BASESTOCK|| this->_optObj==APP_SIM_TBCS ||
		this->_optObj==EXACT_SIM_KBS ||
		this->_optObj==KANBAN || this->_optObj==BASESTOCK || this->_optObj==APP_OPT_TBCS ||
		this->_optObj==EXACT_SIM_KCS||this->_optObj==EXACT_SIM_BS || this->_optObj==EXACT_OPT_BSC ||
		this->_optObj==EXACT_OPT_KSC || this->_optObj==EXACT_OPT_EKCS)
	{
		tempAT_expo.clear();
		tempAT_expo.resize(this->I);
		/*stochasticProperty::RandomNumberGenerator gen(seed);*/
		if(this->_GPmys->mycustomer->arr_description->myType==0)
			this->_GPmys->mycustomer->arr_description->gpExpoDataGeneration(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==1)
			this->_GPmys->mycustomer->arr_description->gpUniformDataGeneration(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==2)
			this->_GPmys->mycustomer->arr_description->gpNormalDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==3)
			cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
		else if(this->_GPmys->mycustomer->arr_description->myType==4)
			this->_GPmys->mycustomer->arr_description->gpConstantDataGeneration(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==5)
			this->_GPmys->mycustomer->arr_description->gpTriangularDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==6)
			this->_GPmys->mycustomer->arr_description->gpLogNDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==7)
			this->_GPmys->mycustomer->arr_description->gpWeibullDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==8)
		this->_GPmys->mycustomer->arr_description->gpGammaDataGenerator(gen,tempAT_expo,int(this->I));
		

		/*cout << at[0] << endl;*/
		/*cout << I << endl;*/
		/*Generation of interarrivals*/
		/*at = vectorSort(tempAT,0,I);*/
		this->demandProcess.clear();
		this->demandProcess.resize(tempAT_expo.size());
		for(size_t i=0;i<tempAT_expo.size();i++)
		{
			this->demandProcess[i] = tempAT_expo[i][0];
		}
		
		//Arrivals generation
		//this->demandProcess[0]=0.0;
		for(size_t i=1;i<this->demandProcess.size();i++)
		this->demandProcess[i]=this->demandProcess[i-1]+this->demandProcess[i];

		std::ofstream outdemand;
		outdemand.open("OUTPUT\\demand.txt");
		for(size_t i=1;i<this->demandProcess.size();i++)
			outdemand << this->demandProcess[i] << endl;
		outdemand.close();
	}
}
void App_OpModel::GenLHSArrivals(stochasticProperty::base_generator_type & gen)
{
	std::vector<std::vector<double> > tempAT_expo;
	tempAT_expo.resize(this->I);
	/*stochasticProperty::RandomNumberGenerator gen(seed);*/
	if(this->_GPmys->mycustomer->arr_description->myType==0)
		this->_GPmys->mycustomer->arr_description->gpLHSExpoDataGeneration(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==1)
		this->_GPmys->mycustomer->arr_description->gpUniformDataGeneration(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==2)
		this->_GPmys->mycustomer->arr_description->gpNormalDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==3)
		cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
	else if(this->_GPmys->mycustomer->arr_description->myType==4)
		this->_GPmys->mycustomer->arr_description->gpConstantDataGeneration(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==5)
		this->_GPmys->mycustomer->arr_description->gpTriangularDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==6)
		this->_GPmys->mycustomer->arr_description->gpLogNDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==7)
		this->_GPmys->mycustomer->arr_description->gpWeibullDataGenerator(gen,tempAT_expo,int(this->I));
	else if(this->_GPmys->mycustomer->arr_description->myType==8)
		this->_GPmys->mycustomer->arr_description->gpGammaDataGenerator(gen,tempAT_expo,int(this->I));
	

	/*cout << at[0] << endl;*/
	/*cout << I << endl;*/
	/*Generation of interarrivals*/
	/*at = vectorSort(tempAT,0,I);*/
	this->arrivalTimes.clear();
	this->arrivalTimes.resize(tempAT_expo.size());
	for(size_t i=0;i<tempAT_expo.size();i++)
	{
		this->arrivalTimes[i] = tempAT_expo[i][0];
	}
	
	//Arrivals generation
	this->arrivalTimes[0]=0.0;
	for(size_t i=1;i<this->arrivalTimes.size();i++)
	{
		if(this->_optObj==EXTENDED_KANBAN||this->_optObj==SIM_EXTENDED_KANBAN||
		this->_optObj==SIM_KANBAN|| this->_optObj==SIM_BASESTOCK|| this->_optObj==APP_SIM_TBCS ||
		this->_optObj==EXACT_SIM_KBS ||
		this->_optObj==KANBAN || this->_optObj==BASESTOCK || this->_optObj==APP_OPT_TBCS ||
		this->_optObj==EXACT_SIM_KCS||this->_optObj==EXACT_SIM_BS || this->_optObj==EXACT_OPT_BSC ||
		this->_optObj==EXACT_OPT_KSC || this->_optObj==EXACT_OPT_EKCS)
			this->arrivalTimes[i]=0;
		else
			this->arrivalTimes[i]=this->arrivalTimes[i-1]+this->arrivalTimes[i];
	}
/*}*/
	if(this->_optObj==EXTENDED_KANBAN||this->_optObj==SIM_EXTENDED_KANBAN||
		this->_optObj==SIM_KANBAN|| this->_optObj==SIM_BASESTOCK|| this->_optObj==APP_SIM_TBCS ||
		this->_optObj==EXACT_SIM_KBS ||
		this->_optObj==KANBAN || this->_optObj==BASESTOCK || this->_optObj==APP_OPT_TBCS ||
		this->_optObj==EXACT_SIM_KCS||this->_optObj==EXACT_SIM_BS || this->_optObj==EXACT_OPT_BSC ||
		this->_optObj==EXACT_OPT_KSC || this->_optObj==EXACT_OPT_EKCS)
	{
		tempAT_expo.clear();
		tempAT_expo.resize(this->I);
		/*stochasticProperty::RandomNumberGenerator gen(seed);*/
		if(this->_GPmys->mycustomer->arr_description->myType==0)
			this->_GPmys->mycustomer->arr_description->gpLHSExpoDataGeneration(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==1)
			this->_GPmys->mycustomer->arr_description->gpUniformDataGeneration(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==2)
			this->_GPmys->mycustomer->arr_description->gpNormalDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==3)
			cout << "ERROR! NO DISTRIBUTION DEFINED!" << endl;
		else if(this->_GPmys->mycustomer->arr_description->myType==4)
			this->_GPmys->mycustomer->arr_description->gpConstantDataGeneration(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==5)
			this->_GPmys->mycustomer->arr_description->gpTriangularDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==6)
			this->_GPmys->mycustomer->arr_description->gpLogNDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==7)
			this->_GPmys->mycustomer->arr_description->gpWeibullDataGenerator(gen,tempAT_expo,int(this->I));
		else if(this->_GPmys->mycustomer->arr_description->myType==8)
		this->_GPmys->mycustomer->arr_description->gpGammaDataGenerator(gen,tempAT_expo,int(this->I));
		

		/*cout << at[0] << endl;*/
		/*cout << I << endl;*/
		/*Generation of interarrivals*/
		/*at = vectorSort(tempAT,0,I);*/
		this->demandProcess.clear();
		this->demandProcess.resize(tempAT_expo.size());
		for(size_t i=0;i<tempAT_expo.size();i++)
		{
			this->demandProcess[i] = tempAT_expo[i][0];
		}
		
		//Arrivals generation
		//this->demandProcess[0]=0.0;
		for(size_t i=1;i<this->demandProcess.size();i++)
		this->demandProcess[i]=this->demandProcess[i-1]+this->demandProcess[i];

		std::ofstream outdemand;
		outdemand.open("OUTPUT\\demand.txt");
		for(size_t i=1;i<this->demandProcess.size();i++)
			outdemand << this->demandProcess[i] << endl;
		outdemand.close();
	}
}
void App_OpModel::DEOsimOpt(std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _FailureMDescr,
							std::ofstream & fout,std::ofstream & fout2,std::ofstream & f3,
							std::ofstream & f4,std::ofstream & f5,std::ofstream & out_solApprossimata,
							std::ifstream & inproc,std::ifstream & inarr, int r)
{
	std::vector<std::vector<double> > myDOEplan;
	double SRcentral(0.0);
	double ptCentralM1(0.0);
	double ptCentralM2(0.0);
	if(this->_deoScope==DOE_SIMOPT)
	{
		if(this->generateDOEcondition(myDOEplan))
		{
			SRcentral = this->sr;
			ptCentralM1 = this->_GPmys->psMachines[0]->pDistribution->m1;
			ptCentralM2 = this->_GPmys->psMachines[0]->pDistribution->m2;

			for(int idoe=0;idoe<myDOEplan.size();idoe++)
			{
				//experimental condition setting
				this->sr = SRcentral + myDOEplan[idoe][0];
				for(int j=0;j<this->_GPmys->psMachines.size();j++){
					this->_GPmys->psMachines[j]->pDistribution->m1= ptCentralM1 + myDOEplan[idoe][1];
					this->_GPmys->psMachines[j]->pDistribution->m2= ptCentralM2 + myDOEplan[idoe][2];
				}
				if(idoe>0)
					this->createEnvironment();
				SIMOPT(_FailureMDescr, fout, fout2, f3, f4, f5, 
					out_solApprossimata, inproc, inarr, r);
			}
			myDOEplan.clear();
		}
	}
	else
	{
		if(this->generateDOEcondition(myDOEplan))
		{
			SRcentral = this->sr;
			ptCentralM1 = this->_GPmys->psMachines[0]->pDistribution->m1;
			ptCentralM2 = this->_GPmys->psMachines[0]->pDistribution->m2;

			for(int idoe=0;idoe<myDOEplan.size();idoe++)
			{
				//experimental condition setting
				this->sr = SRcentral + myDOEplan[idoe][0];
				for(int j=0;j<this->_GPmys->psMachines.size();j++){
					this->_GPmys->psMachines[j]->pDistribution->m1= ptCentralM1 + myDOEplan[idoe][1];
					this->_GPmys->psMachines[j]->pDistribution->m2= ptCentralM2 + myDOEplan[idoe][2];
				}
				if(idoe>0)
					this->createEnvironment();
				SIMOPT(_FailureMDescr, fout, fout2, f3, f4, f5, 
					out_solApprossimata, inproc, inarr, r);
			}
			myDOEplan.clear();
		}
	}
}
void App_OpModel::SIMOPT(std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _FailureMDescr,
							std::ofstream & fout,std::ofstream & fout2,std::ofstream & f3,
							std::ofstream & f4,std::ofstream & f5,std::ofstream & out_solApprossimata,
							std::ifstream & inproc,std::ifstream & inarr, int r)
{
	time_t start, end;
	std::ofstream outarrivals;
	std::ofstream outdemandVec;
	outarrivals.open("OUTPUT/ProcessTime.txt");
	outdemandVec.open("OUTPUT/DemandVec.txt");
	std::ofstream timeFileCPLEX;
	timeFileCPLEX.open("OUTPUT/AlgorithmPerformance.txt");
	timeFileCPLEX << "Sample Generation for PT" << " Demand Sample Generation " << " Opt Model Gen" <<
		" Optimization " << "Simulation Model gen " << " Simulation " <<endl;
	std::ofstream outSumYSumS;
	outSumYSumS.open("OUTPUT\\sumYsumS.txt");
	double startTime(0.0);
	double endTime(0.0);
	int seed=r;
	int iterationIndex(0);
	stochasticProperty::base_generator_type gen(seed);
	int myServerSize(0);
	myServerSize = this->_GPmys->psMachines.size();
	if(this->_optObj==KANBAN)
	{
		/*if(this->_myOFtype == MIN_s)
		{*/
		f5 << "S_opt ";
		f5 << "WT_opt " ;
		f5 << "ML_av_opt ";
		f5 << "WT_av_sim ";		
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			f5 << "WT_av_sim_" << j << " ";
		}
		f5 << "ML_av_sim " << endl;
	}
	if(this->_optObj==EXACT_SIM_KCS)
	{
		f5 << "WT_av_sim ";		
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			f5 << "WT_av_sim_" << j << " ";
		}
		f5 << "ML_av_sim " << endl;
	}
	for(iterationIndex=0;iterationIndex<this->myItern;iterationIndex++)
	{		
		if(iterationIndex>0 && this->_rhsChange == CHANGE_N)	
		{
			this->I=this->I+this->myStep;
			this->d=this->d+(int)(0.5*(this->myStep));
		}
		
		if(this->_GPmys->psMachines[0]->DistribDef==false)
		{
			
			this->_GPmys->ptDistDEF=false;
			this->processTimes.clear();
			this->processTimes.resize(this->I);
			
			for(int parts=0;parts<this->I;parts++)
				this->processTimes[parts].resize(myServerSize);
			for(int parts=0;parts<this->I;parts++)
			{
				for(int servers=0;servers<myServerSize;servers++)
				{
					if(this->_GPmys->psMachines[servers]->DistribDef==false)
						inproc >> this->processTimes[parts][servers];
				}
			}
		}
		else
		{
			cout << "Generating a new sample path" << endl;
			
			if(this->_rhsChange == CHANGE_N && iterationIndex>0)
			{
				std::vector<double> ttpt;
				ttpt.resize(myServerSize);
				for(int parts=this->I-this->myStep;parts<this->I;parts++)
					this->processTimes.push_back(ttpt);
				
				start = clock();
				for(int i=0;i<myServerSize;i++)
				{					
					
					GenProcessTime(_FailureMDescr,gen,iterationIndex,i);
				}
				end = clock();
				timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";

				for(int i=0;i<this->processTimes.size();i++)
				{
					for(int j=0;j<this->processTimes[i].size();j++)
						outarrivals << this->processTimes[i][j] << " ";
					outarrivals << endl;
				}
			}
			else
			{
				this->processTimes.clear();
				this->processTimes.resize(this->I);
				
				for(int parts=0;parts<this->I;parts++)
					this->processTimes[parts].resize(myServerSize);

				start = clock();
				for(int i=0;i<myServerSize;i++)
				{
					GenProcessTime(_FailureMDescr,gen,iterationIndex,i);
				}
				end = clock();
				timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
				for(int i=0;i<this->processTimes.size();i++)
				{
					for(int j=0;j<this->processTimes[i].size();j++)
						outarrivals << this->processTimes[i][j] << " ";
					outarrivals << endl;
				}
			}
		}
		if(this->_GPmys->mycustomer->arrDef==false)
		{
			this->_GPmys->atDistDEF=false;
			if(!inarr)
				throw "No arrival process has been given as input";
			else
			{
				cout << "Taking Arrival Times" << endl;
				this->arrivalTimes.clear();
				this->arrivalTimes.resize(this->I);
				for(int i=0;i<this->I;++i)
				{
					inarr >> this->arrivalTimes[i];
					if(this->_optObj==EXTENDED_KANBAN||this->_optObj==SIM_EXTENDED_KANBAN||this->_optObj==EXACT_SIM_KBS||
						this->_optObj==KANBAN||this->_optObj==BASESTOCK||
						this->_optObj==EXACT_SIM_KCS||this->_optObj==EXACT_SIM_BS || this->_optObj==EXACT_OPT_BSC || 
						this->_optObj==EXACT_OPT_KSC||this->_optObj==EXACT_OPT_EKCS || 
						this->_optObj==APP_SIM_TBCS || this->_optObj==APP_OPT_TBCS)
					{
						this->demandProcess.push_back(this->arrivalTimes[i]);
						this->arrivalTimes[i]=0.0;
					}
				}

			}
		}
		else
		{
			cout << "Distribution defined for arrivals" << endl;
			this->_GPmys->atDistDEF = true;
			start = clock();
			GenArrivals(gen);
			end = clock();
			timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
			for(int i=0; i< this->demandProcess.size();i++)
				outdemandVec << this->demandProcess[i] << endl;
		}
		
		if(this->_GPmys->sysType == CLOSEDLOOP)
		{
			for(int parts=0;parts<this->I;parts++)
			{
				this->processTimes[parts].resize(this->_GPmys->psMachines.size()+1);
				this->processTimes[parts][this->processTimes[parts].size()-1] = 0.0;
			}
		}

		//startTime = this->cplex.getTime();
		start = clock();
		BuildModel(iterationIndex);
		/*endTime = this->cplex.getTime();*/
		end = clock();
		/*timeFileCPLEX << endTime - startTime << " ";*/
		timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
		
		start = clock();
		Optimize();
		end = clock();
		timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
		

		int transitory(0);
		if(d>0)
			transitory=d;
		else
			transitory=1;
		double res(0.0);
		double dem(0.0);
		double relTime(0.0);

		
		if(this->_optObj==EXACT_OPT_KSC)
		{
			std::cout << "OPTIMIZATION RESULTS" << std::endl;
			for(size_t i=transitory-1;i<this->I;i++)
			{
				res += cplex.getValue(rTime[i][this->z_ks[0].getSize()])-this->demandProcess[i];
				relTime += cplex.getValue(rTime[i][this->z_ks[0].getSize()]);
				dem += this->demandProcess[i];
			}
			std::cout << std::endl;
			std::cout << "TOTAL LATENESS: " << res << std::endl;
			std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
		}
		else if(this->_optObj==EXACT_OPT_BSC)
		{
			std::cout << "OPTIMIZATION RESULTS" << std::endl;
			for(size_t i=transitory-1;i<this->I;i++)
			{
				res += cplex.getValue(rTime[i][this->z_bs[0].getSize()])-this->demandProcess[i];
				relTime += cplex.getValue(rTime[i][this->z_bs[0].getSize()]);
				dem += this->demandProcess[i];
			}
			std::cout << std::endl;
			std::cout << "TOTAL LATENESS: " << res << std::endl;
			std::cout << "AVERAGE LATENESS: " << res/(double(this->I-d)) << std::endl;
		}
		
 		int oldObj(0);
		double foVal(0.0);
		if(this->_optObj!=EXACT_SIM&&this->_optObj!=EXACT_SIM_KBS &&
						this->_optObj!=EXACT_SIM_KCS&&this->_optObj!=EXACT_SIM_BS)
		{
			writeOutput(fout,fout2,outSumYSumS);
			if(this->_GPmys->sysType!=CLOSEDLOOP)
			{
				if(this->_optObj==OPTIMIZATION)
				{
					for(size_t k=0;k < x_s_b.getSize(); k++)
					{
						for(size_t l=0;l<x_s_b[k].getSize();l++)
						{
							foVal = foVal+ this->cplex.getValue(x_s_b[k][l]);
						}
					}
				}

				else if(this->_optObj==EXACT_OPT)
				{
					for(size_t k=0;k < z_buf.getSize(); k++)
					{
						for(size_t l=0;l<z_buf[k].getSize();l++)
						{
							if(this->cplex.getValue(z_buf[k][l])>0.0001)
							{
								foVal = foVal+ k +1;
								f5 << k+1 << " ";
							}
						}
					}
					f5 << endl;
					if(this->delta_feasibility>0.0)
						f5 << this->cplex.getValue(epsilon) << endl;
					f5 << foVal << endl;
				}	
				else if(this->_optObj==EXACT_OPT_BSC)
				{
					for(size_t k=0;k < z_bs.getSize(); k++)
					{
						for(size_t l=0;l<z_bs[k].getSize();l++)
						{
							if(this->cplex.getValue(z_bs[k][l])>0.0001)
							{
								foVal = foVal+ k +1;
								f5 << k+1 << " ";
							}
						}
					}
					f5 << endl;
					if(this->delta_feasibility>0.0)
						f5 << this->cplex.getValue(epsilon) << endl;
					f5 << foVal << endl;
					
				}
				else if(this->_optObj==EXACT_OPT_KSC)
				{
					for(size_t k=0;k < z_ks.getSize(); k++)
					{
						for(size_t l=0;l<z_ks[k].getSize();l++)
						{
							if(this->cplex.getValue(z_ks[k][l])>0.0001)
							{
								foVal = foVal+ k +1;
								f5 << k+1 << " ";
							}
						}
					}
					f5 << endl;
					if(this->delta_feasibility>0.0)
						f5 << this->cplex.getValue(epsilon) << endl;
					f5 << foVal << endl;
				}
				else if(this->_optObj==EXACT_OPT_EKCS)
				{
					for(size_t k=0;k < z_bs.getSize(); k++)
					{
						for(size_t l=0;l<z_bs[k].getSize();l++)
						{
							if(this->cplex.getValue(z_ks[k][l])>0.0001)
							{
								f5 << k+1 << " ";
								foVal = foVal+ k+1;
							}
						}
					}
					f5 << endl;
					
					for(size_t k=0;k < z_ks.getSize(); k++)
					{
						for(size_t l=0;l<z_ks[k].getSize();l++)
						{
							if(this->cplex.getValue(z_ks[k][l])>0.0001)
							{
								foVal = foVal+ k;
								f5 << k << " ";
							}
						}
					}
					f5 << endl;
					if(this->delta_feasibility>0.0)
						f5 << this->cplex.getValue(epsilon) << endl;
					f5 << foVal << endl;
				}
				else if(this->_optObj == BASESTOCK)
				{
					for(size_t k=0;k < x_s_b.getSize(); k++)
					{
						for(size_t l=0;l<x_s_b[k].getSize();l++)
						{
							foVal = foVal+ this->cplex.getValue(x_s_b[k][l]);
						}
					}
					f5 << foVal << endl;
				}
				else if(this->_optObj==KANBAN)
				{
					foVal=0.0;
					for(size_t k=0;k < x_s_k.getSize(); k++)
					{
						for(size_t m=0;m<x_s_k[k].getSize();m++)
						{
							foVal = foVal+this->cplex.getValue(x_s_k[k][m]);
						}
					}
					if(this->SeqModel == false)
						f5 << foVal << " ";
				
					foVal=0.0;
					for(int i=0;i<I;i++)
					{
						for (int j = 0; j < rTime[0].getSize()-1;++j)
						{
							foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
						}
					}
					foVal = foVal/I;
					//-------------check whether the Waiting time cut has to be inserted----//
					if((this->_myOFtype == MIN_WT || this->_myOFtype == MIN_s) && this->optCUTS==true)
					{
						this->boundWTval = foVal;
					}
					else
						this->boundWTval = 0.0;
					
					if(this->SeqModel==false)
						f5 << foVal << " ";

					foVal=0.0;
					for(int i=0;i<I;i++)
					{
						foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
					}
					foVal = foVal/I;
					
					if(this->SeqModel==false)
						f5 << foVal << " ";

					
				}

				else if(this->_optObj == EXTENDED_KANBAN)
				{
					for(size_t k=0;k < x_s_b.getSize(); k++)
					{
						for(size_t l=0;l<x_s_b[k].getSize();l++)
						{
							foVal = foVal+ this->cplex.getValue(x_s_b[k][l]);
						}
						f5 << foVal << endl;
					}
					for(size_t k=0;k < x_s_k.getSize(); k++)
					{
						for(size_t m=0;m<x_s_k[k].getSize();m++)
						{
							foVal = foVal+this->cplex.getValue(x_s_k[k][m]);
						}
						f5 << foVal << endl;
					}
				}
				if(this->_optObj!=KANBAN)
				{
					f5 << foVal << endl;
				}
			}
			else
			{
				if(this->_optObj==EXACT_OPT)
				{
					for(size_t k=0;k < z_pal.getSize(); k++)
					{
						if(this->cplex.getValue(z_pal[k])>0.0001)
							foVal = foVal+ k;
					}
				}	
				else if(this->_optObj==OPTIMIZATION)
				{
					if(this->_myOFtype==MIN_s)
					{
						for(size_t k=0;k < x_s_p.getSize(); k++)
							foVal = foVal+ this->cplex.getValue(x_s_p[k]);
					}
					else
					{
						for(size_t k=0;k < x_b_p.getSize(); k++)
							foVal = foVal+ this->cplex.getValue(x_b_p[k]);
					}
				}
				f5 << foVal << endl;
			}
			
			

			cout << "Ho scritto l'output" << endl;

			if(this->_optObj == KANBAN && this->SeqModel==true && this->_myOFtype==MIN_s)
			{
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				//save the values of time buffer for kanbans
				this->TB_kan.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (Kanban): " << endl;
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_kan[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						this->TB_kan[k][l] = this->cplex.getValue(x_s_k[k][l]);
						cout << this->TB_kan[k][l] << " ";
					}
					cout << endl;
				}
				this->_myOFtype = MIN_WT;
				this->optCUTS = true;
				this->tbCUTS = true;
				
				this->ClearCplexElements();		
				this->createEnvironment();

				start = clock();
				BuildModel(iterationIndex);
				end = clock();
				timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
				
				start = clock();
				Optimize();
				end = clock();
				timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
				/*BuildModel(iterationIndex);
				Optimize();*/
				computeBounds(f3,out_solApprossimata);
				if(iterationIndex==0)
				{
					fout << "SERVICE_LEVEL   " << "TOTAL_LATENESS " << "AVERAGE_LATENESS" << " ";
					for(int j=0;j<this->_GPmys->psMachines.size();j++)
					{
						fout << "WTin_" << j+1 << " ";
					}
					for(int j=0;j<this->_GPmys->psMachines.size();j++)
					{
						fout << "WTOUT_" << j+1 << " ";
					}
					for(int j=0;j<this->_GPmys->psMachines.size();j++)
					{
						fout << "Q_ave_" << j+1 << " ";
					}
					fout << endl;
				}
				writeOutput(fout,fout2,outSumYSumS);

				foVal=0.0;
				for(size_t k=0;k < x_s_k.getSize(); k++)
				{
					for(size_t m=0;m<x_s_k[k].getSize();m++)
					{
						foVal = foVal+this->cplex.getValue(x_s_k[k][m]);
					}
				}
				f5 << foVal << " ";
				
				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					for (int j = 0; j < rTime[0].getSize()-1;++j)
					{
						foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
					}
				}
				foVal = foVal/I;
				
				//-------------check whether the Waiting time cut has to be inserted----//
				this->boundWTval = foVal;
				
				f5 << foVal << " ";

				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
				}
				foVal = foVal/I;
				
				f5 << foVal << " ";

			}
			else if(this->_optObj == KANBAN && this->SeqModel==true && this->_myOFtype==MIN_WT)
			{
				this->_myOFtype = MIN_s;
				this->optCUTS = true;

				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					for (int j = 0; j < rTime[0].getSize()-1;++j)
					{
						foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
					}
				}
				foVal = foVal/I;
				
				//-------------check whether the Waiting time cut has to be inserted----//
				this->boundWTval = foVal;
				
				this->ClearCplexElements();		
				this->createEnvironment();

				BuildModel(iterationIndex);
				Optimize();
				computeBounds(f3,out_solApprossimata);
				if(iterationIndex==0)
				{
					fout << "SERVICE_LEVEL  " << "TOTAL_LATENESS: " << "AVERAGE_LATENESS" << " ";
					for(int j=0;j<this->_GPmys->psMachines.size();j++)
					{
						fout << "WTin_" << j+1 << " ";
					}
					for(int j=0;j<this->_GPmys->psMachines.size();j++)
					{
						fout << "WTOUT_" << j+1 << " ";
					}
					for(int j=0;j<this->_GPmys->psMachines.size();j++)
					{
						fout << "Q_ave_" << j+1 << " ";
					}
					fout << endl;
				}
				writeOutput(fout,fout2,outSumYSumS);

				foVal=0.0;
				for(size_t k=0;k < x_s_k.getSize(); k++)
				{
					for(size_t m=0;m<x_s_k[k].getSize();m++)
					{
						foVal = foVal+this->cplex.getValue(x_s_k[k][m]);
					}
				}
				f5 << foVal << " ";
				
				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					for (int j = 0; j < rTime[0].getSize()-1;++j)
					{
						foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
					}
				}
				foVal = foVal/I;
								
				f5 << foVal << " ";

				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
				}
				foVal = foVal/I;
				
				f5 << foVal << " ";

			}
			
			if(this->_optObj!=EXTENDED_KANBAN&&this->_optObj!=KANBAN&&this->_optObj!=BASESTOCK &&
				this->_optObj!=EXACT_OPT_BSC && this->_optObj!=EXACT_OPT_KSC && 
				this->_optObj!=EXACT_OPT_EKCS && this->_optObj!=APP_OPT_TBCS)
			{
				if(this->_optObj!=EXACT_OPT)
				{
					this->_optObj=SIMULATION;
					if(this->_GPmys->sysType==FLOWLINE)
					{
						cout << "The system is a flow line" << endl;
						int mypsBuffSize(0);
						mypsBuffSize = this->_GPmys->psBuff.size();
						this->_GPmys->TB_cap.resize(this->mycap[0]);
						cout << this->mycap[0] << endl;
						cout << "buffer size: " << mypsBuffSize << endl;
						cout << "Time Buffer values: " << endl;
						for(int k=0;k<this->mycap[0];k++)
						{
							this->_GPmys->TB_cap[k].resize(mypsBuffSize);
							for(int l=0;l<mypsBuffSize;l++)
							{				
								if(this->mycap[l]>this->mycap[0])
									this->_GPmys->TB_cap.resize(this->mycap[l]);
								this->_GPmys->TB_cap[k][l] = this->cplex.getValue(x_s_b[k][l]);
								cout << this->_GPmys->TB_cap[k][l] << " ";
							}
							cout << endl;
						}
					}
					else if(this->_GPmys->sysType==CLOSEDLOOP && this->_myOFtype == MIN_s)
					{
						this->_GPmys->TB_cap.resize(this->myPal);
						for(int k=0;k<this->myPal;k++)
						{
							this->_GPmys->TB_cap[k].resize(1);
							this->_GPmys->TB_cap[k][0]=this->cplex.getValue(x_s_p[k]);
						}
					}
					else if(this->_GPmys->sysType==CLOSEDLOOP && this->_myOFtype == MIN_b)
					{
						this->_GPmys->TB_cap.resize(this->myPal);
						for(int k=0;k<this->myPal;k++)
						{
							this->_GPmys->TB_cap[k].resize(1);
							this->_GPmys->TB_cap[k][0]=this->cplex.getValue(x_b_p[k]);
						}
					}
				}
				else
				{
					this->_optObj=EXACT_SIM;
					if(this->_GPmys->sysType==FLOWLINE)
					{
						cout << "The system is a flow line" << endl;
						int mypsBuffSize(0);
						mypsBuffSize = this->_GPmys->psBuff.size();
						
						for(int l=0;l<mypsBuffSize;l++)
						{
							double tempCap(0.0);
							bool foundCap=false;
							int k=0;
							while(foundCap==false && k<this->mycap[l])
							{				
								if(this->cplex.getValue(z_buf[k][l])>0.001)
								{
									tempCap=k+1;
									foundCap=true;
								}
								else
									k++;
							}
							this->_GPmys->psBuff[l]->capacity=tempCap;
						}
					}
					else if(this->_GPmys->sysType==CLOSEDLOOP)
					{
						double tempCap(0.0);
						bool foundCap=false;
						int k=0;
						while(foundCap==false && k<this->myPal)
						{				
							if(this->cplex.getValue(z_pal[k])>0.001)
							{
								tempCap=k+1;
								foundCap=true;
							}
							else
								k++;
						}
						this->myPal=tempCap;
					}
				}
			}
			else
			{
				
				if(this->_optObj == BASESTOCK)
				{
					oldObj=7;
					this->_optObj = SIM_BASESTOCK;
				}
				else if(this->_optObj == EXACT_OPT_BSC)
				{
					oldObj=9;
					this->_optObj = EXACT_SIM_BS;
				}
				else if(this->_optObj == KANBAN)
				{
					oldObj=8;
					this->_optObj = SIM_KANBAN;
				}
				else if(this->_optObj == EXACT_OPT_KSC)
				{
					oldObj=10;
					this->_optObj = EXACT_SIM_KCS;
				}
				else if(this->_optObj == EXACT_OPT_EKCS)
				{
					oldObj=11;
					this->_optObj = EXACT_SIM_KBS;
				}
				else if(this->_optObj == APP_OPT_TBCS)
				{
					oldObj=12;
					this->_optObj = APP_SIM_TBCS;
				}
				else
					this->_optObj = SIM_EXTENDED_KANBAN;
				cout << "The system is a supply chain" << endl;
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				if(oldObj==7||this->_optObj==SIM_EXTENDED_KANBAN)
				{
					this->TB_bs.resize(this->mycap[0]);
					this->TB_kan.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Maximum Base stock size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (main base stock): " << endl;

					for(int k=0;k<this->mycap[0];k++)
					{
						this->TB_bs[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							this->TB_bs[k][l] = this->cplex.getValue(x_s_b[k][l]);
							cout << this->TB_bs[k][l] << " ";
						}
						cout << endl;
					}
				}
				if((oldObj==8 && (this->SeqModel== false || this->_myOFtype!=MIN_WT))||
					this->_optObj==SIM_EXTENDED_KANBAN)
				{
					this->TB_kan.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Kanban size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (Kanban): " << endl;
					for(int k=0;k<this->mycap[0];k++)
					{
						this->TB_kan[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							this->TB_kan[k][l] = this->cplex.getValue(x_s_k[k][l]);
							cout << this->TB_kan[k][l] << " ";
						}
						cout << endl;
					}
				}
				else if((oldObj==12 )||	this->_optObj==SIM_EXTENDED_KANBAN)
				{
					this->TB_kan.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Kanban size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (Kanban): " << endl;
					for(int k=0;k<this->mycap[0];k++)
					{
						this->TB_kan[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							this->TB_kan[k][l] = this->cplex.getValue(x_s_k[k][l]);
							cout << this->TB_kan[k][l] << " ";
						}
						cout << endl;
					}
				}
				else if(oldObj==9)
				{
					int mypsBuffSize(0);
					mypsBuffSize = this->_GPmys->psBuff.size();
					this->IP_bs.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Maximum Base stock size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (main base stock): " << endl;

					this->_GPmys->psBaseStock.resize(mypsBuffSize);
					for(int k=0;k<this->mycap[0];k++)
					{
						this->IP_bs[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							if(this->cplex.getValue(z_bs[k][l])>0.001)
							{
								this->IP_bs[k][l] = this->cplex.getValue(z_bs[k][l]);
								this->_GPmys->psBaseStock[l]->capacity=k+1;
							}
							else
								this->IP_bs[k][l] = 0;
							
							cout << this->IP_bs[k][l] << " ";
						}
						cout << endl;
					}
					for(int l=0;l<mypsBuffSize;l++)
					{
						int countKK(0);
						for(int k=0;k<this->mycap[0];k++)
						{				
							if(this->IP_bs[k][l]==0)
							{
								countKK++;
							}							
						}
						if(countKK==this->mycap[0])
						{
							this->IP_bs[0][l] = 1;
							this->_GPmys->psBaseStock[l]->capacity=1;
						}

					}

				}
				else if(oldObj==10)
				{
					int mypsBuffSize(0);
					mypsBuffSize = this->_GPmys->psBuff.size();
					this->IP_ks.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Maximum Kanban size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (kanban): " << endl;

					this->_GPmys->psKanban.resize(mypsBuffSize);
					for(int k=0;k<this->mycap[0];k++)
					{
						this->IP_ks[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							if(this->cplex.getValue(z_ks[k][l])>0.001)
							{
								this->IP_ks[k][l] = this->cplex.getValue(z_ks[k][l]);
								this->_GPmys->psKanban[l]->capacity=k+1;
							}
							else
								this->IP_ks[k][l] = 0;
							
							cout << this->IP_ks[k][l] << " ";
						}
						cout << endl;
					}
					for(int l=0;l<mypsBuffSize;l++)
					{
						int countKK(0);
						for(int k=0;k<this->mycap[0];k++)
						{				
							if(this->IP_ks[k][l]==0)
							{
								countKK++;
							}							
						}
						if(countKK==this->mycap[0])
						{
							this->IP_ks[0][l] = 1;
							this->_GPmys->psKanban[l]->capacity=1;
						}

					}

				}
				else if(oldObj==11)
				{
					int mypsBuffSize(0);
					mypsBuffSize = this->_GPmys->psBuff.size();
					this->IP_ks.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Maximum Kanban size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (kanban): " << endl;

					this->_GPmys->psKanban.resize(mypsBuffSize);
					for(int k=0;k<this->mycap[0];k++)
					{
						this->IP_ks[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							if(this->cplex.getValue(z_ks[k][l])>0.001)
							{
								this->IP_ks[k][l] = this->cplex.getValue(z_ks[k][l]);
								this->_GPmys->psKanban[l]->capacity=k+1;
							}
							else
								this->IP_ks[k][l] = 0;
							
							cout << this->IP_ks[k][l] << " ";
						}
						cout << endl;
					}
					for(int l=0;l<mypsBuffSize;l++)
					{
						int countKK(0);
						for(int k=0;k<this->mycap[0];k++)
						{				
							if(this->IP_ks[k][l]==0)
							{
								countKK++;
							}							
						}
						if(countKK==this->mycap[0])
						{
							this->IP_ks[0][l] = 1;
							this->_GPmys->psKanban[l]->capacity=1;
						}

					}

					
					mypsBuffSize = this->_GPmys->psBuff.size();
					this->IP_bs.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "Maximum Base stock size: " << this->mycap[0] << endl;
					cout << "Time Buffer values (main base stock): " << endl;

					this->_GPmys->psBaseStock.resize(mypsBuffSize);
					for(int k=0;k<this->mycap[0];k++)
					{
						this->IP_bs[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							if(this->cplex.getValue(z_bs[k][l])>0.001)
							{
								this->IP_bs[k][l] = this->cplex.getValue(z_bs[k][l]);
								this->_GPmys->psBaseStock[l]->capacity=k+1;
							}
							else
								this->IP_bs[k][l] = 0;
							
							cout << this->IP_bs[k][l] << " ";
						}
						cout << endl;
					}
					for(int l=0;l<mypsBuffSize;l++)
					{
						int countKK(0);
						for(int k=0;k<this->mycap[0];k++)
						{				
							if(this->IP_bs[k][l]==0)
							{
								countKK++;
							}							
						}
						if(countKK==this->mycap[0])
						{
							this->IP_bs[0][l] = 1;
							this->_GPmys->psBaseStock[l]->capacity=1;
						}

					}

				}
			}

			
			this->ClearCplexElements();		
			this->createEnvironment();
			
			start = clock();
			BuildModel(iterationIndex);
			end = clock();
			timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
			
			start = clock();
			Optimize();
			end = clock();
			timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
			/*BuildModel(iterationIndex);
			Optimize();*/
			computeBounds(f3,out_solApprossimata);
			if(iterationIndex==0)
			{
				fout << "SERVICE_LEVEL   " << "TOTAL_LATENESS: " << "AVERAGE_LATENESS" << " ";
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WTin_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WTOUT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_" << j+1 << " ";
				}
				fout << endl;
			}
			writeOutput(fout,fout2,outSumYSumS);
			
			if(oldObj==8)
			{
				/*for(int i=0;i<I;i++)
				{
					for (int j = 0; j < rTime[0].getSize()-1;++j)
					{
						foVal += this->cplex.getValue(rTime[i][j+1]) + this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) + this->cplex.getValue(rTime[i][j]);
					}
				}
				f5 << foVal << " ";*/
				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					for (int j = 0; j < rTime[0].getSize()-1;++j)
					{
						foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
					}
				}
				foVal = foVal/I;
				f5 << foVal << " ";
				
				for(int j=0;j < rTime[0].getSize()-1;j++)
				{
					foVal=0.0;
					for (int i = 0; i < I;++i)
					{
						foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
					}
					foVal = foVal/I;
					f5 << foVal << " ";
				}
				foVal=0.0;
				for(int i=0;i<I;i++)
				{
					foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
				}
				f5 << foVal/I << endl;
			}
			if(this->_optObj!=SIM_EXTENDED_KANBAN && 
				this->_optObj!=SIM_KANBAN &&
				this->_optObj!=SIM_BASESTOCK)
				writeReplicateResults(f4,r);
			_GPmys->TB_cap.clear();
			this->TB_bs.clear();
			this->TB_kan.clear();
			ClearCplexElements();

			if(this->_optObj!=SIM_EXTENDED_KANBAN && 
				this->_optObj!=SIM_KANBAN &&
				this->_optObj!=SIM_BASESTOCK&&
				this->_optObj != EXACT_SIM)
				_optObj = OPTIMIZATION;
			
			if(this->_optObj == EXACT_SIM)
				this->_optObj = EXACT_OPT;
			if(oldObj==7)
				_optObj = BASESTOCK;
			else if(oldObj==8)
			{
				_optObj = KANBAN;
				if(this->SeqModel == true && this->_myOFtype == MIN_WT)
				{
					this->_myOFtype = MIN_s;
					this->boundWTval = 0.0;
				}
				else if(this->SeqModel == true && this->_myOFtype == MIN_s)
				{
					this->_myOFtype = MIN_WT;
					this->boundWTval = 0.0;
				}
			}
			else if(oldObj==12)
			{
				_optObj = APP_OPT_TBCS;
			}
			else if(oldObj==9)
				this->_optObj = EXACT_OPT_BSC;
			else if(oldObj==10)
				this->_optObj = EXACT_OPT_KSC;
			else if(oldObj==11)
				this->_optObj = EXACT_OPT_EKCS;
			else 
			{
				if(this->_GPmys->sysType==SUPPLYCHAIN)
					_optObj = EXTENDED_KANBAN;
			}

			if(this->_optObj==SIM_KANBAN && this->_deoScope==0)
				this->_optObj = SIM_KANBAN;
			if(iterationIndex < this->myItern-1)
			{
				createEnvironment();
				timeFileCPLEX << endl;
			}
		}
		//----------------------------------------------------//
		//----------------------------------------------------//
		//-------------IF PERFORMING EXACT SIMULATION---------//
		//----------------------------------------------------//
		else
		{
			foVal=0.0;
			for(int i=0;i<I;i++)
			{
				for (int j = 0; j < rTime[0].getSize()-1;++j)
				{
					foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
				}
			}
			foVal = foVal/I;
			f5 << foVal << " ";
			
			for(int j=0;j < rTime[0].getSize()-1;j++)
			{
				foVal=0.0;
				for (int i = 0; i < I;++i)
				{
					foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
				}
				foVal = foVal/I;
				f5 << foVal << " ";
			}
			foVal=0.0;
			for(int i=0;i<I;i++)
			{
				foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
			}
			f5 << foVal/I << endl;

			if(iterationIndex==0)
			{
				fout << "SERVICE_LEVEL  " << "TOTAL_LATENESS: " << "AVERAGE_LATENESS" << " ";
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WTin_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WTOUT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_" << j+1 << " ";
				}
				fout << endl;
			}
			writeOutput(fout,fout2,outSumYSumS);
			writeReplicateResults(f4,r);
			this->ClearCplexElements();
			if(iterationIndex < this->myItern-1)
			{
				this->createEnvironment();
				timeFileCPLEX << endl;
			}
			
		}
		
	}
	if(this->myItern>1)
		f5 << endl;
	outarrivals.close();
	outdemandVec.close();
	timeFileCPLEX.close();
	outSumYSumS.close();
}
void App_OpModel::SIMonly(std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _FailureMDescr,
							std::ofstream & fout,std::ifstream & fout2,std::ofstream & f3,
							std::ofstream & f4,std::ofstream & f5,std::ofstream & out_solApprossimata,
							std::ifstream & inproc,std::ifstream & inarr, int r)
{
	std::ofstream outarrivals;
	outarrivals.open("OUTPUT/ProcessTime.txt");
	std::ofstream outSumYSumS;
	outSumYSumS.open("OUTPUT\\sumYsumS.txt");

	int seed=r;
	int iterationIndex(0);
	stochasticProperty::base_generator_type gen(seed);
	int myServerSize(0);
	myServerSize = this->_GPmys->psMachines.size();
	
	if(this->_optObj == SIM_KANBAN || this->_optObj == SIM_BASESTOCK || this->_optObj == SIM_EXTENDED_KANBAN
		|| this->_optObj == EXACT_SIM_KCS || this->_optObj == EXACT_SIM_BS || this->_optObj== EXACT_SIM_KBS || this->_optObj == APP_SIM_TBCS)
	{
		f5 << "WT_av_sim ";		
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			f5 << "WT_av_sim_" << j << " ";
		}
		f5 << "ML_av_sim " << endl;
	}

	for(iterationIndex=0;iterationIndex<this->myItern;iterationIndex++)
	{		
		if(iterationIndex>0 && this->_rhsChange == CHANGE_N)	
		{
			this->I=this->I+this->myStep;
			this->d=this->d+(int)(0.5*(this->myStep));
		}
		
		if(this->_GPmys->psMachines[0]->DistribDef==false)
		{
			
			this->_GPmys->ptDistDEF=false;
			this->processTimes.clear();
			this->processTimes.resize(this->I);
			
			for(int parts=0;parts<this->I;parts++)
				this->processTimes[parts].resize(myServerSize);
			for(int parts=0;parts<this->I;parts++)
			{
				for(int servers=0;servers<myServerSize;servers++)
				{
					if(this->_GPmys->psMachines[servers]->DistribDef==false)
						inproc >> this->processTimes[parts][servers];
				}
			}
		}
		else
		{
			cout << "Generating a new sample path" << endl;
			/*std::vector<std::vector<double> > tempPT_expo;*/
			
			if(this->_rhsChange == CHANGE_N && iterationIndex>0)
			{
				std::vector<double> ttpt;
				ttpt.resize(myServerSize);
				for(int parts=this->I-this->myStep;parts<this->I;parts++)
					this->processTimes.push_back(ttpt);
				for(int i=0;i<myServerSize;i++)
				{					
					GenProcessTime(_FailureMDescr,gen,iterationIndex,i);
				}

				for(int i=0;i<this->processTimes.size();i++)
				{
					for(int j=0;j<this->processTimes[i].size();j++)
						outarrivals << this->processTimes[i][j] << " ";
					outarrivals << endl;
				}
			}
			else
			{
				this->processTimes.clear();
				this->processTimes.resize(this->I);
				
				for(int parts=0;parts<this->I;parts++)
					this->processTimes[parts].resize(myServerSize);

				for(int i=0;i<myServerSize;i++)
				{
					GenProcessTime(_FailureMDescr,gen,iterationIndex,i);
				}

				for(int i=0;i<this->processTimes.size();i++)
				{
					for(int j=0;j<this->processTimes[i].size();j++)
						outarrivals << this->processTimes[i][j] << " ";
					outarrivals << endl;
				}
			}
		}
		if(this->_GPmys->mycustomer->arrDef==false)
		{
			this->_GPmys->atDistDEF=false;
			if(!inarr)
				throw "No arrival process has been given as input";
			else
			{
				cout << "Taking Arrival Times" << endl;
				this->arrivalTimes.clear();
				this->arrivalTimes.resize(this->I);
				for(int i=0;i<this->I;++i)
				{
					inarr >> this->arrivalTimes[i];
					if(this->_optObj==EXTENDED_KANBAN||this->_optObj==SIM_EXTENDED_KANBAN||
						this->_optObj==EXACT_SIM_KBS|| this->_optObj == SIM_BASESTOCK ||
						this->_optObj==KANBAN|| this->_optObj == SIM_KANBAN ||
						this->_optObj==BASESTOCK || this->_optObj == APP_SIM_TBCS ||
						this->_optObj==EXACT_SIM_KCS||this->_optObj==EXACT_SIM_BS||this->_optObj==EXACT_OPT_BSC ||
						this->_optObj==EXACT_OPT_KSC || this->_optObj==EXACT_OPT_EKCS)
					{
						this->demandProcess.push_back(this->arrivalTimes[i]);
						this->arrivalTimes[i]=0.0;
					}
				}

			}
		}
		else
		{
			cout << "Distribution defined for arrivals" << endl;
			this->_GPmys->atDistDEF = true;
			GenArrivals(gen);
		}
		
		if(this->_GPmys->sysType == CLOSEDLOOP)
		{
			for(int parts=0;parts<this->I;parts++)
			{
				this->processTimes[parts].resize(this->_GPmys->psMachines.size()+1);
				this->processTimes[parts][this->processTimes[parts].size()-1] = 0.0;
			}
		}

		int oldObj(0);
		double foVal(0.0);
		if(this->_optObj!=EXACT_SIM&&this->_optObj!=EXACT_SIM_KBS &&
						this->_optObj!=EXACT_SIM_KCS&&this->_optObj!=EXACT_SIM_BS)
		{
			
			if(this->_optObj==SIMULATION)
			{
				if(this->_GPmys->sysType==FLOWLINE)
				{
					cout << "The system is a flow line" << endl;
					int mypsBuffSize(0);
					mypsBuffSize = this->_GPmys->psBuff.size();
					this->_GPmys->TB_cap.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "buffer size: " << mypsBuffSize << endl;
					cout << "Time Buffer values: " << endl;
					for(int k=0;k<this->mycap[0];k++)
					{
						this->_GPmys->TB_cap[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							if(this->mycap[l]>this->mycap[0])
								this->_GPmys->TB_cap.resize(this->mycap[l]);
							fout2 >> this->_GPmys->TB_cap[k][l];// = this->cplex.getValue(x_s_b[k][l]);
							//cout << this->_GPmys->TB_cap[k][l] << " ";
						}
						//cout << endl;
					}
				}
				else if(this->_GPmys->sysType==CLOSEDLOOP && this->_myOFtype == MIN_s)
				{
					this->_GPmys->TB_cap.resize(this->myPal);
					for(int k=0;k<this->myPal;k++)
					{
						this->_GPmys->TB_cap[k].resize(1);
						fout2 >> this->_GPmys->TB_cap[k][0];//=this->cplex.getValue(x_s_p[k]);
					}
				}
				else if(this->_GPmys->sysType==CLOSEDLOOP && this->_myOFtype == MIN_b)
				{
					this->_GPmys->TB_cap.resize(this->myPal);
					for(int k=0;k<this->myPal;k++)
					{
						this->_GPmys->TB_cap[k].resize(1);
						fout2 >> this->_GPmys->TB_cap[k][0];//=this->cplex.getValue(x_b_p[k]);
					}
				}
			}
			else if(this->_optObj == SIM_EXTENDED_KANBAN && iterationIndex==0)
			{
				cout << "The system is a supply chain" << endl;
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				this->TB_bs.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (base stock): " << endl;
				std::string strFname;
				fout2 >> strFname;
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_bs[k].resize(mypsBuffSize);
					
					for(int l=0;l<mypsBuffSize;l++)
					{				
						fout2 >> this->TB_bs[k][l];
					}
				}
				fout2 >> strFname;
				this->TB_kan.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (Kanban): " << endl;
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_kan[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						fout2 >> this->TB_kan[k][l];
					}
				}				
			}
			else if(((this->_optObj == SIM_KANBAN || this->_optObj == APP_SIM_TBCS)) && iterationIndex==0)
			{
				cout << "The system is a supply chain" << endl;
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				/*this->TB_bs.resize(this->mycap[0]);*/
				double temp(0.0);
				cout << this->mycap[0] << endl;
				cout << "Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (base stock): " << endl;
				std::string strFname;
				fout2 >> strFname;
				//for(int k=0;k<this->mycap[0];k++)
				//{
				//	/*this->TB_bs[k].resize(mypsBuffSize);*/
				//	
				//	for(int l=0;l<mypsBuffSize;l++)
				//	{				
				//		fout2 >> temp;
				//	}
				//}
				//fout2 >> strFname;
				this->TB_kan.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (Kanban): " << endl;
				if(iterationIndex==0)
				{
					for(int k=0;k<this->mycap[0];k++)
					{
						this->TB_kan[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							fout2 >> this->TB_kan[k][l];
						}
					}
				}
			}
			else if(this->_optObj == SIM_BASESTOCK && iterationIndex==0)
			{
				cout << "The system is a supply chain" << endl;
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				this->TB_bs.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (base stock): " << endl;
				std::string strFname;
				fout2 >> strFname;
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_bs[k].resize(mypsBuffSize);
					
					for(int l=0;l<mypsBuffSize;l++)
					{				
						fout2 >> this->TB_bs[k][l];
					}
				}
				/*fout2 >> strFname;
				this->TB_kan.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (Kanban): " << endl;
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_kan[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						fout2 >> this->TB_kan[k][l];
					}
				}			*/	
			}
			this->ClearCplexElements();		
			this->createEnvironment();

			BuildModel(iterationIndex);
			Optimize();
			if(this->_optObj == SIM_KANBAN || this->_optObj == SIM_BASESTOCK || this->_optObj == SIM_EXTENDED_KANBAN || 
				this->_optObj == APP_SIM_TBCS ||this->_optObj == EXACT_SIM_KCS || this->_optObj == EXACT_SIM_BS || this->_optObj == EXACT_SIM_KBS)
			{
				if(!this->verifySolution())
				{
					foVal=0.0;
					for(int i=0;i<I;i++)
					{
						for (int j = 0; j < rTime[0].getSize()-1;++j)
						{
							foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
						}
					}
					foVal = foVal/I;
					f5 << foVal << " ";
					
					for(int j=0;j < rTime[0].getSize()-1;j++)
					{
						foVal=0.0;
						for (int i = 0; i < I;++i)
						{
							foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
						}
						foVal = foVal/I;
						f5 << foVal << " ";
					}
					foVal=0.0;
					for(int i=0;i<I;i++)
					{
						foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
					}
					f5 << foVal/I << endl;
				}
			}
			computeBounds(f3,out_solApprossimata);
			if(iterationIndex==0)
			{
				fout << "Ltot " << "Lave" << " ";
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WT_in_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WT_OUT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_in_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_out_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_" << j+1 << " ";
				}
				fout << "SL" << endl;
				
				outSumYSumS << "SERVICE_LEVEL   " << "TOTAL_LATENESS: " << "AVERAGE_LATENESS" << " ";
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << "WTin_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << "WTOUT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << "Q_ave_" << j+1 << " ";
				}
				outSumYSumS << endl;
			}
			writeOutputSimulation(fout,outSumYSumS);
			for(int i=0;i<this->I;i++)
			{
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
					outarrivals << this->processTimes[i][j] << " ";
				outarrivals << endl;
			}
			if(this->_optObj!=SIM_EXTENDED_KANBAN && this->_optObj!=SIM_KANBAN && this->_optObj!=SIM_BASESTOCK)
				writeReplicateResults(f4,r);
			/*_GPmys->TB_cap.clear();
			this->TB_bs.clear();
			this->TB_kan.clear();*/
			ClearCplexElements();

			if(iterationIndex < this->myItern-1)
				createEnvironment();
		}
		else
		{
			if(this->_optObj == EXACT_SIM_KCS || this->_optObj == EXACT_SIM_BS || this->_optObj == EXACT_SIM_KBS)
			{
				cout << "The system is a supply chain" << endl;
				int myKanbanSize(0);
				int myBasestockSize(0);
				myKanbanSize = this->_GPmys->psMachines.size();
				myBasestockSize=myKanbanSize;
				
				if(this->_optObj == EXACT_SIM_KCS && iterationIndex==0)
				{
					cout << "Kanban values: " << endl;
					/*std::string strFname;
					fout2 >> strFname;
					cout << strFname;*/
					for(int k=0;k<myKanbanSize;k++)
					{				
						fout2 >> this->_GPmys->psKanban[k]->capacity;
						cout << this->_GPmys->psKanban[k]->capacity << endl;
					}
				}
				else if(this->_optObj == EXACT_SIM_BS && iterationIndex==0)
				{
					cout << "Basestock values: " << endl;
					
					for(int k=0;k<myBasestockSize;k++)
					{				
						fout2 >> this->_GPmys->psBaseStock[k]->capacity;
					}
				}
				else if (this->_optObj == EXACT_SIM_KBS && iterationIndex==0)
				{
					cout << "Basestock & Kanban values: " << endl;
					
					for(int k=0;k<myBasestockSize*2;k++)
					{				
						if(k<myBasestockSize)
							fout2 >> this->_GPmys->psBaseStock[k]->capacity;
						else
							fout2 >> this->_GPmys->psKanban[k-myBasestockSize]->capacity;
					}
				}
			}
			else
			{
				if(this->_GPmys->sysType==FLOWLINE)
				{
					cout << "Simulating an Open Tandem Line" << endl;
					int myBufferSize(0);
				
					myBufferSize = this->_GPmys->psBuff.size();
				
					cout << "Buffer values: " << endl;
					
					for(int k=0;k<myBufferSize;k++)
					{				
						fout2 >> this->_GPmys->psBuff[k]->capacity;
					}
				}
				else
				{
					cout << "Simulating a Closed Tandem Line" << endl;
				
					cout << "Pallet values: " << endl;				
					
					fout2 >> this->myPal;
				}
			}
			BuildModel(iterationIndex);
			Optimize();
			if(this->_optObj == EXACT_SIM_KCS || this->_optObj == EXACT_SIM_BS || this->_optObj == EXACT_SIM_KBS)
			{
				if(!this->verifySolution())
				{
					foVal=0.0;
					for(int i=0;i<I;i++)
					{
						for (int j = 0; j < rTime[0].getSize()-1;++j)
						{
							foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
						}
					}
					foVal = foVal/I;
					f5 << foVal << " ";
					
					for(int j=0;j < rTime[0].getSize()-1;j++)
					{
						foVal=0.0;
						for (int i = 0; i < I;++i)
						{
							foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
						}
						foVal = foVal/I;
						f5 << foVal << " ";
					}
					foVal=0.0;
					for(int i=0;i<I;i++)
					{
						foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
					}
					f5 << foVal/I << endl;
				}
			}
			if(iterationIndex==0)
			{
				fout << "Ltot " << "Lave" << " ";
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WT_in_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WT_OUT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "WT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_in_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_out_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					fout << "Q_ave_" << j+1 << " ";
				}
				fout << "SL" << endl;
				
				outSumYSumS << "SERVICE_LEVEL   " << "TOTAL_LATENESS: " << "AVERAGE_LATENESS" << " ";
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << "WTin_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << "WTOUT_" << j+1 << " ";
				}
				for(int j=0;j<this->_GPmys->psMachines.size();j++)
				{
					outSumYSumS << "Q_ave_" << j+1 << " ";
				}
				outSumYSumS << endl;
			}
			writeOutputSimulation(fout,outSumYSumS);
			writeReplicateResults(f4,r);
			this->ClearCplexElements();
			if(iterationIndex < this->myItern-1)
				this->createEnvironment();
		}
		
	}
	if(this->myItern>1)
		f5 << endl;
	outarrivals.close();
	outSumYSumS.close();
}
void App_OpModel::OPTonly(std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > _FailureMDescr,
							std::ofstream & fout,std::ofstream & fout2,std::ofstream & f3,
							std::ofstream & f4,std::ofstream & f5,std::ofstream & out_solApprossimata,
							std::ifstream & inproc,std::ifstream & inarr, int r)
{
	std::ofstream outSumYSumS;
	outSumYSumS.open("OUTPUT\\sumYsumS.txt");
	std::ofstream outarrivals;
	outarrivals.open("OUTPUT/ProcessTime.txt");
	std::ofstream timeFileCPLEX;
	timeFileCPLEX.open("OUTPUT/AlgorithmPerformance.txt");
	timeFileCPLEX << "Sample Generation for PT" << " Demand Sample Generation " << " Opt Model Gen" <<
		" Optimization " <<endl;

	int seed=r;
	int iterationIndex(0);
	stochasticProperty::base_generator_type gen(seed);
	int myServerSize(0);
	myServerSize = this->_GPmys->psMachines.size();
	time_t start, end;
	if(this->_optObj==KANBAN)
	{
		/*if(this->_myOFtype == MIN_s)
		{*/
		f5 << "S_opt ";
		f5 << "WT_opt " ;
		f5 << "ML_av_opt ";
		f5 << "WT_av_sim ";		
		for(int j=0;j<this->_GPmys->psMachines.size();j++)
		{
			f5 << "WT_av_sim_" << j << " ";
		}
		f5 << "ML_av_sim " << endl;
	}
	for(iterationIndex=0;iterationIndex<this->myItern;iterationIndex++)
	{		
		if(iterationIndex>0 && this->_rhsChange == CHANGE_N)	
		{
			this->I=this->I+this->myStep;
			this->d=this->d+(int)(0.5*(this->myStep));
		}
		
		if(this->_GPmys->psMachines[0]->DistribDef==false)
		{
			
			this->_GPmys->ptDistDEF=false;
			this->processTimes.clear();
			this->processTimes.resize(this->I);
			
			for(int parts=0;parts<this->I;parts++)
				this->processTimes[parts].resize(myServerSize);
			for(int parts=0;parts<this->I;parts++)
			{
				for(int servers=0;servers<myServerSize;servers++)
				{
					if(this->_GPmys->psMachines[servers]->DistribDef==false)
						inproc >> this->processTimes[parts][servers];
				}
			}
		}
		else
		{
			cout << "Generating a new sample path" << endl;
			
			if(this->_rhsChange == CHANGE_N && iterationIndex>0)
			{
				std::vector<double> ttpt;
				ttpt.resize(myServerSize);
				for(int parts=this->I-this->myStep;parts<this->I;parts++)
					this->processTimes.push_back(ttpt);
				start = clock();
				
				if(this->mySampleAlgo==LATINHYPERCUBE)
				{
					for(int i=0;i<myServerSize;i++)
					{
						GenLHSProcessTime(_FailureMDescr,gen,iterationIndex,i);
					}
				}					
				else
				{
					for(int i=0;i<myServerSize;i++)
					{
						GenProcessTime(_FailureMDescr,gen,iterationIndex,i);
					}
				}
				end = clock();
				timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";

				for(int i=0;i<this->processTimes.size();i++)
				{
					for(int j=0;j<this->processTimes[i].size();j++)
						outarrivals << this->processTimes[i][j] << " ";
					outarrivals << endl;
				}
			}
			else if((this->alphaLessi==0)||((this->alphaLessi>0)&&(iterationIndex==0))||((this->alphaLessi>0)&&(iterationIndex>0)&&(this->myStep==0)))
			{
				this->processTimes.clear();
				this->processTimes.resize(this->I);
				
				for(int parts=0;parts<this->I;parts++)
					this->processTimes[parts].resize(myServerSize);

				start = clock();
				for(int i=0;i<myServerSize;i++)
				{
					GenProcessTime(_FailureMDescr,gen,iterationIndex,i);
				}
				end = clock();
				timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";

				for(int i=0;i<this->processTimes.size();i++)
				{
					for(int j=0;j<this->processTimes[i].size();j++)
						outarrivals << this->processTimes[i][j] << " ";
					outarrivals << endl;
				}
			}
		}
		if(this->_GPmys->mycustomer->arrDef==false)
		{
			this->_GPmys->atDistDEF=false;
			if(!inarr)
				throw "No arrival process has been given as input";
			else
			{
				cout << "Taking Arrival Times" << endl;
				this->arrivalTimes.clear();
				this->arrivalTimes.resize(this->I);
				for(int i=0;i<this->I;++i)
				{
					inarr >> this->arrivalTimes[i];
					if(this->_optObj==EXTENDED_KANBAN||this->_optObj==KANBAN||this->_optObj==BASESTOCK||
						this->_optObj==EXACT_OPT_BSC || this->_optObj==EXACT_OPT_KSC|| 
						this->_optObj==EXACT_OPT_EKCS)
					{
						this->demandProcess.push_back(this->arrivalTimes[i]);
						this->arrivalTimes[i]=0.0;
					}
				}

			}
		}
		else
		{
			cout << "Distribution defined for arrivals" << endl;
			this->_GPmys->atDistDEF = true;
			start = clock();
			if((this->alphaLessi==0)||((this->alphaLessi>0)&&(iterationIndex==0))||((this->alphaLessi>0)&&(iterationIndex>0)&&(this->myStep==0)))
			{
				if(this->mySampleAlgo==LATINHYPERCUBE)
					GenLHSArrivals(gen);
				else
					GenArrivals(gen);
			}
			end = clock();
			timeFileCPLEX << (double)(end - start)/(double)CLK_TCK << " ";
			
		}
		
		if((this->alphaLessi==0)||((this->alphaLessi>0)&&(iterationIndex==0))||((this->alphaLessi>0)&&(iterationIndex>0)&&(this->myStep==0)))
		{
			if(this->_GPmys->sysType == CLOSEDLOOP)
			{
				for(int parts=0;parts<this->I;parts++)
				{
					this->processTimes[parts].resize(this->_GPmys->psMachines.size()+1);
					this->processTimes[parts][this->processTimes[parts].size()-1] = 0.0;
				}
			}
		}

		start = clock();
		BuildModel(iterationIndex);
		end = clock();
		timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << " ";
		start = clock();
		Optimize();
		end = clock();
		timeFileCPLEX << (double)( end - start )/(double)CLK_TCK << endl;
		
		double foVal(0.0);
		if(iterationIndex==0)
		{
			fout << "SERVICE_LEVEL   " << "TOTAL_LATENESS " << "AVERAGE_LATENESS" << " ";
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				fout << "WTin_" << j+1 << " ";
			}
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				fout << "WTOUT_" << j+1 << " ";
			}
			for(int j=0;j<this->_GPmys->psMachines.size();j++)
			{
				fout << "Q_ave_" << j+1 << " ";
			}
			fout << endl;
		}
		writeOutput(fout,fout2,outSumYSumS);
		
		if(this->_optObj == KANBAN && this->SeqModel==true && this->_myOFtype==MIN_s)
		{
			int mypsBuffSize(0);
			mypsBuffSize = this->_GPmys->psBuff.size();
			//save the values of time buffer for kanbans
			this->TB_kan.resize(this->mycap[0]);
			cout << this->mycap[0] << endl;
			cout << "Kanban size: " << this->mycap[0] << endl;
			cout << "Time Buffer values (Kanban): " << endl;
			for(int k=0;k<this->mycap[0];k++)
			{
				this->TB_kan[k].resize(mypsBuffSize);
				for(int l=0;l<mypsBuffSize;l++)
				{				
					this->TB_kan[k][l] = this->cplex.getValue(x_s_k[k][l]);
					cout << this->TB_kan[k][l] << " ";
				}
				cout << endl;
			}
			this->_myOFtype = MIN_WT;
			this->optCUTS = true;
			this->tbCUTS = true;
			
			this->ClearCplexElements();		
			this->createEnvironment();

			BuildModel(iterationIndex);
			Optimize();
			computeBounds(f3,out_solApprossimata);
			writeOutput(fout,fout2,outSumYSumS);

		}
		else if(this->_optObj == KANBAN && this->SeqModel==true && this->_myOFtype==MIN_WT)
		{
			foVal=0.0;
			for(size_t k=0;k < x_s_k.getSize(); k++)
			{
				for(size_t m=0;m<x_s_k[k].getSize();m++)
				{
					foVal = foVal+this->cplex.getValue(x_s_k[k][m]);
				}
			}
			if(this->SeqModel == false)
				f5 << foVal << " ";
		
			foVal=0.0;
			for(int i=0;i<I;i++)
			{
				for (int j = 0; j < rTime[0].getSize()-1;++j)
				{
					foVal += this->cplex.getValue(rTime[i][j+1]) - this->cplex.getValue(y[i][j]) + this->cplex.getValue(st[i][j]) - this->cplex.getValue(rTime[i][j]);
				}
			}
			foVal = foVal/I;
			//-------------check whether the Waiting time cut has to be inserted----//
			if((this->_myOFtype == MIN_WT || this->_myOFtype == MIN_s) && this->optCUTS==true)
			{
				this->boundWTval = foVal;
			}
			else
				this->boundWTval = 0.0;
			
			if(this->SeqModel==false)
				f5 << foVal << " ";

			foVal=0.0;
			for(int i=0;i<I;i++)
			{
				foVal += this->cplex.getValue(rTime[i][rTime[0].getSize()-1]) - this->demandProcess[i];
			}
			foVal = foVal/I;
			
			if(this->SeqModel==false)
				f5 << foVal << " ";
			this->_myOFtype = MIN_s;
			this->optCUTS = true;
			
			//-------------check whether the Waiting time cut has to be inserted----//
			this->boundWTval = foVal;
			
			this->ClearCplexElements();		
			this->createEnvironment();

			BuildModel(iterationIndex);
			Optimize();
			writeOutput(fout,fout2,outSumYSumS);

		}
		
		if(this->_optObj!=EXTENDED_KANBAN&&this->_optObj!=KANBAN&&this->_optObj!=BASESTOCK && this->_optObj!=EXACT_OPT_BSC
			&& this->_optObj!=EXACT_OPT_KSC && this->_optObj!=EXACT_OPT_EKCS)
		{
			if(this->_optObj!=EXACT_OPT)
			{
				if(this->_GPmys->sysType==FLOWLINE)
				{
					cout << "The system is a flow line" << endl;
					int mypsBuffSize(0);
					mypsBuffSize = this->_GPmys->psBuff.size();
					this->_GPmys->TB_cap.resize(this->mycap[0]);
					cout << this->mycap[0] << endl;
					cout << "buffer size: " << mypsBuffSize << endl;
					cout << "Time Buffer values: " << endl;
					for(int k=0;k<this->mycap[0];k++)
					{
						this->_GPmys->TB_cap[k].resize(mypsBuffSize);
						for(int l=0;l<mypsBuffSize;l++)
						{				
							if(this->mycap[l]>this->mycap[0])
								this->_GPmys->TB_cap.resize(this->mycap[l]);
							this->_GPmys->TB_cap[k][l] = this->cplex.getValue(x_s_b[k][l]);
							cout << this->_GPmys->TB_cap[k][l] << " "; 
						}
						cout << endl;
						
					}
					for(int l=0;l<mypsBuffSize;l++)
					{
						double tempCap(0.0);
						for(int k=0;k<this->mycap[0];k++)
						{
							if(this->_GPmys->TB_cap[k][l]>0.0001)
								tempCap=tempCap++;
						}
						
						out_solApprossimata << tempCap << " "; 
					}
					out_solApprossimata << endl;
				}
				else if(this->_GPmys->sysType==CLOSEDLOOP && this->_myOFtype == MIN_s)
				{
					this->_GPmys->TB_cap.resize(this->myPal);
					for(int k=0;k<this->myPal;k++)
					{
						this->_GPmys->TB_cap[k].resize(1);
						this->_GPmys->TB_cap[k][0]=this->cplex.getValue(x_s_p[k]);
					}
					double tempPal(0.0);
					for(int k=0;k<this->myPal;k++)
					{
						
						if(this->_GPmys->TB_cap[k][0]>0.0001)
							tempPal=tempPal++;
					}
					
					out_solApprossimata << tempPal << endl;

				}
				else if(this->_GPmys->sysType==CLOSEDLOOP && this->_myOFtype == MIN_b)
				{
					this->_GPmys->TB_cap.resize(this->myPal);
					for(int k=0;k<this->myPal;k++)
					{
						this->_GPmys->TB_cap[k].resize(1);
						this->_GPmys->TB_cap[k][0]=this->cplex.getValue(x_b_p[k]);
					}
					double tempPal(0.0);
					for(int k=0;k<this->myPal;k++)
					{
						
						if(this->_GPmys->TB_cap[k][0]>0.0001)
							tempPal=tempPal++;
					}
					
					out_solApprossimata << tempPal << endl;
				}
			}
			else
			{
				if(this->_GPmys->sysType==FLOWLINE)
				{
					cout << "The system is a flow line" << endl;
					int mypsBuffSize(0);
					mypsBuffSize = this->_GPmys->psBuff.size();
					
					for(int l=0;l<mypsBuffSize;l++)
					{
						double tempCap(0.0);
						bool foundCap=false;
						int k=0;
						while(foundCap==false && k<this->mycap[l])
						{				
							if(this->cplex.getValue(z_buf[k][l])>0.001)
							{
								tempCap=k+1;
								foundCap=true;
							}
							else
								k++;
						}
						this->_GPmys->psBuff[l]->capacity=tempCap;
						fout2 << this->_GPmys->psBuff[l]->capacity << " ";
					}
					fout2 << endl;
				}
				else if(this->_GPmys->sysType==CLOSEDLOOP)
				{
					double tempCap(0.0);
					bool foundCap=false;
					int k=0;
					while(foundCap==false && k<this->myPal)
					{				
						if(this->cplex.getValue(z_pal[k])>0.001)
						{
							tempCap=k+1;
							foundCap=true;
						}
						else
							k++;
					}
					this->myPal=tempCap;
					fout2 << this->myPal << endl;
				}
			}
		}
		else
		{
			cout << "The system is a supply chain" << endl;
			int mypsBuffSize(0);
			mypsBuffSize = this->_GPmys->psBuff.size();
			if(this->_optObj==EXTENDED_KANBAN)
			{
				this->TB_bs.resize(this->mycap[0]);
				this->TB_kan.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Maximum Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (main base stock): " << endl;

				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_bs[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						this->TB_bs[k][l] = this->cplex.getValue(x_s_b[k][l]);
						cout << this->TB_bs[k][l] << " ";
					}
					cout << endl;
				}
				std::vector<int> tempBS;
				for(int l=0;l<mypsBuffSize;l++)
				{
					double tempCap(0.0);
					for(int k=0;k<this->mycap[0];k++)
					{
						if(this->TB_bs[k][l]>0.0001)
							tempCap=tempCap++;
					}
					tempBS.push_back(tempCap);
					
					 
				}
				std::vector<int> newTempBS(mypsBuffSize);
				for(int l=mypsBuffSize-2;l>=0;l--)
				{
					newTempBS[l]=tempBS[l]-tempBS[l+1];				 
				}
				newTempBS[mypsBuffSize-1]=tempBS[mypsBuffSize-1];
				for(int l=0;l<mypsBuffSize;l++)
				{
					out_solApprossimata << newTempBS[l] << " ";
				}
				
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_kan[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						this->TB_kan[k][l] = this->cplex.getValue(x_s_k[k][l]);
						cout << this->TB_kan[k][l] << " ";
					}
					cout << endl;
				}
				for(int l=0;l<mypsBuffSize;l++)
				{
					double tempCap(0.0);
					for(int k=0;k<this->mycap[0];k++)
					{
						if(this->TB_kan[k][l]>0.0001)
							tempCap=tempCap++;
					}
					
					out_solApprossimata << tempCap << " "; 
				}
				out_solApprossimata << endl;
			}
			if(this->_optObj==BASESTOCK)
			{
				this->TB_bs.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Maximum Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (main base stock): " << endl;

				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_bs[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						this->TB_bs[k][l] = this->cplex.getValue(x_s_b[k][l]);
						cout << this->TB_bs[k][l] << " ";
					}
					cout << endl;
				}
				std::vector<int> tempBS;
				for(int l=0;l<mypsBuffSize;l++)
				{
					double tempCap(0.0);
					for(int k=0;k<this->mycap[0];k++)
					{
						if(this->TB_bs[k][l]>0.0001)
							tempCap=tempCap++;
					}
					tempBS.push_back(tempCap);
					
					 
				}
				std::vector<int> newTempBS(mypsBuffSize);
				for(int l=mypsBuffSize-2;l>=0;l--)
				{
					newTempBS[l]=tempBS[l]-tempBS[l+1];				 
				}
				newTempBS[mypsBuffSize-1]=tempBS[mypsBuffSize-1];
				for(int l=0;l<mypsBuffSize;l++)
				{
					out_solApprossimata << newTempBS[l] << " ";
				}
				out_solApprossimata << endl;
			}
			if((this->_optObj==KANBAN && (this->SeqModel== false || this->_myOFtype!=MIN_WT)))
			{
				this->TB_kan.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (Kanban): " << endl;
				for(int k=0;k<this->mycap[0];k++)
				{
					this->TB_kan[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						this->TB_kan[k][l] = this->cplex.getValue(x_s_k[k][l]);
						cout << this->TB_kan[k][l] << " ";
					}
					cout << endl;
				}
				for(int l=0;l<mypsBuffSize;l++)
				{
					double tempCap(0.0);
					for(int k=0;k<this->mycap[0];k++)
					{
						if(this->TB_kan[k][l]>0.0001)
							tempCap=tempCap++;
					}
					
					out_solApprossimata << tempCap << " "; 
				}
				out_solApprossimata << endl;
			}
			else if(this->_optObj==EXACT_OPT_BSC)
			{
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				this->IP_bs.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Maximum Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (main base stock): " << endl;

				this->_GPmys->psBaseStock.resize(mypsBuffSize);
				for(int k=0;k<this->mycap[0];k++)
				{
					this->IP_bs[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						if(this->cplex.getValue(z_bs[k][l])>0.001)
						{
							this->IP_bs[k][l] = this->cplex.getValue(z_bs[k][l]);
							this->_GPmys->psBaseStock[l]->capacity=k+1;
						}
						else
							this->IP_bs[k][l] = 0;
						
						cout << this->IP_bs[k][l] << " ";
					}
					
					cout << endl;
				}
				
				for(int l=0;l<mypsBuffSize;l++)
				{
					int countKK(0);
					for(int k=0;k<this->mycap[0];k++)
					{				
						if(this->IP_bs[k][l]==0)
						{
							countKK++;
						}							
					}
					if(countKK==this->mycap[0])
					{
						this->IP_bs[0][l] = 1;
						this->_GPmys->psBaseStock[l]->capacity=1;
					}

				}
				for(int k=0;k < mypsBuffSize;k++)
				{
					out_solApprossimata << this->_GPmys->psBaseStock[k]->capacity << " ";
				}

			}
			else if(this->_optObj==EXACT_OPT_KSC)
			{
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				this->IP_ks.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Maximum Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (kanban): " << endl;

				this->_GPmys->psKanban.resize(mypsBuffSize);
				for(int k=0;k<this->mycap[0];k++)
				{
					this->IP_ks[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						if(this->cplex.getValue(z_ks[k][l])>0.001)
						{
							this->IP_ks[k][l] = this->cplex.getValue(z_ks[k][l]);
							this->_GPmys->psKanban[l]->capacity=k+1;
						}
						else
							this->IP_ks[k][l] = 0;
						
						cout << this->IP_ks[k][l] << " ";
					}
					cout << endl;
				}
				for(int l=0;l<mypsBuffSize;l++)
				{
					int countKK(0);
					for(int k=0;k<this->mycap[0];k++)
					{				
						if(this->IP_ks[k][l]==0)
						{
							countKK++;
						}							
					}
					if(countKK==this->mycap[0])
					{
						this->IP_ks[0][l] = 1;
						this->_GPmys->psKanban[l]->capacity=1;
					}

				}
				for(int k=0;k < mypsBuffSize;k++)
				{
					out_solApprossimata << this->_GPmys->psKanban[k]->capacity << " ";
				}

			}
			else if(this->_optObj==EXACT_OPT_EKCS)
			{
				int mypsBuffSize(0);
				mypsBuffSize = this->_GPmys->psBuff.size();
				this->IP_ks.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Maximum Kanban size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (kanban): " << endl;

				this->_GPmys->psKanban.resize(mypsBuffSize);
				for(int k=0;k<this->mycap[0];k++)
				{
					this->IP_ks[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						if(this->cplex.getValue(z_ks[k][l])>0.001)
						{
							this->IP_ks[k][l] = this->cplex.getValue(z_ks[k][l]);
							this->_GPmys->psKanban[l]->capacity=k+1;
						}
						else
							this->IP_ks[k][l] = 0;
						
						cout << this->IP_ks[k][l] << " ";
					}
					cout << endl;
				}
				for(int l=0;l<mypsBuffSize;l++)
				{
					int countKK(0);
					for(int k=0;k<this->mycap[0];k++)
					{				
						if(this->IP_ks[k][l]==0)
						{
							countKK++;
						}							
					}
					if(countKK==this->mycap[0])
					{
						this->IP_ks[0][l] = 1;
						this->_GPmys->psKanban[l]->capacity=1;
					}

				}
				for(int k=0;k < mypsBuffSize;k++)
				{
					out_solApprossimata << this->_GPmys->psKanban[k]->capacity << " ";
				}

				out_solApprossimata << endl;
				
				mypsBuffSize = this->_GPmys->psBuff.size();
				this->IP_bs.resize(this->mycap[0]);
				cout << this->mycap[0] << endl;
				cout << "Maximum Base stock size: " << this->mycap[0] << endl;
				cout << "Time Buffer values (main base stock): " << endl;

				this->_GPmys->psBaseStock.resize(mypsBuffSize);
				for(int k=0;k<this->mycap[0];k++)
				{
					this->IP_bs[k].resize(mypsBuffSize);
					for(int l=0;l<mypsBuffSize;l++)
					{				
						if(this->cplex.getValue(z_bs[k][l])>0.001)
						{
							this->IP_bs[k][l] = this->cplex.getValue(z_bs[k][l]);
							this->_GPmys->psBaseStock[l]->capacity=k+1;
						}
						else
							this->IP_bs[k][l] = 0;
						
						cout << this->IP_bs[k][l] << " ";
					}
					cout << endl;
				}
				for(int l=0;l<mypsBuffSize;l++)
				{
					int countKK(0);
					for(int k=0;k<this->mycap[0];k++)
					{				
						if(this->IP_bs[k][l]==0)
						{
							countKK++;
						}							
					}
					if(countKK==this->mycap[0])
					{
						this->IP_bs[0][l] = 1;
						this->_GPmys->psBaseStock[l]->capacity=1;
					}

				}
				for(int k=0;k < mypsBuffSize;k++)
				{
					out_solApprossimata << this->_GPmys->psBaseStock[k]->capacity << " ";
				}

			}
		}
		
		this->ClearCplexElements();		
				
		if(iterationIndex < this->myItern-1)
			createEnvironment();
		
		
	}
	if(this->myItern>1)
		f5 << endl;
	outarrivals.close();
	outSumYSumS.close();
	timeFileCPLEX.close();
}
void App_OpModel::Simulate(std::ofstream & fout,std::ofstream & fout2,std::ofstream & f3,std::ofstream & out_res,int r)
{
	BuildModel(0);
	Optimize();
	cout << "SIMULATION DONE!" << endl;
	/*getchar();*/
	std::ofstream outSumYSumS;
	outSumYSumS.open("OUTPUT\\sumYsumS.txt");
	writeOutputSimulation(fout,outSumYSumS/*,fout2,f3*/);
	writeReplicateResults(out_res,r);

	std::cout << "Ho scritto l'output" << std::endl;
		
	this->ClearCplexElements();		
	this->createEnvironment();
}
double App_OpModel::computeAvgQueue(std::vector<double> yvecj, std::vector<double> yveck,
									std::vector<double> pt,std::vector<int> & zInf,std::vector<double> & SimulatedQueue)
{
	int numP(0);
	numP=yvecj.size();
	double iBP(0.0); //start of the busy period
	double fBP(0.0); //finish of the busy period
	int CUMqueue(1);
	double TQueue(0.0);
	double TI(0.0); //Time interval
	double Qave(0.0); //average queue
	bool EOBP=false;
	int pointQueue(0);
	int i=1;
	int j=0;
	iBP = yveck[0];
	int CountInfeasj(0);
	int CountInfeasjp1(0);
	int simQueueSize(0);
	SimulatedQueue.clear();

	while(i<numP || j<numP)
	{
		if(i<numP && j<numP)
		{
			if(yveck[i]>yvecj[j])
			{
				fBP=yvecj[j];
				TI=yvecj[j]-iBP;
				if(TI<0)
					CountInfeasjp1++;
				TQueue=TQueue+CUMqueue*TI;
				iBP=yvecj[j];
				if(CUMqueue>0)
				{
					CUMqueue = CUMqueue-1;
					SimulatedQueue.push_back(CUMqueue);
				}
				if(j<numP)
					j=j+1;
			}
			else if(yveck[i]<yvecj[j])
			{
				fBP=yveck[i];
				TI=yveck[i]-iBP;
				if(TI<0)
					CountInfeasj++;
				TQueue=TQueue+CUMqueue*TI;
				iBP=yveck[i];
				CUMqueue = CUMqueue+1;
				SimulatedQueue.push_back(CUMqueue);
				
				i=i+1;
			}
			else
			{
				fBP=yveck[i];
				TI=yveck[i]-iBP;
				if(TI<0)
					CountInfeasjp1++;
				TQueue=TQueue+CUMqueue*TI;
				iBP=yvecj[j];
				if(j<numP) 
					j=j+1;
				if(i<numP)
					i=i+1;
			}
		}
		else if(i>=numP && j<numP)
		{
			fBP=yvecj[j];
			TI=yvecj[j]-iBP;
			if(TI<0)
				CountInfeasjp1++;
			TQueue=TQueue+CUMqueue*TI;
			iBP=yvecj[j];
			if(CUMqueue>0)
			{
				CUMqueue = CUMqueue-1;
				SimulatedQueue.push_back(CUMqueue);
			}
			if(j<numP) 
				j=j+1;
		}
		else if(i<numP && j>=numP)
		{
			fBP=yveck[i];
			TI=yveck[i]-iBP;
			if(TI<0)
				CountInfeasjp1++;
			TQueue=TQueue+CUMqueue*TI;
			iBP=yveck[i];
			if(CUMqueue>0)
			{
				CUMqueue = CUMqueue-1;
				SimulatedQueue.push_back(CUMqueue);
			}
			if(i<numP) 
				i=i+1;
		}

		/*iBP=yvecj[i]-pt[i];
		fBP=yvecj[i]-pt[i];
		int j=i+1;
		EOBP=false;
		while(j<numP && EOBP==false)
		{
			if(yveck[j]< yvecj[i])
			{
				if(j==i+1)
				{
					TI=iBP-yveck[j];
				}
				else
				{
					TI=-iBP+yveck[j];
				}
				TQueue=TQueue+CUMqueue*TI;
				pointQueue++;
				iBP=yveck[j];
				
				CUMqueue=CUMqueue+1;
				j++;
			}
			else
			{
				pointQueue=0;
				fBP = yvecj[i];
				TI=fBP-iBP;
				TQueue=TQueue+CUMqueue*TI;
				if(CUMqueue>0)
					CUMqueue = CUMqueue-1;
				EOBP=true;
				i++;
			}
		}*/
	}
	
	zInf.push_back(CountInfeasj);
	zInf.push_back(CountInfeasjp1);
	Qave = TQueue/yvecj[numP-1];
	
	return Qave;
}
double App_OpModel::computeServiceLevel(std::vector<double> zJ,std::vector<double> DD)
{
	double SL(0.0);
	int numLate(0);
	for(int i=0;i<zJ.size(); i++)
	{
		if(zJ[i]-DD[i]>0)
			numLate=numLate+1;
	}
	SL=((double)(zJ.size()-numLate))/((double)(zJ.size()));
	return SL;
}
void App_OpModel::AnalyzeQlevel(std::vector<double> yvecj, std::vector<double> yveck, std::vector<double> pt,std::vector<int> & zInf,std::vector<std::vector<double> >  & Qlevel)

{
	int numP(0);
	numP=yvecj.size();
	double iBP(0.0); //start of the busy period
	double fBP(0.0); //finish of the busy period
	int CUMqueue(1);
	double TQueue(0.0);
	double TI(0.0); //Time interval
	double Qave(0.0); //average queue
	bool EOBP=false;
	int pointQueue(1);
	int i=1;
	int j=0;
	iBP = yveck[0];
	int CountInfeasj(0);
	int CountInfeasjp1(0);
	int VecQueueSize(1);
	Qlevel.resize(VecQueueSize);
	Qlevel[VecQueueSize-1].push_back(iBP);
	Qlevel[VecQueueSize-1].push_back(CUMqueue);

	while(i<numP || j<numP)
	{
		if(i<numP && j<numP)
		{
			if(yveck[i]>yvecj[j])
			{
				fBP=yvecj[j];
				TI=yvecj[j]-iBP;
				if(TI<0)
					CountInfeasjp1++;
				TQueue=TQueue+CUMqueue*TI;
				iBP=yvecj[j];
				if(CUMqueue>0)
				{
					CUMqueue = CUMqueue-1;
					VecQueueSize=VecQueueSize+1;
					Qlevel.resize(VecQueueSize);					
					Qlevel[VecQueueSize-1].push_back(yvecj[j]);
					Qlevel[VecQueueSize-1].push_back(CUMqueue);
					
				}
				j=j+1;
			}
			else if(yveck[i]<yvecj[j])
			{
				fBP=yveck[i];
				TI=yveck[i]-iBP;
				if(TI<0)
					CountInfeasj++;
				TQueue=TQueue+CUMqueue*TI;
				iBP=yveck[i];
				CUMqueue = CUMqueue+1;
				VecQueueSize=VecQueueSize+1;
				Qlevel.resize(VecQueueSize);					
				Qlevel[VecQueueSize-1].push_back(yveck[i]);
				Qlevel[VecQueueSize-1].push_back(CUMqueue);
				
				i=i+1;
			}
			else
			{
				fBP=yveck[i];
				TI=yveck[i]-iBP;
				if(TI<0)
					CountInfeasjp1++;
				TQueue=TQueue+CUMqueue*TI;
				iBP=yvecj[j];
				j=j+1;
				i=i+1;
			}
		}
		else if(i>=numP && j<numP)
		{
			fBP=yvecj[j];
			TI=yvecj[j]-iBP;
			if(TI<0)
				CountInfeasjp1++;
			TQueue=TQueue+CUMqueue*TI;
			iBP=yvecj[j];
			if(CUMqueue>0)
			{
				CUMqueue = CUMqueue-1;
				VecQueueSize=VecQueueSize+1;
				Qlevel.resize(VecQueueSize);					
				Qlevel[VecQueueSize-1].push_back(yvecj[j]);
				Qlevel[VecQueueSize-1].push_back(CUMqueue);
			}
			
			j=j+1;
		}
		else if(i<numP && j>=numP)
		{
			fBP=yveck[i];
			TI=yveck[i]-iBP;
			if(TI<0)
				CountInfeasjp1++;
			TQueue=TQueue+CUMqueue*TI;
			iBP=yveck[i];
			if(CUMqueue>0)
			{
				CUMqueue = CUMqueue-1;
				VecQueueSize=VecQueueSize+1;
				Qlevel.resize(VecQueueSize);					
				Qlevel[VecQueueSize-1].push_back(yveck[i]);
				Qlevel[VecQueueSize-1].push_back(CUMqueue);
			}
			
			i=i+1;
		}
	}
	
	zInf.push_back(CountInfeasj);
	zInf.push_back(CountInfeasjp1);
	Qave = TQueue/yvecj[numP-1];
}
App_OpModel::~App_OpModel(void)
{
	this->env.end();
	std::cout << "Deleted the Model" << std::endl;
}
}
