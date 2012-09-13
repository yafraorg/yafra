// This example is from the book _Java in a Nutshell_ by David Flanagan.
// Written by David Flanagan.  Copyright (c) 1996 O'Reilly & Associates.
// You may study, use, modify, and distribute this example for any purpose.
// This example is provided WITHOUT WARRANTY either expressed or implied.

import java.applet.*;
import java.awt.*;
import java.io.*;
import java.net.*;

public class AppletClient extends Applet {
    public static final int PORT = 6789;
    Socket s;
    DataInputStream in;
    PrintStream out;
    TextField inputfield;
    TextArea outputarea;
    StreamListener listener;
    
    // Create a socket to communicate with a server on port 6789 of the
    // host that the applet's code is on.  Create streams to use with
    // the socket.  Then create a TextField for user input and a TextArea
    // for server output.  Finally, create a thread to wait for and 
    // display server output.
    public void init() {
        try {
            s = new Socket(this.getCodeBase().getHost(), PORT);
            in = new DataInputStream(s.getInputStream());
            out = new PrintStream(s.getOutputStream());

            inputfield = new TextField();
            outputarea = new TextArea();
            outputarea.setEditable(false);
            this.setLayout(new BorderLayout());
            this.add("North", inputfield);
            this.add("Center", outputarea);
            
            listener = new StreamListener(in, outputarea);

            this.showStatus("Connected to " 
                    + s.getInetAddress().getHostName() 
                    + ":" + s.getPort());
        }
        catch (IOException e) { this.showStatus(e.toString()); }
    }
    
    // When the user types a line, send it to the server.
    public boolean action(Event e, Object what) {
        if (e.target == inputfield) {
            out.println((String)e.arg);
            inputfield.setText("");
            return true;
        }
        return false;
    }
}

// Wait for output from the server on the specified stream, and display
// it in the specified TextArea.
class StreamListener extends Thread {
    DataInputStream in;
    TextArea output;
    public StreamListener(DataInputStream in, TextArea output) {
        this.in = in;
        this.output = output;
        this.start();
    }
    public void run() {
        String line;
        try {
            for(;;) {
                line = in.readLine();
                if (line == null) break;
                output.setText(line);
            }
        }
        catch (IOException e) { output.setText(e.toString()); }
        finally { output.setText("Connection closed by server."); }
    }
}
