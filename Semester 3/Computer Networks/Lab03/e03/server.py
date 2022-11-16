import socket
import select
import struct
import sys


def send_information_to_all_clients(clients_dictionary):
    # ip_client0;port_client0|ip_client1;port_client1
    client_information = ''
    
    for information in clients_dictionary.values():
        client_information += information[0] + ';' + str(information[1]) + '|'
        
    client_information = client_information[:-1]
    
    for client in clients_dictionary:
        client.send(client_information.encode())


def main():
    if len(sys.argv) < 3:
        print("executable <ip> <port>")
        return
    
    # key - tcp socket
    # value - a tuple consisting of udp port and ip address
    all_clients_dictionary = dict()
    
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((sys.argv[1], int(sys.argv[2])))
    server_socket.listen(7)

    print("TCP server successfully started working...")

    all_available_reading_sockets = [server_socket]

    while True:
        ready_to_read_sockets, _, _ = select.select(all_available_reading_sockets, [], [])
        for each_socket in ready_to_read_sockets:
            if each_socket is server_socket:
                # the tcp server is called, so we have a new client connection

                client_socket, client_address = server_socket.accept()
                print(f'Welcome to a new client, coming from the address {client_address}!')

                client_port = client_socket.recv(4)
                client_port = struct.unpack('!I', client_port)[0]

                all_clients_dictionary[client_socket] = (client_address[0], client_port)
                send_information_to_all_clients(all_clients_dictionary)

                all_available_reading_sockets.append(client_socket)

            else:
                data_from_client = each_socket.recv(512).decode()
                if not data_from_client or 'QUIT' in data_from_client.upper():
                    each_socket.close()

                    all_available_reading_sockets.remove(each_socket)
                    all_clients_dictionary.pop(each_socket)

                    send_information_to_all_clients(all_clients_dictionary)
    
    
if __name__ == '__main__':
    main()
    
