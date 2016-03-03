#pragma once
#include <s3ePointer.h>
#include <map>
class Input
{
public:
    Input();
    ~Input();
    void Update();

    std::map <int, bool> TouchMap;
};

