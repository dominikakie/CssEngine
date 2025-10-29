#pragma once
class Attribute;
class Selector;
class Section;
class doubleLinkedList;

class Section {
public:
    Attribute* AttributeHead;
    Selector* SelectorHead;

};
class doubleLinkedList {
public:
    doubleLinkedList* previous = nullptr;
    doubleLinkedList* next = nullptr;
    int length = 0;
    Section Tab[8];

    void newTab(Section section) {
        doubleLinkedList* last = this;
        while (last->next != NULL) {
            last = last->next;
        }

        if (last->length >= 8) {
            last->next = new doubleLinkedList;
            last->next->previous = last;
            last->next->length = 1;
            last->next->Tab[0] = section;
        }
        else {
            last->Tab[last->length++] = section;
        }
    }
};
class Selector {
public:
    char* name;
    Selector* next;
};
class Attribute {
public:
    char* name;
    char* value;
    Attribute* next;
};
