/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

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
public final class PartyUpdatePage extends AdminBasePage {

    Party party = new Party();

    public PartyUpdatePage() {
        super();

        Form partyUpdateForm = new Form("partyUpdateForm");
        add(partyUpdateForm);

        final RequiredTextField titleField = new RequiredTextField("title",
                new PropertyModel<String>(party, "title"));
        partyUpdateForm.add(titleField);

        final TextField yearField = new TextField("year",
                new PropertyModel<String>(party, "year"));
        partyUpdateForm.add(yearField);

        final TextField partyleaderField = new TextField("partyleader",
                new PropertyModel<String>(party, "partyleader"));
        partyUpdateForm.add(partyleaderField);

        final TextField partyPrinciplesField = new TextField("partyPrinciples",
                new PropertyModel<String>(party, "partyPrinciples"));
        partyUpdateForm.add(partyPrinciplesField);

        party.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());



        Button getPartyButton = new Button("getPartyInfo") {

            @Override
            public void onSubmit() {

                if (PartyDM.getOneParty(party.getTitle(), party.getElectionId()) != null) {
                    if(ElectionOrganizer.canAddCandidate())
                    {
                    titleField.add(AttributeModifier.replace("readonly", "readonly"));
                    yearField.add(new AttributeModifier("value", PartyDM.getOneParty(party.getTitle(), party.getElectionId()).getYear()));
                    partyleaderField.add(new AttributeModifier("value", PartyDM.getOneParty(party.getTitle(), party.getElectionId()).getPartyLeader()));
                    partyPrinciplesField.add(new AttributeModifier("value", PartyDM.getOneParty(party.getTitle(), party.getElectionId()).getPartyPrinciples()));
                    }
                    else{
                        error("You can update a party until two weeks before election!");
                    }
                } else {
                    error("Requested party does not exist in database!");
                }
            }
        };
        partyUpdateForm.add(getPartyButton);

        Button updatePartyButton = new Button("update_party") {

            @Override
            public void onSubmit() {

                if (PartyDM.getOneParty(party.getTitle(), party.getElectionId()) != null) {
                    PartyDM.updateParty(party);
                    yearField.add(new AttributeModifier("value", PartyDM.getOneParty(party.getTitle(), party.getElectionId()).getYear()));
                    partyleaderField.add(new AttributeModifier("value", PartyDM.getOneParty(party.getTitle(), party.getElectionId()).getPartyLeader()));
                    partyPrinciplesField.add(new AttributeModifier("value", PartyDM.getOneParty(party.getTitle(), party.getElectionId()).getPartyPrinciples()));

                    info("Specified party was updated successfully");
                }
            }
        };
        partyUpdateForm.add(updatePartyButton);

        FeedbackPanel feedback = new FeedbackPanel("updatePartyFeedback");
        this.add(feedback);


    }
}
