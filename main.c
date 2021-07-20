#include <stdio.h>
#include <stdlib.h>
#include <plot.h>
#include <math.h>
#include "bstr.h" 

static plPlotter *plotter;

static int ang = 0;
static double curx = 0;
static double cury = 0;

void fw(int);
void tl(int);
void tr(int);


int
main(int argc, char **argv)
{

	plPlotterParams *plotter_params;

	/* set page size parameter, including viewport size and location */
	plotter_params = pl_newplparams ();
	pl_setplparam (plotter_params, "PAGESIZE",
	    "letter,xsize=8.5in,ysize=11in,xorigin=0in,yorigin=0in");
     
	/* create a Postscript Plotter with the specified parameter */
	plotter = pl_newpl_r ("ps", stdin, stdout, stderr, plotter_params);
     
	pl_openpl_r (plotter);                /* begin page of graphics */

	pl_space_r (plotter, 0, 0, 2159, 2794);   /* set user coor system,
						   * this time use dims
						   * convenient for tenths of
						   * mm */


/*
	for(int t = 0; t < 36; ++t) {
		for(int i = 0; i < 360; ++i) {
			fw(10);
			tr(1);
		}
		fw(30);
		tr(10);
	}
*/

/*

	for(int t = 0; t < 24; ++t) {
		fw(500);
		tr(90);
		fw(500);
		tr(90);
		fw(500);
		tr(90);
		fw(500);
		tr(90);

		//fw(60);
		tr(15);
	}

*/

/*
	fw(250);
	tr(60);
	fw(250);
	tl(180);
	fw(250);
	tr(60);
	fw(250);
*/	

	fw(250);
	tl(60);
	fw(250);
	tl(120);
	fw(125);
	tl(60);
	fw(125);
	tr(60);
	fw(125);
	tl(60);
	fw(125);
	tl(120);

	fw(250);
	tr(60);
	fw(250);
	tr(120);
	fw(125);
	tr(60);
	fw(125);
	tl(60);
	fw(125);
	tr(60);
	fw(125);
	tr(120);

	fw(250);
	tr(60);
	fw(250);
	tl(120);
	fw(125);
	tl(60);
	fw(125);
	tr(60);
	fw(125);
	tl(60);
	fw(125);
	


	pl_closepl_r(plotter);               /* end page of graphics */
	pl_deletepl_r(plotter);	      /* delete Plotter */

	return 0;

}


void
fw(int dist)
{
	double	newx;
	double	newy;

fprintf(stderr, "ang=%d\n", ang);

	newx = curx + dist * sin((double)ang * M_PI / 180);
	newy = cury + dist * cos((double)ang * M_PI / 180);

fprintf(stderr, "%f, %f, %f, %f\n", curx, cury, newx, newy);

	pl_fline_r(plotter, curx, cury, newx, newy);
	
	curx = newx;
	cury = newy;
}


void
tr(int deg)
{
	ang += deg;
	ang = ang % 360;
}


void
tl(int deg)
{
	ang -= (deg % 360);
	if(ang < 0)
		ang = ang + 360;
}



void
usage(const char *execn)
{
	printf("Usage: %s <type> <material_width_mm> <material_thickness_mm>"
	    " <finger_count>\n\n", execn);
	printf("Supported types are: box_symm, box_closed\n");
}


