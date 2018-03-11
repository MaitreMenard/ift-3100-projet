#include "ofMain.h"
#include "gameobject.h"
#include <stack>
#include <vector>

#define UNDO_REDO_VERBOSE 0
#define QUEUE_LIMIT 500

#pragma once
class Command
{
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
	void flush_stack(stack<Command*> * pStack);
    void pop_back_bw();
    stack<Command*> history_bw;
    stack<Command*> history_fw;
public:
    CommandHandler();
	~CommandHandler();
    void add(Command * cmd);
    void undo();
    void redo();
    void enable() { isEnable = true; };
    void disable() { isEnable = false; };
    GameObject * getSelectedGameObject();
};