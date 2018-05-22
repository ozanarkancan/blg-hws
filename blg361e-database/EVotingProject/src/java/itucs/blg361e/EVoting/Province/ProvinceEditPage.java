/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

import itucs.blg361e.EVoting.AdminBasePage;
import itucs.blg361e.EVoting.ElectionOrganizer;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author bahti
 */
public final class ProvinceEditPage extends AdminBasePage {

    Province province = new Province();

    public ProvinceEditPage() {
        super();

        Form province_add_form = new Form("province_add_form");
        add(province_add_form);

        RequiredTextField idField = new RequiredTextField("id",
                new PropertyModel<Integer>(province, "id"));
        province_add_form.add(idField);

        RequiredTextField nameField = new RequiredTextField("name",
                new PropertyModel<String>(province, "name"));
        province_add_form.add(nameField);

        RequiredTextField quotaField = new RequiredTextField("quota",
                new PropertyModel<Integer>(province, "quota"));
        province_add_form.add(quotaField);

        province.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());

        Button add_province_button = new Button("Save") {
            @Override
            public void onSubmit() {

                if (ProvinceDM.getOneProvince(province.getId(), province.getElectionId()) == null && ElectionOrganizer.canAddCandidate() ) {

                    ProvinceDM.addProvince(province);
                    info("Province was added successfully");
                } else {
                    if(ProvinceDM.getOneProvince(province.getId(),province.getElectionId()) != null)
                        error("There is an province with same ID");
                    else
                        error("Province can not be added due to time constrains!");
                }
            }
        };
        province_add_form.add(add_province_button);

        FeedbackPanel feedback = new FeedbackPanel("add_province_feedback");
        this.add(feedback);
    }
}