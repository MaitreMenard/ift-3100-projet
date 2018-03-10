#include "ofMain.h"
#include "gameobject.h"
#include <stack>
#include <vector>

#define UNDO_REDO_VERBOSE 1

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
    void exec();
};

class CommandHandler
{
private:
	bool isEnable = false;
    void flush_fw_command();
    stack<Command*> history_bw;
    stack<Command*> history_fw;
public:
    CommandHandler();
    void add(Command * cmd);
    void undo();
    void redo();
	void enable() { isEnable = true; };
	void disable() { isEnable = false; };
};