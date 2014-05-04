/* 2-D Low-rank One-step Pre-stack Reverse-Time-Migration
     img1 :  crosscorrelation (stdout)
     img2 :  crosscorrelation with source normalization

*/
/*
  Copyright (C) 2014 University of Texas at Austin
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <rsf.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include "lrosutildbg.h"


int main(int argc, char* argv[]) 
{
    clock_t tstart,tend;
    double duration;

    /*flag*/
    bool verb;
    bool wantwf;
    bool wantrecord; // actually means "need record"
    
    /*I/O*/
    sf_file Fvel;
    sf_file left, right, leftb, rightb;
    sf_file Fsrc,/*wave field*/ Frcd/*record*/;
    sf_file Ftmpwf, Ftmpbwf;
    sf_file Fimg1, Fimg2;

    sf_axis at, ax, az;

    /*grid index variables*/
    int nx, nz, nt, wfnt;
    int nzx, nx2, nz2, n2, m2, pad1, nk;
    int ix, it;
    int nxb, nzb;
    float dt, dx, dz, wfdt;
    float ox, oz;

    /*source/geophone location*/
    float slx, slz;
    int   spx, spz;
    float gdep;
    int   gp;

    /*Model*/
    sf_complex **lt, **rt;
    sf_complex **ltb, **rtb;

    /*Data*/
    float ***wavefld;
    sf_complex **record;
    float **img1, **img2;
    int snpint;

    /*source*/
    bool srcdecay;
    int srcrange;
    float srctrunc;
    
    /*abc boundary*/
    int top,bot,lft,rht;

    /*memoray*/
//    float memneed;
    int tmpint;

    tstart = clock();
    sf_init(argc, argv);
    if (!sf_getbool("verb", &verb)) verb=false; /*verbosity*/
    if (!sf_getbool("wantwf", &wantwf)) wantwf=false; /*output forward and backward wavefield*/
    if (!sf_getbool("wantrecord", &wantrecord)) wantrecord=true; /*if n, using record data generated by this program */

    /*Set I/O file*/
    Fvel  = sf_input("vel");  /*velocity - just for model dimension*/
    Fsrc  = sf_input("in");   /*source wavelet*/
    if (wantrecord) {
	Frcd   = sf_input("rec");   /*record from elsewhere*/
    } else {
	Frcd   = sf_output("rec");   /*record produced by forward modeling*/
    }
    Fimg1  = sf_output("out");   /*Imaging*/
    Fimg2  = sf_output("img2");  /*Imaging*/

    if (wantwf) {
	Ftmpwf  = sf_output("tmpwf");/*wavefield snap*/
	Ftmpbwf = sf_output("tmpbwf");
    } else {
	Ftmpwf  = NULL;
	Ftmpbwf = NULL;
    }

    /*--- parameters of source ---*/
    srcpar srcp;
    srcp = createsrc();
    at = sf_iaxa(Fsrc, 1); nt = sf_n(at);  dt = sf_d(at);      
    if (!sf_getbool("srcdecay", &srcdecay)) srcdecay=SRCDECAY;
    /*source decay*/
    if (!sf_getint("srcrange", &srcrange)) srcrange=SRCRANGE;
    /*source decay range*/
    if (!sf_getfloat("srctrunc", &srctrunc)) srctrunc=SRCTRUNC;
    /*trunc source after srctrunc time (s)*/
    srcp->nt = nt; srcp->dt = dt; 
    srcp->decay = srcdecay; srcp->range=srcrange; srcp->trunc=srctrunc;
    loadsrc(srcp, Fsrc);

    /*--- Model axes ---*/
    az = sf_iaxa(Fvel, 1); nzb = sf_n(az); dz = sf_d(az); oz = sf_o(az);
    ax = sf_iaxa(Fvel, 2); nxb = sf_n(ax); dx = sf_d(ax); ox = sf_o(ax);

    /* propagator matrices */
    left  = sf_input("left");
    right = sf_input("right");
    leftb  = sf_input("leftb");
    rightb = sf_input("rightb");

    if (!sf_getint("pad1",&pad1)) pad1=1; /* padding factor on the first axis */
    nz2 = kiss_fft_next_fast_size(nzb*pad1);
    nx2 = kiss_fft_next_fast_size(nxb);
    nk = nz2*nx2;

    nzx = nzb*nxb;
    /* nzx2 = nz2*nx2; */

    if (!sf_histint(left,"n1",&n2) || n2 != nzx) sf_error("Need n1=%d in left",nzx);
    if (!sf_histint(left,"n2",&m2))  sf_error("Need n2= in left");
    
    if (!sf_histint(right,"n1",&n2) || n2 != m2) sf_error("Need n1=%d in right",m2);
    if (!sf_histint(right,"n2",&n2) || n2 != nk) sf_error("Need n2=%d in right",nk);
  
    lt = sf_complexalloc2(nzx,m2);
    rt = sf_complexalloc2(m2,nk);
    sf_complexread(lt[0],nzx*m2,left);
    sf_complexread(rt[0],m2*nk,right);


    ltb = sf_complexalloc2(nzx,m2);
    rtb = sf_complexalloc2(m2,nk);
    sf_complexread(ltb[0],nzx*m2,leftb);
    sf_complexread(rtb[0],m2*nk,rightb);

//    sf_fileclose(left);
//    sf_fileclose(right);

    /* abc parameters */
    if (!sf_getint("top", &top)) top=40;
    if (!sf_getint("bot", &bot)) bot=40;
    if (!sf_getint("lft", &lft)) lft=40;
    if (!sf_getint("rht", &rht)) rht=40;
    /* Width of abc layer */

    nz = nzb - top - bot;
    nx = nxb - lft - rht;

    /*Geometry parameters*/
    geopar geop;
    geop = creategeo();
 
    /*source loaction parameters*/
    
    if (!sf_getfloat("slx", &slx)) slx=-1.0; 
    /*source location x */
    if (!sf_getint("spx", &spx)) spx = -1;
    /*source location x (index)*/
    if((slx<0 && spx <0) || (slx>=0 && spx >=0 ))  sf_error("Need src location");
    if (slx >= 0 )    spx = (int)((slx-ox)/dx+0.5);
    
    if (!sf_getfloat("slz", &slz)) slz=-1.0;
    /* source location z */
    if (!sf_getint("spz", &spz)) spz = -1;
    /*source location z (index)*/
    if((slz<0 && spz <0) || (slz>=0 && spz >=0 ))  sf_error("Need src location");
    if (slz >= 0 )    spz = (int)((slz-ox)/dz+0.5);
    
    if (!sf_getfloat("gdep", &gdep)) gdep=-1.0;
    /* recorder depth on grid*/
    if (!sf_getint("gp", &gp)) gp=0;
    /* recorder depth on index*/
    if ( gdep>=oz) { gp = (int)((gdep-oz)/dz+0.5);}
    if (gp < 0.0) sf_error("gdep need to be >=oz");
    /*source and receiver location*/
    if (!sf_getint("snapinter", &snpint)) snpint=10;
    /* snap interval */

    /*check record data*/
    if (wantrecord){
	sf_histint(Frcd,"n1", &tmpint);
	if (tmpint != nt ) sf_error("Error parameter n1 in record!");
	sf_histint(Frcd,"n2", &tmpint);
	if (tmpint != nx ) sf_error("Error parameter n2 in record!");
    }
    
    geop->nx  = nx;
    geop->nz  = nz;
    geop->nxb = nxb;
    geop->nzb = nzb;
    geop->dx  = dx;
    geop->dz  = dz;
    geop->ox  = ox;
    geop->oz  = oz;
    geop->snpint = snpint;
    geop->spx = spx;
    geop->spz = spz;
    geop->gp = gp;
    geop->top = top;
    geop->bot = bot;
    geop->lft = lft;
    geop->rht = rht;

    /* wavefield and record  */
    wfnt = (int)(nt-1)/snpint+1;
    sf_warning("nt=%d; snpint=%d; wfnt=%d!!!\n",nt,snpint,wfnt);
    wfdt = dt*snpint;
    record = sf_complexalloc2(nt, nx);
    sf_warning("fine!!!");

    wavefld = sf_floatalloc3(nz, nx, wfnt);

    sf_warning("fine!!!");

/*
    if (wantwf)
	wavefld2= sf_floatalloc3(nz, nx, wfnt);
    else
	wavefld2=NULL;
*/

    /*image*/
    img1 = sf_floatalloc2(nz, nx);
    img2 = sf_floatalloc2(nz, nx);

    if (verb) {
	sf_warning("============================");
	sf_warning("nx=%d nz=%d nt=%d", geop->nx, geop->nz, srcp->nt);
	sf_warning("nxb=%d nzb=%d ", geop->nxb, geop->nzb);
	sf_warning("dx=%f dz=%f dt=%f", geop->dx, geop->dz, srcp->dt);
	sf_warning("top=%d bot=%d lft=%d rht=%d", geop->top, geop->bot, geop->lft, geop->rht);
	sf_warning("srcdecay=%d srcrange=%d",srcp->decay,srcp->range);
	sf_warning("spx=%d spz=%d gp=%d snpint=%d", spx, spz, gp, snpint);
	sf_warning("wfdt=%f wfnt=%d ", wfdt, wfnt);
	sf_warning("============================");
    }

    /* write record */
    sf_setn(ax, nx);
    sf_setn(az, nz);
    
    if(!wantrecord) {
	sf_oaxa(Frcd, at, 1);
	sf_oaxa(Frcd, ax, 2);
	sf_settype(Frcd,SF_COMPLEX);
    }

    if (wantwf) {
	/*write temp wavefield */
	sf_setn(at, wfnt);
	sf_setd(at, wfdt);
	
	sf_oaxa(Ftmpwf, az, 1);
	sf_oaxa(Ftmpwf, ax, 2);
	sf_oaxa(Ftmpwf, at, 3);
	sf_settype(Ftmpwf,SF_FLOAT);
	
	/*write temp wavefield */
	sf_oaxa(Ftmpbwf, az, 1);
	sf_oaxa(Ftmpbwf, ax, 2);
	sf_oaxa(Ftmpbwf, at, 3);
	sf_settype(Ftmpbwf,SF_FLOAT);
    }

    /*write image*/
    sf_oaxa(Fimg1, az, 1);
    sf_oaxa(Fimg1, ax, 2);
    sf_settype(Fimg1,SF_FLOAT);
    sf_oaxa(Fimg2, az, 1);
    sf_oaxa(Fimg2, ax, 2);
    sf_settype(Fimg2,SF_FLOAT);

    lrosfor2(wavefld, record, verb, lt, rt, m2, geop, srcp, pad1);
    if(wantrecord) {
	sf_complexread(record[0], nx*nt, Frcd);
    }
    //    lrosback2(img1, img2, wavefld, record, verb, wantwf, ltb, rtb, m2, geop, srcp, pad1, wavefld2);
    
    if (!wantrecord) {
	for (ix=0; ix<nx; ix++) 
	    sf_complexwrite(record[ix], nt, Frcd);
    }
    
    if (wantwf) {
	for (it=0; it<wfnt; it++)
	    for ( ix=0; ix<nx; ix++) {
		sf_floatwrite(wavefld[it][ix], nz, Ftmpwf);
		//		sf_floatwrite(wavefld2[it][ix],nz, Ftmpbwf);
	    }
    }

    for (ix=0; ix<nx; ix++) 
	sf_floatwrite(img1[ix], nz, Fimg1);
    for (ix=0; ix<nx; ix++) 
	sf_floatwrite(img2[ix], nz, Fimg2);
      
    tend = clock();
    duration=(double)(tend-tstart)/CLOCKS_PER_SEC;
    sf_warning(">> The CPU time of single shot migration is: %f seconds << ", duration);
    exit(0);

}



