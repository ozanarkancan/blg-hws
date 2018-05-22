/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.util.UUID;

/**
 *
 * @author coskun
 */
public class PasswordGenerator {
    private static UUID password;
    
    public PasswordGenerator() {
        // generate random unique ids
        password = UUID.randomUUID();
    }
    
    public static String getPassword() {
        new PasswordGenerator();
        
        // generates unique ids like 10d1b913-8985-421c-8c20-00baaa1166c6
        return String.valueOf(password).split("-")[4];
    }
}
