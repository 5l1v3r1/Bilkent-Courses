import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

public class SeekAndDestroy {

    private final static String TARGET_FILE = "target.jpg";
    private static boolean isTargetFound = false;

    private static String address;
    private static int port;

    private static Socket clientSocket;

    private static DataOutputStream outToServer;
    private static BufferedReader inFromServer;

    private static Directory root;

    public static void main(String[] args) throws IOException {

        address = args[0];
        port = Integer.parseInt(args[1]);
        clientSocket = new Socket(address, port);

        outToServer = new DataOutputStream(clientSocket.getOutputStream());

        inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream(), StandardCharsets.US_ASCII));

        root = new Directory("root");

        run();
        sendQUIT();
    }

    private static void run() throws IOException {
        sendUSER("bilkent");
        if (getResponse().contains("200")) {
            sendPASS("cs421");
            if (getResponse().contains("200")) {
                search();
            }
        }
    }

    private static void search() throws IOException {
        serverSocket = new ServerSocket(0);
        sendPORT(serverSocket.getLocalPort());
        recursiveSearch(root);
    }

    private static ServerSocket serverSocket;

    private static void recursiveSearch(final Directory directory) throws IOException {
        if (!isTargetFound) {
            sendNLST();

            Socket dataSocket = serverSocket.accept();
            BufferedReader dataReader = new BufferedReader(new InputStreamReader(dataSocket.getInputStream(), StandardCharsets.US_ASCII));
            String data;
            int count = 0;
            while ((data = dataReader.readLine()) != null) {
                if (count == 0 && data.length() > 2) {
                    count++;
                    data = data.substring(2);
                } else count++;

                if (data.contains(":d")) {
                    directory.addNewDirectory(data.substring(0, data.length() - 2));
                } else if (data.contains(":f") && data.contains(TARGET_FILE)) {
                    isTargetFound = true;
                    downloadFile();
                }
            }


            if (!directory.getChildrenList().isEmpty()) {
                for (Directory dir : directory.getChildrenList()) {
                    if (!isTargetFound) {
                        sendCWD(dir.getName());
                        if (getResponse().contains("200"))
                            recursiveSearch(dir);
                    }
                }
                if (!isTargetFound)
                    sendCDUP();
            } else {
                sendCDUP();
            }
        }
    }

    private static void downloadFile() throws IOException {
        sendRETR(TARGET_FILE);
        Socket downloadSocket = serverSocket.accept();

        DataInputStream dataReader = new DataInputStream(downloadSocket.getInputStream());
        byte[] lengthHeader = new byte[2];
        dataReader.read(lengthHeader);
        ByteBuffer wrapped = ByteBuffer.wrap(lengthHeader);
        int length = wrapped.getShort();
        byte[] data = new byte[length];
        Path file = Paths.get("received.jpg");

        while (dataReader.read(data) > -1) {
            Files.write(file, data);
        }

        deleteFile();
    }

    private static void deleteFile() throws IOException {
        sendDELE(TARGET_FILE);
    }


    // Send username to the server.
    // USER bilkent\r\n
    private static void sendUSER(final String username) throws IOException {
        outToServer.writeBytes("USER " + username + "\r\n");
    }

    // Send password to the server.
    // PASS cs421\r\n
    private static void sendPASS(final String password) throws IOException {
        outToServer.writeBytes("PASS " + password + "\r\n");
    }

    // Send port number of the data connection that the client is bound to.
    // PORT 60001\r\n
    private static void sendPORT(final int port) throws IOException {
        outToServer.writeBytes("PORT " + port + "\r\n");
    }

    // Obtain the list of all files and directories in the current working folder of the server.
    // NLST\r\n
    private static void sendNLST() throws IOException {
        outToServer.writeBytes("NLST\r\n");
    }

    // Change the working directory to the one of the child directories of
    // the current working directory of the server.
    // CWD images\r\n
    private static void sendCWD(final String child) throws IOException {
        outToServer.writeBytes("CWD " + child + "\r\n");
    }

    // Go to the parent directory of the current working directory of the server.
    // CDUP\r\n
    private static void sendCDUP() throws IOException {
        outToServer.writeBytes("CDUP\r\n");
    }

    // Retrieve the file <filename> from the current working directory of the server.
    // RETR sample.txt\r\n
    private static void sendRETR(final String fileName) throws IOException {
        outToServer.writeBytes("RETR " + fileName + "\r\n");
    }

    // Delete the file <filename> from the current working directory of the server.
    // DELE sample.txt\r\n
    private static void sendDELE(final String fileName) throws IOException {
        outToServer.writeBytes("DELE " + fileName + "\r\n");
    }

    // Tell server to end the session and shutdown.
    // QUIT\r\n
    private static void sendQUIT() throws IOException {
        outToServer.writeBytes("QUIT\r\n");
    }

    private static String getResponse() throws IOException {
        return inFromServer.readLine();
    }
}

class Directory {
    private String name;
    private ArrayList<Directory> childrenList;

    Directory(String name) {
        this.name = name;
        childrenList = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    void addNewDirectory(String name) {
        childrenList.add(new Directory(name));
    }

    public ArrayList<Directory> getChildrenList() {
        return childrenList;
    }
}