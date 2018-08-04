// Martin_Hong_Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Caller.h"
#include "CallCenter.h"
#include "Cmp.h"
#include <vector>
#include <queue>
#include <list>
#include <random>
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <iomanip>

using namespace std;

queue<Caller> callers;
CallCenter cc;
int numberOfHours = 24;
int callerCntr = 0;

void createCallers(const vector<double> & times, queue<Caller> & callers)
{
	int cntr = 0;
	int subCntr = 0;
	for (vector<double>::const_iterator citr = times.begin(); citr != times.end(); ++citr)
	{
		Caller c;
		c.setCntr(++callerCntr);
		if (++cntr % 3 == 0)
		{
			c.setHasPaidSubs(true);
			++subCntr;
		}
		c.setCallInTime(*citr);
		callers.push(c);
	}
	cout << "sub callers: " << subCntr << ", total callers: " << cntr << endl;
}


//using the exponential distribution formula, generate a time.
double ran_expo(double lambda) {
	double u;
	u = rand() / (RAND_MAX + 1.0);
	return -log(1 - u) / lambda;
}

/*
void gen()
{
	const int nrolls = 1000;  // number of experiments
	const int nstars = 100;    // maximum number of stars to distribute
	const int nintervals = 30; // number of intervals

	std::default_random_engine generator;
	std::exponential_distribution<double> distribution(25);

	int p[nintervals] = {};

	for (int i = 0; i < nrolls; ++i) {
		double number = distribution(generator);
		if (number < 1.0) ++p[int(nintervals*number)];
	}

	std::cout << "exponential_distribution (25):" << std::endl;
	std::cout << std::fixed; std::cout.precision(1);

	for (int i = 0; i < nintervals; ++i) {
		std::cout << float(i) / nintervals << "-" << float(i + 1) / nintervals << ": ";
		std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
	}

}

void generateExpTimesForOneHour2(vector<int> & times)
{
	double const exp_dist_mean = 5;
	double const exp_dist_lambda = 1 / exp_dist_mean;
	random_device rd;

	exponential_distribution<> rng(exp_dist_lambda);
	mt19937 rnd_gen(rd());

	map<int, int> result_set;

	for (int i = 0; i < 500000; ++i)
	{
		int t = rng(rnd_gen) * 4;
		times.push_back(t);
		++result_set[t];
	}


	for (auto& v : result_set) {
		std::cout << std::setprecision(2) << std::fixed;

		std::cout << v.first / 4.f << " - " << (v.first + 1) / 4.f << " -> ";
		std::cout << std::string(v.second / 400, '.') << std::endl;

		if (v.second / 400 == 0)
			break;
	}

}
*/

//average rate of 25 calls per hour --> 0.41 calls per minute.
//average time between arrivals = 1/25 = 0.04
void generateExpTimesForOneHour(vector<double> & times, const int & offset)
{
	const int numOfTimes = 40;
	default_random_engine e;
	exponential_distribution<> expoRandNums(25);

	double interArrivalTime = 0;
	double arrivalTime = 0;
	int cntr = 0;
	double offsetTime = offset * 3600;
	for (int i = 0; i < numOfTimes; i++)
	{
		double v = expoRandNums(e);
		//v *= 20;
		v *= 60;
		arrivalTime += v;
		times.push_back(arrivalTime + offsetTime);
		double displayTime = offsetTime + arrivalTime;
		cout << "(" << ++cntr << "/" << numOfTimes << "), interval: " << to_string(v) << ", Calling time: " << displayTime << endl;
	}
}

//create the times and then generate the callers
void setup()
{
	vector<double> times;
	int numOfTimes = 100;
	vector<double> tmpTimes;
	for (int i = 0; i < numberOfHours; ++i)
	{
		tmpTimes.clear();
		generateExpTimesForOneHour(tmpTimes, i);
		for (vector<double>::const_iterator citr = tmpTimes.begin(); citr != tmpTimes.end(); ++citr)
		{
			double rTime = *citr;
			times.push_back(rTime);
		}
	}
	createCallers(times, callers);
}

//step through each second and when the caller matches the time, 
//then push each caller into the call center
void simulate(const int & endTime)
{
	int totalCalls = 0;
	for (int t = 0; t < endTime; t++)
	{
		int callsAdded = 0;
		//add callers to the list
		if (!callers.empty())
		{
			Caller c = callers.front();
			while (!callers.empty() && t > c.getCallInTime())
			{
				++callsAdded;
				cc.addCaller(c);
				callers.pop();
				if (!callers.empty())
					c = callers.front();
			}
		}
		totalCalls += callsAdded;
		//cout << "at time: " << t << ", added " << callsAdded << " callers" << ", total: " << totalCalls << endl;
		cc.handle(t);
	}
}

//get the metrics from the call center and display them
void displayMetrics(const int & numOfHours)
{
	string metrics = cc.calculateMetrics(numOfHours);
	cout << metrics.c_str() << endl;
}


//test class for testing the priority queue
void testPriQ()
{
	Caller c1, c2, c3, c4, c5, c6, c7, c8;
	c1.setCallInTime(1.0);
	c2.setCallInTime(2.0);
	c3.setCallInTime(10.0);
	c4.setCallInTime(4.0);
	c4.setHasPaidSubs(true);
	c5.setCallInTime(1.5);
	c6.setCallInTime(4.1);
	c6.setHasPaidSubs(true);


	priority_queue<Caller, vector<Caller>, Cmp > priCallers;
	//priority_queue<Caller, vector<Caller>, greater<Caller> > priCallers;
	//priority_queue<Caller> priCallers;
	priCallers.push(c1);
	priCallers.push(c2);
	priCallers.push(c3);
	priCallers.push(c4);
	priCallers.push(c5);
	priCallers.push(c6);
	while (!priCallers.empty())
	{
		cout << priCallers.top().getCallInTime() << endl;
		priCallers.pop();
	}

}

int main()
{
	//testPriQ();
	numberOfHours = 24;

	//setup all the callers that will call in using an exponential distribution
	setup();

	//push the callers into the call center so it can handle them
	int endTime = numberOfHours * 60 * 60;
	cout << "Simulating for " << endTime << " seconds" << endl;
	simulate(endTime);
	displayMetrics(numberOfHours);
	return 0;
}

