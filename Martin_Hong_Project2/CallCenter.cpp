#include "stdafx.h"
#include "CallCenter.h"


bool operator<(const Caller &x, const Caller &y)
{
	return x.getCallInTime() < y.getCallInTime();
}

CallCenter::CallCenter()
{
	Rep rep1, rep2, rep3;
	reps.push_back(rep1);
	reps.push_back(rep2);
	reps.push_back(rep3);

}


CallCenter::~CallCenter()
{
}

void CallCenter::handle(const int & t)
{
	/*
	//check the reps to see if they are busy
	bool repsBusy = false;
	for (list<Rep>::iterator itr = reps.begin(); itr != reps.end(); ++itr)
	{
		repsBusy = repsBusy | itr->getIsHandlingCustomer();
	}
	if (priCallers.empty() && !repsBusy) return;
	*/

	//check reps, before assigning a caller to one
	for (list<Rep>::iterator itr = reps.begin(); itr != reps.end(); ++itr)
	{
		//if (priCallers.empty()) return;

		Rep & rep = *itr;
		if (rep.checkStatus(t))
		{
			//this rep is done with this caller
			Caller c;
			c = rep.getCurrentCaller();
			if (c.getCompletionDuration() != 0)
			{
				completedCallers.insert(c);
			}

			//assign the rep a new caller if available
			if (!priCallers.empty())
			{
				const Caller & priCaller = priCallers.top();
				rep.assignCaller(priCaller, t);
				priCallers.pop();
			}
		}
	}
}

string CallCenter::calculateMetrics(const int & totalNumHours)
{
	int totalSvcTime = 0;
	int totalTimeInQueue = 0;
	int totalTimeInSys = 0;
	for (set<Caller>::const_iterator citr = completedCallers.begin(); citr != completedCallers.end(); ++citr)
	{
		totalSvcTime += citr->getCompletionDuration();
		totalTimeInQueue += citr->getServiceStartTime() - citr->getCallInTime();
		totalTimeInSys += citr->getCompletionDuration() + (citr->getServiceStartTime() - citr->getCallInTime());
	}
	double avgSvcTime = totalSvcTime / completedCallers.size();
	double totalTimeInQAvg = totalTimeInQueue / completedCallers.size();
	double totalTimeInSysAvg = totalTimeInSys / completedCallers.size();

	string retStr = "================= METRICS ""=================\n";
	retStr.append("Total Number of Customers serviced in ");
	retStr.append(to_string(totalNumHours));
	retStr.append(" hours, ");
	retStr.append(to_string(completedCallers.size()));
	retStr.append("\n");
	retStr.append("Average wait time in the caller queue for a customer ");
	retStr.append(to_string(totalTimeInQAvg));
	retStr.append("\n");
	retStr.append("Average total time in the system for a customer ( queue time + service time ) ");
	retStr.append(to_string(totalTimeInSysAvg));
	retStr.append("\n");
	retStr.append("Average service time ");
	retStr.append(to_string(avgSvcTime));
	return retStr;
}

void CallCenter::addCaller(Caller & c)
{
	priCallers.push(c);
}
