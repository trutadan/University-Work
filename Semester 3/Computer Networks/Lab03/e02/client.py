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
        socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    except socket.error as exception:
        print("Error: ", exception.strerror)
        exit(-1)

    finished = False
    lower_limit = 1
    right_limit = 2 ** 17 - 1
    random.seed()

    step_count = 0

    while not finished:
        my_number = random.randint(lower_limit, right_limit)

        try:
            socket_descriptor.sendto(struct.pack('!I', my_number), (sys.argv[1], int(sys.argv[2])))
            answer, address = socket_descriptor.recvfrom(1)
        except socket.error as msg:
            print('Error: ', msg.strerror)
            socket_descriptor.close()
            exit(-2)

        step_count += 1
        print('Sent the number', my_number, '\nAnswer from server:', answer.decode('ascii'))

        if answer == b'H':
            lower_limit = my_number
        if answer == b'S':
            right_limit = my_number
        if answer == b'G' or answer == b'L':
            finished = True

        time.sleep(0.25)

    socket_descriptor.close()
    if answer == b'G':
        print("I am the winner, with", my_number, "in", step_count, "steps!")
    else:
        print("I lost!")
