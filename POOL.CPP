/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: The Pool Game                                             */
/*                                                                         */
/* Problem by: Glenn Martin                                                */
/* Solution by: Mike Kujawa                                                */
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

//Simple point structure
struct TPoint
{
    int x, y;
};




/* bColinear
   Test to see if point C is on the ray A->B.
   This is done by first comparing the slopes of the rays A->B and A->C.
   If they are the same, then the sign of the changes are compared.
   If THEY are the same, then the rays are shooting in the same direction.

   Although I decided not to allow it in the input, the reason A->C is 
   checked instead of B->C is in case the innocent bystander were between
   the cue ball and the target ball.  Again, that case did not appear in
   the judge input.

   To remove floating point roundoff errors, no fractions are used in the
   calculations.  Instead, the equation:

   dy1    dy2
   --- == ---
   dx1    dx2

   is cross-multiplied to give (dx2)(dy1) == (dx1)(dy2)

   This also removes any division by 0 cases.

   Note that this requires a type large enough to hold the result of 
   the math.  Since the input is bounded to non-negative 16-bit ints, 
   subtracting them fits in 16bits and multiplying them fits in a 
   32-bit int.
*/

bool bColinear(TPoint A, TPoint B, TPoint C)
{
long dx1 = (B.x-A.x);
long dy1 = (B.y-A.y);
long dx2 = (C.x-A.x);
long dy2 = (C.y-A.y);

    return ((dx1 * dy2 == dx2 * dy1) && 
            ((dx1 > 0) == (dx2 > 0)) &&
            ((dy1 > 0) == (dy2 > 0))   //if dx1==dx2==0, this must be checked
	   );
}





/* 
   Read them in and test them.  The message is not printed until all of the
   bystanders for a given case are processed to avoid over-reporting hitting
   somebody. 
*/
void main()
{
FILE *F;
int N; //Number of cases

    F = fopen("pool.in", "r");
    fscanf(F, "%d", &N);

    for (int i=0; i < N; i++)
    {
    TPoint Cue, Ball;   //Points for the cueball and target ball
    int nBystanders;    //Number of innocent bystanders 
    bool bSafe = true;  //true if no bystanders are hit

        //Read in the first line of the case
        fscanf(F, "%d %d %d %d %d", 
            &Cue.x, &Cue.y, &Ball.x, &Ball.y, &nBystanders);

        //Read in the bystanders
	for (int j=0; j < nBystanders; j++)
        {
        TPoint Bystander;
            fscanf(F, "%d %d", &Bystander.x, &Bystander.y);

        if (bColinear(Cue, Ball, Bystander))
            bSafe = false;
        }

        //Output the appropriate message based on bSafe
        if (bSafe)
	    printf("Go ahead, Spike.  It looks clear.\n");
        else
	    printf("Watch out, Spike!  You're going to hit somebody!\n");
    }
}
