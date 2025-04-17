#pragma once
#include "CShape.h"

class CCircle : public CShape {
public:
    CCircle(int segments = 36);
    ~CCircle();
    void draw() override;
    virtual void reset() override;
    virtual void update(float dt) override;
private:
    int _segments;
};