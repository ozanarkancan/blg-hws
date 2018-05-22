/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author fikret
 */
import itucs.blg361e.EVoting.Elector.ElectorPage;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.model.CompoundPropertyModel;

public class PartyAdministratorDeleteForm extends Form {

    public PartyAdministratorDeleteForm(String id, PartyAdministrator aPartyAdministrator) {
        super(id);

        CompoundPropertyModel model = new CompoundPropertyModel(aPartyAdministrator);
        this.setModel(model);

        this.add(new RequiredTextField("userName"));
    }

    @Override
    public void onSubmit() {
        PartyAdministrator partyAdministrator = (PartyAdministrator) this.getModelObject();
        if (PartyAdministratorDM.getOneAdmin(partyAdministrator.getUserName()) == null) {
            error("There is not a party admin with this name !");
        } else {
            Application app = (Application) this.getApplication();
            PartyAdministratorDM deneme = new PartyAdministratorDM();
            deneme.deletePartyAdmin(partyAdministrator);
            PartyAdministratorCollection collection1 = app.getCollection1();
            collection1.deletePartyAdministrator(partyAdministrator);
            UserDM.deleteUser(UserDM.getUser(partyAdministrator.getUserName()));
            info ("Party administrator was deleted succesfully.");
        }
    }
}
