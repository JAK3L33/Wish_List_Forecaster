#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_WISHLIST 10
#define MIN_WISHLIST 1

int main(void)
{
	const double maxIncome = 400000.0;
	const double minIncome = 500.0;
	const double minCostValue = 100.0;
	double netIncome = 0.0;
	int bool1 = 0;
	int wishlistItems = 0;
	int i = 0;
	double cost[MAX_WISHLIST] = { 0.0 };
	int priority[MAX_WISHLIST] = { 0 };
	char finance[MAX_WISHLIST] = { 0 };
	double items_cost = 0.0;
	int menu = 0;
	int priorityFilter = 0;
	int financeOptions = 0;
	double years = 0;
	double months = 0;
	double amountPriority1 = 0.0;
	double amountPriority2 = 0.0;
	double amountPriority3 = 0.0;
	double c = 0.0;

	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n");
	printf("\nEnter your monthly NET income: $");
	scanf("%lf", &netIncome);
	while (bool1 == 0)
	{
		if (netIncome < minIncome)
		{
			bool1 = 0;
			printf("ERROR: You must have a consistent monthly income of at least $500.00");
			printf("\n\nEnter your monthly NET income: $");
			scanf("%lf", &netIncome);
		}
		else if (netIncome > maxIncome)
		{
			bool1 = 0;
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00");
			printf("\n\nEnter your monthly NET income: $");
			scanf("%lf", &netIncome);
		}
		else
		{
			bool1 = 1;
		}
	}
	printf("\nHow many wish list items do you want to forecast?: ");
	scanf("%d", &wishlistItems);
	bool1 = 0;
	while (bool1 == 0)
	{
		if (wishlistItems > MAX_WISHLIST || wishlistItems < MIN_WISHLIST)
		{
			printf("ERROR: List is restricted to between 1 and 10 items.");
			printf("\n\nHow many wish list items do you want to forecast?: ");
			scanf("%d", &wishlistItems);
		}
		else
		{
			bool1 = 1;
		}
	}
	for (i = 0; i < wishlistItems; i++)
	{
		printf("\nItem-%d Details:\n", i + 1);
		printf("   Item cost: $");
		scanf("%lf", &cost[i]);
		while (cost[i] < minCostValue)
		{
			printf("      ERROR: Cost must be at least $%.2lf\n", minCostValue);
			printf("   Item cost: $");
			scanf("%lf", &cost[i]);
		}
		items_cost = items_cost + cost[i];
		printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
		scanf("%d", &priority[i]);
		while (priority[i] < 1 || priority[i] > 3)
		{
			printf("      ERROR: Value must be between 1 and 3");
			printf("\n   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf("%d", &priority[i]);
		}
		while (getchar() != '\n');
		printf("   Does this item have financing options? [y/n]: ");
		scanf("%c", &finance[i]);
		while (finance[i] != 'n' && finance[i] != 'y')
		{
			printf("      ERROR: Must be a lowercase 'y' or 'n'");
			printf("\n   Does this item have financing options? [y/n]: ");
			while (getchar() != '\n');
			scanf("%c", &finance[i]);
		}
	}
	printf("\nItem Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");
	for (i = 0; i < wishlistItems; i++)
	{
		printf("%3d  %5d    %5c    %11.2lf\n", i + 1, priority[i], finance[i], cost[i]);
	}
	printf("---- -------- -------- -----------\n");
	printf("                      $%11.2lf\n\n", items_cost);
	printf("How do you want to forecast your wish list?\n");
	printf(" 1. All items (no filter)\n");
	printf(" 2. By priority\n");
	printf(" 0. Quit/Exit\n");
	printf("Selection: ");
	scanf("%d", &menu);
	do
	{
		if (menu == 1)
		{
			printf("\n====================================================\n");
			printf("Filter:   All items\n");
			printf("Amount:   $%1.2lf\n", items_cost);
			months = items_cost / netIncome;
			months = (int)(months + 0.5); // rounding whole number
			years = (int)months / 12; // finding years needed 

			// checking if the year is less than 1
			if (years > 1) 
			{
				months = (int)months % 12;
			}
			printf("Forecast: %0.lf years, %.0lf months\n", years, months); // printing the years and months to the screen. The same logic is applied for the others
			for (i = 0; i < wishlistItems; i++)
			{
				if (finance[i] == 'y')
				{
					financeOptions = 1;
				}
			}
			if (financeOptions == 1)
			{
				printf("NOTE: Financing options are available on some items.\n");
				printf("      You can likely reduce the estimated months.");
			}
			printf("\n====================================================\n");
			printf("\nHow do you want to forecast your wish list?\n");
			printf(" 1. All items (no filter)\n");
			printf(" 2. By priority\n");
			printf(" 0. Quit/Exit\n");
			printf("Selection: ");
			scanf("%d", &menu);
		}
		else if (menu == 2)
		{
			printf("\nWhat priority do you want to filter by? [1-3]: ");
			scanf("%d", &priorityFilter);
			printf("\n====================================================\n");
			printf("Filter:   by priority (%d)\n", priorityFilter);
			if (priorityFilter == 1)
			{
				for (i = 0; i < wishlistItems; i++)
				{
					if (priorityFilter == priority[i])
					{
						amountPriority1 += cost[i];
					}
				}
				printf("Amount:   $%.2lf\n", amountPriority1); // amount for priority 1
				months = amountPriority1 / netIncome;
				months = (int)(months + 0.5);
				years = (int)months / 12;
				if (years > 1)
				{
					months = (int)months % 12;
				}
				printf("Forecast: %0.lf years, %.0lf months\n", years, months);
				financeOptions = 0;
				for (i = 0; i < wishlistItems; i++)
				{
					if (finance[i] == 'y' && priority[i] == 1)
					{
						financeOptions = 1;
					}
				}
				if (financeOptions == 1)
				{
					printf("NOTE: Financing options are available on some items.\n");
					printf("      You can likely reduce the estimated months.\n");
				}
				printf("====================================================\n");
				printf("\nHow do you want to forecast your wish list?\n");
				printf(" 1. All items (no filter)\n");
				printf(" 2. By priority\n");
				printf(" 0. Quit/Exit\n");
				printf("Selection: ");
				scanf("%d", &menu);
			}
			else if (priorityFilter == 2)
			{
				for (i = 0; i < wishlistItems; i++)
				{
					if (priorityFilter == priority[i])
					{
						amountPriority2 += cost[i];
					}
				}
				printf("Amount:   $%.2lf\n", amountPriority2); // amount for priority 2
				months = amountPriority2 / netIncome;
				months = (int)(months + 0.5);
				years = (int)months / 12;
				if (years > 1)
				{
					months = (int)months % 12;
				}
				printf("Forecast: %0.lf years, %.0lf months\n", years, months);
				financeOptions = 0;
				for (i = 0; i < wishlistItems; i++)
				{
					if (finance[i] == 'y' && priority[i] == 2)
					{
						financeOptions = 1;
					}
				}
				if (financeOptions == 1)
				{
					printf("NOTE: Financing options are available on some items.\n");
					printf("      You can likely reduce the estimated months.\n");
				}
				printf("====================================================\n");
				printf("\nHow do you want to forecast your wish list?\n");
				printf(" 1. All items (no filter)\n");
				printf(" 2. By priority\n");
				printf(" 0. Quit/Exit\n");
				printf("Selection: ");
				scanf("%d", &menu);
			}
			else if (priorityFilter == 3)
			{
				for (i = 0; i < wishlistItems; i++)
				{
					if (priorityFilter == priority[i])
					{
						amountPriority3 += cost[i];
					}
				}
				printf("Amount:   $%.2lf\n", amountPriority3); // amount for priority 3
				months = amountPriority3 / netIncome;
				months = (int)(months + 0.5);
				years = (int)months / 12;
				if (years > 1)
				{
					months = (int)months % 12;
				}
				printf("Forecast: %0.lf years, %.0lf months\n", years, months);
				financeOptions = 0;
				for (i = 0; i < wishlistItems; i++)
				{
					if (finance[i] == 'y' && priority[i] == 3)
					{
						financeOptions = 1;
					}
				}
				if (financeOptions == 1)
				{
					printf("NOTE: Financing options are available on some items.\n");
					printf("      You can likely reduce the estimated months.\n");
				}
				printf("====================================================\n");
				printf("\nHow do you want to forecast your wish list?\n");
				printf(" 1. All items (no filter)\n");
				printf(" 2. By priority\n");
				printf(" 0. Quit/Exit\n");
				printf("Selection: ");
				scanf("%d", &menu);
			}
		}
		else if (menu == 0)
		{
			menu = 0;
		}
		else
		{
			printf("\nERROR: Invalid menu selection.");
			printf("\n\nHow do you want to forecast your wish list?\n");
			printf(" 1. All items (no filter)\n");
			printf(" 2. By priority\n");
			printf(" 0. Quit/Exit\n");
			printf("Selection: ");
			scanf("%d", &menu);
		}
	} while (menu != 0);
	printf("\nBest of luck in all your future endeavours!");
	return 0;
}
