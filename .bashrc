#--- begin autostart feature for HackSPi/RasPike -------
if [ -f "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.2" ]; then
    mv -f "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.2" "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.3"
fi
if [ -f "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.1" ]; then
    mv -f "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.1" "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.2"
fi
if [ -f "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log" ]; then
    mv -f "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log" "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log.1"
fi
"/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/hackspi" | tee "/home/et2024/work/RasPike/sdk/workspace/etrobocon2024/.hackspi/autostart.log"
#--------- autostart feature for HackSPi/RasPike end ---
