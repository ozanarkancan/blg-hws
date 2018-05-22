/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author fikret
 */
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.model.CompoundPropertyModel;

public class PartyEditForm extends Form {

    public PartyEditForm(String id, Party aParty) {
        super(id);

        CompoundPropertyModel model = new CompoundPropertyModel(aParty);
        this.setModel(model);

        this.add(new RequiredTextField("title"));
        this.add(new RequiredTextField("year"));
        this.add(new RequiredTextField("partyleader"));
        this.add(new TextField("partyPrinciples"));
    }

    @Override
    public void onSubmit() {
        Party party = (Party) this.getModelObject();
        party.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
        if (!ElectionOrganizer.canAddCandidate()) {
            error("You can add a party until two weeks before election!");
        } else if (PartyDM.getOneParty(party.getTitle(), party.getElectionId()) != null) {
            error("There is a party with same name!");
        } else {
            Application app = (Application) this.getApplication();
            PartyDM deneme = new PartyDM();
            deneme.addParty(party);
            PartyCollection collection = app.getCollection();
            collection.addParty(party);
            this.setResponsePage(new PartyDisplayPage(party));
        }
    }
}