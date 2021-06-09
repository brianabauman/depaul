Problem 1:
- Open the "problem 1" folder and build with sbt, then run.

Problem 2:
- In one terminal session/command window:
	- Open "problem 2/server" and build with sbt, then run
	- This starts the server
- In another terminal session/command window:
	- Open "problem 2/client" and build with sbt, then run
	- This starts the client
- In the current configuration, the client runs two mappers and two reducers locally, and two of each remotely (on the server)
- The program logs some errors regarding dead letters after the execution is complete and the client terminates the connection. I hope this is OK -- not really sure how to remove them, but everything does shut down after the results are logged!