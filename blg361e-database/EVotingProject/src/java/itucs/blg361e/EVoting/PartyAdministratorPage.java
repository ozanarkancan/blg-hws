/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;


/**
 *
 * @author fikret
 */

import java.sql.ResultSet;
import java.sql.SQLException;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.basic.Label;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.PropertyListView;

/**
 *
 * @author Fikret
 */
public class PartyAdministratorPage extends BasePage {

    public PartyAdministratorPage() {

        Link candidateAddLink = new Link("add_candidate") {

            @Override
            public void onClick() {
                this.setResponsePage(new CandidateAddPage());
            }
        };
        this.add(candidateAddLink);

        Link candidateDeleteLink = new Link("delete_candidate") {

            @Override
            public void onClick() {
                this.setResponsePage(new CandidateDeletePage());
            }
        };
        this.add(candidateDeleteLink);

        Link candidateUpdateLink = new Link("updateCandidatePage") {

            @Override
            public void onClick() {
                this.setResponsePage(new CandidateUpdatePage());
            }
        };
        this.add(candidateUpdateLink);


    }
}
