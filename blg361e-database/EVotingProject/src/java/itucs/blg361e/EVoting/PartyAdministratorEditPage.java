
package itucs.blg361e.EVoting;

import org.apache.wicket.markup.html.panel.FeedbackPanel;


/**
 *
 * @author fikret
 */
public final class PartyAdministratorEditPage extends AdminBasePage {

    public PartyAdministratorEditPage(PartyAdministrator aPartyadmin) {
        this.add(new PartyAdministratorEditForm("partyadmin_edit", aPartyadmin));
        
        FeedbackPanel feedback = new FeedbackPanel("add_partyAdmin_feedback");
        this.add(feedback);
    }
}