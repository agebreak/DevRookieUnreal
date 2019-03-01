#pragma once

#define MAKE_ID(class, _id) class() {id = _id;}

enum class EventID
{
	ID_NULL = 0,
	CURSOR_PICKED,
};

struct IEvent
{
	EventID id;
};

struct Event_CursorPicked : IEvent
{
	MAKE_ID(Event_CursorPicked, EventID::CURSOR_PICKED);
	
	FVector pos;
};

