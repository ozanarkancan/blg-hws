/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.text.AttributedCharacterIterator;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author Fikret
 */
public final class PartyAdministratorUpdatePage extends AdminBasePage {

    PartyAdministrator partyAdmin = new PartyAdministrator();

    public PartyAdministratorUpdatePage() {
        super();

        Form partyAdminUpdateForm = new Form("partyAdminUpdateForm");
        add(partyAdminUpdateForm);

        final RequiredTextField userNameField = new RequiredTextField("userName",
                new PropertyModel<String>(partyAdmin, "userName"));
        partyAdminUpdateForm.add(userNameField);

        final TextField partyTitleField = new TextField("partyTitle",
                new PropertyModel<String>(partyAdmin, "partyTitle"));
        partyAdminUpdateForm.add(partyTitleField);

        partyAdmin.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());

        Button getUserButton = new Button("getPartyAdminInfo") {

            @Override
            public void onSubmit() {

                if (PartyAdministratorDM.getOneAdmin(partyAdmin.getUserName()) != null) {
                    userNameField.add(AttributeModifier.replace("readonly", "readonly"));
                    partyTitleField.add(new AttributeModifier("value", PartyAdministratorDM.getOneAdmin(partyAdmin.getUserName()).getPartyTitle()));
                } else {
                    error("Requested party admin does not exist in database!");
                }
            }
        };
        partyAdminUpdateForm.add(getUserButton);

        Button updatePartyAdminButton = new Button("update_partyAdmin") {

            @Override
            public void onSubmit() {

                if (PartyAdministratorDM.getOneAdmin(partyAdmin.getUserName()) != null) {
                    if (PartyDM.getOneParty(partyAdmin.getPartyTitle(), partyAdmin.getElectionId()) != null) {
                        PartyAdministratorDM.updatePartyAdmin(partyAdmin);
                        partyTitleField.add(new AttributeModifier("value", PartyAdministratorDM.getOneAdmin(partyAdmin.getUserName()).getPartyTitle()));
                        info("Specified party admin was updated successfully");
                    }else{
                        error("Party was not found!");
                    }
                }
            }
        };
        partyAdminUpdateForm.add(updatePartyAdminButton);

        FeedbackPanel feedback = new FeedbackPanel("updatePartyAdminFeedback");
        this.add(feedback);
    }
}
