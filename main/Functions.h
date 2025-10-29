#pragma once
#include<iostream>
using namespace std;

bool endOfCommands() {
    char tab[3];
    for (int i = 0; i < 3; i++) {
        tab[i] = getchar();
        if (tab[i] != '*') return false;
    }
    return true;
}
bool startOfCommands() {
    char tab[3];
    for (int i = 0; i < 3; i++) {
        tab[i] = getchar();
        if (tab[i] != '?') return false;
    }
    return true;
}

bool IsItNumber(char* tab) {
    int j = 0;
    while (tab[j] != '\0') {
        j++;
    }
    for (int i = 0; i < j; i++) {
        if (tab[i] > 57 || tab[i] < 48) {
            return false;
        }
    }
    return true;
}
bool isSpace(char ch) {
    return ((ch == ' ') || (ch == '\n') || (ch == '\t') || (ch == '\r'));
}
char* trim(const char* tab) {
    int j = 0;
    int n = 0;
    while (tab[j] != '\0') {
        j++;
    }
    n = j;
    j = 0;
    for (int i = 0; i < n; i++) {
        if (!isSpace(tab[i])) {
            break;
        }
        j++;
    }
    for (int i = n - 1; n > 0; i--) {
        if (!isSpace(tab[i])) {
            break;
        }
        n--;
    }
    if (n < j) {
        n = j;
    }
    char* temp = (char*)malloc((n - j + 1) * sizeof(char));
    for (int i = 0; i < n - j; i++) {
        temp[i] = tab[i + j];
    }
    temp[n - j] = '\0';
    return temp;
}
bool compareStrings(char* tab1, char* tab2) {
    for (int i = 0;; i++) {
        if (tab1[i] != tab2[i]) return false;
        if (tab1[i] == '\0') return true;
    }
}
Attribute* createAttributeHead(char* name, char* value) {
    Attribute* head = new Attribute();
    head->name = trim(name);
    head->value = trim(value);
    head->next = NULL;
    return head;
}
Selector* createSelectorHead(char* name) {
    Selector* head = new Selector();
    head->name = trim(name);
    head->next = NULL;
    return head;
}
void add_selector(Selector** head, const char* n) {
    Selector* newNode = new Selector();
    newNode->name = trim(n);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    else {
        Selector* last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}
void add_attribute(Attribute** head, char* n, char* v) {
    Attribute* newNode = new Attribute();
    newNode->name = trim(n);
    newNode->value = trim(v);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    else {
        Attribute* last = *head;
        while (last != NULL) {
            if (compareStrings(newNode->name, last->name)) {
                last->value = newNode->value;
              //  free(newNode);
                return;
            }
            if (last->next != NULL) last = last->next;
            else break;
        }
        last->next = newNode;
    }
}
int countSections(doubleLinkedList* doubleListHead) {
    int i = 0;
    while (true) {
        i += (doubleListHead->length);
        doubleListHead = doubleListHead->next;
        if (doubleListHead == NULL) break;
    }
    return i;
}
int countSelectors(Selector* head) {
    if (head == NULL) return 0;
    int i = 1;
    while (head->next != NULL) {
        head = head->next;
        i++;
    }
    return (i);
}
int countAttributes(Attribute* head) {
    if (head == NULL) return 0;
    int i = 1;
    while (head->next != NULL) {
        head = head->next;
        i++;
    }
    return (i);
}
Section* SerchingForSectionByIndex(int number, doubleLinkedList* doubleListHead) {
    while (doubleListHead != NULL) {
        if (number < doubleListHead->length) {
            return &doubleListHead->Tab[number];
        }
        number -= (doubleListHead->length);
        doubleListHead = doubleListHead->next;
    }
    return 0;
}
int numberOfSelectors(int number, doubleLinkedList* doubleListHead) {
    Section* tempSection = SerchingForSectionByIndex(number, doubleListHead);
    if (tempSection == NULL) return -1;
    return (countSelectors(tempSection->SelectorHead));
}
int numberOfAttributes(int number, doubleLinkedList* doubleListHead) {
    Section* tempSection = SerchingForSectionByIndex(number, doubleListHead);
    if (tempSection == NULL) return 0;
    return (countAttributes(tempSection->AttributeHead));
}


int SerchingForNumberOfTabByIndex(int number, doubleLinkedList* doubleListHead) {
    while (doubleListHead != NULL) {
        if (number < doubleListHead->length) {
            return number;
        }
        number -= (doubleListHead->length);
        doubleListHead = doubleListHead->next;
    }
    return 0;
}

doubleLinkedList* SerchingFoDoubleListElementByIndex(int number, doubleLinkedList* doubleListHead) {
    while (number > doubleListHead->length) {
        number -= (doubleListHead->length);
        doubleListHead = doubleListHead->next;
        if (doubleListHead == NULL) return 0;
    }
    return doubleListHead;
}

int nameOfSelector(int numberI, int numberJ, doubleLinkedList* doubleListHead) {
    Section* tempSection = SerchingForSectionByIndex(numberI, doubleListHead);
    if (tempSection == NULL) return 0;
    Selector* selectorTmp = tempSection->SelectorHead;
    for (int i = 0; i < numberJ; i++) {
        selectorTmp = selectorTmp->next;
        if (selectorTmp == NULL) return 0;
    }

    cout << (numberI + 1) << ",S," << (numberJ + 1) << " == " << (selectorTmp->name) << endl;
    return 0;
}


void countNamedSelectors(char* searchingName, doubleLinkedList* doubleListHead) {
    int counter = 0;
    while (doubleListHead != NULL) {
        for (int i = 0; i < doubleListHead->length; i++) {
            Selector* selectorTmp = doubleListHead->Tab[i].SelectorHead;
            while (selectorTmp != NULL) {
                if (compareStrings(searchingName, selectorTmp->name)) {
                    counter++;
                    break;
                }
                selectorTmp = selectorTmp->next;
            }

        }
        doubleListHead = doubleListHead->next;
    }
    cout << searchingName << ",S,? == " << counter << endl;;
}

void printValuesForAttributeName(int numberI, doubleLinkedList* doubleListHead, char* searchingName) {
    char *result = NULL;
    Section* sectionTmp = SerchingForSectionByIndex(numberI, doubleListHead);
    if (sectionTmp == NULL) return;
    Attribute* attributeTmp = sectionTmp->AttributeHead;
    while (attributeTmp != NULL) {
        if (compareStrings(attributeTmp->name, searchingName)) {
            result = attributeTmp->value;

        }
        attributeTmp = attributeTmp->next;

    }
    if (result)
        cout << (numberI + 1) << ",A," << searchingName << " == " << result << endl;
}
void numberOfAttributesWithName(char* searchingName, doubleLinkedList* doubleListHead) {
    int counter = 0;
    while (doubleListHead != NULL) {
        for (int i = 0; i < doubleListHead->length; i++) {
            Attribute* atributeTmp = doubleListHead->Tab[i].AttributeHead;
            while (atributeTmp != NULL) {
                if (compareStrings(searchingName, atributeTmp->name)) {
                    counter++;
                    break;
                }
                atributeTmp = atributeTmp->next;
            }

        }
        doubleListHead = doubleListHead->next;
    }
    cout << searchingName << ",A,? == " << counter << endl;
}
void ValuesForExactAttributes(char* searchingNameOfSelektor, char* searchingNameOfAttribute, doubleLinkedList* doubleListHead) {
    char *result = NULL;
    while (doubleListHead != NULL) {
        for (int i = 0; i < doubleListHead->length; i++) {
            Selector* selectorTmp = doubleListHead->Tab[i].SelectorHead;
            while (selectorTmp != NULL) {
                if (compareStrings(searchingNameOfSelektor, selectorTmp->name)) {
                    Attribute* attributeTmp = doubleListHead->Tab[i].AttributeHead;
                    while (attributeTmp != NULL) {
                        if (compareStrings(searchingNameOfAttribute, attributeTmp->name)) {
                            result = attributeTmp->value;
                            break;
                        }
                        attributeTmp = attributeTmp->next;
                    }
                    break;
                }
                selectorTmp = selectorTmp->next;
            }
        }
        doubleListHead = doubleListHead->next;
    }
    if (result)
        cout << searchingNameOfSelektor << ",E," << searchingNameOfAttribute << " == " << result << endl;
}
void repositionTab(doubleLinkedList* node, int numberOfTab, int numberOfSection) {

    for (int i = numberOfTab; i < numberOfSection - 1; i++) {
        node->Tab[i] = node->Tab[i + 1];
    }
}
void freeSelectorsList(Selector* head) {
    Selector* temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}
void freeAttributeList(Attribute* head) {
    Attribute* temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}

void deleteSection(int number, doubleLinkedList* doubleListHead, doubleLinkedList** doubleListHeadPtr) {

    doubleLinkedList* Node = SerchingFoDoubleListElementByIndex(number, doubleListHead);
    int numberOfTab = SerchingForNumberOfTabByIndex(number, doubleListHead);
    // int numberOfSections = countSections(Node);

    freeSelectorsList(Node->Tab[numberOfTab].SelectorHead);
    freeAttributeList(Node->Tab[numberOfTab].AttributeHead);
    repositionTab(Node, numberOfTab, Node->length);
    if (Node->length == 1) {
        if ((Node->previous == NULL) && (Node->next != NULL)) {
            *doubleListHeadPtr = Node->next;
            Node->next->previous = NULL;
            delete Node;

        }
        else if (Node->previous != NULL) {
            Node->previous->next = Node->next;
            if (Node->next != NULL) Node->next->previous = Node->previous;
            delete Node;
        }
        else {
            delete Node;
            doubleLinkedList* Node = new doubleLinkedList();
            *doubleListHeadPtr = Node;
        }

    }
    else {
        Node->length--;
    }
    //delete &(Node->Tab[Node->length]);
}

void deleteAttribute(int number, char* nameOfAttribute, doubleLinkedList* doubleListHead, doubleLinkedList** doubleListHeadPtr) {
    Section* sectionTmp = SerchingForSectionByIndex(number, doubleListHead);
    if (sectionTmp == NULL) return;
    Attribute* attributeTmp = sectionTmp->AttributeHead;
    Attribute* attributePrev = nullptr;

    while (attributeTmp != NULL) {
        if (compareStrings(attributeTmp->name, nameOfAttribute)) {
            if (numberOfAttributes(number, doubleListHead) == 1) {
                deleteSection(number, doubleListHead, doubleListHeadPtr);
            }
            else if (attributePrev != nullptr) {
                attributePrev->next = attributeTmp->next;
                free(attributeTmp);
            }
            else {
                sectionTmp->AttributeHead = attributeTmp->next;
                free(attributeTmp);
            }
            cout << (number + 1) << ",D," << nameOfAttribute << " == deleted" << endl;
            return;

        }
        attributePrev = attributeTmp;
        attributeTmp = attributeTmp->next;

    }
}
