import sys
import binascii

S = [0] * 256
T = [0] * 256
cifra = ""
chave = ""

def swap(posi, posj):
    aux = S[posi]
    S[posi] = S[posj]
    S[posj] = aux

def stream():
    D = ""
    i = 0
    j = 0
    for x in range(0, len(cifra)):
        i = (i+1) % 256
        j = (j + S[i]) % 256
        swap(i, j)
        t = (S[i] + S[j]) % 256
        D = D + chr(cifra[x] ^ S[t])
    print(D)

def init():
    for i in range(0, 256):
        S[i] = i
        T[i] = ord(chave[i % len(chave)])
    j = 0
    for i in range(0, 256):
        j = (j + S[i] + T[i]) % 256
        swap(i, j)


if(len(sys.argv)!=3):
    print("Chamada inválida use: $ python3 RC4_620378.py ARQUIVO_CIFRA ARQUIVO_CHAVE")
    sys.exit(1)

arquivo_cifra = open(sys.argv[1], "r")
cifra = arquivo_cifra.read()
arquivo_cifra.close()

arquivo_chave = open(sys.argv[2], "r")
chave = arquivo_chave.read().rstrip()
arquivo_chave.close()

# converter cifra em hexadecimal para ascii
cifra = binascii.unhexlify(cifra.rstrip())

init()
stream()
