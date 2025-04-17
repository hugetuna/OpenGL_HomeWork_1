// CShield.h
#pragma once
#include "CShape.h"

class CHex : public CShape {
public:
    CHex();
    ~CHex();
    void draw() override;
    virtual void reset() override;
    virtual void update(float dt) override;
};
