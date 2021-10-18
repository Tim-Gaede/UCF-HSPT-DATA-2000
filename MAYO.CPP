/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Cinco de Mayo                                             */
/*                                                                         */
/* Problem by: Glenn Martin                                                */
/* Solution by: Jason Daly                                                 */
/***************************************************************************/

#include <stdio.h>
#include <string.h>

#define TRUE  1
#define FALSE 0


int main(void)
{
    FILE *fp;
    int  numWeeks, numMeals;
    int  i, j;
    int  mayoCount;
    char mealPiece[256];
    char inChar;
    char inStr[2];

    fp = fopen("mayo.in", "r");

    // Read the number of weeks
    fscanf(fp, "%d\n", &numWeeks);

    for (i = 0; i < numWeeks; i++)
    {
        // Read the number of meals for this week
        fscanf(fp, "%d\n", &numMeals);

        // Initialize the mayo counter
        mayoCount = 0;

        for (j = 0; j < numMeals; j++)
        {
            // Initialize the ingredient string and the input character
            sprintf(mealPiece, "");
            inChar = '\0';

            // Read the meal from the file one ingredient at a time
            while (inChar != '\n')
            {
                // Read the next character
                inChar = fgetc(fp);
                if ((inChar == ' ') || (inChar == '\n'))
                {
                    // End of the ingredient, check if it's mayo
                    if ((strcmp(mealPiece, "mayo") == 0) ||
                        (strcmp(mealPiece, "mayonnaise") == 0))
                    {
                        mayoCount++;
                    }

                    // Move on to the next ingredient
                    sprintf(mealPiece, "");
                }
                else
                {
                    // Add the character to the ingredient string
                    sprintf(inStr, "%c", inChar);
                    strcat(mealPiece, inStr);
                }
            }
        }

        // Print the output for this week
        if (mayoCount >= 5)
            printf("Week #%d: Cinco de Mayo!\n\n", i + 1);
        else
            printf("Week #%d: Way to go, Mason!\n\n", i + 1);
    }

    fclose(fp);

    return 0;
}