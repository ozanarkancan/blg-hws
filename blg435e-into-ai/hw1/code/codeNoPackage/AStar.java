import java.util.ArrayList;
import java.util.PriorityQueue;

public class AStar {
	private Node root;
	private PriorityQueue<Node> priorityQueue;
	private Writer writer;
	
	public AStar(Node root, String outputPath)
	{
		this.root = root;
		priorityQueue = new PriorityQueue<Node>();
		priorityQueue.add(root);
		writer = new Writer(outputPath);
	}
	
	public void search()
	{
		Node current = priorityQueue.poll();
		
		while(!current.isGoal())
		{
			current.createChildren();
			for(Node n : current.getChildren())
			{
				if(n != null)
					priorityQueue.add(n);
			}
			
			if(priorityQueue.size() != 0)
				current = priorityQueue.poll();
			else
			{
				current = null;
				break;
			}
		}
		
		if(current == null)
		{
			writer.write("There is no solution.");
			writer.close();			
		}
		else
		{
			writeSolution(current);
		}
	}
	
	public void writeSolution(Node solutionState)
	{
		ArrayList<Node> solutionPath = new ArrayList<Node>();
		solutionPath.add(solutionState);
		
		while(solutionState.getParent() != null)
		{
			solutionState = solutionState.getParent();
			solutionPath.add(0, solutionState);
		}
		
		for(Node n : solutionPath)
		{
			for(Block b : n.getBlocks())
				writer.write(b.toString() + "\n");
			writer.write("\n");
		}
		writer.close();
	}

}
