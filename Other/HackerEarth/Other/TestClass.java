import java.util.Scanner;
import java.lang.Exception;
public class TestClass
{
    static void solve(int arr[]) throws Exception
    {
        int ans=0;

        for(int i=0;i<10;i++)
            for(int j=i+1;j<10;j++)
                ans+=arr[i]/arr[j];

        throw new MyException(ans);
    }
    public static void main(String args[])
    {
        try
        {
            Scanner in=new Scanner(System.in);
            int n=in.nextInt();
            int []arr= new int[n];
            in.nextLine();

            for(int i=0;i<10;i++)
                arr[i]=Integer.parseInt(in.nextLine());

            String s=in.nextLine();
            System.out.println(s.charAt(10));

            solve(arr);
        }
        catch (MyException e) {}
        catch (Exception e) {
            try {
                throw new MyException(e);
            } catch (MyException ex) {}
        }
    }
}
//Write exception class here
class MyException extends Exception {
    MyException(int id) {
        System.out.println("MyException[" + id + "]");
        System.out.println("Exception Handling Completed");
    }

    MyException(Exception e) {
        if (e instanceof ArithmeticException) System.out.println("Invalid division");
        else if (e instanceof NumberFormatException) System.out.println("Format mismatch");
        else if (e instanceof ArrayIndexOutOfBoundsException) System.out.println("Array index is invalid");
        else if (e instanceof IndexOutOfBoundsException) System.out.println("Index is invalid");
        else System.out.println("Exception encountered");
        System.out.println("Exception Handling Completed");
    }
}