/*
Veerpartap Singh
Project 1 CSCI 36200
09-15-17
*/
#include <iostream> //always included
#include <ctime> //convert time to string
#include <cstdlib> //random number generator,sorting,converting

using namespace std;

clock_t startTime, endTime; //start time and end time
#define MAX_COUNT 10000 //numbers 1-10,000
int num[MAX_COUNT]; //array values
int temp[MAX_COUNT]; //for merge sort
int total_count; //total interger count
int total_steps;

void initializeTotalSteps()
{
	total_steps = 0;
}
void printTotalSTeps()
{
	cout << "Total Steps = " << total_steps << endl;
	total_steps = 0;
}
void increaseTotalSteps(int num = 1)
{
	total_steps += num;
}
void copyValue(int* dest, int *src, int count)
{
	memcpy(dest, src, sizeof(int) * count);
}
void generateNum(int count) //generate array
{
    srand(time(0));
    int i = 0;
    while (i < count)
    {
        num[i] = (rand() + time(0)) % MAX_COUNT;
        i++;
    }

}


void swap(int i, int j) //change values of index i, j
{
	int p = num[i];
    num[i]= num[j];
    num[j]= p;
	increaseTotalSteps(0);
}


void insertionSort(int low, int high) //insertion sorting function for sorting the numbers less than 20
{
      int i, j, tmp;
      for (i = low + 1; i <= high; i++) {
			j = i;
			increaseTotalSteps(1);
	
           while (j > 0 && num[j - 1] > num[j]) {
                  tmp = num[j];
                  num[j] = num[j - 1];
                  num[j - 1] = tmp;
                  j--;
				  //increaseTotalSteps(); //Add this if you want to count each step of work to count in total step
            }
      }
}

void quickSort(int low, int high) //quick sort function based on the middle pivot
{
    int i = low;
    int j = high;
    int pivot = num[(i + j) / 2];
	increaseTotalSteps();

    while (i <= j)
    {
		
		while (num[i] < pivot)
		{
			i++;
			increaseTotalSteps(1);
		}
		while (num[j] > pivot)
		{
			j--;
			increaseTotalSteps(1);
		}
        if (i <= j)
        {
            swap(i, j);
            i++;
            j--;
			increaseTotalSteps(3);
        }
    }
	if (j > low)
	{
		quickSort(low, j);
		increaseTotalSteps();
	}
	if (i < high)
	{
		quickSort(i, high);
		increaseTotalSteps();
	}
}



void displayArray(int low, int high ) //display array numbers
{
    cout<<"{";
    for( int i=low; i<= high; i++ )
        cout<<num[i]<<" ";
    cout<<"}\n";
}


void merge(int left_low, int left_high, int right_low, int right_high)
{
	int length = right_high - left_low + 1;

	int left = left_low;
	int right = right_low;
	//increaseTotalSteps();
	for (int i = 0; i < length; ++i) {
		increaseTotalSteps();
		if (left > left_high)
		{
			temp[i] = num[right++];
			//increaseTotalSteps();
		}
		else if (right > right_high)
		{
			temp[i] = num[left++];
			//increaseTotalSteps();
		}
		else if (num[left] <= num[right])
		{
			temp[i] = num[left++];
			//increaseTotalSteps();
		}
		else
		{
			temp[i] = num[right++];
			//increaseTotalSteps();
		}
		
	}

	for (int i = 0; i < length; ++i)
	{
		num[left_low++] = temp[i];
		//increaseTotalSteps();
	}
}


void merge_sort(int low, int high) {
	if (low >= high)                  //Base case: 1 value to sort->sorted
	{
		//increaseTotalSteps();
		return;
	}
	else {
		int mid = (low + high) / 2;       //Approximate midpoint*
		//increaseTotalSteps();
		merge_sort(low, mid);        //Sort low to mid part of array
		merge_sort(mid + 1, high);     //Sort mid+1 to high part of array
		merge(low, mid, mid + 1, high); //Merge sorted subparts of array
	}
}




void p1()
{
	//already implemented
	//insertionSort : insertion sort function
	//mergeSort : merge sort fucntion
	//quickSort : quick sort function
}

void p2(int count)
{
	generateNum(count);
	cout << "Generated "<<count<<" interges : " << endl;
	displayArray(0, count - 1);
	copyValue(temp, num, count);//saves a to b so you use origanl array

	insertionSort(0, count - 1);
	cout << "Insertion Sort Result : " << endl;
	displayArray(0, count - 1);

	copyValue(num, temp, count);
	merge_sort(0, count - 1);
	cout << "Merge Sort Result : " << endl;
	displayArray(0, count - 1);

	copyValue(num, temp, count);
	quickSort(0, count - 1);
	cout << "Quick Sort Result : " << endl;
	displayArray(0, count - 1);
}
void p2()
{
	p2(100);
	cout << endl << endl;
	p2(1000);
	cout << endl << endl;
}

void p34(int count)
{
	generateNum(count);


	cout << count<<" integers are generated "<< endl<<endl;
	copyValue(temp, num, count);

	initializeTotalSteps();
	startTime = clock();
	insertionSort(0, count - 1);
	endTime = clock();
	cout << "Insertion Sort :" << endl;
	printTotalSTeps();
	cout << "Elapsed Time:  " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	initializeTotalSteps();
	startTime = clock();
	merge_sort(0, count - 1);
	endTime = clock();
	cout << "Merge Sort :" << endl;
	printTotalSTeps();
	cout << "Elapsed Time:  " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl << endl;

	initializeTotalSteps();
	startTime = clock();
	quickSort(0, count - 1);
	endTime = clock();
	cout << "Quick Sort :" << endl;
	printTotalSTeps();
	cout << "Elapsed Time:  " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void p34()
{
	
	p34(100);
	p34(1000);
	p34(5000);
	p34(10000);
}


int main()
{
	p2();
	p34();

	/*int k;
	cin >> k;*/ 
    
    return 0;
}
