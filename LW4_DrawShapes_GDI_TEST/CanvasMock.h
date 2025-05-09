#pragma once
#include <vector>
#include <string>
#include <memory>

struct CanvasLog
{
    std::vector<std::string> calls;
};

struct CanvasMock
{
    static std::shared_ptr<CanvasLog> instance;

    static void Reset()
    {
        instance = std::make_shared<CanvasLog>();
    }
};
