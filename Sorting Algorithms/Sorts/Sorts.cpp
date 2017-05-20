//   ___          _                                  _     _____ 
//  / _ \        (_)                                | |   |____ |
// / /_\ \___ ___ _  __ _ _ __  _ __ ___   ___ _ __ | |_      / /
// |  _  / __/ __| |/ _` | '_ \| '_ ` _ \ / _ \ '_ \| __|     \ \
// | | | \__ \__ \ | (_| | | | | | | | | |  __/ | | | |_  .___/ /
// \_| |_/___/___/_|\__, |_| |_|_| |_| |_|\___|_| |_|\__| \____/ 
//                   __/ |                                       
//                  |___/                                        

//Name   : Brandon Alvino
//Date   : October 10, 2015
//Class  : CSCI-242
//E-mail : null793@gmail.com

//Times to Sort 1.dat
//  Selection Sort: 17m 52s
//  Insertion Sort: 15ms
//  Shell Sort: 444ms
//  Bubble Sort: 19m 48s
//  Merge Sort: 620ms
//  Quick Sort: 335ms
//  Heap Sort: 125ms
//  Bin Sort: 143ms

//Times to Sort 2.dat
//  Selection Sort: 21m 26s
//  Insertion Sort: 8m 37s
//  Shell Sort: 1s 31ms
//  Bubble Sort: 48m 17s
//  Merge Sort: 260ms
//  Quick Sort: 405ms
//  Heap Sort: 34ms
//  Bin Sort: 566ms

//Times to Sort 3.dat
//  Selection Sort: 20m 45s
//  Insertion Sort: 4m 40s
//  Shell Sort: 305ms
//  Bubble Sort: 42m 
//  Merge Sort: 130ms
//  Quick Sort: 162ms
//  Heap Sort: 336ms
//  Bin Sort: 322ms

//Times to Sort 4.dat
//  Merge Sort: 4.224s
//  Quick Sort: 3.692s
//  Heap Sort: 9.083s
//  Bin Sort: 3.974s

//Why did I recieve these times for different sorting algorithms?
//  Shell Sort: Shell is fast not only because it's listed as O(n * log2n) but in it's feature to swap
//       data points that are far apart instead of close together like Bubble Sort does. 
//
//  Insertion Sort: Insertion sort is much faster than Bubble or Selection sort because it allows you to
//       almost short circtuit out of computation if you found where the current value gets inserted.
//       The insertion sort is incredibly fast on 1.dat because there are only 3 data points out of place.
//
//  Selection Sort: While Selection sort is incredibly inneficient, it is still better than Bubble sort,
//       because it waits till the end of the pass to swap values instead of swapping mid pass.
//
//  Bubble Sort: On non-sorted data this is one of the worst algorithms because it swaps values while it's 
//       stepping through the array each time, so the code that is inside the nested for loops get executed n^2 times.
//       This however is one of the fastest sorting algorithms for sorting already sorted data.
//
//  Quick sort: This sorting algorithm is incredibly fast because it will sort the middle element in each partition and after
//       its partition we also will know that there are 2 sorted lists on each side of the sorted index. The Quicksort is often
//       thought of as unstable for working with massive quanitites of data (more than we're working with) because it can cause
//       stack overflow. Also, an important part of the speed of the quicksort is dependant upon the pivot point used for partitioning.
//       if you have a list that goes n^k, n^(k + 1), n^(k + 2), ...., n^(k + a), 1, n^(k + (a + 1)), n^(k + (a + 2)), ...., n^(k + (a + b))
//       where n > 1 and k >= 1, then the merge sort will do terrible with my computation of the partition point being the mid point.
//       This algorithm can be incredibly fast, O(log2n), or incredibly slow with a bad pivot, n^2.
//
//  Merge sort: This sorting algorithm matches it's speed with it's reliability. Because it divides the list up into equal lists of 1 
//       and then will merge them together it is incredibly reliable, with having a speed of O(log2n) each time it is ran. The only downfall
//       to this algorithm is that it uses recursion, much like quicksort, and if the data is to become to big there could be problems
//       with stack overflow.
//
//  Heap sort: While not incredibly fast the heapsort is a very good sorting algorithm because it's fast for an "in place" sorting algorithm.
//       Aditionally, there aren't extra arrays or storage spaces needed for the Heap sort, so it does fairly well on large sets of data. 
//       The heap sort is kind of like the slower but more efficient cousin of the merge sort, because it's consisten like it, but doesn't need
//       to use a secondary array to merge into.
//
//  Bin sort: The bin sort or radix sort is probably our best algorithm learned to date. It's faster than the Merge Sort and Heap sort and is also
//       very consistent with it's sorting time, which is where it beats the Quicksort. The downside to the bin sort is that it uses two arrays, which is
//       still much faster than creating new memory allocations each time it adds an item to a bin. The bin sort is also very easy to understand in that each
//       pass it simply puts that pass's index of the number into a bin and takes it out. The bin sort is also very easy to modify to include words as well as numbers.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <dos.h>
#include <time.h>
#include <string>
#include <sys/timeb.h>

#pragma warning (disable : 4996)
using namespace std;

//function declarations
bool isSorted(int*, int);
void SelectionSort(int*, int);
void InsertionSort(int*, int);
void BubbleSort(int*, int);
void ShellSort(int*, int);

void MergeSort(int, int, int*, int*);
void QuickSort(int, int, int*);

void HeapSort(int*, int);
void BinSort(int*, int);

struct Node
{
	int data;
	Node *next = NULL;
};

struct BinNode
{
	Node *front = NULL;
	Node *back = NULL;
};

//changed from void main to int for error returns.
int main()
{
	int* MyArray;
	int* temp;
	char filename[30];
	int size;

	cout << "Enter File name of file to sort ->";
	cin >> filename;

	FILE* in;
	in = fopen(filename, "rb");

	if (in == NULL)
	{
		cout << "Cannot open file " << filename << endl;
		system("pause");
		return 1;
	}

	fread(&size, sizeof(size), 1, in);
	MyArray = new int[size];
	temp = new int[size];
	int y;

	for (int x = 1; x < size; x++)
	{
		fread(&y, sizeof(y + 1), 1, in);
		MyArray[x] = y;
		temp[x] = y;
	}

	fclose(in);

	char choice;
	cout << "1) Selection Sort" << endl;
	cout << "2) Insertion Sort" << endl;
	cout << "3) Shell Sort" << endl;
	cout << "4) Bubble Sort" << endl;
	cout << "5) Merge Sort" << endl;
	cout << "6) Quicksort" << endl;
	cout << "7) Heap Sort" << endl;
	cout << "8) Bin Sort" << endl;
	cout << "Input sort choice -> ";
	cin >> choice;

	struct _timeb timebuffer;
	char *timeline;
	clock_t a = clock(); //used for counting seconds of execution

	_ftime(&timebuffer);
	timeline = ctime(&(timebuffer.time));

	printf("\nThe time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

	switch (choice)
	{
	case '1': SelectionSort(MyArray, size);
		break;

	case '2': InsertionSort(MyArray, size);
		break;

	case '3': ShellSort(MyArray, size);
		break;

	case '4': BubbleSort(MyArray, size);
		break;

	case '5': MergeSort(1, (size - 1), temp, MyArray);
		break;

	case '6': QuickSort(1, (size - 1), MyArray);
		break;

	case '7': HeapSort(MyArray, size);
		break;

	case '8': BinSort(MyArray, size);
		break;
	default: return 1; //error reporting on invalid input
	}

	delete temp;
	_ftime(&timebuffer);
	timeline = ctime(&(timebuffer.time));
	clock_t b = clock(); //stop the clock
	double se = double(b - a) / CLOCKS_PER_SEC; //computation to decide time, based on comps clock speed

	printf("The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20]);

	string suf = "seconds"; //used in output
							//if there are more than 60 seconds
	if (se >= 60.0)
	{
		se /= 60.0; //convert to minutes
		suf = "minutes"; //rename the unit of time
	}

	//if there was less than a second
	else if (se < 1.0)
	{
		se = timebuffer.millitm; //use the timebuffer's millisecond feature
		suf = "milliseconds"; //rename the unit of time
	}

	//uses a very rigged nested ternary statement for appropriate output
	cout << "\nThe Algorithm took " << se << " " << suf << " to sort using the " << ((choice == '1') ? "Selection" : ((choice == '2') ? "Insertion" : ((choice == '3') ? "Shell" :
		((choice == '4') ? "Bubble" : ((choice == '5') ? "Merge" : ((choice == '6') ? "Quick" : ((choice == '7') ? "Heap" : ((choice == '8') ? "Bin" : "")))))))) << " Sort." << endl;
	cout << "Sorted: " << (isSorted(MyArray, size) ? "True" : "False") << "\n" << endl; //uses defined isSorted() function to test functionality

	int start, finish;
	cout << "Enter the index of where you want to start printing ->";
	cin >> start;
	cout << "Enter the index of where you want to stop printing ->";
	cin >> finish;

	//changed to work with [0] being used as temp
	for (int z = (start + 1); z <= (finish + 1); z++)
	{
		cout << MyArray[z] << "  ";
	}

	//on my system I need to pause after main or else the program will exit
	system("pause");
	return 0;
}

//simple boolean function for determining if the algorithm worked
bool isSorted(int TheArray[], int n)
{
	for (int i = 2; i < n; i++)
	{
		if (TheArray[i - 1] > TheArray[i])
			return false;
	}

	return true;
}

//basic Selection sort
void SelectionSort(int TheArray[], int size)
{
	for (int x = size - 2; x > 1; x--)
	{
		int best = 1;
		for (int y = 1; y <= x; y++)
		{
			if (TheArray[y] > TheArray[best])
			{
				best = y;
			}
		}

		//uses [0] as temp
		TheArray[0] = TheArray[best];
		TheArray[best] = TheArray[x];
		TheArray[x] = TheArray[0];
	}
}

//Insertion sort using sliding feature
void InsertionSort(int TheArray[], int size)
{
	for (int x = 2; x < size; x++)
	{
		int r = x - 1;
		TheArray[0] = TheArray[x];

		while (TheArray[0] < TheArray[r])
		{
			TheArray[r + 1] = TheArray[r--];
		}

		TheArray[r + 1] = TheArray[0];
	}
}

//Shellsort using sliding feature
void ShellSort(int TheArray[], int size)
{
	int ns = sqrt(size);

	while (ns >= 1)
	{
		for (int i = ns + 1; i <= size - 1; i++)
		{
			TheArray[0] = TheArray[i];
			int r = i - ns;

			while (r >= 0 && TheArray[0] < TheArray[r])
			{
				TheArray[r + ns] = TheArray[r];
				r -= ns;
			}

			TheArray[r + ns] = TheArray[0];
		}

		if (ns == 1)
			break;

		ns /= 3;

		if (ns == 0)
			ns = 1;
	}
}

//standard Bubble sort
void BubbleSort(int TheArray[], int size)
{
	for (int i = size - 1; i > 1; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (TheArray[j] > TheArray[j + 1])
			{
				//uses [0] as temp
				TheArray[0] = TheArray[j];
				TheArray[j] = TheArray[j + 1];
				TheArray[j + 1] = TheArray[0];
			}
		}
	}
}

// Original Mergesort
void MergeSort(int low, int high, int* source, int* destination)
{
	// Base-case
	if (low == high)
		return;

	int mid = (low + high) / 2;
	int start_1 = low, end_1 = mid, start_2 = (mid + 1), end_2 = high, dest = start_1;

	// Recursively calls up left and right sides
	MergeSort(low, mid, destination, source);
	MergeSort((mid + 1), high, destination, source);

	// Merge Segment of function
	while (start_1 <= end_1 && start_2 <= end_2)
	{
		if (source[start_1] > source[start_2])
			destination[dest++] = source[start_2++];
		else
			destination[dest++] = source[start_1++];
	}

	// Copies over the rest of the second list
	if (start_1 > end_1)
	{
		for (; start_2 <= end_2; start_2++)
			destination[dest++] = source[start_2];
	}

	// Copies over the rest of the first list
	else
	{
		for (; start_1 <= end_1; start_1++)
			destination[dest++] = source[start_1];
	}
}

// Method for partitioning used by Quicksort
int partition(int left, int right, int* source)
{
	int pivot = source[(left + right) / 2];

	while (left <= right)
	{
		while (source[left] < pivot)
			left++;

		while (source[right] > pivot)
			right--;

		if (left <= right)
		{
			source[0] = source[left];
			source[left++] = source[right];
			source[right--] = source[0];
		}
	}

	return left;
}

// Method responsible for recursively calling Quicksort
void QuickSort(int low, int high, int* source)
{
	int point = partition(low, high, source);

	if (low < point - 1)
		QuickSort(low, point - 1, source);

	if (point < high)
		QuickSort(point, high, source);
}

void HeapSort(int *source, int size)
{
	// Creates variables once
	int child, parent, best, left, right;

	// Puts source into a heap
	for (int i = 1; i < size + 1; i++)
	{
		child = i;
		parent = child / 2;

		// Walking up each of the children as far as it will go
		while (parent != 0 && source[child] > source[parent])
		{
			source[0] = source[child];
			source[child] = source[parent];
			source[parent] = source[0];

			// If the child walks up then it has a new parent
			child = parent;
			parent = child / 2;
		}
	}

	// Sorts the list one by one by putting parent to back of list and re-heaping
	for (int i = size - 1; i > 1; i--)
	{
		parent = 1;

		// Swaps parent with last available index
		source[0] = source[parent];
		source[parent] = source[i];
		source[i] = source[0];

		left = parent * 2;
		right = left + 1;
		best = (left > i - 1 || left == i - 1 || source[left] > source[right]) ? left : right;

		// Re-heaps the list
		while (best < i && source[best] > source[parent])
		{
			source[0] = source[parent];
			source[parent] = source[best];
			source[best] = source[0];

			parent = best;

			left = parent * 2;
			right = left + 1;

			// Heapsort goes much quicker without an aditional method for this
			best = (left > i - 1 || left == i - 1 || source[left] > source[right]) ? left : right;
		}
	}

}


// Calculates the biggest integer in the list and returns its length
int biggest(int* source, int size)
{
	int biggest = -1;
	for (int i = 1; i < size + 1; i++)
	{
		// compares all elements to find largest in the list
		if (source[i] > biggest)
			biggest = source[i];
	}

	// Turns into a string so can return the length function
	// Already used the string module in main method, so why not?
	return to_string(biggest).length();
}

// Puts information into bins and takes them out w times.
void BinSort(int* source, int size)
{
	int pos = 1; // Where to read from integer
	int index = 1; // Index to be put back into in original array
	int storageindex = 1; // Where temp info is being stored
	int location; // So recalculation doesn't need to be made several times for Bin location

	Node *storage = new Node[size]; // Where to store the references
	BinNode *bins = new BinNode[10]; // Where to store the start and back of each list
									 
	for (int i = 0; i < biggest(source, size); i++) // From 0 to the width of the largest peice of data
	{
		// Puts values into the bin
		for (int i = 1; i < size; i++)
		{
			location = source[i] / pos % 10; // Which bin does this go into

											 // Declare back to null later on; can be front alternatively if rewritten
			if (bins[location].back == NULL)
			{
				bins[location].front = &(storage[storageindex]);
				bins[location].back = &(storage[storageindex++]);
			}

			// Links instead of creating new lists
			else
			{
				bins[location].back->next = &(storage[storageindex++]);
				bins[location].back = bins[location].back->next;
			}

			// Puts in data
			bins[location].back->data = source[i];
			bins[location].back->next = NULL;

		}

		// Taking out of bins
		for (int loc = 0; loc < 10; loc++)
		{
			while (bins[loc].front != NULL) // while current node exists
			{
				source[index++] = bins[loc].front->data; // Puts back into original array
				bins[loc].front = bins[loc].front->next; // Advances front
			}

			bins[loc].back = NULL; // Can determine an empty list when putting back into bins
		}

		index = 1; // Resets the index
		pos *= 10; // So not always comparing same position
		storageindex = 1; // Resets storageindex
	}

	delete[] storage; // Frees up memory
}