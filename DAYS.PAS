(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: These Are Odd Days We Live In                             *)
(*                                                                         *)
(* Problem by: Glenn Martin                                                *)
(* Solution by: Eric Heimburg                                              *)
(***************************************************************************)


program Days;
{translated to pascal from the original C++. By Eric Heimburg again.}
{but I think the pascal version is very nice, I did a good job translating 
 and using the various pascal features like embedded functions, so it 
 should read at least as well as the C++ version. Except reading the input,
 which required some nastiness as compared to the C++ version.}


{this will come in handy at various times: an array of the number of days in each month}
const
  DaysPerMonth : array[1..12] of integer = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);



{returns true iff all the digits of num are odd}
function IsAllOdd(Num : integer) : boolean;
var 
  s : string;
  loop : integer;

  function IsOddDigit(c : char) : boolean; { a little utility function }
  begin
    IsOddDigit := (c = '1') or (c = '3') or (c = '5') or (c = '7') or (c = '9');
  end;

begin
  IsAllOdd := true;
  Str(Num, s);
  for loop := 1 to length(s) do
    if not IsOddDigit(s[ loop ]) then
      IsAllOdd := false;
end;


{*******************************************************************}


{returns true if there is another odd day this year, returns false otherwise.
 If it returns true, then the next odd day will be in Month and Day. If it 
 returns false, then Month and Day will be unchanged. }

function FindNextOddDayThisYear(var Month, Day : integer) : boolean;
var
  AMonth, ADay : integer;
begin
  {well, we will want to fiddle with Month and Day while we calculate the
   next all-odd day this year. But there is a chance that there will not
   be another all-odd day this year. If that is the case, we will return
   false, and will want to leave Month and Day in their original, unaltered
   forms. For this reason, we shall work with copies of Month and Day,
   called AMonth and ADay, and only change Month and Day when we are sure
   that we have another odd day this year.}
   
  AMonth := Month;
  ADay := Day;

  inc(ADay); {go to the next day. Otherwise, if Month/Day is an odd day, we will return this day,}
             {and we need to return the NEXT odd day}

  if (AMonth >= 12) then {well, it's the last month of the year, which is an even month.}
                                     {No way there are more odd days this year!}
    FindNextOddDayThisYear := false
  else
    begin
      if not IsAllOdd(AMonth) then {hey, this is an even month! Make it odd!}
        begin
          inc(AMonth); 
          ADay := 1; {reset day counter}
        end;

      while not IsAllOdd(ADay) do {find the next all-odd day}
        inc(ADay);

      if (ADay > DaysPerMonth[ AMonth ]) then {did we go into the next month?}
        begin
          inc(AMonth);
          ADay := 1;
        end;

      if not IsAllOdd(AMonth) then
        inc(AMonth);

      if AMonth >= 12 then {we may have incremented it so far that it is no longer }
                                         {a valid month, or is December, which is an}
                                         {even month. Either way, bail out, cuz we didnt find an all-odd day}
        FindNextOddDayThisYear := false
      else
        begin
          {okay! Success! We have found the next odd day this year, and it is
           stored in AMonth and ADay. Unfortunately these are temporary
           variables. Store the data in Month and Day}
          Month := AMonth;
          Day := ADay;
          FindNextOddDayThisYear := true;
        end;
    end;
end;



{Figures out the next odd date. Returns this date in Month, Day, and Year.}
procedure FindNextOddDate(var Month, Day, Year : integer);
begin
  if IsAllOdd(Year) and FindNextOddDayThisYear(Month, Day) then
    begin
      {success! Found a nice odd date during the current year
       dont really have to do anything here; Woohoo! }
    end
  else
    begin
      {well, this year has no more odd dates. Find the next all-odd year}
      inc(Year);
      while not IsAllOdd(Year) do
        inc(Year);
      Month := 1;
      Day := 1;
    end;
end;



{*******************************************************************}

{this utility function determines the number of days between two dates
 thus, it returns m1/d1/y1 subtracted from m2/d2/y2, so to speak}
function DateDiff(m1, d1, y1, m2, d2, y2 : integer) : longint;
  var
    Diff : longint;
begin
  {well crap. This is hard. How do we find the number of days 
   between these two dates? Hmm, hmm. Well, there's that way, but it's
   too slow. Well who cares if it's slow? It will work. We will just keep 
   incrementing date one over and over again til it is the same 
   as date two. The number of times we have to increment date 1 is the 
   number of days difference.
   Note to those who care: there are more efficient ways to do this.}

  Diff := 0;

  while not ((m1 = m2) and (d1 = d2) and (y1 = y2)) do
    begin
      inc(d1); {increment day counter}
      if (d1 > DaysPerMonth[ m1 ]) then {hey, is that more days than are in this month?}
        begin
          {yes? well, increment month counter then}
          d1 := 1;
          inc(m1);
          if (m1 > 12) then {hey, is that more months than are in a year?}
            begin
              {yes? well, increment year counter then}
              m1 := 1;
              inc(y1);
            end;
        end;
      inc(Diff);
    end;
  DateDiff := Diff;
end;


{*******************************************************************}

var
  f : text;
  nTests : integer;
  s, s2 : string;
  loop : integer;
  Month, Day, Year, NextMonth, NextDay, NextYear : integer;
  Code : integer;
  temp : integer;
begin
  assign(f, 'days.in');
  reset(f);

  readln(f, nTests);
  for loop := 1 to nTests do
    begin
      readln(f, s);

      {okay, now s has a date in m/d/y format. Parse it! rip it up! Get those
       integers out of it! Wow, the code to do this is so much cleaner in C.
       Oh well...}

      temp := pos('/', s);
      s2 := copy(s, 1, temp-1);

      val(s2, Month, Code);

      delete(s, 1, temp);

      temp := pos('/', s);
      s2 := copy(s, 1, temp-1);

      val(s2, Day, Code);

      delete(s, 1, temp);

      val(s, Year, Code);

      {okay! Month, Day, and Year have been filled.}

      NextMonth := Month;
      NextDay := Day;
      NextYear := Year;
      FindNextOddDate(NextMonth, NextDay, NextYear);

      {okay, we have the current date and the next odd date. Find the diff
       between these dates and print it out, and we're done}
      writeln(DateDiff(Month, Day, Year, NextMonth, NextDay, NextYear));
    end;

  close(f);
end.


