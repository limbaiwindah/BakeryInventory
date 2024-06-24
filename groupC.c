#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

typedef struct
{
    char itemName[50];
    float price;
    int stock;
    char keyword[20];
} InventoryItem;

void addItem(InventoryItem items[], int *count);
void editItem(InventoryItem items[], int count);
void deleteItem(InventoryItem items[], int *count);
void displayItems(const InventoryItem items[], int count);
void searchItems(const InventoryItem items[], int count);
void saveToFile(const InventoryItem items[], int count);
void loadFromFile(InventoryItem items[], int *count);

int main()
{
    InventoryItem items[MAX_ITEMS];
    int count = 0;
    int choice;

    loadFromFile(items, &count);

    while (1)
    {
        printf("Menu:\n");
        printf("1. Add Item\n");
        printf("2. Edit Item\n");
        printf("3. Delete Item\n");
        printf("4. Display Items\n");
        printf("5. Search Items\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addItem(items, &count);
            break;
        case 2:
            editItem(items, count);
            break;
        case 3:
            deleteItem(items, &count);
            break;
        case 4:
            displayItems(items, count);
            break;
        case 5:
            searchItems(items, count);
            break;
        case 6:
            saveToFile(items, count);
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addItem(InventoryItem items[], int *count)
{
    if (*count >= MAX_ITEMS)
    {
        printf("Inventory is full!\n");
        return;
    }

    printf("Enter item name: ");
    getchar(); // Clear newline from buffer
    fgets(items[*count].itemName, sizeof(items[*count].itemName), stdin);
    items[*count].itemName[strcspn(items[*count].itemName, "\n")] = '\0';

    printf("Enter price: ");
    scanf("%f", &items[*count].price);

    printf("Enter stock: ");
    scanf("%d", &items[*count].stock);

    printf("Enter keyword: ");
    getchar(); // Clear newline from buffer
    fgets(items[*count].keyword, sizeof(items[*count].keyword), stdin);
    items[*count].keyword[strcspn(items[*count].keyword, "\n")] = '\0';

    (*count)++;
    printf("Item added successfully!\n");

    saveToFile(items, *count);
}

void editItem(InventoryItem items[], int count)
{
    if (count == 0)
    {
        printf("No items to edit.\n");
        return;
    }

    int index;
    printf("Enter item number to edit (1 to %d): ", count);
    scanf("%d", &index);
    if (index < 1 || index > count)
    {
        printf("Invalid item number.\n");
        return;
    }
    index--; // Convert to zero-based index

    printf("Editing item #%d\n", index + 1);

    printf("Enter new item name: ");
    getchar(); // Clear newline from buffer
    fgets(items[index].itemName, sizeof(items[index].itemName), stdin);
    items[index].itemName[strcspn(items[index].itemName, "\n")] = '\0';

    printf("Enter new price: ");
    scanf("%f", &items[index].price);

    printf("Enter new stock: ");
    scanf("%d", &items[index].stock);

    printf("Enter new keyword: ");
    getchar(); // Clear newline from buffer
    fgets(items[index].keyword, sizeof(items[index].keyword), stdin);
    items[index].keyword[strcspn(items[index].keyword, "\n")] = '\0';

    printf("Item updated successfully!\n");

    saveToFile(items, count);
}

void deleteItem(InventoryItem items[], int *count)
{
    if (*count == 0)
    {
        printf("No items to delete.\n");
        return;
    }

    int index;
    printf("Enter item number to delete (1 to %d): ", *count);
    scanf("%d", &index);
    if (index < 1 || index > *count)
    {
        printf("Invalid item number.\n");
        return;
    }
    index--; // Convert to zero-based index

    for (int i = index; i < *count - 1; i++)
    {
        items[i] = items[i + 1];
    }

    (*count)--;
    printf("Item deleted successfully!\n");

    saveToFile(items, *count);
}

void displayItems(const InventoryItem items[], int count)
{
    if (count == 0)
    {
        printf("No items to display.\n");
        return;
    }

    printf("Inventory Items:\n");
    for (int i = 0; i < count; i++)
    {
        printf("Item #%d\n", i + 1);
        printf("Name: %s\n", items[i].itemName);
        printf("Price: %.2f\n", items[i].price);
        printf("Stock: %d\n", items[i].stock);
        printf("Keyword: %s\n\n", items[i].keyword);
    }
}

void searchItems(const InventoryItem items[], int count)
{
    if (count == 0)
    {
        printf("No items to search.\n");
        return;
    }

    char keyword[20];
    printf("Enter keyword to search: ");
    getchar(); // Clear newline from buffer
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    printf("Search Results:\n");
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strstr(items[i].keyword, keyword) != NULL)
        {
            printf("Item #%d\n", i + 1);
            printf("Name: %s\n", items[i].itemName);
            printf("Price: %.2f\n", items[i].price);
            printf("Stock: %d\n", items[i].stock);
            printf("Keyword: %s\n\n", items[i].keyword);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No items found with the keyword \"%s\".\n", keyword);
    }
}

void saveToFile(const InventoryItem items[], int count)
{
    FILE *file = fopen("inventory.txt", "w"); 
    if (file == NULL)
    {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", items[i].itemName);
        fprintf(file, "%.2f\n", items[i].price);
        fprintf(file, "%d\n", items[i].stock);
        fprintf(file, "%s\n", items[i].keyword);
    }

    fclose(file);
    printf("Items saved to file successfully!\n");
}


// file opening
void loadFromFile(InventoryItem items[], int *count)
{
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL)
    {
        printf("No existing inventory file found. Starting fresh.\n");
        return;
    }

    while (!feof(file) && *count < MAX_ITEMS)
    {
        if (fgets(items[*count].itemName, sizeof(items[*count].itemName), file) == NULL)
            break;
        items[*count].itemName[strcspn(items[*count].itemName, "\n")] = '\0';

        fscanf(file, "%f\n", &items[*count].price);
        fscanf(file, "%d\n", &items[*count].stock);

        fgets(items[*count].keyword, sizeof(items[*count].keyword), file);
        items[*count].keyword[strcspn(items[*count].keyword, "\n")] = '\0';

        (*count)++;
    }

    fclose(file);
    printf("Items loaded from file successfully! %d items found.\n", *count);
}
