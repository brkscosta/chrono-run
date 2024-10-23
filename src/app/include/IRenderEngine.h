#pragma once

namespace app::ui::engine {
class IRenderEngine
{
public:
    virtual ~IRenderEngine() = default;

    virtual bool init() = 0;
    virtual void run() = 0;
    virtual void changeFrameRateLimit(int frameRateLimit) = 0;
};
}   // namespace app::ui::engine
