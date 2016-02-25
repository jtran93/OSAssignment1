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

class ProcessT
{
	public:
		void addDataToProcess(DataT data);
		void printProcessTable(DataT data);
		void printProcess(int pid);
		void removeProcess(int pid);
		
		void IORequest(int pid, int clock, int requestTime);
		void IOCompletion(int pid);
		
		void setPriority(int pid, std::string pri);
		std::string getPriority(int pid);
		std::vector<int> getStartTime();
		/*
			Have to add get and set functions for vectors
		*/
		
		void searchLowestStartTime(int& pid, int& time);
		void searchLowestIOTime(int& pid, int& time);
		
		
		
	private:
		int numProcesses;
		std::vector<char> hasStarted;
		std::vector<int> startTime;
		std::vector<int> firstLine;
		std::vector<int> lastLine;
		std::vector<int> currentLine; //Must be between firstLine and lastLine of process
		std::vector<std::string> processState;
		std::vector<int> IOCompletionTime;
		std::vector<std::string> priority;
};
#endif