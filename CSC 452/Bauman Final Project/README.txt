Brian Bauman
CSC 452

Auction DB README:

The database is currently configured and all tables/procedures are created, as long as you log in with my credentials (bbauman5 / cdm1901319). 

If you'd like to recreate the tables and procedures, the relevant SQL files can be found in this directory. I'd recommend doing this -- the auctions will likely all have ended by the time you grade it, otherwise. The SQL files will repopulate some dummy data. 

If you would like to connect to the CDM database as a different user, the values of USER_NAME and PASSWORD can be modified in the AuctionDB.java file in ./AuctionDB/src.


EXECUTION INSTRUCTIONS:

(1) In a terminal/cmd session, navigate into the ./AuctionDB/src folder
(2) Compile the program:
	javac -classpath ".:../lib/*" AuctionDB.java
(3) Run the program:
	java -classpath ".:../lib/*" AuctionDB 
(4) Follow the on-screen prompts to navigate the auction house (see examples below). You can use the admin account (admin / admin) or register yourself as a new user and log in that way!

-------------------------------

    MAIN MENU

(1) Member registration
(2) Member login
(3) Quit

Enter your choice: ...

-------------------------------

    MEMBER MENU

(1) Place an item for auction
(2) Bid on an item
(3) Search for items
(4) Log out

Enter your choice: ...

-------------------------------

    SEARCH ITEMS

OPEN AUCTION
Item No.: 1
Title: Starry Night
Category: Art
Description: A famous landscape from renowned artist Vincent Van Gogh.
Quantity: 1
Start price: 2500000.00
Bid increment: 100000.00
Current price: 2500000.00
Time remaining: 11.77 hours

...

------------------------------