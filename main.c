#include <stdio.h>
#include <string.h>

enum
{
    data,
    next
};

void StringListAdd(char*** list, char* str)
{
    if(list == NULL)
    {
        return;
    }
    char** node = (char**)malloc(sizeof(char*) * 2);
    node[data] = (char*)malloc(sizeof(char) * strlen(str) + next);

    // copy our data to node
    if(node[data]!= NULL) memcpy((char*)node[data], str, strlen(str)+1);
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
    if(list == NULL)
    {
        return;
    }

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

void StringListDestroy(char*** list)
{
    if (list == NULL)
    {
        printf("%s\n", "List destroy");
        return;
    }

    char** node = (*list);
    char** temp = NULL;

    while(node != NULL)
    {
        temp = node[next];
        free(node[data]);
        (*list) = temp;
        node = (char*)node[next];
    }

    free((char*)list[data]);
    free(*list);
    (*list) = NULL;
    printf("%s", "List was destroyed\n");
}

int StringListSize(char** list)
{
    if(list == NULL)
    {
        return;
    }

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
    if(list == NULL)
    {
        return;
    }

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


void StringListSort(char** list)
{
    if(list == NULL)
    {
        return;
    }

    char** tmp = NULL;
    for(char** node = (char**)*list; node[next] != NULL; node = (char**)node[next])
    {
        char** node_min_element = node;
        for(char** iter_node = (char**)node[next]; iter_node != NULL; iter_node = (char**)iter_node[next])
        {
            if(strcmp((char*)iter_node[data], (char*)node_min_element[data]) < 0)
                node_min_element = iter_node;
        }
        tmp = node[data];
        node[data] = node_min_element[data];
        node_min_element[data] = tmp;
    }
}

int main()
{
    char **list = NULL;

    StringListAdd(&list, "abc1");
    StringListAdd(&list, "abc3");
    StringListAdd(&list, "abc1");
    StringListAdd(&list, "abc2");
    StringListAdd(&list, "abc1");
    StringListAdd(&list, "abc1");
    StringListAdd(&list, "abc2");
    StringListAdd(&list, "abc3");
    StringListAdd(&list, "abc4");
    StringListAdd(&list, "abc2");
    StringListAdd(&list, "abc3");
    StringListAdd(&list, "abc4");

    PrintList(list);

    printf("%s\t%d\n", "Element index:", StringListIndexOf(&list, "abc2"));
    printf("%s\t%d\n", "Size list:",  StringListSize(list));


    StringListSort(&list);
    PrintList(list);

    StringListRemove(&list, "abc1");
    PrintList(list);

    StringListDestroy(&list);
    PrintList(list);
}
