// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GPPROBABILITYDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GPPROBABILITYDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifndef GP_PROBABILITY_DISTRIBUTION__HH
#define GP_PROBABILITY_DISTRIBUTION__HH

#ifdef GPPROBABILITYDLL_EXPORTS
#define GPPROBABILITYDLL_API __declspec(dllexport)
#else
#define GPPROBABILITYDLL_API __declspec(dllimport)
#endif

#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <math.h>
#include <cmath>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <process.h>
#include <sstream>
#include <ctime>   
#include <vector>
#include <algorithm>
//-------------------- BOOST MATH LIBRARIES-------------------//

#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>


#include <ctime>            // std::time

#include <boost/random/linear_congruential.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <iosfwd>
#include <istream>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/normal_distribution.hpp> // for normal_distribution
#include <boost/random/lognormal_distribution.hpp>
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/random/uniform_real.hpp>
//#include <boost/math/distributions/weibull.hpp>
#include <boost/random/weibull_distribution.hpp>
//#include <boost/math/distributions/beta.hpp>
//#include <boost/math/distributions/weibull.hpp>
//#include <boost/math/distributions/triangular.hpp>
//#include <boost/math/distributions/fisher_f.hpp>
#include <boost/generator_iterator.hpp>
// This class is exported from the gpProbabilityDLL.dll
namespace stochasticProperty{
typedef boost::mt19937 base_generator_type;
//typedef boost::mt19937 base_generator_type;
//typedef boost::minstd_rand base_generator_type_2;
////typedef boost::uniform_int<> Unif_Distribution;
//typedef boost::uniform_real<> Unif_Distribution;
//typedef boost::exponential_distribution<> Exp_Distribution;
//typedef boost::triangle_distribution<> Tri_Distribution;
//typedef boost::lognormal_distribution<> LogN_Distribution;
//typedef boost::normal_distribution<> Norm_Distribution;
//typedef boost::math::beta_distribution<> Beta_Distribution;
////typedef boost::math::weibull_distribution<double,boost::math::policies::default_policy> Weibull_Distribution;
////typedef boost::math::weibull_distribution<> Weibull_Distribution;
//typedef boost::math::weibull_distribution<> Weibull_Distrib;

//typedef boost::mt19937 RandomNumberGenerator;
//typedef boost::variate_generator<RandomNumberGenerator&, Unif_Distribution> Unif_Generator;
//typedef boost::variate_generator<RandomNumberGenerator&, Exp_Distribution> Exp_Generator;
//typedef boost::variate_generator<RandomNumberGenerator&, Tri_Distribution> Tri_Generator;
//typedef boost::variate_generator<RandomNumberGenerator&, LogN_Distribution> LogN_Generator;
//typedef boost::variate_generator<RandomNumberGenerator&, Norm_Distribution> Norm_Generator;
//typedef boost::variate_generator<RandomNumberGenerator&, Beta_Distribution> Beta_Generator;
//typedef boost::variate_generator<RandomNumberGenerator&, Weibull_Distrib> Weib_Generator;

//using boost::math::normal; // typedef provides default type is double.
using namespace boost;
using namespace boost::random;
using namespace std;
//typedef weibull_distribution
enum PTYPE{
EXPO,
UNIFORM,
NORMAL,
NULLTYPE,
COSTANT,
TRIANGULAR,
LOGNORMAL,
WEIBULL,
GAMMA,
};
typedef enum PTYPE typeDistribution;
class GPPROBABILITYDLL_API gpDistribution {
public:
	typeDistribution myType;

	//Parametri della distribuzione
	double m1;
	double m2;
	double m3;
	double m4;
	double m5;
	gpDistribution();
	gpDistribution(gpDistribution* );
	gpDistribution(typeDistribution , double firstParam, double secondParam=0.0,
		double thirdParam=0.0, double fourthParam=0.0, double fifthParam=0.0);

	bool gpExpoDataGeneration (base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpUniformDataGeneration(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpConstantDataGeneration(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpTriangularDataGenerator(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpLogNDataGenerator(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpNormalDataGenerator(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpWeibullDataGenerator(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpGammaDataGenerator(base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	bool gpLHSExpoDataGeneration (base_generator_type & gen,std::vector<std::vector<double> > & result,
		const int sizeTogenerate=1, const int sizey=1);
	void primeNumbersGenerator(int numN,std::vector<int> & primeSeq);

	//std::vector<double> gprandomDataGenerator(const int size, int seed,RandomNumberGenerator & gen);
	//std::vector<double> gpWeibullDataGenerator(const int size, int seed);
	//std::vector<double> gpBetaDataGenerator(const int size, int seed);

	~gpDistribution();
	// TODO: add your methods here.
};

extern GPPROBABILITYDLL_API int ngpDistribution;

GPPROBABILITYDLL_API int fngpDistribution(void);
}
#endif