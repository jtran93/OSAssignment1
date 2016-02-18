#ifndef DataTables_h
#define DataTables_h

#include <iostream>
#include <string>
#include <vector>

class DataT
{
	public:
		void readData();
		void printData();
		int getSize();
		std::string getOperation(int index);
		int getTime(int index);
		//void setData(std::vector<std::string>);
	
	private:
		int vectorSize;
		std::vector<int> time;
		std::vector<std::string> operation;
		
};

class ProgressT
{
	public:
		void addDataToProgress(DataT data);
		void printProgress(DataT data);
		/*void setStartTime(std::vector<int> sT);
		void setFirstLine(std::vector<int> fL);
		void setLastLine(std::vector<int> lL);
		void setCurrentLine(std::vector<int> cL);
		void setProcessState(std::vector<std::string> pS);
		void setIOCompletion(std::vector<int> io);*/
		
	private:
		std::vector<int> startTime;
		std::vector<int> firstLine;
		std::vector<int> lastLine;
		std::vector<int> currentLine;
		std::vector<std::string> processState;
		std::vector<int> IOCompletion;
};

class DeviceT
{
	public:
		DeviceT(void);
		void setProcess(std::string processNum, int index);
		void setCompletionTime(int time, int index);
		void printDevice();
	private:
		std::vector<std::string> process;
		std::vector<int> completionTime;
};

#endif