#ifndef __PACKET_HEADER__
#define __PACKET_HEADER__

#include "common.h"

namespace PacketFlag
{
	enum Type
	{
		//로그인, 로그아웃
		LOGIN,
		LOGOUT,
		
		//채팅방 들어가기, 나가기
		QUERY_ENTER_CHATROOM,
		REPLY_ENTER_CHATROOM,
		QUERY_QUIT_CHATROOM,
		REPLY_QUIT_CHATROOM,
		
		//채팅방 만들기, 없애기
		QUERY_MAKE_CHATROOM,
		REPLY_MAKE_CHATROOM,
		QUERY_DEL_CHATROOM,
		REPLY_DEL_CHATROOM,
	
		//쿼리를 하면 리플라이가 됐을때 클라이언트에서 진짜 처리를 하는것.
		// 그 것을 위해 패킷안에 패킷주소를 넣는다.
		//CTRL_USER,
		//CTRL_CHATROOM,
		
		//메세지
		QUERY_SEND_MESSAGE,
		REPLY_SEND_MESSAGE,
		
		//유저정보 질의/응답
		QUERY_USER_INFO,
		REPLY_USER_INFO,
		
		//채팅방정보 질의/응답
		QUERY_CHATROOM_INFO,
		REPLY_CHATROOM_INFO,
		
		//채팅방의 유저리스트 질의/응답
		QUERY_USER_LIST_IN_CHATROOM,
		REPLY_USER_LIST_IN_CHATROOM,
		
		//클라이언트의 유저리스트,채팅방리스트 업데이트
		UPDATE_USER_LIST,
		UPDATE_CHATROOM_LIST
	};
	/*
	enum Ctrl_User
	{
		ENTER_CHATROOM,
		QUIT_CHATROOM,
		MODIFY_INFO    //미구현
	};
	
	enum Ctrl_ChatRoom
	{
		ADD_CHATROOM,
		MODIFY_CHATROOM,	//미구현
		DEL_CHATROOM,
		INVITE_USER,    //미구현
		KICK_USER		//미구현
	};
	enum Message
	{
		NORMAL_MSG,
		EMOTICON		//미구현	
	};
	*/
	enum Query_User_Info
	{
		QUERY_USER_INFO_BY_ID,
		QUERY_USER_INFO_BY_NAME
	};
	enum Query_ChatRoom_Info
	{
		QUERY_CHATROOM_INFO_BY_ID,
		QUERY_CHATROOM_INFO_BY_NAME
	};
	//밑에 많이 수정.
	enum Update_User_List
	{
		INIT_USER_LIST,
		ADD_USER,
		MODIFY_USER,		//미구현
		DEL_USER
	};
	enum Update_ChatRoom_List
	{
		INIT_CHATROOM_LIST,
		ADD_CHATROOM,
		MODIFY_USER,		//미구현
		DEL_CHATROOM
	};
}

class Packet
{
private:
	const int packet_sz;
	const PacketFlag::Type flag;
	const int clnt_sock;
public:
	Packet();
	Packet(int packet_sz, PacketFlag::Type flag, int clnt_sock);
	Packet(const char* buf);
	Packet(Packet& p);
	~Packet();

	PacketFlag::Type get_flag(void);

	int CharToPacket(const char* buf);
	int PacketToChar(char** pBuf);   //그 이 함수내에서 동적할당 vs 외부에서 동적할당 (getCharSize?? 만들기)
}

//로그인패킷
class Login_Packet : public Packet
{
private:
	char nickname[NICKNAME_SIZE];
public:
	Login_Packet();
	Login_Packet(Packet& packet, const char* nickname);
	Login_Packet(Packet& packet, const char* buf);
	Login_Packet(const char* buf);
	~Login_Packet();

	char* get_nickname();
	int set_nickname(int);
}

//안쓰임...
class Logout_Packet : public Packet
{
private:
public:
	Logout_Packet(Packet packet);
	~Logout_Packet();
}

class Query_Enter_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Query_Enter_ChatRoom_Packet();
	~Query_Enter_ChatRoom_Packet();
}

class Reply_Enter_ChatRoom_Packet : public Packet
{
private:	
	const void * packet_addr;
	bool is_success;
public:
	Reply_Enter_ChatRoom_Packet();
	~Reply_Enter_ChatRoom_Packet();
}

class Query_Quit_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Query_Quit_ChatRoom_Packet();
	~Query_Quit_ChatRoom_Packet();
}

class Reply_Quit_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Query_Quit_ChatRoom_Packet();
	~Query_Quit_ChatRoom_Packet();
}

class Query_Make_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Query_Make_ChatRoom_Packet();
	~Query_Make_ChatRoom_Packet();
}

class Reply_Make_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Query_Make_ChatRoom_Packet();
	~Query_Make_ChatRoom_Packet();
}

class Query_Del_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Query_Del_ChatRoom_Packet();
	~Query_Del_ChatRoom_Packet();
}

class Reply_Del_ChatRoom_Packet : public Packet
{
private:
	const void * packet_addr;
	int chatroom_id;
public:
	Reply_Del_ChatRoom_Packet();
	~Reply_Del_ChatRoom_Packet();
}

/*
class Ctrl_User_Packet : public Packet
{
private:
	const PacketFlag::Ctrl_User flag;
public:
	Ctrl_User_Packet(Packet packet, int flag);
	Ctrl_User_Packet(const char* buf);
	~Ctrl_User_Packet();
}

class Ctrl_ChatRoom_Packet : public Packet
{
private:
	const PacketFlag::Ctrl_ChatRoom flag;   //add del
	const int chatroom_id;
public:
	Ctrl_ChatRoom_Packet(Packet packet, int flag, int chatroom_id);
	Ctrl_ChatRoom_Packet(const char* buf);
	~Ctrl_ChatRoom_Packet();
}
*/
class Query_Send_Message_Packet : public Packet
{
private:
	const void * packet_addr;
	const int chatroom_id;
	const int message_sz;
	char* message;
public:
	Query_Send_Message_Packet(Packet packet, int chatroom_id);
	Query_Send_Message_Packet(const char* buf);
	~Query_Send_Message_Packet();
	char* get_message();
	int set_message(char* message, int message_sz);   //안에서 데이터
}

class Reply_Send_Message_Packet : public Packet
{
private:
	const void * packet_addr;
	const int chatroom_id;
	const int message_sz;
	char* message;
public:
	Query_Send_Message_Packet(Packet packet, int chatroom_id);
	Query_Send_Message_Packet(const char* buf);
	~Query_Send_Message_Packet();
}

class Query_User_Info_Packet : public Packet
{
private:
	const void * packet_addr;
	const PacketFlag::Query_User_Info flag;
	int data_sz;
	char* data;		// user_sock or user_name
public:
	Query_User_Info_Packet(const char* buf);
	~Query_User_Info_Packet();
}

class Reply_User_Info_Packet : public Packet
{
private:
	const void * packet_addr;
	UserInfo* user_info;

public:
	Reply_User_Info_Packet();
	~Reply_User_Info_Packet();
}

class Query_ChatRoom_Info_Packet : public Packet
{
private:
	const void * packet_addr;
	const PacketFlag::Query_ChatRoom_Info flag;
	int data_sz;
	char* data;		// chatroom_id or chatroom_name
public:
	Query_ChatRoom_Info_Packet(const char* buf);
	~Query_ChatRoom_Info_Packet();
}

class Reply_ChatRoom_Info_Packet : public Packet
{
private:
	const void * packet_addr;
	ChatRoomInfo* chatroom_info;

public:
	Reply_ChatRoom_Info_Packet();
	~Reply_ChatRoom_Info_Packet();
}

class Query_User_List_In_ChatRoom_Packet
{
private:
	const void * packet_addr;
	int chatroom_id;

public:
	Query_User_List_In_ChatRoom_Packet();
	~Query_User_List_In_ChatRoom_Packet();
}

class Reply_User_List_In_ChatRoom_Packet
{
private:
	const void * packet_addr;
	int user_num;
	int* user_sock;

public:
	Reply_User_List_In_ChatRoom_Packet();
	~Reply_User_List_In_ChatRoom_Packet();
}

class Update_User_List_Packet : public Packet
{
private:
	const PacketFlag::Update_User_List flag;    // init, add, del
	int user_num;
	User* user_list;
public:
	Update_User_List_Packet();
	~Update_User_List_Packet();

	int get_user_num();
	User* get_user_list();
	//int init_user_list();
	int add_user(User user);   //안에 static 변수로 count. user_num이용해 추가전에 검사도 하기.
	int del_user(int user_id);
}
class Update_ChatRoom_List_Packet : public Packet
{
private:
	const PacketFlag::Update_ChatRoom_List flag;   // init, add, del
	int chatroom_num;
	ChatRoom* chatroom_list;  //ChatRoomInfo??***************
public:
	Update_ChatRoom_List_Packet();
	~Update_ChatRoom_List_Packet();
	
}

#endif
