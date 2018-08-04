#pragma once
#include "Caller.h"

// Order Sales by greatest sale amount
class Cmp
{
public:
	bool operator()(Caller &x, Caller &y)
	{
		if (x.getHasPaidSubs() && !y.getHasPaidSubs())
		{
			return false;
		}
		if (!x.getHasPaidSubs() && y.getHasPaidSubs())
		{
			return true;
		}
		//earlier calls get priority when both have no paid subs, or
		//both have paid subs.
		return x.getCallInTime() > y.getCallInTime();
	}
};