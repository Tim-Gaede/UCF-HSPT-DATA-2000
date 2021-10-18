(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: The Pool Game                                             *)
(*                                                                         *)
(* Problem by: Glenn Martin                                                *)
(* Solution by: Mike Kujawa                                                *)
(***************************************************************************)

Program Pool;

{ Simple point structure }
Type TPoint = Record
  x, y : Integer;
End;

{ bColinear
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
}
function bColinear(A, B, C : TPoint) : boolean;
Var
  dx1,dy1,dx2,dy2 : longint;

Begin
  dx1 := (B.x - A.x);
  dy1 := (B.y - A.y);
  dx2 := (C.x - A.x);
  dy2 := (C.y - A.y);

  bColinear := (dx1*dy2 = dx2*dy1) AND
               ((dx1 > 0) = (dx2 > 0)) AND
               ((dy1 > 0) = (dy2 > 0));
End;


{ 
   Read them in and test them.  The message is not printed until all of the
   bystanders for a given case are processed to avoid over-reporting hitting
   somebody. 
}
Var
  F : Text;                 { Input file variable }
  N, nBystanders : Integer; { Counts from the input file }
  i, j : Integer;           { Loop variables }
  Cue,                      { Cue ball position }
  Ball,                     { Target ball position }
  Bystander : TPoint;       { Bystander's position }
  bSafe : Boolean;          { Remains true until a bystander is hit }

Begin
  Assign(F, 'pool.in');
  Reset(F);

  { Read in the number of cases }
  Readln(F, N);
  for i := 1 to N do
    Begin
      { Read in the first line of the case }
      Readln(F, Cue.x, Cue.y, Ball.x, Ball.y, nBystanders);
      bSafe := true;
      for j := 1 to nBystanders do
        Begin
          { Read and process each bystander }
          Readln(F, Bystander.x, Bystander.y);
          if bColinear(Cue, Ball, Bystander) then
            bSafe := false;
        End;

      { Output the appropriate message based on bSafe }
      if bSafe then
        Writeln('Go ahead, Spike.  It looks clear.')
      else
        Writeln('Watch out, Spike!  You''re going to hit somebody!');
    End;
End.
