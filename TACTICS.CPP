/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Ultimate Fantasy Tactics                                  */
/*                                                                         */
/* Problem by: Richard Russo                                               */
/* Solution by: Phillip Dexheimer                                          */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//This problem has a very small set of possible solutions, which means it can
//be solved through a brute force method.  That makes the hard part
//enumerating the possible solutions.  After a good amount of thought, I
//realized that the number of possibilities was nEnemy^nParty.  This means
//that if you have 3 party members and 2 enemies, there are eight possible
//solutions.  I describe them as follows:  A unique integer represented in
//base-nEnemy (this gives it nParty digits).  Therefore, our eight possible
//solutions are: 000, 001, 010, 011, 100, 101, 110, 111.  What this means is:
//the party member i attacks enemy digit[i].  Therefore, in the solution 010,
//Enemy 0 is attacked by party members 0 and 2, while party member 1 attacks
//enemy 1.
//Anyway, this gives us a method of representing each solution with a unique
//number, and, perhaps more importantly, a way of extracting that solution
//from the number.
//This leaves only one trick:  The max case has 8^5 possible solutions,
//which is equal to 32768.  A 16-bit signed integer only goes up to 32767,
//so we have to use a long to enumerate the possibilities

int party[6];
int enemy[10];
int attack[6];
int nParty;
int nEnemy;
int nKills;
float WDF;
float LDF;

//1 to nEnemy^nParty
void ConsiderPossibility(long possibility)
{
 int localAttack[6];
 int localEnemy[10];
 int localKills;
 float localWDF, localLDF;

//Extract the base-nEnemy number, and throw it in an array
 int idx = nParty-1;
 memmove(localEnemy, enemy, sizeof(enemy));
 while (idx >= 0)
  {
   localAttack[idx] = possibility % nEnemy;
   possibility /= nEnemy;
   idx--;
  }
//Simulate the attacks, and try to figure out if it's the best
//The data for the best solution is stored in global variables
 for (int i=0;i<nParty;i++)
   localEnemy[localAttack[i]] -= party[i];
 localKills = localWDF = localLDF = 0;
 for (i=0;i<nEnemy;i++)
  {
   if (localEnemy[i] <= 0)
    {
	 localKills++;
	 localWDF -= (float)localEnemy[i]/enemy[i];
	}
   else
	 localLDF += (float)localEnemy[i]/enemy[i];
  }
 if (localKills > nKills)
  {
   memmove(attack, localAttack, sizeof(attack));
   nKills = localKills;
   WDF = localWDF;
   LDF = localLDF;
   return;
  }
 if ((localKills == nKills) && (localWDF < WDF))
  {
   memmove(attack, localAttack, sizeof(attack));
   nKills = localKills;
   WDF = localWDF;
   LDF = localLDF;
   return;
  }
 if ((localKills == nKills) && (fabs(localWDF - WDF) < 1e-6) && (localLDF < LDF))
  {
   memmove(attack, localAttack, sizeof(attack));
   nKills = localKills;
   WDF = localWDF;
   LDF = localLDF;
   return;
  }
}

void main()
{
 FILE *In = fopen("tactics.in", "r");
 int i, j, setnum;

 nParty = 3;
 setnum = 0;
 while (nParty != 0)
  {
   setnum++;
   fscanf(In, "%d", &nParty);
   if (nParty == 0)
     continue;
   for (i=0;i<nParty;i++)
     fscanf(In, "%d", &party[i]);
   fscanf(In, "%d", &nEnemy);
   for (i=0;i<nEnemy;i++)
     fscanf(In, "%d", &enemy[i]);
   nKills = 0;
   WDF = LDF = 1e30;
//figure out the number of possibilities
   long nComb = 1;
   for (i=0;i<nParty;i++)
     nComb *= nEnemy;
   for (long l=0;l<nComb;l++)
     ConsiderPossibility(l);
//Rounding garbage
   WDF = floor((WDF+0.0005)*1000);
   WDF /= 1000;
   LDF = floor((LDF+0.0005)*1000);
   LDF /= 1000;
   printf("+==========================================+\n");
   printf("| Battle #%-32d |\n", setnum);
   printf("+==========================================+\n");
   printf("| %-20s%-20s |\n", "Party Member", "Enemy");
   printf("| %-20s%-20s |\n", "------------", "-----");
   for (i=0;i<nParty;i++)
     printf ("| %-20d%-20d |\n", i+1, attack[i]+1);
   printf("+==========================================+\n");
   printf ("| WDF: %-15.3fLDF: %-15.3f |\n", WDF, LDF);
   printf("+==========================================+\n\n");
  }
}
