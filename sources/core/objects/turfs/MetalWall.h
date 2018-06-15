#pragma once

#include "Turf.h"
#include <bitset>
#include <array>

namespace kv
{

const std::array<Dir, 4> WALL_PROCESSING_DIRS = {Dir::NORTH, Dir::SOUTH, Dir::WEST, Dir::EAST};

class MetalWall : public Turf
{
public:
    DECLARE_SAVEABLE(MetalWall, Turf);
    REGISTER_CLASS_AS(MetalWall);

    MetalWall();

    virtual void AttackBy(IdPtr<Item> item) override;
    virtual void AfterWorldCreation() override;
    virtual void Delete() override;
protected:
    std::bitset<4> KV_SAVEABLE(current_state_);
    QString KV_SAVEABLE(base_state_);
private:
    void UpdateState();
    void NotifyNeighborhood(const Dir dir);
    void CheckNeighborhood(const Dir dir);
    void SetBitByDirection(const Dir dir, const bool value);
};
END_DECLARE(MetalWall);

class ReinforcedWall : public MetalWall
{
public:
    DECLARE_SAVEABLE(ReinforcedWall, MetalWall);
    REGISTER_CLASS_AS(ReinforcedWall);
    ReinforcedWall();

    virtual void AttackBy(IdPtr<Item> item) override;
};
END_DECLARE(ReinforcedWall);

}
