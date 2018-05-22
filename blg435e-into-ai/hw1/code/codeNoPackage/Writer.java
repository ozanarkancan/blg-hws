import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class Writer {
	private FileOutputStream ofstream;
	private DataOutputStream out;
	private BufferedWriter writer;
	
	public Writer(String path)
	{
		try {
			ofstream = new FileOutputStream(path);
			out = new DataOutputStream(ofstream);
			writer = new BufferedWriter(new OutputStreamWriter(out));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
			
	}
	
	public void write(String text)
	{
		try {
			writer.write(text);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void close()
	{
		try {
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
