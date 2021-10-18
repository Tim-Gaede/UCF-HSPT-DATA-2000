/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Halt!  Who goes there?                                    */
/*                                                                         */
/* Problem by: Jason Daly                                                  */
/* Solution by: Eric Heimburg                                              */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
  int nInputs, loop;
  char s[ 512 ];
  
  FILE *f = fopen("halt.in", "r");
  
  fgets(s, sizeof(s), f);
  sscanf(s, "%d", &nInputs);

  for (loop = 0; loop < nInputs; loop++)
  {
    fgets(s, sizeof(s), f);
    char *p = strchr(s, '\n'); //is there a carriage-return on this line?
    if (p)
      *p = '\0'; //yes! Terminate the string there, destroying the \n

    printf("%s will come to a halt.\n\n", s);
  }

  fclose(f);
}
