import java.util.ArrayList;
import java.util.Collections;

public class Node implements Comparable {
	private Board value;
	private ArrayList<Node> children;
	private Node parent;
	private int pathCost;
	private int heuristicCost;
	private int totalCost;
	private boolean whichHeuristic;//false for 1 true for 2
	
	public Node(Board board)
	{
		this.value = board;
		children = null;
		parent = null;
		children = new ArrayList<Node>();
	}
	
	public void createChildren()
	{
		for(Block b : this.value.getBlocks())//create possible moves
		{
			Board nextStep = this.value.moveBlock(b, 0);
			Board nextStep2 = this.value.moveBlock(b, 1);
			
			if(nextStep != null)
			{
				Node newNode = new Node(nextStep);
				newNode.setParent(this);
				newNode.setPathCost(nextStep.getCost());
				newNode.setWhichHeuristic(this.getWhichHeuristic());
				this.AddChild(newNode);
			}
			if(nextStep2 != null)
			{
				Node newNode = new Node(nextStep2);
				newNode.setParent(this);
				newNode.setPathCost(nextStep2.getCost());
				newNode.setWhichHeuristic(this.getWhichHeuristic());
				this.AddChild(newNode);
			}
		}
	}
	
	@Override
	public int compareTo(Object o) {
		int result = 0;
		Node n = (Node)o;
		if(this.getTotalCost() > n.getTotalCost())
			result = 1;
		else if(this.getTotalCost() < n.getTotalCost())
			result = -1;
		return result;
	}
	
	public void AddChild(Node child)
	{
		children.add(child);
	}
	
	public boolean isGoal()
	{
		return this.value.isGoal();
	}
	
	public ArrayList<Node> getChildren()
	{
		return children;
	}

	public Node getParent() {
		return parent;
	}

	public void setParent(Node parent) {
		this.parent = parent;
	}

	public int getPathCost() {
		return pathCost;
	}

	public void setPathCost(int pathCost) {
		this.pathCost = pathCost;
	}
	
	public ArrayList<Block> getBlocks()
	{
		return this.value.getBlocks();
	}

	public int getHeuristicCost() {
		heuristicCost = (this.whichHeuristic) ? this.heuristic2() : this.heuristic1();
		return heuristicCost;
	}

	public void setHeuristicCost(int heuristicCost) {
		this.heuristicCost = heuristicCost;
	}
	
	/*
	 * Number of moves for moving target block to gate
	 * */
	public int heuristic1()
	{
		int cost = 0;
		Block target = this.value.getBlocks().get(this.value.getTarget());
		cost = 6 - (target.getX() + target.getLength());		
		return cost;
	}
	
	/*
	 * Number of blocks on the path that is from target block to gate
	 * */
	public int heuristic2()
	{
		int cost = 0;
		Block target = this.value.getBlocks().get(this.value.getTarget());
		int index = target.getX() + target.getLength();//next cell of target
		for(int i = index; i < 6; i++)
		{
			if(this.value.getBoard()[2][i])
				cost++;
		}
		
		return cost;
	}

	public int getTotalCost() {
		totalCost = this.getPathCost() + this.getHeuristicCost();
		
		return totalCost;
	}
	
	public boolean getWhichHeuristic()
	{
		return this.whichHeuristic;
	}
	
	public void setWhichHeuristic(boolean whichHeuristic) {
		this.whichHeuristic = whichHeuristic;
	}
}
