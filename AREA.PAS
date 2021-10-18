(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Ali's Area Code                                           *)
(*                                                                         *)
(* Problem by: Glenn Martin                                                *)
(* Solution by: Jason Daly                                                 *)
(***************************************************************************)

program Area;

var
  ifp : text;
  nNums, i : integer;
  Line : string;

begin
  assign(ifp, 'area.in');
  reset(ifp);

  readln(ifp, nNums);
  for i:= 1 to nNums do
  begin
    readln(ifp, Line);
    if Line[ 1 ] <> '4' then
      write('(407) ');
    writeln(Line);
  end;
  close(ifp);
end.

