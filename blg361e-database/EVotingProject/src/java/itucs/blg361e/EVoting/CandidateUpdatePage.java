/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.ProvinceDM;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author Fikret
 */
public final class CandidateUpdatePage extends PartyAdministratorPage {

    Candidate candidate = new Candidate();

    public CandidateUpdatePage() {
        super();

        Form candidateUpdateForm = new Form("canUpdateForm");
        add(candidateUpdateForm);

        final RequiredTextField TCnumberField = new RequiredTextField("TCnumber",
                new PropertyModel<String>(candidate, "TCnumber"));
        candidateUpdateForm.add(TCnumberField);

        final TextField nameField = new TextField("name",
                new PropertyModel<String>(candidate, "name"));
        candidateUpdateForm.add(nameField);

        final TextField provinceIdField = new TextField("provinceId",
                new PropertyModel<String>(candidate, "provinceId"));
        candidateUpdateForm.add(provinceIdField);

        candidate.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());


        Button getCandidateButton = new Button("getCanInfo") {

            @Override
            public void onSubmit() {

                if (CandidateDM.getOneCandidate(candidate.getTCnumber()) != null) {
                    if (ElectionOrganizer.canAddCandidate()) {
                        candidate.setPartyTitle(CandidateDM.getOneCandidate(candidate.getTCnumber()).getPartyTitle());
                        candidate.setUserName(CandidateDM.getOneCandidate(candidate.getTCnumber()).getUserName());
                        candidate.setIsIndependent(CandidateDM.getOneCandidate(candidate.getTCnumber()).getIsIndependent());
                        TCnumberField.add(AttributeModifier.replace("readonly", "readonly"));
                        nameField.add(new AttributeModifier("value", CandidateDM.getOneCandidate(candidate.getTCnumber()).getName()));
                        provinceIdField.add(new AttributeModifier("value", CandidateDM.getOneCandidate(candidate.getTCnumber()).getProvinceId()));
                    } else {
                        error("You can update a candidate until two weeks before election!");
                    }
                } else {
                    error("Requested candidate does not exist in database!");
                }
            }
        };
        candidateUpdateForm.add(getCandidateButton);

        Button updateCandidateButton = new Button("updateCan") {

            @Override
            public void onSubmit() {



                if (ProvinceDM.getOneProvince(candidate.getProvinceId(), candidate.getElectionId()) != null) {

                    CandidateDM.updateCan(candidate);
                    nameField.add(new AttributeModifier("value", CandidateDM.getOneCandidate(candidate.getTCnumber()).getName()));
                    provinceIdField.add(new AttributeModifier("value", CandidateDM.getOneCandidate(candidate.getTCnumber()).getProvinceId()));
                    info("Specified candidate was updated successfully");

                } else {

                    error("Province was not found!");
                }

            }
        };
        candidateUpdateForm.add(updateCandidateButton);

        FeedbackPanel feedback = new FeedbackPanel("updateCanFeedback");
        this.add(feedback);


    }
}
