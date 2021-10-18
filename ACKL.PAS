(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Acknowledged                                              *)
(*                                                                         *)
(* Problem by: Richard Russo                                               *)
(* Solution by: Glenn Martin                                               *)
(***************************************************************************)

program ackl;

var infile:text;
    line:string;
    errorFound:boolean;
    numTransaction:integer;
    numM1sPending:integer;
    numM2sPending:integer;

begin
   (* Open the input file *)
   assign(infile, 'ackl.in');
   reset(infile);

   (* Initialize our transaction count *)
   numTransaction:=0;

   (* Read the first line *)
   readln(infile, line);

   (* Repeat until the data ends *)
   while (line <> 'EOF') do
   begin
      (* Assume everything is okay until we detect an error *)
      errorFound:=false;

      (* Initialize counters *)
      numM1sPending:=0;
      numM2sPending:=0;

      (* Print the header for this transaction *)
      inc(numTransaction);
      write('Transaction ', numTransaction, ': ');

      (* Go through the messages until the transaction ends *)
      while (line <> 'EOT') do
      begin
         (* Process the message we just read *)
         if (line = 'm1') then
         begin
            (* Add one to our M1 counter *)
            inc(numM1sPending);

            (* Check to see if what we did was invalid (we sent an m1 when *)
            (* we had one or more already pending)                         *)
            if (numM1sPending >= 2) then
               errorFound:=true;
         end
         else if (line = 'm2') then
         begin
            (* Add one to our M2 counter *)
            inc(numM2sPending);

            (* Check to see if what we did was invalid (we sent an m2 when *)
            (* we had one or more already pending)                         *)
            if (numM2sPending >= 2) then
               errorFound:=true;
         end
         else if (line = 'm12') then
         begin
            (* Add one to both our M1 and M2 counters *)
            inc(numM1sPending);
            inc(numM2sPending);

            (* Check to see if what we did was invalid (we sent an m1 and *)
            (* m2 when we we had one or more m1's and/or m2's already     *)
            (* pending)                                                   *)
            if ( (numM1sPending >= 2) or (numM2sPending >= 2) ) then
               errorFound:=true;
         end
         else if (line = 'a1') then
         begin
            dec(numM1sPending);

            (* Check to see if what we did was invalid (we sent an a1 when *)
            (* we did not have an m1 pending)                              *)
            if (numM1sPending < 0) then
               errorFound:=true;
         end
         else if (line = 'a2') then
         begin
            dec(numM2sPending);

            (* Check to see if what we did was invalid (we sent an a2 when *)
            (* we did not have an m2 pending)                              *)
            if (numM2sPending < 0) then
               errorFound:=true;
         end
         else if (line = 'a12') then
         begin
            (* Remove one from both our M1 and M2 counters *)
            dec(numM1sPending);
            dec(numM2sPending);

            (* Check to see if what we did was invalid (we sent an a1 and  *)
            (* a2 when we we did not have an m1 and/or m2 already pending) *)
            if ( (numM1sPending < 0) or (numM2sPending < 0) ) then
               errorFound:=true;
         end;

         (* Get next message *)
         readln(infile, line);
      end;

      (* Make sure every message was acknowledged *)
      if (numM1sPending > 0) or (numM2sPending > 0) then
         errorFound:=true;

      (* Output whether this transaction was valid or not *)
      if (errorFound) then
         writeln('invalid')
      else
         writeln('valid');
      writeln;

      (* Get first message of new transaction *)
      readln(infile, line);
   end;

   (* Close the input file *)
   close(infile);
end.

