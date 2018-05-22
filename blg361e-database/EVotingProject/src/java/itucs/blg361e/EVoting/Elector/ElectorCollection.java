/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Elector;

/**
 *
 * @author bahti
 */
import java.util.LinkedList;
import java.util.List;

public class ElectorCollection {

    private List<Elector> electors;

    public ElectorCollection() {
        this.electors = new LinkedList<Elector>();
    }

    public List<Elector> getElectors() {
        return this.electors;
    }

    public void addElector(Elector e) {
        this.electors.add(e);
    }

    public void deleteElector(Elector e) {
        this.electors.remove(e);
    }
}