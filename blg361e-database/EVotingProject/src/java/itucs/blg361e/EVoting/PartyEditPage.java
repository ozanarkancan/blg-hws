/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import org.apache.wicket.markup.html.panel.FeedbackPanel;


/**
 *
 * @author fikret
 */
public final class PartyEditPage extends AdminBasePage {

    public PartyEditPage(Party aParty) {
        this.add(new PartyEditForm("party_edit", aParty));
        
        FeedbackPanel feedback = new FeedbackPanel("add_party_feedback");
        this.add(feedback);
    }
}