#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100 // Maximum number of items in the inventory

// Structure to hold the details of an inventory item
typedef struct
{
    char itemName[50]; // Name of the item
    float price;       // Price of the item
    int stock;         // Stock quantity of the item
    char keyword[20];  // Keyword associated with the item
} InventoryItem;

// Function prototypes for inventory operations
void addItem(InventoryItem items[], int *count);
void editItem(InventoryItem items[], int count);
void deleteItem(InventoryItem items[], int *count);
void displayItems(const InventoryItem items[], int count);
void searchItems(const InventoryItem items[], int count);
void saveToFile(const InventoryItem items[], int count);
void loadFromFile(InventoryItem items[], int *count);

int main()
{
    InventoryItem items[MAX_ITEMS]; // Array to hold inventory items
    int count = 0; // Number of items currently in the inventory
    int choice; // Variable to store user's menu choice

    // Load items from file when the program starts
    loadFromFile(items, &count);

    while (1)
    {
        // Display the menu options to the user
        printf("Menu:\n");
        printf("1. Add Item\n");
        printf("2. Edit Item\n");
        printf("3. Delete Item\n");
        printf("4. Display Items\n");
        printf("5. Search Items\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform the action based on the user's choice
        switch (choice)
        {
        case 1:
            addItem(items, &count); // Add a new item
            break;
        case 2:
            editItem(items, count); // Edit an existing item
            break;
        case 3:
            deleteItem(items, &count); // Delete an item
            break;
        case 4:
            displayItems(items, count); // Display all items
            break;
        case 5:
            searchItems(items, count); // Search for items
            break;
        case 6:
            saveToFile(items, count); // Save items to file and exit
            return 0;
        default:
            printf("Invalid choice!\n"); // Handle invalid menu choice
        }
    }

    return 0;
}

// Function to add a new item to the inventory
void addItem(InventoryItem items[], int *count)
{
    if (*count >= MAX_ITEMS) // Check if the inventory is full
    {
        printf("Inventory is full!\n");
        return;
    }

    // Get item details from the user
    printf("Enter item name: ");
    getchar(); // Clear newline from buffer
    fgets(items[*count].itemName, sizeof(items[*count].itemName), stdin);
    items[*count].itemName[strcspn(items[*count].itemName, "\n")] = '\0'; // Remove newline character

    printf("Enter price: ");
    scanf("%f", &items[*count].price);

    printf("Enter stock: ");
    scanf("%d", &items[*count].stock);

    printf("Enter keyword: ");
    getchar(); // Clear newline from buffer
    fgets(items[*count].keyword, sizeof(items[*count].keyword), stdin);
    items[*count].keyword[strcspn(items[*count].keyword, "\n")] = '\0'; // Remove newline character

    (*count)++; // Increment the item count
    printf("Item added successfully!\n");

    saveToFile(items, *count); // Save the updated inventory to the file
}

// Function to edit an existing item in the inventory
void editItem(InventoryItem items[], int count)
{
    if (count == 0) // Check if there are any items to edit
    {
        printf("No items to edit.\n");
        return;
    }

    int index; // Variable to store the item number to be edited
    printf("Enter item number to edit (1 to %d): ", count);
    scanf("%d", &index);
    if (index < 1 || index > count) // Check for valid item number
    {
        printf("Invalid item number.\n");
        return;
    }
    index--; // Convert to zero-based index

    // Get new details from the user
    printf("Editing item #%d\n", index + 1);

    printf("Enter new item name: ");
    getchar(); // Clear newline from buffer
    fgets(items[index].itemName, sizeof(items[index].itemName), stdin);
    items[index].itemName[strcspn(items[index].itemName, "\n")] = '\0'; // Remove newline character

    printf("Enter new price: ");
    scanf("%f", &items[index].price);

    printf("Enter new stock: ");
    scanf("%d", &items[index].stock);

    printf("Enter new keyword: ");
    getchar(); // Clear newline from buffer
    fgets(items[index].keyword, sizeof(items[index].keyword), stdin);
    items[index].keyword[strcspn(items[index].keyword, "\n")] = '\0'; // Remove newline character

    printf("Item updated successfully!\n");

    saveToFile(items, count); // Save the updated inventory to the file
}

// Function to delete an item from the inventory
void deleteItem(InventoryItem items[], int *count)
{
    if (*count == 0) // Check if there are any items to delete
    {
        printf("No items to delete.\n");
        return;
    }

    int index; // Variable to store the item number to be deleted
    printf("Enter item number to delete (1 to %d): ", *count);
    scanf("%d", &index);
    if (index < 1 || index > *count) // Check for valid item number
    {
        printf("Invalid item number.\n");
        return;
    }
    index--; // Convert to zero-based index

    // Shift items to remove the deleted item
    for (int i = index; i < *count - 1; i++)
    {
        items[i] = items[i + 1];
    }

    (*count)--; // Decrement the item count
    printf("Item deleted successfully!\n");

    saveToFile(items, *count); // Save the updated inventory to the file
}

// Function to display all items in the inventory
void displayItems(const InventoryItem items[], int count)
{
    if (count == 0) // Check if there are any items to display
    {
        printf("No items to display.\n");
        return;
    }

    // Display each item in the inventory
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

// Function to search for items by keyword
void searchItems(const InventoryItem items[], int count)
{
    if (count == 0) // Check if there are any items to search
    {
        printf("No items to search.\n");
        return;
    }

    char keyword[20]; // Variable to store the search keyword
    printf("Enter keyword to search: ");
    getchar(); // Clear newline from buffer
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    printf("Search Results:\n");
    int found = 0; // Flag to indicate if any items were found
    // Search for items matching the keyword
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

    if (!found) // If no items were found with the keyword
    {
        printf("No items found with the keyword \"%s\".\n", keyword);
    }
}

// Function to save the inventory to a file
void saveToFile(const InventoryItem items[], int count)
{
    FILE *file = fopen("inventory.txt", "w"); // Open the file for writing
    if (file == NULL) // Check if the file was opened successfully
    {
        printf("Error opening file for saving.\n");
        return;
    }

    // Write each item to the file
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", items[i].itemName);
        fprintf(file, "%.2f\n", items[i].price);
        fprintf(file, "%d\n", items[i].stock);
        fprintf(file, "%s\n", items[i].keyword);
    }

    fclose(file); // Close the file
    printf("Items saved to file successfully!\n");
}
