#include "DataTables.h"
#include "Device.h"
#include "Global.h"

#include <sstream>

int main()
{	
	std::stringstream ss;
	std::string str;
	
	int nextRequest = -1;
	int did = 0;
	int lowStartTime = 500000;
	int lowStartPID = 0;
	int lowDeviceTime = 500000;
	int lowDevicePID = 0;
	int lowIOTime = 500000;
	int lowIOPID = 0;
	
	DataT data;
	ProcessT process;
	Device device;
	
	data.readData();
	process.addDataToProcess(data);
	
	process.printProcessTable(data);

	
	//while(process.searchProcessRemaining())
	//{
		process.searchLowestStartTime(lowStartPID, lowStartTime);
		process.searchLowestIOTime(lowIOPID, lowIOTime);
		device.searchLowestCompletionTime(lowDevicePID, lowDeviceTime, did);
		
		std::cout<<"LowStartPID and LowStartTime: "<<lowStartPID<<", "<<lowStartTime<<"\n";
		std::cout<<"LowIOPID and LowIOTime: "<<lowIOPID<<", "<<lowIOTime<<"\n";
		std::cout<<"LowDevicePID and LowDeviceTime: "<<lowDevicePID<<", "<<lowDeviceTime<<"\n";
		
		if(lowStartTime < lowIOTime && lowStartTime < lowDeviceTime)
		{//Arrival event of lowStartPID
		 //At arrival time lowStartPID requests a core
			ss<<lowStartPID;
			str = ss.str();
			
			totalElapsedTime = data.getTime(process.getFirstLine(lowStartPID));
			device.CPURequest(process.getFirstLine(lowStartPID)+1, str, process.getPriority(lowStartPID));
			process.setPriority(lowStartPID, "High");
			
			process.incrementCurrentLine(lowStartPID);
			nextRequest = lowStartPID;
		}
		else if (lowIOTime < lowStartTime && lowIOTime < lowDeviceTime)
		{//Complete IO of lowIOPID and fetch the next operation
			ss<<lowIOPID;
			str = ss.str();
			
			process.IOCompletion(str);
			process.setPriority(lowIOPID, "High");
			totalTimeElapsed = process.getIOCompletionTime(lowIOPID);
			
			process.incrementCurrentLine(lowIOPID);
			nextRequest = lowIOPID;
		}
		else if (lowDeviceTime < lowStartTime && lowDeviceTime < lowIOTime)
		{//Complete operation of lowDevicePID and fetch the next operation
			ss<<lowDevicePID;
			str = ss.str();
			
			if(did == 0 || did == 1)
			{
				device.CPUCompletion(did);
				totalTimeElapsed = device.getCompletionTime(did);
			}
			else if(did == 2)
			{
				device.DiskCompletion();
				totalTimeElapsed = device.getCompletionTime(did);
				process.setPriority(lowDevicePID, "Low");
			}
			
			process.incrementCurrentLine(lowDevicePID);
			nextRequest = lowDevicePID;
		}
		
		
		
	//}

	return 0;
}



































