#!/system/bin/sh

chmod 666 /sys/power/sleep_while_idle

insmod /lib/modules/inter_dsp.ko
insmod /lib/modules/em_ave.ko
 
ln -s /dev/v4l/video0 /dev/video0
ln -s /dev/v4l/video1 /dev/video1

mkdir /dev/fb
ln -s /dev/graphics/fb0 /dev/fb/0

ls /lib/modules/pvrsrvkm.ko
ret=$?

case ${ret} in
  0)
    mv /system/lib/hw/gralloc.emxx.so /system/lib/hw/gralloc.emxx.so_tmp
    insmod /lib/modules/pvrsrvkm.ko
    /vendor/bin/pvrsrvinit

    insmod /lib/modules/emxxlfb.ko
    insmod /lib/modules/bc_example.ko
    ;;
esac

