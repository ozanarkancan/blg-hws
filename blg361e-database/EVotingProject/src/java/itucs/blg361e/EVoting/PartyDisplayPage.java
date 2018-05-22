/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.wicket.markup.html.WebPage;

/**
 *
 * @author fikret
 */
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.PropertyListView;

public final class PartyDisplayPage extends BasePage {

    public PartyDisplayPage(Party aParty) {

        ArrayList<Candidate> candidates = CandidateDM.getCandidateWithPartyTitle(aParty.getTitle());
        PropertyListView candidateListView = new PropertyListView("party_candidate_list", candidates) {
            
            @Override
            protected void populateItem(ListItem item) {
                Candidate candidate = (Candidate) item.getModelObject();
                CandidateDisplayPageLink candidateLink =
                        new CandidateDisplayPageLink("party_candidate_link", candidate);
                candidateLink.add(new Label("name"));
                item.add(candidateLink);
            }
        };
        this.add(candidateListView);
   

        this.add(new Label("title", aParty.getTitle()));
        this.add(new Label("year", aParty.getYear().toString()));
        this.add(new Label("partyleader", aParty.getPartyLeader()));
        this.add(new Label("partyprinciple", aParty.getPartyPrinciples()));
        this.add(new Label("electionId", aParty.getElectionId().toString()));
                
    }
}
