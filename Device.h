#ifndef Device_h
#define Device_h

#include <iostream>
#include <queue>
#include <string>
#include <vector>

class Device
{
	public:
		Device(void);
		void printDevice();
		
		void CPURequest(int clock, int crt, std::string process, std::string priority);
		void CPUCompletion(int did, int clock);
		void DiskRequest(int clock, int requestTime, std::string process);
		void DiskCompletion(int clock);
		void IORequest();
		void IOCompletion();
		
		void searchLowestCompletionTime(int& pid, int& time);
		
	private:
		
		std::vector<std::string> deviceStatus;
		std::vector<int> completionTime;
		std::queue<std::string> highQ;
		std::queue<int> highQTime;
		std::queue<std::string> lowQ;
		std::queue<int> lowQTime;
		std::queue<std::string> diskQ;
		std::queue<int> diskQTime;
		
		int coreBusyTimes;
		int diskBusyTimes;
		int did; //Device ID
		int crt; //Core request time
		int drt; //Disk request time
		int IOrt; //IO request time
		double coreUtilization;
		
};

#endif