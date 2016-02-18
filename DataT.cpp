#include "DataTables.h"

void DataT::readData()
{
	std::string inputOperation;
	int inputTime;
	
	while(!std::cin.eof())
	{
		std::cin >> inputOperation;
		if(inputOperation != "END")
		{
			std::cin >> inputTime;
		}
		else
			inputTime = 0;
		time.push_back(inputTime);
		operation.push_back(inputOperation);
	}	
	
	vectorSize = time.size();

}

void DataT::printData()
{
	int index = 0;

	for(index = 0; index<vectorSize; index++)
	{
		std::cout<<operation[index]<<" "<<time[index]<<"\n";
	}

}

int DataT::getSize()
{
	return vectorSize;
}


std::string DataT::getOperation(int index)
{
	return operation[index];
}

int DataT::getTime(int index)
{
	return time[index];	
}