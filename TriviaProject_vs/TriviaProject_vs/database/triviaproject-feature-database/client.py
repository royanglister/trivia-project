import socket

PORT = 8826
SERVER_ADDRESS = 'localhost'


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        try:
            sock.connect((SERVER_ADDRESS, PORT))
        except:
            print("Couldn't connect.")
            exit(1)

        code = input('For login enter 1, For signup enter 2: ')
        if code == '1' or code == '2':
            data = '{username:"' + input("Enter username: ") + '",'
            data += 'Password:"' + input("Enter password: ") + '"'
            if code == '2':
                data += ',"mail' + input('Enter mail: ') + '"'
            data += '}'

            sock.send(code.encode() + len(data).to_bytes(4, 'big') + data.encode())
            server_data = sock.recv(1024)
            print(server_data.decode())


if __name__ == '__main__':
    main()
