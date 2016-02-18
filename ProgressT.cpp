#include "DataTables.h"

void ProgressT::addDataToProgress(DataT data)
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
		}
		else if(data.getOperation(i) == "END")
		{	
			lastLine.push_back(i);
			IOCompletion.push_back(completionT);
			processState.push_back("Waiting");
			completionT = 0;
		}		
	}
}

void ProgressT::printProgress(DataT data)
{
	int coreTime = 0;
	int start = 0;
	int end = 0;
	
	int size = startTime.size();
	for (int i = 0; i < size; i++)
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