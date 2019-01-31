#pragma once

#include "objects/movable/Movable.h"
#include "objects/mobs/Slot.h"

namespace kv
{

class Item : public Movable
{
public:
    DECLARE_SAVEABLE(Item, Movable);
    REGISTER_CLASS_AS(Item);
    Item();

    virtual bool Attack(IdPtr<MapObject> object);

    SlotType GetItemType() const { return type_; }
    void SetItemType(SlotType type) { type_ = type; }

    qint32 GetDamage() const { return damage_; }
    void SetDamage(qint32 damage) { damage_ = damage; }
private:
    SlotType KV_SAVEABLE(type_);
    qint32 KV_SAVEABLE(damage_);
};
END_DECLARE(Item);

class Screwdriver : public Item
{
public:
    DECLARE_SAVEABLE(Screwdriver, Item);
    REGISTER_CLASS_AS(Screwdriver);
    Screwdriver();
    virtual void AfterWorldCreation() override;
};
END_DECLARE(Screwdriver);

class Wirecutters : public Item
{
public:
    DECLARE_SAVEABLE(Wirecutters, Item);
    REGISTER_CLASS_AS(Wirecutters);
    Wirecutters();
};
END_DECLARE(Wirecutters);

class Crowbar : public Item
{
public:
    DECLARE_SAVEABLE(Crowbar, Item);
    REGISTER_CLASS_AS(Crowbar);
    Crowbar();
};
END_DECLARE(Crowbar);

class Wrench : public Item
{
public:
    DECLARE_SAVEABLE(Wrench, Item);
    REGISTER_CLASS_AS(Wrench);
    Wrench();
};
END_DECLARE(Wrench);

class Multitool : public Item
{
public:
    DECLARE_SAVEABLE(Multitool, Item);
    REGISTER_CLASS_AS(Multitool);
    Multitool();
    virtual bool Attack(IdPtr<MapObject> object) override;
};
END_DECLARE(Multitool);

class BulletCasing : public Item
{
public:
    DECLARE_SAVEABLE(BulletCasing, Item);
    REGISTER_CLASS_AS(BulletCasing);
    BulletCasing();
};
END_DECLARE(BulletCasing);

}
