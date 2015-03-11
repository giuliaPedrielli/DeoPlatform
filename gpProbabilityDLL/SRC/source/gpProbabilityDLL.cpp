// gpProbabilityDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gpProbabilityDLL.h"


namespace stochasticProperty{
	using namespace boost::random;
	/*using namespace xint;*/
// This is an example of an exported variable
GPPROBABILITYDLL_API int ngpDistribution=0;

// This is an example of an exported function.
GPPROBABILITYDLL_API int fngpDistribution(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see gpProbabilityDLL.h for the class definition
gpDistribution::gpDistribution()
{ 
	this->myType=NULLTYPE;
}
gpDistribution::gpDistribution(typeDistribution disType,double f1,double f2,double f3,
							   double f4,double f5)
{
	this->myType=disType;
	this->m1=f1;
	this->m2=f2;
	this->m3=f3;
	this->m4=f4;
	this->m5=f5;
}
gpDistribution::gpDistribution(stochasticProperty::gpDistribution* dCopy)
{
	this->myType=dCopy->myType;
	this->m1=dCopy->m1;
	this->m2=dCopy->m2;
	this->m3=dCopy->m3;
	this->m4=dCopy->m4;
	this->m5=dCopy->m5;
}
bool gpDistribution::gpExpoDataGeneration(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey){

	/*std::vector<double> result;*/
	result.clear();
	result.resize(sizex);
	typedef boost::exponential_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(1/(this->m1)));
	boost::generator_iterator<gen_type> die(&die_gen);

	/*int seed(45);
	for(size_t i=0;i<34;i++)
	{
		
	
		stochasticProperty::base_generator_type gen2(seed);
		for(size_t j=0;j<5;j++)
		{
			typedef boost::exponential_distribution<> distribution_type2;
			typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type2;
			gen_type die_gen2(gen2,distribution_type2(1));
			boost::generator_iterator<gen_type2> die2(&die_gen2);
			cout << *die2++ << endl;
		}
	}*/

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			//std::cout << *die << " ";
			die++;
			//std::cout << endl;
		}
	}
	//for(int i=0;i<sizeTog;i++)
	//{
	//	stochasticProperty::Exp_Distribution expDis(1/this->m1);
	//	/*stochasticProperty::RandomNumberGenerator */
	//	/*gen(seed);*/
	//	gen.seed(seme);
	//	stochasticProperty::Exp_Generator ExpoGen(gen,expDis);

	//	result[i] = ExpoGen();
	//	/*seed++;*/
	//}

	return true;
}

bool gpDistribution::gpLHSExpoDataGeneration(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{											  
	typedef boost::random::uniform_real_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	std::ofstream out_rnd;
	out_rnd.open("OUTPUT\\rndGen.txt");
	std::ofstream out_rnd2;
	out_rnd2.open("OUTPUT\\rndGen2.txt");

	std::vector<double> temp;
	/*temp.resize(sizex);*/
	int numGroup(4);
	int countGroup=0;
	double a,b;
	
	for(int i=0;i<sizex;i++)
	{			
		/*a=((double)(countGroup))/((double)(numGroup));
		b=a+(((double)1)/((double)numGroup));*/
		
		a=((double)(i)/((double)(sizex)));
		b=((double)(i+1)/((double)sizex));
		gen_type die_gen(gen,distribution_type(a,b));
		boost::generator_iterator<gen_type> die(&die_gen);

		if(i%((int)(sizex/numGroup))==0 && i>0)
			countGroup++;	
		temp.push_back(*die);
		out_rnd2 << temp[i] << endl;
		die++;
	}

	std::random_shuffle(temp.begin(),temp.end());

	for(int j=0;j<sizey;j++)
	{
		for(int i=0;i<sizex;i++)
		{						
			/*result[i].push_back(-std::log(1-temp[i])/(((double)this->m1)));*/
			result[i].push_back(-std::log(1-temp[i])*(((double)this->m1)));
			out_rnd << result[i][j] << endl;
		}
	}
	out_rnd.close();
	return true;
}

bool gpDistribution::gpUniformDataGeneration(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);
	typedef boost::random::uniform_real_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(this->m1,this->m2));
	boost::generator_iterator<gen_type> die(&die_gen);

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			die++;
		}
	}
	
	return true;
}
bool gpDistribution::gpConstantDataGeneration(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(this->m1);
		}
	}
	//for(int i=0;i<sizeTog;i++)
	//{
	//	stochasticProperty::Exp_Distribution expDis(1/this->m1);
	//	/*stochasticProperty::RandomNumberGenerator */
	//	/*gen(seed);*/
	//	gen.seed(seme);
	//	stochasticProperty::Exp_Generator ExpoGen(gen,expDis);

	//	result[i] = ExpoGen();
	//	/*seed++;*/
	//}

	return true;
}
bool gpDistribution::gpTriangularDataGenerator(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);
	typedef boost::triangle_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(this->m1,this->m2,this->m3));
	boost::generator_iterator<gen_type> die(&die_gen);

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			//std::cout << *die << " ";
			die++;
			//std::cout << endl;
		}
	}
	//std::vector<double> result;
	//result.resize(sizeTogenerate);
	//for(int i=0;i<sizeTogenerate;i++)
	//{
	//	/*result[i]=0.0;*/
	//	stochasticProperty::Tri_Distribution triDis(this->m1,this->m2,this->m3);
	//	stochasticProperty::RandomNumberGenerator gen(seed);
	//	stochasticProperty::Tri_Generator TriGen(gen,triDis);
	//	result[i] = TriGen();
	//	seed++;
	//}

	return true;
}
bool gpDistribution::gpLogNDataGenerator(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);
	/*typedef boost::lognormal_distribution<> distribution_type;*/
	typedef boost::random::lognormal_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(this->m1,this->m2));
	boost::generator_iterator<gen_type> die(&die_gen);

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			//std::cout << *die << " ";
			die++;
			//std::cout << endl;
		}
	}
	return true;
}
bool gpDistribution::gpNormalDataGenerator(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);
	typedef boost::normal_distribution<> distribution_type;
	/*typedef boost::variate_generator<*/
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(this->m1,this->m2));
	boost::generator_iterator<gen_type> die(&die_gen);

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			//std::cout << *die << " ";
			die++;
			//std::cout << endl;
		}
	}
	/*return result;
	std::vector<double> result;
	result.resize(sizeTogenerate);
	for(int i=0;i<sizeTogenerate;i++)
	{
		stochasticProperty::Norm_Distribution normDis(this->m1,this->m2);
		stochasticProperty::RandomNumberGenerator gen(seed);
		stochasticProperty::Norm_Generator normGen(gen,normDis);
		result[i]=normGen();
		seed++;
	}*/

	return true;
}
bool gpDistribution::gpWeibullDataGenerator(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);
	typedef boost::random::weibull_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(this->m1,this->m2));
	boost::generator_iterator<gen_type> die(&die_gen);
	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			//std::cout << *die << " ";
			die++;
			//std::cout << endl;
		}
	}
	//result.clear();
	//result.resize(sizex);
	//typedef distribution_type;
	/*typedef boost::*/
	///*typedef boost::variate_generator<*/
	//
	//gen_type die_gen(gen,distribution_type(this->m1,this->m2));
	//boost::generator_iterator<gen_type> die(&die_gen);

	//for(int i=0;i<sizex;i++)
	//{
	//	for(int j=0;j<sizey;j++)
	//	{
	//		result[i].push_back(*die);
	//		//std::cout << *die << " ";
	//		die++;
	//		//std::cout << endl;
	//	}
	//}
	return true;
}
//std::vector<double> gpDistribution::gpWeibullDataGenerator(const int sizeTogenerate, int seed)
//{
//	std::vector<double> result;
//	result.resize(sizeTogenerate);
//	for(int i=0;i<sizeTogenerate;i++)
//	{
//		stochasticProperty::Weibull_Distrib weibDis(this->m1);//,this->m2);
//		stochasticProperty::RandomNumberGenerator gen(seed);
//		Weib_Generator weibGen(gen,weibDis);
//		/*Weibull_Generator weibGen;*/
//		
//		/*stochasticProperty::Weibull_Generator weibGen(gen,weibDis);*/
//		/*result[i]=weibGen(double);*/
//		seed++;
//	}
//
//	return result;
//}
//std::vector<double> gpDistribution::gpBetaDataGenerator(const int sizeTogenerate, int seed)
//{
//	std::vector<double> result;
//	result.resize(sizeTogenerate);
//	for(int i=0;i<sizeTogenerate;i++)
//	{
//		stochasticProperty::Beta_Distribution betaDis(this->m1,this->m2);
//		stochasticProperty::RandomNumberGenerator gen(seed);
//		stochasticProperty::Beta_Generator betaGen(gen,betaDis);
//		result[i]=betaGen();
//		seed++;
//	}
//	return result;
//}
//std::vector<double> gpDistribution::gprandomDataGenerator(const int size2gen,
//														  int seed, RandomNumberGenerator & gen)
//{
//	std::vector<double> result;
//	switch (this->myType)
//	{
//	case EXPO: 
//		result = gpExpoDataGeneration(size2gen, seed, gen);
//		break;
//	case UNIFORM: 
//		result = gpUniformDataGeneration(size2gen, seed);
//		break;
//	case NORMAL:
//		result=gpNormalDataGenerator(size2gen, seed);
//		break;
//	case COSTANT:
//		result=gpConstantDataGeneration(size2gen);
//		break;
//	case TRIANGULAR:
//		result=gpTriangularDataGenerator(size2gen, seed);
//		break;
//	case LOGNORMAL:
//		result=gpLogNDataGenerator(size2gen, seed);
//		break;
//	/*case WEIBULL:
//		result = gpWeibullDataGenerator(size2gen, seed);
//		break;*/
//	/*case BETA:
//		result = gpBetaDataGenerator(size2gen, seed);*/
//	default: std::cout << "Didn't receive legal argument" << std::endl;
//		break;
//	}
//
//	return result;
//}
bool gpDistribution::gpGammaDataGenerator(base_generator_type & gen,
										  std::vector<std::vector<double> > & result,
										  const int sizex,const int sizey)
{
	result.clear();
	result.resize(sizex);
	/*typedef boost::lognormal_distribution<> distribution_type;*/
	typedef boost::random::gamma_distribution<> distribution_type;
	typedef boost::variate_generator<base_generator_type&,distribution_type> gen_type;
	gen_type die_gen(gen,distribution_type(this->m1,this->m2));
	boost::generator_iterator<gen_type> die(&die_gen);

	for(int i=0;i<sizex;i++)
	{
		for(int j=0;j<sizey;j++)
		{
			result[i].push_back(*die);
			//std::cout << *die << " ";
			die++;
			//std::cout << endl;
		}
	}
	return true;
}
void gpDistribution::primeNumbersGenerator(int numN,std::vector<int> & primeSeq)
{
	int i=2;
	
	primeSeq.resize(numN);
	primeSeq.push_back(1);
	int countGen(0);
	while(countGen<numN-1)
	{
		int countDiv(0);
		for(int j=1;j<i+1;j++)
		{
			//conto i divisori di i
			int a = i%j;
			if (a==0)
				countDiv = countDiv+1;
		}
		if (countDiv==2){
			primeSeq.push_back(i);
			countGen++;
		}
		i=i+1;
	}
}
gpDistribution::~gpDistribution(void)
{
}
}
