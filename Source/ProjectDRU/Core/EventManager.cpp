#include "EventManager.h"
#include "IEventHandler.h"

void EventManager::SendEvent(IEvent * pEvent)
{
	for (auto& handler : GetInstance()._handlerList)
	{
		handler->HandleEvent(pEvent);
	}
}

void EventManager::AddHandler(IEventHandler * pHandler)
{
	GetInstance()._handlerList.Add(pHandler);
}

void EventManager::RemoveHandler(IEventHandler * pHandler)
{
	GetInstance()._handlerList.Remove(pHandler);
}
