import sys
import threading
import socket
import json

# Host definitions
LOCALHOST   = '127.0.0.1'
PORT        = 5918
BUFFER_SIZE = 512

# Message types
TEXT    = 0
CONTROL = 1
ECHO    = 3

# Queues
sending_queue   = []
receiving_queue = []

def SendMessage(IP, port, data, type=TEXT):
    msg = {'IP':IP, 'Port': port, 'Type':type, 'Data':data}
    sending_queue.append(msg)

def Sender(tcp):
    while True:
        if sending_queue:
            # Getting the next message
            msg = sending_queue[0]
            # Connecting with its destination
            tcp.connect((msg['IP'], msg['Port']))
            # Sending json message
            del msg['IP']
            del msg['Port']
            msg_json = json.dumps(msg)
            tcp.send(msg_json.encode('ascii'))
            # Verifying echo
            echo_json = tcp.recv(BUFFER_SIZE)
            echo = json.loads(echo_json.decode('ascii'))
            if msg['Data'] == echo['Data'] and echo['Type'] == ECHO:
                del sending_queue[0]
            # Closing connection
            tcp.close()

def Receiver(tcp):
    while True:
        # Listening for clients
        tcp.listen()
        print("Socket is listening...")
        while True:
            # Accepting a connection
            conn, addr = tcp.accept()
            print('Connection accepted:', addr)
            # Receiving message
            msg_json = conn.recv(BUFFER_SIZE)
            if not msg_json: break
            msg = json.loads(msg_json.decode('ascii'))
            print("Received data:", msg[DATA])
            # Sending echo
            msg['Type'] = ECHO
            conn.send(data)
        # Closing connection
        conn.close()

def Initialize():
    print("Wellcome! :)")
    # Initializing TCP socket
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Binding the port
    PORT = int(input("Enter a port: "))
    try:
        tcp.bind((LOCALHOST, PORT))
    except:
        print("Bind failed. Error : " + str(sys.exc_info()))
        sys.exit()
    # Initializing sender thread
    sender = threading.Thread(target=Sender,args=(tcp,))
    sender.start()
    # Initializing receiver thread
    receiver = threading.Thread(target=Receiver,args=(tcp,))
    receiver.start()

Initialize()
SendMessage('127.0.0.1', 5718, 'Hey')
