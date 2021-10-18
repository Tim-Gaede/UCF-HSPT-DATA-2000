/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Halt!  Who goes there?                                    */
/*                                                                         */
/* Problem by: Jason Daly                                                  */
/* Solution by: Eric Heimburg                                              */
/***************************************************************************/

program Halt;

var
  f : text;
  nTests : integer;
  loop : integer;
  s : string;

begin
  assign(f, 'halt.in');
  reset(f);

  readln(f, nTests);

  for loop:= 1 to nTests do
    begin
      readln(f, s);
      writeln(s, ' will come to a halt.');
      writeln;
    end;

  close(f);
end.
