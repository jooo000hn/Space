#pragma once 
#include "stdafx.h"
#include "Game/Object/Include/ObjectManager.h"
namespace SpaceGameEngine
{
	struct Message					//消息
	{
		std::string m_ReceiverName;		//接受器的名称
		int m_Content;					//消息的内容		
		Message();
		Message(int c);
		Message(const std::string& name, int c) :
			m_ReceiverName(name), m_Content(c)
		{}
	};

	class Receiver						//接收器
	{
	public:
		void ReceiveMessage(const Message& message);//接受消息
		void ReceiveMessage(int message);			//接受消息
		int TakeOutMessage();					//取出消息
		bool IfEmpty();								//是否为空
		int Size();									//获取队列的大小
		void Clear();								//清空队列
		bool IfHaveMessage(int c);					//是否含有某个消息
	private:
		std::queue<int> m_MessageQueue;
	};

	class MessageManager				//消息管理器
	{
	public:
		MessageManager();
		~MessageManager();
		void Release();

		void SetAsMainManager();
		static MessageManager* GetMainManager();

		void PushMessage(const Message& message);
		void Run();

		template<typename T>
		struct NewReceiver
		{
			Receiver* operator () (const std::string& name)
			{
				if (sm_pThis == nullptr)
				{
					ThrowError(L"需要先定义一个消息管理器");
					return nullptr;
				}
				if (m_Receivers.find(name) != m_Receivers.end())
				{
					ThrowError(L"已存在该接收器");
					return nullptr;
				}
				Receiver* pointer = new T();
				sm_pThis->m_Receivers.insert(make_pair(name, pointer));
				return pointer;
			}
		};
		NewReceiver<Receiver> NewBaseReceiver;
		bool DeleteReceiver(const std::string& name);
		bool DeleteReceiver(Receiver* pr);
		bool AddReceiver(const std::string& name, Receiver* pr);
		Receiver* FindReceiver(const std::string& name);
		std::string FindReceiverName(Receiver* pr);
		void SetMaxSize(int i);
	private:
		static MessageManager* sm_pThis;
		std::map<std::string, Receiver*> m_Receivers;
		std::queue<Message> m_GlobalMessageQueue;
		int m_MaxSize;
	};

	class Sender						//发送器
	{
	public:
		Sender();
		Sender(const std::string& name);
		~Sender();

		void ProduceMessage(const Message& message);			//产生并发送消息
		void ProduceMessage(const std::string& name, int c);	//产生并发送消息
		void ProduceMessage(MessageManager& manager, const Message& message);	//产生并发送消息
		void ProduceMessages(const std::vector<std::string>& names, int c);		//发送同一消息给多个对象
		void ProduceMessages(MessageManager& manager, const std::vector<std::string>& names, int c);	//发送同一消息给多个对象
		void FastProduceMessage(Receiver& r, const Message& message);			//快速发送消息（不经过管理器队列）：不推荐使用

		void DebugLog(const Message& message);

		void SetName(const std::string& name);
		std::string GetName();
	private:
		std::string m_Name;
	};
}