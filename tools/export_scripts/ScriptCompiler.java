import java.io.*;
import java.util.*;

// Takes a list of script file names and creates 0.txt by putting them end to end
class ScriptCompiler
{
	public static void main(String[] args) throws IOException
	{
		if(args.length != 1)
		{
			System.out.println("Usage: ScriptCompiler <scripts.txt>");
			return;
		}
		
		Scanner sc = new Scanner(new FileReader(args[0]));
		PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream("0.txt"),"SHIFT_JIS"));
			
		while (sc.hasNextLine())
		{
			File f = new File(sc.nextLine());
			System.out.println("Adding " + f.getPath() + " to 0.txt");
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(f.getPath()),"SHIFT_JIS"));
			String line = br.readLine();
			while (line != null)
			{
				pw.println(line);
				line = br.readLine();
			}
			br.close();
		}
		
		pw.close();
		System.out.println("Done writing 0.txt");
	}
}