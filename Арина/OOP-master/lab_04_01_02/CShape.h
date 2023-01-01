#pragma once
#include "IShape.h"

class CShape :
	virtual public IShape
{
public:
	void SetOutlineColor(uint32_t const& color) override;
	uint32_t GetOutlineColor() const override;

private:
	uint32_t m_outlineColor = 000000;
};

