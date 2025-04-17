#pragma once
#include "CShape.h"

class CTrapezoid : public CShape {
public:
    CTrapezoid();
    virtual ~CTrapezoid();
    virtual void draw() override;
    virtual void reset() override;
    virtual void update(float dt) override;
};