/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Elector;

import itucs.blg361e.EVoting.AdminBasePage;
import itucs.blg361e.EVoting.ElectionOrganizer;
import itucs.blg361e.EVoting.User;
import itucs.blg361e.EVoting.UserDM;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author bahti
 */
public final class ElectorDeletePage extends AdminBasePage {

    Elector elector = new Elector();
    User user = new User();

    public ElectorDeletePage() {
        super();

        Form elector_delete_form = new Form("elector_delete_form");
        add(elector_delete_form);

        RequiredTextField TCnumberField = new RequiredTextField("TCnumber",
                new PropertyModel<String>(elector, "TCnumber"));
        elector_delete_form.add(TCnumberField);

        Button delete_elector_button = new Button("delete_elector") {
            @Override
            public void onSubmit() {

                if (ElectorDM.getOneElector(elector.getTCNumber()) != null && ElectionOrganizer.canAddCandidate()) {

                    UserDM.deleteUser(UserDM.getUser(elector.getTCNumber().toString()));

                    ElectorDM.deleteElector(elector);

                    info("Specified Elector was deleted successfully");
                } else {
                    if(ElectorDM.getOneElector(elector.getTCNumber()) == null)
                        error("Requested Elector does not exist in database!");
                    else
                        error("Elector can not be deleted due to time constraints!");
                }
            }
        };
        elector_delete_form.add(delete_elector_button);

        FeedbackPanel feedback = new FeedbackPanel("delete_elector_feedback");
        this.add(feedback);
    }
}
