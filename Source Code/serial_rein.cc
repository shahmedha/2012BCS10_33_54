#include<iostream>
#include "util.h"
#include "datastruct.h"
#include <sys/time.h>

using namespace std;

int main ()
{

  int subs =10000;			//number of subs submitted
  int ifNo =10000; 	    	//number of interfaces
  int pubs =1;						//number of pubs published
  int attrs = 60;				//number of attributes in pubs schema
  int items = 10;					//number of constraints in subs
  double width = 0.5;   	//constraints width of subs
  int cells = 8;					//number of cells divided among [0,1]
  int first = 8;					//number of indexed attributes for method 2
  double zipf = 0.01; 	//attributes selection distribution

  int nobkt = 1000;  //the number of buckets=1000
  unsigned  long diff;

	vector<int> matchNo;
	vector<Sub> m_subList;
	string ostr = "";



	Bucket bucket_array[(attrs+1)*2][nobkt];
	for (int i=0; i<((attrs+1)*2); i++)
	for (int j=0; j<nobkt; j++)
			bucket_array[i][j].count1=0;


/*
	----------------------------------------******************----------------------------------------
																						Sub Processing
	----------------------------------------******************----------------------------------------
*/

	string subStr;
	Sub sub;

	double step = 2000000.0 / nobkt;
	int index=-1;
        int lowVal, higVal;
	int loc1, loc2;
	Combo combo1;

	for (int n=0; n<subs; n++)
	{

		subStr = Util::SubDis (items, attrs, width, zipf);
		cout<<endl<<"substr"<<subStr;

		sub = Util::ExtractSub (subStr);

		sub.client = n/(subs/ifNo);
		m_subList.push_back (sub);

        cout<<endl;



		for (int i=0; i<=(sub.constraintList.size ()-1); i++)
		{
			index = Util::Name2Index (sub.constraintList.at(i).prop);


			lowVal =  sub.constraintList.at(i).lowValue * 2000000.0 ;

			higVal =  sub.constraintList.at(i).highValue * 2000000.0 ;
			loc1 = (int) ( lowVal / step);
			loc2 = (int) ( higVal / step);


			bucket_array[index*2][loc1].count1++;
            combo1.value = lowVal;
            combo1.subID = n;
            bucket_array[index*2][loc1].elements.push_back(combo1);



			bucket_array[index*2+1][loc2].count1++;
			combo1.subID = n;
			combo1.value = higVal;
			bucket_array[index*2+1][loc2].elements.push_back(combo1);


		}
    }


	/*
	----------------------------------------******************----------------------------------------
																						Event Matching
	----------------------------------------******************----------------------------------------
	*/

  cout<<endl; cout<<endl; cout<<endl;

    vector<bool> bits;
    string pubStr;
    Pub pub;
    int matchIf=0;
    int n,i,j,k;
    struct timeval tv1, tv2;


    gettimeofday(&tv1, NULL);

		for (n=0; n<pubs; n++)
		{

			pubStr = Util::PubDis (attrs);
			pub = Util::ExtractPub (pubStr);

			bits.resize(subs);
			for (i=0; i<subs; i++)
				bits.at(i) = false;


			for (i=0; i<pub.pairList.size(); i++)
			{
				index = Util::Name2Index (pub.pairList.at (i).prop);
				lowVal = pub.pairList.at (i).value * 2000000 - 1;
				higVal = lowVal + 2;

				loc1 = (int) lowVal / step;
				loc2 = (int) higVal /step;


				for (k=0; k<bucket_array[index*2+1][loc1].elements.size(); k++)
				{
					if (bucket_array[index*2+1][loc1].elements.at(k).value<lowVal)
					{

						bits.at(bucket_array[index*2+1][loc1].elements.at(k).subID) = true;


					}

				}




				for (j=0; j<loc1; j++)
				{
					for (k=0; k<bucket_array[index*2+1][j].elements.size(); k++)
					{
						bits.at(bucket_array[index*2+1][j].elements.at(k).subID) = true;

					}

				}



				for (k=0; k<bucket_array[index*2][loc2].elements.size(); k++)
				{
					if (bucket_array[index*2][loc2].elements.at(k).value>higVal)
					{
						bits.at(bucket_array[index*2][loc2].elements.at(k).subID) = true;



					}

				}

                for (j=loc2+1; j<nobkt; j++)
				{
					for (k=0; k<bucket_array[index*2][j].elements.size(); k++)
					{
						bits.at(bucket_array[index*2][j].elements.at(k).subID) = true;

					}

				}

			}

		for (i=0; i<subs; i++)
			{
				if (bits.at(i) == false)
				{
					matchIf++;

				}
			}

			cout<<endl<<"matched subsriptions for pub  "<< n+1 <<" are :"<<matchIf<<endl;

			matchIf=0;


		}



		gettimeofday(&tv2, NULL);
		diff = 1000000 *(tv2.tv_sec-tv1.tv_sec)+ tv2.tv_usec-tv1.tv_usec;
               cout<<endl<<"Time difference : "<<diff<<endl;


}//end of file





