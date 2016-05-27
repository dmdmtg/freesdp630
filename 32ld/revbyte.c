/* return true if host is reversed byte order (little endian) */
#include <stdio.h>
main()
{
	union {
		long l;
		char c[4];
	} un;

	strncpy(un.c, "\01\02\03\04", 4);
	if (0x01020304L == un.l) 
	    /* not reversed */
	    return(1);
	else if (0x04030201L == un.l) 
	    /* reversed */
	    return(0);
	fprintf(stderr,"can't determine byte order\n");
	return(2);
}
