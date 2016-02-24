#include "DataTables.h"
#include "Device.h"
#include "Global.h"

int main()
{	

	int lowStartTime = 0;
	int lowStartPID = 0;
	int lowDeviceTime = 0;
	int lowDevicePID = 0;
	int lowIOTime = 0;
	int lowIOPID = 0;
	
	DataT data;
	ProcessT process;
	Device device;
	
	data.readData();
	process.addDataToProcess(data);
	
	data.printData();
	process.printProcessTable(data);
	
	std::cout<<"Deleting a process\n";
	process.removeProcess(0);
	process.printProcessTable(data);
	
	device.printDevice();

	
	while(process.getStartTime().empty() != true)
	{

		
		process.searchLowestStartTime(lowStartPID, lowStartTime);
		process.searchLowestIOTime(lowIOPID, lowIOTime);
		device.searchLowestCompletionTime(lowDevicePID, lowDeviceTime);
		
		if(lowStartTime < lowIOTime && lowStartTime < lowDeviceTime)
		{
			//Arrival event of lowStartPID
		}
		else if (lowIOTime < lowStartTime && lowIOTime < lowDeviceTime)
		{
			//Complete IO of lowIOPID and fetch the next operation
		}
		else if (lowDeviceTime < lowStartTime && lowDeviceTime < lowIOTime)
		{
			
			//Complete operation of lowDevicePID and fetch the next operation
		}
		
	}

	
	
	
	
	
	
	return 0;
}



































