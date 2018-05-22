/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author fikret
 */
import itucs.blg361e.EVoting.ElectionOrganizer.State;
import itucs.blg361e.EVoting.Elector.ElectorPage;
import java.util.ArrayList;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.model.CompoundPropertyModel;

public class PartyDeleteForm extends Form {

    User user = new User();

    public PartyDeleteForm(String id, Party aParty) {
        super(id);

        CompoundPropertyModel model = new CompoundPropertyModel(aParty);
        this.setModel(model);

        this.add(new RequiredTextField("title"));
    }

    @Override
    public void onSubmit() {
        Party party = (Party) this.getModelObject();
        party.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
        if (ElectionOrganizer.state == State.NOTSTARTED) {
            if (PartyDM.getOneParty(party.getTitle(), party.getElectionId()) == null) {
                error("There is not a party with this name !");
            } else {

                ArrayList<PartyAdministrator> partyadmin = PartyAdministratorDM.getPartyAdministratorWithParty(party.getTitle(), party.getElectionId());
                for (PartyAdministrator p : partyadmin) {
                    PartyAdministratorDM.deletePartyAdmin(p);
                    UserDM.deleteUser(UserDM.getUser(p.getUserName()));
                }
                Application app = (Application) this.getApplication();
                PartyDM deneme = new PartyDM();
                deneme.deleteParty(party);
                PartyCollection collection = app.getCollection();
                collection.deleteParty(party);

                ArrayList<Candidate> candidates = CandidateDM.getCandidateWithPartyTitle(party.getTitle());
                for (Candidate can : candidates) {
                    CandidateDM.deleteCan(can);
                    UserDM.deleteUser(UserDM.getUser(can.getUserName()));
                }

                this.setResponsePage(new PartyPage());

            }
        } else {
            error("Election has been started");
        }
    }
}