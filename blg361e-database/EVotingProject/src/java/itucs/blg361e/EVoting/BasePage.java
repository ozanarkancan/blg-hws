/*
 * WicketExamplePage.java
 *
 * Created on 14 Ekim 2012 Pazar, 18:43
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Elector.ElectorPage;
import java.sql.Timestamp;
import java.util.Calendar;
import org.apache.wicket.ajax.AbstractAjaxTimerBehavior;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.markup.html.WebPage;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.model.Model;
import org.apache.wicket.util.time.Duration;

/**
 *
 * @author OZAN
 * @version
 */
public abstract class BasePage extends WebPage {

    private String nowString;
    private Label labelDateTime;
    private Label electionLabel;
    public BasePage() {
        super();
        
        ElectionOrganizer.setCurrentOrNextElection();
        Timestamp now = new Timestamp(Calendar.getInstance().getTimeInMillis());
        nowString = now.toLocaleString();
        labelDateTime = new Label("date_time", new Model<String>(nowString));
        this.add(labelDateTime);
        labelDateTime.setOutputMarkupId(true);
        labelDateTime.add(new AbstractAjaxTimerBehavior(Duration.seconds(0.5)) {

            @Override
            protected void onTimer(AjaxRequestTarget target) {
                Timestamp now = new Timestamp(Calendar.getInstance().getTimeInMillis());
                nowString = now.toLocaleString();
                labelDateTime.setDefaultModelObject(nowString);
                target.add(labelDateTime);
            }
        });
        electionLabel = new Label("electionLabel", "");
        electionLabel.setOutputMarkupId(true);
        this.add(electionLabel);
        electionLabel.add(new AbstractAjaxTimerBehavior(Duration.seconds(3)) {

            @Override
            protected void onTimer(AjaxRequestTarget target) {
                ElectionOrganizer.setCurrentOrNextElection();
            }
        });

        HomePageLink homePageLink = new HomePageLink("home_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new HomePage());
            }
        };
        this.add(homePageLink);

        Link partyPageLink = new Link("party-page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new PartyPage());
            }
        };
        this.add(partyPageLink);

        Link candidatePageLink = new Link("candidate_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new CandidatePage());
            }
        };
        this.add(candidatePageLink);

        Link electorPageLink = new Link("elector_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new ElectorPage());
            }
        };
        this.add(electorPageLink);
        electorPageLink.setVisible(MySession.get().isLoggedIn()
                && UserDM.getUser(MySession.get().getUser().getUsername()).getUserType() == 2);

        Link votingPageLink = new Link("voting_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new VotePage());
            }
        };
        this.add(votingPageLink);
        votingPageLink.setVisible(MySession.get().isLoggedIn()
                && UserDM.getUser(MySession.get().getUser().getUsername()).getUserType() == 2
                && ElectionOrganizer.state == ElectionOrganizer.State.STARTED);

        Link resultPageLink = new Link("results_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new ResultsPage());
            }
        };
        this.add(resultPageLink);
        resultPageLink.setVisible(ElectionOrganizer.state == ElectionOrganizer.State.STARTED || ElectionOrganizer.state == ElectionOrganizer.State.FINISHED);

        Link AdminPageLink = new Link("admin_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new AdminPage());
            }
        };
        this.add(AdminPageLink);
        // set visibility according to login state and user type
        AdminPageLink.setVisible(MySession.get().isLoggedIn()
                && UserDM.getUser(MySession.get().getUser().getUsername()).getUserType() == 0);

        Link PartyAdministratorPageLink = new Link("party_administrator") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new PartyAdministratorPage());
            }
        };
        this.add(PartyAdministratorPageLink);
        PartyAdministratorPageLink.setVisible(MySession.get().isLoggedIn()
                && UserDM.getUser(MySession.get().getUser().getUsername()).getUserType() == 1);
        
        Link loginPageLink = new Link("login_page") {
            
            @Override
            public void onClick() {
                this.setResponsePage(new LoginPage());
            }
        };
        this.add(loginPageLink);
        loginPageLink.setVisible(!MySession.get().isLoggedIn());

        Link logOutPageLink = new Link("logout") {
            
            @Override
            public void onClick() {
                MySession.get().invalidate();
                this.setResponsePage(new HomePage());
            }
        };
        this.add(logOutPageLink);
        logOutPageLink.setVisible(MySession.get().isLoggedIn());
        
    } // end constructor
}
