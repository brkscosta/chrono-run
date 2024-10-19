#pragma once

namespace domain::usecases {

class UpdatePlayerPosition
{
public:
    UpdatePlayerPosition();
    ~UpdatePlayerPosition();
    void execute();
};
}   // namespace domain::usecases