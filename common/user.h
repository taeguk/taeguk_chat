#ifndef __USER_HEADER__
#define __USER_HEADER__

#include "common.h"
#include "chatroom.h"

typedef ChatRoom* ChatRoomPtr;
typedef vector<ChatRoomPtr> ChatRoomPtr_v;

class UserInfo
{
private:
	const int user_sock;
	char nickname[NICKNAME_SIZE];

public:
	UserInfo();
	~UserInfo();
}

class User 
{
private:
	const int user_sock;
	char nickname[NICKNAME_SIZE];

public:
	User(int user_sock, const char* nickname);
	~User();

	inline int get_user_sock();
	char* get_nickname();
	
	bool changeNickname(const char* nickname);

	char* to_char(void);
}

// 굳히 서버랑 클라이언트랑 달리할필요없을듯..?
// 클라이언트용 Ex도 만들어야겠는데??? 걍 같이 써도 될꺼같다..?
// chatroom.h 도 마찬가지
// enter,kick 등도 이 클래스안에 넣기??흠...

class UserEx : public User
{
private:
	//int clnt_sock;
	ChatRoomPtr_v pChatRoom_list;
	int pChatRoom_num;

private:
	ChatRoomPtr_v::iterator find_iter(int chatroom_id);
public:
	UserEx(int user_sock, const char* nickname);
	UserEx(int user_sock, const char* nickname, ChatRoomPtr_v& pChatRoom_list, int pChatRoom_num);
	~UserEx();

	ChatRoomPtr_v& get_pChatRoom_list();
	inline int get_pChatRoom_num();
	ChatRoomPtr get_pChatRoom(int chatroom_id);

	int add_pChatRoom(const ChatRoomPtr pChatRoom);
	int del_pChatRoom(const int chatroom_id);
}

//// clnt_sock 이랑 user_id 랑 걍 합쳐서 써도 되겠네??

#endif
