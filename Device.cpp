#include "Device.h"
#include "Global.h"

/*
   Index 0 = Core0
   Index 1 = Core1
   Index 2 = Disk
   
	Each operation can contain free/process ID
	Completion time = the time the process will be on that operation
				
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

void Device::CPURequest(int requestTime, std::string process, std::string priority)
{
	if(deviceStatus[0] == "Free")
	{
		deviceStatus[0] = process;
		completionTime[0] = totalElapsedTime + requestTime;
		coreBusyTimes = coreBusyTimes + requestTime;
	}
	else if(deviceStatus[1] == "Free")
	{
		deviceStatus[1] = process;
		completionTime[1] = totalElapsedTime + requestTime;
		coreBusyTimes = coreBusyTimes + requestTime;
	}
	else
	{
		if(priority == "High")
			highQ.push_back(process);
		else if(priority == " Low")
			lowQ.push_back(process);
	}
}

void Device::CPUCompletion(int did)
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
			completionTime[did] = totalElapsedTime + highQTime.front();
			coreBusyTimes = coreBusyTimes + highQTime.front();
			highQ.pop_front();
			highQTime.pop_front();
		}
		else
		{
			deviceStatus[did] = lowQ.front();
			completionTime[did] = totalElapsedTime + lowQTime.front();
			coreBusyTimes = coreBusyTimes + lowQTime.front();
			lowQ.pop_front();
			lowQTime.pop_front();
		}
	}
	
}

void Device::DiskRequest(int requestTime, std::string process)
{
	if(deviceStatus[2] == "Free")
	{
		deviceStatus[2] = process;
		completionTime[2] = totalElapsedTime + requestTime;
		diskBusyTimes = diskBusyTimes + requestTime;
	}
	else
	{
			diskQ.push_back(process);
			diskQTime.push_back(requestTime);
	}
}

void Device::DiskCompletion()
{
	if(diskQ.empty() == true)
	{
		deviceStatus[2] = "Free";
	}
	else
	{
		deviceStatus[2] = diskQ.front();
		completionTime[2] = diskQTime.front() + totalElapsedTime;
		diskQ.pop_front();
		diskQTime.pop_front();
	}
}

void Device::searchLowestCompletionTime(int& pid, int& time)
{
	for(int i = 0; i<3; i++)
	{
		if(deviceStatus[i] != "Free" && completionTime[i]<time && completionTime[i] != 0)
		{
			pid = deviceStatus[i];
			time = completionTime[i];
			did = i;
		}
	}
	
}

void Device::printHighQ()
{
	std::cout<<"HIGH-PRIORITY READY QUEUE:\n";
	if(highQ.empty() != true)
	{
		for(int i = 0; i < highQ.size(); i++)
		{
			std::cout<<"Process "<<highQ[i]<<"\n";
		}
	}
	else
	{
		std::cout<<"EMPTY\n";
	}
}

void Device::printLowQ()
{
	std::cout<<"LOW-PRIORITY READY QUEUE:\n";
	if(lowQ.empty() != true)
	{
		for(int i = 0; i < lowQ.size(); i++)
		{
			std::cout<<"Process "<<lowQ[i]<<"\n";
		}
	}
	else
	{
		std::cout<<"EMPTY\n";
	}
}

void Device::printDiskQ()
{
	std::cout<<"DISK QUEUE:\n";
	if(diskQ.empty() != true)
	{
		for(int i = 0; i < diskQ.size(); i++)
		{
			std::cout<<"Process "<<diskQ[i]<<"\n";
		}
	}
	else
	{
		std::cout<<"EMPTY\n";
	}
}

















