/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Elector;

/**
 *
 * @author bahti
 */
import org.apache.wicket.markup.html.link.Link;

public class ElectorDisplayPageLink extends Link {

    private Elector elector;

    public ElectorDisplayPageLink(String id, Elector e) {
        super(id);
        this.elector = e;
    }

    @Override
    public void onClick() {
        this.setResponsePage(new ElectorPage());
    }
}
