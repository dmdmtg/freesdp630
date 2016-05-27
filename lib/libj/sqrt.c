/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)sqrt.c	1.1.1.2	(5/10/87)";

#define MAXROOT 0xb504
long
Lsqrt(x)
        long x;
{
        register long high = MAXROOT;
        register long low=0;
        register long current = MAXROOT/2;

        if(x<=0)
                return 0;
        if (x >= MAXROOT * MAXROOT)
                return(MAXROOT);
        
        while (high > low + 1)
        {
                if (current * current == x)
                        return (current);
                if (current * current > x)
                {
                        high = current;
                }
                else
                {
                        low = current;
                }
                current = (high + low)>>1;
        }
        return (current);
}


sqrtryz(r,y,z)
{
        register long sumsq;

        sumsq = r*r - y*y - z*z;
        if (sumsq <= 0)
                return 0;
        return ( (int)Lsqrt(sumsq) );
}


norm (x, y, z)
int x, y, z;
{
    register long X = x, Y = y, Z = z;

    return (Lsqrt ((long) (X*X + Y*Y + Z*Z)));
}
