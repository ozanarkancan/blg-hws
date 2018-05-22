/*
 * HomePage.java
 *
 * Created on 14 Ekim 2012 Pazar, 18:43
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.ElectionOrganizer.State;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.ajax.markup.html.AjaxLink;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.image.Image;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.model.Model;

public class HomePage extends BasePage {

    Image howToUse;
    HomePage storage = this;
    
    public HomePage() {
        super();

        String election_announcement = "";
        if (ElectionOrganizer.state == State.NOTSTARTED) {
            election_announcement = "Next election is at "
                    + ElectionOrganizer.currentOrNextElection.getStartDateOfElection().toLocaleString();
        } else if (ElectionOrganizer.state == State.STARTED) {
            election_announcement = "Voting has been started for election "
                    + Integer.toString(ElectionOrganizer.currentOrNextElection.getElectionID())
                    + " <br/><br/>Finish time of election is "
                    + ElectionOrganizer.currentOrNextElection.getFinishDateOfElection().toLocaleString();
        } else {
            election_announcement = "There is no active election";
        }

        Label label = new Label("election_info", election_announcement);
        this.add(label);
        label.setEscapeModelStrings(false);
        
        AjaxLink initProjectLink = new AjaxLink("init_project") {

            @Override
            public void onClick(AjaxRequestTarget target) {
                DatabaseDemoCreator.initializeDemo();
                target.add(storage);
            }
        };
        this.add(initProjectLink);
        
        howToUse = new Image("how_to_use", new Model<String>("images/how-to-use.png")); 
        howToUse.setVisible(false);
        this.add(howToUse);
         
        Link howToUseLink = new Link("how_to_use_link") {
            @Override
            public void onClick() {
                howToUse.setVisible(!howToUse.isVisible());
            }
        };
        this.add(howToUseLink);

    }
}
