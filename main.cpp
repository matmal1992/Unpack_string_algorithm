#include <iostream>
#include <vector>
#include <string>

using namespace std;

string expand(string stringInBrackets, string counter)
{
    int convertedCounter = stoi(counter);
    string expandedString{};

    for(int i = 0; i < convertedCounter; i++)
        expandedString += stringInBrackets;

    return expandedString;
}

string findCounter(string packedString, int position)
{
    string counter = "";

    while(isdigit(packedString[position - 1]) && position >= 1)
    {
        counter = packedString[position - 1] + counter;
        position--;

        if(position < 1)
            break;
    }
    return counter;
}

string unpack(string packedString)
{
    int length = packedString.length();
    int counterLength{};
    int closeBracketPosition{};
    string counter{}, stringInBrackets{}, expandedString{};

    for(int i = 0; i < length; i++)
    {
        if(packedString[i] == '[')
        {
            closeBracketPosition = packedString.find(']');

            counter = findCounter(packedString, i);
            counterLength = counter.length();

            stringInBrackets = packedString.substr(i + 1, closeBracketPosition - i - 1);
            expandedString = expand(stringInBrackets, counter);

            packedString.replace(i - counterLength, closeBracketPosition - i + counterLength + 1, expandedString);
        }
    }
    return packedString;
}

int main()
{
    string packedString = "2[a]3[bc]d";

    cout << unpack(packedString);
    return 0;
}
