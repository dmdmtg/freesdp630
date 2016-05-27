/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)printf.c	1.1.1.3	(5/10/87)";

/*
** FUNCTION:	lprintf, bprintf, sprintf
**
** SYNOPSIS:	lprintf(fmt, arg1, arg2, ...)
** 		bprintf(fmt, arg1, arg2, ...)
**		sprintf(s, fmt, arg1, arg2, ...)
**
** DESCRIPTION:
**   		lprintf converts, and prints its arguments on the layer
**		starting at the current point (global variable sPtCurrent),
**		under the control of the string fmt.
**
**		bprintf does the same, only it draws into a fixed area
**		at the bottom of the screen.
**
**		The fmt string contains ordinary characters, which are
**		simply copied to the layer, and conversion specifications,
**		each of which causes conversion and printing of the next
**		successive argument to lprintf.
**
**		Each conversion specification is introduced by the character
**		% and followed by a conversion character. These conversion
**		options will be accepted:
**
**			d	The argument is converted to decimal notation.
**			u	The argument is converted to unsigned decimal.
**			o	The argument is converted to unsigned octal
**				notation (without a leading 0).
**			x	The argument is converted to unsigned hex
**				notation (without a leading 0x).
**			D	The argument is converted to long unsigned
**				decimal (same as %lu)
**			c	The argument is taken to be a single character.
**			s	The argument is a string; characters from the
**				string are printed until a null character is
**				reached.
**
**		If the character after the % is not one of the above conversion
**		character, that character is printed.
**
**		These characters are processed for lprintf and bprintf:
**
**			\n	Newline. Scroll if necesary.
**			\r	Carriage return. The x coord of the current
**				point is reset to layers coord 0.
**			\t	Tab. Tabs are set every 8 characters from the
**				left border of layer.
**
** NOTES :	Since lprintf uses sPtCurrent and moveto(). That leads
**		to the following considerations:
**
**		Applications can affect where printing will occur with
**		the moveto() function.
**
**		sPtCurrent is stored as an offset off Drect.origin in
**		screen coordinates (see comments in moveto.c).
**
**		Since sPtCurrent is stored as an offset, Moves between calls
**		to lprintf are handled properly. Reshapes, however, are a
**		problem (see comments in moveto.c). After a layer is
**		reshaped, if the offset is still in the window, printing
**		will continue at the offset into the new window that printing
**		was occurring before the reshape. If the offset is no longer
**		in the window, the current point will move to Drect.origin.
**		If an application wants to do a better job of this, it
**		should watch RESHAPED and call moveto(Drect.origin):
**
**			if(P->state&RESHAPED) {
**				if(!(P->state&MOVED))
**					moveto(Drect.origin);
**				P->state &= ~(MOVED|RESHAPED);
**			}
*/ 
 
extern lputchar();
extern bputchar();
extern _doprnt();

lprintf(fmt, args)
char *fmt;
int args;
{
        _doprnt(lputchar, fmt, &args);
}

bprintf(fmt, args)
char *fmt;
int args;
{
        _doprnt(bputchar, fmt, &args);
}

/*
**	sprintf()
**
*/

static char *_sp;

_sputc(c)
char c;
{
        *_sp++ = c;
}

sprintf(s, fmt, args)
char *s, *fmt;
int args;
{
        _sp = s;
        _doprnt(_sputc, fmt, &args);
	*_sp = '\0';
}

