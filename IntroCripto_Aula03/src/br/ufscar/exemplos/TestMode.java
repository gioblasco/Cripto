/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package br.ufscar.exemplos;

import br.ufscar.util.FileName;
import br.ufscar.util.Util;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.security.SecureRandom;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
/**
 *
 * @author yeda
 */
public class TestMode {
    Cipher c;
    SecretKeySpec objKey;
    IvParameterSpec ivParam;
    byte[] cipherText;
    String plain;
    
    public TestMode(){
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
        
        //des.cifraTexto("gZig^ZkZtre");
        //des.cifraArquivoTexto("PADRAO_PARA_BACKUP.txt");
        //des.cifraImagemBMP_RGB("Tux.bmp");
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
    
    public void cifraArquivoTexto(String arq){
        FileInputStream fis;
        FileOutputStream fos;
        byte[] data = new byte[8];
        int tam;
        FileName fn;
        
        try {
            System.out.println("ARQUIVO TEXTO\n");
            fn = new FileName(arq);
            
            // CIFRAGEM
            c.init(Cipher.ENCRYPT_MODE, objKey, ivParam);
            
            fis = new FileInputStream(arq);
            fos = new FileOutputStream(fn.getName()+"_cripto."+fn.getExt());

            tam = fis.available();
            System.out.println("Tamanho do arquivo DE ORIGEM: " + tam);
            
            while(tam > 8){
                fis.read(data);
                //System.out.println(new String(data));
                fos.write(c.update(data));
                tam = fis.available();
            }
            fis.read(data,0,tam);
            fos.write(c.doFinal(data,0,tam));
            fis.close();
            fos.close();
            
            // DECIFRAGEM
            c.init(Cipher.DECRYPT_MODE, objKey, ivParam);
            
            fis = new FileInputStream(fn.getName()+"_cripto."+fn.getExt());
            fos = new FileOutputStream(fn.getName()+"_decripto."+fn.getExt());
            
            tam = fis.available();
            System.out.println("Tamanho do arquivo CRIPTOGRAFADO: " + tam + "\n\n");
            
            while(tam > 8){
                fis.read(data);
                fos.write(c.update(data));
                tam = fis.available();
            }
            fis.read(data,0,tam);
            fos.write(c.doFinal(data,0,tam));
            fis.close();
            fos.close();
            
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    
    public void cifraImagemBMP_RGB(String arq){
        FileInputStream fis;
        FileOutputStream fos;
        byte[] header = new byte[54];
        byte[] data = new byte[8];
        int tam;
        FileName fn;
        
        try {
            System.out.println("ARQUIVO BMP\n");
            fn = new FileName(arq);
            
            // CIFRAGEM
            c.init(Cipher.ENCRYPT_MODE, objKey, ivParam);
            
            fis = new FileInputStream(arq);
            fos = new FileOutputStream(fn.getName()+"_cripto."+fn.getExt());
            fis.read(header);
            //Util.viewHex(header);
            fos.write(header);
            
            tam = fis.available();
            System.out.println("Tamanho do arquivo: " + tam);
            
            while(tam > 8){
                fis.read(data);
                fos.write(c.update(data));
                tam = fis.available();
                //System.out.println("Tamanho do arquivo: " + tam);
            }
            fis.read(data,0,tam);
            fos.write(c.doFinal(data,0,tam));
            fis.close();
            fos.close();
            
            // DECIFRAGEM
            c.init(Cipher.DECRYPT_MODE, objKey, ivParam);
            
            fis = new FileInputStream(fn.getName()+"_cripto."+fn.getExt());
            fos = new FileOutputStream(fn.getName()+"_decripto."+fn.getExt());
            fis.read(header);
            //Util.viewHex(header);
            fos.write(header);
            
            
            tam = fis.available();
            System.out.println("Tamanho do arquivo: " + tam);
            
            while(tam >0){
                fis.read(data);
                fos.write(c.update(data));
                tam = fis.available();
            }
            fis.read(data,0,tam);
            fos.write(c.doFinal(data,0,tam));
            fis.close();
            fos.close();
            
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}

