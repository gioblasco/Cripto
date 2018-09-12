entrada = input()
entrada = entrada.upper();
letras = ['A', 'E', 'O', 'S', 'R', 'D', 'N', 'I', 'T', 'M', 'U', 'L', 'C', 'V', 'P', 'G', 'Q', 'B', 'F', \
'H', 'J', 'X', 'Z', 'K', 'Y', 'W']

ocorrencias = [0]*26
for i in range(0, len(entrada)):
    if entrada[i].isalpha():
        ocorrencias[ord(entrada[i])-65] += 1

print("\n-- LISTA DE OCORRENCIAS EM ORDEM ALFABETICA --")
for j in range(0, 26):
    print("%c - %d" % (chr(j+65), ocorrencias[j])),

print("\n-- LISTA DE OCORRENCIAS EM ORDEM DE MAIOR INCIDENCIA --")
for k in range(0, 26):
    max_value = max(ocorrencias)
    if max_value > 0:
        print("%c - %d ---> %c" % (chr(ocorrencias.index(max_value)+65), max_value, letras[k]))
    else:
        print("%c - %d" % (chr(ocorrencias.index(max_value)+65), max_value))
    ocorrencias[ocorrencias.index(max_value)] = -1
