package itucs.blg361e.EVoting;

/**
 * **
 * @author bahti
***
 */
import itucs.blg361e.EVoting.BasePage;
import itucs.blg361e.EVoting.Province.Province;
import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.ajax.form.AjaxFormComponentUpdatingBehavior;
import org.apache.wicket.markup.html.WebMarkupContainer;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.form.ChoiceRenderer;
import org.apache.wicket.markup.html.form.DropDownChoice;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.PropertyListView;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.LoadableDetachableModel;
import org.apache.wicket.model.PropertyModel;

public final class CandidatePage extends BasePage {

    private DropDownChoice<Province> provinces;
    private WebMarkupContainer textArea;
    private WebMarkupContainer provinceWMC;
    private transient Province provinceStorage;
    FeedbackPanel feedback;
    private CandidatePage storage = this;
    PropertyListView candidateListView;

    public CandidatePage() {

        super();
        this.setOutputMarkupId(true);
        provinceStorage = new Province();
        LoadableDetachableModel model = new LoadableDetachableModel() {
            @Override
            protected Object load() {
                return provinceStorage;
            }
        };
        candidateListView = new PropertyListView("candidate_list", CandidateDM.getCandidatesForProvince(34, ElectionOrganizer.currentOrNextElection.getElectionID(),
                2)) {
            @Override
            protected void populateItem(ListItem item) {
                Candidate candidate = (Candidate) item.getModelObject();
                CandidateDisplayPageLink candidateLink =
                        new CandidateDisplayPageLink("candidate_link", candidate);
                candidateLink.add(new Label("TCnumber"));
                candidateLink.add(new Label("name"));
                candidateLink.add(new Label("partyTitle"));
                candidateLink.add(new Label("isIndependent"));
                candidateLink.add(new Label("provinceId"));
                item.add(candidateLink);
            }
        };
        candidateListView.setOutputMarkupId(true);
        candidateListView.setVisible(false);
        this.add(candidateListView);


        provinces = new DropDownChoice<Province>("xxxList",
                new PropertyModel<Province>(this, "provinceStorage"), new ProvincesModel(),
                new ChoiceRenderer("name", "name") {
                    protected boolean wantOnSelectionChangedNotifications() {
                        return true;
                    }
                });
        provinces.add(new AjaxFormComponentUpdatingBehavior("onchange") {
            @Override
            protected void onUpdate(AjaxRequestTarget target) {
                candidateListView = new PropertyListView("candidate_list", CandidateDM.getCandidatesForProvince(provinceStorage.getId(), ElectionOrganizer.currentOrNextElection.getElectionID(),
                2)) {
                    @Override
                    protected void populateItem(ListItem item) {
                        Candidate candidate = (Candidate) item.getModelObject();
                        CandidateDisplayPageLink candidateLink =
                                new CandidateDisplayPageLink("candidate_link", candidate);
                        candidateLink.add(new Label("TCnumber"));
                        candidateLink.add(new Label("name"));
                        candidateLink.add(new Label("partyTitle"));
                        candidateLink.add(new Label("isIndependent"));
                        candidateLink.add(new Label("provinceId"));
                        item.add(candidateLink);
                    }
                };
                candidateListView.setOutputMarkupId(true);
                candidateListView.setVisible(true);
                target.add(storage);
            }
        });
        provinces.setNullValid(true);
        provinces.setOutputMarkupId(true);

        this.add(provinces);

        /*feedback = new FeedbackPanel("feedbackEditForm");
         feedback.setOutputMarkupId(true);
         this.add(feedback);*/
    }

    private static class ProvincesModel extends LoadableDetachableModel<List<? extends Province>> {

        @Override
        protected List<? extends Province> load() {
            return ProvinceDM.getProvince();
        }
    }
}