#include "Gun.h"
#include "Tile.h"

Gun::Gun(size_t id) : Item(id)
{
    SetSprite("icons/guns.dmi");
    ammunition_ = 1;
    max_ammunition_ = 1;
}

bool Gun::UseAmmo()
{
    if (ammunition_ <= 0)
    {
        ammunition_ = 0;
        return false;
    }
    --ammunition_;
    return true;
}

void Gun::ShootImpl(VDir target, const std::string& sound, const std::string& projectile_type, const std::string& casing_type)
{
    id_ptr_on<CubeTile> tile = GetOwner()->GetOwner();
    if (tile.valid())
    {	
        if (UseAmmo())
        { 
            auto projectile = Create<Projectile>(projectile_type,tile);
            projectile->MakeMovementPattern(target,GetOwner());
            PlaySoundIfVisible(sound,tile.ret_id());
            if(!casing_type.empty())
            {
                Dir dir = GetRand() % 4;
                id_ptr_on<Item> bc =Create<Item>(casing_type,tile.ret_id());
                bc->Rotate(dir);
            } 	
        }
        else
        {
            PlaySoundIfVisible("empty.ogg",tile.ret_id()); 
            // the *click* text from ss13
        }
    }	
}

void Gun::Shoot(VDir target)
{
}

bool Gun::AddAmmo()
{
    if (ammunition_ < max_ammunition_)
    {
        ++ammunition_;
        return true;
    }
    return false;
}
void Gun::AttackBy(id_ptr_on<Item> item)
{
    if (id_ptr_on<AmmunitionBox> box = item)
    {
        if(box->CheckBullets())
        {
            if(AddAmmo())
            {
		        box->RemoveBullet();
                return;
            }
        }
        // message which tells the player that the box is empty 
    }
}

bool Gun::Targetable(id_ptr_on<IOnMapBase> item)
{
    if (!item.valid())
    {
        return false;
    }

    if (!item->GetOwner())
    {
        return false;
    }

    id_ptr_on<CubeTile> cube_tile = item->GetOwner();
    if (!cube_tile.valid())
    {
        return false;
    }

    return true;
}

VDir Gun::TargetTileLoc(id_ptr_on<IOnMapBase> item) const
{
    id_ptr_on<CubeTile> cube_tile = item->GetOwner();
    VDir f;
    f.x = (cube_tile->GetX() - GetOwner()->GetX());
    f.y = (cube_tile->GetY() - GetOwner()->GetY());
    f.z = 0;
    return f;
}
