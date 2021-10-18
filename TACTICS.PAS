(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Ultimate Fantasy Tactics                                  *)
(*                                                                         *)
(* Problem by: Richard Russo                                               *)
(* Solution by: Phillip Dexheimer                                          *)
(***************************************************************************)

program tactics;

{I have a very long and detailed comment concerning this solution in
 tactics.cpp.  The only thing that might cause a problem with you, and
 the only non-compatability with pascal, is that C is 0-based (ie, counting
 starts with 0 instead of 1).  Anyway, this solution is basically just a port
 from C, so it all holds.}

type
  arraytype = array [1..10] of integer;

var
  party, enemy, attack : arraytype;
  nParty, nEnemy, nKills : integer;
  setnum, i : integer;
  WDF, LDF : real;
  Infile : text;
  nComb, l : longint;
  outputicky : string;

procedure ConsiderPossibility (possibility : longint);

var
  localEnemy, localAttack : arraytype;
  localWDF, localLDF : real;
  idx, localKills : integer;

begin
  for idx := 1 to 10 do
    localEnemy[idx] := enemy[idx];
  idx := nParty;
  while (idx >= 1) do
   begin
    localAttack[idx] := possibility mod nEnemy + 1;
    possibility := possibility div nEnemy;
    dec(idx);
   end;
  for idx := 1 to nParty do
    localEnemy[localAttack[idx]] := localEnemy[localAttack[idx]] - party[idx];
  localKills := 0;
  localWDF := 0;
  localLDF := 0;
  for idx := 1 to nEnemy do
   begin
    if LocalEnemy[idx] <= 0 then
     begin
      inc(LocalKills);
      LocalWDF := LocalWDF - localEnemy[idx]/enemy[idx];
     end
    else
      LocalLDF := LocalLDF + localEnemy[idx]/enemy[idx];
   end;
  if (localKills > nKills) then
   begin
    for idx := 1 to 10 do
      attack[idx] := localAttack[idx];
    nKills := LocalKills;
    WDF := localWDF;
    LDF := localLDF;
   end
  else if (localKills = nKills) and (localWDF < WDF) then
   begin
    for idx := 1 to 10 do
      attack[idx] := localAttack[idx];
    nKills := LocalKills;
    WDF := localWDF;
    LDF := localLDF;
   end
  else if (localKills = nKills) and (abs(WDF-localWDF) < 1E-6) and (localLDF < LDF) then
   begin
    for idx := 1 to 10 do
      attack[idx] := localAttack[idx];
    nKills := LocalKills;
    WDF := localWDF;
    LDF := localLDF;
   end
end;

begin
  assign(infile, 'tactics.in');
  reset(infile);
  nParty := 3;
  setnum := 0;
  while (nParty <> 0) do
   begin
    read(infile, nparty);
    if (nparty <> 0) then
     begin
      inc(setnum);
      for i := 1 to nParty do
	read(infile, party[i]);
      readln(infile);
      read(infile, nEnemy);
      for i := 1 to nEnemy do
	read(infile, enemy[i]);
      readln(infile);

      nKills := 0;
      WDF := 1e30;
      LDF := 1e30;
      nComb := 1;
      for i := 1 to nParty do
	nComb := nComb * nEnemy;
      for l := 0 to nComb do
	ConsiderPossibility(l);

{Oh, yeah.  The output in pascal is *ugly*}
      writeln ('+==========================================+');
      str(setnum, outputicky);
      write ('| Battle #', outputicky);
      for i := 42 downto (10+Length(outputicky)) do
	write (' ');
      writeln ('|');
      writeln ('+==========================================+');
      writeln ('| Party Member        Enemy                |');
      writeln ('| ------------        -----                |');
      for i := 1 to nParty do
	writeln ('| ', i, '                   ', attack[i], '                    |');
      writeln ('+==========================================+');
      str(WDF:0:3, outputicky);
      write ('| WDF: ', outputicky);
      for i := 19 downto (5+Length(outputicky)) do
	write(' ');
      str(LDF:0:3, outputicky);
      write ('LDF: ', outputicky);
      for i := 20 downto (5+Length(outputicky)) do
	write(' ');
      writeln ('|');
      writeln ('+==========================================+');
      writeln;
     end;
   end;
end.