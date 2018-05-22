/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.ProvinceDM;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author coskun
 */
public final class IndependentAddPage extends AdminBasePage {

    Candidate candidate = new Candidate();
    User user = new User();

    public IndependentAddPage() {
        super();

        Form independent_add_form = new Form("independent_add_form");
        add(independent_add_form);

        RequiredTextField TCnumberField = new RequiredTextField("tc_number",
                new PropertyModel<String>(candidate, "TCnumber"));
        independent_add_form.add(TCnumberField);

        RequiredTextField nameField = new RequiredTextField("name",
                new PropertyModel<String>(candidate, "name"));
        independent_add_form.add(nameField);

        RequiredTextField userNameField = new RequiredTextField("user_name",
                new PropertyModel<String>(candidate, "userName"));
        independent_add_form.add(userNameField);

        RequiredTextField provinceIdField = new RequiredTextField("province_id",
                new PropertyModel<String>(candidate, "provinceId"));
        independent_add_form.add(provinceIdField);

        Button add_independent_button = new Button("add_independent") {
            @Override
            public void onSubmit() {

                if (CandidateDM.getOneCandidate(candidate.getTCnumber()) == null
                        && UserDM.getUser(candidate.getUserName()) == null
                        && ProvinceDM.getOneProvince(candidate.getProvinceId(), candidate.getElectionId()) != null
                        && ElectionOrganizer.canAddCandidate()) {

                    user.setUsername(candidate.getUserName());
                    user.setPassword(PasswordGenerator.getPassword());
                    user.setUserType(3);
                    UserDM.addUser(user);

                    candidate.setIsIndependent(Boolean.TRUE);
                    candidate.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
                    CandidateDM.addCan(candidate);

                    info("Independent candidate was added successfully");
                } else {
                    error("There is a candidate with same username or TC number!");
                }
            }
        };
        independent_add_form.add(add_independent_button);

        FeedbackPanel feedback = new FeedbackPanel("add_independent_feedback");
        this.add(feedback);
    }
}
