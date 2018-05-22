/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Calendar;

/**
 *
 * @author OZAN
 */

public class ElectionOrganizer {
    public enum State
    {
        NOTSTARTED, STARTED, FINISHED
    }
    
    public static Election currentOrNextElection = null;
    public static State state = null;
    
    public static void setCurrentOrNextElection()
    {
        Timestamp current = new Timestamp(Calendar.getInstance().getTimeInMillis());
        if(currentOrNextElection == null)
        {
            ArrayList<Election> elections = ElectionDM.getElections(current, 1, 0);
            if(elections != null)
            {
                if(!elections.isEmpty())
                {
                    currentOrNextElection = elections.get(0);
                    setState();
                }
            }
        }
        else
        {
            //1 month
            if(current.getTime() > currentOrNextElection.getFinishDateOfElection().getTime() + 2592e6)
            {
                currentOrNextElection = null;
                setCurrentOrNextElection();
                setState();
            }
        }
    }
    
    public static void setState()
    {
        Timestamp current = new Timestamp(Calendar.getInstance().getTimeInMillis());
        if(currentOrNextElection.getStartDateOfElection().getTime() > current.getTime())
            state = State.NOTSTARTED;
        else
        { 
            if(currentOrNextElection.getFinishDateOfElection().getTime() < current.getTime())
                state = State.FINISHED;
            else
                state = State.STARTED;
        }
        
    }
    
    public static boolean canVote()
    {
        boolean result = false;
        if(state == State.STARTED)
            result = true;
        return result;
    }
    
    public static boolean canAddCandidate()
    {
        boolean result = false;
        Timestamp current = new Timestamp(Calendar.getInstance().getTimeInMillis());
        if(currentOrNextElection != null)
            if(currentOrNextElection.getLastDateOfAddingCandidate().getTime() > current.getTime())
                result = true;
        return result;
    }
    
}
