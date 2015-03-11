// gpBCDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gpBCDLL.h"

namespace postProcess{
// This is an example of an exported variable
GPBCDLL_API int ngpBCDLL=0;

// This is an example of an exported function.
GPBCDLL_API int fngpBCDLL(void)
{
	return 42;
}

AppSolAlg::AppSolAlg(void)
{
}

AppSolAlg::~AppSolAlg(void)
{
}

int AppSolAlg::calcCapApp(std::vector<double> yj,std::vector<double> yjp1, int I){
int i(0);
int k(0);
bool out(false);
int tempMax(0);
int maxVal(0);

for(i=0;i<I;i++)
{
	tempMax = 0;
	k=i+1;
	out=false;
	while((k<I) && (out==false))
	{
		if(/*yj[k]>yj[i] && */yj[k]<yjp1[i])
		{
			tempMax++;
			k++;
		}
		else
			out=true;
		/*k++;*/
	}
	if(tempMax > maxVal)
		maxVal = tempMax;
}

return maxVal;

}
BoundsCalculation::BoundsCalculation()
{
	return;
}
BoundsCalculation::~BoundsCalculation(void)
{
}
int BoundsCalculation::computeLowerBound(std::vector<double> xvet, std::vector<double> svet,
											int PartNumber, int Pallet,int d,typeSys sysT,_OFtype ofT)
{
	int k(0);
	int p(Pallet-1);
	int p_true(0);
	int run(0); /*questo contatore mi serve per gli esperimenti*/
	int i(0);
	int j(0);
	int count(0);

	bool esc(false);
	bool found(false);
	bool esc1(false);
	int p_low(0);
	double differenza(0.0);
	double stemp(0.0);
	double(0.0);
	double(0.0);
	int benchcount(0);

	p_true = Pallet+1;
	//k = p_true - 1;
	if((sysT==FLOWLINE) || (sysT==CLOSEDLOOP && ofT == MIN_s))
	{
		while(k < p_true)
		{
			i=0;
			esc = false;
			while(i < ((PartNumber) - p_true))
			{
				stemp = svet[k];
				differenza = xvet[i+p_true] - xvet[i+k];
				if(svet[k] >= xvet[i+p_true] - xvet[i+k])
				{
					count++;
				}
				benchcount++;
				i++;
			}
			k++;
		}
		if (benchcount==count && count>0)
			return p_true;
		else
			return 1;
	}
	else
	{
		while(k < p_true)
		{
			i=d;
			esc = false;
			while(i < ((PartNumber-d) - p_true))
			{
				stemp = svet[k];
				differenza = xvet[i+p_true] - xvet[i+k];
				if(svet[k] < xvet[i+p_true] - xvet[i+k])
				{
					count++;
				}
				benchcount++;
				i++;
			}
			k++;
		}
		if (benchcount==count && count>0)
			return p_true;
		else
			return 1;
	}
}

int BoundsCalculation::computeUpperBound(std::vector<double> xvet, std::vector<double> svet,
											int PartNumber, int Pallet, int d,typeSys sysT,_OFtype ofT)
{
	int k(0);
	int p(Pallet-1);
	int p_true(0);
	int run(0); /*questo contatore mi serve per gli esperimenti*/
	int i(0);
	int j(0);
	int count(0);
	int benchcount(0);

	bool esc(false);
	bool found(false);
	bool esc1(false);
	int p_low(0);
	double differenza(0.0);
	double stemp(0.0);
	double(0.0);
	double(0.0);

	p_true = Pallet;
	//k =p_true - 1;
	if((sysT==FLOWLINE) || (sysT==CLOSEDLOOP && ofT == MIN_s))
	{
		while(k < p_true)
		{
			i=d;
			esc = false;
			while(i < ((PartNumber) - p_true))
			{
				stemp = svet[k];
				differenza = xvet[i+p_true] - xvet[i+k];
				if(svet[k] <= xvet[i+p_true] - xvet[i+k])
				{
					count++;
				}
				benchcount++;
				i++;
			}
			k++;
		}

		if(benchcount==count && count>0)
			return p_true;
		else 
			return PartNumber;
	}
	else
	{
		while(k < p_true)
		{
			i=d;
			esc = false;
			while(i < ((PartNumber) - p_true))
			{
				stemp = svet[k];
				differenza = xvet[i+p_true] - xvet[i+k];
				if(svet[k] > xvet[i+p_true] - xvet[i+k])
				{
					count++;
				}
				benchcount++;
				i++;
			}
			k++;
		}

		if(benchcount==count && count>0)
			return p_true;
		else 
			return PartNumber;
	}
}
}
