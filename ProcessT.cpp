#include "DataTables.h"

void ProcessT::addDataToProcess(DataT data)
{
	int completionT = 0;

	for(int i = 0; i < data.getSize(); i++)
	{
		completionT = completionT + data.getTime(i);
		
		if(data.getOperation(i) == "START")
		{
			startTime.push_back(data.getTime(i));
			firstLine.push_back(i);				
			currentLine.push_back(i);
			hasStarted.push_back('N');
		}
		else if(data.getOperation(i) == "END")
		{	
			lastLine.push_back(i);
			IOCompletionTime.push_back(0);
			processState.push_back("Waiting");
			priority.push_back("High");
			completionT = 0;
			processTime.push_back(0);
			processCoreTime.push_back(0);
		}		
	}
	
	numProcesses = startTime.size();
}

void ProcessT::printProcessTable(DataT data)
{
	int coreTime = 0;
	int start = 0;
	int end = 0;
	
	for (int i = 0; i < startTime.size(); i++)
	{
		if(processState[i] != "Done")
		{
			
			std::cout<<"Process "<<i<<" started at "<<startTime[i]<<", got "<<processCoreTime[i]<<" ms of CORE time and is "<<processState[i]<<"\n";
		}
	}
	std::cout<<"\n";
}

void ProcessT::printProcess(int pid)
{
	std::cout<<"Process "<<pid<<" started at "<<startTime[pid]<<", got  ms of CORE time and is "<<processState[pid]<<"\n";
}

void ProcessT::printIOCompletion()
{
	for(int i = 0; i<IOCompletionTime.size(); i++)
	{
		std::cout<<"IO completion time for process "<<i<<": "<<IOCompletionTime[i]<<"\n";
	}
}

void ProcessT::removeProcess(int pid)
{
	processState[pid] = "Done";
}

void ProcessT::IORequest(int clock, int pid, int requestTime)
{
	IOCompletionTime[pid] = clock + requestTime;
}

void ProcessT::IOCompletion(int pid)
{
	priority[pid] = "High";
}

void ProcessT::setPriority(int pid, std::string pri)
{
	priority[pid] = pri;
}

void ProcessT::setProcessState(int pid, std::string state)
{
	processState[pid] = state;
}

void ProcessT::setHasStarted(int pid)
{
	hasStarted[pid] = 'Y';
}

void ProcessT::setIOCompletionTime(int pid, int requestTime)
{
	IOCompletionTime[pid] = requestTime;
}

void ProcessT::incrementCurrentLine(int pid)
{
	currentLine[pid]++;
}

void ProcessT::addToProcessTime(int pid, int time)
{
	processTime[pid] = processTime[pid] + time;
}

void ProcessT::addToCoreTime(int pid, int time)
{
	processCoreTime[pid] = processCoreTime[pid] + time;
	std::cout<<"Process "<<pid<<" has "<<processCoreTime[pid]<<" core time\n";
}

std::vector<int> ProcessT::getStartTime()
{
	return startTime;
}

int ProcessT::getFirstLine(int pid)
{
	return firstLine[pid];
}

int ProcessT::getLastLine(int pid)
{
	return lastLine[pid];
}

int ProcessT::getCurrentLine(int pid)
{
	return currentLine[pid];
}

std::string ProcessT::getProcessState(int pid)
{
	return processState[pid];
}

int ProcessT::getIOCompletionTime(int pid)
{
	return IOCompletionTime[pid];
}

std::string ProcessT::getPriority(int pid)
{
	return priority[pid];
}

void ProcessT::searchLowestStartTime(int& pid, int& time)
{
	
	for(int i = 0; i < startTime.size(); i++)
	{
		if(startTime[i]<time && hasStarted[i]=='N')
		{
			time = startTime[i];
			pid = i;
		}
	}
	
}

void ProcessT::searchLowestIOTime(int& pid, int& time)
{
	
	for(int i = 0; i < IOCompletionTime.size(); i++)
	{
		if(IOCompletionTime[i] != 0 && IOCompletionTime[i]<time)
		{
			time = IOCompletionTime[i];
			pid = i;
		}
	}
}

bool ProcessT::searchProcessRemaining()
{
	for (int i = 0; i < startTime.size(); i++)
	{
		if(processState[i] != "Done")
			return true;
	}
	return false;
}













