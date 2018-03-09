#include "command.h"

/***** COMMANDHANDLER *****/

CommandHandler::CommandHandler(){
}

void CommandHandler::flush_fw_command() {
	while (!history_fw.empty()){
		history_fw.pop();
	}
}

void CommandHandler::add(Command * cmd) {
	if(isEnable){
		cout << "add" << endl;
		flush_fw_command();
		history_bw.push(cmd);
		history_bw.top()->exec();
	}
}

void CommandHandler::undo() {
    if(!history_bw.empty()){
		cout << "undo" << endl;
		history_fw.push(history_bw.top());
		history_bw.pop();
		if(!history_bw.empty())
			history_bw.top()->exec();
    }
}

void CommandHandler::redo() {
    if (!history_fw.empty()) {
		cout << "redo" << endl;
		history_bw.push(history_fw.top());
		history_fw.pop();
		history_bw.top()->exec();
    }
}

/***** COMMAND *****/
Command::Command(GameObject * gobj){
	gobj_ = gobj;
	color_ = ofColor(gobj->getColor());
	transf_ = Transform(gobj->getTransform());
}

Command::~Command() {
}

void Command::exec() {
	gobj_->setTransform(transf_);
	gobj_->setColor(color_);
}

