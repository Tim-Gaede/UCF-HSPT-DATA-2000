/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Secret Judging League                                     */
/*                                                                         */
/* Problem by: Glenn Martin and Michael Smith                              */
/* Solution by: Phillip Dexheimer                                          */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//I just threw the table into a const array, which means the program
//basically just boils down to a couple of lookups.  I could have used 3
//arrays rather than a multi-D array with one dimension of 3, but this is
//what I thought of first

const char *table[3][26] =
{{"Stinky",
"Lumpy",
"Buttercup",
"Gidget",
"Crusty",
"Greasy",
"Fluffy",
"Cheeseball",
"Chim-Chim",
"Poopsie",
"Flunky",
"Booger",
"Pinky",
"Zippy",
"Goober",
"Doofus",
"Slimy",
"Loopy",
"Snotty",
"Falafel",
"Dorkey",
"Squeezit",
"Oprah",
"Skipper",
"Dinky",
"Zsa-Zsa"},
{"Diaper",
"Toilet",
"Giggle",
"Bubble",
"Girdle",
"Barf",
"Lizard",
"Waffle",
"Cootie",
"Monkey",
"Potty",
"Liver",
"Banana",
"Rhino",
"Burger",
"Hamster",
"Toad",
"Gizzard",
"Pizza",
"Gerbil",
"Chicken",
"Pickle",
"Chuckle",
"Tofu",
"Gorilla",
"Stinker"},
{"head",
"mouth",
"face",
"nose",
"tush",
"breath",
"pants",
"shorts",
"lips",
"honker",
"butt",
"brain",
"tushie",
"chunks",
"hiney",
"biscuits",
"toes",
"buns",
"fanny",
"sniffer",
"sprinkles",
"kisser",
"squirt",
"humperdinck",
"brains",
"juice"}};

void main ()
{
 FILE *In = fopen("league.in", "r");
 int i, N;
 char line[85], *p, name[80];

 fgets(line, 80, In);
 N = atoi(line);
 for (i=0;i<N;i++)
  {
   fgets(line, sizeof(line), In);
   p = strchr(line, '\n');
   if (p) *p = '\0';
   sprintf (name, "%s ", table[0][tolower(line[0])-'a']);

//All that nonsense of multiple middle names can be circumvented by just
//going straight to the last name.  just what strrchr() was invented for.
   p = strrchr(line, ' ');
   p++;
   strcat (name, table[1][tolower(*p)-'a']);
   strcat (name, table[2][tolower(line[strlen(line)-1])-'a']);
   printf ("%s\n", name);
  }
 fclose(In);
}