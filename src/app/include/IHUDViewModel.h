#pragma once

namespace app::ui::viewmodels {
class IHUDViewModel
{
public:
    virtual ~IHUDViewModel() = default;

    virtual void update() = 0;
    virtual void render() = 0;
};
}   // namespace app::ui::viewmodels
