#!/system/bin/sh

chmod 666 /sys/power/sleep_while_idle

busybox mknod /dev/ave c 125 0
busybox mkdir /dev/InterDSP
busybox mknod /dev/InterDSP/datamgr c 251 20
busybox mknod /dev/InterDSP/control c 251 16
chown 0:1003 /dev/ave
chown 0:1003 /dev/InterDSP/datamgr
chown 0:1003 /dev/InterDSP/control

insmod /lib/modules/inter_dsp.ko
insmod /lib/modules/em_ave.ko
 
ln -s /dev/v4l/video0 /dev/video0
ln -s /dev/v4l/video1 /dev/video1

mkdir /dev/fb
ln -s /dev/graphics/fb0 /dev/fb/0

/system/vendor/bin/pvrsrvctl --start

