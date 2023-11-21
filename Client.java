import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        int portno;
        String sip;
        Scanner sc = new Scanner(System.in);
        System.out.println("This is the client Program");
        Socket socket = null;
        System.out.println("Enter the Server IP: ");
        sip = sc.nextLine();
        System.out.println("Enter the port no : ");
        portno = sc.nextInt();

        try {
            socket = new Socket(sip, portno);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Attempting to create input stream : ");
        DataInputStream inputStream = null;
        try {
            inputStream = new DataInputStream(socket.getInputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Data Output Stream attempt");
        DataOutputStream outputStream = null;
        try {
            outputStream = new DataOutputStream(socket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
        while (true) {
            String inputString = sc.nextLine();
            String copy = new String(inputString);

            try {
                outputStream.writeUTF(inputString);
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                System.out.println(inputStream.readUTF());
            } catch (IOException E) {
                System.out.println(E);
            }
        }
    }
}
