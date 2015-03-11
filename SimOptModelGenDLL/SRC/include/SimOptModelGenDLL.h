// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SIMOPTMODELGENDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SIMOPTMODELGENDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SIMOPTMODELGENDLL_EXPORTS
#define SIMOPTMODELGENDLL_API __declspec(dllexport)
#else
#define SIMOPTMODELGENDLL_API __declspec(dllimport)
#endif
#include <App_OpModel.h>

namespace SIMOPTGEN{

// This class is exported from the SimOptModelGenDLL.dll
class SIMOPTMODELGENDLL_API CSimOptModelGenDLL {
public:
	CSimOptModelGenDLL(void);
	// TODO: add your methods here.
};

extern SIMOPTMODELGENDLL_API int nSimOptModelGenDLL;
SIMOPTMODELGENDLL_API std::vector<double> vectorSort(std::vector<double> v2Sort,int q, int p);
SIMOPTMODELGENDLL_API int fnSimOptModelGenDLL(void);
SIMOPTMODELGENDLL_API OptimizationModel::App_OpModel* createOptimizationModel(std::ifstream & in_algInfo,
						  productionSystem::gpProductionSystem* Sys/*,
						  std::ifstream & in_processTime=std::ifstream(), std::ifstream & in_arrivalTime=std::ifstream()*/);

SIMOPTMODELGENDLL_API void createSystem(productionSystem::gpProductionSystem* Sys, std::ifstream & in_mach, std::ifstream & in_buff);
SIMOPTMODELGENDLL_API bool GenFailures(std::ifstream & in_fail,std::map<int,std::vector<std::pair<double,stochasticProperty::gpDistribution*> > > & _FailureMDescr);
extern SIMOPTMODELGENDLL_API void SolveModel(const char* & failFile,const char* & in_machf, const char* & in_bufff, 
									  const char* & in_dimensionsf,
									  const char* & out_thf, const char* & out_tbf,
									  const char* & out_boundsf,const char* & out_rep,const char* & out_fo,const char* & out_solApp,
									  const char* & in_procTf, const char* & in_arrTimef);
//SIMOPTMODELGENDLL_API void OutputStatistics(OptimizationModel::App_OpModel *myMod,std::ofstream &out_res,int r);
//SIMOPTMODELGENDLL_API void OutputStatistics(OptimizationModel::App_OpModel* myMod,std::ofstream &out_res, int re);
extern SIMOPTMODELGENDLL_API bool SimulationModel(const char* & f1, const char* & f2, const char* & f3,
										  const char* & f4, const char* & f5, const char* & f6,const char* & f7,
										  const char*  & f8, const char* & f9);
//SIMOPTMODELGENDLL_API bool SimulationModel(std::string in_machines, std::string in_buffers, std::string in_dimensions,
//										   std::string out_throughput, std::string out_x, std::string out_y,std::string out_report,
//										   std::string in_processTime = "", std::string in_arrTime="");

//SIMOPTMODELGENDLL_API void SolveOptModel(std::ifstream & in_mach, std::ifstream & in_buff,std::ifstream & in_algInfo,
//										 std::ofstream & out_throughput,std::ofstream & out_tb, std::ofstream & out_BC,
//										 std::ifstream & in_processTime=std::ifstream(), std::ifstream & in_arrivalTime=std::ifstream());

}