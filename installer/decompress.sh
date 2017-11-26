#!/bin/bash
echo ""
echo "Self Extracting Installer"
echo ""

if [ "$(whoami)" != "root" ];
	then echo "please run as root"
	echo "Installation aborted"
	exit
fi

export TMPDIR=`mktemp -d /tmp/selfextract.XXXXXX`

ARCHIVE=`awk '/^__ARCHIVE_BELOW__/ {print NR + 2; exit 0; }' $0`

tail -n+$ARCHIVE $0 | tar xzv -C $TMPDIR

CDIR=`pwd`
cd $TMPDIR
./installer.sh

cd $CDIR
rm -rf $TMPDIR

exit 0

__ARCHIVE_BELOW__

