#pragma once

template<typename T>
class FAttributeData;



template<>
class FAttributeData<float>
{
public:
	FAttributeData& operator+=(float Value);
	FAttributeData& operator+=(const FAttributeData& Value);

	float GetBaseValue();

	void SetBaseValue(float Value);

protected:
	float BaseValue;
};

template<>
class FAttributeData<bool>
{

};