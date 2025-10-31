#include "encryption.h"
#include <string.h>

void encrypt(char *msg, int key) {
    for (int i = 0; i < strlen(msg); i++) {
        msg[i] = msg[i] ^ key;  // simple XOR encryption
    }
}

void decrypt(char *msg, int key) {
    encrypt(msg, key);  // XOR is reversible
}
