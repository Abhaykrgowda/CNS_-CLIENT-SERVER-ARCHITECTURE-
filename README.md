# Client-Server Architecture with Encryption

This repository contains implementations of a secure client-server chat application in both C and Python. The applications demonstrate fundamental networking concepts with XOR encryption for message security.

## Overview

The project consists of two implementations:
- **C Version**: Windows-specific implementation using Winsock2
- **Python Version**: Cross-platform implementation with threading support

Both versions feature:
- TCP socket communication
- XOR encryption/decryption of messages
- Real-time bidirectional chat between client and server
- Graceful connection handling

## Project Structure

```
CNS_AAT1/
├── C_Version/
│   ├── client.c          # C client implementation
│   ├── server.c          # C server implementation
│   ├── encryption.c      # XOR encryption functions
│   └── encryption.h      # Encryption header file
├── Python_Version/
│   ├── client.py         # Python client implementation
│   ├── server.py         # Python server implementation
│   └── crypto.py         # XOR encryption module
└── README.md             # This file
```

## Features

### Security
- **XOR Encryption**: All messages are encrypted using XOR cipher with a default key of 5
- **Secure Communication**: Messages are encrypted before transmission and decrypted upon receipt

### Networking
- **TCP Protocol**: Reliable connection-oriented communication
- **Port 8080**: Default communication port for both implementations
- **Localhost**: Configured for local machine communication

### User Experience
- **Interactive Chat**: Real-time bidirectional messaging
- **Exit Commands**: Type 'exit' to gracefully terminate sessions
- **Connection Status**: Clear feedback on connection state

## C Version

### Requirements
- Windows OS
- C compiler with Winsock2 support (Visual Studio, MinGW, etc.)
- ws2_32.lib library

### Compilation

Using Visual Studio or compatible compiler:
```bash
# Compile server
gcc -o server.exe server.c encryption.c -lws2_32

# Compile client  
gcc -o client.exe client.c encryption.c -lws2_32
```

### Usage

1. **Start the Server**:
   ```bash
   ./server.exe
   ```
   The server will listen on port 8080 and wait for client connections.

2. **Start the Client**:
   ```bash
   ./client.exe
   ```
   The client will connect to the server at localhost:8080.

3. **Chat**:
   - Both server and client can send messages
   - Messages are automatically encrypted/decrypted
   - Type 'exit' to end the session

### Technical Details
- Uses Winsock2 API for networking
- Synchronous communication (blocking I/O)
- Single client per server instance
- XOR encryption with key=5

## Python Version

### Requirements
- Python 3.x
- No additional packages required (uses standard library)

### Usage

1. **Start the Server**:
   ```bash
   python server.py
   ```
   The server will listen on port 8080 and wait for client connections.

2. **Start the Client**:
   ```bash
   python client.py
   ```
   The client will connect to the server at localhost:8080.

3. **Chat**:
   - Both server and client can send/receive messages simultaneously
   - Messages are automatically encrypted/decrypted
   - Type 'exit' to end the session

### Technical Details
- Uses Python's `socket` module for networking
- Multithreaded implementation using `threading` module
- Asynchronous send/receive operations
- Single client per server instance
- XOR encryption with key=5

## Encryption Details

Both implementations use XOR encryption:

### Algorithm
```
Encryption: encrypted_char = original_char XOR key
Decryption: original_char = encrypted_char XOR key
```

### Key Features
- **Symmetric**: Same key used for encryption and decryption
- **Reversible**: XOR operation is its own inverse
- **Lightweight**: Minimal computational overhead
- **Default Key**: 5 (can be modified in source code)

**Note**: XOR with a single key is not cryptographically secure and should only be used for educational purposes.

## Usage Instructions

### Starting a Chat Session

1. **Terminal 1 (Server)**:
   ```bash
   # For C version
   ./server.exe
   
   # For Python version
   python server.py
   ```

2. **Terminal 2 (Client)**:
   ```bash
   # For C version
   ./client.exe
   
   # For Python version
   python client.py
   ```

3. **Chat Flow**:
   - Server shows: "Server listening on port 8080..."
   - Client shows: "Connected to server"
   - Both can now exchange messages
   - Messages appear as "You: [your message]" and "Server/Client: [received message]"

### Terminating Sessions
- Type `exit` in either terminal to end the chat
- The other party will be notified and the connection will close
- Both programs will terminate gracefully

## Differences Between Implementations

| Feature | C Version | Python Version |
|---------|-----------|----------------|
| **Platform** | Windows-specific | Cross-platform |
| **Threading** | Single-threaded | Multi-threaded |
| **I/O Model** | Synchronous/Blocking | Asynchronous send/receive |
| **API** | Winsock2 | Python socket module |
| **Compilation** | Required | Interpreted |
| **Dependencies** | ws2_32.lib | None (standard library) |

## Educational Value

This project demonstrates:
- **Socket Programming**: TCP client-server architecture
- **Network Security**: Basic encryption implementation
- **Cross-Platform Development**: Same functionality in different languages
- **Threading Concepts**: Concurrent operations (Python version)
- **Error Handling**: Network error management
- **Protocol Design**: Simple chat protocol implementation

## Potential Enhancements

- **Multiple Clients**: Support concurrent client connections
- **Stronger Encryption**: Implement AES or other secure algorithms
- **GUI Interface**: Add graphical user interface
- **File Transfer**: Extend to support file sharing
- **Authentication**: Add user login/authentication
- **Message History**: Store and retrieve chat history
- **Network Discovery**: Automatic server discovery
- **Configuration**: External configuration files

## Security Considerations

⚠️ **Warning**: The XOR encryption used in this project is for educational purposes only and provides minimal security. For production applications, use established cryptographic libraries and protocols.

## Troubleshooting

### Common Issues

1. **Port Already in Use**:
   - Ensure no other application is using port 8080
   - Wait a few seconds after closing before restarting

2. **Connection Refused**:
   - Start the server before the client
   - Check firewall settings
   - Verify localhost connectivity

3. **Compilation Errors (C)**:
   - Ensure Winsock2 library is available
   - Check compiler flags and linking

4. **Python Import Errors**:
   - Verify Python 3.x installation
   - Ensure crypto.py is in the same directory

## License

This project is for educational purposes. Feel free to modify and extend for learning objectives.

## Author

Part of CNS (Computer Network Security) coursework demonstrating client-server architecture and basic encryption concepts.