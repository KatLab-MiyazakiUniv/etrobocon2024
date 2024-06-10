#!/bin/sh
<<DOCUMENT_COMMENT
@file   organize_logfile.sh
@brief  前回のログファイルを退避する
@author YKhm20020
DOCUMENT_COMMENT

mkdir -p etrobocon2024/logfiles
oldName="logfile.txt"
newName=`date +"%m%d-%H:%M.txt"`

mv -f $oldName etrobocon2024/logfiles/$newName
