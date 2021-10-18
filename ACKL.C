/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Acknowledged                                              */
/*                                                                         */
/* Problem by: Richard Russo                                               */
/* Solution by: Glenn Martin                                               */
/***************************************************************************/

#include <stdio.h>
#include <string.h>

main()
{
   FILE   *infile;
   char   line[80];
   int    errorFound;
   int    numTransaction;
   int    numM1sPending;
   int    numM2sPending;

   /* Open the input file */
   infile = fopen("ackl.in", "r");

   /* Initialize the transaction counter */
   numTransaction = 0;

   /* Read the first line */
   fgets(line, sizeof(line), infile);
   if (line[strlen(line)-1] == '\n')
      line[strlen(line)-1] = '\0';

   /* Repeat until we get to the end of data */
   while (strcmp(line, "EOF") != 0)
   {
      /* Assume everything is okay until we detect an error */
      errorFound = 0;

      /* Initialize counters */
      numM1sPending = 0;
      numM2sPending = 0;

      /* Print the header for this transaction */
      numTransaction++;
      printf("Transaction %d: ", numTransaction);

      /* Process through the transaction until the end */
      while (strcmp(line, "EOT") != 0)
      {
         /* Process the message we just read */
         if (strcmp(line, "m1") == 0)
         {
            /* Add one to our M1 counter */
            numM1sPending++;

            /* Check to see if what we did was invalid (we sent an m1 when */
            /* we had one or more already pending)                         */
            if (numM1sPending >= 2)
               errorFound = 1;
         }
         else if (strcmp(line, "m2") == 0)
         {
            /* Add one to our M2 counter */
            numM2sPending++;

            /* Check to see if what we did was invalid (we sent an m2 when */
            /* we had one or more already pending)                         */
            if (numM2sPending >= 2)
               errorFound = 1;
         }
         else if (strcmp(line, "m12") == 0)
         {
            /* Add one to both our M1 and M2 counters */
            numM1sPending++;
            numM2sPending++;

            /* Check to see if what we did was invalid (we sent an m1 and */
            /* m2 when we we had one or more m1's and/or m2's already     */
            /* pending)                                                   */
            if ( (numM1sPending >= 2) || (numM2sPending >= 2) )
               errorFound = 1;
         }
         else if (strcmp(line, "a1") == 0)
         {
            numM1sPending--;

            /* Check to see if what we did was invalid (we sent an a1 when */
            /* we did not have an m1 pending)                              */
            if (numM1sPending < 0)
               errorFound = 1;
         }
         else if (strcmp(line, "a2") == 0)
         {
            numM2sPending--;

            /* Check to see if what we did was invalid (we sent an a2 when */
            /* we did not have an m2 pending)                              */
            if (numM2sPending < 0)
               errorFound = 1;
         }
         else if (strcmp(line, "a12") == 0)
         {
            /* Take one off our M1 and M2 counters */
            numM1sPending--;
            numM2sPending--;

            /* Check to see if what we did was invalid (we sent an a1 and  */
            /* a2 when we we did not have an m1 and/or m2 already pending) */
            if ( (numM1sPending < 0) || (numM2sPending < 0) )
               errorFound = 1;
         }

         /* Get next message */
         fgets(line, sizeof(line), infile);
         if (line[strlen(line)-1] == '\n')
            line[strlen(line)-1] = '\0';
      }

      /* Make sure every message was acknowledged */
      if ( (numM1sPending > 0) || (numM2sPending > 0) )
	 errorFound = 1;

      /* Output whether this transaction was valid or not */
      if (errorFound == 1)
         printf("invalid\n\n");
      else
         printf("valid\n\n");

      /* Get first message of new transaction */
      fgets(line, sizeof(line), infile);
      if (line[strlen(line)-1] == '\n')
         line[strlen(line)-1] = '\0';
   }
}

