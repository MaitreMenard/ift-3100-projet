#include "command.h"

/***** COMMANDHANDLER *****/

CommandHandler::CommandHandler()
{}

CommandHandler::~CommandHandler()
{
	flush_stack(&history_bw);
	flush_stack(&history_fw);
}

void CommandHandler::flush_stack(stack<Command*> * pStack)
{
    while (!pStack->empty())
    {
		delete pStack->top();
		pStack->pop();
    }
}

void CommandHandler::add(Command * cmd)
{
    if (isEnable && (history_bw.empty() || *history_bw.top() != *cmd))
    {
        if (UNDO_REDO_VERBOSE) cout << "Cmd add" << endl;
        flush_stack(&history_fw);
        history_bw.push(cmd);
        history_bw.top()->exec();
    }
    // Limit stack length
    if (history_bw.size() > QUEUE_LIMIT)
        pop_back_bw();
}

void CommandHandler::undo()
{
    if (!history_bw.empty())
    {
        if (UNDO_REDO_VERBOSE) cout << "Cmd undo" << endl;
        history_fw.push(history_bw.top());
        history_bw.pop();
        if (!history_bw.empty())
            history_bw.top()->exec();
    }
}

void CommandHandler::redo()
{
    if (!history_fw.empty())
    {
        if (UNDO_REDO_VERBOSE) cout << "Cmd redo" << endl;
        history_bw.push(history_fw.top());
        history_fw.pop();
        history_bw.top()->exec();
    }
}

void CommandHandler::pop_back_bw()
{
    stack<Command*> temp_stack;
    // unstack to get last object
    while (!history_bw.empty())
    {
        temp_stack.push(history_bw.top());
        history_bw.pop();
    }
    // pop last object
	delete temp_stack.top();
    temp_stack.pop();
    // restack rest of objects
    while (!temp_stack.empty())
    {
        history_bw.push(temp_stack.top());
        temp_stack.pop();
    }
}

GameObject * CommandHandler::getSelectedGameObject()
{
    return history_bw.empty() ? __nullptr : history_bw.top()->getGameObject();
};

/***** COMMAND *****/
Command::Command(GameObject * gobj)
{
    gobj_ = gobj;
    transf_ = Transform(gobj->getTransform());
}

Command::~Command()
{}

void Command::exec()
{
    gobj_->setTransform(transf_);
}

bool Command::operator==(const Command &cmd)
{
    // TODO check children / id GameObject
    if (gobj_ != cmd.gobj_) return false;
    if (transf_ != cmd.transf_) return false;
    return true;
}

bool Command::operator!=(const Command &cmd)
{
    return !(*this == cmd);
}
