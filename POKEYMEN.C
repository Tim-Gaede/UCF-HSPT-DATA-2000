/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Gotta Fetch 'em All!                                      */
/*                                                                         */
/* Problem by: Jason Daly                                                  */
/* Solution by: Richard Russo                                              */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#define FALSE 0
#define TRUE  (!FALSE)

/** define this to turn on debugging output. */
/** #define DEBUG */

/** problem guarantees 10 chars max; I'm being safe */
#define POKEYMEN_NAME_LENGTH 20

#define MAX_NUM_POKEYMEN     100

typedef struct {
  int element;
  int level;
  char name[POKEYMEN_NAME_LENGTH + 1];
} pokeyman;

/** nash's pokeymen */
pokeyman nash_pokeymen[MAX_NUM_POKEYMEN];

/** indicates if a pokeyman has been used or not,
    remember to memset it to zero on init */
int      used[MAX_NUM_POKEYMEN];

/** the number of pokeymen nash has */
int      num_pokeymen;
    
const char *elements[] =
{
  "fire",
  "water",
  "earth",
  "air",
  "electricity",
  "poison",
  "psychics",
  "fighting"
};

#define FIRE         0
#define WATER        1
#define EARTH        2
#define AIR          3
#define ELECTRICITY  4
#define POISON       5
#define PSYCHICS     6
#define FIGHTING     7

#define NUM_ELEMENTS 8

/**
 * initialize any data structures.
 *
 */

void
init (void)
{
  memset (used, 0, sizeof (used));
}

/**
 * get the index of the string `str' in the array
 * of char*'s `list' which has n elements.
 *
 * returns -1 if `str' not found.
 *
 */

int
str_get_idx (const char *list[], int n, const char *str)
{
  int count;

  for (count = 0; count < n; count++) {
    if (!strcmp (list[count], str)) {
      return count;
    }
  }

  return -1;
}

/**
 * This function will give strictly the advantage
 * that a pokeyman of element `elem1' has over a
 * pokeyman of element `elem2'
 *
 */

int
get_rel_elem_adv (int elem1, int elem2)
{
  switch (elem1) {
  case FIRE:
    if (EARTH == elem2) return 1;
    break;

  case WATER:
    if (FIRE == elem2) return 1;
    break;

  case EARTH:
    if (ELECTRICITY == elem2) return 1;
    break;

  case AIR:
    if (EARTH == elem2) return 1;
    break;

  case ELECTRICITY:
    if (WATER == elem2) return 1;
    break;

  case POISON:
    if ((FIRE == elem2) || (EARTH == elem2)
	|| (WATER == elem2) || (AIR == elem2)) {
      return 1;
    }
    break;

  case PSYCHICS:
    if (PSYCHICS != elem2) return 1;
    break;

    /** FIGHTING is always a 0 advantage */
  }

  return 0;
}

/**
 * get the advantage of pokeyman p1 over pokeyman p2.
 *
 */

int
get_rel_pokeyman_adv (pokeyman *p1, pokeyman *p2)
{
  int adv = 0;

  /**
   * I would offer a rigorous proof that the following two
   * lines do calculate the relative advantage, but you can 
   * check me easily by trying all possibilities.  There are 
   * only NUM_ELEMENTS * NUM_ELEMENTS of them.
   *
   */

  adv = get_rel_elem_adv (p1->element, p2->element);
  adv -= get_rel_elem_adv (p2->element, p1->element);

  adv += p1->level;
  adv -= p2->level;

  return adv;
}

/** input will be read from this FILE* */
FILE *f;

/** 
 * enough space to hold one line of input 
 *
 */

#define BUF_SIZE 256

/**
 * This function will read the descriptions of nash's pokeymen
 * into the nash_pokeymen array.  It assumes that num_pokeymen
 * has been set appropriately.  Input is read from `f' above.
 *
 */

void
get_pokeymen_input (void)
{
  int count;
  char buf[BUF_SIZE];
  char element_name[BUF_SIZE];

  for (count = 0; count < num_pokeymen; count++) {
    fgets (buf, BUF_SIZE, f);
    sscanf (buf, "%s %s %d", 
	    &(nash_pokeymen[count].name),
	    element_name,
	    &(nash_pokeymen[count].level));

    nash_pokeymen[count].element = str_get_idx (elements, NUM_ELEMENTS,
						element_name);

    assert (strlen (nash_pokeymen[count].name) > 0);
    assert ((nash_pokeymen[count].level > 0)
	    &&(nash_pokeymen[count].level <= 3));

    assert ((nash_pokeymen[count].element >= 0)
	    &&(nash_pokeymen[count].element < NUM_ELEMENTS));
  }
}

/**
 * returns the index of the pokeyman in nash_pokeymen
 * that has the lowest advantage or least disadvantage
 * relative to a pokeyman of element `elem' and level
 * `level'
 *
 * It only looks at the pokeymen that are !used[]
 *
 */

int
get_best_pokeyman (int elem, int level)
{
  int count;
  int best = -30; /* a disadvantage will never be that small */
  int best_idx = -1;
  int rel_adv;
  pokeyman p;

  p.name[0] = '\0';
  p.level   = level;
  p.element = elem;

  for (count = 0; count < num_pokeymen; count++)
    {
      if (!used[count]) 
	{
	  rel_adv = get_rel_pokeyman_adv (&(nash_pokeymen[count]),
					  &(p));

#ifdef DEBUG
	  printf ("rel: %d, idx: %d\n", rel_adv, count);
#endif
	  if ( (best <= 0) )
	    {
	      if ( (rel_adv > 0) || (abs (rel_adv) < abs (best)) )
		{
		  best_idx = count;
		  best = rel_adv;
		}
	    }

	  if ( (best > 0) && (rel_adv < best) && (rel_adv > 0) )
	    {
	      best_idx = count;
	      best = rel_adv;
	    }

	} /* if (!used[count]) */
    } /* for (count = 0; ... */

#ifdef DEBUG
  printf ("best: %d, best_idx: %d\n", best, best_idx);
#endif

  return best_idx;
}


int
main (void)
{
  int count;
  int elem, level;
  int num_baddies;
  char buf[BUF_SIZE];
  char elem_name[BUF_SIZE];
  int idx;

  f = fopen ("pokeymen.in", "r");

  assert (NULL != f);

  fgets (buf, BUF_SIZE, f);

  sscanf (buf, "%d", &num_pokeymen);

  while (num_pokeymen > 0)
  {
    init ();
    get_pokeymen_input ();

    printf ("********************\n");
    printf ("\n");

    fgets (buf, BUF_SIZE, f);

    sscanf (buf, "%d", &num_baddies);

    for (count = 0; count < num_baddies; count++)
    {

      fgets (buf, BUF_SIZE, f);
      sscanf (buf, "%s %d", elem_name, &level);

      elem = str_get_idx (elements, NUM_ELEMENTS, elem_name);

      assert ((0 < level) && (level < 4));
      assert ((0 <= elem) && (elem < NUM_ELEMENTS));

      idx = get_best_pokeyman (elem, level);

      assert ((0 <= idx) && (idx < num_pokeymen));
      used[idx] = TRUE;

      printf ("Match %d: %s, I choose you!\n",
	      count + 1,
	      nash_pokeymen[idx].name);
	      printf ("\n");
    }

    fgets (buf, BUF_SIZE, f);
    sscanf (buf, "%d", &num_pokeymen);
  }

  fclose (f);
  return 0;
}


