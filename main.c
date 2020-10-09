#include <stdio.h>
#include <string.h>

enum
{
    data,
    next
};

void StringListInit(char*** list)
{
    list[data] = NULL;
    list[next] = NULL;
}

void StringListAdd(char*** list, char* str)
{
    char** node = (char**)malloc(sizeof(char*) * 2);
    node[data] = (char*)malloc(sizeof(char) * strlen(str) + next);

    // copy our data to node
    strcpy((char*)node[data], str);
    node[next] = NULL;

    // check that our list empty
    if(*list == NULL)
    {
        *list = node;
    }
    else
    {
        char** newNode = *list;

        // go to the last element
        while(newNode[next] != NULL)
            newNode = (char*)newNode[next];

        newNode[next] = (char**)node;
    }
}

// Print list
void PrintList(char** list)
{
    char** node = list;

    if(node == NULL)
    {
        printf("%s", "List empty");
    }

    while(node != NULL)
    {
        printf("%s\n", (node[data]));
        node = (char*)node[next];
    }
    printf("\n");
}

void StringListRemove(char** list, char* str)
{
    char** node = *list;
    char** prev_node = NULL;

    while (node != NULL)
    {
        if (!strcmp((char*)node[data], str))
        {
             // delete data in our node that we search
            free((char*)node[data]);

            if (prev_node)
                prev_node[next] = node[next];
            else
                *list = (char*)node[next];

            char* node_to_free = (char*)node;
            node = (char*)node[next];
            free(node_to_free);
        }
        else
        {
            prev_node = node;
            node = (char*)node[next];
        }
    }
}

int StringListSize(char** list)
{
    int count = 0;
    char** node = list;

    // go to the last element
    while(node != NULL)
    {
        count++;
        node = (char*)node[next];
    }

    return count;
}

int StringListIndexOf(char** list, char* str)
{
    char** node = *list;
    int amount = 0;

    while(node != NULL)
    {
        // if we find coincidence return index
        if(!strcmp((char*)node[data], str))
            return amount;
        else
            amount++;

        node = (char*)node[next];
    }
    return -1;
}

int main()
{
    char **list = NULL;

    StringListAdd(&list, "abc1");
    StringListAdd(&list, "abc2");
    StringListAdd(&list, "abc3");
    StringListAdd(&list, "abc4");

    PrintList(list);

    printf("%s\t%d\n", "Element index:", StringListIndexOf(&list, "abc2"));
    printf("%s\t%d\n", "Size list:",  StringListSize(list));

    StringListRemove(&list, "abc3");
    PrintList(list);
}
