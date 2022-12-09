#pragma once

enum class InputType
{
	next,
	pause
};

class InputState
{
public:
	bool isTriggered(InputType type) const;
	
	bool isPressed(InputType type) const;
	
	void update();
private:
	int keypadState;			
	int lastKeypadState;		
	char keystate[256];			
	char lastKeystate[256];		
};
