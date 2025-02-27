// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp)
    : BitField(mp)
    , MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet& s)
    : MaxPower(s.MaxPower)
    , BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf)
    : MaxPower(bf.GetLength())
    , BitField(bf)
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem < 0) || (Elem >= MaxPower))
    {
        throw "IsMember: array out of bounds";
    }

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
        if ((Elem < 0) || (Elem >= MaxPower))
        {
            throw "InsElem: array out of bounds";
        }
    

    if (!IsMember(Elem))
    {
        BitField.SetBit(Elem);
    }
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem < 0) || (Elem >= MaxPower))
    {
        throw "DelElem: array out of bounds";
    }

    if (IsMember(Elem))
    {
        BitField.ClrBit(Elem);
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.MaxPower;

    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return ((MaxPower == s.MaxPower) && (BitField == s.BitField));
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return (!(*this == s));
}

TSet TSet::operator+(const TSet& s) // объединение
{
    return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "operator+: array out of bounds";
    }

    TSet res(*this);
    res.InsElem(Elem);

    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементов
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "operator-: array out of bounds";
    }

    TSet res(*this);
    res.DelElem(Elem);

    return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    return TSet(~BitField);
}

// перегрузка ввода/вывода

istream& operator>>(istream& in, TSet& s) // ввод
{
    int i = 1;

    while (i > 0 && i < s.MaxPower)
    {
        in >> i;
        s.InsElem(i);
    }

    return in;
}

ostream& operator<<(ostream& out, const TSet& s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMemBer(i))
        {
            cout << i;
        }
        if (i + 1 < s.MaxPower)
        {
            cout << " ";
        }
    }

    return out;
}
