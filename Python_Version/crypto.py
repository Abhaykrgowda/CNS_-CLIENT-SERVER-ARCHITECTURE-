def encrypt(msg, key=5):
    return ''.join([chr(ord(c) ^ key) for c in msg])

def decrypt(msg, key=5):
    return encrypt(msg, key)
