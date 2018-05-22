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
public final class PartyDeletePage extends AdminBasePage {
    
    public PartyDeletePage(Party aParty) {
        this.add(new PartyDeleteForm("party_delete", aParty));
        FeedbackPanel feedback = new FeedbackPanel("delete_party_feedback");
        this.add(feedback);
    }
}
