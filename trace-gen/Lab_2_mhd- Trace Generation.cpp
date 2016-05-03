//-----------------------------------------------------------------------
// Understanding the Impact of Memory System Design Tradeoffs on Machine Performance
//-----------------------------------------------------------------------
//  The source code of this lab is copied and adapted from the Figure 2.29, page 133-134 of the text book
//  Hennessey and Patterson, "Computer Architecture: A Quantitative Approach", 5th Ed., 2011 
//  Updated in 2/14/2012 by Gita Alaghband, Lan Vu
//-----------------------------------------------------------------------
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#define READ 0
#define WRITE 1
using namespace std;
ofstream out_data("Trace Generation Lb2 Code.dat");  // Open a file to save the result of the program "Traces"

void trace(int rw, int * addr);
void trace(double type, double * addr);
//In other to run this code in your own computer, adjust the ARRAY_MIN and ARRAY_MAX 
//to the size that matchs the cache configurations of your processor.
//Below setup is for the AMD Opteron 2427 processors on Hydra cluster
//Resize with suitable information of cache if you want to test on your computer
#define ARRAY_MIN (16*1024)		//1/4 smallest cache	(L1 size of AMD Opteron 2427 processor is 64 KB)
#define ARRAY_MAX (3*512*1024)	//1/4 largest cache		(L3 size of AMD Opteron 2427 processor is 6 MB)
int x[ARRAY_MAX];				//array going to stride through 


//-----------------------------------------------------------------------------
//routine to read time in seconds
//-----------------------------------------------------------------------------
#ifdef __linux__ //for Linux

#include <sys/time.h>
double get_seconds()
{
  static int sec = -1;
  trace(WRITE, &sec);
  struct timeval tv;
 // trace(READ, &tv);
	trace(WRITE, &tv);
  gettimeofday(&tv, NULL);
  if (sec < 0) 	
  
  sec = tv.tv_sec;
  trace(WRITE,&sec);
 return (double)((tv.tv_sec - sec) + 1.0e-6*tv.tv_usec);
 trace(WRITE,&H);
}

#else //for Windows

double get_seconds() { 
	__time64_t ltime;
	_time64(&ltime);
	
	return (double) ltime;
}
#endif 	

//-----------------------------------------------------------------------------
//generate text labels
//-----------------------------------------------------------------------------
int label ( int i) {
	if (i<1e3) 
	{
	
	trace(WRITE,&i);
	//trace(READ,&le3);
	cout << i << "B,"; 
	trace(READ,&i);
}
	else if (i<1e6)
	{
	  
	trace(READ,&i);
	//trace(READ,&le6);
	cout << i/1024 << "K,";
	trace(WRITE,&i);
}
	else if (i<1e9) 
	{
	
	trace(READ,&i);
	//trace(READ,&le9);
	cout << i/1048576 << "M,";
	trace(WRITE,&i);
}
	else 
	{
	
	cout << i/1073741824 << "G,";
}
trace(WRITE,&i);
	return 0;
	trace(WRITE, &i);
}


//-----------------------------------------------------------------------------
//Main functions
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	
	int register nextstep,i, index, stride;
	trace(WRITE,&nextstep);
	trace(WRITE,&i);
	trace(WRITE,&index);
	trace(WRITE,&stride);
	int csize;
	trace(WRITE,&csize);
	double steps , tsteps;
	trace(WRITE,&steps);
	trace(WRITE,&tsteps);
	double loadtime, lastsec, sec0, sec1, sec; //timing variables
	trace(WRITE,&loadtime);
	trace(WRITE,&lastsec);
	trace(WRITE,&sec0);
	trace(WRITE,&sec1);
	trace(WRITE,&sec);
	//Initialize output
	cout <<" ,";
	for (stride = 1 ; stride <= ARRAY_MAX/2; stride=stride*2)
	{
		trace(READ, &stride);
		trace(READ, &stride);
		trace(READ, &x[stride*2]);
		label (stride*sizeof(int));
		trace(WRITE, &stride);
	}
	trace(WRITE, &stride);
	cout <<endl;

	//Main loop for each configuration
	for (csize = ARRAY_MIN; csize < ARRAY_MAX; csize = csize*2)
	{
		trace(READ, &csize);
		trace(READ, &csize);
		trace(READ, &x[csize]);
		label (csize*sizeof(int)); // print cache size this loop
		for (stride = 1 ; stride <= csize/2; stride=stride*2) 
		{
			trace(READ, &stride);
			trace(READ, &stride);
			trace(READ, &csize);
			//Lay out path of memory references in array 
			for(index=0; index < csize; index=index + stride)
				
				trace(READ, &index);
				trace(READ, &index);
				//trace(READ, &czise);
				x[index] = index + stride;	//pointer to next
				trace(WRITE, &x[index]);
			x[index-stride] = 0;  //loop back to beginning
			trace(WRITE, &x[index-stride]);
			//Wait for timer to roll over
			lastsec = get_seconds();
			trace(READ, &lastsec);
			trace(WRITE, &lastsec);
			do 
			{
			
			trace(READ, &lastsec);
		sec0 = get_seconds(); 
		}	while (sec0 == lastsec);
		
			trace(WRITE, &sec0);
			//Walk through path in array for twenty seconds
			//This gives 5% accuracy with second resolution
			steps = 0.0;
			trace(WRITE, &steps);
			//Number of steps taken
			nextstep = 0;	//Start at beginning of path
			trace(WRITE, &nextstep);
			sec0 = get_seconds();	//Start timer
			trace(WRITE, &sec0);

			do {//Repeat until collect 20 seconds
					for (i=stride; i!=0; i--)
					{ //Keep samples same
						trace(READ, &i);
						trace(READ, &i);
						trace(READ, &stride);
						nextstep = 0;
						trace(WRITE, &nextstep);
					do 
					{
					
					trace(WRITE, &nextstep);
					nextstep = x[nextstep]; //Dependency
					trace(WRITE, &nextstep);
					}while (nextstep != 0);
					}
					trace(WRITE, &i);
				steps = steps + 1.0; //Count loop iterationsace
				trace(WRITE, &steps);
				sec1 = get_seconds(); //End timer
				trace(WRITE, &sec1);
			}
			while ((sec1 - sec0) < 20.0); //Collect 20 seconds
			trace(WRITE, &sec0);
			trace(WRITE, &sec1);
			sec = sec1 - sec0;
			trace(WRITE, &sec);
			//Repeat empty loop to loop subtract overhead
			tsteps = 0.0; //used to match no. while iterations
			trace(WRITE, &tsteps);
			sec0 = get_seconds() ; //start timer
			trace(WRITE, &sec0);
			do { //repeat until some no. iterations as above
				for (i = stride;i!=0;i=i-1) //keep samples some
				{
					trace(READ, &i);
					trace(READ, &i);
					trace(READ, &stride);
					index = 0;
					trace(WRITE, &index);
					do 
					{
					
					trace(WRITE, &index);
					index = index + stride;
					trace(READ, &index);
					}while (index < csize);
				}
				trace(WRITE, &i);
				tsteps = tsteps + 1.0;
				trace(WRITE, &tsteps);
				sec1 = get_seconds(); //- overheadace
				trace(WRITE, &sec1);
			} 
			while (tsteps<steps); //until = no. iterations
			trace(WRITE, &steps);
				trace(WRITE, &tsteps);
			sec = sec - (sec1 - sec0);
			trace(WRITE, &sec);
			loadtime = (sec*1e9)/(steps*csize); 
			trace(WRITE, &loadtime);
			
			cout << ((loadtime<0.1)? 0.1 : loadtime) << setiosflags(ios::fixed) << setprecision(1) << ",";//write out the results in .csv format for Excel 
			
		};//end of inner for loop
		cout << endl;

	};//end of outer for loop

	return 0;
}


void trace(double types, double * addrs)
{
//ofstream outfile;// declaration of file pointer named outfile
    //outfile.open("outputs", ios::out); // opens file named "outputs" for output
		//outfile << types << addrs << endl;
	//	outfile.close(); 
	cout << "  " <<types << " " << addrs << endl;
    out_data << types << "  " << addrs << endl; // // Write the result in the text file 


}

void trace(int type, int * addr)
{
//ofstream outfile;// declaration of file pointer named outfile
  //  outfile.open("outputs", ios::out); // opens file named "outputs" for output
	//	outfile << type << addr << endl;
	//	outfile.close();
	cout << "  " << type << " " <<addr << endl;
    out_data << type << "  " << addr << endl;  // Write the result in the text file 

}
