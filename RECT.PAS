(***************************************************************************)
(*                      UCF ACM/UPE Fourteenth Annual                      *)
(*                    High School Programming Tournament                   *)
(*                                                                         *)
(* Problem Name: Bounding Rects                                            *)
(*                                                                         *)
(* Problem by: Phillip Dexheimer                                           *)
(* Solution by: Paulius Micikevicious                                      *)
(***************************************************************************)

{$N+}

(*  Bounding recatangle

  all that you need to do find the bouding rectangle area is:
   find the minimum and maximum x and y coordinates (corneres)
   find the lengths of the sides (difference between max and min
   multiply the lengths together to get the area
*)

program rect;
var
   i, j, v, N:integer;
   x, y, xmin, ymin, xmax, ymax:longint;
   length, height, area:longint;
   inputfile:text;


begin
     assign(inputfile,'rect.in');
     reset(inputfile);
     readln(inputfile, N);

     for i:=1 to N do
     begin
          readln(inputfile,v);

	  readln(inputfile,x,y);
	  v:=v-1;

	  xmin:=x;
          xmax:=x;
	  ymin:=y;
          ymax:=y;

	  for j:=1 to v do
	  begin
	       readln(inputfile, x, y);
	       if x>xmax then
	          xmax:=x;

	       if x<xmin then
	          xmin:=x;

	       if y>ymax then
	          ymax:=y;

	       if y<ymin then
                  ymin:=y;
	  end;

	  length:=xmax-xmin;
	  height:=ymax-ymin;
	  area:=length*height;

	  writeln('The bounding rect of polygon ',i,' has area ',area,'.');
     end;

     close(inputfile);
end.