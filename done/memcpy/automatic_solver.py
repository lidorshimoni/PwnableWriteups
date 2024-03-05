
import socket
import time

def main():
    for i in range(128,129):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect(('pwnable.kr', 9022))
            sock.send(f'16\n32\n64\n{i}\n256\n300\n900\n2000\n3000\n5000\n'.encode())
            time.sleep(3)
            data = sock.recv(0xFFFF).decode()
            print(data)
            if "experiment 5" in data:
                print(f'Found: {i}')
                break
            elif "experiment 4" not in data:
                print(f'{i} failed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
            else:
                print(f'{i} failed')
            sock.close()
        except WindowsError as e:
            print(f'Error: {e}')
            continue



if __name__ == '__main__':
    main()