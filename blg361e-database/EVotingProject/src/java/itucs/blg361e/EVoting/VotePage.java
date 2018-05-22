/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Elector.Elector;
import itucs.blg361e.EVoting.Elector.ElectorDM;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Calendar;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.ajax.markup.html.form.AjaxButton;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RadioChoice;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author OZAN
 */
public final class VotePage extends BasePage{

    private String selected = null;
    private FeedbackPanel feedback;
    private User user;
    private Elector elector;
    
    public VotePage() {
        super();
        user = MySession.get().getUser();
        elector = ElectorDM.getOneElector(user.getUsername());
        
        RadioChoice<String> participants = new RadioChoice<String>(
                    "participants", new PropertyModel<String>(this, "selected"),
                    createParticipantList()
        );
        
        Form form = new Form("voteForm");
        form.setOutputMarkupId(true);
        AjaxButton voteButton = new AjaxButton("voteButton", form)
        {
            @Override
            protected void onSubmit(AjaxRequestTarget target, Form<?> form)
            {
                if(elector.getHasVoted())
                    error("You have already voted!");
                else
                {
                    if(ElectionOrganizer.canVote())
                    {
                        elector.setHasVoted(true);
                        ElectorDM.updateElector(elector);
                        Vote vote = new Vote();
                        vote.setElectionId(ElectionOrganizer.currentOrNextElection.getElectionID());
                        vote.setVoteTime(new Timestamp(Calendar.getInstance().getTimeInMillis()));
                        if(selected != null)
                            vote.setPartyTitle(selected);
                        else
                            vote.setPartyTitle("");
                        vote.setProvinceId(elector.getProvinceID());
                        VoteDM.addVote(vote);
                        info("You have voted successfully");
                    }
                    else
                    {
                        error("Voting finished. You can not vote.");
                    }
                }
                target.add(feedback);
            }
            
            @Override
            protected void onError(AjaxRequestTarget target, Form<?> form)
            {
                target.add(feedback);
            }
        };
        form.add(voteButton);
        form.add(participants);
        
        this.add(form);
        
        if(elector.getHasVoted())
        {
            form.setVisible(false);
            info("You have already voted.");
        }
        
        feedback = new FeedbackPanel("feedbackVote");
        feedback.setOutputMarkupId(true);
        this.add(feedback);
    }
    
    public ArrayList<String> createParticipantList()
    {
        ArrayList<String> participantList = new ArrayList<String>();
        for(Party party : PartyDM.getPartiesWithElectionId(ElectionOrganizer.currentOrNextElection.getElectionID()))
            participantList.add(party.getTitle());
        for(Candidate candidate : CandidateDM.getCandidatesForProvince(elector.getProvinceID(), ElectionOrganizer.currentOrNextElection.getElectionID(), 1))//independents
            participantList.add(candidate.getName());
        return participantList;
    }
}
