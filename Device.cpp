#include "Device.h"
#include "Global.h"

/*
   Index 0 = Core0
   Index 1 = Core1
   Index 2 = Disk
   Index 3 = Input
   
	Each operation can contain busy/free/process
	Completion time = the time the process will be on that operation
					= 0 if it is free
				
	Events
		Arrival of new process
		Start of computing step
		Completion of computing step
		
	High Priority
		If process has completed I/O request
	Low Priority
		if process has completed disk request			
	
*/

Device::Device(void)
{
	for(int i = 0; i<3; i++)
	{
		deviceStatus.push_back("Free");
		completionTime.push_back(0);
	}
	coreBusyTimes = 0;
	diskBusyTimes = 0;
}

void Device::printDevice()
{
	int size = 3;
	for(int j = 0; j<size; j++)
	{
		std::cout<<deviceStatus[j]<<" "<<completionTime[j]<<"\n";
	}
}

void Device::CPURequest(int clock, int requestTime, std::string process, std::string priority)
{
	if(deviceStatus[0] == "Free")
	{
		deviceStatus[0] = process;
		completionTime[0] = clock + requestTime;
		coreBusyTimes = coreBusyTimes + requestTime;
	}
	else if(deviceStatus[1] == "Free")
	{
		deviceStatus[1] = process;
		completionTime[1] = clock + requestTime;
		coreBusyTimes = coreBusyTimes + requestTime;
	}
	else
	{
		if(priority == "High")
			highQ.push(process);
		else if(priority == " Low")
			lowQ.push(process);
	}
}

void Device::CPUCompletion(int did, int clock)
{
	if(highQ.empty() == true && lowQ.empty() == true)
	{
		deviceStatus[did] = "Free";
	}
	else
	{
		if(highQ.empty() == false)
		{
			deviceStatus[did] = highQ.front();
			completionTime[did] = clock + highQTime.front();
			coreBusyTimes = coreBusyTimes + highQTime.front();
			highQ.pop();
			highQTime.pop();
		}
		else
		{
			deviceStatus[did] = lowQ.front();
			completionTime[did] = clock + lowQTime.front();
			coreBusyTimes = coreBusyTimes + lowQTime.front();
			lowQ.pop();
			lowQTime.pop();
		}
	}
	
}

void Device::DiskRequest(int clock, int requestTime, std::string process)
{
	if(deviceStatus[2] == "Free")
	{
		deviceStatus[2] = process;
		completionTime[2] = clock + requestTime;
		diskBusyTimes = diskBusyTimes + requestTime;
	}
	else
	{
			diskQ.push(process);
			diskQTime.push(requestTime);
	}
}

void Device::DiskCompletion(int clock)
{
	if(diskQ.empty() == true)
	{
		deviceStatus[2] == "Free";
	}
	else
	{
		deviceStatus[2] = diskQ.front();
		completionTime[2] = diskQTime.front() + clock;
	}
}

void Device::searchLowestCompletionTime(int& pid, int& time)
{
	for(int i = 0; i<3; i++)
	{
		if(deviceStatus[i] != "Free" && i == 0)
		{
			pid = i;
			time = completionTime[i];
		}
		else if(deviceStatus[i] != "Free" && completionTime[i]<time)
		{
			pid = i;
			time = completionTime[i];
		}
	}
	
}


















