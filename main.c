#include <stdio.h>
#include <stdlib.h>
#include <plot.h>
#include "bstr.h" 

static plPlotter *plotter;

void drawolliehead(plPlotter *, int, int, int);

void usage(const char *);

#define POINTING_RIGHT	0
#define POINTING_LEFT	1

#define MODE_BOX_SYMM	0
#define MODE_BOX_CLOSED	1

#define X_GAP	25

int drawfingers_sym_startwi(int, int, int, int, int, int);
int drawfingers_sym_startwo(int, int, int, int, int, int);
int drawfingers_closed(int, int, int, int, int, int);
int drawfingers_open(int, int, int, int, int, int);

#define BEFORE_LEN	500
#define GAP_LEN		200

int
main(int argc, char **argv)
{
	int	matwidth;
	int	matthick;
	int	fingercnt;
	int	mode;

	plPlotterParams *plotter_params;

	if(argc != 5) {
		usage(argv[0]);
		exit(-1);
	}

	mode = MODE_BOX_SYMM;

	if(!xstrcmp(argv[1], "box_symm"))
		mode = MODE_BOX_SYMM;
	else
	if(!xstrcmp(argv[1], "box_closed"))
		mode = MODE_BOX_CLOSED;
	else {
		fprintf(stderr, "Invalid mode specified.\n");
		exit(-1);
	}

	matwidth = atoi(argv[2]) * 10;
	matthick = atoi(argv[3]) * 10;
	fingercnt = atoi(argv[4]);

	if(matwidth == 0) {
		fprintf(stderr, "Invalid material width specified.\n");
		exit(-1);
	}

	if(matthick == 0) {
		fprintf(stderr, "Invalid material thickness specified.\n");
		exit(-1);
	}

	if(fingercnt == 0) {
		fprintf(stderr, "Invalid finger count specified.\n");
		exit(-1);
	}
     
       /* set page size parameter, including viewport size and location */
       plotter_params = pl_newplparams ();
       pl_setplparam (plotter_params, "PAGESIZE",
                      "letter,xsize=8.5in,ysize=11in,xorigin=0in,yorigin=0in");
     
       /* create a Postscript Plotter with the specified parameter */
       plotter = pl_newpl_r ("ps", stdin, stdout, stderr, plotter_params);
     
       pl_openpl_r (plotter);                /* begin page of graphics */

       pl_space_r (plotter,
                    0, 0, 2159, 2794);   /* set user coor system, this time
					  * use dims convenient for tenths of
					  * mm */

	if(mode == MODE_BOX_SYMM) {

		(void) drawfingers_sym_startwi(0, 0, POINTING_RIGHT, fingercnt,
		    matwidth, matthick);
		(void) drawfingers_sym_startwo(BEFORE_LEN + matthick + GAP_LEN,
		    0, POINTING_LEFT, fingercnt, matwidth, matthick);

	} else
	if(mode == MODE_BOX_CLOSED) {

		(void) drawfingers_open(0, 0, POINTING_RIGHT, fingercnt,
		    matwidth, matthick);
		(void) drawfingers_closed(BEFORE_LEN + matthick + GAP_LEN, 0,	
		    POINTING_LEFT, fingercnt, matwidth, matthick);

	}


	pl_closepl_r (plotter);               /* end page of graphics */
	pl_deletepl_r (plotter);	      /* delete Plotter */

	return 0;

}


void
usage(const char *execn)
{
	printf("Usage: %s <type> <material_width_mm> <material_thickness_mm>"
	    " <finger_count>\n\n", execn);
	printf("Supported types are: box_symm, box_closed\n");
}


int
drawfingers_sym_startwi(int x, int y, int dir, int fingercnt, int matwidth,
	int matthick)
{
	int	i;
	double	fingerlen;

	fingerlen = (double) matwidth / (fingercnt * 2);

	if(dir == POINTING_RIGHT) {
		pl_line_r(plotter,
		    x,
		    y,
		    x + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x,
		    y + matwidth,
		    x + BEFORE_LEN,
		    y + matwidth);

		for(i = 0; i < fingercnt; ++i) {

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen),
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen));

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen),
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);
		}

	} else { /* POINTING_LEFT */

		pl_line_r(plotter,
		    x + matthick,
		    y,
		    x + matthick + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x + matthick,
		    y + matwidth,
		    x + matthick + BEFORE_LEN,
		    y + matwidth);


		for(i = 0; i < fingercnt; ++i) {

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen),
			    x,
			    (double) y + (i * 2 * fingerlen));

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen),
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);
		}
	}

	return 0;
}


int
drawfingers_sym_startwo(int x, int y, int dir, int fingercnt, int matwidth,
	int matthick)
{
	int	i;
	double	fingerlen;

	fingerlen = (double) matwidth / (fingercnt * 2);

	if(dir == POINTING_RIGHT) {
		pl_line_r(plotter,
		    x,
		    y,
		    x + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x,
		    y + matwidth,
		    x + BEFORE_LEN,
		    y + matwidth);

		for(i = 0; i < fingercnt; ++i) {

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen),
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);
		}

	} else { /* POINTING_LEFT */

		pl_line_r(plotter,
		    x + matthick,
		    y,
		    x + matthick + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x + matthick,
		    y + matwidth,
		    x + matthick + BEFORE_LEN,
		    y + matwidth);


		for(i = 0; i < fingercnt; ++i) {

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen),
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);
		}
	}

	return 0;
}


int
drawfingers_closed(int x, int y, int dir, int fingercnt, int matwidth,
	int matthick)
{
	int	i;
	double	fingerlen;

	fingerlen = (double) matwidth / (fingercnt * 2 + 1);

	if(dir == POINTING_RIGHT) {
		pl_line_r(plotter,
		    x,
		    y,
		    x + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x,
		    y + matwidth,
		    x + BEFORE_LEN,
		    y + matwidth);

		for(i = 0; i < fingercnt + 1; ++i) {

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen),
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen));

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen),
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			if(i >= fingercnt) {
			 	break;
			}

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);

			/* The X */
			pl_fline_r(plotter,
			    x + BEFORE_LEN + X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen +
			    X_GAP,
			    x + BEFORE_LEN + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen  * 2 -
			    X_GAP);
			pl_fline_r(plotter,
			    x + BEFORE_LEN + X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2 -
			    X_GAP,
			    x + BEFORE_LEN + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen 
			    + X_GAP);
		}

	} else { /* POINTING_LEFT */

		pl_line_r(plotter,
		    x + matthick,
		    y,
		    x + matthick + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x + matthick,
		    y + matwidth,
		    x + matthick + BEFORE_LEN,
		    y + matwidth);


		for(i = 0; i < fingercnt + 1; ++i) {

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen),
			    x,
			    (double) y + (i * 2 * fingerlen));

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen),
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			if(i >= fingercnt)
				break;

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);

			/* The X */
			pl_fline_r(plotter,
			    x + X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen +
			    X_GAP,
			    x + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2 -
			    X_GAP);
			pl_fline_r(plotter,
			    x + X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2 -
			    X_GAP,
			    x + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen +
			    X_GAP);
		}
	}

	return 0;
}


int
drawfingers_open(int x, int y, int dir, int fingercnt, int matwidth,
	int matthick)
{
	int	i;
	double	fingerlen;

	fingerlen = (double) matwidth / (fingercnt * 2 + 1);

	if(dir == POINTING_RIGHT) {
		pl_line_r(plotter,
		    x,
		    y,
		    x + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x,
		    y + matwidth,
		    x + BEFORE_LEN,
		    y + matwidth);

		for(i = 0; i < fingercnt + 1; ++i) {

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen),
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			/* The X */
			pl_fline_r(plotter,
			    x + BEFORE_LEN + X_GAP,
			    (double) y + (i * 2 * fingerlen) + X_GAP,
			    x + BEFORE_LEN + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen -
			    X_GAP);
			pl_fline_r(plotter,
			    x + BEFORE_LEN + X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen -
			    X_GAP,
			    x + BEFORE_LEN + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + X_GAP);

			if(i >= fingercnt)
				break;

			pl_fline_r(plotter,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);

			pl_fline_r(plotter,
			    x + BEFORE_LEN + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2,
			    x + BEFORE_LEN,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);
		}

	} else { /* POINTING_LEFT */

		pl_line_r(plotter,
		    x + matthick,
		    y,
		    x + matthick + BEFORE_LEN,
		    y);
		pl_line_r(plotter,
		    x + matthick,
		    y + matwidth,
		    x + matthick + BEFORE_LEN,
		    y + matwidth);

		for(i = 0; i < fingercnt + 1; ++i) {

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen),
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			/* The X */
			pl_fline_r(plotter,
			    x + X_GAP,
			    (double) y + (i * 2 * fingerlen) + X_GAP,
			    x + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen -
			    X_GAP);
			pl_fline_r(plotter,
			    x + X_GAP,
			    (double) y + (i * 2 * fingerlen) + fingerlen -
			    X_GAP,
			    x + matthick - X_GAP,
			    (double) y + (i * 2 * fingerlen) + X_GAP);

			if(i >= fingercnt)
				break;

			pl_fline_r(plotter,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen);

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);

			pl_fline_r(plotter,
			    x,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2,
			    x + matthick,
			    (double) y + (i * 2 * fingerlen) + fingerlen * 2);
		}
	}

	return 0;
}


