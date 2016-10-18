#ifndef OUPUTINFO_H
#define OUPUTINFO_H


class OutputInfo
{
public:
    OutputInfo();

    int getId() const;
    void setId(int value);

    int getBitNumber() const;
    void setBitNumber(int value);

private:
    int id;
    int bitNumber;
};

#endif // OUPUTINFO_H

// TO DO remove
