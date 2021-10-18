(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Baby's Big Now!                                           *)
(*                                                                         *)
(* Problem by: Michael Kujawa                                              *)
(* Solution by: Jason Daly                                                 *)
(***************************************************************************)

program baby;

var
    bornDay, bornYear       : integer;
    currentDay, currentYear : integer;
    daysDiff, yearsDiff     : integer;
    totalDiff               : integer;
    fp                      : text;

begin

    {Open the input file}
    assign(fp, 'baby.in');
    reset(fp);

    {Read the first input element}
    read(fp, bornDay);
    while (bornDay <> -1) do
     begin

        {Read the rest of the input on this line}
        readln(fp, bornYear, currentDay, currentYear);

        {Figure out the total difference in days}
        daysDiff := currentDay - bornDay;
        yearsDiff := currentYear - bornYear;
        totalDiff := 365 * yearsDiff + daysDiff;

        if (totalDiff >= 570) then
         begin
            {Output the difference in years}
            writeln(totalDiff DIV 365, ' years');
         end
        else if ((totalDiff < 570) AND (totalDiff >= 30)) then
         begin
            {Output the difference in months}
            writeln(totalDiff DIV 30, ' months');
         end
        else if ((totalDiff < 30) AND (totalDiff >= 14)) then
         begin
            {Output the difference in months}
            writeln(totalDiff DIV 7, ' weeks');
         end
        else
         begin
            {Output the difference in days}
            writeln(totalDiff, ' days');
         end;

         {Read the first input element on the next line}
         read(fp, bornDay);
     end;

     {Close the file}
     close(fp);
end.