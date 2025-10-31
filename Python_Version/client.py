import socket
import threading
from crypto import encrypt, decrypt

HOST = 'localhost'
PORT = 8080

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))
print(f"Connected to server at {HOST}:{PORT}")

running = True  # shared flag

def receive_messages():
    global running
    while running:
        try:
            data = client.recv(1024)
            if not data:
                print("Server disconnected.")
                running = False
                break
            decrypted_msg = decrypt(data.decode())
            if decrypted_msg.lower() == "exit":
                print("Server ended chat.")
                running = False
                break
            print(f"\nServer: {decrypted_msg}")
        except:
            running = False
            break

def send_messages():
    global running
    while running:
        try:
            msg = input("You: ")
            encrypted_msg = encrypt(msg)
            client.send(encrypted_msg.encode())
            if msg.lower() == "exit":
                running = False
                break
        except:
            running = False
            break

recv_thread = threading.Thread(target=receive_messages)
send_thread = threading.Thread(target=send_messages)

recv_thread.start()
send_thread.start()

recv_thread.join()
send_thread.join()

client.close()
print("Client closed.")
