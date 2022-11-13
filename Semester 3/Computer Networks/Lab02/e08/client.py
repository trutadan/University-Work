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
    step_count = 0

    while not finished:
        client_number = int(input("\nGuess the number: "))
        while left_limit > client_number or client_number > right_limit:
            client_number = int(input("\nGuess the number: "))

        try:
            socket_descriptor.sendall(struct.pack('!I', client_number))
            answer = socket_descriptor.recv(8)

            server_answer = answer.decode('ascii')[0]
            clients_count = answer.decode('ascii')[1:]
        except socket.error as msg:
            print('Error: ', msg.strerror)
            socket_descriptor.close()
            exit(-2)

        step_count += 1
        print('\nThere are', clients_count, 'clients taking part!\nSent the number:', client_number, '\nAnswer from server:', server_answer)

        if server_answer == 'G' or server_answer == 'L':
            finished = True

        time.sleep(0.25)

    socket_descriptor.close()
    if server_answer == 'G':
        print("I am the winner, with the number", client_number, "guessed in", step_count, "steps!")
    else:
        print("I lost!")



