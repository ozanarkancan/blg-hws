/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.Timestamp;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.ajax.markup.html.form.AjaxButton;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.CompoundPropertyModel;
import org.apache.wicket.model.LoadableDetachableModel;

/**
 *
 * @author OZAN
 */
public class AddElectionForm extends Form{

    private AddElectionForm storage = this;
    FeedbackPanel feedback;
    
    public AddElectionForm(String id)
    {
        super(id);
        
        LoadableDetachableModel model = new LoadableDetachableModel() {
            @Override
            protected Object load() {
                Election election = new Election();
                return election;
            }
        };
        CompoundPropertyModel model2 = new CompoundPropertyModel(model);
        this.setModel(model2);
        
        TextField sde = new TextField("startDateOfElection", Timestamp.class);
        sde.setRequired(true);
        sde.add(AttributeModifier.replace("readonly", "readonly"));
        this.add(sde);
        TextField fde = new TextField("finishDateOfElection", Timestamp.class);
        fde.setRequired(true);
        fde.add(AttributeModifier.replace("readonly", "readonly"));
        this.add(fde);
        TextField lde = new TextField("lastDateOfAddingCandidate", Timestamp.class);
        lde.setRequired(true);
        lde.add(AttributeModifier.replace("readonly", "readonly"));
        this.add(lde);
        
        AjaxButton addButton = new AjaxButton("addButton", this)
        {
            @Override
            protected void onSubmit(AjaxRequestTarget target, Form<?> form)
            {
                Election election = (Election) storage.getModelObject();
                if(election.getFinishDateOfElection().getTime() >= election.getStartDateOfElection().getTime() + 864e5)
                {
                    if(election.getStartDateOfElection().getTime() >= election.getLastDateOfAddingCandidate().getTime() + 14*864e5)
                    {
                        ElectionDM.addElection(election);
                        info("Election has been added.");
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
                
                storage.setModelObject(new Election());
                target.add(storage);
            }
            
            @Override
            protected void onError(AjaxRequestTarget target, Form<?> form)
            {
                target.add(feedback);
            }
        };
        this.add(addButton);
        
        feedback = new FeedbackPanel("feedbackAddForm");
        feedback.setOutputMarkupId(true);
        this.add(feedback);
    }
}
