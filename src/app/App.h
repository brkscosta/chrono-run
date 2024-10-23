#pragma once

#include <memory>

namespace app::ui::engine {
class RenderEngine;
}

namespace app {

struct AppDependencies
{
    virtual ~AppDependencies() = default;
    virtual void start() = 0;
};

class App : public AppDependencies
{
public:
    App();
    ~App() override = default;

    void start() override;

private:
    void init();

    std::shared_ptr<app::ui::engine::RenderEngine> m_renderEngine;
};
}   // namespace app