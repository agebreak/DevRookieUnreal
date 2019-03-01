#pragma once
#include "CoreMinimal.h"
#include "IEvent.h"

class IEventHandler;

class EventManager
{
public:	
	static void SendEvent(IEvent* pEvent);

	static void AddHandler(IEventHandler* pHandler);
	static void RemoveHandler(IEventHandler* pHandler);

protected:
	static EventManager& GetInstance()
	{
		static EventManager instance; 
		return instance;
	}

	TArray<class IEventHandler*> _handlerList;
};