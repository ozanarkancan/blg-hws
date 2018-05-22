/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author bahti
 */
package itucs.blg361e.EVoting.Elector;

import itucs.blg361e.EVoting.BasePage;
import itucs.blg361e.EVoting.ElectionEditorPage;
import itucs.blg361e.EVoting.ElectionOrganizer;
import itucs.blg361e.EVoting.MySession;
import java.sql.Date;
import java.text.SimpleDateFormat;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.markup.head.IHeaderResponse;
import org.apache.wicket.markup.head.JavaScriptHeaderItem;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;
import org.apache.wicket.request.resource.JavaScriptResourceReference;

public final class ElectorUpdatePage extends BasePage {

    Elector elector = new Elector();

    public ElectorUpdatePage() {
        super();

        Form elector_update_form = new Form("elector_update_form");
        add(elector_update_form);

        final RequiredTextField TCnumberField = new RequiredTextField("TCnumber",
                new PropertyModel<Integer>(elector, "TCnumber"));
        elector_update_form.add(TCnumberField);

        TCnumberField.add(new AttributeModifier("value", MySession.get().getUser().getUsername()));
        TCnumberField.add(AttributeModifier.replace("readonly", "readonly"));
        elector.setTC(MySession.get().getUser().getUsername());
        final TextField provinceIDField = new TextField("provinceID",
                new PropertyModel<Integer>(elector, "provinceID"));
        elector_update_form.add(provinceIDField);

        final TextField nameField = new TextField("name",
                new PropertyModel<String>(elector, "name"));
        elector_update_form.add(nameField);

        final TextField birthdayField = new TextField("birthday",
                new PropertyModel<Date>(elector, "birthday"));
        elector_update_form.add(birthdayField);

        final TextField professionField = new TextField("profession",
                new PropertyModel<String>(elector, "profession"));
        elector_update_form.add(professionField);

        final TextField educationField = new TextField("education",
                new PropertyModel<String>(elector, "education"));
        elector_update_form.add(educationField);

        final TextField addressField = new TextField("address",
                new PropertyModel<String>(elector, "address"));
        elector_update_form.add(addressField);

        Button get_elector_button = new Button("get_elector_info") {
            @Override
            public void onSubmit() {
                if(ElectionOrganizer.canAddCandidate()){
                SimpleDateFormat df = new SimpleDateFormat("dd.MM.yyyy");

                provinceIDField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getProvinceID()));
                nameField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getName()));
                birthdayField.add(new AttributeModifier("value", df.format(ElectorDM.getOneElector(elector.getTCNumber()).getBirthday())));
                professionField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getProfession()));
                educationField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getEducation()));
                addressField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getAddress()));
            }
                else{
                    if(!ElectionOrganizer.canAddCandidate())
                    error("Elector can not be updated due to time constraints!");
                    else
                    error("Requested elector does not exist in database!");
                }
            }
        };
        elector_update_form.add(get_elector_button);

        Button update_elector_button = new Button("update_elector") {
            @Override
            public void onSubmit() {

                if (ElectorDM.getOneElector(elector.getTCNumber()) != null&& ElectionOrganizer.state == ElectionOrganizer.State.NOTSTARTED) {
                    SimpleDateFormat df = new SimpleDateFormat("dd.MM.yyyy");
                    ElectorDM.updateElector(elector);
                    elector = ElectorDM.getOneElector(elector.getTCNumber());
                    provinceIDField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getProvinceID()));
                    nameField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getName()));
                    birthdayField.add(new AttributeModifier("value", df.format(ElectorDM.getOneElector(elector.getTCNumber()).getBirthday())));
                    professionField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getProfession()));
                    educationField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getEducation()));
                    addressField.add(new AttributeModifier("value", ElectorDM.getOneElector(elector.getTCNumber()).getAddress()));

                    info("Specified elector was updated successfully");
                }
                else{
                    if(ElectorDM.getOneElector(elector.getTCNumber()) == null)
                        error("Requested Elector does not exist in database!");
                    else
                        error("Election has been started!");
                }
                    
            }
        };
        elector_update_form.add(update_elector_button);

        FeedbackPanel feedback = new FeedbackPanel("update_elector_feedback");
        this.add(feedback);
    }

    public void render(IHeaderResponse response) {
        response.render(JavaScriptHeaderItem.forReference(new JavaScriptResourceReference(ElectorUpdatePage.class, "../js/DateTimePicker/datetimepicker_css.js")));
    }
}