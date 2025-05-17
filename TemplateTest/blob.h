#pragma once
class blob
{
public:
	blob(int value);
	~blob();
	blob(const blob& otherBlob);
	blob& operator=(const blob& otherblob);
	blob(blob&& otherBlob) noexcept;
	blob& operator=(blob&& otherBlob) noexcept;
	
	blob operator+(const blob& otherBlob);
	blob& operator+=(const blob& otherBlob);
	blob operator-(const blob& otherBlob);
	blob& operator-=(const blob& otherBlob);
	blob operator++(int);
	blob& operator++();
	blob operator--(int);
	blob& operator--();

	blob operator+(int value);
	blob& operator +=(int value);
	blob operator-(int value);
	blob& operator-=(int value);

private:
	int  m_Value;
};

