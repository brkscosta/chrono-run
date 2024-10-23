#pragma once
#include "include/IHUDView.h"

namespace app::ui::views {
class HUDView : public IHUDView
{
public:
    HUDView();
    ~HUDView() override = default;
    void render() override;
    void update() override;
};
}   // namespace app::ui::views