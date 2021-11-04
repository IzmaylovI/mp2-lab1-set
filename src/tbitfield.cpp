// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>
#include <algorithm>

#define BITS_IN_ONE_MEM (sizeof(TELEM)*8)

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Negative TBitField length";
	}

	BitLen = len;
	MemLen = (len - 1) / BITS_IN_ONE_MEM + 1;
	pMem = new TELEM[MemLen]{};
}

TBitField::TBitField(const TBitField& bf)// конструктор копирования
	: BitLen(bf.BitLen)
	, MemLen(bf.MemLen)
{
	pMem = new TELEM[bf.MemLen]{};

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] |= bf.pMem[i];
	}
}

TBitField::~TBitField()
{

	BitLen = 0;
	MemLen = 0;

	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw "GetMemIndex: array out of bounds";
	}
	return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw "GetMemIndex const: array out of bounds";
	}
	TELEM Mask = 1;

	int sdvig = n % BITS_IN_ONE_MEM; // количество разрядов, на которое необходимо сдвинуть 1 (<<)

	return Mask << sdvig;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во бит)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "SetBit: array out of bounds";
	}
	
	const int k = GetMemIndex(n); // номер байта pMem, в котором необходимо установить бит

	pMem[k] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
		if (n < 0 || n >= BitLen)
		{
			throw "ClrBit: array out of bounds";
		}
		
		const int k = GetMemIndex(n);
	    pMem[k] &= ~GetMemMask(n);
}

///????????
int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
	{
		throw "GetBit: array out of bounds";
	}

	const int k = GetMemIndex(n);
	
	return static_cast<bool>(pMem[k] & GetMemMask(n));
}


// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		BitLen = bf.BitLen;
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];

		for (int i = 0; i < bf.MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}

	}
	return *this; 
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int k = 1;

	if (BitLen != bf.BitLen)
	{
		k = 0;
	}
	else {
		for (int i = 0; k != 0 && i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				k = 0;
			}
		}
	}

	return k;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return (!(bf == *this ));
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	const int len_ = max(BitLen, bf.BitLen);
	TBitField sum(len_);

	for (int i = 0; i < MemLen; i++)
	{
		sum.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++)
	{
		sum.pMem[i] |= bf.pMem[i];
	}

	return sum;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	const int len_ = max(BitLen, bf.BitLen);
	TBitField diff(len_);

	for (int i = 0; i < MemLen; i++)
	{
		diff.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		diff.pMem[i] &= bf.pMem[i];
	}

	return diff;
}


TBitField TBitField::operator~(void) // отрицание
{
	TBitField denial(BitLen);

	for (int i = 0; i < BitLen; i++)
	{
		if (!GetBit(i))
		{
			denial.SetBit(i);
		}
	}

	return denial;
}

// ввод/вывод

istream& operator>>(istream& in, TBitField& bf) // ввод
{
	int i = 0;
	char ze = 0;

	while (ze != EOF && i < bf.BitLen)
	{
		ze = getchar();
		if (ze == '0')
		{
			bf.ClrBit(i++);
		}
		else
		{
			if (ze == '1')
			{
				bf.SetBit(i++);
			}
		}
	}

	return in;

}

ostream& operator<<(ostream& out, const TBitField& bf) // вывод
{

	for (int i = 0; i < bf.BitLen; i++)
	{
		if (i % 8 == 0 && i != 0)
		{
			out << " ";
		}

		out << bf.GetBit(i);

	}

	return out;

}
