#include "DataTables.h"
#include "Global.h"

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
			currentLine.push_back(i+1);
			hasStarted.push_back('N');
		}
		else if(data.getOperation(i) == "END")
		{	
			lastLine.push_back(i);
			IOCompletionTime.push_back(0);
			processState.push_back("Waiting");
			priority.push_back("High");
			completionT = 0;
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
			start = firstLine[i];
			end = lastLine[i];
			
			for(start; start<end; start++)
			{
				if(data.getOperation(start) == "CORE")
				{
					coreTime = coreTime + data.getTime(start);
				}
			}
			std::cout<<"Process "<<i<<" started at "<<startTime[i]<<", got "<<coreTime<<" ms of CORE time and is "<<processState[i]<<"\n";
		coreTime = 0;
		}
	}
}

void ProcessT::printProcess(int pid)
{
	std::cout<<"Process "<<pid<<" started at "<<startTime[pid]<<", got  ms of CORE time and is "<<processState[pid]<<"\n";
}

void ProcessT::removeProcess(int pid)
{
	processState[pid] = "Done";
}

void ProcessT::IORequest(int pid, int requestTime)
{
	IOCompletionTime[pid] = totalElapsedTime + requestTime;
}

void ProcessT::IOCompletion(int pid)
{
	priority[pid] = "High";
}

void ProcessT::setPriority(int pid, std::string pri)
{
	priority[pid] = pri;
}

void ProcessT::incrementCurrentLine(int pid)
{
	currentLine[i]++;
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















