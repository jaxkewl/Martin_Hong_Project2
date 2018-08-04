#include "stdafx.h"
#include "Rep.h"


Rep::Rep()
{
	generateNormalTimes();
}


Rep::~Rep()
{
}

void Rep::generateNormalTimes()
{
	vector<int> values(10);
	default_random_engine e;
	// Generate normally distributed numbers with mean 6 & std dev 2
	normal_distribution<> normalRandNums(6, 2);

	for (int i = 0; i < 2000; i++)
	{
		int v = lround(normalRandNums(e));	// round			
		if (v < values.size())
		{
			values[v]++;	// count how often value appears
			serviceTimes.push(v);
		}
	}

	//for (int j = 0; j < values.size(); j++)
//		cout << j << ": " << string(values[j], '*') << endl;

}

Caller Rep::getCurrentCaller()
{
	if (currentCaller.getCompletionDuration() != 0)
	{
		return currentCaller;
	}
	else
		return Caller();
}

void Rep::assignCaller(const Caller & caller, const int & t)
{
	assignedTime = t;
	currentCaller = caller;

	//assign a completion time to the caller
	timeToComplete = serviceTimes.front();
	serviceTimes.pop();
	currentCaller.setCompletionDuration(timeToComplete);
	currentCaller.setServiceStartTime(t);
	isHandlingCustomer = true;
}

bool Rep::checkStatus(const int & t)
{
	int elapsedTime = t - assignedTime;
	if (elapsedTime >= timeToComplete)
	{
		//if (!isHandlingCustomer) return false;

		isHandlingCustomer = false;
		return true;
	}
	return false;
}
