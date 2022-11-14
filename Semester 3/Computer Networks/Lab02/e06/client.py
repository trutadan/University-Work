import random
import socket
import struct
import sys
import time

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("./<executable> <IPv4> <PORT>")
        exit(-1)

    try:
        socket_descriptor = socket.create_connection((sys.argv[1], int(sys.argv[2])))
    except socket.error as exception:
        print("Error: ", exception.strerror)
        exit(-1)

    finished = False
    left_limit = 1
    right_limit = 2 ** 17 - 1
    random.seed()

    data = socket_descriptor.recv(1024)
    print(data.decode('ascii'))

    while not finished:
        client_number = random.randint(left_limit, right_limit)

        try:
            socket_descriptor.sendall(struct.pack('!I', client_number))
            answer = socket_descriptor.recv(32)
            server_answer = answer.decode('utf8')
        except socket.error as msg:
            print('Error: ', msg.strerror)
            socket_descriptor.close()
            exit(-2)

        print('\nSent the number:', client_number, '\nAnswer from server:', server_answer)

        if server_answer == 'smaller':
            right_limit = client_number - 1
        elif server_answer == 'larger':
            left_limit = client_number + 1
        else:
            finished = True

        time.sleep(0.25)

    socket_descriptor.close()
