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
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.CompoundPropertyModel;

public class PartyAdministratorEditForm extends Form {

    User user = new User();

    public PartyAdministratorEditForm(String id, PartyAdministrator aPartyAdministrator) {
        super(id);

        CompoundPropertyModel model = new CompoundPropertyModel(aPartyAdministrator);
        this.setModel(model);
        this.add(new RequiredTextField("userName"));
        this.add(new RequiredTextField("partyTitle"));

    }

    @Override
    public void onSubmit() {
        PartyAdministrator partyAdministrator = (PartyAdministrator) this.getModelObject();
        user.setUsername(partyAdministrator.getUserName());
        user.setPassword(PasswordGenerator.getPassword());
        user.setUserType(1);
        if (UserDM.getUser(user.getUsername()) == null) {
            if (PartyDM.getOneParty(partyAdministrator.getPartyTitle(), partyAdministrator.getElectionId()) != null) {

                UserDM.addUser(user);
                partyAdministrator.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
                Application app = (Application) this.getApplication();
                PartyAdministratorDM deneme = new PartyAdministratorDM();
                deneme.addPartyAdmin(partyAdministrator);
                PartyAdministratorCollection collection1 = app.getCollection1();
                collection1.addPartyAdministrator(partyAdministrator);
                info("Party administrator was added succesfully.");
            } else {
                error("There is not a party with this name!");
            }


        } else {
            error("There is an admin with same username!");
        }
    }
}