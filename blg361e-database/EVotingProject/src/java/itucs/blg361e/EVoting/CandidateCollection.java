/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author Cemil
 */
public class CandidateCollection {
 
    private List<Candidate> candidates;

    public CandidateCollection() {
        this.candidates = new LinkedList<Candidate>();
    }

    public List<Candidate> getCandidate() {
        return this.candidates;
    }

    public void addCandidate(Candidate can) {
        this.candidates.add(can);
    }

    public void deleteCandidate(Candidate can) {
        this.candidates.remove(can);
    }
    
    
}
