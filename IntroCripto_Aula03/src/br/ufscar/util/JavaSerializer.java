/*
 * JavaSerializer.java
 *
 * Created on 19 de Janeiro de 2005, 14:06
 */

package br.ufscar.util;

import java.io.*;

/** This class use the Java object serialization to save and recover the seirializable objects form/of files.
 *
 * @author Yeda Regina Venturini
 */
public class JavaSerializer {
    /** Serialized object . */
    private byte[] objSerialized;
    
    /** Creates a new instance of JavaSerializer. */
    public JavaSerializer() {
    }
    
     /**
     *  Recovers the serialized object stored in the filePathName.
     * 
     * @param filePathname The path of file.
     * @throws IOException If an error occurs during Serialization. The exception cause can be recovered through the getCause().
     */
    public void loadObject(String filePathname) throws IOException {
        IOException ioException = null;
        
        try {
            FileInputStream input = new FileInputStream (filePathname);
            this.objSerialized = new byte[input.available()];
            input.read(this.objSerialized);
            input.close ();
        } catch (FileNotFoundException fnfe) {
            ioException = new IOException("File not found.");
            ioException.initCause(fnfe);
            throw ioException;
        } catch (IOException ioe) {
            ioException = new IOException("Error reading file.");
            ioException.initCause(ioe);
            throw ioException;
        } catch (NullPointerException npe) {
            ioException = new IOException("The file name is null.");
            ioException.initCause(npe);
            throw ioException;
        }
    }
    
    /**
     * Loads a serializable object.
     * 
     * @param obj Serializable object
     * @throws IOException If an error occurs during serialization.
     */
    public void loadObject(Serializable obj) throws IOException {        
        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            ObjectOutputStream output = new ObjectOutputStream(out);
            output.writeObject(obj);
            output.close(); 
            this.objSerialized = out.toByteArray();
            out.close();
        } catch (IOException ioe) {
            throw new IOException("Error in serializable object.");
        } catch (NullPointerException npe) {
            throw new IOException("Null serializable object.");
        }
    }
         
    /** Recovers the Object of the loaded serialized object.
     *
     *@return Serialized object
     *@throws IOException If an error occurs during object deserialization.
     */
    public Object getObject() throws IOException {
        Object obj = null;
        try {
            ByteArrayInputStream in = new ByteArrayInputStream(this.objSerialized);
            ObjectInputStream input = new ObjectInputStream(in);
            obj = input.readObject();
            input.close ();
            in.close();        
        } catch (ClassNotFoundException cnfe) {
            throw new IOException("Invalid object type.");
        } catch (IOException ioe) {
            throw new IOException("Error recovering serialized object.");
        }    
        return obj;
    }
    
    
    /** Gets the bytes of serialized object.
     *
     *@return The bytes of serialized object.
     */
    public byte[] getObjSerialized() {
        return this.objSerialized;
    }
    
    /** Sets the bytes of serialized object.
     *
     *@param obj The bytes of serialized object.
     */
    public void setObjSerialized(byte[] obj) {
        this.objSerialized = obj;
    }
    
    /** Saves the serialized object in a file.
     * 
     * @param filePathname The file name to save the serialized object.
     * @throws IOException If an error occurs saving file.
     */
    public void saveObject(String filePathname) throws IOException {
        File file = new File(filePathname);
        if(!file.exists()){
            File folder = file.getParentFile();
            folder.mkdirs();
        }
        try {
            FileOutputStream output = new FileOutputStream(filePathname);
            output.write(this.objSerialized);
            output.close();
        } catch (IOException ioe) {
            throw new IOException("Error saving file.");
        } catch (NullPointerException npe) {
            throw new IOException("Null file name.");
        }
    }
    
    /** Returns the length of the loaded serialized object.
     *
     *@return The length of the loaded serialized object.
     */
    public long size() {
        return this.objSerialized.length;
    }
}
