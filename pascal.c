// ============================================= =============  ====    = =
//
// Pascal Triangle using only sums (does not overflow at level 21 as most solutions)
// Written by Vander Roberto Nunes Dias, a.k.a imerso / imersiva.com
//
// =========================================================== =============  ====    = =

/*

Example of results level 22

1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
1 6 15 20 15 6 1
1 7 21 35 35 21 7 1
1 8 28 56 70 56 28 8 1
1 9 36 84 126 126 84 36 9 1
1 10 45 120 210 252 210 120 45 10 1
1 11 55 165 330 462 462 330 165 55 11 1
1 12 66 220 495 792 924 792 495 220 66 12 1
1 13 78 286 715 1287 1716 1716 1287 715 286 78 13 1
1 14 91 364 1001 2002 3003 3432 3003 2002 1001 364 91 14 1
1 15 105 455 1365 3003 5005 6435 6435 5005 3003 1365 455 105 15 1
1 16 120 560 1820 4368 8008 11440 12870 11440 8008 4368 1820 560 120 16 1
1 17 136 680 2380 6188 12376 19448 24310 24310 19448 12376 6188 2380 680 136 17 1
1 18 153 816 3060 8568 18564 31824 43758 48620 43758 31824 18564 8568 3060 816 153 18 1
1 19 171 969 3876 11628 27132 50388 75582 92378 92378 75582 50388 27132 11628 3876 969 171 19 1
1 20 190 1140 4845 15504 38760 77520 125970 167960 184756 167960 125970 77520 38760 15504 4845 1140 190 20 1
1 21 210 1330 5985 20349 54264 116280 203490 293930 352716 352716 293930 203490 116280 54264 20349 5985 1330 210 21 1
1 22 231 1540 7315 26334 74613 170544 319770 497420 646646 705432 646646 497420 319770 170544 74613 26334 7315 1540 231 22 1

(and you can still go way up without overflowing)

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct number
{
	unsigned long value;
	struct number* next;
};


int main(int argc, char *argv[])
{
	int r;
	int c;

	// must have an argument with the level, from 0 and up
	if (argc != 2 || atoi(argv[1]) < 0)
	{
		printf("Syntax: %s <number_of_levels>\n", argv[0]);
		return -1;
	}

	// allocate n lists, one for each row
	struct number** rowList = (struct number**)malloc(sizeof(struct number) * (atoi(argv[1])+1));

	// loop through the rows
	for(r=0; r<=atoi(argv[1]); r++)
	{
		// start with 1 at left
		rowList[r] = (struct number*)malloc(sizeof(struct number));

		// always 1 at left
		rowList[r]->value = 1;
		rowList[r]->next = NULL;

		// start pointing to the first number in the current row
		struct number* current = rowList[r];
		printf ("%lu", current->value);

		// from third level and up, will sum previous columns
		if (r > 1)
		{
			// add columns from previous row
			struct number* previous = rowList[r-1];

			for (int c=0; c<r; c++)
			{
				if (previous->next)
				{
					struct number* next = (struct number*)malloc(sizeof(struct number));

					next->value = previous->value + previous->next->value;
					printf (" %lu", next->value);

					current->next = next;
					current = next;

					previous = previous->next;
				}

			}
		}

		// from second row and up, will always have 1 at right
		if (r > 0)
		{
			// ends with 1 at right
			struct number* right = (struct number*)malloc(sizeof(struct number));
			right->value = 1;
			right->next = NULL;

			// add to the linked list
			current->next = right;
			printf (" %lu", right->value);
		}

		printf("\n");
	}

	// walk the list releasing memory
	for(r=0; r<=atoi(argv[1]); r++)
	{
		struct number* current = rowList[r];

		do
		{
			struct number* next = current->next;
			free(current);

			if (next)
			{
				current = next;
				if (!current->next) { free(current); break; }
			}
			else break;
		}
		while (current->next);
	}

	free(rowList);

	// done.
	return 0;
}

