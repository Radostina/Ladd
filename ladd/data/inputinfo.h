#ifndef INPUTINFO_H
#define INPUTINFO_H


class InputInfo
{
public:
    InputInfo();

    bool isValid() const;

    int getId() const;
    void setId(int value);

    int getBitNumber() const;
    void setBitNumber(int value);

    bool getInitialUnsetValue() const;
    void setInitialUnsetValue(bool value);

private:
    int id;
    int bitNumber; // LSB
    bool initialUnsetValue;
};

#endif // INPUTINFO_H
