/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package br.ufscar.exemplos;

import br.ufscar.util.Util;
import java.security.SecureRandom;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

/**
 **************************  A CONSTRUIR **************************************
 * 
 * @author yeda
 */
public class TesteRSA {
    Cipher c;
    SecretKeySpec objKey;
    IvParameterSpec ivParam;
    byte[] cipherText;
    String plain;
    
    public TesteRSA(){
        SecureRandom sr = new SecureRandom();
        byte[] ivTemp = new byte[8];
        sr.nextBytes(ivTemp);
        ivParam = new IvParameterSpec(ivTemp);
        byte[] key = "12345678".getBytes();
        objKey = new SecretKeySpec(key, "DES");
        try{
            c = Cipher.getInstance("DES/CBC/PKCS5PADDING");
        } catch(Exception e){
            e.printStackTrace();
        }
    }
    public static void main(String[] args) { 
        TestMode des = new TestMode();
        
        des.cifraTexto("gZig^ZkZtre");
        
    }
       
    public void cifraTexto(String text){
            
        try {
            // CIFRAGEM
            c.init(Cipher.ENCRYPT_MODE, objKey,ivParam);
            cipherText = c.doFinal(text.getBytes());
            System.out.println("TEXTO SIMPLES \n\n"+ "Bytes após cifrado (" + cipherText.length + "):");
            Util.viewHex(cipherText);
            c.init(Cipher.DECRYPT_MODE, objKey,ivParam);
            plain = new String(c.doFinal(cipherText));
            System.out.println("Texto decifrado: " + plain + "\n\n");
            
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
