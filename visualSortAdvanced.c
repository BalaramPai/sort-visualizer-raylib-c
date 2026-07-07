#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <time.h>

// ======================================================
//                  WINDOW CONFIGURATION
// ======================================================

// Initial window size.
// The window is resizable, so these are only the starting
// dimensions.
#define WIDTH 900
#define HEIGHT 600

// Height reserved for the top control panel.
#define TOP_PANEL_HEIGHT 90

// Number of bars.
#define COUNT 50


// ======================================================
//                  GUI LAYOUT
// ======================================================

// Control positions.
#define CONTROL_Y      20

#define DROPDOWN_X     20
#define START_X        250
#define RESET_X        360

#define DROPDOWN_W     200
#define BUTTON_W       90
#define BUTTON_H       35


// ======================================================
//                  GLOBAL DATA
// ======================================================

// Array that stores all bar values.
int numbers[COUNT];


// ======================================================
//              SORT STATUS STRUCTURE
// ======================================================

// Stores information about the current state of sorting.
typedef struct
{
    bool swapped;

    // Indices currently being compared/swapped.
    int i;
    int j;

    // True once the algorithm has completed.
    bool sort_done;

} SortStatus;


// ======================================================
//              BUBBLE SORT STATE
// ======================================================

// Bubble sort keeps its own state so that one comparison
// happens every frame instead of sorting instantly.

SortStatus bubbleStatus = { false, 0, 1, false };

int bubbleCurrentIndex = 0;

bool bubbleAnySwapDuringSweep = false;


// ======================================================
//            SELECTION SORT STATE
// ======================================================

// Selection sort also keeps its own persistent state.

SortStatus selectionStatus = { false, 0, 1, false };

int selectionOuterIndex = 0;

int selectionInnerIndex = 1;

int selectionMinimumIndex = 0;


// ======================================================
//              APPLICATION STATE
// ======================================================

// Controls whether sorting is currently running.
bool isSorting = false;

// Controls pause/resume.
bool isPaused = false;


// ======================================================
//                  DRAWING FUNCTIONS
// ======================================================

void draw_bars(SortStatus status)
{
    // Current window size.
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Area available for drawing bars.
    int drawableHeight = screenHeight - TOP_PANEL_HEIGHT - 10;

    // Common baseline for every bar.
    int baseline = screenHeight - 10;

    for (int i = 0; i < COUNT; i++)
    {
        int value = numbers[i];

        // Scale the array value into pixels.
        int bar_height = value * drawableHeight / COUNT;

        Color color = WHITE;

        // Entire array sorted.
        if (status.sort_done)
        {
            color = LIME;
        }
        // Highlight bars involved in the current swap.
        else if (status.swapped &&
                (i == status.i || i == status.j))
        {
            color = RED;
        }

        DrawRectangle(
            ((float)i / COUNT) * screenWidth,
            baseline - bar_height,
            screenWidth / COUNT - 2,
            bar_height,
            color
        );
    }
}


// ======================================================
//                  HELPER FUNCTIONS
// ======================================================

// Swap two array elements.
void swap(int i, int j)
{
    int temp = numbers[i];

    numbers[i] = numbers[j];

    numbers[j] = temp;
}


// ======================================================
//              ARRAY INITIALIZATION
// ======================================================

// Creates a shuffled array using Fisher-Yates Shuffle.
void init_random_numbers()
{
    // Create sorted array.
    for (int i = 0; i < COUNT; i++)
    {
        numbers[i] = i;
    }

    // Shuffle.
    for (int i = COUNT - 1; i >= 0; i--)
    {
        int j = rand() % (i + 1);

        swap(i, j);
    }
}


// ======================================================
//          RESET BUBBLE SORT STATE
// ======================================================

void reset_bubble_sort()
{
    bubbleStatus = (SortStatus){ false, 0, 1, false };

    bubbleCurrentIndex = 0;

    bubbleAnySwapDuringSweep = false;
}


// ======================================================
//        RESET SELECTION SORT STATE
// ======================================================

void reset_selection_sort()
{
    selectionStatus = (SortStatus){ false, 0, 1, false };

    selectionOuterIndex = 0;

    selectionInnerIndex = 1;

    selectionMinimumIndex = 0;
}

// ======================================================
//              BUBBLE SORT (ONE STEP)
// ======================================================
//
// Executes ONE comparison every frame.
//

SortStatus bubble_sort_step()
{
    bubbleStatus.i = bubbleCurrentIndex;
    bubbleStatus.j = bubbleCurrentIndex + 1;

    if (bubbleCurrentIndex < COUNT - 1)
    {
        int current_value = numbers[bubbleCurrentIndex];
        int next_value = numbers[bubbleCurrentIndex + 1];

        if (current_value > next_value)
        {
            swap(bubbleCurrentIndex, bubbleCurrentIndex + 1);

            bubbleStatus.swapped = true;

            bubbleAnySwapDuringSweep = true;
        }
        else
        {
            bubbleStatus.swapped = false;
        }

        bubbleCurrentIndex++;
    }
    else
    {
        // Finished one complete sweep.

        if (!bubbleAnySwapDuringSweep)
        {
            bubbleStatus.sort_done = true;
        }

        bubbleCurrentIndex = 0;

        bubbleAnySwapDuringSweep = false;
    }

    return bubbleStatus;
}


// ======================================================
//           SELECTION SORT (ONE STEP)
// ======================================================
//
// Executes ONE comparison every frame.
//

SortStatus selection_sort_step()
{
    selectionStatus.swapped = false;

    // Finished sorting.
    if (selectionOuterIndex >= COUNT - 1)
    {
        selectionStatus.sort_done = true;

        return selectionStatus;
    }

    // Searching for minimum element.
    if (selectionInnerIndex < COUNT)
    {
        // Highlight:
        //
        // GREEN (current minimum)
        // WHITE (currently scanning)
        //
        // Once swap happens, they become RED.
        selectionStatus.i = selectionMinimumIndex;
        selectionStatus.j = selectionInnerIndex;

        if (numbers[selectionInnerIndex] <
            numbers[selectionMinimumIndex])
        {
            selectionMinimumIndex = selectionInnerIndex;
        }

        selectionInnerIndex++;
    }
    else
    {
        // Highlight the actual swap.
        selectionStatus.i = selectionOuterIndex;
        selectionStatus.j = selectionMinimumIndex;

        if (selectionMinimumIndex != selectionOuterIndex)
        {
            swap(selectionOuterIndex,
                 selectionMinimumIndex);

            selectionStatus.swapped = true;
        }

        // Next iteration.
        selectionOuterIndex++;

        selectionMinimumIndex = selectionOuterIndex;

        selectionInnerIndex = selectionOuterIndex + 1;
    }

    return selectionStatus;
}

// ======================================================
//                      MAIN
// ======================================================

int main()
{
    srand(time(NULL));

    // Allow resizing before creating the window.
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(WIDTH, HEIGHT, "Sorting Visualizer");

    SetTargetFPS(COUNT * 3);

    init_random_numbers();

    SortStatus status = bubbleStatus;

    int activeOption = 0;
    int previousOption = 0;

    bool dropDownEditMode = false;

    while (!WindowShouldClose())
    {
        // ============================================
        // Execute one sorting step
        // ============================================

        if (isSorting &&
            !isPaused &&
            !status.sort_done)
        {
            if (activeOption == 0)
            {
                status = bubble_sort_step();
            }
            else
            {
                status = selection_sort_step();
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        // ============================================
        // Top Panel
        // ============================================

        DrawRectangle(
            0,
            0,
            GetScreenWidth(),
            TOP_PANEL_HEIGHT,
            DARKGRAY
        );

        DrawLine(
            0,
            TOP_PANEL_HEIGHT,
            GetScreenWidth(),
            TOP_PANEL_HEIGHT,
            LIGHTGRAY
        );

        DrawText(
            "Sorting Visualizer",
            20,
            58,
            22,
            WHITE
        );

        // ============================================
        // Draw Bars
        // ============================================

        draw_bars(status);

        // ============================================
        // Dropdown
        // ============================================

        if (GuiDropdownBox(
                (Rectangle)
                {
                    DROPDOWN_X,
                    CONTROL_Y,
                    DROPDOWN_W,
                    BUTTON_H
                },
                "Bubble Sort;Selection Sort",
                &activeOption,
                dropDownEditMode))
        {
            dropDownEditMode = !dropDownEditMode;

            if (!dropDownEditMode &&
                activeOption != previousOption)
            {
                isSorting = false;
                isPaused = false;

                init_random_numbers();

                if (activeOption == 0)
                {
                    reset_bubble_sort();
                    status = bubbleStatus;
                }
                else
                {
                    reset_selection_sort();
                    status = selectionStatus;
                }

                previousOption = activeOption;
            }
        }

        // ============================================
        // Action Button
        // ============================================

        const char *actionText;

        if (!isSorting)
        {
            actionText = "Start";
        }
        else if (isPaused)
        {
            actionText = "Resume";
        }
        else
        {
            actionText = "Pause";
        }

        if (GuiButton(
                (Rectangle)
                {
                    START_X,
                    CONTROL_Y,
                    BUTTON_W,
                    BUTTON_H
                },
                actionText))
        {
            if (!isSorting)
            {
                isSorting = true;
                isPaused = false;
            }
            else if (isPaused)
            {
                isPaused = false;
            }
            else
            {
                isPaused = true;
            }
        }

        // ============================================
        // Reset Button
        // ============================================

        if (GuiButton(
                (Rectangle)
                {
                    RESET_X,
                    CONTROL_Y,
                    BUTTON_W,
                    BUTTON_H
                },
                "Reset"))
        {
            isSorting = false;
            isPaused = false;

            init_random_numbers();

            if (activeOption == 0)
            {
                reset_bubble_sort();
                status = bubbleStatus;
            }
            else
            {
                reset_selection_sort();
                status = selectionStatus;
            }
        }

        // ============================================
        // Algorithm Name
        // ============================================

        const char *algorithmName =
            (activeOption == 0)
            ? "Bubble Sort"
            : "Selection Sort";

        DrawText(
            algorithmName,
            GetScreenWidth() - 220,
            18,
            20,
            YELLOW
        );

        // ============================================
        // Current Status
        // ============================================

        const char *statusText;

        if (status.sort_done)
        {
            statusText = "Finished";
        }
        else if (!isSorting)
        {
            statusText = "Waiting";
        }
        else if (isPaused)
        {
            statusText = "Paused";
        }
        else
        {
            statusText = "Running";
        }

        DrawText(
            statusText,
            GetScreenWidth() - 220,
            50,
            18,
            SKYBLUE
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}