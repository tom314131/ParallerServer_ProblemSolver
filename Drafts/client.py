from socket import socket, AF_INET, SOCK_STREAM
import sys

serverIP = "127.0.0.1" 			#set server ip from arguments.
serverPort = int(sys.argv[1])	#set server port from arguments.

sock = socket(AF_INET, SOCK_STREAM)	#create udp socket above IP.
sock.connect((serverIP,serverPort))

matrix  = "1,-1,1,1,1\n"
matrix += "1,-1,1,-1,1\n"
matrix += "1,1,1,-1,1\n"
matrix += "0,0\n"
matrix += "2,4\n"
matrix += "end\n"
sock.send(matrix)
#Received:  Up,Up,Left,Left,Down,Down,Left,Left,Up,Up

#msg = 'a'

#while not msg == 'end':    
 #   msg = raw_input("Enter message: ")
  #  if msg == 'done':
   #     break;
    #print "Sending: ", msg
    #sock.send(msg+'\n')
        
data = sock.recv(4096)
print "Received: ",data

sock.close()
