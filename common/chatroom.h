#ifndef __CHATROOM_HEADER__
#define __CHATROOM_HEADER__

#include "common.h"
#include "user.h"
#include "packet.h"

typedef User* UserPtr;
typedef vector<UserPtr> UserPtr_v;

class ChatRoomInfo
{
private:
	const int chatroom_id;
	char chatroom_name[CHATROOM_NAME_SIZE];
	int admin_sock;
	int user_num;

public:
	ChatRoomInfo();
	~ChatRoomInfo();
}

class ChatRoom
{
private:
	const int chatroom_id;
	char chatroom_name[CHATROOM_NAME_SIZE];
	int admin_sock;
	int user_num;

public:
	~ChatRoom();

	int get_chatroom_id();
	char* get_chatroom_name();
	int get_user_num();

	bool changeChatroomName(const char chatroom_name[]);
}

class ChatRoomEx : public ChatRoom
{
private:
	//UserPtr admin_user;
	UserPtr_v pUser_list;
	int pUser_num;   //없어도 되잖아??

private:
	UserPtrs::iterator find_iter(int user_id);
public:
	ChatRoomEx(int chatroom_id, char chatroom_name[], int pUser_num);
	ChatRoomEx(int chatroom_id, char chatroom_name[], UserPtr_v pUser_list, int pUser_num);
	~ChatRoomEx();
	
	UserPtr_v* get_pUser_list();
	int get_pUser_num();

	int add_pUser(const UserPtr pUser);
	int del_pUser(const int user_id);
}

#endif
