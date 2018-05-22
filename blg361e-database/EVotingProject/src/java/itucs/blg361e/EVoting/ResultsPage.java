/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.Province;
import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.text.DecimalFormat;
import java.util.*;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.image.Image;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.model.Model;

/**
 *
 * @author OZAN
 */
public final class ResultsPage extends BasePage{
    
    public static class ResultForAProvincePageLink extends Link
    {
        private String province="Unknown";
        
        public ResultForAProvincePageLink(String id)
        {
            super(id);
            province=id;
        }
        
        @Override
        public void onClick() {
            this.setResponsePage(new ResultForAProvincePage(province));
        }
    }
    
    Map<String, Integer> votes = null;
    double total = 0;
    DecimalFormat df = new DecimalFormat("#.###");

    public ResultsPage() {
        
        votes = VoteDM.getVotesForAProvince(ElectionOrganizer.currentOrNextElection.getElectionID(),0);
        votes = sortByComparator(votes);

        for (Integer value : votes.values()) {
            total += value;
        }
        
        this.add(new Label("resultMessage", "Election Results"));
        this.add(new Label("slidingResult", getResultMessage()).setEscapeModelStrings(false));
        this.add(new Label("candidateDistribution", getDistributionMessage()).setEscapeModelStrings(false));
        this.add(new Image("TurkeyMap", new Model<String>("images/TurkeyMap.png")));
        
        this.createLinksForAllProvinces();
    }
    
    public void createLinksForAllProvinces()
    {
        this.add(new ResultForAProvincePageLink("Adana"));
        this.add(new ResultForAProvincePageLink("Adıyaman"));
        this.add(new ResultForAProvincePageLink("Afyon"));
        this.add(new ResultForAProvincePageLink("Ağrı"));
        this.add(new ResultForAProvincePageLink("Amasya"));
        this.add(new ResultForAProvincePageLink("Ankara"));
        this.add(new ResultForAProvincePageLink("Antalya"));
        this.add(new ResultForAProvincePageLink("Artvin"));
        this.add(new ResultForAProvincePageLink("Aydın"));
        this.add(new ResultForAProvincePageLink("Balıkesir"));
        this.add(new ResultForAProvincePageLink("Bilecik"));
        this.add(new ResultForAProvincePageLink("Bingöl"));
        this.add(new ResultForAProvincePageLink("Bitlis"));
        this.add(new ResultForAProvincePageLink("Bolu"));
        this.add(new ResultForAProvincePageLink("Burdur"));
        this.add(new ResultForAProvincePageLink("Bursa"));
        this.add(new ResultForAProvincePageLink("Çanakkale"));
        this.add(new ResultForAProvincePageLink("Çankırı"));
        this.add(new ResultForAProvincePageLink("Çorum"));
        this.add(new ResultForAProvincePageLink("Denizli"));
        this.add(new ResultForAProvincePageLink("Diyarbakır"));
        this.add(new ResultForAProvincePageLink("Edirne"));
        this.add(new ResultForAProvincePageLink("Elazığ"));
        this.add(new ResultForAProvincePageLink("Erzincan"));
        this.add(new ResultForAProvincePageLink("Erzurum"));
        this.add(new ResultForAProvincePageLink("Eskişehir"));
        this.add(new ResultForAProvincePageLink("Gaziantep"));
        this.add(new ResultForAProvincePageLink("Giresun"));
        this.add(new ResultForAProvincePageLink("Gümüşhane"));
        this.add(new ResultForAProvincePageLink("Hakkari"));
        this.add(new ResultForAProvincePageLink("Hatay"));
        this.add(new ResultForAProvincePageLink("Isparta"));
        this.add(new ResultForAProvincePageLink("Mersin"));
        this.add(new ResultForAProvincePageLink("İstanbul"));
        this.add(new ResultForAProvincePageLink("İzmir"));
        this.add(new ResultForAProvincePageLink("Kars"));
        this.add(new ResultForAProvincePageLink("Kastamonu"));
        this.add(new ResultForAProvincePageLink("Kayseri"));
        this.add(new ResultForAProvincePageLink("Kırklareli"));
        this.add(new ResultForAProvincePageLink("Kırşehir"));
        this.add(new ResultForAProvincePageLink("Kocaeli"));
        this.add(new ResultForAProvincePageLink("Konya"));
        this.add(new ResultForAProvincePageLink("Kütahya"));
        this.add(new ResultForAProvincePageLink("Malatya"));
        this.add(new ResultForAProvincePageLink("Manisa"));
        this.add(new ResultForAProvincePageLink("Kahramanmaraş"));
        this.add(new ResultForAProvincePageLink("Mardin"));
        this.add(new ResultForAProvincePageLink("Muğla"));
        this.add(new ResultForAProvincePageLink("Muş"));
        this.add(new ResultForAProvincePageLink("Nevşehir"));
        this.add(new ResultForAProvincePageLink("Niğde"));
        this.add(new ResultForAProvincePageLink("Ordu"));
        this.add(new ResultForAProvincePageLink("Rize"));
        this.add(new ResultForAProvincePageLink("Sakarya"));
        this.add(new ResultForAProvincePageLink("Samsun"));
        this.add(new ResultForAProvincePageLink("Siirt"));
        this.add(new ResultForAProvincePageLink("Sinop"));
        this.add(new ResultForAProvincePageLink("Sivas"));
        this.add(new ResultForAProvincePageLink("Tekirdağ"));
        this.add(new ResultForAProvincePageLink("Tokat"));
        this.add(new ResultForAProvincePageLink("Trabzon"));
        this.add(new ResultForAProvincePageLink("Tunceli"));
        this.add(new ResultForAProvincePageLink("Şanlıurfa"));
        this.add(new ResultForAProvincePageLink("Uşak"));
        this.add(new ResultForAProvincePageLink("Van"));
        this.add(new ResultForAProvincePageLink("Yozgat"));
        this.add(new ResultForAProvincePageLink("Zonguldak"));
        this.add(new ResultForAProvincePageLink("Aksaray"));
        this.add(new ResultForAProvincePageLink("Bayburt"));
        this.add(new ResultForAProvincePageLink("Karaman"));
        this.add(new ResultForAProvincePageLink("Kırıkkale"));
        this.add(new ResultForAProvincePageLink("Batman"));
        this.add(new ResultForAProvincePageLink("Şırnak"));
        this.add(new ResultForAProvincePageLink("Bartın"));
        this.add(new ResultForAProvincePageLink("Ardahan"));
        this.add(new ResultForAProvincePageLink("Iğdır"));
        this.add(new ResultForAProvincePageLink("Yalova"));
        this.add(new ResultForAProvincePageLink("Karabük"));
        this.add(new ResultForAProvincePageLink("Kilis"));
        this.add(new ResultForAProvincePageLink("Osmaniye"));
        this.add(new ResultForAProvincePageLink("Düzce"));
    }
    
    public String getResultMessage()
    {
        String resultMessage = "";
        
        for (String partyTitle : votes.keySet()) {
            if (!partyTitle.equals("") && !CandidateDM.getCandidateWithName(partyTitle, ElectionOrganizer.currentOrNextElection.getElectionID())) {
                resultMessage += partyTitle + " %" + df.format(votes.get(partyTitle).doubleValue() / total * 100) + "&nbsp&nbsp&nbsp&nbsp";
            }
        }
        
        return resultMessage;
    }
    
    public String getDistributionMessage()
    {
        String resultMessage = "<h2>Congressman Distribution</h2>";
        
        Map<String, Integer> distribution = new HashMap<String, Integer>();
        
        for(Province p : ProvinceDM.getProvince())
        {
            Map<String, Integer> provinceDist = VoteDM.getCandidateDistributionForAProvince(ElectionOrganizer.currentOrNextElection.getElectionID(), p.getId());
            for(String title : provinceDist.keySet())
            {
                if(CandidateDM.getCandidateWithName(title, ElectionOrganizer.currentOrNextElection.getElectionID()))
                {
                    System.out.println("xxxxxxxxxxxxx:" + title);
                    if(distribution.containsKey("Independents"))
                        distribution.put("Independents", distribution.get("Independents") + 1);
                    else
                        distribution.put("Independents", 1);
                }
                else
                {
                    if(distribution.containsKey(title))
                        distribution.put(title, distribution.get(title) + provinceDist.get(title));
                    else
                        distribution.put(title, provinceDist.get(title));
                }
            }
        }
        
        
        for (String title : distribution.keySet())
                resultMessage += title + " : " + Integer.toString(distribution.get(title)) + "<br>";
        
        return resultMessage;
    }
    
    public static Map sortByComparator(Map<String, Integer> unsortMap) {

        List list = new LinkedList(unsortMap.entrySet());

        // sort list based on comparator
        Collections.sort(list, new Comparator() {

            public int compare(Object o1, Object o2) {
                return -(((Comparable) ((Map.Entry) (o1)).getValue()).compareTo(((Map.Entry) (o2)).getValue()));
            }
        });

        Map sortedMap = new LinkedHashMap();
        for (Iterator it = list.iterator(); it.hasNext();) {
            Map.Entry entry = (Map.Entry) it.next();
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        return sortedMap;
    }
}
