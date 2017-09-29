/* Computer Science Internal Assessment, designed and complied by Rasheika Panton
   This program is an Electronic Payroll System created for Blue Cafe and functions mainly to:
	- Add Employee Information
	- View Employees
	- Delete Employees' Information
	- Update Employeess' Information
	- Calculate Employees' Income
	- View Employees' Info and Income and then Exit 
	
Default Username: 'Manager'
Default Password: 'M4N4G3R'*/

/*Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <windows.h>

/*Declaration of the variables used throughout the program*/
int totalhours, otherdeductions;
float gross_income, net_income, stotal, itotal;

FILE *adminsettings;
FILE *employeeINFO; /*Declaration of file*/

int totalemployees=0, emp;

/*Declaration of a structure called "Login"*/
struct Login_Info
{
	char correctu[10], correctp[10];
};
struct Login_Info Login;

/*Declaration of a structure called "Employee"*/
struct EmployeeRecords
{
	char firstname[20];
	char lastname[20];
	int employeeID;	
}; 
struct EmployeeRecords Employee[20];
/*End of structure*/

/*Declaration of Functions*/
int searchByID(); //function to return the index of the ID being searched for or -1
void menu(); //function to display menu selections
void viewanemployee(int count); //function to view a specific employee searched for
void read_employees(); //function to read employees from the file
void write_employees(); //function to write employees to the file
void rewrite(int loc); //function to rewrite employees to the file
void view_employees();//function to view employees in the file
void sort_employees(); //function to sort employees by ID number
void add_employee(); //function to add an employee to the file
void del_employee(); //function to delete an employee from the file
void up_employee(); //function to update an employee in the file
void calculate_pay(); //function to calculate an employee's income
void view_pay(int emp); //function to view an employee's payslip
void readlogin_info(); //function to read login info from the file
void writelogin_info(); //function to write login info to the file
void change_un(); //function to change username
void change_pw(); //function to change password
void settings(); //function that displays 
void Exit();

/*Begin Main Function*/
int main()
{
	char username[10], password[10]; /*Declarion local variables*/

	system ("COLOR 1F"); /*Changes colour of display screen*/
	
	/*Calling on the standard time*/
	time_t timer;
    timer=time(NULL); 
    printf(" %s\n\n",asctime(localtime (&timer)));  
    
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n\n");
	printf ("\t\t\tADMINISTRATIVE LOGIN HOMEPAGE\n\n");
	printf ("Please enter your username and password to access the Payroll System.\n\n");
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n\n");
	
	/*Accepting Username and Password from user*/	
	printf ("Username:\t");
	scanf ("%s", &username);
	printf ("\n");
	printf ("Password:\t");
	scanf ("%s", &password);
	
	readlogin_info();
	
	if (strcmp (username, Login.correctu) == 0 && strcmp (password, Login.correctp) == 0) /*Checking for accuracy of Username and Password*/
	{
		system ("cls"); /*Clears the display screen*/
		
		menu(); /*Calling Menu Function*/
	
		getch(); /*Pauses the screen and awaits input*/
	} /*End Check*/
	else
	{
		printf ("\n\nError! Username or Password was entered incorrectly, press the Enter Key to try again!"); /*Error message*/
		getch(); /*Pauses screen and awaits input*/
		system ("cls"); /*Clears screen*/
		main(); /*Calling main function*/
	}
}
/*End Main Function*/

/*Defining Menu Function*/
void menu()
{
	int choice; /*Declaration of local variable*/
	
	system ("COLOR F1"); /*Changes colour of display screen*/
	
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n\n"); /*Begin Display Menu*/
	printf ("- - - - - - - - (: WELCOME TO BLUE CAFE's PAYROLL SYSTEM :) - - - - - - - -  \n\n");
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n\n");
	
	printf ("							0. LOG OUT\n\n\n");
	printf ("\t\tC H O I C E \n");
	printf ("\t\t  M E N U	\n\n\t");
	printf ("1. Add Employee Information\n\t");
	printf ("2. View ALL Employees\n\t");
	printf ("3. Delete Employee Information\n\t");		
	printf ("4. Modify/Update Employee Information \n\t");
	printf ("5. Calculate Income\n\t");
	printf ("6. View Income & Other Information\n\t");
	printf ("7. EXIT \n\n"); 
	printf ("							8. Settings\n\n"); /*End Display Menu*/
	
	
	printf ("\tPlease enter a number choice.\n\t");
	scanf ("%d", &choice); /*Prompting the user to input a choice from the display menu*/
	
	switch (choice) /*Directing the user to a function based on their choice previously inputted*/
	{
		case 0: 
			system ("cls"); /*Clears screen*/
			main(); /*Calling main function*/
			break;
		
		case 1: 
			read_employees(); /*Calling Read Employees Function*/
			add_employee(); /*Calling Add Employees Function*/
			sort_employees(); /*Calling Sort Employees Function*/
			view_employees(); /*Calling View Employees Function*/
			write_employees(); /*Calling Write Employees Function*/
			getch();
			menu(); /*Calling Menu Function*/
			break;	/*Case End*/
		
		case 2:
			read_employees(); /*Calling Read Employees Function*/
			sort_employees(); /*Calling Sort Employees Function*/
			view_employees(); /*Calling View Employees Function*/
			getch();
			menu(); /*Calling Menu Function*/
			break; /*Case End*/
			
		case 3:
			del_employee(); /*Calling Delete Employee Function*/
			sort_employees(); /*Calling Sort Employees Function*/
			view_employees(); /*Calling View Employees Function*/
			getch();
			menu(); /*Calling Menu Function*/
			break; /*Case End*/
			
		case 4:
			up_employee(); /*Calling Update Employee Function*/
			sort_employees(); /*Calling Sort Employees Function*/
			view_employees(); /*Calling View Employees Function*/
			getch();
			menu(); /*Calling Menu Function*/
			break; /*Case End*/
			
		case 5:
			calculate_pay(); /*Calling Calculate Income Function*/
			break; /*Case End*/
			
		case 6:
			view_pay(emp); /*Calling View Payslip Function*/
			break; /*Case End*/
			
		case 7:
			Exit(); /*Calling Exit Function*/
			break; /*Case End*/
			
		case 8:
			settings();
			break; /*Case End*/
			
		/*Used if a choice of 1-6 isn't chosen*/
		default: printf ("You did not choose one of the choices above.\nPlease pick a valid option.\n\n\n"); /*Error message*/
		getch(); /*Pauses screen and awaits input*/
		system ("cls"); /*Clears screen*/
		menu(); /*Calling the menu function*/
	}
}

/*Defining Read Employees Fucntion*/
void read_employees()
{
	int count;
	
	if ((employeeINFO = fopen("Employee Records.txt", "r")) == NULL)
	{
		printf ("FILE CANNOT OPEN");
	}
	else
	{	
		fscanf(employeeINFO, "%d\n\n", &totalemployees);
		
		for (count=0; count<totalemployees; count++)
		{
			fscanf(employeeINFO, "%s ", &Employee[count].firstname);
			fscanf(employeeINFO, "%s\n", &Employee[count].lastname);
			fscanf(employeeINFO, "%d\n\n", &Employee[count].employeeID);
		}
	}
	
	fclose(employeeINFO); //closes file
}

/*Defining Add Employee Fucntion*/
void add_employee()
{
	system("cls");
	
	printf ("\tOPTION 1: Add Employee Information\n\n\n");
	
	printf("Enter Employee's First Name:\t");
	scanf("%s", &Employee[totalemployees].firstname);
	
	printf("\nEnter Employee's Last Name:\t");
	scanf("%s", &Employee[totalemployees].lastname);
			
	printf("\nEnter Employee's ID Number:\t");
	scanf("%d", &Employee[totalemployees].employeeID);
	
	totalemployees++; //total employees will increase by 1
	
	write_employees(); //Writing new record to the file
	
	printf ("\nEmployee has been added successfully!\n");
	printf ("Press enter to proceed to view ALL current employees.\n");
	getch();
	system ("cls");
}

/*Defining Write Employees Fucntion*/
void write_employees()
{
	int count;
	
	if((employeeINFO = fopen("Employee Records.txt", "w"))== NULL) //Open file in write mode
	{
		printf("File CANNOT open");
	}
	else
	{	
		fprintf(employeeINFO, "%d\n\n", totalemployees); 
		
		for(count=0; count<totalemployees; count++)
		{
			fprintf(employeeINFO, "%s ", Employee[count].firstname);
			fprintf(employeeINFO, "%s\n", Employee[count].lastname);
			fprintf(employeeINFO, "%d\n\n", Employee[count].employeeID);
		}	
	}
	fclose(employeeINFO);
}	
/*Defining View Employees Fucntion*/
void view_employees()
{
	system ("cls");
	int count;
	
	printf ("\t\tBlue Cafe Employees' Listing\n\n\n");
	printf ("\tNAME\t\t\t\tID Number\n\n");
	
	for (count = 0; count < totalemployees; count++)
	{
		printf ("\t%s ", Employee[count].firstname);
		printf ("%s\t\t\t", Employee[count].lastname);
		printf ("%d\n", Employee[count].employeeID);
	}
}

/*Defining Sort Employees Fucntion*/
void sort_employees()
{	
	int phase, count, tempID;
	char tempFN[20], tempLN[20]; 
	
	for (phase=1; phase<totalemployees; phase++)
	{
		for (count=0; count<totalemployees-1; count++)
		{
			if (Employee[count].employeeID > Employee[count+1].employeeID)
			{
				tempID = Employee[count].employeeID;
				Employee[count].employeeID = Employee[count+1].employeeID;
				Employee[count+1].employeeID = tempID;
				
				strcpy(tempFN, Employee[count].firstname);
				strcpy(Employee[count].firstname, Employee[count+1].firstname);
				strcpy(Employee[count+1].firstname, tempFN);
				
				strcpy(tempLN, Employee[count].lastname);
				strcpy(Employee[count].lastname, Employee[count+1].lastname);
				strcpy(Employee[count+1].lastname, tempLN);
			}
		}
	}
}

/*Defining View an Employee Fucntion*/
void viewanemployee(int count)
{
	printf ("\n");
	printf ("First Name:\t%s\n", Employee[count].firstname);
	printf ("Last Name:\t%s\n", Employee[count].lastname);
	printf ("ID Number:\t%d\n", Employee[count].employeeID);
}

/*Defining Search by ID Fucntion*/
int searchByID()
{
	int ID, count;
	
	printf("\n\nEnter Employee's ID Number:\t");
	scanf("%d", &ID);
	
	for(count=0; count<totalemployees; count++)
	{
		if(Employee[count].employeeID == ID)
		{
			return count;
		}
	}
	
	printf("\nThat employee is not in the current database!\n");	
	return -1;
}

/*Defining Delete Employee Fucntion*/
void del_employee()
{
	int loc;
	char ans;
	
	system ("cls");
	
	printf ("\tOPTION 3: Delete Employee Information\n");
	read_employees();
	loc=searchByID();
	
	if (loc != -1)
	{
		viewanemployee(loc);
	
		printf ("\n\nIs this the employee you want to DELETE. Enter 'Y' for yes and 'N' for no.\t");
		fflush(stdin);
		scanf ("%c", &ans);
	
		if (ans == 'Y')
		{
			rewrite(loc);
			
			system ("cls");		
			printf ("\nEmployee has been successfully remove!\n\n");
			printf ("Press enter to proceed to view ALL current employees.");
			read_employees();	
			getch();
		}
		else 
		{
			if (ans == 'N')
			{
				printf ("Okay! Press enter to return to the main menu.\n");
				getch();
				menu();
			}
			else
			{
				printf ("Invalid input! Try again!\n");
				getch();
				system ("cls");
				del_employee();
			}
		}	
	}
	else
	{
		printf ("Please try again!\n\n");
		system("pause");
		menu();
	}
}

/*Defining Rewrite Employees Fucntion*/
void rewrite(int loc)
{
	int count;
	
	if((employeeINFO = fopen("Employee Records.txt", "w"))== NULL) //Open file in write mode
	{
		printf("File CANNOT open");
	}
	else
	{	
		fprintf(employeeINFO, "%d\n\n", totalemployees-1); 
		
		for(count=0; count<totalemployees; count++)
		{
			if(count != loc)
			{			
				fprintf(employeeINFO, "%s ", Employee[count].firstname);
				fprintf(employeeINFO, "%s\n", Employee[count].lastname);
				fprintf(employeeINFO, "%d\n\n", Employee[count].employeeID);
			}
		}	
	}
	totalemployees--;
	fclose(employeeINFO);
}

/*Defining Update Employee Fucntion*/
void up_employee()
{
	int loc;
	char ans;
	
	system ("cls");
	
	printf ("\tOPTION 4: Update Employee Information\n");
	read_employees();
	loc=searchByID();
	
	if (loc != -1)
	{
		viewanemployee(loc);
	
		printf ("\n\nIs this the employee you want to UPDATE. Enter 'Y' for yes and 'N' for no.\t");
		fflush(stdin);
		scanf ("%c", &ans);
	
		if (ans == 'Y')
		{
			system ("cls");	
		
			printf ("\tU P D A T E D\tI N F O R M A T I O N\n\n\n");
		
			printf ("Please enter Employee's updated First Name:\t");
			scanf ("%s", &Employee[loc].firstname);
			printf ("\nPlease enter Employee's updated Last Name:\t");
			scanf ("%s", &Employee[loc].lastname);
			printf ("\nPlease enter Employee's updated ID Number:\t");
			scanf ("%d", &Employee[loc].employeeID);
		
			write_employees();
		
			printf("\n\t");
			system("pause");
			printf ("\nEmployee has been successfully updated!\n");
			printf ("Press enter to proceed to view ALL current employees.");		
			getch();
			system ("cls");
		}
		else 
		{
			if (ans == 'N')
			{
				printf ("Okay. Press enter to return to the main menu.\n");
				getch();
				system ("cls");
				menu();
			}
			else
			{
				printf ("Invalid input! Try again!\n");
				getch();
				system ("cls");
				up_employee();
			}
		}	
	}
	else
	{
		printf ("Please try again!\n\n");
		system("pause");
		menu();
	}
}

/*Defining Calculate Pay Fucntion*/
void calculate_pay()
{
	/*Declaration of local variables*/
	float statutory_deduction=0.15, hourly_rate=299.99, income_tax=0.125, total_deduction;
	int overhourly_rate=350, overhours, overtime_pay, donations=500, hour[7], reg_pay, treg_hours;
	char ans;
	
	system ("cls");

	read_employees();
	sort_employees();
	view_employees();	
	
	printf ("\n\tOPTION 5: Calculate Income\n");
	printf ("\nPlease select an employee to calculate their income.");
	emp=searchByID();
	system ("cls");
	
	viewanemployee(emp);
	
	printf ("\nPress enter to proceed in calculating the income for the employee above.\n");
	getch();
	
	system ("cls"); /*Clears screen*/
	
	printf ("\t\t\t %s %s's PAYROLL ACCOUNT\n\n", Employee[emp].firstname, Employee[emp].lastname);
	printf ("\t\t\t\tGross Income\n\n");
	
	printf ("Enter the total hours worked by %s on each of the following days:\n", Employee[emp].firstname);
	printf ("(NB: Do not include any hour worked overtime if there are any)\n\n\t");
	
	/*Accepting the amount of hours worked by employee on Mon-Sat*/
	printf ("Mon:\t");
	scanf ("%d", &hour[1]);
		
	printf ("\tTue:\t");
	scanf ("%d", &hour[2]);
	
	printf ("\tWed:\t");
	scanf ("%d", &hour[3]);

	printf ("\tThurs:\t");
	scanf ("%d", &hour[4]);

	printf ("\tFri:\t");
	scanf ("%d", &hour[5]);
	
	printf ("\tSat:\t");
	scanf ("%d", &hour[6]);
	
	treg_hours= hour[1]+hour[2]+hour[3]+hour[4]+hour[5]+hour[6]; /*Calculating the total regular hours*/
	
	printf ("If %s worked overtime hours, enter the amount of hours worked, if not, please input 0.\n\t", Employee[emp].firstname);
	scanf ("%d", &overhours); /*Accepting the amount of overtime hours worked*/
	
	totalhours= treg_hours+overhours; /*Calculating overall amount of hours worked*/
	reg_pay= treg_hours*hourly_rate; /*Calculating pay based on total regular hours only*/
	overtime_pay= overhours*overhourly_rate; /*Calculating overtime pay*/
	
	gross_income= reg_pay+overtime_pay; /*Calculating total pay before tax*/

	printf ("\n\n%s's Gross Income has been calculated. Press Enter to proceed to the Net Income.\n", Employee[emp].firstname);
	
	getch(); /*Pauses screen and awaits input*/
	system ("cls"); /*Clears screen*/
	
	printf ("\t\t\t %s %s's PAYROLL ACCOUNT\n\n", Employee[emp].firstname, Employee[emp].lastname);
	printf ("\t\t\t\tNet Income\n\n");
	
	stotal= statutory_deduction*gross_income; /*Calculating statutory deduction*/
	itotal= income_tax*gross_income; /*Calculating income tax*/
	
	printf ("Is this employee on the Donors' List? Enter 'Y' for yes or 'N' for no.\n\t");
	scanf ("%s", &ans); /*Accepting data from user*/
	
	if (ans=='Y') /*Testing data against 'Y'*/
	{
		printf ("This donation along with Income Tax and Statutory Deductions will be deducted.\n\tPress the Enter Key to Continue.\n\n");
	
		otherdeductions= donations; /*Assigning other deductions to donations ($500)*/
		getch(); /*Pauses screen and awaits input*/
	}
	else /*If data is not 'Y'*/
	{
		if (ans=='N') /*Testing data against 'N'*/
		{
			printf ("Okay, only Income Tax and Statutory Deductions will be deducted.\n\tPress the Enter Key to Continue.\n\n");
		
			otherdeductions= 0; /*Assigning other deductions to 0*/
			getch(); /*Pauses screen and awaits input*/
		} 
		
	}
	total_deduction= otherdeductions+itotal+stotal; /*Calculating the total deductions*/
	net_income= gross_income-total_deduction; /*Calculating pay after deductions*/
	
	system ("cls"); /*Clears screen*/
	printf ("%s %s's Net Income has been calculated. ", Employee[emp].firstname, Employee[emp].lastname);
	printf ("Use the Enter Key to return to the main menu to view the calculations.\n");
	
	getch(); /*Pauses screen and awaits input*/
	system ("cls"); /*Clears screen*/
	
	menu(); /*Calling menu function*/
}

/*Defining View Payslip Fucntion*/
void view_pay(int emp)
{
	system ("COLOR F0");
	system ("cls"); /*Clears screen*/
	printf ("OPTION 6: View Income & Other Information\n\n");
	/*Calling on the standard time*/
	time_t timer;
    timer=time(NULL); 
    printf("Date & Time:\t%s\n",asctime(localtime (&timer)));
    
    /*Pay slip header design*/
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n");
	printf ("\t\t\t\tB L U E   C A F E\n");
	printf ("\t\t\t\tEmployee #%d\n", Employee[emp].employeeID);
	printf ("\t\t\t\tP A Y    S L I P\n");
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n\n");
	
	/*Outputting calculated information*/ 
	printf ("Employee's Name:\t %s %s\n\n\n", Employee[emp].firstname, Employee[emp].lastname);
	printf ("Total Hours:		%d\n\n", totalhours);
	printf ("\t\tGross Pay:	$%.2f\n\n", gross_income);
	printf ("Income Tax:		$%.2f\n", itotal);
	printf ("Statutory Deduction:	$%.2f\n", stotal);
	printf ("Other Deductions:	$%d\n\n", otherdeductions);
	printf ("\t\tNet Pay:	$%.2f\n\n", net_income);
	
	/*Pay slip footer design*/
	printf ("o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o oo o \n\n");
	printf ("\t\t\t\t\t Signed: Rasheika R. Panton \n\t\t\t\t\t -Management");
	
	getch(); /*Pauses screen and awaits input*/
	system ("cls"); /*Clears screen*/
	menu(); /*Calling menu function*/
}

/*Defining settings function*/
void settings()
{
	/*Declaring local variable*/
	int change;
	
	system ("cls"); /*Clears screen*/
	system ("COLOR F0"); /*Changes color of output screen*/
	
	printf ("\tS E T T I N G S\n\t   M E N U\n\n");
	printf ("What would you like to do?\n\n"); /*Requesting input*/
	
	printf ("\t1. Change Username\n");
	printf ("\t2. Change Password\n");
	printf ("\t3. Return to Main Menu\n");
	
	printf ("\nPlease enter a number choice.\n\t");
	scanf ("%d", &change); /*Accepting an option from user*/
	
	switch (change) /*Directing user based on option provided*/
	{
		case 1: /*Option 1*/
			change_un();
			break;
		
		case 2:	/*Option 2*/
			change_pw();
			break; 
		
		case 3: /*Option 3*/
			system ("cls");
			menu(); /*Calling menu function*/
			break;
			
		default: printf ("You did not choose one of the choices above.\nPlease pick a valid option.\n\n\n");
		getch();
		system ("cls");
		settings();
		
	}
}

/*Defining Read Login Info Fucntion*/
void readlogin_info()
{
	int count;
	
	if ((adminsettings = fopen("Admin Information.txt", "r")) == NULL)
	{
		printf ("FILE CANNOT OPEN");
	}
	else
	{
		fscanf(adminsettings, "%s\n", Login.correctu);
		fscanf(adminsettings, "%s\n", Login.correctp);
	}
	
	fclose(adminsettings); //closes file
}

/*Defining Write Login Info Fucntion*/
void writelogin_info()
{
	int count;
	
	if((adminsettings = fopen("Admin Information.txt", "w"))== NULL) //Open file in write mode
	{
		printf("File CANNOT open");
	}
	else
	{	
			fprintf(adminsettings, "%s\n", Login.correctu);
			fprintf(adminsettings, "%s\n", Login.correctp);	
	}
	fclose(adminsettings);
}	

/*Defining Change username Fucntion*/
void change_un()
{
	char currentp[10];
	system ("cls"); /*Clears screen*/
	
	readlogin_info();
	
	printf ("\tOPTION 1: Change Username\n\n");
	/*Requesting password to continue*/
	printf ("You have requested to change your username.\nPlease enter your current password to continue.\n\n\t");
	scanf ("%s", currentp); /*Aceepting current password*/
	if (strcmp (currentp, Login.correctp) == 0) /*Checking for accuracy of current Password*/
	{
		system ("cls"); /*Clears screen*/
		printf ("USER SETTINGS: Change Username\n\n");
		printf ("Enter new username:\t"); /*Requesting new username*/
		scanf ("%s", &Login.correctu); /*Accepting new username*/
		
		writelogin_info();
		
		system ("cls"); /*Clears screen*/
				
		/*Sucess message*/
		printf ("You have successfully changed your username!\nPress enter to return to Main Settings.\n");
		getch(); /*Pauses screen and awaits input*/
		settings(); /*Calling settings function*/
	}
	else /*If password is incorrect*/
	{
		printf ("\n");
		system ("pause");
		/*Error message*/
		printf ("\nThe password you entered is incorrect! Press enter to return to the Main Settings.\n");
		getch(); /*Pauses screen and awaits input*/
		settings(); /*Calling settings fucntion*/
	}
}

/*Defining Change password Fucntion*/
void change_pw()
{
	char currentp[10];
	system ("cls"); /*Clears screen*/
	
	readlogin_info();
	printf ("\tOPTION 2: Change Password\n\n");
	/*Requesting password to continue*/
	printf ("You have requested to change your password.\nPlease enter your current password to continue.\n\n\t");
	scanf ("%s", currentp); /*Aceepting current password*/
	if (strcmp (currentp, Login.correctp) == 0) /*Checking for accuracy of current Password*/
	{
		system ("cls"); /*Clears screen*/
		printf ("USER SETTINGS: Change Password\n\n");
		printf ("Enter new password:\t"); /*Requesting new password*/
		scanf ("%s", &Login.correctp); /*Accepting new password*/
			
		writelogin_info();	
		system ("cls"); /*Clears screen*/
				
		/*Success message*/
		printf ("You have successfully changed your username!\nPress enter to return to Main Settings.\n");
		getch(); /*Pauses screen and awaits input*/
		settings(); /*Calling settings function*/
	}
	else /*If password is incorrect*/
	{
		printf ("\n");
		system ("pause");
		/*Error message*/
		printf ("The password you entered is incorrect! Press enter to return to the Main Settings.\n");
		getch(); /*Pauses screen and awaits input*/
		settings(); /*Calling settings function*/
	}
}

/*Defining exit function*/
void Exit()
{
	system ("cls"); /*Clears the screen*/
  
	exit(1); /*Exits program*/
} 
