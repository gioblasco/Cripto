# le entrada
entrada = input()
entrada = entrada.upper();

# define sequencia de estatistica
letras = ['A', 'E', 'O', 'S', 'R', 'D', 'N', 'I', 'T', 'M', 'U', 'L', 'C', 'V', 'P', 'G', 'Q', 'B', 'F', \
'H', 'J', 'X', 'Z', 'K', 'Y', 'W']

# contabiliza ocorrencias
ocorrencias = [0]*26
for i in range(0, len(entrada)):
    if entrada[i].isalpha():
        ocorrencias[ord(entrada[i])-65] += 1

# printa ocorrencias
print("\n-- LISTA DE OCORRENCIAS EM ORDEM ALFABETICA --")
for j in range(0, 26):
    print("%c - %d" % (chr(j+65), ocorrencias[j])),

# printa ocorrencias ordenadas
ordenado = []
print("\n-- LISTA DE OCORRENCIAS EM ORDEM DE MAIOR INCIDENCIA --")
for k in range(0, 26):
    max_value = max(ocorrencias)
    if max_value > 0:
        print("%c - %d ---> %c" % (chr(ocorrencias.index(max_value)+65), max_value, letras[k]))
    else:
        print("%c - %d" % (chr(ocorrencias.index(max_value)+65), max_value))
    ordenado.append(chr(ocorrencias.index(max_value)+65))
    ocorrencias[ocorrencias.index(max_value)] = -1

# printa mensagem decifrada
saida = []
for j in range(0, len(entrada)):
    if entrada[j].isalpha():
        indice = ordenado.index(entrada[j])
        saida.append(letras[indice])

print("\nMensagem decifrada: %s\n" % ''.join(saida))

while True:
    # verifica se quer editar letras    
    while True:
        msg = input("Deseja alterar alguma letra? \n1 - Sim\n2 - Nao\n")
        if msg != '1' and msg != '2':
            print("Entrada invalida\n")
            continue
        else:
            break

    # se quer substituir 
    if msg == '1':
        while True:
            let1 = input("\nQual letra quer substituir? ")
            if not let1.isalpha():
                print("%s nao eh uma letra" % let1)
                continue
            else:
                break
        while True:
            let2 = input("Por qual letra? ")
            if not let2.isalpha():
                print("%s nao eh uma letra" % let2)
                continue
            else:
                break
        while True:
            try:
                indice = saida.index(let1.upper())
                saida[indice] = let2.upper()
            except ValueError:
                break
        print("\nNova mensagem decifrada: %s\n" % ''.join(saida))
    else:
        break
