#ifndef __SERVER_HEADER__
#define __SERVER_HEADER__

#include <vector>
#include <queue>
#include "../common/common.h"
#include "../common/user.h"
#include "../common/chatroom.h"
#include "../common/packet.h"

typedef UserEx* UserExPtr;
typedef vector<UserExPtr> UserExPtr_v;
typedef vector<ChatRoomExPtr> ChatRoomExPtr_v;
typedef priority_queue<int, vector<int>, greater<int> > UserId_q;
typedef priority_queue<int, vector<int>, greater<int> > ChatRoomId_q;

class ServerManager
{
private:
	pthread_mutex_t mutx;

	int serv_sock;
	struct sockaddr_in serv_addr;

	//ChatRoomPtr_v default_pChatRoom_list; //처음에 서버시작시 세팅될것임.

	UserExPtr_v pUserEx_list;
	ChatRoomExPtr_v pChatroomEx_list;
	//sUserId_q remain_user_id;
	ChatRoomId_q remain_chatroom_id;
	int user_num;
	int chatroom_num;

public:
	ServerManager(/*나중에 채워 넣기!*/);
	~ServerManager();

	int server_manage_main(void* arg);
	//arg[0]= port
	
	void* client_handler(void* arg);
	//arg[0]= clnt_sock, 함수내에서 로그인 진행

	//로그인 로그아웃 패킷 처리
	UserEx* process_login_packet( Login_Packet & packet );
	int process_logout_packet( Logout_Packet & packet, UserEx * user );

	//채팅방 생성,삭제 패킷 처리
	int process_query_enter_chatroom_packet( Query_Enter_ChatRoom_Packet & packet );
	int process_query_del_chatroom_packet( Query_Del_ChatRoom_Packet & packet );

	//메세지 관련 패킷 처리
	int process_query_send_message_packet( Query_Send_Message_Packet & packet );

	//유저정보 질의 패킷 처리
	int process_query_user_info_packet( Query_User_Info_Packet & packet );
	
	//채팅방정보 질의 패킷 처리
	int process_query_chatroom_info_packet( Query_ChatRoom_Info_Packet & packet );

	//채팅방 내 유저리스트 질의 패킷 처리
	int process_query_user_list_in_chatroom_packet( Query_User_List_In_ChatRoom & packet );

	/*************************************/

	UserEx* login(Login_Packet& packet);  //여기서 유저리스트 추가하기
	int logout(UserEx* user);     //여기서 유저리스트 삭제하기

	int add_user(UserEx* user);
	UserEx* del_user(int user_id);
	
	ChatRoomEx* make_chatroom();  // ret= chatroom_id
	ChatRoomEx* del_chatroom(int chatroom_id);
	int rename_chatroom(int user_id, int chatroom_id, char chatroom_name[]);

	int invite_user(int chatroom_id, int send_user_id, int recv_user_id, char* msg, int len);
	int kick_user(int chatroom_id, int send_user_id, int recv_user_id, char* msg, int len);

	int enter_chatroom(int user_sock, int chatroom_id);
	int quit_chatroom(int user_sock, int chatroom_id);
	int quit_chatroom(int user_sock, ChatRoom* pChatroom);

	int send_msg(int chatroom_id, int send_user_id ,int recv_user_id, char* msg, int len);
}

#endif
