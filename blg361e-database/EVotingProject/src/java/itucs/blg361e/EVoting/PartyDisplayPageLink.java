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

public class PartyDisplayPageLink extends Link {

    private Party party;

    public PartyDisplayPageLink(String id, Party aParty) {
        super(id);
        this.party = aParty;
    }

    @Override
    public void onClick() {
        this.setResponsePage(new PartyDisplayPage(this.party));
    }
}
