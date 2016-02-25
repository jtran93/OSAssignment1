#ifndef Device_h
#define Device_h

#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <deque>
#include <string>
#include <vector>

class Device
{
	public:
		Device(void);
		void printDevice();
		
		std::string CPURequest(int clock, int requestTime, std::string process, std::string priority);
		void CPUCompletion(int clock, int did, int& popFromQ);
		void DiskRequest(int clock, int requestTime, std::string process);
		void DiskCompletion(int clock);
		
		void searchLowestCompletionTime(int& pid, int& time, int& did);
		
		int getCompletionTime(int device);
		void resetCompletionTime(); //reset completion time if device is free to 0
		
		void printQs();
		void printHighQ();
		void printLowQ();
		void printDiskQ();
		void printCoreData(int clock);
		
	private:
		
		std::vector<std::string> deviceStatus;
		std::vector<int> completionTime;
		std::deque<std::string> highQ;
		std::deque<int> highQTime;
		std::deque<std::string> lowQ;
		std::deque<int> lowQTime;
		std::deque<std::string> diskQ;
		std::deque<int> diskQTime;
		
		int coreBusyTimes;
		int diskBusyTimes;
		
};

#endif