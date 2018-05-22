package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.text.DecimalFormat;
import java.util.*;
import org.apache.wicket.Component;
import org.apache.wicket.ajax.AjaxEventBehavior;
import org.apache.wicket.ajax.AjaxRequestTarget;
import org.apache.wicket.ajax.attributes.AjaxCallListener;
import org.apache.wicket.ajax.attributes.AjaxRequestAttributes;
import org.apache.wicket.markup.html.basic.Label;

/**
 *
 * @author OZAN
 */
public final class ResultForAProvincePage extends BasePage {

    Map<String, Integer> votes = null;
    Map<String, Integer> distribution = null;
    double total = 0;
    double totalOther = 0;
    DecimalFormat df = new DecimalFormat("#.###");

    public ResultForAProvincePage(String province) {

        votes = VoteDM.getVotesForAProvince(ElectionOrganizer.currentOrNextElection.getElectionID(),
                ProvinceDM.getOneProvince(province, ElectionOrganizer.currentOrNextElection.getElectionID()).getId());
        distribution = VoteDM.getCandidateDistributionForAProvince(ElectionOrganizer.currentOrNextElection.getElectionID(), ProvinceDM.getOneProvince(province, ElectionOrganizer.currentOrNextElection.getElectionID()).getId());
        
        votes = sortByComparator(votes);

        for (Integer value : votes.values()) {
            total += value;
        }

        this.add(new AjaxEventBehavior("onLoad") {

            @Override
            protected void onEvent(AjaxRequestTarget target) {
            }

            @Override
            protected void updateAjaxAttributes(AjaxRequestAttributes attributes) {
                super.updateAjaxAttributes(attributes);
                AjaxCallListener myAjaxCallListener = new AjaxCallListener() {

                    @Override
                    public CharSequence getBeforeHandler(Component component) {
                        String js = "";
                        int i = 0;
                        for (String partyTitle : votes.keySet()) {
                            if (!partyTitle.equals("")) {
                                if (i < 4) {
                                    switch (i) {
                                        case 0:
                                            js += "var rule = document.styleSheets[0].cssRules[13];"
                                                    + "rule.style.cssText = 'z-index:98; height:100px;';"
                                                    + "rule = document.styleSheets[0].cssRules[14];"
                                                    + "rule.style.cssText = 'z-index:999; background-color:#1f81ac; margin-left:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 10)) + "px;';"
                                                    + "rule = document.styleSheets[0].cssRules[15];"
                                                    + "rule.style.cssText = 'z-index:998; background-color:#1a6c90; width:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 50)) + "px;"
                                                    + "background:-moz-linear-gradient(-90deg, #1a6c90, #14506b);"
                                                    + "background:-webkit-gradient(linear, 0 top, 0 bottom, from(#1a6c90), to(#14506b));';";
                                            i++;
                                            break;
                                        case 1:
                                            js += "rule = document.styleSheets[0].cssRules[17];"
                                                    + "rule.style.cssText = 'z-index:96; height:100px;';"
                                                    + "rule = document.styleSheets[0].cssRules[18];"
                                                    + "rule.style.cssText = 'z-index:997; background-color:#bc003c; margin-left:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 10)) + "px;';"
                                                    + "rule = document.styleSheets[0].cssRules[19];"
                                                    + "rule.style.cssText = 'z-index:996; background-color:#9d0032; width:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 50)) + "px;"
                                                    + "background:-moz-linear-gradient(-90deg, #9d0032, #7a0027);" 
                                                    + "background:-webkit-gradient(linear, 0 top, 0 bottom, from(#9d0032), to(#7a0027));';";
                                            i++;
                                            break;
                                        case 2:
                                            js += "rule = document.styleSheets[0].cssRules[21];"
                                                    + "rule.style.cssText = 'z-index:94; height:100px;';"
                                                    + "rule = document.styleSheets[0].cssRules[22];"
                                                    + "rule.style.cssText = 'z-index:995; background-color:#d98f23; margin-left:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 10)) + "px;';"
                                                    + "rule = document.styleSheets[0].cssRules[23];"
                                                    + "rule.style.cssText = 'z-index:994; background-color:#9d0032; width:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 50)) + "px;"
                                                    + "background:-moz-linear-gradient(-90deg, #b6781e, #916018);" 
                                                    + "background:-webkit-gradient(linear, 0 top, 0 bottom, from(#b6781e), to(#916018));';";
                                            i++;
                                            break;
                                        case 3:
                                            js += "rule = document.styleSheets[0].cssRules[25];"
                                                    + "rule.style.cssText = 'z-index:92; height:100px;';"
                                                    + "rule = document.styleSheets[0].cssRules[26];"
                                                    + "rule.style.cssText = 'z-index:993; background-color:#7da864; margin-left:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 10)) + "px;';"
                                                    + "rule = document.styleSheets[0].cssRules[27];"
                                                    + "rule.style.cssText = 'z-index:992; background-color:#9d0032; width:"
                                                    + Double.toString(Math.floor((votes.get(partyTitle).doubleValue() / total) * (460 - 10) + 50)) + "px;"
                                                    + "background:-moz-linear-gradient(-90deg, #698d54, #506b40);" 
                                                    + "background:-webkit-gradient(linear, 0 top, 0 bottom, from(#698d54), to(#506b40));';";
                                            i++;
                                            break;
                                        default:
                                            break;
                                    }
                                } else {
                                    break;
                                }
                            }
                        }
                        
                        js += "rule = document.styleSheets[0].cssRules[29];"
                                + "rule.style.cssText = 'z-index:90; height:100px;';"
                                + "rule = document.styleSheets[0].cssRules[30];"
                                + "rule.style.cssText = 'z-index:991; background-color:#3f1150; margin-left:"
                                + df.format(Math.floor((totalOther / total) * (460 - 10) + 10)) + "px;';"
                                + "rule = document.styleSheets[0].cssRules[31];"
                                + "rule.style.cssText = 'z-index:990; background-color:#9d0032; width:"
                                + df.format(Math.floor((totalOther / total) * (460 - 10) + 50)) + "px;"
                                + "background:-moz-linear-gradient(-90deg, #340e43, #1a0721);"
                                + "background:-webkit-gradient(linear, 0 top, 0 bottom, from(#340e43), to(#1a0721));';";

                        return js;
                    }
                };
                attributes.getAjaxCallListeners().add(myAjaxCallListener);
            }
        });

        this.add(new Label("headMessage", "Results for " + province));

        Label bar = new Label("bar", getChartMessage());
        bar.setEscapeModelStrings(false);
        this.add(bar);
        
        Label resultMessage = new Label("resultMessage", getResultMessage());
        resultMessage.setEscapeModelStrings(false);
        this.add(resultMessage);
        
        Label distMessage = new Label("distMessage", getDistributionMessage());
        distMessage.setEscapeModelStrings(false);
        this.add(distMessage);
    }

    public String AddLiElement(int order, String partyName, double votePercentage) {
        String partyId;

        switch (order) {
            case 0:
                partyId = "party1";
                break;
            case 1:
                partyId = "party2";
                break;
            case 2:
                partyId = "party3";
                break;
            case 3:
                partyId = "party4";
                break;
            default:
                partyId = "other";
        }
        String structure = "";
        structure = "<li id='" + partyId + "'>\n"
                + "<div class='top'></div>\n"
                + "<div class='bottom'>\n"
                + "<div class='infobox'>\n"
                + "<h3>" + partyName + "</h3>\n"
                + "<p>%" + df.format(votePercentage * 100) + "</p>\n"
                + "</div>\n"
                + "</div>\n"
                + "</li>\n";
        return structure;
    }

    public String getChartMessage() {
        String chart = "";
        int i = 0;

        for (String partyTitle : votes.keySet()) {
            if (!partyTitle.equals("")) {
                if (i < 4) {
                    chart += AddLiElement(i++, partyTitle, votes.get(partyTitle).doubleValue() / total);
                } else {
                    totalOther += votes.get(partyTitle).doubleValue();
                }
            } else {
                totalOther += votes.get(partyTitle).doubleValue();
            }
        }

        chart += AddLiElement(4, "Other", totalOther / total);
        return chart;
    }
    
    public String getResultMessage()
    {
        String resultMessage = "";
        
        for (String partyTitle : votes.keySet()) {
            if (!partyTitle.equals("")) {
                resultMessage += partyTitle + " %" + df.format(votes.get(partyTitle).doubleValue() / total * 100) + "&nbsp&nbsp&nbsp&nbsp";
            }
        }
        
        return resultMessage;
    }
    
    public String getDistributionMessage()
    {     
        String resultMessage = "Congressman Counts : &nbsp&nbsp&nbsp&nbsp";

        for (String title : distribution.keySet()) {
            if(!CandidateDM.getCandidateWithName(title, ElectionOrganizer.currentOrNextElection.getElectionID()))
                resultMessage += title + " : " + Integer.toString(distribution.get(title)) + "&nbsp&nbsp&nbsp&nbsp";
            else
                resultMessage += title + "&nbsp&nbsp&nbsp&nbsp";
        }
        
        return resultMessage;
    }

    public static Map sortByComparator(Map<String, Integer> unsortMap) {
        System.out.println(unsortMap.size());
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
