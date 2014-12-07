#include "server.h"

int ServerManager::server_manage_main(void* arg)
{
	const int PORT = atoi(arg[0]);
	const int backlog = 40;

	pthread_mutex_init(&mutx, NULL);
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);

	if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
		error_handling("bind() error!!");

	if( listen(serv_sock, backlog) == -1 )
		error_handling("listen() error!!");

	//로비 채팅방 만드는 코드 여기에 추가!!!!

	while(1)
	{
		int clnt_sock;
		struct sockaddr_in clnt_addr;
		int clnt_addr_sz = sizeof(clnt_addr);

		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_sz);
		pthread_create(&t_id, NULL, client_handler, (void*)&clnt_sock);
		pthread_detach(t_id);

		printf("Connected client IP: %s\n", inet_ntoa(clnt_addr.sin_addr));
	}

	close(serv_sock);

	return 0;
}

void* ServerManager::client_handler(void* arg)
{
	const int clnt_sock = atoi(arg[0]);
	int packet_sz;
	int read_sz;
	char* buffer;
	UserEx* user;
	bool is_login = false;

	bool is_exit = false;

	while(!is_exit)
	{
		read_sz = 0;
		while(read_sz < sizeof(int))
			read_sz += read(clnt_sock, (char*)&packet_sz+read_sz, sizeof(packet_sz)-read_sz);
		
		buffer = (char*)malloc(packet_sz);
		*(int*)buffer = packet_sz;

		while(read_sz < packet_sz)
			read_sz += read(clnt_sock, buffer, packet_sz-read_sz);

		Packet header(buffer);

		switch( header.get_flag() )
		{
			case LOGIN:
				if( is_login )
				{
					is_exit = true;
					break;
				}
				Login_Packet packet(buffer);
				if( (user=process_login_packet(packet)) == NULL )
					is_exit = true;
				else
					is_login = true;
				/*
				if( (user=login(packet)) == NULL )
					is_exit = true;
				else
					is_login = true;
				*/
				break;

			case LOGOUT:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				//if( logout(user) == -1 )
				//	is_exit = true;		
				Logout_Packet packet(buffer);
				if( process_logout_packet(packet,user) == -1 )
				{
					// 실패처리 나중에 하기.****
				}
				break;

			case QUERY_ENTER_CHATROOM:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_Enter_ChatRoom_Packet packet(buffer);
				if( process_query_enter_chatroom_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}
				break;

			case QUERY_QUIT_CHATROOM:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_Quit_ChatRoom_Packet packet(buffer);
				if( process_query_quit_chatroom_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}
				break;

				
			case QUERY_MAKE_CHATROOM:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_Make_ChatRoom_Packet p acket(buffer);
				if( process_query_make_chatroom_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}
				break;
			
			case QUERY_DEL_CHATROOM:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_Del_ChatRoom_Packet p acket(buffer);
				if( process_query_del_chatroom_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}
				break;

			case QUERY_SEND_MESSAGE:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_Send_Message_Packet packet(buffer);
				if( process_query_send_message_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}
				break;

			case QUERY_USER_INFO:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_User_Info_Packet packet(buffer);
				if( process_query_user_info_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}	
				break;

			case QUERY_CHATROOM_INFO:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_ChatRoom_Info_Packet packet(buffer);
				if( process_query_chatroom_info_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}	
				break;

			case QUERY_USER_LIST_IN_CHATROOM:
				if( !is_login )
				{
					is_exit = true;
					break;
				}
				Query_User_List_In_ChatRoom_Packet packet(buffer);
				if( process_query_user_list_in_chatroom_packet(packet) == -1 )
				{
					// 실패처리 나중에 하기.****
				}	
				break;

			default:
				// 예외 처리 나중에 하기.*****
		}

		free(buffer);
	}

	close(clnt_sock);

	return NULL;
}

UserEx* ServerManager::process_login_packet(Login_Packet& packet)
{
	return login(packet);
}

int ServerManager::process_logout_packet(Logout_Packet& packet, UserEx* user)
{
	return logout(user);
}

int ServerManager::process_query_enter_chatroom_packet( Query_Enter_ChatRoom_Packet & packet )
{

}

UserEx* ServerManager::login(Login_Packet& packet)
{
	UserEx* pUserEx = new UserEx(packet.clnt_sock, packet.nickname);

	// 유저 추가
	if( add_user(pUserEx) == -1 )
	{
		//실패 처리 나중에 하기...****
	}

	// 로비 접속
	enter_chatroom(get_clnt_sock(), pChatroomEx_list[0]->get_chatroom_id());

	return pUserEx;
}

int ServerManager::logout(UserEx* user)
{
	int user_sock = user->get_user_sock();
	ChatRoomPtr_v& pChatRoom_list = user->get_pChatRoom_list();

	for( ChatRoomPtr_v::iterator iter = pChatRoom_list.begin();
			iter != pChatRoom_list.end(); ++iter )
	{
		quit_chatroom(user_sock, *iter);
	}
}




//리퀘스트패킷과 리플라이 패킷 만들기.
