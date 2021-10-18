/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Ali's Area Code                                           */
/*                                                                         */
/* Problem by: Glenn Martin                                                */
/* Solution by: Jason Daly                                                 */
/***************************************************************************/

#include <stdio.h>
#include <string.h>

void main(void)
{
  FILE * ifp;
  int nNums, i;
  char Line[100];

  ifp = fopen("area.in", "r");
  fscanf(ifp, "%d", &nNums);
  for (i = 0; i < nNums; i++)
  {
	fscanf(ifp, "%s", Line); 
	if (Line[0] != '4')
	  printf("(407) ");
	printf("%s\n", Line);
  }
  fclose(ifp);
}
