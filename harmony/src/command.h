#include "ofMain.h"
#include "gameobject.h"
#include <stack>
#include <vector>

#define UNDO_REDO_VERBOSE 1
#define QUEUE_LIMIT 50

#pragma once
class Command {
private:
	GameObject * gobj_;
	ofTexture texture_;
	ofColor color_;
	Transform transf_;
	vector<GameObject*> child_;

public:
	Command(GameObject * gob);
	~Command();
	GameObject* getGameObject() { return gobj_; };
    void exec();
	bool operator==(const Command &cmd);
	bool operator!=(const Command &cmd);
};

class CommandHandler
{
private:
	bool isEnable = false;
    void flush_fw_command();
	void pop_back_bw();
    stack<Command*> history_bw;
    stack<Command*> history_fw;
public:
    CommandHandler();
    void add(Command * cmd);
    void undo();
    void redo();
	void enable() { isEnable = true; };
	void disable() { isEnable = false; };
	GameObject * getSelectedGameObject();
};