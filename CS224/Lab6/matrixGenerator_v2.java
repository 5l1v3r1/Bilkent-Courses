
import java.nio.charset.StandardCharsets;
import java.io.*;
import java.util.Random;

 
public class matrixGenerator_v2 {

	public static final int COUNT = 100;
 
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
 
		generateFile("matrix1.dat");
		generateFile("matrix2.dat");
	}
 
private static void generateFile(String fileName) {
 
	try{

	      File file=new File(fileName);
	      
	      if (file.createNewFile()){
	        System.out.println("File is created!");
	      }else{
	        System.out.println("File already exists.");
	      }
	      
 
		FileOutputStream fos=new FileOutputStream(fileName);
		DataOutputStream dos=new DataOutputStream(fos);
 
		Random generator = new Random();
 
		String nums="";
		for (int i=0; i<COUNT; i++) {
			for (int j=0; j<COUNT; j++) {
				int num=generator.nextInt(9) + 1; //generate a random number
				nums += String.valueOf(num).concat( " "); //write the number to the file 
			}
			nums += "\n";
		}
		byte[] b = nums.getBytes(StandardCharsets.US_ASCII);
		dos.write(b);
		
		dos.close();
		
		}

 
		catch (IOException e)
		{
			e.printStackTrace();
		} 
 
	}
}
