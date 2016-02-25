#include "Device.h"

/*
   Index 0 = Core0
   Index 1 = Core1
   Index 2 = Disk
   
	Each device can contain free/process ID
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
	std::cout<<"\n";
}

std::string Device::CPURequest(int clock, int requestTime, std::string process, std::string priority)
{
	
	if(deviceStatus[0] == "Free")
	{
		//std::cout<<"Process "<<process<<" is at CORE "<<0<<"\n";
		
		deviceStatus[0] = process;
		completionTime[0] = clock + requestTime;
		coreBusyTimes = coreBusyTimes + requestTime;
		return "RUNNING";
	}
	else if(deviceStatus[1] == "Free")
	{
		//std::cout<<"Process "<<process<<" is at CORE "<<1<<"\n";
		
		deviceStatus[1] = process;
		completionTime[1] = clock + requestTime;
		coreBusyTimes = coreBusyTimes + requestTime;
		return "RUNNING";
	}
	else
	{
		//std::cout<<"WHICH Q DO I GO TO? "<<priority<<"\n";
		if(priority == "High")
		{
			//std::cout<<"Process "<< process<<" went to *HIGH* Q\n";
			
			highQ.push_back(process);
		}
		else if(priority == "Low")
		{
			//std::cout<<"Process "<< process<<" went to *LOW* Q\n";
			
			lowQ.push_back(process);
		}
		return "READY";
	}
}

void Device::CPUCompletion(int clock, int did, int& popFromQ)
{
	
	if(highQ.empty() == true && lowQ.empty() == true)
	{
		//std::cout<<"CORE Qs are empty!\n";
		
		
		
		deviceStatus[did] = "Free";
	}
	else
	{
		if(highQ.empty() == false)
		{
			//std::cout<<"Process "<<highQ.front()<<" from *HIGH* Q to CORE "<<did<<"\n";
			
			
			deviceStatus[did] = highQ.front();
			completionTime[did] = clock + highQTime.front();
			coreBusyTimes = coreBusyTimes + highQTime.front();
			highQ.pop_front();
			highQTime.pop_front();
			
			popFromQ = atoi(deviceStatus[did].c_str());
		}
		else if(lowQ.empty() == false)
		{
			//std::cout<<"Process "<<lowQ.front()<<" from *LOW* Q to CORE "<<did<<"\n";
			
			
			
			deviceStatus[did] = lowQ.front();
			completionTime[did] = clock + lowQTime.front();
			coreBusyTimes = coreBusyTimes + lowQTime.front();
			lowQ.pop_front();
			lowQTime.pop_front();
			
			popFromQ = atoi(deviceStatus[did].c_str());
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
		//std::cout<<"Process "<<process<<" goes to *DISK* Q\n";
		
		diskQ.push_back(process);
		diskQTime.push_back(requestTime);
	}
}

void Device::DiskCompletion(int clock)
{
	if(diskQ.empty() == true)
	{
		
		//std::cout<<"DISK Q is empty!\n";
		
		
		
		deviceStatus[2] = "Free";
	}
	else
	{
		//std::cout<<"Process "<<diskQ.front()<<" from *DISK* Q to DISK\n";
		
		
		deviceStatus[2] = diskQ.front();
		completionTime[2] = diskQTime.front() + clock;
		diskQ.pop_front();
		diskQTime.pop_front();
	}
}

void Device::searchLowestCompletionTime(int& pid, int& time, int& did)
{
	
	for(int i = 0; i<3; i++)
	{
		if(/*deviceStatus[i] != "Free" &&*/ completionTime[i]<time && completionTime[i] != 0)
		{	
			pid = atoi(deviceStatus[i].c_str());
			time = completionTime[i];
			did = i;
		}
	}
	
}

int Device::getCompletionTime(int device)
{
	return completionTime[device];
}

void Device::resetCompletionTime()
{
	for(int i = 0; i < 3; i++)
	{
		if(deviceStatus[i] == "Free")
			completionTime[i] = 0;
	}
}

void Device::printQs()
{
	printHighQ();
	printLowQ();
	printDiskQ();
}

void Device::printHighQ()
{
	std::cout<<"==HIGH-PRIORITY READY QUEUE==\n";
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
	std::cout<<"==LOW-PRIORITY READY QUEUE==\n";
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
	std::cout<<"==DISK QUEUE==\n";
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

void Device::printCoreData(int clock)
{
	int numBusyCores = 0;
	for(int i = 0; i < 2; i++)
	{
		if(deviceStatus[i] != "Free")
			numBusyCores++;
	}
	
	std::cout<<"Current number of busy cores: "<<numBusyCores<<"\n";
	
	float avgNumBusyCores = double(coreBusyTimes) / double(clock);
	std::cout<<"Average number of busy cores: "<<std::setprecision(3)<<avgNumBusyCores<<"\n";
}

















