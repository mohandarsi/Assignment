#pragma once


# define PURE	=0 //for pure virtual functions
# define interface	struct //c,c++ does n't have keyword for interface
#define DEFAULT_DESTRUCTOR(type) virtual ~##type##() = default;
