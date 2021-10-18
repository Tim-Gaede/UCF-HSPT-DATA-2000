/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Baby's Big Now!                                           */
/*                                                                         */
/* Problem by: Michael Kujawa                                              */
/* Solution by: Jason Daly                                                 */
/***************************************************************************/

#include <stdio.h>

int bornDay, bornYear;
int currentDay, currentYear;

int main(void)
{
    FILE *fp;

    int bornDay, bornYear;
    int currentDay, currentYear;

    int yearsDiff, daysDiff, totalDiff;

    /* Open the input file */
    fp = fopen("baby.in", "r");

    /* Read the first element on the line */
    fscanf(fp, "%d", &bornDay);
    while (bornDay != -1)
    {
	/* Read the rest of the input on this line */
	fscanf(fp, "%d %d %d\n", &bornYear, &currentDay, &currentYear);

	/* Calculate the total difference in days */
	yearsDiff = currentYear - bornYear;
	daysDiff = currentDay - bornDay;
	totalDiff = 365 * yearsDiff + daysDiff;

	if (totalDiff >= 570)
	{
	    /* Output the difference in years */
	    printf("%d years\n", totalDiff / 365);
	}
	else if ((totalDiff < 570) && (totalDiff >= 30))
	{
	    /* Output the difference in months */
	    printf("%d months\n", totalDiff / 30);
	}
	else if ((totalDiff < 30) && (totalDiff >= 14))
	{
	    /* Output the difference in months */
	    printf("%d weeks\n", totalDiff / 7);
	}
	else
	{
	    /* Output the difference in days */
	    printf("%d days\n", totalDiff);
	}

	fscanf(fp, "%d", &bornDay);
    }

    fclose(fp);

    return 0;
}