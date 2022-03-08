#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void header();      // HEADER OF MANAGEMENT SYSTEM
string loginMenu(); // Function to Input Username and Passwords and to return the Status as ADMIN,CUSTOMER OR INVALID
void tempStop();    // Function to Stop Program Execution Temperarily
// size variable is used to control the number of customers in the bank
const int size = 50;     // Total Customers Size limit
int day = 0;             // Variable to help in displaying date
int Employees_count = 0; // Variable to count number of Employees
// This Count is used to check current customers in the bank.
int customers_count = 0; // Variable to count the number of Registered Customers
int Account_no = 1111;   // Variable to Generate Account no
int captcha_code = 8989; // A Captcha Code
string temp_captcha_code;
string TodayDate; // Date is in following format day/month/year
// Starting of Admin Function
void admin_menu();
void addCustomer();               // Function to Add A new Customer
void checkAccounts();             // Function to Print Customers Info to Admin
void makeCopyOfBalance();         // Function to create the copy of Balance Array
int MaxIndex();                   // Function To Find index of Most Cash owning Customer
void MakeMaxIdxArray();           // Function to store indexes of maximum cah owning customer in a order
void checkAccountsSorted();       // Function to Check Accounts in a sorted Order
float totalCashinTheBank(float);  // Function to Print the total Cash in the Bank
bool isValidPhoneNumber(string);  // input validation
bool isValidCnic(string);         // input validation
bool isUserNameNotTaken(string);  // input validation
bool isValidPassword(string);     // input validation
bool isValidAddress(string);      // input validation
bool isValidStatus(char);         // Check wheather status entered by admin is valid
bool isAccountExist(string name); // Check wheather particular Account exists
int SearchIdx(string name);       // Returns the index of Searched username
void DeleteAccount();             // Deletes a Customer Account
void UpdateDate();                // Update Today Date when attendance is taken
void cout_tab();
// int Max_Cash_idx(int idx);//This Function will return maximum index
//  End of Admin Functions
//  Starting of Customers Functions
void customer_Menu();                            // Customer,s Menu
void checkAccountsInfo(int idx);                 // Function to print customer Information to Current user
void depositCash(int idx, float deposit_cash);   // Function to deposit Cash
void withdrawCash(int idx, float withdraw_cash); // Function to withdraw Cash
// Start of Loan Management Functions
bool isLoanEligible(float loan_amount, float asset_price); // Function to Check Wheather a Customer is eligible for Loan or Not
float installment_calculator(int, float);                  // Function to Calculate the installment of Customer According to his Installment Plan
void pay_loan(int idx);                                    // Functiont to Pay loan and updating balance
void ViewLoanInfo(int idx);                                // Function to print Loan info to Customer if Loan is taken
void show_captcha_code();                                  // Print the Captcha code to customer
bool isCaptchaSolved();                                    // Check Wheather Captcha code Entered by user is Right
void storeData(int idx);
void storeAttendence();
void storeEmployeesDetails(); // Store Employee Data
void LoadEmployeesDetails();  // Function to Load Employee Data
void LoadAttendence();        // Load Attendance from file
void loadData();              // Load Customers Data from File
void takeAttendence();        // Input Attendance
void checkAttendence();       // Prints Attendance
bool isEligibleGold();        // Check wheather a customer is eligible for Gold Status
void AssignGoldStatus();      // Function To Assign Golden Status to Eligible customers

// End of Loan Managing Functions
// Ending of Customers Functions
// Customer Data
//
string customers_name[size];
string customers_address[size];
string customers_phone_numbers[size];
string customers_cnic[size];
string customers_username[size];
string customers_password[size];
float customers_balance[size];
float customers_balance_copy[size]; // This Array will store the copy of customers_balance and will help in sorting
int customers_sorted_idx[size];     // This array will store the indexes of Maximux Cash owning Customers in a Descending Sequence
float customers_asset_price[size];
bool customers_loan_taken_status[size];
float customers_total_loan_amount[size];
float customers_loan_amount_left[size];
float customers_installment[size];
char customers_status[size];
int customers_account_no[size];
string Employees_Name[20];        //{"Kevin","john","Jonathan","Mick","Henrick","Fred"};
string Employees_Designation[20]; //{"Security_Guard","Sweeper","Cashier","Cashier","Cashier","Manager"};
int Employees_Salaries[20];
char Employees_Attendence_month_jan[10][31];
// username and password are globally declared to be passed to void function
string username;
string password;
string admin_username = "admin";
string admin_password = "12345";
float processing_fee = 100; // processing fee to be charged on every CUstomer at the time of Account Creation
// option variable is declared globally to be passed to adminMenu() and customer_Menu() function
int option;
string key; // key variable to  stop the execution temporary
int main()
{
    // LoadCommonVariables();
    LoadEmployeesDetails();
    LoadAttendence();
    loadData();
    // Fee will be added to bank cash when registering new user.
    float deposit_cash, withdraw_cash;
    string who = " ";

    while (true)
    {
        header();
        who = loginMenu();
        if (who == "ADMIN")
        {
            option = 1;
            while (option != 9)
            {
                header();
                admin_menu();
                if (option == 1)
                {
                    //  count = count + 1;
                    header();
                    addCustomer();
                    customers_count = customers_count + 1;
                    storeData(customers_count);
                }
                else if (option == 2)
                {
                    header();
                    cout_tab;
                    DeleteAccount();
                    storeData(customers_count);
                }
                else if (option == 3)
                {
                    header();
                    checkAccounts();
                    tempStop();
                }
                else if (option == 4)
                {
                    header();
                    // makeCopyOfBalance();
                    MakeMaxIdxArray();
                    checkAccountsSorted();
                    tempStop();
                }
                else if (option == 5)
                {
                    header();
                    cout_tab();
                    cout << "Total Cash in the bank = " << totalCashinTheBank(processing_fee) << endl;
                    tempStop();
                }
                else if (option == 6)
                {
                    header();
                    takeAttendence();
                    storeAttendence();
                    // storeCommonVariables();
                    tempStop();
                }
                else if (option == 7)
                {
                    header();
                    checkAttendence();
                    tempStop();
                }
                else if (option == 8)
                {
                    header();
                    AssignGoldStatus();
                    tempStop();
                }
            }
        }
        else if (who == "CUSTOMER")
        {
            for (int i = 0; i < customers_count; i++)
            {
                if (username == customers_username[i] && password == customers_password[i])
                {
                    int current_customer_idx = i;
                    option = 1;
                    while (option != 7)
                    {
                        storeData(customers_count);
                        header();
                        customer_Menu();
                        if (option == 1)
                        {
                            header();
                            checkAccountsInfo(current_customer_idx);
                        }
                        else if (option == 2)
                        {
                            header();
                            cout_tab();
                            cout << "Enter amount to deposit:";
                            cin >> deposit_cash;
                            depositCash(current_customer_idx, deposit_cash);
                            tempStop();
                        }
                        else if (option == 3)
                        {
                            header();
                            cout_tab();
                            cout << "Enter amount to withdraw:";
                            cin >> withdraw_cash;
                            withdrawCash(current_customer_idx, withdraw_cash);
                            tempStop();
                        }
                        if (option == 4)
                        {
                            header();
                            if (customers_loan_taken_status[current_customer_idx] == 0)
                            {
                                float temp_loan_amount;
                                float temp_asset_price;
                                int temp_installment_plan;
                                cout_tab();
                                cout << "Enter Loan Amount::";
                                cin >> temp_loan_amount;
                                cout_tab();
                                cout << "Enter your Assets Price::";
                                cin >> temp_asset_price;
                                if (isLoanEligible(temp_loan_amount, temp_asset_price))
                                {
                                    cout_tab();
                                    cout << "Your Request is Successfully Processed." << endl;
                                    cout_tab();
                                    cout << "Enter your Installment Plan" << endl;
                                    cout_tab();
                                    cout << "1_ 12 Months      2_ 24 Months" << endl;
                                    cout_tab();
                                    cin >> temp_installment_plan;
                                    while (temp_installment_plan > 2 || temp_installment_plan < 1)
                                    {
                                        cout_tab();
                                        cout << "Enter Valid Installment Plan" << endl;
                                        cout_tab();
                                        cout << "1_ 12 Months      2_ 24 Months" << endl;
                                        cout_tab();
                                        cin >> temp_installment_plan;
                                    }

                                    customers_installment[current_customer_idx] = installment_calculator(temp_installment_plan, temp_loan_amount);
                                    cout_tab();
                                    cout << "The Installment is = " << customers_installment[current_customer_idx] << endl;
                                    customers_total_loan_amount[current_customer_idx] = temp_loan_amount;
                                    customers_loan_amount_left[current_customer_idx] = customers_total_loan_amount[current_customer_idx];
                                    customers_asset_price[current_customer_idx] = temp_asset_price;
                                    customers_balance[current_customer_idx] = customers_balance[current_customer_idx] + customers_total_loan_amount[current_customer_idx];
                                    customers_loan_taken_status[current_customer_idx] = 1;
                                }
                                else
                                {
                                    cout_tab();
                                    cout << "You are not Eligible for Loan because your requested Amount is Too Big!" << endl;
                                }
                            }
                            else
                            {
                                cout_tab();
                                cout << "Sorry Sir Loan is already taken." << endl;
                            }
                            tempStop();
                        }
                        if (option == 5)
                        {
                            header();
                            if (customers_loan_taken_status[current_customer_idx] == 1 && customers_loan_amount_left[current_customer_idx] > 0)
                            {
                                pay_loan(current_customer_idx);
                                cout_tab();
                                cout << "Your Lefted Amount of Loan is = " << customers_loan_amount_left[current_customer_idx] << endl;
                            }
                            else
                            {
                                cout_tab();
                                cout << "All Loan Amount is already Payed." << endl;
                            }
                            tempStop();
                        }
                        else if (option == 6)
                        {
                            header();
                            if (customers_loan_taken_status[current_customer_idx] == 1)
                            {
                                ViewLoanInfo(current_customer_idx);
                                tempStop();
                            }
                            else
                            {
                                cout_tab();
                                cout << "ALL Loan Amount is Already Payed" << endl;
                                tempStop();
                            }
                        }
                    }
                }
            }
        }
        else
        {
            header();
            cout_tab();
            cout << "Invalid Credantials" << endl;
            tempStop();
        }
    }
    return 0;
}

void header() // Header of MANAGEMENT SYSTEM
{
    cout << endl
         << endl
         << endl
         << endl;
    /*cout << "\t\t\t*****************************************************************************" << endl;
    cout << "\t\t\t*                                                                           *" << endl;
    cout << "\t\t\t*                                                                           *" << endl;
    cout << "\t\t\t*                        Banking Management System                          *" << endl;
    cout << "\t\t\t*                                                                           *" << endl;
    cout << "\t\t\t*                                                                           *" << endl;
    cout << "\t\t\t*****************************************************************************" << endl;
    cout << endl;
    */
     cout_tab();cout<<" _______                #  #           #####       |\\    /|                  #####                          #    "<<endl;
    cout_tab();cout<<"|       \\               # #   ( )      #   #       | \\  / |                  #   # ####         ####        #         "<<endl;
    cout_tab();cout<<"|_______/   ####  #     ##     #  #    #####       |  \\/  | ####  #    ####  ##### # /# #       # /# #    #####  "<<endl;
    cout_tab();cout<<"|       \\   #  #  ####  # #    #  ###      #       |      | #  #  #### #  #      # #/   ######) #/   ####   #      "  <<endl;
    cout_tab();cout<<"|_______/   ####_ #  #  #  #   #  # #  #####       |      | ####_ #  # ####_ ##### #### #  #  ) #### #  #   ##    "   <<endl;
    
    cout << endl;
    cout_tab();cout <<"                     ########   #     # ######## ########## ######  #     #                   "<<endl;
    cout_tab();cout <<"                     #           #   #  #             #     #       # # # #                   "<<endl;
    cout_tab();cout <<"                     ########     # #   ########      #     ######  #  #  #            "<<endl;
    cout_tab();cout <<"                            #      #           #      #     #       #     #           "<<endl;
    cout_tab();cout <<"                     ########      #    ########      #     ######  #     #           "<<endl;
    cout_tab();cout <<"_________________________________________________________________________________________________________________"<<endl;
    cout << endl<<endl;
}

// customer menu to be showed
void customer_Menu()
{
    cout << "\t\t\tMenu>>>" << endl;
    cout << "\t\t\t       1_Check Account Info" << endl;
    cout << "\t\t\t       2_Deposit Cash" << endl;
    cout << "\t\t\t       3_Withdraw Cash" << endl;
    cout << "\t\t\t       4_Take Loan" << endl;
    cout << "\t\t\t       5_Pay Loan" << endl;
    cout << "\t\t\t       6_View Loan Info" << endl;
    cout << "\t\t\t       7_Exit" << endl;
    cout << "\t\t\tEnter your option:" << endl;
    cout << "\t\t\t";
    cin >> option;
    system("cls");
}
void tempStop() // FUNCTION TO STOP THE EXECUTION TEMPORARILY
{
    cout_tab();
    cout << "Enter any Key to Continue......";
    cin >> key;
    system("cls");
}
// STARTING OF ADMIN FUNCTIONALITY HANDLING
void admin_menu() // ADmin Menu
{
    cout << "\t\t\tMENU>>>" << endl;
    cout << "\t\t\t        1_New Account" << endl;
    cout << "\t\t\t        2_Delete Account" << endl;
    cout << "\t\t\t        3_Check Accounts" << endl;
    cout << "\t\t\t        4_Check Accounts in a Sorting Order" << endl;
    cout << "\t\t\t        5_Check Total Cash in Bank" << endl;
    cout << "\t\t\t        6_Take Employees Attendence.." << endl;
    cout << "\t\t\t        7_Check Employees Attendence." << endl;
    cout << "\t\t\t        8_Open Recomended Instruction Box." << endl;
    cout << "\t\t\t        9_Exit" << endl;
    cout << "\t\t\tEnter your option:" << endl;
    cout << "\t\t\t";
    cin >> option;
    system("cls");
}
void addCustomer()
{
    if (customers_count < size)
    {

        cout_tab();
        cout << "Enter Customer Name:";
        cin >> customers_name[customers_count];
        cout_tab();
        cout << "Enter Customer Phone Number:";
        cin >> customers_phone_numbers[customers_count];
        while (!isValidPhoneNumber(customers_phone_numbers[customers_count]))
        {
            cout_tab();
            cout << "Enter Valid Phone number.";
            cin >> customers_phone_numbers[customers_count];
        }

        cout_tab();
        cout << "Enter Customers Address:";
        cin >> customers_address[customers_count];
        while (!isValidAddress(customers_address[customers_count]))
        {
            cout_tab();
            cout << "Valid Address is Typed with (_) underScore.Eg.Shalimar_road_street_6,etc" << endl;
            cin >> customers_address[customers_count];
        }
        cout_tab();
        cout << "Enter Customer Cnic:";
        cin >> customers_cnic[customers_count];
        while (!isValidCnic(customers_cnic[customers_count]))
        {
            cout_tab();
            cout << "Enter Valid Cnic Number.." << endl;
            cin >> customers_cnic[customers_count];
        }
        cout_tab();
        cout << "Assign Current Customer Status.. (r) for Regular.";
        cin >> customers_status[customers_count];
        while (!isValidStatus(customers_status[customers_count]))
        {
            cout_tab();
            cout << "Enter Valid Customer Status..";
            cin >> customers_status[customers_count];
        }

        cout_tab();
        cout << "Set Username of Customer:";
        cin >> customers_username[customers_count];
        while (!isUserNameNotTaken(customers_username[customers_count]))
        {
            cout_tab();
            cout << "Username is already Taken.";
            cin >> customers_username[customers_count];
        }
        cout_tab();
        cout << "Enter password of Customer:";
        cin >> customers_password[customers_count];
        while (!isValidPassword(customers_password[customers_count]))
        {
            cout_tab();
            cout << "First Letter of Password should be in UpperCase.";
            cin >> customers_password[customers_count];
        }
        customers_account_no[customers_count] = Account_no++;
        Account_no++;
        system("cls");
    }
}
void checkAccounts()
{
    if (customers_count > 0)
    {
        cout_tab();
        cout << "Account#\tCustomer Name\t\tCustomer PhoneNumber\t\tCustomer Balance\tCustomers Status" << endl;
        for (int i = 0; i < customers_count; i++)
        {
            cout_tab();
            cout << customers_account_no[i] << "\t\t" << customers_name[i] << "\t\t\t" << customers_phone_numbers[i] << "\t\t\t\t" << customers_balance[i] << "\t\t\t" << customers_status[i] << endl;
        }
    }
    else
    {
        cout_tab();
        cout << "There are no Customers Registered" << endl;
    }
}
int MaxIndex()
{
    float max = customers_balance_copy[0];
    int max_idx = 0;
    for (int i = 0; i < customers_count; i++)
    {
        if (max < customers_balance_copy[i])
        {
            max = customers_balance_copy[i];
            max_idx = i;
        }
    }
    return max_idx;
}

void MakeMaxIdxArray()
{
    for (int a = 0; a < customers_count; a++)
    {
        customers_sorted_idx[a] = MaxIndex();
        customers_balance_copy[MaxIndex()] = -1;
    }
}
void checkAccountsSorted()
{
    if (customers_count > 0)
    {
        cout_tab();
        cout << "Account#\tCustomer Name\t\tCustomer PhoneNumber\t\tCustomer Balance\tCustomers Status" << endl;
        for (int i = 0; i < customers_count; i++)
        {
            cout_tab();
            cout << customers_account_no[customers_sorted_idx[i]] << "\t\t" << customers_name[customers_sorted_idx[i]] << "\t\t\t" << customers_phone_numbers[customers_sorted_idx[i]] << "\t\t\t" << customers_balance[customers_sorted_idx[i]] << "\t\t\t" << customers_status[customers_sorted_idx[i]] << endl;
        }
    }
}
float totalCashinTheBank(float processing_fee)
{
    float total_cash = 0;
    if (customers_count > 0)
    {
        for (int i = 0; i < customers_count; i++)
        {
            total_cash = total_cash + customers_balance[i] + (customers_count * processing_fee);
        }
    }
    return total_cash;
}
// ENDING OF ADMIN FUNCTIONALITY CUSTOMERS
// STARTING OF CUSTOMERS FUNCTIONALITY FUNCTIONS
//  checkAccountsInfo() function is used to Show the Customer,s Account Info to Him
void checkAccountsInfo(int idx)
{
    cout_tab();
    cout << "Your Username::          " << customers_name[idx] << endl;
    cout_tab();
    cout << "Your Phone number        " << customers_phone_numbers[idx] << endl;
    cout_tab();
    cout << "your cnic =              " << customers_cnic[idx] << endl;
    cout_tab();
    cout << "your address =           " << customers_address[idx] << endl;
    cout_tab();
    cout << "your total balance =     " << customers_balance[idx] << endl;
    tempStop();
}
// deposit cash function will deposit the cash and will update the customers balance
void depositCash(int idx, float deposit_cash)
{
    if (isCaptchaSolved())
    {
        customers_balance_copy[idx] = customers_balance[idx] + deposit_cash;
        customers_balance[idx] = customers_balance[idx] + deposit_cash;
        cout_tab();
        cout << "Your cash is successfully deposit.." << endl;
        captcha_code--;
    }
    else
    {
        cout_tab();
        cout << "Falied to Deposit Cash.." << endl;
    }
}
// withdraw Cash Function will withdraw the cash and will update the customers balance
void withdrawCash(int idx, float withdraw_cash)
{
    if (withdraw_cash <= customers_balance[idx])
    {
        if (isCaptchaSolved())
        {
            customers_balance_copy[idx] = customers_balance[idx] - withdraw_cash;
            customers_balance[idx] = customers_balance[idx] - withdraw_cash;
            cout_tab();
            cout << "Your Cash is successfully withdrawn." << endl;
        }
        else
        {
            cout_tab();
            cout << "Failed to Withdraw Cash" << endl;
        }
    }
    else
    {
        cout_tab();
        cout << "Insufficient Cash!" << endl;
    }
}
// isLoanEligible function will Check wheather a customer is Eligible for Loan or Not
bool isLoanEligible(float loan_amount, float asset_price)
{
    if (asset_price >= loan_amount)
    {
        return true;
    }
    return false;
}
//
float installment_calculator(int temp_installment_plan, float temp_loan_amount)
{
    float temp;
    if (temp_installment_plan == 1)
    {
        temp = temp_loan_amount / 12.0;
    }
    else
    {
        temp = temp_loan_amount / 24.0;
    }
    return temp;
}
void pay_loan(int idx)
{
    if (customers_balance[idx] >= customers_installment[idx])
    {
        if (customers_loan_amount_left[idx] >= customers_installment[idx])
        {
            customers_balance[idx] = customers_balance[idx] - customers_installment[idx];
            customers_loan_amount_left[idx] = customers_loan_amount_left[idx] - customers_installment[idx];
            cout_tab();
            cout << "Installment is succesfully payed from your Bank Account." << endl;
        }
        else
        {
            customers_balance[idx] = customers_balance[idx] - customers_loan_amount_left[idx];
            customers_loan_amount_left[idx] = 0;
            customers_loan_taken_status[idx] = 0;
        }
    }
    else
    {
        cout_tab();
        cout << "You Don,t have Enough Bank Balance to pay Loan Installment." << endl;
    }
}
void ViewLoanInfo(int idx)
{
    cout_tab();
    cout << "Total Loan Amount Taken = " << customers_total_loan_amount[idx] << endl;
    cout_tab();
    cout << "Installment = " << customers_installment[idx] << endl;
    cout_tab();
    cout << "Total Loan Amount Left  = " << customers_loan_amount_left[idx] << endl;
}
// ENDING OF CUSTOMER FUNCTIONALITY HANDLING FUNCTIONS
void makeCopyOfBalance()
{
    for (int i = 0; i < customers_count; i++)
    {
        customers_balance_copy[i] = customers_balance[i];
    }
}
string loginMenu()
{
    cout << "\t\t\tEnter username:";
    cin >> username;
    cout << "\t\t\tEnter password:";
    cin >> password;
    system("cls");
    if (username == admin_username && password == admin_password)
    {
        return "ADMIN";
    }
    if (customers_count > 0)
    {
        for (int i = 0; i < customers_count; i++)
        {
            if (username == customers_username[i] && password == customers_password[i])
            {
                return "CUSTOMER";
            }
        }
    }
    return "INVALID";
}
void storeData(int idx)
{
    fstream file;
    file.open("customerData.txt", ios::out);
    for (int iteration = 0; iteration < idx; iteration++)
    {
        file << customers_name[iteration] << " ";
        file << customers_address[iteration] << " ";
        file << customers_phone_numbers[iteration] << " ";
        file << customers_cnic[iteration] << " ";
        file << customers_username[iteration] << " ";
        file << customers_password[iteration] << " ";
        file << customers_balance[iteration] << " ";
        customers_balance_copy[iteration] = customers_balance[iteration];
        file << customers_balance_copy[iteration] << " ";
        file << customers_sorted_idx[iteration] << " ";
        file << customers_asset_price[iteration] << " ";
        file << customers_loan_taken_status[iteration] << " ";
        file << customers_total_loan_amount[iteration] << " ";
        file << customers_loan_amount_left[iteration] << " ";
        file << customers_installment[iteration] << " ";
        file << customers_status[iteration] << " ";
        file << customers_account_no[iteration];
        file << '\n';
    }
    file.close();
}
void loadData()
{
    string temp_s = " ";
    float temp_f = 0.0;
    int temp_i = 0;
    char temp_c;
    customers_count = 0;
    fstream file;
    file.open("customerData.txt", ios::in);
    while (!file.eof())
    {
        file >> customers_name[customers_count];
        if (customers_name[customers_count] == "")
            break;
        file >> customers_address[customers_count];
        file >> customers_phone_numbers[customers_count];
        file >> customers_cnic[customers_count];
        file >> customers_username[customers_count];
        file >> customers_password[customers_count];
        file >> temp_s;
        temp_f = stoi(temp_s);
        customers_balance[customers_count] = temp_f;
        file >> temp_s;
        temp_f = stoi(temp_s);
        customers_balance_copy[customers_count] = temp_f;
        file >> temp_s;
        temp_i = stoi(temp_s);
        customers_sorted_idx[customers_count] = temp_i;
        file >> temp_s;
        temp_i = stoi(temp_s);
        customers_asset_price[customers_count] = temp_i;
        file >> temp_s;
        temp_i = stoi(temp_s);
        customers_loan_taken_status[customers_count] = temp_i;
        file >> temp_s;
        temp_i = stoi(temp_s);
        customers_total_loan_amount[customers_count] = temp_i;
        file >> temp_s;
        temp_i = stoi(temp_s);
        customers_loan_amount_left[customers_count] = temp_i;
        file >> temp_s;
        temp_i = stoi(temp_s);
        customers_installment[customers_count] = temp_i;
        file >> temp_c;
        customers_status[customers_count] = temp_c;
        file >> temp_s;
        customers_account_no[customers_count] = stoi(temp_s);
        customers_count++;
        Account_no++;
    }
    file.close();
}
bool isValidPhoneNumber(string temp_phone)
{
    int num_count = 0;
    while (temp_phone[num_count] != '\0')
    {
        num_count++;
    }
    if (num_count == 11)
    {
        return true;
    }
    return false;
}
bool isValidCnic(string temp_cnic)
{
    int num_count = 0;
    while (temp_cnic[num_count] != '\0')
    {
        num_count++;
    }
    if (num_count == 13)
    {
        return true;
    }
    return false;
}
bool isValidPassword(string temp_password)
{
    int temp_Ascii = int(temp_password[0]);
    if (temp_Ascii >= 65 && temp_Ascii <= 90)
    {
        return true;
    }
    return false;
}
bool isUserNameNotTaken(string temp_username)
{
    for (int i = 0; i < customers_count; i++)
    {
        if (temp_username == customers_username[i])
        {
            return false;
        }
    }
    return true;
}
bool isValidAddress(string temp_address)
{
    for (int i = 0; i < temp_address.length(); i++)
    {
        if (temp_address[i] == '_')
        {
            return true;
        }
    }
    return false;
}
bool isValidStatus(char temp_c)
{
    if (temp_c == 'r')
    {
        return true;
    }
    return false;
}
void show_captcha_code()
{
    temp_captcha_code = to_string(captcha_code);
    cout_tab();
    cout << "*************************************" << endl;
    cout_tab();
    cout << temp_captcha_code[0] << "****************" << endl;
    cout_tab();
    cout << temp_captcha_code[1] << "*********************" << endl;
    cout_tab();
    cout << "************************" << temp_captcha_code[2] << temp_captcha_code[3] << endl;
    cout_tab();
    cout << "************************************" << endl;
    captcha_code--;
}
bool isCaptchaSolved()
{
    string temp_user_captcha_code = " ";
    int temp_captcha_count = 0;

    show_captcha_code();
    cout_tab();
    cout << "Enter Captcha Code from Above.." << endl;
    cout_tab();
    cin >> temp_user_captcha_code;
    while (temp_user_captcha_code != temp_captcha_code)
    {
        cout_tab();
        cout << "Enter Valid Captcha Code..";
        cin >> temp_user_captcha_code;
        cout_tab();
        cout << "Temp Captcha code = " << temp_user_captcha_code << endl;
        temp_captcha_count++;
        if (temp_captcha_count == 5)
        {
            return false;
        }
    }
    return true;
}
void takeAttendence()
{
    for (int i = 0; i < Employees_count; i++)
    {
        cout_tab();
        cout << "Is Present " << Employees_Name[i] << "  " << Employees_Designation[i] << " :? (p) for Present (a) for absennt (l) for Leave::";
        cin >> Employees_Attendence_month_jan[i][day];
    }
    day++;
    UpdateDate();
}
void UpdateDate()
{
    string month = "-01-2022";
    string temp_day = to_string(day);
    TodayDate = temp_day + month;
    cout_tab();
    cout << "Today Date = " << TodayDate << endl;
}
void checkAttendence()
{
    cout_tab();
    cout << "Today Date ::" << TodayDate << endl;
    cout << "\t ";
    if (day < 11)
    {
        cout_tab();
        for (int a = 0; a < day; a++)
        {
            if (a < 9)
            {
                cout << 0;
            }
            cout << a + 1 << "  ";
        }
    }
    else
    {
        cout_tab();
        for (int a = day - 10; a < day; a++)
        {
            if (a < 9)
            {
                cout << 0;
            }
            cout << a + 1 << "  ";
        }
    }
    cout << endl;
    for (int i = 0; i < Employees_count; i++)
    {
        cout_tab();
        cout << Employees_Name[i];
        cout << "\t ";
        if (day < 11)
        {
            for (int a = 0; a <= day; a++)
            {
                cout << Employees_Attendence_month_jan[i][a] << "   ";
            }
            cout << "\n";
        }
        else
        {
            for (int a = day - 10; a <= day; a++)
            {
                cout << Employees_Attendence_month_jan[i][a] << "   ";
            }
            cout << "\n";
        }
    }
}
void storeAttendence()
{
    fstream file;
    file.open("EmployeesAttendence.txt", ios::out);
    for (int i = 0; i < Employees_count; i++)
    {
        for (int a = 0; a < day; a++)
        {
            file << Employees_Attendence_month_jan[i][a];
        }
        file << '\n';
    }
    file.close();
}
void LoadAttendence()
{
    string line;
    fstream file;
    file.open("EmployeesAttendence.txt", ios::in);
    while (!file.eof())
    {
        file >> line;
        for (int i = 0; i < Employees_count; i++)
        {
            day = 0;
            for (int a = 0; a < line.length(); a++)
            {
                Employees_Attendence_month_jan[i][a] = line[a];
                day++;
            }
        }
    }
    file.close();
}
void LoadEmployeesDetails()
{
    string temp_s = " ";
    fstream file;
    file.open("employees_details.txt", ios::in);
    int temp_idx = 0;
    while (!file.eof())
    {
        file >> Employees_Name[temp_idx];
        file >> Employees_Designation[temp_idx];
        file >> temp_s;
        Employees_Salaries[temp_idx] = stoi(temp_s);
        temp_idx++;
        Employees_count++;
    }
}
bool isEligibleGold(int idx)
{
    if (customers_balance[idx] > 100000)
    {
        return true;
    }
    return false;
}
void AssignGoldStatus()
{
    char temp_choice;
    int temp_count = 0;
    for (int i = 0; i < customers_count; i++)
    {
        if (isEligibleGold(i) && customers_status[i] == 'r')
        {
            cout_tab();
            cout << "Customers Name = " << customers_name[i] << " is Eligible for Gold Status.(y) to assign";
            cin >> temp_choice;
            if (temp_choice == 'G' || temp_choice == 'g')
            {
                customers_status[i] = 'G';
            }
            temp_count++;
        }
    }
    if (temp_count == 0)
    {
        cout_tab();
        cout << "There are no Recommended customers For Golden Status." << endl;
        cout_tab();
        cout << "Press 1 to Know About Golden Status::";
        cin >> temp_count;
        if (temp_count == 1)
        {
            cout_tab();
            cout << "Golden Customers are those whose Bank Balance is greater than 100000 rupees." << endl;
        }
    }
}
bool isAccountExist(string name)
{
    for (int i = 0; i < customers_count; i++)
    {
        if (name == customers_username[i])
        {
            return true;
        }
    }
    return false;
}
int SearchIdx(string name)
{
    int temp_idx = 0;
    for (int i = 0; i < customers_count; i++)
    {
        if (name == customers_username[i])
        {
            temp_idx = i;
        }
    }
    return temp_idx;
}
void DeleteAccount()
{
    string temp_name;
    char temp_choice = ' ';
    cout << "\t\t\tEnter username of Customer You Want to Delete ..?";
    cin >> temp_name;
    if (isAccountExist(temp_name))
    {
        cout << "\t\t\tAre You sure to Delete ? Press (y) for yes (n) for no.";
        cin >> temp_choice;
        if (temp_choice == 'y')
        {
            int temp_idx = SearchIdx(temp_name);
            customers_name[temp_idx] = customers_name[customers_count - 1];
            customers_address[temp_idx] = customers_address[customers_count - 1];
            customers_phone_numbers[temp_idx] = customers_phone_numbers[customers_count - 1];
            customers_cnic[temp_idx] = customers_cnic[customers_count - 1];
            customers_username[temp_idx] = customers_username[customers_count - 1];
            customers_password[temp_idx] = customers_password[customers_count - 1];
            customers_balance[temp_idx] = customers_balance[customers_count - 1];
            customers_balance_copy[temp_idx] = customers_balance_copy[customers_count - 1];
            ; // This Array will store the copy of customers_balance and will help in sortingt customers_sorted_idx[size];     // This array will store the indexes of Maximux Cash owning Customers in a Descending Sequence
            customers_asset_price[temp_idx] = customers_asset_price[customers_count - 1];
            customers_loan_taken_status[temp_idx] = customers_loan_taken_status[customers_count - 1];
            customers_total_loan_amount[temp_idx] = customers_total_loan_amount[customers_count - 1];
            customers_loan_amount_left[temp_idx] = customers_loan_amount_left[customers_count - 1];
            customers_installment[temp_idx] = customers_installment[customers_count - 1];
            customers_status[temp_idx] = customers_status[customers_count - 1];
            customers_account_no[temp_idx] = customers_account_no[customers_count - 1];
            customers_count--;
            cout << "\t\t\tAccount Deleted Successfully.." << endl;
        }
    }
    else
    {
        cout_tab();
        cout << "The Given Username does Not Exist.." << endl;
    }
    tempStop();
}
void cout_tab()
{
    cout << "\t\t\t";
}
