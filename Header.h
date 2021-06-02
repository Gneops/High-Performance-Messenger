typedef struct user_info
{
	char* username;
	char* password;
	char* phone_num;
	struct user_info* next;
}User;
typedef struct message
{
	char* sender;
	char* reciver;
	char* text_message;
	int state;/*Unread or read Messages*/
	struct message* next;
}Message;
char* string_maker();
void Signup(User*linkUsers, Message*linkPm, char*username);
void Login(User*linkUsers, Message*linkPm, char*username);
void mainMenu(User*linkUsers, Message*linkPm);
void Menu(User*linkUsers, Message*linkPm, char*username);
void SenDMessage(User*linkUsers, Message*linkPm, char*username);
void ShowSentpm(User*linkUsers, Message*linkPm, char*username);
void ShowReceivedpm(User*linkUsers, Message*linkPm, char*username);
void aboutUser(User*linkUsers, Message*linkPm, char*username);
void info(User*linkUsers, Message*linkPm, char*username);
void addPm(Message* linkPm, Message* newPM);
void addUser(User*linkUsers, User*newUser);
void EditUsername(User*linkUsers, Message*linkPm, char*username);
void EditPassword(User*linkUsers, Message*linkPm, char*username);
void PmState(Message* linkPm, char*username);
int CheckPhoneFormat(char*new_phoneNum);
int CheckPhoneExist(User* head, char* new_phoneNum);
int CheckUserExist(User* head, char*new_username);
