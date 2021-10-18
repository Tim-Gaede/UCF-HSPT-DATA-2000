(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Cinco de Mayo                                             *)
(*                                                                         *)
(* Problem by: Glenn Martin                                                *)
(* Solution by: Jason Daly                                                 *)
(***************************************************************************)

program mayo;

var
    fp        : text;
    numWeeks  : integer;
    numMeals  : integer;
    mealPiece : string[255];
    mayoCount : integer;
    inChar    : char;
    i, j      : integer;

begin
    assign(fp, 'mayo.in');
    reset(fp);

    { Read the number of weeks to process }
    readln(fp, numWeeks);

    for i:=1 to numWeeks do
     begin

        mayoCount := 0;

        { Read the number of meals for this week }
        readln(fp, numMeals);

        for j:=1 to numMeals do
         begin

            { Initialize the ingredient string }
            mealPiece := '';
            inChar := #0;

            { Read the meal line, one ingredient at a time }
            while not eoln(fp) do
             begin

                { Read the next character }
                read(fp, inChar);

                if (inChar = ' ') then
                 begin

                    { We're done with this ingredient, is it mayo? }
                    if ((mealPiece = 'mayo') OR
                        (mealPiece = 'mayonnaise')) then
                     begin
                        mayoCount := mayoCount + 1;
                     end;

                     { Move on to the next ingredient }
                     mealPiece := '';
                 end
                else
                 begin

                     { Add this character to the ingredient string }
                     mealPiece := mealPiece + inChar;
                 end;
              end;

             { Check the last ingredient on the line to see if it's mayo }
             if ((mealPiece = 'mayo') OR
                 (mealPiece = 'mayonnaise')) then
              begin
                 mayoCount := mayoCount + 1;
              end;

             { Next meal, please }
             mealPiece := '';
             readln(fp);
         end;

        { Print the output for this week }
        if (mayoCount >= 5) then
         begin
            writeln('Week #', i,': Cinco de Mayo!');
            writeln;
         end
        else
         begin
            writeln('Week #', i,': Way to go, Mason!');
            writeln;
         end;

     end;

    close(fp);
end.