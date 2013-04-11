#!/system/bin/sh

chmod 666 /sys/power/sleep_while_idle

busybox mknod /dev/ave c 125 0
busybox mkdir /dev/InterDSP
# MAJOR and MINOR must match with values assigned by kernel driver
# arch/arm/mach-emxx/inter_dsp.c : DSPDEV_MAJOR, DSPDEV_CONTROL_MINOR, DSPDEV_DATAMGR_MINOR
busybox mknod /dev/InterDSP/datamgr c 63 25
busybox mknod /dev/InterDSP/control c 63 16

chown 0:1003 /dev/ave
chown 0:1003 /dev/InterDSP/datamgr
chown 0:1003 /dev/InterDSP/control

chmod 777 /dev/ave
chmod 777 /dev/InterDSP
chmod 777 /dev/InterDSP/datamgr
chmod 777 /dev/InterDSP/control

insmod /lib/modules/inter_dsp.ko
insmod /lib/modules/em_ave.ko
 
ln -s /dev/v4l/video0 /dev/video0
ln -s /dev/v4l/video1 /dev/video1

mkdir /dev/fb
ln -s /dev/graphics/fb0 /dev/fb/0

# Start the SGX modules
/system/vendor/bin/pvrsrvctl --start

