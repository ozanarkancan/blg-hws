/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author fikret
 */
import org.apache.wicket.markup.html.link.Link;

public class PartyAdministratorDisplayPageLink extends Link {

    private PartyAdministrator partyadmin;

    public PartyAdministratorDisplayPageLink(String id, PartyAdministrator aPartyAdministrator) {
        super(id);
        this.partyadmin = aPartyAdministrator;
    }

    @Override
    public void onClick() {
        this.setResponsePage(new PartyAdministratorDisplayPage(this.partyadmin));
    }
}
