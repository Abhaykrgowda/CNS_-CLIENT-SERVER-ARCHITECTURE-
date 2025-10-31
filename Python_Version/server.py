import socket
import threading
from crypto import encrypt, decrypt

HOST = 'localhost'
PORT = 8080

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)
print(f"Server listening on {HOST}:{PORT}...")

conn, addr = server.accept()
print(f"Connected to client: {addr}")

running = True  # shared flag

def receive_messages():
    global running
    while running:
        try:
            data = conn.recv(1024)
            if not data:
                print("Client disconnected.")
                running = False
                break
            decrypted_msg = decrypt(data.decode())
            if decrypted_msg.lower() == "exit":
                print("Client ended chat.")
                running = False
                break
            print(f"\nClient: {decrypted_msg}")
        except:
            running = False
            break

def send_messages():
    global running
    while running:
        try:
            msg = input("You: ")
            encrypted_msg = encrypt(msg)
            conn.send(encrypted_msg.encode())
            if msg.lower() == "exit":
                running = False
                break
        except:
            break

recv_thread = threading.Thread(target=receive_messages)
send_thread = threading.Thread(target=send_messages)

recv_thread.start()
send_thread.start()

recv_thread.join()
send_thread.join()

conn.close()
server.close()
print("Server closed.")
