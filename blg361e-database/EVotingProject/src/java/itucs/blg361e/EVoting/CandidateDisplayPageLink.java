/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author Fikret
 */

import org.apache.wicket.markup.html.link.Link;

public class CandidateDisplayPageLink extends Link {
    
    private Candidate candidate;

    public CandidateDisplayPageLink(String id, Candidate aCandidate) {
        super(id);
        this.candidate = aCandidate;
    }

    @Override
    public void onClick() {
        this.setResponsePage(new CandidateDisplayPage(this.candidate));
    }
    
}
