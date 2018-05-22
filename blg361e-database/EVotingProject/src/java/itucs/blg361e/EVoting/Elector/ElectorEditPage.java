/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author bahti
 */
package itucs.blg361e.EVoting.Elector;

import itucs.blg361e.EVoting.AdminBasePage;
import itucs.blg361e.EVoting.BasePage;
import itucs.blg361e.EVoting.ElectionEditorPage;
import itucs.blg361e.EVoting.ElectionOrganizer;
import itucs.blg361e.EVoting.ElectionOrganizer.State;
import itucs.blg361e.EVoting.PasswordGenerator;
import itucs.blg361e.EVoting.User;
import itucs.blg361e.EVoting.UserDM;
import java.sql.Date;
import org.apache.wicket.markup.head.IHeaderResponse;
import org.apache.wicket.markup.head.JavaScriptHeaderItem;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;

import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;

import org.apache.wicket.model.PropertyModel;
import org.apache.wicket.request.resource.JavaScriptResourceReference;

public class ElectorEditPage extends AdminBasePage {

    Elector elector = new Elector();
    User user = new User();

    public ElectorEditPage() {
        super();

        Form elector_add_form = new Form("elector_add_form");
        add(elector_add_form);

        RequiredTextField TCnumberField = new RequiredTextField("TCnumber",
                new PropertyModel<Integer>(elector, "TCnumber"));
        elector_add_form.add(TCnumberField);

        RequiredTextField provinceIDField = new RequiredTextField("provinceID",
                new PropertyModel<Integer>(elector, "provinceID"));
        elector_add_form.add(provinceIDField);

        RequiredTextField nameField = new RequiredTextField("name",
                new PropertyModel<String>(elector, "name"));
        elector_add_form.add(nameField);

        RequiredTextField birthdayField = new RequiredTextField("birthday",
                new PropertyModel<Date>(elector, "birthday"));
        elector_add_form.add(birthdayField);

        RequiredTextField professionField = new RequiredTextField("profession",
                new PropertyModel<String>(elector, "profession"));
        elector_add_form.add(professionField);

        RequiredTextField educationField = new RequiredTextField("education",
                new PropertyModel<String>(elector, "education"));
        elector_add_form.add(educationField);

        RequiredTextField addressField = new RequiredTextField("address",
                new PropertyModel<String>(elector, "address"));
        elector_add_form.add(addressField);




        Button add_elector_button = new Button("Save") {
            @Override
            public void onSubmit() {


                if (ElectorDM.getOneElector(elector.getTCNumber()) == null && ElectionOrganizer.canAddCandidate()) {
                    user.setUsername(elector.getTCNumber().toString());
                    user.setPassword(PasswordGenerator.getPassword());
                    user.setUserType(2);
                    UserDM.addUser(user);
                    elector.setElectionID(ElectionOrganizer.currentOrNextElection.getElectionID());
                    elector.setHasVoted(false);
                    ElectorDM.addElector(elector);
                    info("Elector was added successfully");
                } else {
                    if(ElectorDM.getOneElector(elector.getTCNumber()) != null)
                        error("There is an elector with same TCnumber");
                    else
                        error("Elector can not be added due to time constraints!");
                }
            }
        };
        elector_add_form.add(add_elector_button);

        FeedbackPanel feedback = new FeedbackPanel("add_elector_feedback");
        this.add(feedback);

    }

    public void render(IHeaderResponse response) {
        response.render(JavaScriptHeaderItem.forReference(new JavaScriptResourceReference(ElectionEditorPage.class, "../js/DateTimePicker/datetimepicker_css.js")));
    }
}