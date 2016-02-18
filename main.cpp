#include "DataTables.h"

int main()
{
	DataT data;
	ProgressT progress;
	DeviceT device;
	
	data.readData();
	progress.addDataToProgress(data);
	
	data.printData();
	progress.printProgress(data);
	
	device.printDevice();

	return 0;
}