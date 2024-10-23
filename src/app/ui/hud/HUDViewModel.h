#pragma once
#include "include/IHUDViewModel.h"

namespace app::ui::viewmodels {
class HUDViewModel : public IHUDViewModel
{
public:
    HUDViewModel();
    ~HUDViewModel() override = default;
};
}   // namespace app::ui::viewmodels