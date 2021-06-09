import java.net.*;
import java.time.Instant;
import java.util.LinkedList;

public class PingClient {

	public static void main(String[] args) throws Exception {
		
		// Input validation
		if (args.length < 2) throw new Exception("Please use: PingClient host port");
		
		String host = args[0];
		int port = Integer.parseInt(args[1]);
		
		DatagramSocket clientSocket;
		DatagramPacket sendPacket;
		DatagramPacket receivePacket;
		byte[] receiveData = new byte[1024];
		byte[] sendData = new byte[1024];
		InetAddress IPAddress;
		
		// Create client socket to destination
		clientSocket = new DatagramSocket();
		clientSocket.setSoTimeout(1000); 
		IPAddress = InetAddress.getByName (host);
		
		// Initialize variables for statistics
		int totalSent = 10;
		int receiveCount = 0;
		LinkedList<Long> times = new LinkedList<Long>();
		
		for (int seq = 0; seq < totalSent; seq++) {
			
			// Format PING message
			String currentTime = Instant.now().toString();
			String sendString = "PING " + seq  + " " + currentTime + ".\r\n";
			sendData = sendString.getBytes();
			
			// Create packet and send to server
			sendPacket = new DatagramPacket(sendData, 
					                        sendData.length,  
							                IPAddress, 
							                port);
			long sendTime = System.nanoTime();
			clientSocket.send(sendPacket);
			System.out.println("PING " + seq + " sent to " + host + " at " + currentTime + ".");
			
			// Create receiving packet and receive from server	
			try {
				receivePacket = new DatagramPacket(receiveData, receiveData.length); 	
				clientSocket.receive(receivePacket);
				long receiveTime = System.nanoTime();
				long elapsedTime = receiveTime - sendTime;
				String response = new String(receivePacket.getData(), 
	                                         0,
	                                         receivePacket.getLength());
				receiveCount++;
				
				long elapsedMilliseconds = elapsedTime / 1000000;
				times.add(elapsedMilliseconds);
				
				System.out.println("PING received from " + host + ": seq#=" + seq + " time=" + elapsedMilliseconds);
			} catch (Exception ex) {
				// The client did not receive a packet in the specified timeout window	
				System.out.println(ex.getMessage());
			}
		}
		
		// Gather and display statistics
		int dropCount = totalSent - receiveCount;
		
		System.out.println("--- PING statistics ---");
		System.out.println(totalSent + " packets transmitted, " + receiveCount + " received, " + (100 * dropCount / (double)totalSent) + "% packet loss");
		
		long min;
		long max;
		double avg;
		
		if (times.size() > 0) {
			min = times.getFirst();
			max = times.getFirst();
			
			double sum = 0;
			for (long time : times) {
				if (time > max) max = time;
				if (time < min) min = time;
				sum += time;
			}
			avg = sum / (double)times.size();

			System.out.println("rtt min/avg/max = " + min + " " + String.format("%.2f", avg) + " " + max + " ms");
		} else {
			System.out.println("Statistics unavailable -- no packets received.");
		}
		
		clientSocket.close();
	}
}