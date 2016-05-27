# @(#)dmdman.sh	2.0	(6/15/93)

case $# in
    0) echo "Usage: dmdman manpage ..." >&2; exit 1;;
esac
for file
do
	nroff -man ${DMD:-DeFdMd}/man/man*/$file.*
done
