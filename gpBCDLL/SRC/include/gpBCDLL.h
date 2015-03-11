// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GPBCDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GPBCDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifndef GPBOUNDING__HH
#define GPBOUNDING__HH

#ifdef GPBCDLL_EXPORTS
#define GPBCDLL_API __declspec(dllexport)
#else
#define GPBCDLL_API __declspec(dllimport)
#endif
#include "gpSYSDLL.h"
#include <vector>
typedef enum OBJTYPE{
MIN_s,
MIN_b,
MIN_WT,
MIN_TT,
MIN_ML,
};
typedef OBJTYPE _OFtype;
// This class is exported from the gpBCDLL.dll
namespace postProcess{
class GPBCDLL_API AppSolAlg{
public:
	AppSolAlg(void);
	~AppSolAlg(void);
	int calcCapApp(std::vector<double> yj,std::vector<double> yjp1, int I);
}; 
class GPBCDLL_API BoundsCalculation {
public:
	BoundsCalculation(void);
	~BoundsCalculation(void);
	int computeLowerBound(std::vector<double> x1, std::vector<double> s,int Npart, int p,int d,typeSys , _OFtype);
	int computeUpperBound(std::vector<double> x1, std::vector<double> s,int Npart, int p,int d, typeSys, _OFtype);

};

extern GPBCDLL_API int ngpBCDLL;

GPBCDLL_API int fngpBCDLL(void);
}
#endif