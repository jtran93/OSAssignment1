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
		
		void IORequest(int pid, int requestTime);
		void IOCompletion(int pid);
		
		//Set functions
		void setPriority(int pid, std::string pri);
		void incrementCurrentLine(int pid);
		
		//Get functions
		std::vector<int> getStartTime();
		int getFirstLine(int pid);
		int getLastLine(int pid);
		int getCurrentLine(int pid);
		std::string getProcessState(int pid);
		int getIOCompletionTime(int pid);
		std::string getPriority(int pid);
		
		void searchLowestStartTime(int& pid, int& time);
		void searchLowestIOTime(int& pid, int& time);
		bool searchProcessRemaining();
		
		
		
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