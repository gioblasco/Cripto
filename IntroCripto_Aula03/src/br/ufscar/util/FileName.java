/*
 * FileName.java
 *
 * Created on 20 de Mar�o de 2003, 01:17
 */

package br.ufscar.util;

import java.io.File;
import java.io.Serializable;

/** This class allows to get the path, the name and the extension of a qualified file name.
 * @author LARC - Laborat�rio de Arquitetura e Redes de Computadores
 */
public class FileName implements Serializable {
    
    /*Propriedade com o nome do arquivo*/
    private String name = "";
    /*Propriedade com o caminho do arquivo*/
    private String path = "";
    /*Propriedade com a extens�o do arquivo*/
    private String ext = "";
    
    /** Creates a new instance of FileName
     * @param file A qualified file name (full fiel name).
     */
    public FileName(String file) throws NullPointerException{
        this.setFileName(file);
    }
    
    /** Sets a qualified file name.
     * @param file A qualified file name (full fiel name).
     */    
  public void setFileName(String file) throws NullPointerException{
        if( (file != null)&&(file.length()!=0) ) {
            int ind = file.lastIndexOf(File.separator);
            String fileName = "";
            if(ind >= 0){
                this.path = file.substring(0, ind);
                if(ind < file.length()-1){
                    fileName = file.substring(ind+1);
                }
            } else {
                this.path = "";
		fileName = file;
            }
            int indExt = fileName.lastIndexOf(".");
            if(indExt >= 0) {
                String nameTemp = fileName.substring(indExt+1);
                this.name = fileName.substring(0, fileName.lastIndexOf("."));
                this.ext = fileName.substring(fileName.lastIndexOf(".")+1);                
                if (this.name.length() == 0){
                    this.name = new String("." + this.ext);
                    this.ext = "";
                }
            } else {
                this.name = fileName;
                this.ext = "";
            }
        } else {
            throw new NullPointerException();
        }        
    }
  
    /** Seta nome do arquivo
     *@param newName Novo nome do arquivo
     */
    public void setName(String newName) {
        this.name = newName;
    }
    
    /** Seta extens�o do arquivo
     *@param extFile Extens�o a ser associada ao nome do arquivo
     */
    public void setExt(String extFile) {
        this.ext = extFile;
    }
    
    /** Seta caminho do arquivo
     *@param newPath Caminho associado ao arquivo
     */
    public void setPath(String newPath) {
        this.path = newPath;
    }
    
    /** Gets the name of the file without the extension.
     * @return the name of file without the extension.
     */    
    public String getName() {
        return this.name;
    }
    
    public String getFullName() {
        return this.path + File.separator + this.getNameExt();
    }
    
    /** Gets the extension of the file name.
     * @return the extension of file name.
     */    
    public String getExt() {
        return this.ext;
    }
    
    /** Gets the path of the file name.
     * @return the path of file name.
     */    
    public String getPath() {
        return this.path;
    }
    
    /** Gets the name plus extension of the file name.
     * @return the name plus extension of file name.
     */    
    public String getNameExt() {
        if (this.ext != ""){
            return (this.name + "." + this.ext);
        } else {
            return this.name;
        }
            
    }
    
    /** Change the extension of the file name.
     * @param ext the new extension of the file name.
     */    
    public void changeExt(String ext) {
        this.ext = ext;
    }
}
