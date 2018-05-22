/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.io.Serializable;

/**
 *
 * @author coskun
 */

public class User implements Serializable {
    
    private String username;
    private String password;
    private Integer userType;
    
    public User() {
    }
    
    public User(String username, String password, Integer userType) {
        this.username = username;
        this.password = password;
        this.userType = userType;
    }
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
    
    public void setUserType(Integer userType) {
        this.userType = userType;
    }
    
    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public Integer getUserType() {
        return userType;
    }
}
