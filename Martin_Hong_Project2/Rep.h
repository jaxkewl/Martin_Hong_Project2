#pragma once
#include "Caller.h"
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Rep
{
private:
	bool isHandlingCustomer = false;
	int timeToComplete = 0.0;
	int assignedTime = 0;
	Caller currentCaller;
	queue<int> serviceTimes;

public:
	Rep();
	~Rep();
	bool getIsHandlingCustomer() const { return isHandlingCustomer; };
	void setIsHandlingCustomer(const bool & h) { isHandlingCustomer = h; };
	double getTimeToComplete() const { return timeToComplete; };
	void setTimeToComplete(const double & t) { timeToComplete = t; };
	void assignCaller(const Caller & caller, const int & t);
	bool checkStatus(const int & t);
	void generateNormalTimes();
	Caller getCurrentCaller();
};

