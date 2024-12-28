import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;
import java.util.StringTokenizer;
import java.util.HashMap;
import java.util.Map;
import java.math.BigInteger;

public class day19 {
    private static Map<String, BigInteger> cache = new HashMap<>();

    public static void main(String[] args) {
        // Initialize the file and vector
        File myObj = new File("input.txt");

        Vector<String> words = new Vector<>();
        Vector<String> str = new Vector<>(); //to be validated

        // Read the file and populate the vector
        readFile(myObj, words, str);

        int count = 0;
        BigInteger overall = BigInteger.ZERO;
        for (String s : str) {
            System.out.println(s);
            BigInteger tmp = valid(s, words);
            if (tmp.compareTo(BigInteger.ZERO) > 0) {
                System.out.println("isValid\n");
                count++;
                overall = overall.add(tmp);
            } else {
                System.out.println("notValid-----------\n");
            }
        }

        System.out.println("part 1 count is " + count + "\n");
        System.out.println("part 2 count is " + overall + "\n");
    }

    public static BigInteger valid(String design, Vector<String> pattern) {
        if (design.isEmpty()) {
            return BigInteger.ONE;
        }
        design = design.trim();
        // System.out.println(design);
        if (cache.containsKey(design)) {
            System.out.println("here\n");
            System.out.println("get is " + cache.get(design));
            return cache.get(design);
        }

        BigInteger design_ways = BigInteger.ZERO;
        for (String pat : pattern) {
            if (startsWith(design, pat)) {
                BigInteger res = valid(design.substring(pat.length()), pattern);
                System.out.println("res is " + res);
                design_ways = design_ways.add(res);
            }
        }
        System.out.println("designways " + design_ways);
        cache.put(design, design_ways);
        return design_ways;
    }

    static boolean startsWith(String design, String pattern) {
        int length = pattern.length();
        if (design.length() < length) {
            return false;
        }
        String sub = design.substring(0, length);
        return sub.equals(pattern);
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
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}
