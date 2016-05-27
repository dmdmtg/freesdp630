#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)dmdmemory.sh	1.1.1.3	(6/2/87)

USAGE="Usage: dmdmemory [-c]\n"
cval=""

set -- `getopt c $*`
if [ $? != 0 ]
then
	echo $USAGE
	exit 2
fi

while [ true ]
do
	case "$1" in
	-c) cval=$1; shift;;
	--) shift; break;;
	esac
done

${DMD:-DeFdMd}/bin/dmdld ${DMD:-DeFdMd}/lib/dmdmemory.m ${cval}
