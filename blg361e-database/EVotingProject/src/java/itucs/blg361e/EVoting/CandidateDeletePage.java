package itucs.blg361e.EVoting;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import itucs.blg361e.EVoting.AdminBasePage;
import itucs.blg361e.EVoting.Candidate;
import itucs.blg361e.EVoting.CandidateDM;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author bahti
 */
public final class CandidateDeletePage extends PartyAdministratorPage {

    Candidate candidate = new Candidate();
    
    User user = new User();
    
    public CandidateDeletePage() {
        super();

        Form candidate_delete_form = new Form("candidate_delete_form");
        add(candidate_delete_form);

        RequiredTextField TCnumberField = new RequiredTextField("TCnumber",
                new PropertyModel<String>(candidate, "TCnumber"));
        candidate_delete_form.add(TCnumberField);

        Button delete_candidate_button = new Button("delete_candidate") {
            @Override
            public void onSubmit() {
                candidate = CandidateDM.getOneCandidate(candidate.getTCnumber()); 
                if (candidate != null) {
                    
                    UserDM.deleteUser(UserDM.getUser(candidate.getUserName().toString()));
                    CandidateDM.deleteCan(candidate);   
                    info("Specified Candidate was deleted successfully");
                } else {
                    error("Requested Candidate does not exist in database!");
                }
            }
        };
        candidate_delete_form.add(delete_candidate_button);

        FeedbackPanel feedback = new FeedbackPanel("delete_candidate_feedback");
        this.add(feedback);
    }
}
