#include<stdlib.h>
#include<iostream>
#include<fstream>

using namespace std;
#define Array_size 100

#define READ 0
#define WRITE 1
ofstream out_data("Trace Generation of Bubble Sort.dat");

void trace(int type, int * addr);

int main(int argc, char** argv)
{
	
//ofstream out_data("Ran.dat");

int i, array[Array_size];
 
trace(WRITE, &i);  // initialize i
trace(WRITE, &array[Array_size]);  // initialize i


for(i=0;i<Array_size;i++)
{
	trace(READ, &i);  // To check i value for loop
	trace(READ, &i); //Read of i value for array indexing
	trace(READ, &array[i]); //read of arr[i] for write
	
    array[i] = rand()%Array_size; //  Generate Random Numbers and store them in the array
    //	printf("%d \n", arr[i]);
  // 	printf ("%X   %d\n",(void *)(& array[i]), array[i]); 
    	
    trace(WRITE, &array[i]);  // i=i+1
}
 
	trace(READ, &i); // read for last value i that breaks out of the loop

	trace( WRITE, &i); //initialize i

int sign, j,temp;
	trace( WRITE, &sign); //initialize sign
	trace( WRITE, &temp); //initialize temp
	trace( WRITE, &j); //initialize j

for(i = 1; (i <= Array_size) && sign; i++)
     {
   		trace(READ, &i);  // To check i value for loop
		trace(READ, &i); //Read of i value for array indexing
          sign = 0; temp=0;
          	trace( WRITE, &sign); //initialize sign again 
			trace( WRITE, &temp); //initialize temp again
			trace(WRITE, &j); //To initialize j value
          for (j=0; j < (Array_size -1); j++)
         {
             trace(READ, &j); //To check j value for loop
			 trace(READ, &array[j+1]); //read of arr[J+1] for write
			 	trace(READ, &j); // read for j index again
			 trace(READ, &array[j]); //read of arr[J] for write
	
               if (array[j+1] < array[j])      // Check If array[j+1] value less than array[j] value 
              { 
                    temp = array[j];             // swap values
                   	trace(WRITE, &temp); //j read for j index
                   	
               		trace(READ, &j); //j read for j index
               		trace(READ, &array[j+1]); //read of arr[J+1] for write
		    	 	trace(READ, &j); // read for j index again
		            trace(READ, &array[j]); //read of arr[J] for write
	
                    array[j] = array[j+1];
                    trace(WRITE, &array[j]); //Write the value of array[j+1] to array[j]
					trace(READ, &temp);
					trace(READ, &j);
                    array[j+1] = temp;
               		trace(READ, &j);
		    		trace(WRITE, &array[j + 1]);

                    sign = 1;               // It means that the swapping done
               }
               	trace(WRITE, &j); //  j= j+1
          }
           	trace(WRITE, &i); //  i= i+1
			trace(READ, &j); // Read  last value of j that breaks out of loop

           	trace(WRITE, &i); //  i= i+1
      }
      	trace(READ, &i); // Read  last value of j that breaks out of loop

 for(i=0;i<Array_size;i++)
{
    // Print the array elements after sortingin
   //	printf("%d \n",  array[i]);
  //	printf ("%X   %d\n",(void *)(& array[i]), array[i]); 
 }     
   getchar();
 }

void trace(int type, int * addr)
{
//ofstream outfile;// declaration of file pointer named outfile
  //  outfile.open("outputs", ios::out); // opens file named "outputs" for output
	//	outfile << type << addr << endl;
	//	outfile.close();
	//	fprintf( filepointer," %d  --   %X \n ", type ,addr);

	cout << type << "  " << addr << endl;
	out_data << type << "  " << addr << endl;
}
