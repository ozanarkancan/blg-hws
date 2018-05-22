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
public final class ProvinceDeletePage extends AdminBasePage {

    Province province = new Province();

    public ProvinceDeletePage() {
        super();
        province.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
        Form province_delete_form = new Form("province_delete_form");
        add(province_delete_form);

        RequiredTextField idField = new RequiredTextField("id",
                new PropertyModel<Integer>(province, "id"));
        province_delete_form.add(idField);

        Button delete_province_button = new Button("delete_province") {
            @Override
            public void onSubmit() {

                if (ProvinceDM.getOneProvince(province.getId(), province.getElectionId()) != null && ElectionOrganizer.canAddCandidate()) {
                    ProvinceDM.deleteProvince(province);
                    info("Specified Province was deleted successfully");
                } else {
                    if(ProvinceDM.getOneProvince(province.getId(), province.getElectionId()) == null)
                        error("Requested Province does not exist in database!");
                    else
                        error("Province can not be deleted due to time constrains!");
                }
            }
        };
        province_delete_form.add(delete_province_button);

        FeedbackPanel feedback = new FeedbackPanel("delete_province_feedback");
        this.add(feedback);
    }
}
