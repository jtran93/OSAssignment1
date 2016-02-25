#include "DataTables.h"
#include "Global.h"

void ProcessT::addDataToProcess(DataT data)
{
	int dataSize = data.getSize();	
	int completionT = 0;

	for(int i = 0; i < dataSize; i++)
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
			IOCompletionTime.push_back(completionT);
			processState.push_back("Waiting");
			completionT = 0;
			priority.push_back("High");
		}		
	}
	
	numProcesses = startTime.size();
}

void ProcessT::printProcessTable(DataT data)
{
	int coreTime = 0;
	int start = 0;
	int end = 0;
	
	int size = startTime.size();
	for (int i = 0; i < size; i++)
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

void ProcessT::IORequest(int pid, int clock, int requestTime)
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

std::vector<int> ProcessT::getStartTime()
{
	return startTime;
}

std::string ProcessT::getPriority(int pid)
{
	return priority[pid];
}

void ProcessT::searchLowestStartTime(int& pid, int& time)
{
	int size = startTime.size();
	
	for(int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			time = startTime[i];
			pid = i;
		}
		else if(startTime[i]<time && hasStarted[i]=='N')
		{
			time = startTime[i];
			pid = i;
		}
	}
	
}

void ProcessT::searchLowestIOTime(int& pid, int& time)
{
	int size = IOCompletionTime.size();
	
	for(int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			time = IOCompletionTime[i];
			pid = i;
		}
		else if(IOCompletionTime[i]<time)
		{
			time = IOCompletionTime[i];
			pid = i;
		}
	}
}















