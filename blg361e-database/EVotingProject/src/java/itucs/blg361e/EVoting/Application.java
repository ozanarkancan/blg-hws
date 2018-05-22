/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author bahti
 */
import itucs.blg361e.EVoting.Elector.Elector;
import itucs.blg361e.EVoting.Elector.ElectorCollection;
import itucs.blg361e.EVoting.Province.Province;
import itucs.blg361e.EVoting.Province.ProvinceCollection;
import org.apache.wicket.Session;
import org.apache.wicket.protocol.http.WebApplication;
import org.apache.wicket.request.Request;
import org.apache.wicket.request.Response;

public class Application extends WebApplication {

    private PartyCollection collection;
    private PartyAdministratorCollection collection1;
    private CandidateCollection collection2;
    private ElectorCollection collection3;
    private ProvinceCollection collection4;
    
    public void init()
    {
        getDebugSettings().setAjaxDebugModeEnabled(false); 
    }

    public Application() {
        
      
        /* fikret's code*/
        
        this.collection = new PartyCollection();
        this.collection1 = new PartyAdministratorCollection();
        
    
        /* cemil's code*/
        this.collection2=new CandidateCollection();
        
       /*bahti's code*/
        this.collection3=new ElectorCollection();
        Elector elector1;
        
        this.collection4=new ProvinceCollection();
        Province province1;
         
    }

    public Class getHomePage() {
        return HomePage.class;
    }

    public PartyCollection getCollection() {
        return this.collection;
    }
 
    public PartyAdministratorCollection getCollection1(){
        return this.collection1;
    }
  
    public CandidateCollection getCollection2() {
        return this.collection2;
    }
    
    public ElectorCollection getCollection3(){
        return this.collection3;
    } 
    public ProvinceCollection getCollection4(){
        return this.collection4;
    } 
      
    @Override
    public Session newSession(Request request, Response response) {
        return new MySession(request);
    }

}