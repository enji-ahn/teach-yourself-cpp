class Command {
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

class JumpCommand : public Command {
public:
	virtual void execute() {
		::jump();
	}
};

class FireCommand : public Command {
public:
	virtual void execute() {
		::fireGun();
	}
};

class SwapWeaponCommand : public Command {
public:
	virtual void execute() {
		::swapWeapon();
	}
};

class LurchCommand : public Command {
public:
	virtual void execute() {
		::lurchIneffectively();
	}
};

class PatternedInputHandler {
public:
	void handleInput();
	void assignButton(enum BUTTON b, Command* cmd) {
		switch (b) {
		case BUTTON::A: buttonA_ = cmd; break;
		case BUTTON::B: buttonB_ = cmd; break;
		case BUTTON::X: buttonX_ = cmd; break;
		case BUTTON::Y: buttonY_ = cmd; break;
		}
	}
private:
	bool isPressed(enum BUTTON b) {
		static std::map<enum BUTTON, bool/*used*/> m = {
		{BUTTON::A, false},
		{BUTTON::B, false},
		{BUTTON::X, false},
		{BUTTON::Y, false},
		};

		return ::isPressed(m, b);
	}

	Command* buttonA_;
	Command* buttonB_;
	Command* buttonX_;
	Command* buttonY_;
};