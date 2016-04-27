#include <stdio.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

#define ARR_SIZE 100

void trace(int rw, int *addr);
int main(int argc, char**argv)
{
	srand(72341);
	int arr[ARR_SIZE];
	int i;

	trace(WRITE, &i); //account for initialization of i

	for (i = 0; i<ARR_SIZE; i++)
	{
		trace(READ, &i); //loop read of i for conditional check

		trace(READ, &i); //read of i for array indexing
		trace(READ, &arr[i]); //read of arr[i] for write
		arr[i] = rand();

		trace(WRITE, &i); //loop increment of i
	}
	trace(READ, &i); //account for last read of i that breaks out of the loop

	trace(WRITE, &i); //account for initialization of i

	for (i = 0; i<ARR_SIZE; i++)
	{
		int already_sorted = 1;
		trace(WRITE, &already_sorted); //unconditional write of already_sorted

		int j;
		trace(WRITE, &j); //account for initialization of j
		for (j = 0; j<ARR_SIZE - 1; j++)
		{
			trace(READ, &j); //loop read of j for conditional check

			trace(READ, &j); //j read for j+1 index calculation
			trace(READ, &arr[j + 1]); //arr[j+1] read for comparison

			trace(READ, &j); //j read for j index
			trace(READ, &arr[j]); //arr[j] read for comparison
			if (arr[j] > arr[j + 1])
			{

				already_sorted = 0;
				trace(WRITE, &already_sorted);

				trace(READ, &j); //read j for index
				trace(READ, &arr[j]); //read arr[j] for hold
				int hold = arr[j];
				trace(WRITE, &hold); //write for hold update

				trace(READ, &j);
				trace(READ, &arr[j + 1]);
				arr[j] = arr[j + 1];
				trace(READ, &j);
				trace(WRITE, &arr[j]);

				trace(READ, &hold);
				arr[j + 1] = hold;
				trace(READ, &j);
				trace(WRITE, &arr[j + 1]);

			}


			trace(WRITE, &j); //loop increment of j
		}
		trace(READ, &j); //account for last read of j that breaks out of loop

		trace(READ, &already_sorted);
		if (already_sorted)
		{
			break;
		}

		trace(WRITE, &i); //loop increment of i
	}
	//trace(READ, &i); --no need to account for last read of i that breaks out of the loop, as already_sorted will have already done so

	//for(int i = 0; i<ARR_SIZE; i++)
	//{
	//	printf("%d\n", arr[i]);
	//}
}


void trace(int type, int * addr)
{

	printf("%d %X\n", type, (unsigned int)addr);

}