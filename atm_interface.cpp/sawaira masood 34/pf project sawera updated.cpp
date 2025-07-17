#include <iostream>
#include <string>
#include<fstream>
using namespace std;

struct Account {
    string name;
    int pin;
    double balance;
    string history;
    int countTransaction;
    int NumOfAttempts;
    int  TwoStepVerification;
};
void createAccount(Account &acc) {
    cout << "Enter name to create account: ";
    cin >> acc.name;
    cout << "Enter a  PIN for  account: ";
    cin >> acc.pin;
    cout << "Enter a 4-digit two step verification code for password recovery: ";
    cin>>acc.TwoStepVerification;
    cout << "Enter  initial balance: ";
    cin >> acc.balance;
    acc.history = "Account created with balance: " + to_string(acc.balance);
    acc.countTransaction = 0;
    acc.NumOfAttempts = 0;
}
void deposit(Account &acc) {
    double amount;
    int pin;
    int maxAttempts = 3; 
    int attempts = 0; 
    while (attempts < maxAttempts) {
        cout << "Enter your PIN to deposit money: ";
        cin >> pin;
        if (pin == acc.pin) { 
            cout << "Enter the amount you want to deposit: ";
            cin >> amount;
            if (amount > 0) { 
                acc.balance += amount;
                acc.history += "Deposited: " + to_string(amount) ;
                acc.countTransaction++; 
                cout << "\nDeposit successful!";
                cout << "\nAfter this deposit, your new balance is: " << acc.balance << endl;
                return; 
            } else {
                cout << "Invalid amount! Deposit must be greater than 0." << endl;
                return;
            }
        } else {
            attempts++;
            cout << "Incorrect PIN! You have " << (maxAttempts - attempts) 
                 << " attempt(s) left." << endl;
        }
    }
    cout << "Maximum attempts reached! Deposit canceled for security reasons & account is locked!!!." << endl;
}
void withdraw(Account &acc) {
    double amount;
    int pin;
    int maxAttempts = 3; 
    int attempts = 0;    
    while (attempts < maxAttempts) {
        cout << "Enter your PIN to withdraw money: ";
        cin >> pin;
        if (pin == acc.pin) { 
            cout << "Enter the amount that you want to withdraw from your account: ";
            cin >> amount;
            if (amount > 0 && amount <= acc.balance) { 
                acc.balance -= amount; 
                acc.history += "Withdrawn: " + to_string(amount); 
                acc.countTransaction++; 
                cout << "\nWithdrawal successful!";
                cout << "\nYour new balance after this withdrawal is: " << acc.balance << endl;
                return; 
            } else if (amount > acc.balance) {
               cout << "Invalid amount! Your balance is insufficient." << endl;
                return; 
            } else {
                cout << "Invalid amount! Withdrawal amount must be greater than 0." << endl;
                return; 
            }
        } else {
            attempts++; 
            cout << "Incorrect PIN! You have " << (maxAttempts - attempts)
                 << " attempt(s) left." << endl;
        }
    }
    cout << "Maximum attempts reached! Withdrawal canceled for security reasons & acccount is locked now!!!" << endl;
}
void checkBalance(const Account &acc) {
    cout << "Current balance: " << acc.balance << endl;
    if (acc.balance < 100) {
        cout << "Warning: Low balance! Please upgrade your balance" << endl;
    }
}
void history(const Account &acc) {
    cout << "Transaction History:\n" << acc.history;
    cout << "Total Transactions: " << acc.countTransaction << endl;
}
void changePin(Account &acc) {
    int oldPin, newPin;
    cout << "Enter current PIN: ";
    cin >> oldPin;
    if (oldPin == acc.pin) {
        cout << "Enter new PIN: ";
        cin >> newPin;
        acc.pin = newPin;
        cout << "PIN changed successfully!" << endl;
    } else {
        acc.NumOfAttempts++;
        cout << "You enter the wrong PIN ,Please enter the correct one!" << endl;
        if (acc.NumOfAttempts >= 3) {
            cout << "Warning: Account is locked due to multiple  incorrect attempts!" << endl;
        }
    }
}
void recoverPin(Account &acc) {
    int code;
    cout << "Enter Two step verification code to reset PIN: ";
    cin>>code;
    if (code == acc.TwoStepVerification) {
        int newPin;
        cout << "Enter new PIN: ";
        cin >> newPin;
        acc.pin = newPin;
        cout << "PIN reset successfully!"<<"Your new PIN now to onward is:"<<newPin << endl;
    } else {
        cout << " you entered Incorrect code!" << endl;
    }
}
void transferFunds(Account &sender, Account &receiver) {
    double amount;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    if (amount > 0 && amount <= sender.balance) {
        sender.balance -= amount;
        receiver.balance += amount;
        sender.history += "Transferred: " + to_string(amount) + " to " + receiver.name ;
        receiver.history += "Received: " + to_string(amount) + " from " + sender.name;
        sender.countTransaction++;
        receiver.countTransaction++;
        cout << "Transfer successful!  after this transaction your new balance is: " << sender.balance << endl;
    } else if(amount > sender.balance)  {
        cout <<  "Insufficient balance!"<< endl;
    }
    else{
    	cout << "Invalid amount!"<< endl;
	}
}
void saveData(const Account &acc) {
    ofstream file(acc.name + ".txt");
    if (file.is_open()) {
        file << acc.name << endl;
        file << acc.pin << endl;
        file << acc.TwoStepVerification << endl;
        file << acc.balance << endl;
        file << acc.history << endl;
        file << acc.countTransaction << endl;
        file.close();
        cout << "huhh Congrats!!!!Your Account data is successfully saved now You can access it anytime!" << endl;
    } else {
        cout << "Error occurs!!!!Unable to save account data." << endl;
    }
}
bool loadData(Account &acc, const string &fileName) {
    ifstream file(fileName + ".txt");
    if (file.is_open()) {
        file>> acc.name;
        file >> acc.pin;
        file >> acc.TwoStepVerification;
        file >> acc.balance;
        file>>acc.history;
        file >> acc.countTransaction;
        file.close();
        cout << "Congrats!!!!YOUR saved data is successfully loaded!" << endl;
        return true;
    } else {
        cout << "Error: File is not found" << endl;
        return false;
    }
}

int main() {
    Account acc1, acc2;
    int choice;
    bool acc1Created= false, acc2Created = false;
    do {
    	cout<<"######################################";
        cout << "\n--------------------ATM Menu----------------\n";
        cout << "\n 1.Create an Account for yourself ";
        cout << "\n 2. Create Account for aother person";
        cout << "\n 3. Deposit Money ";
        cout << "\n 4. Withdraw Money ";
        cout << "\n 5. Check  your Balance ";
        cout << "\n 6. View your Transaction History ";
        cout << "\n 7. Change your ATM Pin ";
        cout << "\n 8. Recover your ATM PIN ";
        cout << "\n 9. Transfer Funds  to another account";
        cout << "\n 10. Save  the Account Data to File";
        cout << "\n 11. Load the Account Data from File";
        cout << "\n 12. Exit";
        cout<<"\n";
        cout<<"\n########################################";
        cout<<"\n";
        cout << "\n Which action do you want to perform: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if (!acc1Created) {
                    createAccount(acc1);
                    acc1Created = true;
                } else {
                    cout << "You already created an acoount for yourself!!" << endl;
                }
                break;
            case 2:
                if (!acc2Created) {
                    createAccount(acc2);
                    acc2Created = true;
                } else {
                    cout << " For another  user account is already created!" << endl;
                }
                break;
            case 3:
                if (acc1Created) {
				deposit(acc1);
			    }
                else {
			    cout << "No such  account found! Please create it first!" << endl;
			    }
                break;
            case 4:
                if (acc1Created){
			    withdraw(acc1);
			    }
                else {
                cout << "No matching account found! Please create it first!" << endl;
				}
                break;
            case 5:
                if (acc1Created){
                	checkBalance(acc1);
				} 
                else {
                	cout << "Account not found! Please create it first!" << endl;
				}
                break;
            case 6:
                if (acc1Created){
                	history(acc1);
				} 
                else {
                	cout << "Invalid Attempt! Please create a valid account first!" << endl;
				}
                break;
            case 7:
                if (acc1Created){
                	 changePin(acc1);
				}
                else{
                cout << "No  account found! Please create it first!" << endl;	
				} 
                break;
            case 8:
                if (acc1Created){
                	recoverPin(acc1);
				} 
                else{
                	cout << "Wrong attempt!!!!" << endl;
				} 
                break;
            case 9:
                if(acc1Created && acc2Created) {
                	transferFunds(acc1, acc2);
				}
                else {
				cout << "Both accounts must be created to transfer funds!" << endl;
                }
				break;
            case 10: 
                if (acc1Created) {
                saveData(acc1);
                }
			    else {
                cout << "No account found! Please create an account first." << endl;
                }
                break;
            case 11:{
            	 string fileName;
                cout << "Enter file name to load account data: ";
                cin >> fileName;
                if (loadData(acc1, fileName)) {
                acc1Created = true;
                }
                break;
            }
            case 12:
                cout << "Exiting... Thank you for using the ATM!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}
