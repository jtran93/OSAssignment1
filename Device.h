#ifndef Device_h
#define Device_h

#include <iostream>
#include <deque>
#include <string>
#include <vector>

class Device
{
	public:
		Device(void);
		void printDevice();
		
		void CPURequest(int requestTime, std::string process, std::string priority);
		void CPUCompletion(int did);
		void DiskRequest(int requestTime, std::string process);
		void DiskCompletion();
		void IORequest();
		void IOCompletion();
		
		void searchLowestCompletionTime(int& pid, int& time, int& did);
		
		void printHighQ();
		void printLowQ();
		void printDiskQ();
		
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
		int did; //Device ID
		int crt; //Core request time
		int drt; //Disk request time
		int IOrt; //IO request time
		double coreUtilization;
		
};

#endif