/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author fikret
 */

import java.util.LinkedList;
import java.util.List;

public class PartyCollection {

    private List<Party> parties;

    public PartyCollection() {
        this.parties = new LinkedList<Party>();
    }

    public List<Party> getParties() {
        return this.parties;
    }

    public void addParty(Party aParty) {
        this.parties.add(aParty);
    }

    public void deleteParty(Party aParty) {
        this.parties.remove(aParty);
    }
}