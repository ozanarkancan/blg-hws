/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.Timestamp;
import java.util.List;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.ajax.form.AjaxFormComponentUpdatingBehavior;
import org.apache.wicket.ajax.markup.html.form.AjaxButton;
import org.apache.wicket.markup.html.WebMarkupContainer;
import org.apache.wicket.markup.html.form.*;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.CompoundPropertyModel;
import org.apache.wicket.model.LoadableDetachableModel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author OZAN
 */
public class DeleteAndUpdateElectionForm extends Form{
    private WebMarkupContainer textArea;
    private WebMarkupContainer electionWMC;
    private transient Election electionStorage;
    private DeleteAndUpdateElectionForm storage = this;
    private DropDownChoice<Election> elections;
    FeedbackPanel feedback;
            
    public DeleteAndUpdateElectionForm(String id)
    {
        super(id);
        this.setOutputMarkupId(true);
        electionStorage  = new Election();
        LoadableDetachableModel model = new LoadableDetachableModel() {
            @Override
            protected Object load() {
                return electionStorage;
            }
        };
        CompoundPropertyModel model2 = new CompoundPropertyModel(model);
        this.setModel(model2);
        this.setModelObject(electionStorage);
        
        textArea = new WebMarkupContainer("textArea");
        textArea.setOutputMarkupId(true);
        textArea.setDefaultModel(model2);
        
        TextField eID = new TextField("electionID", Integer.class);
        eID.add(AttributeModifier.replace("readonly", "readonly"));
        textArea.add(eID);
        TextField sde = new TextField("startDateOfElection", Timestamp.class);
        sde.setRequired(true);
        sde.add(AttributeModifier.replace("readonly", "readonly"));
        textArea.add(sde);
        TextField fde = new TextField("finishDateOfElection", Timestamp.class);
        fde.setRequired(true);
        fde.add(AttributeModifier.replace("readonly", "readonly"));
        textArea.add(fde);
        TextField lde = new TextField("lastDateOfAddingCandidate", Timestamp.class);
        lde.setRequired(true);
        lde.add(AttributeModifier.replace("readonly", "readonly"));
        textArea.add(lde);
        
        AjaxButton deleteButton = new AjaxButton("deleteButton", storage)
        {
            @Override
            protected void onSubmit(AjaxRequestTarget target, Form<?> form)
            {
                Election election = (Election)this.getForm().getModelObject();
                if(election != null)
                {
                    ElectionDM.deleteElection(election);
                    electionStorage = null;
                    storage.setModelObject(null);
                    elections.setChoices(new ElectionsModel());
                }
                else
                {
                    error("No election is selected.");
                }
                target.add(storage);
            }
            
            @Override
            protected void onError(AjaxRequestTarget target, Form<?> form)
            {
                target.add(feedback);
            }
        };
        textArea.add(deleteButton);
        
        AjaxButton updateButton = new AjaxButton("updateButton", storage)
        {
            @Override
            protected void onSubmit(AjaxRequestTarget target, Form<?> form)
            {
                Election election = (Election)this.getForm().getModelObject();
                if(election.getFinishDateOfElection().getTime() >= election.getStartDateOfElection().getTime() + 864e5)
                {
                    if(election.getStartDateOfElection().getTime() >= election.getLastDateOfAddingCandidate().getTime() + 14*864e5)
                    {
                        ElectionDM.updateElection(election);
                        info("Election has been updated.");
                    }
                    else
                    {
                        error("All candidates have to be determined two weeks earlier than the election.");
                    }
                }
                else
                {
                    error("Start date of election must be earlier than finish date of election.\n"
                            + "There must be at least 24 hours difference.");
                }
                
                electionStorage = null;
                storage.setModelObject(null);
                elections.setChoices(new ElectionsModel());
                target.add(storage);
            }
            
            @Override
            protected void onError(AjaxRequestTarget target, Form<?> form)
            {
                target.add(feedback);
            }
        };
        textArea.add(updateButton);
        textArea.setOutputMarkupId(true);

        this.add(textArea);

        elections = new DropDownChoice<Election>("electionList",
                new PropertyModel<Election>(storage, "electionStorage"), new ElectionsModel(),
                new ChoiceRenderer("electionID", "electionID")
                {
                    protected boolean wantOnSelectionChangedNotifications(){ return true;}
                });
        elections.add(new AjaxFormComponentUpdatingBehavior("onchange") {

            @Override
            protected void onUpdate(AjaxRequestTarget target) {
                target.add(storage);
            }
        });
        elections.setNullValid(true);
        elections.setOutputMarkupId(true);
        electionWMC = new WebMarkupContainer("elections");
        electionWMC.setOutputMarkupPlaceholderTag(true);
        electionWMC.add(elections);
        textArea.add(electionWMC);
        
        feedback = new FeedbackPanel("feedbackEditForm");
        feedback.setOutputMarkupId(true);
        this.add(feedback);
    }
    
    private static class ElectionsModel extends LoadableDetachableModel<List<? extends Election>>
    {
        @Override
        protected List<? extends Election> load() {
             return ElectionDM.getElections();            
        }
    }
}
