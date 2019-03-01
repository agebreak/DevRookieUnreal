#include "IEventHandler.h"
#include "EventManager.h"

IEventHandler::IEventHandler()
{
	EventManager::AddHandler(this);
}

IEventHandler::~IEventHandler()
{
	EventManager::RemoveHandler(this);
}

void IEventHandler::Bind(EventID id, EventFunc func)
{
	_HandlerFunc.Emplace(id, func);
}

void IEventHandler::HandleEvent(IEvent * pEvent)
{
	if (_HandlerFunc.Contains(pEvent->id))
	{
		_HandlerFunc[pEvent->id](pEvent);
	}
}