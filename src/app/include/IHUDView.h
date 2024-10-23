#pragma once

namespace app::ui::views {
class IHUDView
{
public:
    virtual ~IHUDView() = default;

    virtual void render() = 0;
    virtual void update() = 0;
};
}   // namespace app::ui::views