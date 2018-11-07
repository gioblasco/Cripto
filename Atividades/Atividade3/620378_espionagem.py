import sys

if(len(sys.argv)!=2):
    print("Chamada inválida use: $ python3 s.py ARQUIVO_ENTRADA")
    sys.exit(1)

# leitura do arquivo
arquivo = open(sys.argv[1], "r")
texto = arquivo.readline()
cifrado = arquivo.readline()
arquivo.readline()
lista = arquivo.readlines()

texto_bin = bin(int(texto))[2:].zfill(32)

# aplicando a logica inversa do xor para encontrar a chave
chave = int(texto) ^ int(cifrado)

# verifica mensagens criptografadas
for msg in lista:
    # transforma msg criptografada para binario e faz xor com chave encontrada
    binario = bin(int(msg) ^ chave)[2:].zfill(32)
    if texto_bin[:8] == binario[:8]:
        print(int(binario[16:], 2))
