import socket
import threading
import random
import struct
import sys
import time

random.seed()
left_limit = 1
right_limit = 2 ** 17 - 1
server_number = random.randint(left_limit, right_limit)

print('Number chosen by the server:', server_number)
thread_lock = threading.Lock()
client_guessed = False
winner_thread = 0

e = threading.Event()
e.clear()

threads = []
client_count = 0


def worker(cs):
    global thread_lock, client_guessed, server_number, winner_thread, client_count, e

    client_id_count = client_count
    print('Client #', client_count, 'with the details', cs.getpeername())
    message = 'Hello client #' + str(client_count) + '! You are entering the number guess competition now!'
    cs.sendall(bytes(message, 'ascii'))

    while not client_guessed:
        try:
            client_number = cs.recv(4)
            client_number = struct.unpack('!I', client_number)[0]

            if client_guessed:
                break

            if client_number > server_number:
                server_message = 'S' + str(client_count)
                cs.sendall(bytes(server_message, 'ascii'))

            if client_number < server_number:
                server_message = 'H' + str(client_count)
                cs.sendall(bytes(server_message, 'ascii'))

            if client_number == server_number:
                thread_lock.acquire()
                client_guessed = True
                winner_thread = threading.get_ident()
                thread_lock.release()

        except socket.error as exception:
            print('Error:', exception.strerror)
            break

    if client_guessed:
        if threading.get_ident() == winner_thread:
            server_message = 'G' + str(client_count)
            cs.sendall(bytes(server_message, 'ascii'))

            print('The winner is', cs.getpeername())
            print("Thread", client_id_count, "winner!")

            e.set()
        else:
            server_message = 'L' + str(client_count)
            cs.sendall(bytes(server_message, 'ascii'))

            print("Thread", client_id_count, " loser!")

    time.sleep(1)
    cs.close()
    print("Worker thread", client_id_count, "ended!")


def resetServer():
    global thread_lock, client_guessed, winner_thread, server_number, threads, e, client_count

    while True:
        e.wait()

        for t in threads:
            t.join()
        print("All threads finished now!")

        e.clear()
        thread_lock.acquire()
        threads = []

        client_guessed = False
        winner_thread = -1
        client_count = 0

        server_number = random.randint(left_limit, right_limit)
        print('Number chosen by the server:', server_number)

        thread_lock.release()


if __name__ == '__main__':
    try:
        socket_descriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket_descriptor.bind((sys.argv[1], int(sys.argv[2])))
        socket_descriptor.listen(5)
    except socket.error as exception:
        print(exception.strerror)
        exit(-1)

    t = threading.Thread(target=resetServer, daemon=True)
    t.start()

    while True:
        client_socket, address = socket_descriptor.accept()

        t = threading.Thread(target=worker, args=(client_socket,))
        threads.append(t)
        client_count += 1
        t.start()
