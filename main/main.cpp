#include <iostream>
#include <stdio.h>
#include <cstdio>
#include "Classes.h"
#include "Functions.h"
using namespace std;
#define LINE_LENGTH 500 // max line lenght 

enum state {
    state_selector,
    state_attribute,
    state_commands

};

int main()
{
    state currentState = state_selector;
    Selector* headSelector = NULL;
    Attribute* headAttribute = NULL;
    bool headSelectorExist = false;
    bool headAttributeExist = false;
    int i = 0;
    int k = 0;
    char mode;
    int number;
    int numberJ;
    int result;
    char line[LINE_LENGTH];
    char delimiter;
    char* trimmedSecondLine;
    doubleLinkedList* doubleLinkedListHead = new doubleLinkedList();
    while (true)
    {
        switch (currentState)
        {
        case state_selector:
        {
            if (scanf_s("%[^,{?]", line, sizeof(line)) == EOF) return 0;
            scanf_s("%c", &delimiter, 1);
            switch (delimiter)
            {

            //adding selectors
            case ',':
            {
                if (headSelectorExist == false)
                {
                    headSelector = createSelectorHead(line);
                    headSelectorExist = true;
                }
                else
                    add_selector(&headSelector, line);
                break;
            }

            //adding last selector
            case '{':
            {
                if (headSelectorExist == false)
                {
                    headSelector = createSelectorHead(line);
                    headSelectorExist = true;
                }
                else
                    add_selector(&headSelector, line);
                currentState = state_attribute;
                headSelectorExist = false;
                break;
            }

            //entering state commands
            case '?':
            {
                if (startOfCommands())
                    currentState = state_commands;
                break;
            }
            }
            break;
        }
        case state_attribute:
        {
            scanf_s("%[^;}?]", line, sizeof(line));
            scanf_s("%c", &delimiter, 1);
            switch (delimiter)
            {

            //adding new attribute
            case ';':
            {
                i = 0;
                while (line[i] != ':')
                    i++;
                line[i] = '\0';
                k = i + 1;

                char* name = line;
                char* value = line + k;

                if (headAttributeExist == false)
                {
                    headAttribute = createAttributeHead(name, value);
                    headAttributeExist = true;
                }
                else
                    add_attribute(&headAttribute, name, value);
                break;
            }

            //adding last sttribute
            case '}':
            {
                Section newSection;
                newSection.SelectorHead = headSelector;
                newSection.AttributeHead = headAttribute;
                doubleLinkedListHead->newTab(newSection);
                currentState = state_selector;
                headAttributeExist = false;
                break;
            }
            case '?':
            {
                if (startOfCommands())
                    currentState = state_commands;
                break;
            }
            }
            break;
        }
        case state_commands:
        {
            if (scanf_s(" %[^?,*]", line, sizeof(line)) == EOF) return 0;
            scanf_s("%c", &delimiter, 1);
            switch (delimiter)
            {
            case '*':
            {
                if (endOfCommands())
                    currentState = state_selector;
                break;
            }

            //printing the number of CSS sections
            case '?':
            {
                cout << "? == " << countSections(doubleLinkedListHead) << endl;
                break;
            }

            case ',':
            {
                char* trimmedLine = trim(line);
                bool isLineNumber = IsItNumber(trimmedLine);
                if (isLineNumber)
                    number = atoi(trimmedLine);

                scanf_s("%c,", &mode, 1);
                switch (mode) {
                case'S':
                    scanf_s("%[^?\n]", line, sizeof(line));
                    scanf_s("%c", &delimiter, 1);

                    // printing the total number of occurrences of selector with exact name
                    if (!isLineNumber) {
                        countNamedSelectors(trimmedLine, doubleLinkedListHead);
                    }

                    //cprint the number of selectors for exact section
                    if ((delimiter == '?') && (isLineNumber)) {
                        result = numberOfSelectors(number - 1, doubleLinkedListHead);
                        if (result != -1)
                            cout << number << "," << mode << "," << delimiter << " == " << result << endl;
                    }

                    //print the exact selector for the exact block
                    if ((delimiter == '\n') && (isLineNumber)) {
                        trimmedSecondLine = trim(line);
                        if (IsItNumber(trimmedSecondLine)) {
                            numberJ = atoi(trimmedSecondLine);
                            nameOfSelector(number - 1, numberJ - 1, doubleLinkedListHead);
                            free(trimmedSecondLine);
                        }
                    }
                    break;
                case'A':
                    scanf_s("%[^?\n]", line, sizeof(line));
                    scanf_s("%c", &delimiter, 1);

                    //print the number of attributes for exact section
                    if ((delimiter == '?') && (isLineNumber)) {
                        result = numberOfAttributes(number - 1, doubleLinkedListHead);
                        if (result != 0)
                            cout << number << ",A,? == " << result << endl;
                    }

                    //print the value of the attribute with the exact name
                    if ((delimiter == '\n') && (IsItNumber(trimmedLine))) {
                        trimmedSecondLine = trim(line);
                        printValuesForAttributeName(number - 1, doubleLinkedListHead, trimmedSecondLine);
                        free(trimmedSecondLine);
                    }

                    //- print the total number of occurrences of attribute with exact name
                    if ((delimiter == '?') && (!isLineNumber)) {
                        numberOfAttributesWithName(trimmedLine, doubleLinkedListHead);
                    }

                    break;
                case'E':
                    //print the value of the attribute with exact named for the exact selector
                    scanf_s("%[^\n]", line, sizeof(line));
                    trimmedSecondLine = trim(line);
                    ValuesForExactAttributes(trimmedLine, trimmedSecondLine, doubleLinkedListHead);
                    free(trimmedSecondLine);
                    break;
                case'D':
                    scanf_s("%[^*\n]", line, sizeof(line));
                    scanf_s("%c", &delimiter, 1);
                    trimmedSecondLine = trim(line);

                    //remove the entire section
                    if ((delimiter == '*') && (IsItNumber(trimmedLine))) {
                        if (number <= countSections(doubleLinkedListHead)) {
                            deleteSection(number - 1, doubleLinkedListHead, &doubleLinkedListHead);
                            cout << number << ",D,* == deleted" << endl;
                        }

                    }

                    // remove the attribute with exact name
                    if ((delimiter == '\n') && (IsItNumber(trimmedLine))) {
                        deleteAttribute(number - 1, trimmedSecondLine, doubleLinkedListHead, &doubleLinkedListHead);

                    }
                    free(trimmedSecondLine);
                    break;
                default:
                    scanf_s("%[^\n]", line, sizeof(line));
                    break;
                }
                free(trimmedLine);
                break;
            }

            }
            break;
        }
        }
    }
    return 0;
}