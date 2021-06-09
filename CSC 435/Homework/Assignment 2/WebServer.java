import java.io.* ;
import java.net.* ;
import java.util.*;

final class HttpRequest implements Runnable {
	
    final static String CRLF = "\r\n";
    Socket socket;
    
    // Constructor
    public HttpRequest(Socket socket) throws Exception {
        // Store the socket
        this.socket = socket;
    }
    
    // Implement the run() method of the Runnable interface.
    public void run() {
    		try {
    			processRequest();
    		} catch (Exception e) {
    			System.out.println(e);
    		}
    }

    private void processRequest() throws Exception {
    		// Get a reference to the socket's input and output streams
    		InputStream is = socket.getInputStream(); // get input stream of socket 
    		OutputStream oss = socket.getOutputStream(); // get output stream of socket 
    		DataOutputStream os = new DataOutputStream(oss);
	
    		// Set up input stream filters
    		BufferedReader br = new BufferedReader(new InputStreamReader(is));

    		// Get the request line of the HTTP request message
    		String requestLine = br.readLine(); 

    		// Extract the filename from the request line
    		StringTokenizer tokens = new StringTokenizer(requestLine);
    
    		// Check that the next token is a get
    		String nextToken = tokens.nextToken();
    		if (!nextToken.contains("GET")) {
    			throw new Exception("Request does not contain a GET.");
    		}
    		 
    		// Get the file name
    		String fileName = tokens.nextToken();
    		System.out.println(fileName);
	
    		// Prepend a "." so that file request is within the current directory
    		fileName = "." + fileName;
    		System.out.println(fileName);   		
    		
    		// Open the requested file
    		FileInputStream fis = null;
    		boolean fileExists = true;
    		try {
    			fis = new FileInputStream(fileName);
    		} catch (FileNotFoundException e) {
    			fileExists = false;
    		}

    		// Debug info for private use
    		System.out.println("Incoming!!!");
    		System.out.println(requestLine);
    		String headerLine = null;
    		while ((headerLine = br.readLine()).length() != 0) {
    			System.out.println(headerLine);
    		}
	
    		// Construct the response message
        String statusLine = null;
        String contentTypeLine = null;
        String entityBody = null;
        if (fileExists) {
        		statusLine = "HTTP/1.0 200 OK" + CRLF; // should contain "HTTP/1.0 200 OK" and a CRLF
        		contentTypeLine = "Content-Type: " + contentType(fileName) + CRLF;
        } else {
        		statusLine = "HTTP/1.0 404 Not Found" + CRLF; // 404 error msg if not found. 
                     // ie. "HTTP/1.0 404 Not Found" + CRLF;
        		contentTypeLine = "Content-Type: text.html" + CRLF; // set it to text/html 
                     // ie "Content-Type: text/html" + CRLF;
        		entityBody = "<HTML>" + 
        				     "<HEAD><TITLE>Not Found</TITLE></HEAD>" +
        				     "<BODY>Not Found</BODY></HTML>";
        }
	
        // Send the status line on os
        os.writeBytes(statusLine);

        // Send the content type line on os
        os.writeBytes(contentTypeLine);
       
        // Send a blank line on os to indicate the end of the header lines.
        os.writeBytes(CRLF);

        // Send the entity body.
        if (fileExists) {
        		sendBytes(fis, os);
        		fis.close();
        } else {
        		os.writeBytes(entityBody) ;
        }

        // Close streams and socket.
        os.close();
        br.close();
        socket.close();
    }

    private static void sendBytes(FileInputStream fis, OutputStream os) throws Exception {
    		// Construct a 1K buffer to hold bytes on their way to the socket.
    		byte[] buffer = new byte[1024];
    		int bytes = 0;
	
    		// Copy requested file into the socket's output stream.
    		while ((bytes = fis.read(buffer)) != -1) {
    			os.write(buffer, 0, bytes);
    		}
    }

    private static String contentType(String fileName) {
    		if (fileName.endsWith(".htm") || fileName.endsWith(".html")) {
    			return "text/html";
    		}
    		if (fileName.endsWith(".ram") || fileName.endsWith(".ra")) {
    			return "audio/x-pn-realaudio";
    		}
    		
    		return "application/octet-stream" ;
    	}
}

public final class WebServer {
	
    public static void main(String argv[]) throws Exception {
    	
    		// Get the port number from the command line
    		int port = (new Integer(argv[0])).intValue();
    		
    		// Establish the listen socket at port
    		System.out.println("Binding port " + port + "...");
    		ServerSocket socket = new ServerSocket(port);
	
    		// Process HTTP service requests in an infinite loop
    		while (true) {
    			
    			// Listen for a TCP connection request.
    			System.out.println("Waiting for connection...");
    			Socket connection = socket.accept();
	    
    			// Construct an object to process the HTTP request message
    			HttpRequest request = new HttpRequest(connection);
	    
    			// Create a new thread to process the request
    			Thread thread = new Thread(request);
	    
    			// Start the thread
    			System.out.println("Processing request...");
    			thread.start();
    		}
    }
}