To run:
- Navigate to the DeathWatch_server folder, build with sbt and run. This will start up the server.
- Once the server is running, open a second shell and navigate to the DeathWatch_client folder, build with sbt, and run. This will kick off the client that creates and destroys the actors.

After the client is running, killing the server will return a message to the client informing it of the server actor's death.