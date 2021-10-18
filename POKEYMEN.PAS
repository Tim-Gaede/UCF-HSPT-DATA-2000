(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Gotta Fetch 'em All!                                      *)
(*                                                                         *)
(* Problem by: Jason Daly                                                  *)
(* Solution by: Phillip Dexheimer                                          *)
(***************************************************************************)

program pokeymen;

{I just ported this from Richard's C solution.  About the only thing that
 I did differently was to use enumerations (one of the nice things about
 pascal)}

type
  element_type = (fire, water, earth, air, electricity, poison, psychics, fighting);
  pokeymen_desc = record
                    name : string;
                    level : integer;
                    element : element_type;
                  end;
  pokeymen_array = array[1..100] of pokeymen_desc;
  boolean_array = array[1..100] of boolean;

const
  element_names :
      array[fire..fighting] of string =
          ('fire', 'water', 'earth', 'air', 'electricity', 'poison',
           'psychics', 'fighting');

var
  Infile : text;
  nash_pokeymen : pokeymen_array;
  num_pokeymen : integer;
  i, count, num_enemies : integer;
  used : boolean_array;
  level, index : integer;
  elem, levstr : string;

function get_enumeration(elem : string) : element_type;
var
  element, return_value : element_type;
begin
  for element := fire to fighting do
    if (element_names[element] = elem) then
      return_value := element;
  get_enumeration := return_value;
end;

function get_rel_elem_adv(e1 : element_type; e2 : element_type) : integer;
var
  retval : integer;
begin
  retval := 0;
  case (e1) of
    fire        : if (earth = e2) then retval := 1;
    water       : if (fire = e2) then retval := 1;
    earth       : if (electricity = e2) then retval := 1;
    air         : if (earth = e2) then retval := 1;
    electricity : if (water = e2) then retval := 1;
    poison      : if ((fire = e2) OR (earth = e2)
	          OR (water = e2) OR (air = e2)) then
                     retval := 1;
    psychics    : if (psychics <> e2) then retval := 1;
    { FIGHTING is always a 0 advantage }
  end;

  get_rel_elem_adv := retval;
end;

function get_rel_pokeymen_adv(var p1 : pokeymen_desc; var p2 : pokeymen_desc) : integer;
var
  adv : integer;
begin
  adv := 0;
  adv := get_rel_elem_adv (p1.element, p2.element);
  adv := adv - get_rel_elem_adv (p2.element, p1.element);

  adv := adv + p1.level;
  adv := adv - p2.level;

  get_rel_pokeymen_adv := adv;
end;

function get_best_pokeymen(elem : string; level : integer) : integer;
var
  p : pokeymen_desc;
  rel_adv, best_idx, best, count : integer;
begin
  p.name := '';
  p.level := level;
  p.element := get_enumeration(elem);

  best := -30;
  for count := 1 to num_pokeymen do
   begin
    if (not used[count]) then
     begin
      rel_adv := get_rel_pokeymen_adv(nash_pokeymen[count], p);

      if best <= 0 then
       begin
         if ( (rel_adv > 0) or (abs (rel_adv) < abs (best)) ) then
	  begin
	   best_idx := count;
	   best := rel_adv;
	  end;
       end;

      if ( (best > 0) and (rel_adv < best) and (rel_adv > 0) ) then
       begin
        best_idx := count;
	best := rel_adv;
       end;

     end;
   end;
  get_best_pokeymen := best_idx;
end;

procedure get_nashs_pokeymen;
var
  count  : integer;
  buffer : string;
  elem_name : string;
begin
  for count := 1 to num_pokeymen do
   begin
    readln(infile, buffer);
    nash_pokeymen[count].name := copy(buffer, 1, pos(' ', buffer)-1);
    delete(buffer, 1, pos(' ', buffer));
    elem_name := copy(buffer, 1, pos(' ', buffer)-1);
    nash_pokeymen[count].element := get_enumeration(elem_name);
    delete(buffer, 1, pos(' ', buffer));
    nash_pokeymen[count].level := ord(buffer[1]) - ord('0');
   end;

end;

begin
  assign(infile, 'pokeymen.in');
  reset(infile);

  readln(infile, num_pokeymen);

  while (num_pokeymen > 0) do
   begin
     for i := 1 to num_pokeymen do
       used[i] := false;
     get_nashs_pokeymen;
     writeln('********************');
     writeln;
     readln(infile, num_enemies);
     for count := 1 to num_enemies do
      begin
        readln(infile, elem);
        levstr := copy(elem, pos(' ', elem), length(elem)-pos(' ', elem)+1);
        delete(elem, pos(' ', elem), length(elem)-pos(' ', elem)+1);
        delete(levstr, 1, 1);
        level := ord(levstr[1]) - ord('0');

        index := get_best_pokeymen(elem, level);

        used[index] := true;

        writeln('Match ', count, ': ', nash_pokeymen[index].name, ', I choose you!');
        writeln;
      end;
     readln(infile, num_pokeymen);
   end;

  close(infile);
end.