/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)font1.c	1.1.1.2	(5/22/87)";

#include <dmd.h>
#include <font.h>

/*Library routines and associated manual pages.	*/
void bitblt();		/* BITBLT(3R)		*/

/*Library macros and associated manual pages.	*/
/* Point Pt()		   Pt(3L)		*/

main()
{}

void
drawchar(Character, FontPointer, DestinationBitmap, 
         ScreenPoint, StorageCode)

char    Character;		/* character to be drawn	*/
Font   *FontPointer;		/* pointer to font used	*/
Bitmap *DestinationBitmap;	/* destination Bitmap		*/
Point  ScreenPoint;		/* point to draw character	*/
Code   StorageCode;		/* graphics storage code	*/
{
    Rectangle CharRect;
    Fontchar *CharDescriptor;

    /*
    ** Get the "Fontchar" character descriptor for "Character".
    */
    CharDescriptor = FontPointer->info+Character;

    /*
    ** Determine the enclosing rectangle for "Character"
    ** based on the graphical storage code used.
    */
    if(StorageCode == F_STORE) {
        /*
        ** y-coordinates of the "character image cell".
	*/
        CharRect.origin.y = 0;
        CharRect.corner.y = FontPointer->height;
    } else {
	/*
        ** y-coordinates of the minimum enclosing rectangle.
        */
        CharRect.origin.y = CharDescriptor->top;
        CharRect.corner.y = CharDescriptor->bottom;
    }

    /*
    ** x-coordinates
    */
    CharRect.origin.x = CharDescriptor->x;
    CharRect.corner.x = (CharDescriptor+1)->x;

    /*
    ** Display the character.
    */
    bitblt(
    /*Source Bitmap     */ FontPointer->bits,
    /*Source Rectangle  */ CharRect,
    /*Destination Bitmap*/ DestinationBitmap,
    /*Destination Point */ Pt(ScreenPoint.x + CharDescriptor->left,
                              ScreenPoint.y + CharRect.origin.y),
    /*Storage code      */ StorageCode);
}

