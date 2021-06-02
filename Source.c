#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <Windows.h>
#include "Header.h"
#define TWO 2
#define ONE 1
#define ZERO 0
#define phoneNumSize 11
#define MINPasswordSize 6
int main()
{
	User *Ut_users = (User*)malloc(sizeof(User));/*Structure of all user*/
	Ut_users->next = NULL;
	Message* Ut_pm = (Message*)malloc(sizeof(Message));/*Structure of all message*/
	Ut_pm->next = NULL;
	printf("Welcome to UT messenger.\n");
	mainMenu(Ut_users,Ut_pm);
	return 0;
}
void mainMenu(User* linkUsers,Message* linkPm)
{
	printf("Please enter your command.\n>> ");
	char*Host_username = NULL;/*username of users who go to login menu*/
	char* option = string_maker();
	if (strcmp(option, "signup") == ZERO)/*command check*/
	{
		Signup(linkUsers,linkPm,Host_username);
	}
	else if (strcmp(option, "login") == ZERO)
	{
		Login(linkUsers,linkPm,Host_username);
	}
	else if (strcmp(option, "close") == ZERO)
	{
		exit(0);
	}
	else
	{
		printf("Not defined.\n");
		mainMenu(linkUsers, linkPm);
	}
}
char* string_maker()/*function for make string in commandline*/
{
	int counter = ZERO;
	char* string = (char*)malloc(sizeof(char) * TWO);
	char character;
	while ((character = getchar()) != ' ' && character != '\n')
	{
		string = (char*)realloc(string, sizeof(char)*(counter + TWO));
		string[counter] = character;
		counter++;
	}
	string[counter] = '\0';
	return string;
}
void Signup(User* linkUsers,Message* linkPm, char*username)
{
	User* newUser = (User*)malloc(sizeof(User));
		newUser->username = string_maker();newUser->password = string_maker();newUser->phone_num = string_maker();
		if (CheckUserExist(linkUsers, newUser->username) == ZERO)
		{
				if (strlen(newUser->password) >= MINPasswordSize)/*Check password format*/
				{
					if (CheckPhoneFormat(newUser->phone_num) == ONE)
						if (CheckPhoneExist(linkUsers, newUser->phone_num) == ZERO)
						{
							addUser(linkUsers, newUser);/*linking new user to list*/
							username = newUser->username;/*username of users who go to login menu*/
							printf("Signup succesfully.\n");
							Menu(linkUsers, linkPm, username);
						}
							else {
								printf("This phone number has exist\n");
								free(newUser);
								mainMenu(linkUsers, linkPm);/*back to mainmenu*/
							}
						else {
							printf("phone number has wrong format\n");
							free(newUser);
							mainMenu(linkUsers, linkPm);
						}
				}
				else
				{
					printf("password has wrong format\n");
					free(newUser);
					mainMenu(linkUsers, linkPm);
				}
		}
		else {
			printf("This username has exist\n");
			free(newUser);
			mainMenu(linkUsers, linkPm);
		}
}
void Login(User* linkUsers,Message*linkPm,char* username)
{
	User* head = linkUsers->next;
	char* entered_username = string_maker();/*username in commandline*/
	char* entered_password = string_maker();/*password in command line*/
	while (head != NULL)
	{
		if (strcmp(head->username, entered_username) == ZERO)/*check username exist*/
		{
			while (ONE)
			{
				if (strcmp(head->password, entered_password) == ZERO)
				{
					username = entered_username;/*username of users who go to login menu*/
					printf("Login succesfully.\n");
					Menu(linkUsers, linkPm, username);/*go to login menu*/
				}
				else
				{
					printf("Password was wrong.\n");
					mainMenu(linkUsers, linkPm);
				}
			}
		}
		head = head->next;/*shift linklist*/
	}
	printf("This user does'nt exist.\nPlease signup first.\n");
	mainMenu(linkUsers,linkPm);

}
void addUser(User*linkUsers, User*newUser)/*function for linking new user to list */
{
	User* current = linkUsers->next;
	User* previous = linkUsers;
	while (current != NULL)
	{
		current = current->next;
		previous = previous->next;
	}
	current = (User*)malloc(sizeof(User));
	current = newUser;
	current->next = NULL;
	previous->next = current;
}
void addPm(Message* linkPm, Message* newPM)/*function for linking new message to list */
{
	Message* current = linkPm->next;
	Message* previous = linkPm;
	while (current != NULL)
	{
		current = current->next;
		previous = previous->next;
	}
	current = (Message*)malloc(sizeof(Message));
	current = newPM;
	current->next = NULL;
	previous->next = current;
}
void Menu(User* linkUsers,Message* linkPm,char* username)/*login menu*/
{
	PmState(linkPm, username);
	printf("Please enter your command.\n>> ");
		char* option = string_maker();
		if (strcmp(option, "send") == ZERO)/*commandline check*/
		{
			SenDMessage(linkUsers, linkPm, username);
		}
		else if (strcmp(option, "show_sent") == ZERO)/*commandline check*/
		{
			ShowSentpm(linkUsers, linkPm, username);
		}
		else if (strcmp(option, "show_received") == ZERO)/*commandline check*/
		{
			ShowReceivedpm(linkUsers, linkPm, username);
		}
		else if (strcmp(option, "logout") == ZERO)/*commandline check*/
		{
			printf("Logout succesfully.\n");
			mainMenu(linkUsers, linkPm);
		}
		else if (strcmp(option, "about") == ZERO)
		{
			aboutUser(linkUsers,linkPm,username);
		}
		else if (strcmp(option, "edit_user") == ZERO)
		{
			EditUsername(linkUsers, linkPm, username);
		}
		else if (strcmp(option, "edit_pass") == ZERO)
		{
			EditPassword(linkUsers, linkPm, username);
		}
		else if (strcmp(option, "info") == ZERO)
		{
			info(linkUsers, linkPm, username);
		}
		else {
			printf("Not defined.\n");
			Menu(linkUsers, linkPm, username);
		}
}
void SenDMessage(User*linkUsers,Message* linkPm, char* username)
{
	Message* newPM = (Message*)malloc(sizeof(Message));
	newPM->reciver = string_maker();/*assign usernames to pm struct*/
	newPM->text_message = string_maker();
	newPM->sender = username;
	newPM->state = 0;
		if (CheckUserExist(linkUsers, newPM->reciver) == ONE)
		{
			printf("Message sent succesfully.\n");
			addPm(linkPm, newPM);
			Menu(linkUsers, linkPm, username);
		}
		else
		{
			printf("This username does'nt exist.\n");
			free(newPM);
			Menu(linkUsers, linkPm, username);
		}
}
void ShowSentpm(User* linkUsers,Message*linkPm,char* username)
{
	Message* head = linkPm->next;
	char* contactUser = string_maker();/*username of user target*/
	if (CheckUserExist(linkUsers, contactUser) == ONE)
	{
			while (head != NULL)
			{
				if (strcmp(head->sender ,username ) == ZERO)
					if (strcmp(head->reciver, contactUser) == ZERO)
					{
						if (head->state == 0)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
							printf("Message to: %s\n", head->reciver);
							printf("%s\n", head->text_message);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						}
						else
						{
							printf("Message to: %s\n", head->reciver);
							printf("%s\n", head->text_message);
						}
					}
				head = head->next;/*shift Pm list*/
			}
			Menu(linkUsers, linkPm, username);
	}
	else
	{
		printf("This username does'nt exist.\n");
		Menu(linkUsers, linkPm, username);
	}
}
void ShowReceivedpm(User* linkUsers, Message*linkPm, char* username)
{
	Message* head = linkPm->next;
	char* contactUser = string_maker();
	if (CheckUserExist(linkUsers, contactUser) == ONE)
	{
		while (head != NULL)
		{
			if (strcmp(head->reciver, username) == ZERO)/*check users of existed pm*/
			{
				if (strcmp(head->sender, contactUser) == ZERO)
				{
					if (head->state == 0)
					{
						printf("Message from: %s\n", head->sender);
						printf("%s\n", head->text_message);
						head->state = 1;
					}
					else
					{
						printf("Message from: %s\n", head->sender);
						printf("%s\n", head->text_message);
					}
				}
				head = head->next;/*shift pm list*/
			}
		}
		Menu(linkUsers, linkPm, username);/*back to login menu*/
	}
	else
	{
		printf("This username does'nt exist.\n");
		Menu(linkUsers, linkPm, username);
	}
}
void aboutUser(User* linkUsers,Message* linkPm,char* username)/*function for show detail of each person*/
{
	User* head = linkUsers->next;
	char* ID = string_maker();
	if (CheckUserExist(linkUsers, ID) == ONE)
	{
		while (head != NULL)
		{
			if (strcmp(ID, head->username) == ZERO)
			{
				printf("Username: %s\n", head->username);
				printf("PhoneNumber: %s\n", head->phone_num);
				Menu(linkUsers, linkPm, username);
			}
			head = head->next;
		}
	}
	else
	{
		printf("This user doesn't exist.\n");
		Menu(linkUsers, linkPm, username);
	}
}
void EditUsername(User*linkUsers,Message*linkPm,char*username)
{
	char* newUsername = string_maker();
	if (CheckUserExist(linkUsers, newUsername) == 1)
	{
		printf("This User has exist.try again.\n");
		Menu(linkUsers, linkPm, username);
	}
	User*head = linkUsers->next;
	while (head != NULL)
	{
		if (strcmp(username, head->username) == ZERO)
		{
			strcpy(head->username,newUsername);
			strcpy(username, newUsername);
			printf("Username changed.\n");
			Menu(linkUsers, linkPm, username);
		}
		head = head->next;
	}
}
void EditPassword(User*linkUsers, Message*linkPm, char*username)
{
	char* newPassword = string_maker();
	if (strlen(newPassword) < 6)
	{
		printf("Password has wrong format.try again.\n");
		Menu(linkUsers, linkPm, username);
	}
	User*head = linkUsers->next;
	while (head != NULL)
	{
		if (strcmp(username, head->username) == ZERO)
		{
			strcpy(head->password, newPassword);
			printf("Password changed.\n");
			Menu(linkUsers, linkPm, username);
		}
		head = head->next;
	}
}
void info(User*linkUsers, Message*linkPm, char*username)
{
	User* head = linkUsers->next;
	while (head != NULL)
	{
		printf("%s\n", head->username);
		head = head->next;
	}
	Menu(linkUsers, linkPm, username);
}
int CheckUserExist(User* head, char*new_username)
{
	User* CheckUserlist = head->next;
	while (CheckUserlist != NULL)
	{
		if (strcmp(new_username, CheckUserlist->username) == ZERO)/*username has exist*/
		{
			return ONE;/*existed*/
		}
		CheckUserlist = CheckUserlist->next;
	}
	return ZERO;/*doesn't exist*/
}
int CheckPhoneFormat(char*new_phoneNum)
{
	int counter = ZERO;/*counter for digit of phone number*/
	if (strlen(new_phoneNum) == phoneNumSize)
		if (new_phoneNum[ZERO] == 48 ) /*48 is ascii number of '0'*/
			for (int i = ZERO; new_phoneNum[i] != '\0';i++)
				if (new_phoneNum[i] >= 48 && new_phoneNum[i] <= 58)/*between 0-9*/
					counter++;
				else
					return ZERO;
		else
			return ZERO;
	else
		return ZERO;/*wrong format*/
	if (counter == phoneNumSize)
		return ONE;/*Correct format*/
	else
		return 0;
}
int CheckPhoneExist(User* head, char* new_phoneNum)
{
	User* CheckUserlist = head->next;
	while (CheckUserlist != NULL)
	{
		if (strcmp(CheckUserlist->phone_num, new_phoneNum) == ZERO)/*phone number existed*/
			return ONE;/*existed*/
		CheckUserlist = CheckUserlist->next;
	}
	return ZERO;/*doesn't exist*/
}
void PmState(Message* linkPm, char*username)
{
	Message*head = linkPm->next;
	while (head != NULL)
	{
		if (strcmp(head->reciver, username) == ZERO)
			if (head->state == ZERO)
			{
				printf("UnRead Message from : %s\n", head->sender);
			}
		head = head->next;
	}
}
