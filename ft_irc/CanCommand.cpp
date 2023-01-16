#include "CanCommand.hpp"

CanCommand::CanCommand(){

}

CanCommand::CanCommand(const CanCommand& obj) {
	*this = obj;
}

CanCommand& CanCommand::operator=(const CanCommand& obj){
	if(*this != obj){

	}
	return *this;
}

CanCommand::~CanCommand(){

}