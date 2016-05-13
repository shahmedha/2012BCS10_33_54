
#include "util.h"
#include "fstream"
#include "iostream"
#include "vector"
#include "string"
#include "sstream"
#include "cstdlib"
#include "time.h"
#include "omp.h"


using namespace std;



std::string Util::RemoveBlank (std::string str)
{

	unsigned short strLen = str.size ();
	while ( str.at (strLen - 1) == ' ')
	{
		str = str.substr(0, strLen - 1);
		strLen = str.size ();
	}
	return str;

}

void Util::Maopao(vector<int> &vec)
{

	int temp;
	if (vec.size() < 2)
		return;

  for(unsigned int i = 0; i < vec.size()-1; i++)
  {
  	for(unsigned int j = 0; j < vec.size()-1-i; j++)
    {
  	  if(vec.at(j) > vec.at(j+1))
      {
  	   	temp = vec.at(j);
       	vec.at(j) = vec.at(j+1);
       	vec.at(j+1) = temp;
      }
  	}
  }


}


string Util::Double2String (double value)
{

  double d = value;
  std::ostringstream os;
  os << d;
  std::string str = os.str();
 // cout<<"string:"<<str;
  return RemoveBlank(str);
}

double Util::String2Double (string str)
{

	double d;

    istringstream(str) >> d;

	return d;
}

bool Util::CheckExist (int value, vector<int> array)
{

	bool result = false;
	for (unsigned short i=0; i<array.size(); i++)
	{
		if (array.at (i) == value)
		{
			result = true;
			break;
		}
	}
	return result;
}


Sub Util::ExtractSub (string text)
{

	Sub sub;
	while (text.size () > 0)
	{

		int loc1 = text.find ('[');
		int loc2 = text.find (']');
		int loc3 = text.find(',');

		Cnt cons;
		cons.prop = text.substr (loc1 + 1, 3);
		cons.lowValue = Util::String2Double (text.substr (loc1 + 5, 8));

        cons.highValue = Util::String2Double (text.substr (loc3 + 1, 8));
		sub.constraintList.push_back (cons);
		text = text.substr (loc2+1, text.size ());

	}

	return sub;
}

Pub Util::ExtractPub (string text)
{

	Pub pub;
	while (text.size () > 0)
	{
		int loc1 = text.find ('[');
		int loc2 = text.find (']');
		Pair pair;
		pair.prop = text.substr (loc1 + 1, 3);
		pair.value = Util::String2Double (text.substr (loc1 + 5, 8));
		pub.pairList.push_back (pair);
		text = text.substr (loc2+1, text.size ());
	}

	return pub;
}


int Util::Name2Index (string str)
{
	int result = -1;

	for (unsigned short i=0; i<sizeof(attr)/sizeof("abc"); i++)
	{
		if (attr[i] == str)
		{
			result = i;
			break;
		}
	}
	return result;
}

/*-----------------------------------------------------------------
generate fixed width subscriptions according to normal distribution
------------------------------------------------------------------*/

string Util::GenerateSub_normal (int items, int attrs, double width, double alp)
{

  string subStr = "";




  double value1 = 0.0;
	double value2 = 0.0;
	double w = width;
	vector<int> props;
	int proIndex ;
	int alpha =0;
	int m_items = items;

	int i,j;


	for(j=0;j<items;j++)
	{

	proIndex=rand()%(attrs-alpha+1)+alpha;

	while (Util::CheckExist (proIndex, props))
		{
			proIndex = rand()%(attrs-alpha+1)+alpha;

		}
	props.push_back (proIndex);
	}



	Maopao (props);


	for(j=0;j<items;j++)
	{

	value1 = ((double) rand() / (RAND_MAX))+1 ;

	while (value1 < 0.00001 or value1 + w >= 0.9999)
		{
			value1 = ((double) rand() / (RAND_MAX)) ;

		}

	value2 = value1 + w;

	subStr += "[" + attr[props.at(j)] + ":" +Util::Double2String (value1) + "," + Util::Double2String (value2) + "]";
	}
	return subStr;
}


string Util::GeneratePub (int attrs)
{
	string pubStr = "";

  double a = 0.0;

  for (int i=0; i<attrs; i++)
  {
     a=((double) rand() / (RAND_MAX)) ;

  	pubStr = pubStr + "[" + attr[i] + "=" + Util::Double2String (a) + "]";

  }

  pubStr = Util::RemoveBlank (pubStr);

  return pubStr;
}


string  Util::SubDis (int items, int attrs, double width, double zipf)
{

	string subStr;

    subStr = Util::GenerateSub_normal(items, attrs, width, zipf);

	return subStr;
}

string Util::PubDis (int attrs)
{
	string pubStr;
    pubStr = Util::GeneratePub (attrs);
	return pubStr;
}






