#include<iostream>
#include "util.h"
#include "datastruct.h"
#include <sys/time.h>
#include<omp.h>
#include<vector>

using namespace std;

int main (int argc, char *argv[])
{

  int subs =100000;//200000;			//number of subs submitted
  int ifNo =100000;//200000; 	    	//number of interfaces
  int pubs = 1;						//number of pubs published
  int attrs = 60;				//number of attributes in pubs schema
  int items = 10;					//number of constraints in subs
  double width = 0.5;   	//constraints width of subs
  //int cells = 8;					//number of cells divided among [0,1]
  int first = 8;					//number of indexed attributes for method 2
  double zipf = 0.01; 	//attributes selection distribution

  int nobkt = 1000;  //the number of buckets
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
	cout<<" subscription";
	for (int n=0; n<subs; n++)
	{

		subStr = Util::SubDis (items, attrs, width, zipf);
		cout<<endl<<"substr"<<subStr;

		sub = Util::ExtractSub (subStr);

		sub.client = n/(subs/ifNo);
		m_subList.push_back (sub);

        cout<<endl;


		#pragma omp
		{
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
    }


	/*
	----------------------------------------******************----------------------------------------
																						Event Matching
	----------------------------------------******************----------------------------------------
	*/

  cout<<endl; cout<<endl; cout<<endl;


	int i1,j1;
	int **bits = new int*[pubs];
	for(int i = 0; i < pubs; ++i) {
    	bits[i] = new int[subs+1];
}
	for(i1=0;i1<pubs;i1++)
	for(j1=0;j1<=subs;j1++)
	bits[i1][j1]=0;

    string pubStr;
    Pub pub;
    int matchIf=0;
    int n,i,j,k;
int t1,t2;
    struct timeval tv1, tv2;
	int nthreads, tid;



    gettimeofday(&tv1, NULL);


		for (n=0; n<pubs; n++)
		{


			pubStr = Util::PubDis (attrs);
			cout<<pubStr;

			pub = Util::ExtractPub (pubStr);

			#pragma omp
			{

			for (i=0; i<pub.pairList.size(); i++)
			{

				index = Util::Name2Index (pub.pairList.at (i).prop);

				lowVal = pub.pairList.at (i).value * 2000000 - 1;
				higVal = lowVal + 2;

				loc1 = (int) lowVal / step;
				loc2 = (int) higVal /step;




				#pragma omp sections nowait
				{

				#pragma omp section

				for (k=0; k<bucket_array[index*2+1][loc1].elements.size(); k++)
				{
					if (bucket_array[index*2+1][loc1].elements.at(k).value<lowVal)
					{

						#pragma omp critical(bits)
						bits[n][bucket_array[index*2+1][loc1].elements.at(k).subID] =1;


					}

				}



				#pragma omp section
				for (j=0; j<loc1; j++)
				{
					for (k=0; k<bucket_array[index*2+1][j].elements.size(); k++)

					{	//cout<<"in 2 st loop";
						#pragma omp critical(bits)
						bits[n][bucket_array[index*2+1][j].elements.at(k).subID] =1;

					}

				}

				#pragma omp section

				for (k=0; k<bucket_array[index*2][loc2].elements.size(); k++)
				{
					if (bucket_array[index*2][loc2].elements.at(k).value>higVal)
					{
						//cout<<"in 3 st loop";
						#pragma omp critical(bits)
						bits[n][bucket_array[index*2][loc2].elements.at(k).subID]=1; 						}

				}




				#pragma omp section
				for (j=loc2+1; j<nobkt; j++)
				{
					for (k=0; k<bucket_array[index*2][j].elements.size(); k++)
					{

						#pragma omp critical(bits)
						bits[n][bucket_array[index*2][j].elements.at(k).subID] = 1;

					}

				}


				}
			}
			}


		}







		#pragma omp barrier
		for(j=0;j<pubs;j++)
		{

		for (i=0; i<subs; i++)
			{

				if (bits[j][i] == 0)
				{
				#pragma omp critical (matchIf)
					matchIf++;

				}

			}
                  cout<<endl<<"Matched subscription for pub" <<j<< "are" <<matchIf<<endl;

			#pragma omp critical (matchIf)
			matchIf=0;

		}



		gettimeofday(&tv2, NULL);
		diff = 1000000 * (tv2.tv_sec-tv1.tv_sec)+ tv2.tv_usec-tv1.tv_usec;
               cout<<endl<<"Time difference : "<<diff<<endl;


}//end of file





