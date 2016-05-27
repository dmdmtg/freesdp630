/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)infont.c	1.1.1.3	(5/10/87)";

#include <dmd.h>
#include <font.h>

Bitmap *balloc();
char *alloc();


int
inbyte()       /* re-pack font bytes from host */
{
        register int c;

        while((c = rcvchar()) == -1)
                wait(RCV);
        return (c);
}


Font *
infont(yourinbyte)
int (*yourinbyte)();    /* inbyte routine */
{ /* load a font */
        short n;        /* # chars in the font */
        register Font *f;       /* the font */
        register Bitmap *b;     /* its bitmap */
        register int (*myinbyte)();     /* inbyte */
        register int i;
        char dummy[2];
	char *dummyp;
	char *p;	/* pointer to pointer to where input is going */

        if(!yourinbyte) { /* use my inbyte */
                myinbyte = inbyte;
        }
        else
        {
                myinbyte = yourinbyte;
        }

	p = (char *)&n;
        if(ninch(2,&p,myinbyte))	/* read f->n to find size of f */
                goto err2;
        if((f = (Font *) alloc(sizeof(Font)+ISIZE(n))) == (Font *)0)
                goto err2;
        f->n = n-1;	/* why??? */
	p = 2 + (char *)f;
        if(ninch(6,&p,myinbyte)) /* 6 == sizeof(height+ascent+unused) */
                goto err;
	p = (char *)f->info;
	dummyp = dummy;
        for(i=0; i<n+1; i++, p+=sizeof(Fontchar)) /* changed to be 5620 compatable */
                if(ninch(sizeof(Fontchar),&p,myinbyte) ||
                  ninch(FCHARSIZE - sizeof(Fontchar), &dummyp, myinbyte))
                        goto err;
        /* changed to be 5620 compatable */
        if((b = balloc(Rect(0,0,(f->info[n].x + 31)&0xFFE0,f->height))) == (Bitmap *)0)
                goto err;
        f->bits = b;
        if(ninch(sizeof(Word)*f->height*b->width,(char **)&(b->base),myinbyte))
                goto berr;
        return(f);

        berr:
                bfree(f->bits);
        err:
                free(f);
        err2:
        return((Font *)0);
}

int
ninch(n,s,inbyte)
        int n;
        char **s;
        int (*inbyte)();
{
        register x, i;

	i = 0;
	while(n-- > 0)
        {
                (*s)[i++] = x = (*inbyte)();
                if(x == -1)
                        return(1);
        }
        return(0);
}


