/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: These Are Odd Days We Live In                             */
/*                                                                         */
/* Problem by: Glenn Martin                                                */
/* Solution by: Eric Heimburg                                              */
/***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//this will come in handy at various times: an array of the number of days in each month
int DaysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


//a util function, only called in IsAllOdd(), below
bool IsOddDigit(char c)
{
  return (c == '1') || (c == '3') || (c == '5') || (c == '7') || (c == '9');
}


//returns true iff all the digits of num are odd
bool IsAllOdd(int num)
{
  char s[ 256 ];
  sprintf(s, "%d", num);
  for (unsigned loop = 0; loop < strlen(s); loop++)
    if (!IsOddDigit(s[ loop ]))
      return false;
  return true;
}




//returns true if there is another odd day this year, returns false otherwise.
//If it returns true, then the next odd day will be in Month and Day. If it 
//returns false, then Month and Day will be unchanged.
bool FindNextOddDayThisYear(int &Month, int &Day)
{
  //well, we will want to fiddle with Month and Day while we calculate the
  //next all-odd day this year. But there is a chance that there will not
  //be another all-odd day this year. If that is the case, we will return
  //false, and will want to leave Month and Day in their original, unaltered
  //forms. For this reason, we shall work with copies of Month and Day,
  //called AMonth and ADay, and only change Month and Day when we are sure
  //that we have another odd day this year.
  
  int AMonth = Month;
  int ADay = Day;

  ADay++; //go to the next day. Otherwise, if Month/Day is an odd day, we will return this day, and we need to return the NEXT odd day

  if (AMonth >= 12) //well, it's the last month of the year, which is an even month. No way there are more odd days this year!
    return false;

  if (!IsAllOdd(AMonth)) //hey, this is an even month! Make it odd!
  {
    AMonth++; //inc month counter
    ADay = 1; //reset day counter
  }

  while (!IsAllOdd(ADay)) //find the next all-odd day
    ADay++;
  
  if (ADay > DaysPerMonth[ AMonth-1 ]) //did we go into the next month?
  {
    AMonth++; //if so, increment the month counter, and 
    ADay = 1; //reset the day counter
  }

  if (!IsAllOdd(AMonth))
    AMonth++;

  if (AMonth >= 12) //we may have incremented it so far that it is no longer a valid month, or is December, which is an even month. Either way, bail out, cuz we didnt find an all-odd day
    return false;
  else 
  {
    //okay! Success! We have found the next odd day this year, and it is
    //stored in AMonth and ADay. Unfortunately these are temporary
    //variables. Store the data in Month and Day
    Month = AMonth;
    Day = ADay;
    return true;
  }
}



//Figures out the next odd date. Returns this date in Month, Day, and Year.
void FindNextOddDate(int &Month, int &Day, int &Year)
{
  if (IsAllOdd(Year) && FindNextOddDayThisYear(Month, Day))
  {
    //success! Found a nice odd date during the current year
    //dont really have to do anything here; Woohoo! 
  }
  else
  {
    //well, this year has no more odd dates. Find the next all-odd year
    Year++;
    while (!IsAllOdd(Year))
      Year++;
    Month = 1;
    Day = 1;
  }
}



//*******************************************************************

//this utility function determines the number of days between two dates
//thus, it returns m1/d1/y1 subtracted from m2/d2/y2, so to speak
long DateDiff(int m1, int d1, int y1, int m2, int d2, int y2)
{
  //well crap. This is hard. How do we find the number of days 
  //between these two dates? Hmm, hmm. Well, there's that way, but it's
  //too slow. Well who cares if it's slow? It will work. We will just keep 
  //incrementing date one over and over again til it is the same 
  //as date two. The number of times we have to increment date 1 is the 
  //number of days difference.
  //Note to those who care: there are more efficient ways to do this.

  long Diff = 0;

  while (! ((m1 == m2) && (d1 == d2) && (y1 == y2)) )
  {
    d1++; //increment day counter
    if (d1 > DaysPerMonth[ m1-1 ]) //hey, is that more days than are in this month?
    {
      //yes? well, increment month counter then
      d1 = 1;
      m1++;
      if (m1 > 12) //hey, is that more months than are in a year?
      {
        //yes? well, increment year counter then
        m1 = 1;
        y1++;
      }
    }
    Diff++;
  }

  return Diff;
}


//*******************************************************************


void main()
{
  FILE *f = fopen("days.in", "r");
  int nTests;
  char s[ 512 ];

  fgets(s, sizeof(s), f);
  sscanf(s, "%d", &nTests);

  for (int loop = 0; loop < nTests; loop++)
  {
    int Month, Day, Year;
    int NextMonth, NextDay, NextYear;
    fgets(s, sizeof(s), f);
    sscanf(s, "%d/%d/%d", &Month, &Day, &Year);
    NextMonth = Month;
    NextDay = Day;
    NextYear = Year;
    FindNextOddDate(NextMonth, NextDay, NextYear);

    //okay, we have the current date and the next odd date. Find the diff between these dates and print it out, and we're done
    long Difference = DateDiff(Month, Day, Year, NextMonth, NextDay, NextYear);
    //printf("%d/%d/%d -- %d/%d/%d = %ld\n", Month, Day, Year, NextMonth, NextDay, NextYear, Difference);
    printf("%ld\n", Difference);
  }
  fclose(f);
}


