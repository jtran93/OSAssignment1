#include "DataTables.h"
#include "Device.h"
#include "Clock.h"

#include <sstream>

int main()
{	
	int clock = 0;
	
	std::stringstream ss;
	std::string str;
	std::string state;			//State of process, can be Running/Waiting/Terminated
	
	std::string operation = "";	//These are used to proceed to next step of process.
	int requestTime = 0;
	
	int nextRequest = -1;
	int did = 0;				//Device ID
	int popFromQ = 0;			//Represents process that went from High/Low Q to Core
	
	
	int lowStartTime = 500000;	//*LOW* Variables are used to compute the next event to happen.
	int lowStartPID = 0;		//Each *LOW* variable grabs the lowest start time for arrival events
	int lowDeviceTime = 500000; //and the lowest completion times for IO and Device completion times.
	int lowDevicePID = 0;		//*LOW* ID's marks the respective process.
	int lowIOTime = 500000;
	int lowIOPID = 0;
	
	DataT data;
	ProcessT process;
	Device device;
	
	data.readData();
	process.addDataToProcess(data);
	
	process.printProcessTable(data);

	while(process.searchProcessRemaining() == true)
	{
		nextRequest = -1;
		did = 0;
		
		lowStartTime = 500000;    
		lowStartPID = 0;
		lowDeviceTime = 500000;
		lowDevicePID = 0;
		lowIOTime = 500000;
		lowIOPID = 0;
		ss.str("");
		
		process.searchLowestStartTime(lowStartPID, lowStartTime);
		process.searchLowestIOTime(lowIOPID, lowIOTime);
		device.searchLowestCompletionTime(lowDevicePID, lowDeviceTime, did);
		
		
		if(lowStartTime == lowIOTime && lowStartTime == lowDeviceTime)
		{
			std::cout<<"\nWHAT'S THE ERROR\n";
			std::cout<<"CURRENT CLOCK TIME: "<<clock<<"\n";
			device.printDevice();
			process.printIOCompletion();
			device.printQs();
			std::cout<<"LowStartPID and LowStartTime:                 "<<lowStartPID<<", "<<lowStartTime<<"\n";
			std::cout<<"LowIOPID and LowIOTime:                       "<<lowIOPID<<", "<<lowIOTime<<"\n";
			std::cout<<"LowDevicePID and LowDeviceTime and Device ID: "<<lowDevicePID<<", "<<lowDeviceTime<<", "<<did<<"\n";
			std::cout<<"\n";
			return 0;
		}
		/*
			This set of ifelse statements goes through arrival and completion routines
		*/
		if(lowStartTime < lowIOTime && lowStartTime < lowDeviceTime)
		{//Arrival event of lowStartPID
		 //At arrival time lowStartPID requests a core
			std::cout<<"--ARRIVAL EVENT--\n";
			ss<<lowStartPID;
			str = ss.str();
			
			clock = data.getTime(process.getFirstLine(lowStartPID));
			
			//Sets the process to either waiting or running depending on if the process grabbed a core, or was put in queue.
			state = device.CPURequest(clock, data.getTime(process.getFirstLine(lowStartPID)+1), str, process.getPriority(lowStartPID));
			
			process.setProcessState(lowStartPID, state);
			process.setPriority(lowStartPID, "High");
			process.setHasStarted(lowStartPID);
			
			process.incrementCurrentLine(lowStartPID);
			
		}
		else if (lowIOTime < lowStartTime && lowIOTime < lowDeviceTime)
		{//Complete IO of lowIOPID and mark nextRequest with the process that completed
			std::cout<<"--IO Completion--\n";
			ss<<lowIOPID;
			str = ss.str();
			
			process.IOCompletion(lowIOPID);
			process.setPriority(lowIOPID, "High");
			clock = process.getIOCompletionTime(lowIOPID);
			process.setIOCompletionTime(lowIOPID, 0);
			
			process.incrementCurrentLine(lowIOPID);
			nextRequest = lowIOPID;
		}
		else if (lowDeviceTime < lowStartTime && lowDeviceTime < lowIOTime)
		{//Complete operation of lowDevicePID and nextRequest with process that completed
			std::cout<<"--Device Completion--";
			ss<<lowDevicePID;
			str = ss.str();
			
			if(did == 0 || did == 1)
			{
				std::cout<<"--Core Completion--\n";
				device.CPUCompletion(clock, did, popFromQ);
				clock = device.getCompletionTime(did);
				process.setProcessState(popFromQ, "RUNNING");
				process.setPriority(lowDevicePID, "Low");
			}
			else if(did == 2)
			{
				std::cout<<"--Disk Completion--\n";
				device.DiskCompletion(clock);
				clock = device.getCompletionTime(did);
				process.setPriority(lowDevicePID, "Low");
			}
			
			device.resetCompletionTime();
			
			process.incrementCurrentLine(lowDevicePID);
			nextRequest = lowDevicePID;
		}
		
		/*
			This set of ifelse computes CPU/IO/Disk request routines.
		*/
		if(nextRequest != -1)
		{
			ss.str("");
			ss<<nextRequest;
			str = ss.str();
			
			operation = data.getOperation(process.getCurrentLine(nextRequest));
			requestTime = data.getTime(process.getCurrentLine(nextRequest));
			if(operation == "CORE")
			{
				std::cout<<"--Core Request--\n";
				state = device.CPURequest(clock, requestTime, str, process.getPriority(nextRequest));
				process.setProcessState(nextRequest, state);
			}
			else if(operation == "I/O")
			{
				std::cout<<"--IO Request--\n";
				process.setProcessState(nextRequest, "WAITING");
				process.IORequest(clock, nextRequest, requestTime);
			}
			else if(operation == "DISK")
			{
				std::cout<<"--Disk Request--\n";
				if(requestTime == 0)
				{
					std::cout<<"--DISK CORE Request--\n";
					process.incrementCurrentLine(nextRequest);
					operation = data.getOperation(process.getCurrentLine(nextRequest));
					state = requestTime = data.getTime(process.getCurrentLine(nextRequest));
					process.setProcessState(nextRequest, state);
					
					device.CPURequest(clock, requestTime, str, process.getPriority(nextRequest));
				}
				else
				{
					process.setProcessState(nextRequest, "WAITING");
					device.DiskRequest(clock, requestTime, str);
				}
			}
			else if(operation == "END")
			{
				std::cout<<"--Process "<<nextRequest<<" has terminated--\n";
				std::cout<<"--CURRENT STATE OF SYSTEM AT TIME "<<clock<<"--\n";
				device.printCoreData(clock);
				device.printQs();
				
				process.setProcessState(nextRequest, "TERMINATED");
				std::cout<<"==Process Table=="<<"\n";
				process.printProcessTable(data);
				process.removeProcess(nextRequest);
				
				device.printDevice();
				process.printIOCompletion();
				
				
			}
		}
		
	}

	return 0;
}


































