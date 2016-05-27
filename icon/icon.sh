#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)icon.sh	1.1.1.5	6/2/87

USAGE="Usage: icon [-c] [-x m] [-y n]"
xval="50"
yval="50"
cval=""

set -- `getopt cx:y: $*`
if [ $? != 0 ]
then
	echo $USAGE
	exit 2
fi

while [ true ]
do
	case "$1" in
	-x) xval=$2; shift 2;;
	-y) yval=$2; shift 2;;
	-c) cval=$1; shift;;
	--) shift; break;;
	esac
done

DMD=${DMD:-DeFdMd}
echo $xval $yval | ${DMD}/bin/jx ${DMD}/lib/icon.m ${cval} -d ${DMD} 
