from socket import *
from _thread import *
import struct
import os

class SocketInfo:
    HOST = "127.0.0.1"
    PORT = 21000
    BUFSIZE = 4096
    ADDR = (HOST, PORT)

# def recv_data(client_socket):
#     while True:
#         try:
#             data = client_socket.recv(SocketInfo.BUFSIZE)
#             if not data:
#                 print("서버 연결 종료")
#                 break
#             print("Received: ", data.decode('utf-8'))
#         except Exception as e:
#             print("Error receiving data:", e)
#             break
def first_send(client_socket, msg):
    try:
        print("갔나?")
        client_socket.sendall(msg.to_bytes(4, byteorder='big', signed=True))
    except Exception as e:
        print("Error sending message:", e)
def send_message(client_socket, message):
    try:
        client_socket.sendall(message)
    except Exception as e:
        print("Error sending message:", e)
def send_file(client_socket):
    filename = "C:\\Users\\IOT\\Desktop\\AIimage\\shape.jpg"
    try:
        file_size = os.path.getsize(filename)
        client_socket.sendall(struct.pack("!I", file_size))

        with open(filename, 'rb') as f:
            while True:
                data = f.read(SocketInfo.BUFSIZE)
                if not data:
                    break
                client_socket.sendall(data)
        msg = "ok"
        send_message(client_socket, msg)
        print('파일 전송 완료')
    except Exception as e:
        print("Error sending file:", e)
        close_connection(client_socket)
        exit()

def receive_file(client_socket):
    save_file = "C:\\Users\\IOT\\Desktop\\AIimage\\shape.jpg"
    try:
        file_size_bytes = client_socket.recv(4)
        # file_size = struct.unpack("!I", file_size_bytes)[0]
        file_size = int.from_bytes(file_size_bytes)
        with open(save_file, 'wb') as f:
            remaining_size = 0
            while remaining_size < file_size:
                data = client_socket.recv(SocketInfo.BUFSIZE)
                if not data:
                    break
                f.write(data)
                remaining_size += len(data)
        print('파일 수신 완료')
    except Exception as e:
        print("Error receiving file:", e)
        close_connection(client_socket)
        exit()

def close_connection(client_socket):
    try:
        client_socket.close()
    except Exception as e:
        print("Error closing connection:", e)

client_socket = socket(AF_INET, SOCK_STREAM)

try:
    client_socket.connect(SocketInfo.ADDR)
    print('서버 연결')

    # start_new_thread(recv_data, (client_socket,))

    # msg=1
    # first_send(client_socket, msg)

    # message = "하이"
    # send_message(client_socket, message)

    while True:
        receive_file(client_socket)
        send_file(client_socket)
        # message = input("Enter your message ('quit' to exit): ")
        # if message == 'q':
        #     send_message(client_socket, message)
        # if message == 'send_file':
        #     send_file(client_socket)
        # else:
        #     send_message(client_socket, bytes(message.encode('UTF-8')))

    close_connection(client_socket)

except Exception as e:
    print("Error:", e)
    close_connection(client_socket)
    exit()
