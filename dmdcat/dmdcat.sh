#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)dmdcat.sh	1.1.1.5	(6/12/87)

# dmdcat shell
#

pon="1i"
poff="\033[?4i\r\c"
pcol=0
prog=$0
v=
u=
t=
e=

	set -- `getopt bsvute $*`
	if [ $? != 0 ]
	then
		echo "Usage: ${prog} [-b] [-s] [-v] [-u] [-t] [-e] [file ...]"
		exit 2
   	fi
   
   	while [ true ]
	do
		case "$1" in
		-b) 
			if [ ! -x /usr/bin/col ]
			then
				echo '${prog}: -b option does not work on your computer'
				exit 1
			else
				pcol=1
			fi
			;;

		-s)
			pon="2i"
			poff="\033[4i\r\c"
			;;

		-v)
			v="-v"
			;;
		-u)
			u="-u"
			;;
		-t)
			t="-t"
			;;
		-e)
			e="-e"
			;;

		--)
			shift; break;;
		esac
		shift
   	done

#   fi


if [ ! -x ${DMD:-DeFdMd}/lib/dmdgetpr ]
then
	echo ${prog}:  cannot execute ${DMD:-DeFdMd}/lib/dmdgetpr
	exit 1
fi

trap "" 2
trap 'echo $poff ; exit 1' 2
if
#  call c program that reads terminal response and returns
#  true if printer granted
	${DMD:-DeFdMd}/lib/dmdgetpr "$pon" </dev/tty
then
	:
else
	echo $poff 
	echo ${prog}:  printer not available
	exit 1
fi

if [ $pcol = 1 ]
then
	cat $v $u $t $e $@ | col -b
else
	cat $v $u $t $e $@ 
fi

exitstatus=$?
trap "" 2
echo $poff 
exit $exitstatus
