/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

import itucs.blg361e.EVoting.AdminBasePage;
import itucs.blg361e.EVoting.BasePage;
import itucs.blg361e.EVoting.ElectionOrganizer;
import java.sql.Date;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author bahti
 */
public final class ProvinceUpdatePage extends AdminBasePage {

    Province province = new Province();

    public ProvinceUpdatePage() {
        super();

        Form province_update_form = new Form("province_update_form");
        add(province_update_form);

        final RequiredTextField idField = new RequiredTextField("id",
                new PropertyModel<Integer>(province, "id"));
        province_update_form.add(idField);

        final TextField nameField = new TextField("name",
                new PropertyModel<String>(province, "name"));
        province_update_form.add(nameField);

        final TextField quotaField = new TextField("quota",
                new PropertyModel<Integer>(province, "quota"));
        province_update_form.add(quotaField);
        province.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());

        Button get_province_button = new Button("get_province_info") {
            @Override
            public void onSubmit() {

                if (ProvinceDM.getOneProvince(province.getId(), province.getElectionId()) != null && ElectionOrganizer.canAddCandidate()) {
                    idField.add(new AttributeModifier("value", ProvinceDM.getOneProvince(province.getId(), province.getElectionId()).getId()));
                    nameField.add(new AttributeModifier("value", ProvinceDM.getOneProvince(province.getId(), province.getElectionId()).getName()));
                    quotaField.add(new AttributeModifier("value", ProvinceDM.getOneProvince(province.getId(), province.getElectionId()).getQuota()));

                } else {
                    if(!ElectionOrganizer.canAddCandidate())
                    error("Province can not be updated due to time constrains!");
                    else
                    error("Requested province does not exist in database!");
                }
            }
        };
        province_update_form.add(get_province_button);

        Button update_province_button = new Button("update_province") {
            @Override
            public void onSubmit() {

                if (ProvinceDM.getOneProvince(province.getId(), province.getElectionId()) != null && ElectionOrganizer.canAddCandidate()) {


                    ProvinceDM.updateProvince(province);
                    province = ProvinceDM.getOneProvince(province.getId(), province.getElectionId());
                    idField.add(new AttributeModifier("value", ProvinceDM.getOneProvince(province.getId(), province.getElectionId()).getId()));
                    nameField.add(new AttributeModifier("value", ProvinceDM.getOneProvince(province.getId(), province.getElectionId()).getName()));
                    quotaField.add(new AttributeModifier("value", ProvinceDM.getOneProvince(province.getId(), province.getElectionId()).getQuota()));


                    info("Specified province was updated successfully");
                }
                else {
                    if(!ElectionOrganizer.canAddCandidate())
                    error("Province can not be updated due to time constrains!");
                    else
                    error("Requested province does not exist in database!");
                }
            }
        };
        province_update_form.add(update_province_button);

        FeedbackPanel feedback = new FeedbackPanel("update_province_feedback");
        this.add(feedback);
    }
}