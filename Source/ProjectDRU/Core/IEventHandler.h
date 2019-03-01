#pragma once
#include "IEvent.h"
#include <functional>
#include "CoreMinimal.h"

#define BIND_FUNC(id, func) Bind(id, [](IEvent* pEvent){func(pEvent);} )
using EventFunc = std::function<void(IEvent*)>;

class IEventHandler
{
public:
	IEventHandler();
	~IEventHandler();

	void Bind(EventID id, EventFunc func);

	void HandleEvent(IEvent * pEvent);

protected:
	TMap<EventID, EventFunc> _HandlerFunc;

private:
};


