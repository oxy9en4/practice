// FileIO.h
#pragma once
#include "LinkedList.h"

class FileIO {
public:
    static bool save(const std::string& filename, LinkedList& list);
    static bool load(const std::string& filename, LinkedList& list);
};
