import sys
import socket
import struct
import threading


# server sends ip and port of client
all_clients_information = []
# block actions when
thread_lock = threading.Lock()

thread_for_reading_clients_messages = threading.Thread()


def read_clients_messages(client_socket):
    import datetime

    # read client messages from the open udp ports
    while True:
        message, address = client_socket.recvfrom(512)
        string_message = message.decode()

        current_datetime = datetime.datetime.now()
        current_datetime_string_format = f"[{current_datetime.day}/{current_datetime.month}/{current_datetime.year}:{current_datetime.hour}:{current_datetime.minute}:{current_datetime.second}]"

        print(f"{address}{current_datetime_string_format}: {string_message}")


def read_client_input(client_socket):
    global all_clients_information, thread_lock

    # read uset input and send it to all the clients
    while True:
        user_input = input()
        encoded_user_input = user_input.encode()

        if 'QUIT' in user_input.upper():
            thread_for_reading_clients_messages.join()
            return

        # block all other clients from sending messages
        thread_lock.acquire()

        for client_ip_and_port in all_clients_information:
            client_socket.sendto(encoded_user_input, client_ip_and_port)

        thread_lock.release()


def recreate_client_information_list(ips_and_ports_string):
    global all_clients_information

    clients_ip_and_ports_list = ips_and_ports_string.split('|')

    all_clients_information.clear()
    for each_client in clients_ip_and_ports_list:
        each_client_ip_and_port = each_client.split(';')

        ip = each_client_ip_and_port[0].rstrip()
        port = int(each_client_ip_and_port[1])

        all_clients_information.append((ip, port))


def main():
    global all_clients_information, thread_lock, thread_for_reading_clients_messages

    if len(sys.argv) < 4:
        print("executable <ip> <server_port> <client_port>")
        return

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.connect((sys.argv[1], int(sys.argv[2])))

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.bind((sys.argv[1], int(sys.argv[3])))

    thread_for_reading_clients_messages = threading.Thread(target=read_clients_messages, args=(client_socket,))
    thread_for_reading_input = threading.Thread(target=read_client_input, args=(client_socket,))

    thread_for_reading_clients_messages.start()
    thread_for_reading_input.start()

    # send the udp port to the server
    server_socket.send(struct.pack('!I', int(sys.argv[3])))

    while True:
        all_clients_as_formatted_string = server_socket.recv(512).decode()

        nicely_formatted_clients_string = all_clients_as_formatted_string
        nicely_formatted_clients_string = nicely_formatted_clients_string.replace(";", ":")
        nicely_formatted_clients_string = nicely_formatted_clients_string.replace("|", ", ")
        print(f'Received new peer list: {nicely_formatted_clients_string}')

        thread_lock.acquire()
        recreate_client_information_list(all_clients_as_formatted_string)
        thread_lock.release()


if __name__ == '__main__':
    main()
