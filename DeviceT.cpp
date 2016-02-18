#include "DataTables.h"

/*
   Index 0 = Core0
   Index 1 = Core1
   Index 2 = Disk
   Index 3 = Input
   
Each operation can contain busy/free/process
Completion time = the time the process will be on that operation
				= 0 if it is free
*/

DeviceT::DeviceT(void)
{
	for(int i = 0; i<4; i++)
	{
		process.push_back("1");
		completionTime.push_back(0);
	}
}

void DeviceT::setProcess(std::string processNum, int index)
{
	process[index] = processNum;
}

void DeviceT::setCompletionTime(int time, int index)
{
	completionTime[index] = time;
}

void DeviceT::printDevice()
{
	int size = 4;
	for(int j = 0; j<size; j++)
	{
		std::cout<<process[j]<<" "<<completionTime[j]<<"\n";
	}
}

