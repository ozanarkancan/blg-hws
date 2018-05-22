import java.util.Scanner;

public class MainProgram {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		if(args.length == 3)
		{
			boolean choice = false;
			choice = Integer.parseInt(args[2]) == 1 ? false : true;
			AStar astar = new AStar(createStartState(args[0], choice), args[1]);
			astar.search();
		}
		else if(args.length == 0)
		{
			Scanner input = new Scanner(System.in);
			System.out.println("Give the path of start state:");
			String inputPath = input.nextLine();
			System.out.println("Give the path of output:");
			String outputPath = input.nextLine();
			System.out.println("Choose the heuristic function(1 or 2):");
			int which = input.nextInt();
			input.close();
			
			boolean choice = which == 1 ? false : true;
			AStar astar = new AStar(createStartState(inputPath, choice), outputPath);
			astar.search();
		}
		else
			System.out.println("Wrong program call.");
	}
	
	public static Node createStartState(String path, boolean heuristic)//Choose the heuristic function
	{
		Reader reader = new Reader(path);
		String line = "";
		boolean target = true;
		Board board = new Board();
		while((line = reader.readLine()) != null)
		{
			line = line.trim();
			if(line == "")
				break;
			String[] data = line.split(" ");
			Block block = new Block(Integer.parseInt(data[1]), Integer.parseInt(data[0]),
					Integer.parseInt(data[2]), data[3].charAt(0), target);
			if(target)
				target = false;
			
			board.addBlock(block);
		}
		board.updateBoard();
		board.setCost(0);
		board.setTarget(0);
		Node start = new Node(board);
		start.setWhichHeuristic(heuristic);
		return start;
	}

}
