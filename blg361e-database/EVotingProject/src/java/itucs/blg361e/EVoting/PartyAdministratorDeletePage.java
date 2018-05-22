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
public final class PartyAdministratorDeletePage extends AdminBasePage {

    public PartyAdministratorDeletePage(PartyAdministrator aPartyadmin) {
        this.add(new PartyAdministratorDeleteForm("partyadministrator_delete", aPartyadmin));
        FeedbackPanel feedback = new FeedbackPanel("delete_partyAdmin_feedback");
        this.add(feedback);
    }
}
