/***************************************************************************/
/*                      UCF ACM/UPE Fourteenth Annual                      */
/*                    High School Programming Tournament                   */
/*                                                                         */
/* Problem Name: Bounding Rects                                            */
/*                                                                         */
/* Problem by: Phillip Dexheimer                                           */
/* Solution by: Paulius Micikevicious                                      */
/***************************************************************************/




//  Bounding recatangle

// all that you need to do find the bouding rectangle area is:
//   find the minimum and maximum x and y coordinates (corneres)
//   find the lengths of the sides (difference between max and min
//   multiply the lengths together to get the area

#include <fstream.h>

void main()
{
	int i, j, v, N;
	long x, y, xmin, ymin, xmax, ymax;
	unsigned long length, height, area;
	// input file
	ifstream inputfile("rect.in");

	inputfile>>N;

	for(i=1;i<=N;i++)
	{
		inputfile>>v;
		
		// use the first point as the minimum and the maximum
		inputfile>>x>>y;
		v--;
		xmin=xmax=x;
		ymin=ymax=y;

		for(j=0;j<v;j++)
		{
			inputfile>>x>>y;
			if(x>xmax)
				xmax=x;

			if(x<xmin)
				xmin=x;

			if(y>ymax)
				ymax=y;

			if(y<ymin)
				ymin=y;
		}

		length=xmax-xmin;
		height=ymax-ymin;
		area=length*height;

		cout<<"The bounding rect of polygon "<<i<<" has area "<<area<<"."<<endl;
	}

	inputfile.close();
}