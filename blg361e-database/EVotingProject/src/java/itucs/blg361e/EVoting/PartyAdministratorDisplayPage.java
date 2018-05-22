/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;


/**
 *
 * @author fikret
 */
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.link.Link;

public final class PartyAdministratorDisplayPage extends AdminBasePage {

    public PartyAdministratorDisplayPage(PartyAdministrator aPartyAdministrator) {
        this.add(new Label("userName", aPartyAdministrator.getUserName()));       
        this.add(new Label("partyTitle", aPartyAdministrator.getPartyTitle()));
        
    }
}
