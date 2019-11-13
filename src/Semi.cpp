#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
//#include "../header/RBase.h"
//#include "../header/Command.h"
//
//void Command::parse(std::string toParse){
//	char *cstr = &toParse[0];
//	char** args = new char*[arguments.size()+1];
//
//	    for (unsigned i = 0; i < arguments.size(); i++) {
//	            args[i] = arguments.at(i);
//	                }
//	                    args[arguments.size()] = NULL;	args[0] = cstr;
//
//	                    }
//
//
//	                    Command::Command(std::string com){
//	                        this->executable = com;
//	                            this->failed = false;
//	                                this->followedByAND = false;
//	                                    this->followedByOR = false;
//	                                        parse(executable); 
//	                                        }
//
//	                                        void Command::Run(){
//	                                        	cout << "running: " << this->executable << endl;
//
//	                                        	}
//
