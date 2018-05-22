import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

public class Reader {
	private FileInputStream ifstream;
	private DataInputStream in;
	private BufferedReader reader;
	
	public Reader(String path)
	{
		try {
			ifstream = new FileInputStream(path);
			in = new DataInputStream(ifstream);
			reader = new BufferedReader(new InputStreamReader(in));	
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}		
	}
	
	public String readLine()
	{
		String line = "";
		try {
			line = reader.readLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return line;
	}
	
	public void close()
	{
		try {
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
