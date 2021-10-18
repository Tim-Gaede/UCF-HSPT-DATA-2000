(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Secret Judging League                                     *)
(*                                                                         *)
(* Problem by: Glenn Martin and Michael Smith                              *)
(* Solution by: Phillip Dexheimer                                          *)
(***************************************************************************)

program league;

const
  names :array [1..3,'A'..'Z'] of string =
(('Stinky',
'Lumpy',
'Buttercup',
'Gidget',
'Crusty',
'Greasy',
'Fluffy',
'Cheeseball',
'Chim-Chim',
'Poopsie',
'Flunky',
'Booger',
'Pinky',
'Zippy',
'Goober',
'Doofus',
'Slimy',
'Loopy',
'Snotty',
'Falafel',
'Dorkey',
'Squeezit',
'Oprah',
'Skipper',
'Dinky',
'Zsa-Zsa'),
('Diaper',
'Toilet',
'Giggle',
'Bubble',
'Girdle',
'Barf',
'Lizard',
'Waffle',
'Cootie',
'Monkey',
'Potty',
'Liver',
'Banana',
'Rhino',
'Burger',
'Hamster',
'Toad',
'Gizzard',
'Pizza',
'Gerbil',
'Chicken',
'Pickle',
'Chuckle',
'Tofu',
'Gorilla',
'Stinker'),
('head',
'mouth',
'face',
'nose',
'tush',
'breath',
'pants',
'shorts',
'lips',
'honker',
'butt',
'brain',
'tushie',
'chunks',
'hiney',
'biscuits',
'toes',
'buns',
'fanny',
'sniffer',
'sprinkles',
'kisser',
'squirt',
'humperdinck',
'brains',
'juice'));

var
  Infile : text;
  line, outname : string;
  i, N : integer;

begin
  assign(Infile, 'league.in');
  reset(Infile);
  readln(infile, N);
  for i := 1 to N do
   begin
     delete(outname, 1, length(outname));
     readln(infile, line);
     outname := outname + names[1, upcase(line[1])];
{This was slightly harder than in C.  I just deleted all the middle names,
 and then decided I was at the last name.  This is slightly different from
 my C solution, where I just looked from the end of the line backward}
     while (pos(' ', line) > 0) do
       delete(line, 1, pos(' ', line));
     outname := outname + ' ' + names[2, upcase(line[1])];
     outname := outname + names[3, upcase(line[length(line)])];
     writeln(outname);
   end;
  close(infile);
end.