/*
1. Sprawdz, czy w wyrazie wystepuje lewy nawias
    1.1. nie - zwroc dany wyraz
    1.2. tak - sprawdz czy wystepuje jeszcze inny lewy nawias. Sprawdzaj do momentu, gdy natrafi na prawy nawias.
        1.2.1. Po odnalezieniu najbardziej zagniezdzonego elementu - rozpakuj go, modyfikujac tym samym sam wyraz.
        1.2.2. Zwijaj w ten sposob funkcje rekurencyjne, otrzymujac wyraz bez zadnej lewej klamry.
*/

#include <iostream>
#include <string>
#include <cstdlib>

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

string unpackSingleBrackets(string packedString, int i)
{
    int length = packedString.length();
    int counterLength{};
    int closeBracketPosition{};
    string counter{}, stringInBrackets{}, expandedString{};

    for(;i < length; i++)
    {
        if(packedString[i] == '[')
        {
            closeBracketPosition = packedString.find(']');

            counter = findCounter(packedString, i);
            counterLength = counter.length();

            stringInBrackets = packedString.substr(i + 1, closeBracketPosition - i - 1);
            expandedString = expand(stringInBrackets, counter);

            packedString.replace(i - counterLength, closeBracketPosition - i + counterLength + 1, expandedString);
            break;
        }
    }
    return packedString;
}

void findLastLeftBracket(string &packedString, int i)
{
    string shortenedString = packedString.substr(i + 1);
    int nextRightBracket = shortenedString.find(']');
    int nextLeftBracket = shortenedString.find('[');
    int nextLeftBracketPos{};

    if(nextRightBracket > nextLeftBracket && nextLeftBracket > 0) // warunek rekurencyjny
    {
        nextLeftBracketPos = nextLeftBracket + i + 1;
        findLastLeftBracket(packedString, nextLeftBracketPos);
    }
    else
        packedString = unpackSingleBrackets(packedString, i);  //warunek podstawowy
}

string unpack(string &packedString)
{
    int openBracket = packedString.find('[');

    if(openBracket > 0)
    {
        for(size_t i = 0; i < packedString.length(); i++)
        {
            if(packedString[i] == '[')
            {
                findLastLeftBracket(packedString, i);
                i = 0;
            }
            if(i == packedString.length() - 1)
                return packedString;
        }
    }
    else
        return packedString;
}

int main()
{
    //string packedString = "aaaabb";
    //string packedString = "aaaa3[t]bb";
    //string packedString = "2[3[t]]3[w]";
    string packedString = "qwe3[ab]rty";
    //string packedString = "g2[es3[et]]";            // gesetetetesetetet
    //string packedString = "g2[eset3[de4[w]]]3[hi]"; // gesetdewwwwdewwwwdewwwwesetdewwwwdewwwwdewwwwhihihi

    cout << "Packed string: " << packedString << endl;
    cout << "Unpacked string: " << unpack(packedString) << endl;


    return 0;
}
