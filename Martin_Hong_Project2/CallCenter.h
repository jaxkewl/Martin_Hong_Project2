#pragma once
#include <queue>
#include "Caller.h"
#include "Rep.h"
#include "Cmp.h"
#include <iostream>
#include <list>
#include <set>
#include <functional>

using namespace std;

class CallCenter
{
private:
	list<Rep> reps;
	priority_queue<Caller, vector<Caller>, Cmp > priCallers;
	//queue<Caller> priCallers;
	set<Caller> completedCallers;
public:
	CallCenter();
	~CallCenter();

	void handle(const int & t);
	void addCaller(Caller & c);
	set<Caller> getCompletedCallers() const {
		return completedCallers;
	}
	string calculateMetrics(const int & totalNumHours);
};

