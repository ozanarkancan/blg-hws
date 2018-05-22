import java.util.ArrayList;

public class Board{
	private ArrayList<Block> blocks;
	private boolean[][] board;
	private int target;
	private int cost;
	
	public Board()
	{
		board = new boolean[6][6];
		blocks = new ArrayList<Block>();
		for(int i = 0; i < 6; i++)
			for(int j = 0; j < 6; j++)
				board[i][j] = false;
	}
	
	public ArrayList<Block> getCopyOfBoardConfig()
	{
		ArrayList<Block> copy = new ArrayList<Block>();
		for(Block b : blocks)
		{
			Block newBlock = new Block(b.getX(), b.getY(), b.getLength(), b.getDirection(), b.isTarget());
			copy.add(newBlock);
		}
		return copy;
	}
	
	public void addBlock(Block b)
	{
		blocks.add(b);
	}
	
	public void updateBoard()
	{
		for(Block b : blocks)
		{
			if(b.getDirection() == 'v')
			{
				for(int i = 0; i < b.getLength(); i++)
				{
					board[b.getX() - 1][b.getY() - 1 - i] = true;
				}
			}
			else
			{
				for(int i = 0; i < b.getLength(); i++)
				{
					board[b.getX() - 1 + i][b.getY() - 1] = true;
				}
			}
		}
	}
	public ArrayList<Block> getBlocks()
	{
		return blocks;
	}
	
	public void setBlocks(ArrayList<Block> blocks)
	{
		this.blocks = blocks;
	}
	
	public Board moveBlock(Block b, int direction)
	{
		/*
		 * 0 left or down
		 * 1 right or up
		 */
		Board newConfiguration = null;
		int cost = 0;
		
		if(b.getDirection() == 'v')
		{
			int  index = b.getY();
			int temp = index;
			//index--;//index with programming language notation(start with 0)
			if(direction == 0)
			{
				if(index != 6)
				{
					if(!board[b.getX() - 1][index])//can move to next square
					{
						cost++;
						while(index < 5)//move to suitable place
						{
							index++;
							if(board[b.getX() - 1][index])
							{
								index--;
								break;
							}
							cost++;
						}
						b.setY(index + 1); //Change for next step
						ArrayList<Block> blocks = this.getCopyOfBoardConfig();
						b.setY(temp); //Set current position
						newConfiguration = new Board();
						newConfiguration.setBlocks(blocks);
						newConfiguration.updateBoard();
						newConfiguration.setTarget(this.getTarget());
						newConfiguration.setCost(cost + this.getCost());
					}
				}
			}
			else
			{
				if(index - b.getLength() != 0)
				{
					index--;
					if(!board[b.getX() - 1][index - b.getLength()])
					{
						cost++;
						while(index - b.getLength() > -1)//move to suitable place
						{
							if(board[b.getX() - 1][index - b.getLength()])
								break;
							index--;
							cost++;
						}
						b.setY(index + 1); //Change for next step
						ArrayList<Block> blocks = this.getCopyOfBoardConfig();
						b.setY(temp); //Set current position
						newConfiguration = new Board();
						newConfiguration.setBlocks(blocks);
						newConfiguration.updateBoard();
						newConfiguration.setTarget(this.getTarget());
						newConfiguration.setCost(cost + this.getCost());
					}
				}
			}
		}
		else
		{
			int  index = b.getX();
			int temp = index;
			if(direction == 0)
			{
				if(index != 1)
				{
					index -= 2;
					if(!board[index][b.getY() - 1])//can move to next square
					{
						cost++;
						while(index > 0)//move to suitable place
						{
							index--;
							if(board[index][b.getY() - 1])
							{
								index++;
								cost++;
								break;
							}
							cost++;
							//index--;
							//cost++;
						}
						b.setX(index + 1); //Change for next step
						ArrayList<Block> blocks = this.getCopyOfBoardConfig();
						b.setX(temp); //Set current position
						newConfiguration = new Board();
						newConfiguration.setBlocks(blocks);
						newConfiguration.updateBoard();
						newConfiguration.setTarget(this.getTarget());
						newConfiguration.setCost(cost + this.getCost());
					}
				}
			}
			else
			{
				if(index + b.getLength() != 7)
				{
					index--;
					if(!board[index + b.getLength()][b.getY() - 1])
					{
						cost++;
						while(index + b.getLength() < 6)//move to suitable place
						{
							if(board[index + b.getLength()][b.getY() - 1])
								break;
							index++;
							cost++;
						}
						b.setX(index + 1); //Change for next step
						ArrayList<Block> blocks = this.getCopyOfBoardConfig();
						b.setX(temp); //Set current position
						newConfiguration = new Board();
						newConfiguration.setBlocks(blocks);
						newConfiguration.updateBoard();
						newConfiguration.setTarget(this.getTarget());
						newConfiguration.setCost(cost + this.getCost());
					}
				}
			}
		}
		
		return newConfiguration;
	}
	
	public boolean[][] getBoard()
	{
		return this.board;
	}

	public int getTarget() {
		return target;
	}

	public void setTarget(int target) {
		this.target = target;
	}

	public boolean isGoal()
	{
		boolean isGoal = false;
		
		Block target = blocks.get(this.getTarget());
		if(target.getX() - 1 + target.getLength() == 6 && target.getY() == 3)
			isGoal = true;
		
		return isGoal;
		
	}

	public int getCost() {
		return cost;
	}

	public void setCost(int cost) {
		this.cost = cost;
	}
}
