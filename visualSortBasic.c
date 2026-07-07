#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



// ======================================================
//                  WINDOW CONFIGURATION
// ======================================================

#define WIDTH 900
#define HEIGHT 600

// Total number of bars to be visualized and sorted.
#define COUNT 50



// ======================================================
//                  GLOBAL DATA
// ======================================================

// Array containing the values represented by the bars.
int numbers[COUNT];



// ======================================================
//              SORT STATUS STRUCTURE
// ======================================================

// This structure stores the current state of the sorting
// algorithm so that the renderer knows:
//
// • Which two bars were compared/swapped.
// • Whether a swap happened.
// • Whether the entire array has been sorted.
//
typedef struct
{
	bool swapped;

	// Indices of the two bars currently being compared.
	int i, j;

	// Indicates that the array is completely sorted.
	bool sort_done;

} SortStatus;



// ======================================================
//                  DRAWING FUNCTIONS
// ======================================================

// Draws all the bars present in the array.
//
// Every value inside the array is converted into a bar.
// The larger the value, the taller the bar.
//
// Bar colours:
// White -> Normal bar
// Red   -> Recently swapped bars
// Green -> Entire array has been sorted
//
void draw_bars(SortStatus status)
{
	for (int i = 0; i < COUNT; i++)
	{
		int value = numbers[i];

		// Convert the array value into a drawable height.
		// We reserve only 75% of the window height for bars
		// and distribute it equally among COUNT values.
		int bar_height = value * HEIGHT * 0.75 / COUNT;

		Color color = WHITE;

		if (status.sort_done)
		{
			color = LIME;
		}
		else if (status.swapped && (i == status.i || i == status.j))
		{
			color = RED;
		}

		// DrawRectangle(x, y, width, height, colour)
		//
		// x:
		// Evenly spaces every bar across the window width.
		//
		// y:
		// Since rectangles are drawn from the top-left corner,
		// subtracting the bar height ensures every bar grows
		// upwards from the same baseline.
		//
		// width:
		// Width allocated to every bar with a small gap.
		//
		// height:
		// Height proportional to the array value.
		DrawRectangle(
			((float)i / COUNT) * WIDTH,
			HEIGHT * 0.75 - bar_height,
			WIDTH / COUNT - 2,
			bar_height,
			color
		);
	}
}



// ======================================================
//                  HELPER FUNCTIONS
// ======================================================

// Swaps two elements inside the array.
void swap(int i, int j)
{
	int temp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = temp;
}



// ======================================================
//              ARRAY INITIALIZATION
// ======================================================

// Creates a shuffled array.
//
// Step 1:
// Fill the array with values:
//
// 0,1,2,3,4....COUNT-1
//
// Step 2:
// Shuffle the array using the Fisher-Yates Shuffle
// algorithm.
//
// Time Complexity: O(n)
//
void init_random_numbers()
{
	// Create a sorted array.
	for (int i = 0; i < COUNT; i++)
	{
		numbers[i] = i;
	}

	// Fisher-Yates Shuffle.
	for (int i = COUNT - 1; i >= 0; i--)
	{
		// Random index between 0 and i.
		int j = rand() % (i + 1);

		// Swap the values.
		swap(i, j);
	}
}



// ======================================================
//              BUBBLE SORT (ONE STEP)
// ======================================================

// Executes ONE comparison of Bubble Sort.
//
// This function is called every frame instead of sorting
// the entire array at once so that the sorting process
// becomes visible to the user.
//
// Returns the current sorting status.
//
SortStatus sort_step()
{
	static SortStatus status = (SortStatus){false, 0, 1, false};

	// Current comparison index.
	static int i = 0;

	// Keeps track of whether any swap occurred during the
	// current sweep.
	static bool any_swap_during_sweep = false;

	status.i = i;
	status.j = i + 1;

	bool done = false;
	bool swapped = false;

	if (i < COUNT - 1)
	{
		int current_value = numbers[i];
		int next_value = numbers[i + 1];

		// Swap if elements are out of order.
		if (current_value > next_value)
		{
			swap(i, i + 1);

			status.swapped = true;
			any_swap_during_sweep = true;
		}
		else
		{
			status.swapped = false;
		}

		// Move to the next comparison.
		i++;
	}
	else
	{
		// Completed one sweep through the array.
		//
		// If no swaps occurred during the entire sweep,
		// Bubble Sort has finished.
		if (!any_swap_during_sweep)
		{
			status.sort_done = true;
		}

		// Start another sweep.
		i = 0;
		any_swap_during_sweep = false;
	}

	return status;
}



// ======================================================
//                      MAIN
// ======================================================

int main()
{
	// Generate a random unsorted array.
	init_random_numbers();

	// Create the application window.
	InitWindow(WIDTH, HEIGHT, "SORT VISUALISER");

	// Control animation speed.
	SetTargetFPS(COUNT * 3);

	SortStatus status;

	// ============================
	//        MAIN GAME LOOP
	// ============================
	while (!WindowShouldClose())
	{
		// Continue sorting until the array is completely sorted.
		if (status.sort_done != true)
		{
			status = sort_step();
		}

		BeginDrawing();

		// Clear the previous frame.
		ClearBackground(BLACK);

		// Draw the current state of the array.
		draw_bars(status);

		EndDrawing();
	}

	// Clean up resources.
	CloseWindow();
}