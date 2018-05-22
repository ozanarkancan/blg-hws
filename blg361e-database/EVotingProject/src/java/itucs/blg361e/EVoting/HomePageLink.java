/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import org.apache.wicket.markup.html.link.Link;

/**
 *
 * @author OZAN
 */
public class HomePageLink extends Link {

    public HomePageLink(String id)
    {
        super(id);
    }
    @Override
    public void onClick() {
        HomePage homePage = new HomePage();
        this.setResponsePage(homePage);
    }
    
}
