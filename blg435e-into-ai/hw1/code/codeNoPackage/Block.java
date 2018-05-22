
public class Block {
	private int x;//column
	private int y;//row
	private int length;
	private char direction;
	private boolean isTarget;
	
	public Block(int x, int y,int length, char direction, boolean isTarget)
	{
		this.setX(x);
		this.setY(y);
		this.setLength(length);
		this.setDirection(direction);
		this.setTarget(isTarget);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

	public char getDirection() {
		return direction;
	}

	public void setDirection(char direction) {
		this.direction = direction;
	}

	public int getLength() {
		return length;
	}

	public void setLength(int length) {
		this.length = length;
	}

	public boolean isTarget() {
		return isTarget;
	}

	public void setTarget(boolean isTarget) {
		this.isTarget = isTarget;
	}
	
	public String toString()
	{
		String str = "";
		str = Integer.toString(y) + " " + Integer.toString(x) + " " 
				+ Integer.toString(length) + " " + Character.toString(direction);
		return str;
	}

}
