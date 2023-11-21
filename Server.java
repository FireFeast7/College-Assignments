import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server implements Runnable {
    int id;
    Socket socket;

    Server(Socket socket, int id) {
        this.socket = socket;
        this.id = id;
    }

    public void run() {
        System.out.println("Connected with id " + id + " ");
        DataInputStream inputStream = null;
        try {
            inputStream = new DataInputStream(socket.getInputStream());
        } catch (IOException e) {
            System.out.println(e);
        }
        DataOutputStream outputStream = null;
        try {
            outputStream = new DataOutputStream(socket.getOutputStream());
        } catch (IOException e) {
            System.out.println(e);
        }
        while (true) {
            try {
                outputStream.writeUTF(inputStream.readUTF());
            } catch (IOException e) {
                System.out.println("Client with ID = " + id + " exited.");
                return;
            }
        }
    }

    public static void main(String[] args) {
        int id = 1;
        int port;
        Scanner sc = new Scanner(System.in);
        System.out.println("This is Server Program");
        System.out.println("Enter the port no");
        port = sc.nextInt();
        sc.close();
        ServerSocket mySocket = null;
        try {
            mySocket = new ServerSocket(port);
        } catch (IOException e) {
            System.out.println(e);
        }
        while (true) {
            Socket socket = null;
            try {
                socket = mySocket.accept();
            } catch (IOException e) {
                System.out.println("Connected to a new Client");
            }
            new Thread(new Server(socket, id++)).start();
        }

    }
}