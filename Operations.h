#ifndef Operations_h
#define Operations_h

#include <vector>
#include <iostream>
#include <queue>

class Operations
{
	public:
		void CPURequest();
		void CPUCompletion();
		void DiskRequest();
		void DiskCompletion();
		void IORequest();
		void IOCompletion();
	private:
		Queue HighQ;
		Queue LowQ;
		Queue DiskQ;
};
#endif;




