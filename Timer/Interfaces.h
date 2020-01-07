#pragma once


#include<memory>
#include<list>
#include<string>

using namespace std;

# define PURE	=0 //for pure virtual functions
# define interface	struct //c,c++ does n't have keyword for interface
#define DEFAULT_DESTRUCTOR(type) virtual ~##type##() = default;
