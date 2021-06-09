import sys, time, math
from socket import *

# Get the server hostname and port as command line arguments                  
host = sys.argv[1]
port = sys.argv[2]
timeout = 1 # in second, change as needed

# Create UDP client socket
# Note the use of SOCK_DGRAM for UDP datagram packet
clientsocket = socket(AF_INET, SOCK_DGRAM)
# Set socket timeout as 1 second
clientsocket.settimeout(timeout)
# Command line argument is a string, change the port into integer
port = int(port)  
# Sequence number of the ping message
ptime = 0  

receiveCount = 0;
times = []

# Ping for 10 times
while ptime < 10: 
	ptime += 1

	# Format the message to be sent. 
        # use time.asctime() for currTime
	currTime = str(time.asctime())

	data = "PING " + str(ptime) + " " + currTime + "\r\n"
     
	try:
		print("PING " + str(ptime) + " sent to " + host + " at " + currTime)

		# Sent time. from time.time()
		RTTb = time.time()

		# Send the UDP packet with the ping message
		clientsocket.sendto(data.encode(),(host, port))

		# Receive the server response
		message, address = clientsocket.recvfrom(1024)  
		receiveCount = receiveCount + 1

		# Received time. use time.time()
		RTTa = time.time()

		# Display the server response as an output
		print("PING received from " + host + ": seq#" + str(ptime) + " time=" + time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(RTTb)))

		# Round trip time is the difference between sent and received time
		elapsedTime = (RTTa - RTTb) * 1000
		times.append(elapsedTime)

	except:
		# Server does not response
		# Assume the packet is lost
		print ("Request timed out.")
		continue

# Gather and print statistics
dropCount = 10 - receiveCount
print("--- PING statistics ---")
print("10 packets transmitted, " + str(receiveCount) + " received, " + str((100 * dropCount / 10)) + "% packet loss")

if len(times) > 0:
	min = times[0]
	max = times[0]
	sum = 0
	
	for time in times:
		sum = sum + time
		if (time < min):
			min = time
		if (time > max):
			max = time
	
	avg = sum / receiveCount
	print("rtt min/avg/max = " + str(min) + " " + str(avg) + " " + str(max) + " ms")

else:
	print("Statistics unavailable -- no packets received.")

# Close the client socket
clientsocket.close()