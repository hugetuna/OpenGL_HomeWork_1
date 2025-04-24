#pragma once
#include "CShape.h"

class CStar : public CShape {
public:
    CStar(int points = 5, float outerRadius = 0.5f, float innerRadius = 0.25f);
    ~CStar();
    void draw() override;
    virtual void reset() override;
    virtual void update(float dt) override;
};
