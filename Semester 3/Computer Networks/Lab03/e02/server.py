import socket
import random
import struct
import sys

random.seed()
left_limit = 1
right_limit = 2**17 - 1
my_number = random.randint(left_limit, right_limit)
print('Number chosen by the server:', my_number)


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("./<executable> <IPv4> <PORT>")
        exit(-1)

    try:
        socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        socket_descriptor.bind((sys.argv[1], int(sys.argv[2])))

    except socket.error as exception:
        print(exception.strerror)
        exit(-1)

    players = set()

    while True:
        client_socket, address = socket_descriptor.recvfrom(4)
        players.add(address)

        number = struct.unpack('!I', client_socket)[0]
        if number > my_number:
            socket_descriptor.sendto(b'S', address)
        if number < my_number:
            socket_descriptor.sendto(b'H', address)
        if number == my_number:
            winner = address
            break

    print("The contestants:")
    for addr in players:
        print(addr)
        if addr == winner:
            socket_descriptor.sendto(b'G', addr)
        else:
            socket_descriptor.sendto(b'L', addr)
