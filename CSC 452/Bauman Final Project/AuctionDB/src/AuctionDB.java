import oracle.jdbc.OracleTypes;

import java.sql.*;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.Scanner;

public class AuctionDB {

    private static String USER_NAME = "bbauman5";
    private static String PASSWORD = "cdm1901319";

    private static String _currentUserName = "";
    private static Connection _connection;

    public static void main(String[] args) {

        try {
            //connect to Auction DB
            Class.forName("oracle.jdbc.driver.OracleDriver");
            _connection = DriverManager.getConnection("jdbc:oracle:thin:@acadoradbprd01.dpu.depaul.edu:1521:ACADPRD0",
                    USER_NAME,
                    PASSWORD);

            executeMainMenu();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    private static void executeMainMenu() {
        _currentUserName = "";

        clearScreen();
        System.out.println("    MAIN MENU");
        System.out.println();
        System.out.println("(1) Member registration");
        System.out.println("(2) Member login");
        System.out.println("(3) Quit");
        System.out.println();
        System.out.print("Enter your choice: ");

        switch (new Scanner(System.in).nextInt()) {
            case 1:
                executeMemberRegistration();
                break;
            case 2:
                executeMemberLogin();
                break;
            case 3:
                executeGoodbye();
                break;
            default:
                clearScreen();
                System.out.println();
                System.out.println("Error encountered:");
                System.out.println("Invalid selection, please try again...");
                new Scanner(System.in).nextLine();
                executeMainMenu();
                break;
        }
    }

    private static void executeMemberRegistration() {
        clearScreen();
        System.out.println("    MEMBER REGISTRATION");
        System.out.println();
        System.out.println("Please type \"quit\" to return to the main");
        System.out.println("menu at any time!");
        System.out.println();
        System.out.print("Press Enter to continue...");
        new Scanner(System.in).nextLine();

        clearScreen();
        System.out.println("    MEMBER REGISTRATION");
        System.out.println();
        System.out.print("User Name: ");
        String userName = readOrQuit();
        System.out.print("Password: ");
        String password = readOrQuit();
        System.out.print("Full Name: ");
        String name = readOrQuit();
        System.out.print("Address (on one line): ");
        String address = readOrQuit();
        System.out.print("Phone Number (e.g. 123-456-7890): ");
        String phoneNumber = readOrQuit();
        System.out.print("Email address: ");
        String email = readOrQuit();

        if (verifyUser(userName)) {
            registerUser(userName, password, name, address, phoneNumber, email);
        } else {
            clearScreen();
            System.out.println("    MEMBER REGISTRATION");
            System.out.println();
            System.out.println("User name taken. Please try again. ");
            System.out.println();
            System.out.print("Press Enter to continue... ");
            new Scanner(System.in).nextLine();

            executeMemberRegistration();
        }

        _currentUserName = userName;
        clearScreen();
        System.out.println("    MEMBER REGISTRATION");
        System.out.println();
        System.out.println("Registration complete!");
        System.out.println();
        System.out.println("Press Enter to continue...");
        System.out.println();
        new Scanner(System.in).nextLine();

        executeMemberMenu();
    }

    private static void executeMemberLogin() {
        clearScreen();
        System.out.println("    MEMBER LOGIN");
        System.out.println();
        System.out.print("User Name: ");
        String userName = new Scanner(System.in).nextLine();
        System.out.print("Password: ");
        String password = new Scanner(System.in).nextLine();

        if (verifyLogin(userName, password)) {
            _currentUserName = userName;
            executeMemberMenu();
        } else {
            clearScreen();
            System.out.println("    MEMBER LOGIN");
            System.out.println();
            System.out.println("Login failed. Returning to Main Menu. ");
            System.out.println();
            System.out.print("Press Enter to continue. ");
            new Scanner(System.in).nextLine();

            executeMainMenu();
        }
    }

    private static void executeGoodbye() {
        clearScreen();
        System.out.println();
        System.out.println("Thanks for visiting Auction DB!");
        System.out.println();
        System.console().readLine();
        System.exit(0);
    }

    private static void executeMemberMenu() {
        clearScreen();
        System.out.println("    MEMBER MENU");
        System.out.println();
        System.out.println("(1) Place an item for auction");
        System.out.println("(2) Bid on an item");
        System.out.println("(3) Search for items");
        System.out.println("(4) Log out");
        System.out.println();
        System.out.print("Enter your choice: ");

        switch (new Scanner(System.in).nextInt()) {
            case 1:
                executeAddItem();
                break;
            case 2:
                executePlaceBid();
                break;
            case 3:
                executeSearchItems();
                break;
            case 4:
                executeMainMenu();
                break;
            default:
                clearScreen();
                System.out.println();
                System.out.println("Error encountered:");
                System.out.println("Invalid selection, please try again...");
                new Scanner(System.in).nextLine();
                executeMainMenu();
                break;
        }
    }

    private static void executeAddItem() {
        clearScreen();
        System.out.println("    ADD ITEM FOR AUCTION");
        System.out.println();
        System.out.println("Please type \"quit\" to return to the main");
        System.out.println("menu at any time!");
        System.out.println();
        System.out.print("Press Enter to continue...");
        new Scanner(System.in).nextLine();

        int quantity = 0;
        double price = 0.00;
        double bidIncrement = 0.00;
        double closeTime = 0.00;

        clearScreen();
        System.out.println("    ADD ITEM FOR AUCTION");
        System.out.println();
        System.out.print("Title (max length 128): ");
        String title = readOrQuit();
        System.out.print("Category (max length 32): ");
        String category = readOrQuit();
        System.out.print("Description (max length 256): ");
        String description = readOrQuit();
        System.out.print("Quantity: ");
        String quantityText = readOrQuit();
        System.out.print("Start Price (e.g. 2500.00): ");
        String startPriceText = readOrQuit();
        System.out.print("Bid Increment (e.g. 50.00): ");
        String bidIncrementText = readOrQuit();
        System.out.print("Close time, in hours (e.g. \"5.5\" --> in 5 1/2 hours): ");
        String closeTimeText = readOrQuit();

        try {
            quantity = Integer.parseInt(quantityText);
            price = Double.parseDouble(startPriceText);
            bidIncrement = Double.parseDouble(bidIncrementText);
            closeTime = Double.parseDouble(closeTimeText);
        } catch (Exception ex) {
            clearScreen();
            System.out.println("    ADD ITEM FOR AUCTION");
            System.out.println();
            System.out.println("There were errors with your input. Please try again.");
            System.out.println();
            System.out.print("Press Enter to continue...");
            System.out.println();
            new Scanner(System.in).nextLine();
            executeAddItem();
        }

        addItem(_currentUserName, title, category, description, quantity, price, bidIncrement, closeTime);

        clearScreen();
        System.out.println("    ADD ITEM FOR AUCTION");
        System.out.println();
        System.out.println("Item added!");
        System.out.println();
        System.out.print("Press Enter to continue...");
        System.out.println();
        new Scanner(System.in).nextLine();
        executeMemberMenu();
    }

    private static void executePlaceBid() {
        clearScreen();
        System.out.println("    PLACE BID");
        System.out.println();
        System.out.println("Please type \"quit\" to return to the main");
        System.out.println("menu at any time!");
        System.out.println();
        System.out.print("Press Enter to continue...");
        new Scanner(System.in).nextLine();

        int itemID = 0;
        double bidPrice = 0.00;
        int quantityDesired = 0;

        clearScreen();
        System.out.println("    PLACE BID");
        System.out.println();
        System.out.print("Item ID: ");
        String itemIDText = readOrQuit();
        System.out.print("Bid Price (e.g. 2500.00): ");
        String bidPriceText = readOrQuit();
        System.out.print("Quantity desired: ");
        String quantityDesiredText = readOrQuit();

        try {
            itemID = Integer.parseInt(itemIDText);
            bidPrice = Double.parseDouble(bidPriceText);
            quantityDesired = Integer.parseInt(quantityDesiredText);
        } catch (Exception ex) {
            clearScreen();
            System.out.println("    PLACE BID");
            System.out.println();
            System.out.println("There were errors with your input. Please try again.");
            System.out.println();
            System.out.print("Press Enter to continue...");
            System.out.println();
            new Scanner(System.in).nextLine();
            executeAddItem();
        }

        if (verifyBid(_currentUserName, itemID, bidPrice, quantityDesired)) {
            placeBid(_currentUserName, itemID, bidPrice, quantityDesired);
        }

        clearScreen();
        System.out.println("    PLACE BID");
        System.out.println();
        System.out.println("Bid placed!");
        System.out.println();
        System.out.print("Press Enter to continue...");
        System.out.println();
        new Scanner(System.in).nextLine();
        executeMemberMenu();
    }

    private static void executeSearchItems() {
        clearScreen();
        System.out.println("    SEARCH ITEMS");
        System.out.println();
        System.out.print("Search: ");
        String argument = readOrQuit();

        displaySearchResults("%" + argument.toLowerCase() + "%");

        executeSearchItems();
    }

    private static void displaySearchResults(String argument) {
        ResultSet searchResults;

        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.search_items(?, ?) }");
            statement.setString(1, argument);
            statement.registerOutParameter(2, OracleTypes.CURSOR);
            statement.execute();

            searchResults = (ResultSet)statement.getObject(2);

            clearScreen();
            System.out.println("    SEARCH ITEMS");
            System.out.println();

            if (!searchResults.isBeforeFirst()) {
                System.out.println("No results returned...");
                System.out.println();
            }

            while (searchResults.next()) {
                double hoursRemaining = 0.00;
                LocalDateTime endTime = searchResults.getTimestamp(10).toLocalDateTime();
                if (endTime.isAfter(LocalDateTime.now())) {
                    hoursRemaining = Duration.between(LocalDateTime.now(), endTime).toMinutes() / 60.00;
                }

                double startPrice = searchResults.getDouble(7);
                double currentPrice = searchResults.getDouble(9);
                if (hoursRemaining == 0.0 && startPrice == currentPrice) {
                    System.out.println("AUCTION CLOSED");
                } else if (hoursRemaining == 0) {
                    System.out.println("ITEM SOLD");
                } else {
                    System.out.println("OPEN AUCTION");
                }
                System.out.println("Item No.: " + searchResults.getInt(1));
                System.out.println("Title: " + searchResults.getString(3));
                System.out.println("Category: " + searchResults.getString(2));
                System.out.println("Description: " + searchResults.getString(4));
                System.out.println("Quantity: " + searchResults.getInt(6));
                System.out.printf("Start price: %.2f\n", startPrice);
                System.out.printf("Bid increment: %.2f\n", searchResults.getDouble(8));
                System.out.printf("Current price: %.2f\n", currentPrice);
                System.out.printf("Time remaining: %.2f hours\n", hoursRemaining);

                System.out.println();
                Thread.sleep(300);
            }

            System.out.print("Press Enter to return to the Member Menu... ");
            new Scanner(System.in).nextLine();
            executeMemberMenu();

        } catch (Exception ex) {
            handleUnhandledError(ex);
        }
    }

    private static boolean verifyUser(String userName) {
        int userNameTaken = 0;

        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.verify_user(?, ?) }");
            statement.setString(1, userName);
            statement.registerOutParameter(2, Types.INTEGER);
            statement.execute();

            userNameTaken = statement.getInt(2);
        } catch (SQLException ex) {
            handleUnhandledError(ex);
        }

        return (userNameTaken == 0);
    }

    private static void registerUser(String userName,
                                     String password,
                                     String name,
                                     String address,
                                     String phoneNumber,
                                     String email) {

        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.register_user(?, ?, ?, ?, ?, ?) }");
            statement.setString(1, userName);
            statement.setString(2, password);
            statement.setString(3, name);
            statement.setString(4, address);
            statement.setString(5, phoneNumber);
            statement.setString(6, email);
            statement.execute();
        } catch (SQLException ex) {
            handleUnhandledError(ex);
        }
    }

    private static boolean verifyBid(String bidderUserName,
                                     int itemID,
                                     double bidPrice,
                                     int quantityDesired) {
        int rtnCode = 0;

        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.verify_bid(?, ?, ?, ?) }");
            statement.setInt(1, itemID);
            statement.setDouble(2, bidPrice);
            statement.setInt(3, quantityDesired);
            statement.registerOutParameter(4, Types.INTEGER);
            statement.execute();

            rtnCode = statement.getInt(4);
        } catch (SQLException ex) {
            handleUnhandledError(ex);
        }

        switch (rtnCode) {
            case 1:
                clearScreen();
                System.out.println("    PLACE BID");
                System.out.println();
                System.out.println("The item doesn't exist. Returning to Member Menu. ");
                System.out.println();
                System.out.print("Press Enter to continue...");
                new Scanner(System.in).nextLine();
                executeMemberMenu();
            case 2:
                clearScreen();
                System.out.println("    PLACE BID");
                System.out.println();
                System.out.println("The item is no longer for auction. Returning to Member Menu. ");
                System.out.println();
                System.out.print("Press Enter to continue...");
                new Scanner(System.in).nextLine();
                executeMemberMenu();
            case 3:
                clearScreen();
                System.out.println("    PLACE BID");
                System.out.println();
                System.out.println("The bid is not high enough. Returning to Member Menu. ");
                System.out.println();
                System.out.print("Press Enter to continue...");
                new Scanner(System.in).nextLine();
                executeMemberMenu();
            case 4:
                clearScreen();
                System.out.println("    PLACE BID");
                System.out.println();
                System.out.println("You have requested a higher quantity than");
                System.out.println("the quantity that remains. Returning to Member Menu. ");
                System.out.println();
                System.out.print("Press Enter to continue...");
                new Scanner(System.in).nextLine();
                executeMemberMenu();
            case 5:
                return true;
            default:
                clearScreen();
                System.out.println("    PLACE BID");
                System.out.println();
                System.out.print("Place bid failed. Returning to Main Menu. ");
                System.out.println();
                System.out.print("Press Enter to continue...");
                new Scanner(System.in).nextLine();
        }

        //failure
        clearScreen();
        System.out.println("    PLACE BID");
        System.out.println();
        System.out.print("Place bid failed. Returning to Main Menu. ");
        System.out.println();
        System.out.print("Press Enter to continue...");
        new Scanner(System.in).nextLine();
        executeMainMenu();

        return false;
    }

    private static void placeBid(String bidderUserName,
                                     int itemID,
                                     double bidPrice,
                                     int quantityDesired) {
        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.place_bid(?, ?, ?, ?) }");
            statement.setString(1, bidderUserName);
            statement.setInt(2, itemID);
            statement.setDouble(3, bidPrice);
            statement.setInt(4, quantityDesired);
            statement.execute();
        } catch (SQLException ex) {
            handleUnhandledError(ex);
        }
    }

    private static boolean verifyLogin(String userName, String password) {
        int loginValid = 0;

        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.verify_login(?, ?, ?) }");
            statement.setString(1, userName);
            statement.setString(2, password);
            statement.registerOutParameter(3, Types.INTEGER);
            statement.execute();

            loginValid = statement.getInt(3);
        } catch (SQLException ex){
            loginValid = 0;
        }

        return (loginValid == 1);
    }

    private static void addItem(String sellerUserName,
                                String title,
                                String category,
                                String description,
                                int quantity,
                                double startPrice,
                                double bidIncrement,
                                double hours) {
        try {
            CallableStatement statement = _connection.prepareCall("{ call auction_db.add_item(?, ?, ?, ?, ?, ?, ?, ?) }");
            statement.setString(1, sellerUserName);
            statement.setString(2, category);
            statement.setString(3, title);
            statement.setString(4, description);
            statement.setInt(5, quantity);
            statement.setDouble(6, startPrice);
            statement.setDouble(7, bidIncrement);
            statement.setDouble(8, hours);
            statement.execute();
        } catch (SQLException ex) {
            handleUnhandledError(ex);
        }
    }

    private static void clearScreen() {
        System.out.print("\033[H\033[2J");
    }

    private static String readOrQuit() {
        String input = new Scanner(System.in).nextLine();
        if  (input.equals("quit")) {
            executeMainMenu();
        }

        return input;
    }

    private static void handleUnhandledError(Exception ex) {
        clearScreen();
        System.out.println();
        System.out.println("Unhandled error: ");
        System.out.println(ex.getMessage());
        System.out.println();
        System.out.println("Exiting...");
        System.console().readLine();
        System.exit(0);
    }
}
