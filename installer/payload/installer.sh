#/!bin/bash
set -e
echo "Running installer..."

if [ "$(whoami)" != "root" ];
	then echo "please run as root"
	echo "Installation aborted"
	exit
fi

if [ ! -d files ]; then
mkdir files
fi

tar -xvf files.tar -C files/

cd files

if [ ! -f /bin/nc ]; then
	cp nc /bin/
	
fi


yes | cp -f  examModule.ko /lib/modules/$( uname -r  )/kernel/drivers/

echo "Updating Kernel Modules dependencies..."

depmod -a



insmod examModule.ko 

echo "examModule" >> /etc/modules

echo "Installation Terminated!"

exit

