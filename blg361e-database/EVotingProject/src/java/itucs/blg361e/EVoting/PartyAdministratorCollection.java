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

public class PartyAdministratorCollection{

    private List<PartyAdministrator> partyadmin;

    public PartyAdministratorCollection() {
        this.partyadmin = new LinkedList<PartyAdministrator>();
    }

    public List<PartyAdministrator> getPartyAdministrator() {
        return this.partyadmin;
    }

    public void addPartyAdministrator(PartyAdministrator aPartyadmin) {
        this.partyadmin.add(aPartyadmin);
    }

    public void deletePartyAdministrator(PartyAdministrator aPartyadmin) {
        this.partyadmin.remove(aPartyadmin);
    }
}
