#pragma once
#include <string>

using namespace std;



class Caller
{
private:
	int priority;
	bool hasPaidSub = false;
	double callInTime = 0.0;
	int serviceStartTime = 0;
	int completionDuration = 0;
	int cntr = 0;
public:
	Caller();
	~Caller();
	void setCntr(const int & c) {
		cntr = c;
	}


	int getPriority() const {
		return priority;
	}
	void setPriority(const int p)
	{
		priority = p;
	}

	void setHasPaidSubs(const bool & sub)
	{
		hasPaidSub = sub;
	}
	bool getHasPaidSubs()
	{
		return hasPaidSub;
	}

	void setCallInTime(const double & t)
	{
		callInTime = t;
	}
	double getCallInTime() const
	{
		return callInTime;
	}

	void setServiceStartTime(const int & t)
	{
		serviceStartTime= t;
	}
	int getServiceStartTime() const
	{
		return serviceStartTime;
	}

	void setCompletionDuration(const int & t)
	{
		completionDuration = t;
	}
	int getCompletionDuration() const
	{
		return completionDuration;
	}

	string toString() {
		string returnStr = "callin time: ";
		returnStr.append(to_string(callInTime));
		returnStr.append(", completion time: ");
		returnStr.append(to_string(completionDuration));

		return returnStr;
	}
};

