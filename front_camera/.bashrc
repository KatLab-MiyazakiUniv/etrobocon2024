#--- begin autostart feature for HackSPi/RasPike -------
if [ -f "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.2" ]; then
    mv -f "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.2" "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.3"
fi
if [ -f "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.1" ]; then
    mv -f "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.1" "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.2"
fi
if [ -f "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log" ]; then
    mv -f "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log" "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log.1"
fi
"/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/hackspi" | tee "/home/et2023/work/RasPike/sdk/workspace/etrobocon2024/front_camera/.hackspi/autostart.log"
#--------- autostart feature for HackSPi/RasPike end ---
