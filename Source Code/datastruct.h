
#include <vector>
#include<string>

#ifndef DATASTRUCT_H
#define DATASTRUCT_H



using namespace std;


struct Pair
{
	string prop;
	double value;
};

struct Pub
{
	vector<Pair> pairList;
};

struct Cnt
{
	string prop;
	double lowValue;
	double highValue;
};

struct Sub
{
	int client;
	vector<Cnt> constraintList;
};

struct Combo
{
   // bool bit;
	int value;
	int subID;
};


struct Bucket
{
	int count1;
	vector<Combo> elements;
};





#endif

