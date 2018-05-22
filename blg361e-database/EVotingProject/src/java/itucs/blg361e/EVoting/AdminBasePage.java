/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;


/**
 *
 * @author coskun
 */
public class AdminBasePage extends BasePage {

    public AdminBasePage() {
        super();
        
        add(new AdminPanel("admin_panel"));
    }
    
}
