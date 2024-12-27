import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.Vector; // Import the Vector class
import java.util.StringTokenizer; // Import the StringTokenizer class
import java.util.HashMap;
import java.util.Map;

public class day19 {
    private static Map<String, Integer> cache = new HashMap<>();

    public static void main(String[] args) {
        // Initialize the file and vector
        File myObj = new File("input.txt");

        Vector<String> words = new Vector<>();
        Vector<String> str = new Vector <>(); //to be validated

        // Read the file and populate the vector
        readFile(myObj, words, str);

        int count = 0;

        for(String s: str) {
            System.out.println(s);
            if(valid(s, words) > 0) {
                System.out.println("isValid\n");
                count++;
            }
            else {
                System.out.println("notValid-----------\n");
            }
        }

        System.out.println("part 1 count is " + count + "\n");
    }

    public static int valid(String design, Vector<String> pattern) {
        if(design.isEmpty()) {
            return 1;
        }

        if(cache.containsKey(design)) {
            return cache.get(design);
        }

        int design_ways = 0;
        for(String pat : pattern) {
            if(startsWith(design, pat)) {
                int res = valid(design.substring(pat.length()), pattern);
                design_ways += res;
            }
        }

        cache.put(design, design_ways);
        return design_ways;
    }

    static boolean startsWith(String design, String pattern) {
        int length = pattern.length();
        if(design.length() < length) {
            return false;
        }
        String sub = design.substring(0, length);
        if(sub.equals(pattern)) {
            return true;
        }
        return false;
    }

    static void readFile(File myObj, Vector<String> v, Vector<String> str) {
        try {
            Scanner myReader = new Scanner(myObj);

            String data = myReader.nextLine();
            System.out.println(data); // Print the raw line

            // Tokenize and add to the vector
            StringTokenizer st1 = new StringTokenizer(data, " ");
            while (st1.hasMoreTokens()) {
                String tmp = st1.nextToken().replace(",", "").trim();
                v.add(tmp);
            }
            myReader.nextLine();
            // Read each line and tokenize it
            while (myReader.hasNextLine()) {
                String sen = myReader.nextLine();
                str.add(sen); 
            }
            myReader.close();
        } 
        catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}
