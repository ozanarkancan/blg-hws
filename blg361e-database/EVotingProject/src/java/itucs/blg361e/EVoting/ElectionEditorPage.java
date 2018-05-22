/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.util.ArrayList;
import java.util.List;
import org.apache.wicket.AttributeModifier;
import org.apache.wicket.extensions.markup.html.tabs.AbstractTab;
import org.apache.wicket.extensions.markup.html.tabs.ITab;
import org.apache.wicket.extensions.markup.html.tabs.TabbedPanel;
import org.apache.wicket.markup.head.IHeaderResponse;
import org.apache.wicket.markup.head.JavaScriptHeaderItem;
import org.apache.wicket.markup.html.WebMarkupContainer;
import org.apache.wicket.markup.html.panel.Panel;
import org.apache.wicket.model.Model;
import org.apache.wicket.request.resource.JavaScriptResourceReference;

/**
 *
 * @author OZAN
 */
public final class ElectionEditorPage extends AdminBasePage {

    public ElectionEditorPage() {
        super();
        
        setDefaultModel(new Model<String>("tabpanel"));
        List<ITab> tabs = new ArrayList<ITab>();
        tabs.add(new AbstractTab(new Model<String>("Add Election"))
        {
            private static final long serialVersionUID = 1L;
            
            @Override
            public Panel getPanel(String panelId)
            {
                return new ElectionAdd(panelId);
            }

        });

        tabs.add(new AbstractTab(new Model<String>("Delete or Update Election"))
        {
            private static final long serialVersionUID = 1L;
            
            @Override
            public Panel getPanel(String panelId)
            {
                return new ElectionEdit(panelId);
            }

        });

        add(new TabbedPanel("tabs", tabs).add(AttributeModifier.replace("class",
            ElectionEditorPage.this.getDefaultModel())));
    }
    
    private static class ElectionAdd extends Panel
    {
        private static final long serialVersionUID = 1L;
        private WebMarkupContainer containerForAdd;
    
        public ElectionAdd(String id)
        {
            super(id);
            
            containerForAdd = new WebMarkupContainer("containerForAdd");
            AddElectionForm aef = new AddElectionForm("addElectionForm"); 
            containerForAdd.add(aef);
            this.add(containerForAdd);
            
        }
    }

    private static class ElectionEdit extends Panel
    {
        private static final long serialVersionUID = 1L;
        private WebMarkupContainer containerForDeleteAndUpdate;
        
        public ElectionEdit(String id)
        {
            super(id);
            
            containerForDeleteAndUpdate = new WebMarkupContainer("containerForDeleteAndUpdate");
            DeleteAndUpdateElectionForm deuef = new DeleteAndUpdateElectionForm("deleteAndUpdateElectionForm");
            containerForDeleteAndUpdate.add(deuef);
            this.add(containerForDeleteAndUpdate);
        }

    }
    
    public void render(IHeaderResponse response)
    {
        response.render(JavaScriptHeaderItem.forReference(new JavaScriptResourceReference(ElectionEditorPage.class, "js/DateTimePicker/datetimepicker_css.js")));
    }
}
