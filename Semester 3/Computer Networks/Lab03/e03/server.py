import struct
import socket
import select


def send_clients(clients):
    data_to_send = ''
    for client_information in clients.values():
        data_to_send += client_information[0] + ',' + str(client_information[1]) + ';'
        
    data_to_send = data_to_send[:-1]
    for client in clients:
        client.send(data_to_send.encode())


if __name__ == '__main__':
    clients = dict() # key: tcp socket - used to send the list of clients ,
                    # values: (udp_port - udp communication happens here, ip address - communication)
    rdv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rdv.bind(('127.0.0.1', 1234))
    rdv.listen(5)

    reading_sockets = [rdv]
    while True:
        sockets_ready_for_read, _, _ = select.select(reading_sockets, [], [])
        for socket in sockets_ready_for_read:
            if socket is rdv:
                # we have a new client connection
                client_connection, client_address = socket.accept()
                print('New client from the address: ', client_address)
                
                c_udpp = client_connection.recv(4)
                c_udpp = struct.unpack('!I', c_udpp)[0]
                clients[client_connection] = (client_address[0], c_udpp)
                
                send_clients(clients)
                reading_sockets.append(client_connection)
                
            else:
                data = socket.recv(512)
                if not data or 'quit' in data.decode().lower():
                    socket.close()
                    clients.pop(socket)
                    reading_sockets.remove(socket)
                    send_clients(clients)
