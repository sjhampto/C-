///
/// Your comments here
/// 
/// Steve Hampton Midterm Project CSC 134
/// 
/// This program is used to create and update a seating chart / manifest for a flight.
/// When it starts a menu will display giving the user 8 options to choose from -- 
///     1. Create Manifest
///     2. Create Seating Chart
///     3. Find Passenger
///     4. Show Seat Occupant
///     5. Assign Seat
///     6. Remove Passenger
///     7. Exit Program
///     C. Clear Screen
/// 
/// By selecting option 1 a user will be able to create manifest of the people on the flight.
/// This will be saved to a file in the program folder. Selecting option two will use a multi
/// dimension array to create a properly laid out seating chart.  This chart will be saved to 
/// a file in the program folder.  Option 3 will look up a passenger by their name and then
/// display the passenger info wether they are on the flight or not on the flight.  Option 4
/// will display the occupant of the seat the user tells it to look up.  This will display the
/// results of the search for the user.  Option 5 gives the user the opportunity to assign a 
/// seat to a passenger of their choice.  If the seat is taken passenger will not be added.
/// Option 6 will remove a passenger from the seating chart.  This is done by changing the 
/// array value from the passenger name to the empty seat prompt.  Option 7 will exit the 
/// program.  Finally option C will clear the console and redisplay a fresh menu for the user 
/// to choose from.
/// 
///
/// Program logic assumes only a single letter is used for seat lettering.
/// 
/// Include iostream for standard input and output objects library
#include <iostream>
// Inclue fstream source file to allow input output file stream
#include <fstream>
// Include string source file to use standard string objecs
#include <string>
// Include ctime source to use standard time objects.
#include <ctime>
// Inclue iamanpic source file to provide parametric manipulators
#include <iomanip>
// Include cctype source file to allow for character handling functions
#include <cctype>

// If an object name does not exist in the current namespace this will check 
// if there exists a namespace std where it does exist. It will then use the
// found object.
using namespace std;

/// Declare global constants that will be used through out the entire program.  
/// 
/// The constant NUM_SEAT_LETTERS sets the maximum amount of seat letters the 
/// program can use to 6.  If this wasnt a constant the value could be accidentally
/// changed and if we are using only 6 different letters and the value was changed
/// to anything but 6 and we tried to call it as a reference to the 6 letters we 
/// would create errors.
const int NUM_SEAT_LETTERS = 6;

/// Creates the SEAT_TYPE_INDEX multidimensional array which will be used to 
/// set up the proper seating chart layout and be used to index and locate passengers
/// and seat numbers through out the programs.
const char SEAT_TYPE_INDEX[NUM_SEAT_LETTERS]{ 'A', 'B', 'C', 'D', 'E', 'F' };

/// Create a string constant EMPTY_SEAT. This will be used throughout the entire 
/// program in order to set the value to any seat that is not assigned a person 
/// to the string <EMPTY>.
const string EMPTY_SEAT = "<EMPTY>";
///
/// Both SEAT_INDEX_ROW_POS and SEAT_INDEX_LETTER_POS constants are created and used
/// for the seat2Index function in order to set the index for the array we then use
/// to set the seperated seat value into a number and seat letter. 
const int SEAT_INDEX_ROW_POS = 0;
const int SEAT_INDEX_LETTER_POS = 1;
///

/// Declare constant values to be used in the main body of the program.
/// 
/// Create Constant that can be called each time we want to open the log file
/// that starts with the word log. This allows you to eliminate possible errors
/// in matched spelling.
const string LOG_FILE_NAME = "log";

/// CREATE_MANIFEST_LOG_TEXT is used to output to the log file that the create 
/// manifest option was either started or completed.
const string CREATE_MANIFEST_LOG_TEXT = "Create Manifest";

/// CREATE_SEATING_LOG_TEXT is used to output to the log file that the create
/// seating log option was either started or completed.
const string CREATE_SEATING_LOG_TEXT = "Create Seating Chart";

/// FIND_PASSENGER_LOG_TEXT is used to output to the log file that the find 
/// passenger option was either started or completed.
const string FIND_PASSENGER_LOG_TEXT = "Find Passenger";

/// SHOW_OCCUPANT_LOG_TEXT is used to output to the log file that the show
/// occupant option was either started or completed.
const string SHOW_OCCUPANT_LOG_TEXT = "Show Seat Occupant";

/// ASSIGN_SEAT_LOG_TEXT is used to output to the log file that the assign 
/// seate option was either started or completed.
const string ASSIGN_SEAT_LOG_TEXT = "Assign Seat";

/// REMOVE_PASSENGER_LOG_TEXT is used to output to the log file that the remove 
/// passenger option was either started or completed.
const string REMOVE_PASSENGER_LOG_TEXT = "Remove Passenger";


/// MANIFEST_MESSAGE is used to output to the log file that the manifest was
/// created.  
const string MANIFEST_MESSAGE = "Manifest was created. File name: ";

/// SEATING_CHART_MESSAGE is used to output to the log file that the seating 
/// chart was created.  Will be followed by the files name.
const string SEATING_CHART_MESSAGE = "Seating chart was created. File name: ";

/// FOUND_PASSENGER_MESSAGE constant is used in the main function switch statement in order to
/// output the string is assigned seat. 
const string FOUND_PASSENGER_MESSAGE = " is assigned seat ";

/// NOT_FOUND_PASSENGER_MESSAGE constant is used in the main function swtich statement in order to
/// output the string does not have an assigned seat. 
const string NOT_FOUND_PASSENGER_MESSAGE = " does not have an assigned seat";

/// FOUND_OCCUPANT_MESSAGE constant is used in the main function switch statement,
/// for when the find occupant option is selected, in order to output the string
/// is occupied by.
const string FOUND_OCCUPANT_MESSAGE = " is occupied by ";

/// NOT_FOUND_OCCUPANT_MESSAGE constant is used in the main function switch statement,
/// for when the find occupant option is selected, in order to output the string
/// is empty.
const string NOT_FOUND_OCCUPANT_MESSAGE = " is empty";

/// ASSIGNED_SEAT_TO_PASSENGER_MESSAGE constant is used in the main function switch statement,
/// for when the assign seat option is selected, in order to output the FOUND_PASSENGER_MESSAGE
/// constant which is the string is assigned seat.
const string ASSIGNED_SEAT_TO_PASSENGER_MESSAGE = FOUND_PASSENGER_MESSAGE;

/// NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE constant is used in the main function switch statement,
/// for when the assign seat option is selected, in order to output the string
/// cannont be assigned seat.
const string NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE = " cannot be assigned seat ";

/// REMOVED_PASSENGER_MESSAGE constant is used in the main function switch statement,
/// for when the remove passenger option is selected, in order to output the string
/// was removed from seat.
const string REMOVED_PASSENGER_MESSAGE = " was removed from seat ";

/// NOT_REMOVED_PASSENGER_MESSAGE constant is used in the main function switch statement,
/// for when the remove passenger option is selected, in order to output the string
/// was not removed from seat.
const string NOT_REMOVED_PASSENGER_MESSAGE = " was not removed from seat ";

/// INVALID_CHOICE_ERROR_MESSAGE is used for the main function switch statement's
/// default value in order to display the error message Please enter a valid choic.
const string INVALID_CHOICE_ERROR_MESSAGE = "Please enter a valid choice ";

/// WINDOWS_CLEAR_SCREEN is used in the main function switc statement for when the
/// clear option is chosen.  This constant sets the system function argument to cls
/// which clears the console.
const char* WINDOWS_CLEAR_SCREEN = "cls";

/// SEAT_PROMPT constant is used throughout the main function in order to display the 
/// prompt asking the user to enter a properly formated seat number.
const string SEAT_PROMPT = "Please enter the seat number (format = NNA e.g. 02C): ";
/// FIND_PASSENGER_PROMPT constant is used throughout the main function in order to display the 
/// prompt asking the user to enter the passengers name.
const string FIND_PASSENGER_PROMPT = "Please enter the passenger's name: ";

/// LOG_COMMAND_STARTED constant is used to output to the log file that the
/// specific command was started.
const string LOG_COMMAND_STARTED = " command started";

/// LOG_COMMAND_COMPLETED constant is used to output to the log file that the 
/// specific command was completed.
const string LOG_COMMAND_COMPLETED = " command completed";
///

/// Your comments here
/// SEAT_GRID_DIMENSION constant is used to set the array size of the seatIndex
/// in the seat2Index function.
const int SEAT_GRID_DIMENSION = 2;
///

/// SEAT_STR_ROW_NUM_DIGITS constant is used in multiple seat functions in order
/// to set the length of the seat number to 2.
const int SEAT_STR_ROW_NUM_DIGITS = 2;
///

/// SEAT_STR_ROW_START_POS constant is used to clarify where in the
/// seat string the seat number starts.
const int SEAT_STR_ROW_START_POS = 0;
/// SEAT_STR_LETTER_START_POS constant is used to clarify where in the
/// seat string the seat letter starts.
const int SEAT_STR_LETTER_START_POS = 2;

// Although this constant is defined, the program logic assumes only a single letter is used for seat lettering.
// If this constant is increased, dependent logic would need to be reevaluated.
const int SEAT_STR_LETTER_NUM_CHARS = 1;


/// This constant sets the starting point of the rows of seats.  Because of zero based indexing
/// you would need to subtract one from this constant in order to properly find the index value 
/// your are looking for
const int SEAT_ROWS_START = 1;

/// This constant sets the ending point and max number of the rows of seats.  
/// Because of zero based indexing you do not need to subtract one from this 
/// constant in order to properly find the index value you're are looking for.
const int SEAT_ROWS_END = 15;

/// This constant calculates the total number of rows by subtracting SEAT_ROWS_START from
/// SEAT_ROWS_END and then adding 1.   
const int NUM_SEAT_ROWS = SEAT_ROWS_END - SEAT_ROWS_START + 1;

/// This constant is used to make sure the seat letter is accounted for
/// when setting the value for the seatIndex array and when setting the seat string value
const int LETTER_OFFSET = (int)'A';

/// This constant is used to output in the full and short menus the prompt for the
/// user selection to clear the screen and refresh the full menu.
const string CLEAR_SCREEN_MESSAGE = ". Clear Screen and Refresh Full Menu";

/// This constant is used to output in the full and short menus the prompt for the
/// user selection to exit the program.
const string EXIT_PROGRAM_MESSAGE = ". Exit Program";

/// This constant is used to output in the full and short menus the prompt for the
/// user to enter their choice from the menu.
const string ENTER_CHOICE_MESSAGE = "Enter your choice: ";

/// Declare HEADER_TEXT string constant to be used in the displayHeader function.
const string HEADER_TEXT = "Airline Seating Assignment Maintenance";

/// This constant is used to set the length out how wide the dashed line will print
/// based on the length of the HEADER_TEXT constant.
const int DASH_LENGTH = HEADER_TEXT.length();

/// This constant is used to make sure that when the files are opened or closed the correct
/// file extension is used and there are no potentials for user input error.
const string TEXT_FILE_EXTENSION = ".txt";

/// This constant is used to display the create manifest text for the
/// full menu option to do so.
const string CREATE_MANIFEST_MESSAGE = ". Create Manifest";

/// This constant is used to display the create seating chart text for the full menu option to do so.
const string CREATE_SEATING_CHART_MESSAGE = ". Create Seating Chart";

/// This constant is used to display the find passenger by name text for the full menu option to do so.
const string FIND_PASSENGER_MESSAGE = ". Find Passenger (by name)";

/// This constant is used to display the show occupant message by seat text for the full menu option to do so.
const string SHOW_OCCUPANT_MESSAGE = ". Show Seat Occupant (by seat)";

/// This constant is used to display the assign seat by name text for the full menu option to do so.
const string ASSIGN_SEAT_MESSAGE = ". Assign Seat (by name)";

/// This constant is used to display the remove passenger by name text for the full menu option to do so.
const string REMOVE_PASSENGER_MESSAGE = ". Remove Passenger (by name)";

/// This constant is used to set the choice value for creating a manifest to be used in the display menu and main function.
const char MENU_CREATE_MANIFEST = '1';

/// This constant is used to set the choice value for creating a seating chart to be used in the display menu and main function.
const char MENU_CREATE_SEATING_CHART = '2';

/// This constant is used to set the choice value for finding a passenger to be used in the display menu and main function.
const char MENU_FIND_PASSENGER = '3';

/// This constant is used to set the choice value for showing a seats occupant to be used in the display menu and main function.
const char MENU_SHOW_OCCUPANT = '4';

/// This constant is used to set the choice value for assigning a seat to a person to be used in the display menu and main function.
const char MENU_ASSIGN_SEAT = '5';

/// This constant is used to set the choice value for removing a person from a seat to be used in the display menu and main function.
const char MENU_REMOVE_PASSENGER = '6';

/// This constant is used to set the choice value for exiting the program to be used in the menus and main function.
const char MENU_EXIT_PROGRAM = '7';

/// This constant is used to set the choice value for clearing the console screen to be used in the display menu and main function.
const char MENU_CLEAR_SCREEN = 'C';

/// This constant is used to set the proper whitespacing to the output file for the main header
/// in the create manifest function. 
const int DISPLAY_WIDTH_CM = 15;

/// This constant is used to set the proper whitespacing to the output file for the main header
/// in the create manifest function. 
const int NUM_DISPLAY_COLS_CM = 2;

/// This constant is used to set the prefix for the output file name.  By doing this you elimnate
/// the option for user input error and allows the same file to be called consistantly.
const string MANIFEST_FILENAME_PREFIX = "manifest";

/// This constant is used to output the heading for the passenger column.
const string PASSENGER_HEADING = "Passenger";

/// This constant is used to output the heading for the seat column.
const string SEAT_HEADING = "Seat";

/// This constant is used to set the proper whitespacing to the output file for the main header 
/// in the create seating chart function.
const int DISPLAY_WIDTH_CSC = 10;

/// This constant is used to set the proper whitespacing to the output file for the header columns
/// in the create manifest function. 
const int NUM_DISPLAY_COLS_CSC = 7;

/// This constant is used to set the prefix for the output file name.  By doing this you elimnate
/// the option for user input error and allows the same file to be called consistantly.
const string CHART_FILENAME_PREFIX = "chart";

/// This constant is used to output each rows heading.
const string ROW_HEADING = "row ";

/// This constant is used to add the proper suffix to each row heading.
const string ROW_HEADING_SUFFIX = ":";

/// This constant is used in the index2Seat function to add a 0 to the seat number if the number 
/// is a single digit number.
const char PAD_CHAR = '0';

/// This constant is used to have a uniformly used character to create the dashed lines throughout the programs
/// output and display.  Using this constant removes the possibiltiy of user input error throughout the code.
const char REPEAT_CHAR = '-';

/// This constant is used to create the prefix to the error message if the error message should be displayed.
const string ERROR_MESSAGE_PREFIX = "***";

/// This constant is used to create the output message that the seat length is invalid.
const string INVALID_SEAT_LENGTH_MESSAGE = "Invalid seat length";

/// This constant is used to create the output message that the seat row is invalid and non numeric.
const string INVALID_SEAT_ROW_NON_NUMERIC_MESSAGE = "Invalid seat row -- non-numeric";

/// This constant is used to create the output message that the seat row is invalid less than and out of the proper range.
const string INVALID_SEAT_ROW_OUT_OF_RANGE_LOWER_MESSAGE = "Invalid seat row -- out of range - less than ";

/// This constant is used to create the output message that the seat row is invalid more than and out of the proper range.
const string INVALID_SEAT_ROW_OUT_OF_RANGE_UPPER_MESSAGE = "Invalid seat row -- out of range - greater than ";

/// This constant is used to create the output message that the user input for the seat letter is invalid and not alphabetic.
const string INVALID_SEAT_LETTER_NON_ALPHABETIC = "Invalid seat letter -- non-alphabetic";

/// This constant is used to create the output message that the user input for the seat letter is invalid and must be a 
/// specific way.
const string INVALID_SEAT_LETTER_OUT_OF_RANGE = "Invalid seat letter - must be ";

/// Declare the following function prototypes.  More indepth details regarding each functions functionality can
/// be found at each function definition below.
/// 
/// Declare the displayHeader function.  Returns nothing.
void displayHeader();
/// Declare the displayShortMenu function. Returns nothing.
void displayShortMenu();
/// Declare the displayFullMenu Function. Return nothing.
void displayFullMenu();
/// Declare the getMenuChoice Function. Return nothing.
char getMenuChoice();

/// Declare the createManifest function passing the multidimensional seatGrid string array as the argument.
/// Returns a string.
string createManifest(string seatGrid[][NUM_SEAT_LETTERS]);

/// Declare the createSeatingChart function passing the multidimensional seatGrid string array and the 
/// constant SEAT_TYPE_INDEX char array as the arguments. Returns a string.
string createSeatingChart(string seatGrid[][NUM_SEAT_LETTERS], const char SEAT_TYPE_INDEX[NUM_SEAT_LETTERS]);

/// Declare the findPassenger function passing the multidimensional seatGrid string array and the 
/// passengerName string variable as the arguments. Returns a string.
string findPassenger(string seatGrid[][NUM_SEAT_LETTERS], string passengerName);

/// Declare the showOccupant function passing the multidimensional seatGRid string array and the seat variable.
/// Returns a string.
string showOccupant(string seatGrid[][NUM_SEAT_LETTERS], string seat);

/// Declare the assignSeat function passing the multidimensional seatGrid string array, the seat, 
/// and passengerName variable.  Returns a boolean.
bool assignSeat(string seatGrid[][NUM_SEAT_LETTERS], string seat, string passengerName);

/// Declare the releaseSeat function passing the multidimensional seatGrid string array 
/// and the seat variable. Returns a boolean.
bool releaseSeat(string seatGrid[][NUM_SEAT_LETTERS], string seat);

/// Declare the index2Seat function passing the row and letter int variables. Returns a string.
string index2Seat(int row, int letter);

/// Declare the seat2Index function that points to a int and passes the seat variable as the argument.
int* seat2Index(string seat);

/// Declare the dashLine function that passes the lineLength variable as the argument. Returns nothing.
void dashLine(int lineLength);

/// Declare the overridden dashLine function that passes the lineLength variable and and the 
/// output stream outFile. Returns nothing.
void dashLine(int lineLength, ofstream* outFile);

/// Declare the upperCase function which passes the string string2upper.  Returns a string.
string upperCase(string string2upper);

///  Declare the isSeatValid function which passes the string seat.  Returns a boolean.
bool isSeatValid(string seat);

/// This is the main function of the program.  All the other functions and variables will be 
/// executed and processed in this section in order to achieve the programs main functionability.
/// 
int main()
{
    // Initialize the exitProgram boolean to the value of false.
    bool exitProgram = false;

    // Initialize the choice variable to the value of the MENU_EXIT_PROGRAM constant.
    char choice = MENU_EXIT_PROGRAM;

    // Initializa the strings manifestFileName and seatingChartFileName.
    string manifestFileName;
    string seatingChartFileName;

    // Output logFile object in order to operate on file.
    ofstream logFile;

    // Initialize the string variable seat.
    string seat;

    // Initialize the seatGrid array with the index sizes being NUM_SEAT_ROWS and NUM_SEAT_LETTERS.
    // This will be used to create the main seating chart grid.
    string seatGrid[NUM_SEAT_ROWS][NUM_SEAT_LETTERS];

    // Initialize the string variable passengerName.
    string passengerName;

    /// Open logFile using the concatenation of LOG_FILE_NAME constant plus the time function called inside the
    /// to_string function, to set the current time to a string value, plus the TEXT_FILE_EXTENSION constant.  
    /// By setting and using these constants to write the file name and extension we can assure that user input
    /// errors will not effect save or load errors.
    logFile.open(LOG_FILE_NAME + to_string(time(0)) + TEXT_FILE_EXTENSION);

    /// Use a nested for loop to cycle through the entire seatGrid array and assign it index to the value of 
    /// the EMPTY_SEAT constant.  If you were starting from scratch and not seeding the list with a pre set
    /// text of array data this would be essential to writing the data to the manifest and seating chart files.
    for (int x = 0; x < NUM_SEAT_ROWS; x++) {
        for (int y = 0; y < NUM_SEAT_LETTERS; y++) {
            seatGrid[x][y] = EMPTY_SEAT;
        }
    }

    //// Use this if you want to have seed passengers
    // Fully initilized and seeded seatGrid array thanks to the legend Dr Lynden.
    seatGrid[0][0] = EMPTY_SEAT;
    seatGrid[0][1] = EMPTY_SEAT;
    seatGrid[0][2] = "Avery";
    seatGrid[0][3] = "Daniel";
    seatGrid[0][4] = "Luke";
    seatGrid[0][5] = EMPTY_SEAT;

    seatGrid[1][0] = "Leo";
    seatGrid[1][1] = "Abigail";
    seatGrid[1][2] = "Isabella";
    seatGrid[1][3] = EMPTY_SEAT;
    seatGrid[1][4] = EMPTY_SEAT;
    seatGrid[1][5] = "Chloe";

    seatGrid[2][0] = "Lillian";
    seatGrid[2][1] = "Isaac";
    seatGrid[2][2] = "Ella";
    seatGrid[2][3] = "James";
    seatGrid[2][4] = EMPTY_SEAT;
    seatGrid[2][5] = EMPTY_SEAT;

    seatGrid[3][0] = EMPTY_SEAT;
    seatGrid[3][1] = "Evelyn";
    seatGrid[3][2] = "Aurora";
    seatGrid[3][3] = "Noah";
    seatGrid[3][4] = EMPTY_SEAT;
    seatGrid[3][5] = "Mia";

    seatGrid[4][0] = "Liam";
    seatGrid[4][1] = EMPTY_SEAT;
    seatGrid[4][2] = "Riley";
    seatGrid[4][3] = "Emma";
    seatGrid[4][4] = "Mason";
    seatGrid[4][5] = "Eleanor";

    seatGrid[5][0] = EMPTY_SEAT;
    seatGrid[5][1] = "Logan";
    seatGrid[5][2] = "Jacob";
    seatGrid[5][3] = EMPTY_SEAT;
    seatGrid[5][4] = "John";
    seatGrid[5][5] = EMPTY_SEAT;

    seatGrid[6][0] = EMPTY_SEAT;
    seatGrid[6][1] = EMPTY_SEAT;
    seatGrid[6][2] = EMPTY_SEAT;
    seatGrid[6][3] = "Grace";
    seatGrid[6][4] = EMPTY_SEAT;
    seatGrid[6][5] = "Elijah";

    seatGrid[7][0] = EMPTY_SEAT;
    seatGrid[7][1] = "Madison";
    seatGrid[7][2] = EMPTY_SEAT;
    seatGrid[7][3] = "Charlotte";
    seatGrid[7][4] = EMPTY_SEAT;
    seatGrid[7][5] = "Zoey";

    seatGrid[8][0] = "Ava";
    seatGrid[8][1] = "Nora";
    seatGrid[8][2] = "Harper";
    seatGrid[8][3] = "Samuel";
    seatGrid[8][4] = EMPTY_SEAT;
    seatGrid[8][5] = "Amelia";

    seatGrid[9][0] = EMPTY_SEAT;
    seatGrid[9][1] = "Michael";
    seatGrid[9][2] = EMPTY_SEAT;
    seatGrid[9][3] = "Aiden";
    seatGrid[9][4] = "Hannah";
    seatGrid[9][5] = "Joseph";

    seatGrid[10][0] = "Oliver";
    seatGrid[10][1] = "Zoe";
    seatGrid[10][2] = EMPTY_SEAT;
    seatGrid[10][3] = EMPTY_SEAT;
    seatGrid[10][4] = EMPTY_SEAT;
    seatGrid[10][5] = "Jack";

    seatGrid[11][0] = "Sofia";
    seatGrid[11][1] = "Lucas";
    seatGrid[11][2] = "Penelope";
    seatGrid[11][3] = "Carter";
    seatGrid[11][4] = "Layla";
    seatGrid[11][5] = EMPTY_SEAT;

    seatGrid[12][0] = EMPTY_SEAT;
    seatGrid[12][1] = EMPTY_SEAT;
    seatGrid[12][2] = "Henry";
    seatGrid[12][3] = "Alexander";
    seatGrid[12][4] = "Mila";
    seatGrid[12][5] = EMPTY_SEAT;

    seatGrid[13][0] = "Matthew";
    seatGrid[13][1] = EMPTY_SEAT;
    seatGrid[13][2] = "Violet";
    seatGrid[13][3] = "David";
    seatGrid[13][4] = EMPTY_SEAT;
    seatGrid[13][5] = "Elizabeth";

    seatGrid[14][0] = "Sophia";
    seatGrid[14][1] = "Luna";
    seatGrid[14][2] = "Benjamin";
    seatGrid[14][3] = "Ethan";
    seatGrid[14][4] = "Olivia";
    seatGrid[14][5] = EMPTY_SEAT;
    ////
    /// Call the displayFullMenu function in order to display the menu for the user 
    /// to select from.
    displayFullMenu();

    /// Use a do while loop to execute specific code while the users choice is not the option to close
    /// the program.
    do {
        // Set choice to the return value from calling the toupper function on the getMenuChoice function.
        choice = toupper(getMenuChoice());

        // Use a switch statement to decide what code to run depending on what the users input choice was.
        switch (choice) {

            /// If the value of choice is equal to the MENU_CREATE_MANIFEST constant execute the following
            /// code in order to create a file containing the flight manifest information.
        case MENU_CREATE_MANIFEST:
            // Output to the log file the CREATE_MANIFEST_LOG_TEXT and LOG_COMMAND_STARTED constants.
            logFile << CREATE_MANIFEST_LOG_TEXT << LOG_COMMAND_STARTED << endl;

            // Update the manifestFileName variable to the returned value from calling the createManifest
            // function that passes the seatGrid array as its argument.
            manifestFileName = createManifest(seatGrid);

            /// Output to logFIle the MANIFEST_MESSAGE constant and the manifestFileName variable.
            logFile << MANIFEST_MESSAGE << manifestFileName << endl;

            /// Call the dashLine function by passing the length of MANIFEST_MESSAGE plus manifestFileName
            /// in order to create a dashed line that spands the length of the file.
            dashLine((MANIFEST_MESSAGE + manifestFileName).length());
            // Display the MANIFEST_MESSAGE constant and the manifestFileName variable.
            cout << MANIFEST_MESSAGE << manifestFileName << endl;
            /// Call the dashLine function by passing the length of MANIFEST_MESSAGE plus manifestFileName
            /// in order to create a dashed line that spands the length of the file.
            dashLine((MANIFEST_MESSAGE + manifestFileName).length());

            // Print a blank line in order to create proper white space.
            cout << endl;

            /// Output to logFile the CREATE_MANIFEST_LOG_TEXT and LOG_COMMAND_COMPlETED constants to show
            /// in the logFile file that the manifest was greated.  Use endl to create the proper white
            /// space after the output.
            logFile << CREATE_MANIFEST_LOG_TEXT << LOG_COMMAND_COMPLETED << endl << endl;

            // Call the displayShortMenu function in order to promp the user to make their next choice 
            displayShortMenu();
            // break once all the necessary code is run.
            break;

            /// If the choice variable is equal to the MENU_CREATE_SEATING_CHART constant then execute the 
            /// following code in order to create a seating chart file.
        case MENU_CREATE_SEATING_CHART:
            // Output to the log file the CREATE_SEATING_LOG_TEXT and LOG_COMMAND_STARTED constants.
            logFile << CREATE_SEATING_LOG_TEXT << LOG_COMMAND_STARTED << endl;

            // Update the seatingCharFileName variable to the returned value from calling the createSeatingChart
            // function that passes the seatGrid array and SEAT_TYPE_INDEX constant as its arguments.
            seatingChartFileName = createSeatingChart(seatGrid, SEAT_TYPE_INDEX);

            // Output to the log file the SEATING_CHART_MESSAGE constant and seatingChartFileName variable.
            logFile << SEATING_CHART_MESSAGE << seatingChartFileName << endl;

            /// Call the dashLine function by passing the length of SEATING_CHART_MESSAGE plus seatingChartFileName
            /// in order to create a dashed line that spands the length of the file.
            dashLine((SEATING_CHART_MESSAGE + seatingChartFileName).length());
            /// Display to the console the SEATING_CHART_MESSAGE constant followed by the seatingChartFileName variable.
            cout << SEATING_CHART_MESSAGE << seatingChartFileName << endl;
            /// Call the dashLine function by passing the length of SEATING_CHART_MESSAGE plus seatingChartFileName
            /// in order to create a dashed line that spands the length of the file.
            dashLine((SEATING_CHART_MESSAGE + seatingChartFileName).length());

            /// Output to the log file the CREATE_SEATING_LOG_TEXT and LOG_COMMAND_COMPLETED constants.  
            /// Use endl to creat the proper whitespace after.  This will write a line in the log file that
            /// states that the function was completed.
            logFile << CREATE_SEATING_LOG_TEXT << LOG_COMMAND_COMPLETED << endl << endl;

            /// Print a blank line to the console.
            cout << endl;

            // Call the displayShortMenu function in order to promp the user to make their next choice 
            displayShortMenu();
            // break once all the necessary code is run.
            break;

            /// If choice equals the MENU_FIND_PASSENGER constant then execute the following code
            /// in order to look up and display a passenger on the flight by their name.
        case MENU_FIND_PASSENGER:
            // Output to the log file the FIND_PASSENGER_LOG_TEXT and LOG_COMMAND_STARTED constants.
            logFile << FIND_PASSENGER_LOG_TEXT << LOG_COMMAND_STARTED << endl;

            // Display the FIND_PASSENGER_PROMPT constant.
            cout << FIND_PASSENGER_PROMPT;

            // Extract the cin user input into the passengerName variable.
            getline(cin, passengerName);

            // Update the seat value by calling the findPassenger function passing the seatGrid array
            // and the passengerName variable.
            seat = findPassenger(seatGrid, passengerName);

            // Create proper whitespace.
            cout << endl;

            /// If the value of seat is not equal to the EMPTY_SEAT constant execute the following code.
            if (seat != EMPTY_SEAT) {

                // Output to the log file passengerName, FOUND_PASSENGER_MESSAGE, constant and seat.
                logFile << passengerName << FOUND_PASSENGER_MESSAGE << seat << endl;

                /// Call the dashLine function by passing the length of passengerName + FOUND_PASSENGER_MESSAGE + seat
                /// in order to create a dashed line that spands the length of the file.
                dashLine((passengerName + FOUND_PASSENGER_MESSAGE + seat).length());

                /// Display passengerName and FOUND_PASSENGER_MESSAGE
                cout << passengerName << FOUND_PASSENGER_MESSAGE << seat << endl;

                /// Call the dashLine function by passing the length of passengerName + FOUND_PASSENGER_MESSAGE + seat
                /// in order to create a dashed line that spands the length of the file.
                dashLine((passengerName + FOUND_PASSENGER_MESSAGE + seat).length());
            }
            else {
                // Output to the log file passengerName, NOT_FOUND_PASSENGER_MESSAGE constant.
                logFile << passengerName << NOT_FOUND_PASSENGER_MESSAGE << endl;

                /// Call the dashLine function by passing the length of passengerName + NOT_FOUND_PASSENGER_MESSAGE
                /// in order to create a dashed line that spands the length of the file.
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());

                /// Display passengerName and NOT_FOUND_PASSENGER_MESSAGE
                cout << passengerName << NOT_FOUND_PASSENGER_MESSAGE << endl;

                /// Call the dashLine function by passing the length of passengerName + NOT_FOUND_PASSENGER_MESSAGE
                /// in order to create a dashed line that spands the length of the file.
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());
            }

            /// Output to the log file the FIND_PASSENGER_LOG_TEXT and LOG_COMMAND_COMPLETED constants.  
            /// Use endl to creat the proper whitespace after.  This will write a line in the log file that
            /// states that the function was completed.
            logFile << FIND_PASSENGER_LOG_TEXT << LOG_COMMAND_COMPLETED << endl << endl;

            /// Print a blank line to the console.
            cout << endl;

            // Call the displayShortMenu function in order to promp the user to make their next choice 
            displayShortMenu();
            // break once all the necessary code is run.
            break;

            /// If choice is equal to MENU_SHOW_OCCUPANT execute the following code in order to 
            /// show a seats occupant by searching the seat number.
        case MENU_SHOW_OCCUPANT:
            // Output to the log file the SHOW_OCCUPANT_LOG_TEXT and LOG_COMMAND_STARTED constants.
            logFile << SHOW_OCCUPANT_LOG_TEXT << LOG_COMMAND_STARTED << endl;

            /// Use a do while loop to prompt a user to ender the seat they would like to check.
            /// By using a do while loop we can assure that the program will only continue if
            /// the user enters a valid seat number.  If an invalid number is entered the loop will 
            /// just endlessly repeat.
            do {
                // Display SEAT_PROMPT constant.
                cout << SEAT_PROMPT;
                // Extract the cin user input into the seat variable.
                getline(cin, seat);
            } while (!isSeatValid(seat));

            // Update the value of passengerName by calling the showOccupant function passing 
            // the seatGrid array and seat variable as the arguments.
            passengerName = showOccupant(seatGrid, seat);

            // Create whitespace.
            cout << endl;

            // Execute the following code if the passengerName variable does not equal EMPTY_SEAT
            if (passengerName != EMPTY_SEAT) {
                // Output to the log file seat, FOUND_OCCUPANT_MESSAGE, and passengerName.
                logFile << seat << FOUND_OCCUPANT_MESSAGE << passengerName << endl;

                /// Call the dashLine function by passing the length of seat, FOUND_OCCUPANT_MESSAGE, and passengerName
                /// in order to create a dashed line that spands the length of the file.
                dashLine((seat + FOUND_OCCUPANT_MESSAGE + passengerName).length());

                // Display seat, FOUND_OCCUPANT_MESSAGE, and passengerName.
                cout << seat << FOUND_OCCUPANT_MESSAGE << passengerName << endl;

                /// Call the dashLine function by passing the length of seat, FOUND_OCCUPANT_MESSAGE, and passengerName
                /// in order to create a dashed line that spands the length of the file.
                dashLine((seat + FOUND_OCCUPANT_MESSAGE + passengerName).length());
            }
            else {

                // Output to the log file seat and NOT_FOUND_OCCUPANT_MESSAGE.
                logFile << seat << NOT_FOUND_OCCUPANT_MESSAGE << endl;

                /// Call the dashLine function by passing the length of seat and NOT_FOUND_OCCUPANT_MESSAGE
                /// in order to create a dashed line that spands the length of the file.
                dashLine((seat + NOT_FOUND_OCCUPANT_MESSAGE).length());

                // Display seat and NOT_FOUND_OCCUPANT_MESSAGE.
                cout << seat << NOT_FOUND_OCCUPANT_MESSAGE << endl;

                /// Call the dashLine function by passing the length of seat and NOT_FOUND_OCCUPANT_MESSAGE
                /// in order to create a dashed line that spands the length of the file.
                dashLine((seat + NOT_FOUND_OCCUPANT_MESSAGE).length());
            }


            /// Output to the log file the SHOW_OCCUPANT_LOG_TEXT and LOG_COMMAND_COMPLETED constants.  
            /// Use endl to creat the proper whitespace after.  This will write a line in the log file that
            /// states that the function was completed.
            logFile << SHOW_OCCUPANT_LOG_TEXT << LOG_COMMAND_COMPLETED << endl << endl;

            /// Print a blank line to the console.
            cout << endl;

            // Call the displayShortMenu function in order to promp the user to make their next choice 
            displayShortMenu();
            // break once all the necessary code is run.
            break;

            /// If choice is equal to the MENU_ASSIGN_SEAT constant execute the followin code in order
            /// to assigne an empty seat to a new passenger.
        case MENU_ASSIGN_SEAT:
            // Output to the log file the ASSIGN_SEAT_LOG_TEXT and LOG_COMMAND_STARTED constants.
            logFile << ASSIGN_SEAT_LOG_TEXT << LOG_COMMAND_STARTED << endl;

            /// Use a do while loop to prompt a user to ender the seat they would like to check.
            /// By using a do while loop we can assure that the program will only continue if
            /// the user enters a valid seat number.  If an invalid number is entered the loop will 
            /// just endlessly repeat.
            do {
                // Display SEAT_PROMPT constant.
                cout << SEAT_PROMPT;
                // Extract the cin user input into the seat variable.
                getline(cin, seat);
            } while (!isSeatValid(seat));

            // Display the FIND_PASSENGER_PROMPT constant. This will prompt the user to enter a 
            // passenger name.
            cout << FIND_PASSENGER_PROMPT;
            // Extract the cin user input into the passengerName variable.
            getline(cin, passengerName);

            // Create whitespace
            cout << endl;

            // If the function assignSeat with seatGrid, seat, and passengerName passed as the 
            // arguments returns true, the, execute the following code.
            if (assignSeat(seatGrid, seat, passengerName)) {
                // Output to the log file passengerName, ASSIGNED_SEAT_TO_PASSENGER_MESSAGE, and seat.
                logFile << passengerName << ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << seat << endl;

                /// Call the dashLine function by passing the length of  passengerName, 
                /// ASSIGNED_SEAT_TO_PASSENGER_MESSAGE, and seat in order to create a dashed 
                /// line that spands the length of the file.
                dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + seat).length());

                // Display seat and ASSIGNED_SEAT_TO_PASSENGER_MESSAGE.
                cout << passengerName << ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << seat << endl;

                /// Call the dashLine function by passing the length of  passengerName, 
                /// ASSIGNED_SEAT_TO_PASSENGER_MESSAGE, and seat in order to create a dashed 
                /// line that spands the length of the file.
                dashLine((passengerName + ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + seat).length());
            }
            else {
                // Output to the log file seat, FOUND_OCCUPANT_MESSAGE, and passengerName.
                logFile << passengerName << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << seat << endl;

                /// Call the dashLine function by passing the length of  passengerName, 
                /// NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE, and seat in order to create a dashed 
                /// line that spands the length of the file.
                dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + seat).length());

                // Display passengerName, NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE, and seat.
                cout << passengerName << NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE << seat << endl;

                /// Call the dashLine function by passing the length of  passengerName, 
                /// NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE, and seat in order to create a dashed 
                /// line that spands the length of the file.
                dashLine((passengerName + NOT_ASSIGNED_SEAT_TO_PASSENGER_MESSAGE + seat).length());
            }

            /// Output to the log file the ASSIGN_SEAT_LOG_TEXT and LOG_COMMAND_COMPLETED constants.  
            /// Use endl to creat the proper whitespace after.  This will write a line in the log file that
            /// states that the function was completed.
            logFile << ASSIGN_SEAT_LOG_TEXT << LOG_COMMAND_COMPLETED << endl << endl;

            /// Print a blank line to the console.
            cout << endl;

            // Call the displayShortMenu function in order to promp the user to make their next choice 
            displayShortMenu();
            // break once all the necessary code is run.
            break;

            /// If choice is equal to the constant MENU_REMOVE_PASSENGER than execute the following code
            /// in order to remove a passenger from the flight list.
        case MENU_REMOVE_PASSENGER:
            // Output to the log file the REMOVE_PASSENGER_LOG_TEXT and LOG_COMMAND_STARTED constants.
            logFile << REMOVE_PASSENGER_LOG_TEXT << LOG_COMMAND_STARTED << endl;

            // Display the FIND_PASSENGER_PROMPT constant.  This will print a prompt for the user
            // to enter the passenger name they wish to remove.
            cout << FIND_PASSENGER_PROMPT;
            // Extract the cin user input into the passengerName variable.
            getline(cin, passengerName);

            // Update the seat value by calling the findPassenger function passing the seatGrid array
            // and the passengerName variable.
            seat = findPassenger(seatGrid, passengerName);

            // If the seat variable does not equal the EMPTY_SEAT constant then execute the following code.
            if (seat != EMPTY_SEAT) {

                // If the releaseSeat function with seatGrid and seat passed as the argumetns returns
                // true then execute the following lines of code.
                if (releaseSeat(seatGrid, seat)) {
                    // Output to the log file passengerName, REMOVED_PASSENGER_MESSAGE, and seat.
                    logFile << passengerName << REMOVED_PASSENGER_MESSAGE << seat << endl;

                    /// Call the dashLine function by passing the length of  passengerName, 
                    /// REMOVED_PASSENGER_MESSAGE, and seat in order to create a dashed 
                    /// line that spands the length of the file.
                    dashLine((passengerName + REMOVED_PASSENGER_MESSAGE + seat).length());

                    // Display passengerName, REMOVED_PASSENGER_MESSAGE, and seat.
                    cout << passengerName << REMOVED_PASSENGER_MESSAGE << seat << endl;

                    /// Call the dashLine function by passing the length of  passengerName, 
                    /// REMOVED_PASSENGER_MESSAGE, and seat in order to create a dashed 
                    /// line that spands the length of the file.
                    dashLine((passengerName + REMOVED_PASSENGER_MESSAGE + seat).length());
                }
                else {
                    // Output to the log file passengerName, NOT_REMOVED_PASSENGER_MESSAGE, and seat.
                    logFile << passengerName << NOT_REMOVED_PASSENGER_MESSAGE << seat;

                    /// Call the dashLine function by passing the length of  passengerName, 
                    /// NOT_REMOVED_PASSENGER_MESSAGE, and seat in order to create a dashed 
                    /// line that spands the length of the file.
                    dashLine((passengerName + NOT_REMOVED_PASSENGER_MESSAGE).length());

                    // Display passengerName, NOT_REMOVED_PASSENGER_MESSAGE, and seat.
                    cout << passengerName << NOT_REMOVED_PASSENGER_MESSAGE << seat << endl;

                    /// Call the dashLine function by passing the length of  passengerName, 
                    /// NOT_REMOVED_PASSENGER_MESSAGE, and seat in order to create a dashed 
                    /// line that spands the length of the file.
                    dashLine((passengerName + NOT_REMOVED_PASSENGER_MESSAGE).length());
                }
            }
            else {
                // Output to the log file passengerName, NOT_REMOVED_PASSENGER_MESSAGE, and seat.
                logFile << passengerName << NOT_FOUND_PASSENGER_MESSAGE << endl;

                /// Call the dashLine function by passing the length of  passengerName
                /// and NOT_FOUND_PASSENGER_MESSAGE in order to create a dashed 
                /// line that spands the length of the file.
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());

                // Display passengerName and NOT_REMOVED_PASSENGER_MESSAGE.
                cout << passengerName << NOT_FOUND_PASSENGER_MESSAGE << endl;

                /// Call the dashLine function by passing the length of  passengerName
                /// and NOT_FOUND_PASSENGER_MESSAGE in order to create a dashed 
                /// line that spands the length of the file.
                dashLine((passengerName + NOT_FOUND_PASSENGER_MESSAGE).length());
            }

            /// Output to the log file the REMOVE_PASSENGER_LOG_TEXT and LOG_COMMAND_COMPLETED constants.  
            /// Use endl to creat the proper whitespace after.  This will write a line in the log file that
            /// states that the function was completed.
            logFile << REMOVE_PASSENGER_LOG_TEXT << LOG_COMMAND_COMPLETED << endl << endl;

            /// Print a blank line to the console.
            cout << endl;

            // Call the displayShortMenu function in order to promp the user to make their next choice 
            displayShortMenu();
            // break once all the necessary code is run.
            break;

            /// If choice equals the MENU_EXIT_PROGRAM constant then run the following code in order to
            /// exit the program sucessfully.
        case MENU_EXIT_PROGRAM:
            // Update the value of exitProgram to true.
            exitProgram = true;

            // break once all the necessary code is run.
            break;


            /// If choice equals MENU_CLEAR_SCREEN constant then run the following code in order to 
            /// clear the console and then display a fresh menu to choose from.
        case MENU_CLEAR_SCREEN:
            // Call the system function by passing the WINDOWS_CLEAR_SCREEN constant as the argument.
            // This will clear the console screen.
            system(WINDOWS_CLEAR_SCREEN);

            // Once the console is clear call the displayFullMenu function to display the menu for the 
            // user to make a choice from.
            displayFullMenu();

            // break once all the necessary code is run.
            break;

            /// If choice doesnt match any of the above cases than print to the console the INVALID_CHOICE_ERROR_MESSAGE
            /// constant to inform the user of the invalid choice.
        default:
            cout << INVALID_CHOICE_ERROR_MESSAGE;

        }

    } while (!exitProgram);  // While exitProgram is not true do the aboce code.

    // Call the close function to logFile to close the opened file.
    logFile.close();
}

/// Create the displayHeader function to be called in order to create
/// the main header of the display menu. Return nothing.
void displayHeader()
{
    // Print the HEADER_TEXT constant value and end the line.
    cout << HEADER_TEXT << endl;

    // Call the dashLine() function passing DASH_LENGTH as the argument.
    dashLine(DASH_LENGTH);
}

/// Create the displayShortMenu function to be called in order to display 
/// the secondary menu after the full menu has been displayed and a choice 
/// has been made. Return nothing.
void displayShortMenu()
{
    // Call the displayHeader function.
    displayHeader();

    // Print the MENU_CLEAR_SCREEN and CLEAR_SCREEN_MESSAGE constants
    cout << MENU_CLEAR_SCREEN << CLEAR_SCREEN_MESSAGE << endl;
    // Print the  MENU_EXIT_PROGRAM and EXIT_PROGRAM_MESSAGE constants
    cout << MENU_EXIT_PROGRAM << EXIT_PROGRAM_MESSAGE << endl;
    // Print a blank line 
    cout << endl;
    // Print the ENTER_CHOICE_MESSAGE constant.
    cout << ENTER_CHOICE_MESSAGE;
}

/// Create the displayFullMenu function to be called in order to display
/// the full initial menu. User will used this menu to make initial selection
/// Call proper functions where needed.  Return nothing.
void displayFullMenu()
{
    // Call the displayHeader function
    displayHeader();

    // After the displayHeader function is called print all of the appropriate 
    // constants to create the section in the actual menu item section from the
    // main menu which will allow theuser to make their selection.
    cout << MENU_CREATE_MANIFEST << CREATE_MANIFEST_MESSAGE << endl;
    cout << MENU_CREATE_SEATING_CHART << CREATE_SEATING_CHART_MESSAGE << endl;
    cout << MENU_FIND_PASSENGER << FIND_PASSENGER_MESSAGE << endl;
    cout << MENU_SHOW_OCCUPANT << SHOW_OCCUPANT_MESSAGE << endl;
    cout << MENU_ASSIGN_SEAT << ASSIGN_SEAT_MESSAGE << endl;
    cout << MENU_REMOVE_PASSENGER << REMOVE_PASSENGER_MESSAGE << endl;
    // Call the dashLine function passing the DASH_LENTH constant as the argument
    dashLine(DASH_LENGTH);
    cout << MENU_EXIT_PROGRAM << EXIT_PROGRAM_MESSAGE << endl;
    // Call the dashLine function passing the DASH_LENTH constant as the argument
    dashLine(DASH_LENGTH);
    // Print a blank line 
    cout << endl;
    cout << MENU_CLEAR_SCREEN << CLEAR_SCREEN_MESSAGE << endl;
    // Print a blank line 
    cout << endl;
    cout << ENTER_CHOICE_MESSAGE;
}

/// Create the getMenuChoice function to be called in order to get the
/// users input for their menu choice.
char getMenuChoice()
{
    // Initialize the char variable choice to the value of the constant MENU_EXIT_PROGRAM.
    char choice = MENU_EXIT_PROGRAM;

    //  cin user input and store the input in the choice variable.
    cin >> choice;
    // Ignore the line break after user input is recieved.
    cin.ignore();

    // Print two blank lines.
    cout << endl << endl;

    // Retrun the value of the variable choice.
    return choice;
}

/// Create the createManifest function passing the two demensional seatGrid array
/// which passes the NUM_SEAT_LETTERS constant as the arrays column value. Return
/// a string value.
string createManifest(string seatGrid[][NUM_SEAT_LETTERS])
{
    // Output manifestFile object in order to operate on files.
    ofstream manifestFile;

    // Initialize the manifestFileName by concatenating MANIFEST_FILENAME_PREFIX, the current time 
    // using the to_string method and time function, and TEXT_FILE_EXTENSION.  
    string manifestFileName = MANIFEST_FILENAME_PREFIX + to_string(time(0)) + TEXT_FILE_EXTENSION;

    // Open manifestFile by passing the manifestFileName variable into the open function.  
    manifestFile.open(manifestFileName);

    // Adjust the output data to be justified to the left.
    manifestFile << left;
    // Set the width and output the PASSENGER_HEADING and SEAT_HEADING constants in order to create the main
    // heading for the output file.
    manifestFile << setw(DISPLAY_WIDTH_CM) << PASSENGER_HEADING << setw(DISPLAY_WIDTH_CM) << SEAT_HEADING << endl;

    // Call the dashLine function passing DISPLAY_WIDTH_CM multiplied by NUM_DISPLAY_COLS_CM as well as a
    // reference to the manifestFile object.
    dashLine(DISPLAY_WIDTH_CM * NUM_DISPLAY_COLS_CM, &manifestFile);

    // Create a blank line in the output.
    manifestFile << endl;

    // Create a nested for loop to cycle through each row and letter in the array in order to output the 
    // manifest list.
    for (int row = 0; row < NUM_SEAT_ROWS; row++)
        for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++)
            if (seatGrid[row][letter] != EMPTY_SEAT)
                // If the value of seatGrid at the current row and letter value is not equal to the EMPTY_SEAT constant, output
                // that seatGrid value and then the returned value from the index2Seat function with row and letter passed as the 
                // arguments. End the line.
                manifestFile << setw(DISPLAY_WIDTH_CM) << seatGrid[row][letter] << setw(DISPLAY_WIDTH_CM) << index2Seat(row, letter) << endl;

    // Close the output file.
    manifestFile.close();

    // Return the value of manifestFileName
    return manifestFileName;
}

/// This function will be used in order to create a file
/// in which contains a detailed seating chart. 
/// 
/// Create the createSeatingChart function passing the the two demensional seatGrid array
/// which passes the NUM_SEAT_LETTERS constant as the arrays column value. Also passes the 
/// char array constant SEAT_TYPE_INDEX. Returns a string value chartFileName.
string createSeatingChart(string seatGrid[][NUM_SEAT_LETTERS], const char SEAT_TYPE_INDEX[NUM_SEAT_LETTERS])
{
    // Output seatingCharFile object in order to operate on files.
    ofstream seatingChartFile;

    // Initialize the chartFileName by concatenating CHART_FILENAME_PREFIX, the current time 
    // using the to_string function and time function, and TEXT_FILE_EXTENSION.
    string chartFileName = CHART_FILENAME_PREFIX + to_string(time(0)) + TEXT_FILE_EXTENSION;

    // Open seatingChartFile by passing the chartFileName variable into the open function.  
    seatingChartFile.open(chartFileName);

    // Adjust the output data to be justified to the left.
    seatingChartFile << left;
    // Create the whitespace needed before the seat letters are displayed.
    seatingChartFile << setw(DISPLAY_WIDTH_CSC) << " ";

    // For loop to cycle through the SEAT_TYPE_INDEX in order to display each seat letter.  Use setw() 
    // to create even space between each letter.
    for (int x = 0; x < NUM_SEAT_LETTERS; x++)
        seatingChartFile << setw(DISPLAY_WIDTH_CSC) << SEAT_TYPE_INDEX[x];
    // Create a blank line.
    seatingChartFile << endl;

    // Call the dashLine function passing DISPLAY_WIDTH_CM multiplied by NUM_DISPLAY_COLS_CM as well as a
    // reference to the seatingChartFile object.  This will created a dashed line that crosses the entire file.
    dashLine(DISPLAY_WIDTH_CSC * NUM_DISPLAY_COLS_CSC, &seatingChartFile);

    // Create a blank line.
    seatingChartFile << endl;

    // Use a nested for loop to display each row with the proper column data from the seatGrid array.
    for (int x = 0; x < NUM_SEAT_ROWS; x++)
    {
        // Add one because of zero-based indexing.
        // Output to seatingChartFile concatenate the ROW_HEADING constant, with the to_string function,
        // and with the ROW_HEADING_SUFFIX constant.  This will display each row header properly in the output file.
        seatingChartFile << setw(DISPLAY_WIDTH_CSC) << ROW_HEADING + to_string(x + 1) + ROW_HEADING_SUFFIX;
        // Nested for loop.
        for (int y = 0; y < NUM_SEAT_LETTERS; y++)
            // Using the nested for loop output the seatGrid value at the current value for x and y.  X being the row 
            // letter and y being the seat letter.  
            seatingChartFile << setw(DISPLAY_WIDTH_CSC) << seatGrid[x][y];
        // Create a blank line.
        seatingChartFile << endl;
    }

    // Close the output file.
    seatingChartFile.close();

    // Return the value of chartFileName.
    return chartFileName;
}

/// Accepts the Seat Grid and Passenger Name
/// Returns the seat the passenger occupies or EMPTY_SEAT
/// 
/// If you find the passenger in seatGrid, use index2Seat to convert the row/column location in seatGrid to a seat string
/// 
/// To put this into perspective, this function is about 15 lines of code.
/// 
/// Create findPassenger function passing the seatGrid array and passengerName string as arguments.  This function will use 
/// nested loops in order to determin wether or not passengerName is a value in the seatGrid array and if it is will return
/// the appropriate seat value by calling the index2Seat function.
/// 
string findPassenger(string seatGrid[][NUM_SEAT_LETTERS], string passengerName)
{
    // Initialize the seat variable to the EMPTY_SEAT constant so if passengerName is not found
    // it will return EMPTY_SEAT.
    string passSeat = EMPTY_SEAT;



    // Create a nested for loop to cycle through each row and letter in the array in order to output the 
    // manifest list.
    for (int row = 0; row < NUM_SEAT_ROWS; row++) {
        for (int letter = 0; letter < NUM_SEAT_LETTERS; letter++) {
            // If seatGrid[][] is not equal to the EMPTY_SEAT constant continue.
            if (seatGrid[row][letter] != EMPTY_SEAT) {
                /// Call both passengerName and the seatGrid value to the upperCase function to insure
                /// that if their chars match it shows equal.  
                if (upperCase(passengerName) == upperCase(seatGrid[row][letter])) {
                    // If passengerName and the seatGrid value at the current row and letter are equal
                    // seat equals the returned value from the index2Seat function at the current row and letter.
                    passSeat = index2Seat(row, letter);
                }
            }
        }
    }


    // Return the value of seat.
    return passSeat;

}

/// Accepts the Seat Grid and a seat string
/// Returns the name of the passenger that occupies this seat or EMPTY_SEAT
///
/// Pass the seat string to seat2Index (use upperCase function on the seat string) to convert
///     a seat string to int* seatIndex (which is a pointer to an array of int)
/// Use the values in seatIndex (again, the pointer to an array of int)
///     to index into seatGrid to get the passenger name (or EMPTY_SEAT) in that seat.
/// 
/// To put this into perspective, this function is about 5 lines of code.
/// 
/// Create showOccupant function that accepts seatGrid and seat as arguments to be used to look up
/// a passenger based on their seat number.  Returns string variable occupant.
string showOccupant(string seatGrid[][NUM_SEAT_LETTERS], string seat)
{
    // Create a reference int array seatIndex by calling the seat2Index function with seat passed as the
    // argument.  This will give you the correct array values to index the seatGrid array to obtain the
    // occupant information.
    int* seatIndex = seat2Index(upperCase(seat));

    // Index the seatGrid array using the seatIndex array values.
    string occupant = seatGrid[seatIndex[0]][seatIndex[1]];

    // Return occupant string.  
    return occupant;
}

/// Accepts the Seat Grid, a seat string, and a passenger name
/// Returns true or false
///     true = the seat was successfully assigned to the passenger
///     false = the seat was not successfully assigned to the passenger (because someone is already sitting there)
///
/// Pass the seat string to seat2Index (use upperCase function on the seat string) to convert
///     a seat string to int* seatIndex (which is a pointer to an array of int)
/// Use the values in seatIndex (again, the pointer to an array of int)
///     to index into seatGrid to see if there is a passenger in that seat.
/// If the occupant is EMPTY_SEAT, then assign the seat to the new passenger.
/// 
/// To put this into perspective, this function is about 4 additional lines of code.
/// 
/// Create the assignSeat function which accepts seatGrid, seat, and passengerName as arguments.  This function 
/// is used to determin if a seat is currently occupied.  If the seat is not occupied return true and add the passengerName
/// value to the seatGrid array.  If the seat is occupied return false.  
bool assignSeat(string seatGrid[][NUM_SEAT_LETTERS], string seat, string passengerName)
{

    // Use this variable and the code below to release the dynamically allocated memory
    int* seatIndex = nullptr;


    // Create a reference int array seatIndex by calling the seat2Index function with seat passed as the
    // argument.  This will give you the correct array values to index the seatGrid array to obtain the
    // occupant information.
    seatIndex = seat2Index(upperCase(seat));

    // Index the seatGrid array using the seatIndex array values to initialize the occupant string.
    string occupant = seatGrid[seatIndex[0]][seatIndex[1]];


    if (occupant == EMPTY_SEAT) {
        // If occupant is equal to EMPTY_SEAT then add the value of passengerName to the seatGrid array
        // at the index values of seatIndex.
        seatGrid[seatIndex[0]][seatIndex[1]] = passengerName;
        // Function returns true if this is run.
        return true;
    }
    else {
        // If the seat is not equal to EMPTY_SEAT the function will return false.
        return false;
    }


    // Use this code to release the dynamically allocated memory
    delete[] seatIndex;
    seatIndex = nullptr;


}

/// Accepts the Seat Grid and a seat string
/// Returns true = the seat was successfully released
///     If the execution makes it here, there is no good reason for the seat not be released because
///         the case in the main function for this checks if the passenger exists.
///
/// Pass the seat string to seat2Index (use upperCase function on the seat string) to convert
///     a seat string to int* seatIndex (which is a pointer to an array of int)
/// Use the values in seatIndex (again, the pointer to an array of int)
///     to index into seatGrid and assign the seat to EMPTY_SEAT.
/// 
/// To put this into perspective, this function is about 3 additional lines of code.
/// 
/// Create the releaseSeat function passing in the seatGrid array and seat variable.  When true this function
/// will assign the EMPTY_SEAT constant to the seatGrid array indexed with seatIndex array values. 
/// Returns a boolean value.
bool releaseSeat(string seatGrid[][NUM_SEAT_LETTERS], string seat)
{
    // Given to you since true is always returned.
    bool releaseSeatOK = true;


    // Create a reference int array seatIndex by calling the seat2Index function with seat passed as the
    // argument.  This will give you the correct array values to index the seatGrid array to set the
    // occupant information.
    int* seatIndex = seat2Index(upperCase(seat));

    // Index the seatGrid array using the seatIndex array values and assign the value EMPTY_SEAT.
    seatGrid[seatIndex[0]][seatIndex[1]] = EMPTY_SEAT;


    // Given to you since true is always returned.
    return releaseSeatOK;
}

/// The index2Seat function passes 2 ints row and letter to return the properly formatted
/// seat variable.
string index2Seat(int row, int letter)
{
    // Initialize the seat string.
    string seat;
    // Initializa the padding string with an empty value.
    string padding = "";

    // Add one because of zero-based indexing.
    seat = to_string(row + 1);

    // If the seat number is a single digit number a 0 will be added to the beginning.
    padding.insert(0, SEAT_STR_ROW_NUM_DIGITS - seat.length(), PAD_CHAR);

    // Concatenate padding and seat and assign the value to seat.
    seat = padding + seat;
    // Add the letter string and LETTER_OFFSET to the seat string.
    seat += (char)(letter + LETTER_OFFSET);

    // Return the seat string.
    return seat;
}

/// Create seat2Index function which a string argument seat.  This function is used to take the seat variable
/// and split it into 2 array values.  Returns an int.
int* seat2Index(string seat)
{
    // Create a new int array seatIndex whose size is equal to SEAT_GRID_DIMENSION.
    int* seatIndex = new int[SEAT_GRID_DIMENSION];

    // Substract one because of zero-based indexing.
    ///
    /// Convert seat from a string to an int value taking the substring of seat starting at SEAT_STR_ROW_START_POS for the 
    /// length of SEAT_STR_ROW_NUM_DIGITS. Subtract 1 and assign that value to the seatIdex array at index 
    /// SEAT_INDEX_ROW_POS.
    seatIndex[SEAT_INDEX_ROW_POS] = (stoi(seat.substr(SEAT_STR_ROW_START_POS, SEAT_STR_ROW_NUM_DIGITS))) - 1;
    /// Convert seat to an int removing the letter from the beginning of the seat index and assign that value to the seatIndex
    /// array at index SEAT_INDEX_LETTER_POS.
    seatIndex[SEAT_INDEX_LETTER_POS] = (int)seat[SEAT_STR_LETTER_START_POS] - LETTER_OFFSET;

    // Return the seatIndex array.
    return seatIndex;
}

/// dashLine is overloaded. What does that mean?
///
/// dashLine function recieves lineLength and returns nothing.
void dashLine(int lineLength)
{
    // Use a for loop to repeatedly print the REPEAT_CHAR constant until
    // the value of x is less than the lineLenght variable.
    for (int x = 0; x < lineLength; x++)
        cout << REPEAT_CHAR;

    // Create a blank line.
    cout << endl;
}

/// dashLine is overloaded. What does that mean?
/// Overridden dashLine function takes lineLength and outFile output file arguments.
/// By over riding the dashLine function we are able to add more functionality to the 
/// function when needed.
void dashLine(int lineLength, ofstream* outFile)
{
    // Use a for loop to repeatedly print the REPEAT_CHAR constant until
    // the value of x is less than the lineLenght variable. This is then added
    // to the outFile stream.
    for (int x = 0; x < lineLength; x++)
        *outFile << REPEAT_CHAR;

    // Create a blank line in outFile.
    *outFile << endl;
}

/// Create upperCase function which accepts string2Upper as an argument and 
/// returns a string value. This function will convert a given string into all 
/// upper case letters.
string upperCase(string string2Upper)
{
    // Initialize the stringUpperCased variable.
    string stringUpperCased;

    // Use a for loop to cycle through each char i the string2Upper variable.
    for (size_t x = 0; x < string2Upper.length(); x++) {
        // Each time the loop processes stringUpperCased is update by adding 
        // string2Upper array, with x being the index value, called inside the 
        // toupper function.  This will concatanate and eventually produce the
        // string2Upper variable to completely capital letters.
        stringUpperCased += toupper(string2Upper[x]);
    }

    // Return the stringUpperCased variable.
    return stringUpperCased;
}
 
/// Create the isSeatValid function passing the seat variable as the the argument.  
/// This function will return a boolean value.
bool isSeatValid(string seat)
{
    // Initialize the validSeat boolean to true.
    bool validSeat = true;

    /// If the length of seat is not equal to SEAT_STR_ROW_NUM_DIGITS + SEAT_STR_LETTER_NUM_CHARS do the following.
    if (seat.length() != (SEAT_STR_ROW_NUM_DIGITS + SEAT_STR_LETTER_NUM_CHARS)) {
        /// Print an empty line followed by ERROR_MESSAGE_PREFIX, INVALID_SEAT_LENGTH_MESSAGE, ERROR_MESSAGE_PREFIX
        /// constants, and two more empty lines.  This will print out the error message needed if the seat variable is 
        /// the wrong size.
        cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_LENGTH_MESSAGE << ERROR_MESSAGE_PREFIX << endl << endl;
        // Set validSeat to false.
        validSeat = false;
    }
    else {
        /// If the length of seat is equal to SEAT_STR_ROW_NUM_DIGITS + SEAT_STR_LETTER_NUM_CHARS do the following. 
        /// Uses a for loop to cycle through each digit in the seat variable. 
        for (int x = 0; x < SEAT_STR_ROW_NUM_DIGITS; x++) {
            // If the isdigit function returns false at the specified digit in the seat variable then validSeat is false
            // else returns true.
            if (!isdigit(seat[x]))
                validSeat = false;
        }
        /// If validSeat is false print out an error message using the ERROR_MESSAGE_PREFIX, INVALID_SEAT_LENGTH_MESSAGE, 
        /// ERROR_MESSAGE_PREFIX constants.  Use endl to add the needed white space around the error message.
        if (!validSeat) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_ROW_NON_NUMERIC_MESSAGE << ERROR_MESSAGE_PREFIX << endl << endl;
        }
    }

    // Initialize the setTypeIndexStr variable to the value of the SEAT_TYPE_INDEX array as a string.
    string seatTypeIndexStr = string(SEAT_TYPE_INDEX);

    //  If validSeat is true execute the following code in order to find any other potential errors.
    if (validSeat) {

        /// Convert the seat substring object from a string to and int. The substring is figured using the SEAT_STR_ROW_START_POS and SEAT_STR_ROW_NUM_DIGITS
        /// constants.  If the value of the seat substring in conversion is less than the SEAT_ROWS_START constant execute the following code 
        /// in order to display an error message using the ERROR_MESSAGE_PREFIX, INVALID_SEAT_LENGTH_MESSAGE, 
        /// ERROR_MESSAGE_PREFIX constants.  Use endl to add the needed white space around the error message. 
        if (stoi(seat.substr(SEAT_STR_ROW_START_POS, SEAT_STR_ROW_NUM_DIGITS - SEAT_STR_ROW_START_POS)) < SEAT_ROWS_START) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_ROW_OUT_OF_RANGE_LOWER_MESSAGE << SEAT_ROWS_START << ERROR_MESSAGE_PREFIX << endl << endl;
            // Set the validSeat boolean to false.
            validSeat = false;
        }
        /// Convert the seat substring object from a string to and int. The substring is figured using the SEAT_STR_ROW_START_POS and SEAT_STR_ROW_NUM_DIGITS
        /// constants.  If the value of the seat substring in conversion is greater than the SEAT_ROWS_START constant execute the following code 
        /// in order to display an error message using the ERROR_MESSAGE_PREFIX, INVALID_SEAT_LENGTH_MESSAGE, 
        /// ERROR_MESSAGE_PREFIX constants.  Use endl to add the needed white space around the error message. 
        else if (stoi(seat.substr(SEAT_STR_ROW_START_POS, SEAT_STR_ROW_NUM_DIGITS - SEAT_STR_ROW_START_POS)) > NUM_SEAT_ROWS) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_ROW_OUT_OF_RANGE_UPPER_MESSAGE << NUM_SEAT_ROWS << ERROR_MESSAGE_PREFIX << endl << endl;
            // Set the validSeat boolean to false.
            validSeat = false;
        }
        /// Call the isalpha function and if the seat variable digit at the SEAT_STR_LETTER_START_POS is alphabetic execute the following code 
        /// in order to display an error message using the ERROR_MESSAGE_PREFIX, INVALID_SEAT_LENGTH_MESSAGE, 
        /// ERROR_MESSAGE_PREFIX constants.  Use endl to add the needed white space around the error message.
        else if (!isalpha(seat[SEAT_STR_LETTER_START_POS])) {
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_LETTER_NON_ALPHABETIC << ERROR_MESSAGE_PREFIX << endl << endl;
            // Set the validSeat boolean to false.
            validSeat = false;
        }
        /// Search the seatTypeIndexStr using the to upper fucntion to find the digit value of the seat variable at
        /// the SEAT_STR_LETTER_START_POS and if that value is not found execute the following code in oroder to display
        /// the proper error message and return the right boolean value.
        else if (seatTypeIndexStr.find(toupper(seat[SEAT_STR_LETTER_START_POS])) == string::npos) {

            /// Zero and one based indexing.
            /// Display an error message using the values from ERROR_MESSAGE_PREFIX, INVALID_SEAT_LETTER_OUT_OF_RANGE, 
            /// SEAT_TYPE_INDEX and the zero index, SEAT_TYPE_INDEX at the NUM_SEAT_LETTERS minus 1 index, and the ERRO_MESSAGE_PREFIX.
            /// Use endl to add the needed white space around the error message.
            cout << endl << ERROR_MESSAGE_PREFIX << INVALID_SEAT_LETTER_OUT_OF_RANGE << SEAT_TYPE_INDEX[0] << "-" << SEAT_TYPE_INDEX[NUM_SEAT_LETTERS - 1] \
                << ERROR_MESSAGE_PREFIX << endl << endl;
            // Set the validSeat boolean to false.
            validSeat = false;
        }
        else
            /// Finally if validSeat is true set the seat array at index SEAT_STR_LETTER_START_POS equal to the returned value
            /// of calling the toupper function on the seat array at index SEAT_STR_LETTER_START_POS. This just sets the variable to all 
            /// capital letters to make matching more streamline in the rest of the program.
            seat[SEAT_STR_LETTER_START_POS] = toupper(seat[SEAT_STR_LETTER_START_POS]);
    }

    // Once all of the above code is executed and processed return the validSeat boolean.
    return validSeat;
}