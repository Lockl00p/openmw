#ifndef OPENMW_COMPONENTS_NIF_PHYSICS_HPP
#define OPENMW_COMPONENTS_NIF_PHYSICS_HPP

#include "base.hpp"

// This header contains certain record definitions
// specific to Bethesda implementation of Havok physics
namespace Nif
{

// Generic collision object
struct NiCollisionObject : public Record
{
    // The node that references this object
    NodePtr target;

    void read(NIFStream *nif) override
    {
        target.read(nif);
    }
    void post(NIFFile *nif) override
    {
        target.post(nif);
    }
};

// Bethesda Havok-specific collision object
struct bhkCollisionObject : public NiCollisionObject
{
    unsigned short flags;
    CollisionBodyPtr body;

    void read(NIFStream *nif) override;
    void post(NIFFile *nif) override
    {
        NiCollisionObject::post(nif);
        body.post(nif);
    }
};


// Abstract Havok shape info record
struct bhkWorldObject : public Record
{
    bhkShapePtr shape;
    unsigned int flags; // Havok layer type, collision filter flags and group
    struct WorldObjectInfo
    {
        unsigned char phaseType;
        unsigned int data;
        unsigned int size;
        unsigned int capacityAndFlags;
    };
    WorldObjectInfo worldObjectInfo;
    void read(NIFStream *nif) override;
    void post(NIFFile *nif) override;
};

struct bhkShape : public Record {};

} // Namespace
#endif