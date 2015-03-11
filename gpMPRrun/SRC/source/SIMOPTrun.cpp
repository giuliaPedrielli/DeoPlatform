// Approximate Simulation.cpp : Defines the entry point for the console application.


#include <SimOptModelGenDLL.h>
#include <gpProbabilityDLL.h>
//#include <wtUtility.h>
//#include <wtVfConnectorLib.h>
//#include <iomanip>
//#include <wtVfConnector.h>
//#include <wtProcess.h>
//#include <wtVfce productionSystem;
using namespace std;
using namespace OptimizationModel;
using namespace productionSystem;
using namespace SIMOPTGEN;
//using namespace wtVfdm;
#define __PARAM_MAX 5
string wtGetAppDirPath();
string wtGetAppFullPath();
int main(int argc, char *argv[])
{
	try
	{
		//*****************************************************************************
		//************************|              |*************************************
		//************************|  DATA INPUT  |*************************************
		//************************|______________|*************************************
		//*****************************************************************************

		//create the connector to the VFDM

		//wtVfConnector* vfconn = new wtVfConnector();

		std::string programPath = wtGetAppDirPath();
		std::cout << "Directory del programma: " << programPath << std::endl;

		std::string in_dimensions = programPath + "\\INPUT\\dimensions.txt";
		std::string in_machines = programPath + "\\INPUT\\MACHINEInfo.txt";
		std::string in_buffers = programPath + "\\INPUT\\buffersInfo.txt";
		std::string in_arrivalTime = programPath + "\\INPUT\\arrivalTime.txt";
		std::string in_processTime = programPath + "\\INPUT\\processTime.txt";
		std::string in_failures = programPath + "\\INPUT\\failures.txt";

		const char* in_dimen = in_dimensions.c_str();
		const char* in_mach = in_machines.c_str();
		const char* in_buff = in_buffers.c_str();
		const char* in_arrT = in_arrivalTime.c_str();
		const char* in_procT = in_processTime.c_str();
		const char* in_ff = in_failures.c_str();


		std::string out_throughput = programPath + "\\OUTPUT\\Throughput.txt";
		std::string out_x = programPath + "\\OUTPUT\\x.txt";
		std::string out_y = programPath + "\\OUTPUT\\y.txt";
		std::string out_report = programPath + "\\OUTPUT\\REP.txt";
		std::string out_tbuffer = programPath + "\\OUTPUT\\TimeBuffer.txt";
		std::string out_bounds = programPath + "\\OUTPUT\\bounds.txt";
		std::string out_fobj = programPath + "\\OUTPUT\\ObjectiveFunction.txt";
		std::string out_solApp = programPath + "\\OUTPUT\\approximateSolution.txt";

		const char* out_th = out_throughput.c_str();
		const char* out_xx = out_x.c_str();
		const char* out_yy = out_y.c_str();
		const char* out_rep = out_report.c_str();
		const char* out_tb = out_tbuffer.c_str();
		const char* out_bb = out_bounds.c_str();
		const char* out_of = out_fobj.c_str();
		const char* out_ssApp = out_solApp.c_str();
		
		//if(SIMOPTGEN::SolveModel(in_ff,in_mach,in_buff,in_dimen,out_th,out_tb,out_bb,out_rep,out_of,out_ssApp,
		//	in_processTime,in_arrivalTime))//in_arrivalTime,in_processTime))
		SIMOPTGEN::SolveModel(in_ff,in_mach,in_buff,in_dimen,out_th,out_tb,out_bb,out_rep,out_of,out_ssApp,
			in_procT,in_arrT);
			std::cout << "Model Solved" << std::endl;
	}
	catch(char* str)
	{
		std::cerr<<"  Cannot Solve previous errors "<< str <<std::endl;
	}
		
	return 0;
}

std::string wtGetAppFullPath(){
	string result;
	TCHAR szAppPath[MAX_PATH];
	GetModuleFileName(NULL, szAppPath, sizeof(szAppPath) - 1);
	for(int j=0; szAppPath[j]!=0; j++){
		result += szAppPath[j];	
	}
	return result;
}

/// get application directory path
std::string wtGetAppDirPath(){
	return wtGetAppFullPath().substr(0, wtGetAppFullPath().rfind("\\"));
}