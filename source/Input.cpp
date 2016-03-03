#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

void Input::Update()
{
    s3ePointerUpdate();
    for (size_t i = 0; i < S3E_POINTER_TOUCH_MAX; i++)
    {
        if (s3ePointerGetTouchState(i) == S3E_POINTER_STATE_DOWN)
        {
            TouchMap[i] = true;
        }
        else if(s3ePointerGetTouchState(i) == S3E_POINTER_STATE_RELEASED)
        {
            TouchMap[i] = false;
        }
    }
}
