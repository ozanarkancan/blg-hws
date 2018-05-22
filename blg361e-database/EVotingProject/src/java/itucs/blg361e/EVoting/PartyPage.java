/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author fikret
 */
import itucs.blg361e.EVoting.Application;
import itucs.blg361e.EVoting.BasePage;
import itucs.blg361e.EVoting.HomePageLink;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.basic.Label;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.ListView;
import org.apache.wicket.markup.html.list.PropertyListView;

public final class PartyPage extends BasePage {

    public PartyPage() {

        PartyCollection collection = new PartyCollection();
        PartyDM partydm = new PartyDM();
        ResultSet result = partydm.searchParty();

        try {
            while (result.next()) {
                Party party = new Party(result.getString("TITLE"), result.getInt("YEAR"), result.getString("PARTYLEADER"), result.getString("PARTYPRINCIPLE"), result.getInt("ELECTIONID"));
                collection.addParty(party);
            }
        } catch (SQLException ex) {
            Logger.getLogger(PartyPage.class.getName()).log(Level.SEVERE, null, ex);
        }

        List<Party> parties = collection.getParties();
        PropertyListView partyListView = new PropertyListView("party_list", parties) {

            @Override
            protected void populateItem(ListItem item) {
                Party party = (Party) item.getModelObject();
                PartyDisplayPageLink partyLink =
                        new PartyDisplayPageLink("party_link", party);
                partyLink.add(new Label("title"));
                partyLink.add(new Label("year"));
                partyLink.add(new Label("partyleader"));
                item.add(partyLink);
            }
        };
        this.add(partyListView);
    }
}