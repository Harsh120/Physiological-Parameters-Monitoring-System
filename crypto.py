from cryptography.fernet import Fernet

def encryption(msg):
    file = open(r"C:\Users\Intel\Desktop\Project\key.key", 'rb')
    key = file.read()
    file.close()

    encoded = msg.encode()
    f = Fernet(key)
    encrypted = f.encrypt(encoded)
    return encrypted

def decryption(msg):
    file = open(r"C:\Users\Intel\Desktop\Project\key.key", 'rb')
    key = file.read()
    file.close()

    f = Fernet(key)
    decrypted = f.decrypt(msg)

    original = decrypted.decode()
    return original
