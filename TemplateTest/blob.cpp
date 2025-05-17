#include "pch.h"
#include "blob.h"

blob::blob(int value)
	:m_Value(value)
{
}

blob::~blob()
{
}

blob::blob(const blob& otherBlob)
	:m_Value(otherBlob.m_Value)
{
}

blob& blob::operator=(const blob& otherblob)
{
	this->m_Value = otherblob.m_Value;
	return *this;
}



blob::blob(blob&& otherBlob) noexcept
	:m_Value(otherBlob.m_Value)
{
	otherBlob.m_Value = 0;
}

blob& blob::operator=(blob&& otherBlob) noexcept
{
	this->m_Value = otherBlob.m_Value;
	otherBlob.m_Value = 0;
	return *this;
}


blob blob::operator+(const blob& otherBlob)
{
	return blob(m_Value + otherBlob.m_Value);
}

blob& blob::operator+=(const blob& otherBlob)
{
	m_Value += otherBlob.m_Value;
	return *this;
}

blob blob::operator-(const blob& otherBlob)
{
	return blob(m_Value - otherBlob.m_Value);
}

blob& blob::operator-=(const blob& otherBlob)
{
	m_Value -= otherBlob.m_Value;
	return *this;
}

blob blob::operator++(int)
{
	m_Value++;
	return *this;
}

blob& blob::operator++()
{
	++m_Value;
	return *this;
}

blob blob::operator--(int)
{
	m_Value--;
	return *this;
}

blob& blob::operator--()
{
	--m_Value;
	return *this;
}

blob blob::operator+(int value)
{
	return blob(m_Value + value);
}

blob& blob::operator+=(int value)
{
	m_Value += value;
	return *this;
}

blob blob::operator-(int value)
{
	return blob(m_Value - value);
}

blob& blob::operator-=(int value)
{
	m_Value -= value;
	return *this;
}
