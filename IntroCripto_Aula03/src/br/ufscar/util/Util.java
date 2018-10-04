/*
 * Util.java
 *
 * Created on August 27, 2002, 3:50 PM
 */

package br.ufscar.util;

/** Esta classe possui metodos estaticos de apoio para atuar com valores hexadecimais.
 *
 * @author Yeda Regina Vetnurini
 */
public class Util {
    /** Valores hexadecimais min�sculos */
    static String hex[]={"0","1","2","3","4","5","6","7","8","9", "a","b","c","d","e","f"};
    /** Valores hexadecimais mai�sculos */
    static char[] cHex = {'0','1','2','3','4','5','6','7','8','9', 'A','B','C','D','E','F'};
    
    /** Mostra bytes no formato hexadecimal. S�o utilizadas linhas de 16 bytes.
     *
     * @param value bytes a serem apresentados.
     */
    public static void viewHex(byte[] value) {
        int i;
        
        if(value == null) {
            System.out.println("Null object ...");
            return;
        }
        
        System.out.println("DADOS: ");
        for(i=0;i<value.length;i++) {
            if((i>0) && ((i%12)==0)) System.out.println("");
            
            System.out.print(hex[(value[i]>>4)& 0x0f] + hex[value[i] & 0x0f] + " ");
        }
        System.out.println(" ");
    }
    
    /** Converte bytes em string de valores hexadecimais.
     *
     * @param value bytes a serem convertidos.
     * @return a string de valores hexadecimais.
     */
    public static String byteToHex(byte[] value) {
        int i;
        char[] vHex = new char[value.length*2];
        for(i=0;i<value.length;i++) {
            vHex[i*2] = cHex[(value[i]>>4)& 0x0f];
            vHex[i*2+1] = cHex[value[i] & 0x0f];
        }
        return (new String(vHex));
    }
    
    /** Converte uma string em Hexadecimal para um vetor de Bytes.
     *
     * @param value string de valores hexadecimais.
     * @return os bytes convertidos.
     */
    public static byte[] hexToByte(String value) {
        int i, x, p1, p2, pTmp;
        byte [] stringValue = value.getBytes();
        byte [] byteValue = new byte [stringValue.length/2];
        
        x = 0;
        for( i=0;i<stringValue.length;i=i+2) {
            if ( stringValue[i] <= '9' ) {
                p1 = stringValue [i] - '0';
            } else {
                p1 = stringValue [i] - 'A' + 10;
            }
            if ( stringValue[i+1] <= '9' ) {
                p2 = stringValue [i+1] - '0';
            } else {
                p2 = stringValue [i+1] - 'A' + 10;
            }
            
            pTmp = (p1 *16) + p2;
            byteValue [x] = (byte) pTmp;
            x++;
        }
        return byteValue;
    }
    
    /** Converts bytes in string of char values.
     * @param value the bytes
     * @return the string of char values.
     */
    public static String byteToString(byte[] value) {
        StringBuffer sb = new StringBuffer();
        int i;
        for (i=0;i<value.length;i++) {
            byte c = (byte)value[i];
            sb.append((char)c);
        }
        return sb.toString();
    }
}
