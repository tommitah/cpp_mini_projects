/*
 * SOURCE: https://www.geeksforgeeks.org/the-slowest-sorting-algorithms/
 * MIIKKA: Valitsin "hitaan" sorttialgoritmin netistä, koska ei ollut
 * käsillä mitään muuta optimoitavaa. Shakkiprojekti kadonnut eetteriin,
 * eikä siinä olisi hirveästi optimoitavaa ollut, kun ei algoritmit 
 * hirveen monimutkaisia/toimivia olleet.
 * */

/*
 * PERFORMANCE: 
 *  Stage 1:
 *     26.006s with no flags. Compiles instantly.
 *     O1-flag: 19.8713s. Compiles instantly.
 *     O2-flag: 13.3975s. Compiles instantly.
 *     O3-flag: 12.5522.  Compiles instantly.
 *  Stage 2:
 *     33.2567s with -pg -O3.
 *     Spends 98.14% of the time in the sort function(surprisingly /s).
 *     stoogesort() is called 2 097 110 times.
 *     
 *     60.8453s with -pg -fprofile-arcs -ftest-coverage -O3, attempted
 *     to get line-by-line profiling with gprof -l --> wrong output.
 *
 *     79.4807s with -pg -g (for line_by_line). output with
 *     gprof -b stooge gmon.out > profout_lines.txt
 *     
 *     Educated guess: 
 *          line 82 rand() and modulus operation take time, not part 
 *          of the algorithm per-say.
 *
 *          line 26 (swap operation, std slow huehue) take time.
 *          line 30 & 31 have conditional operations, and arithmetic.
 *  Stage 3:
 *     
 * */

// C++ program for the stooge sort
#include <iostream>
#include <ctime>
using namespace std;

#define SIZE_a 5000

// Function to implement stooge sort
void stoogesort(int arr[], int l, int h)
{
	// Base Case
	if (l >= h)
		return;

	// If first element is smaller than
	// last element, swap them
	if (arr[l] > arr[h])
		swap(arr[l], arr[h]);

	// If there are more than 2 elements
	// in the array
	if (h - l + 1 > 2) {
		int t = (h - l + 1) / 3;

		// Recursively sort the first
		// 2/3 elements
		stoogesort(arr, l, h - t);

		// Recursively sort the last
		// 2/3 elements
		stoogesort(arr, l + t, h);

		// Recursively sort the first
		// 2/3 elements again
		stoogesort(arr, l, h - t);
	}
}

inline void stoogesort_opt(int arr[], int l, int h)
{
	// Base Case
	if (l >= h)
		return;

	// If first element is smaller than
	// last element, swap them
	if (arr[l] > arr[h])
		swap(arr[l], arr[h]);

	// If there are more than 2 elements
	// in the array
	if (h - l + 1 > 2) {
		int t = (h - l + 1) / 3;

		// Recursively sort the first
		// 2/3 elements
		stoogesort_opt(arr, l, h - t);

		// Recursively sort the last
		// 2/3 elements
		stoogesort_opt(arr, l + t, h);

		// Recursively sort the first
		// 2/3 elements again
		stoogesort_opt(arr, l, h - t);
	}
}


// Driver Code
int main()
{
  /*--------- Tommis additions ---------*/
	int arr[SIZE_a] = {};

  clock_t start = clock();

  /* populate the array with 5000 random values between 1-100 */
  for(int i = 0; i < SIZE_a; i++) {
    arr[i] = rand() % 100 + 1;
  }

	int N = sizeof(arr) / sizeof(arr[0]);

	// Function Call
	stoogesort_opt(arr, 0, N - 1);

  clock_t end = clock();
  clock_t duration = end - start;

  cout << "execution time : " << (float)duration / CLOCKS_PER_SEC << " seconds" << endl;

	return 0;
}
