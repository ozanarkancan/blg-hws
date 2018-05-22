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
public final class CandidateAddPage extends PartyAdministratorPage {

    Candidate candidate = new Candidate();
    User user = new User();

    public CandidateAddPage() {
        super();

        Form candidate_add_form = new Form("candidate_add_form");
        add(candidate_add_form);

        RequiredTextField TCnumberField = new RequiredTextField("tc_number",
                new PropertyModel<String>(candidate, "TCnumber"));
        candidate_add_form.add(TCnumberField);

        RequiredTextField nameField = new RequiredTextField("name",
                new PropertyModel<String>(candidate, "name"));
        candidate_add_form.add(nameField);

        RequiredTextField userNameField = new RequiredTextField("user_name",
                new PropertyModel<String>(candidate, "userName"));
        candidate_add_form.add(userNameField);

        RequiredTextField provinceIdField = new RequiredTextField("province_id",
                new PropertyModel<String>(candidate, "provinceId"));
        candidate_add_form.add(provinceIdField);

        Button add_candidate_button = new Button("add_candidate") {
            @Override
            public void onSubmit() {

                if (CandidateDM.getOneCandidate(candidate.getTCnumber()) == null
                        && UserDM.getUser(candidate.getUserName()) == null
                        && ProvinceDM.getOneProvince(candidate.getProvinceId(), candidate.getElectionId())!=null
                        && ElectionOrganizer.canAddCandidate()) {

                    user.setUsername(candidate.getUserName());
                    user.setPassword(PasswordGenerator.getPassword());
                    user.setUserType(3);
                    UserDM.addUser(user);
                        
                    candidate.setIsIndependent(Boolean.FALSE);
                    candidate.setPartyTitle(PartyAdministratorDM.getOneAdmin(MySession.get().getUser().getUsername()).getPartyTitle());
                    candidate.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
                    CandidateDM.addCan(candidate);

                    info("Candidate was added successfully");
                } else {
                    error("There is a candidate with same username or TC number or there is no such province!");
                }
            }
        };
        candidate_add_form.add(add_candidate_button);

        FeedbackPanel feedback = new FeedbackPanel("add_candidate_feedback");
        this.add(feedback);
    }
}
