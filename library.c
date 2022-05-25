#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


#define RSIZ 100 //max no. of books
#define LSIZ 128 //book name length

//function declarations
bool save_changes(char list[RSIZ][LSIZ], int listcnt, string filename);
bool check_borrowed(string bookname, int borrcnt, char list[RSIZ][LSIZ] );


int main(void) {
    system("clear");

    //load all library.txt books into array
    char books[RSIZ][LSIZ];
    char booksarr[RSIZ][LSIZ];
    FILE *fptr = NULL;
    int x = 0;
    fptr = fopen("library.txt", "r");
    if (fptr == NULL)   {
        printf("Cannot open file \n");
        exit(0);
    }
    while(fgets(*books, sizeof(books), fptr))
	{
        strncpy(booksarr[x],*books, sizeof(*books));
        x++;
    }
    fclose(fptr);
    int totbooks = x;


    //load borrowed.txt books into array
    char borrowed[RSIZ][LSIZ];
    char borrowedarr[RSIZ][LSIZ];
    FILE *bptr = NULL;
    int y = 0;
    bptr = fopen("borrowed.txt", "r");
    if (bptr == NULL)   {
        printf("Cannot open file\n");
         exit(0);
    }
    while(fgets(*borrowed, sizeof(borrowed), bptr))
	{
        strncpy(borrowedarr[y],*borrowed, sizeof(*borrowed));
        y++;
    }
    fclose(bptr);
    int totborr = y;


    //MAIN MENU
    int endprogram = 1;

    string ans;

    //start of main menu loop
    while(endprogram != 0) {
    system("clear");
    printf("\n\n");
    printf("Welcome!\n");
    printf("There are %d books in the library, %d books are currently checked out.\n", totbooks, totborr);
    printf("\n");
    printf("Choose your adventure:\n");
    printf("(1) List all Books\n");
    printf("(2) List all Borrowed Books\n");
    printf("(3) Add a Book\n");
    printf("(4) Check Out a Book\n");
    printf("(5) Return a Book\n");
    printf("(6) Save Changes\n");
    printf("(7) Exit the Library\n");

    ans = get_string("Choose a number: ");



    //main menu choice 1 - List All Books
    if(strcmp( ans, "1") == 0) {
        system("clear");
        printf("\n");

        printf("\nYour %d Books:\n\n", totbooks);
        for(int i = 0; i < totbooks; i++)
        {
            printf("%d ", i+1);
            printf("%s", booksarr[i]);
        }
        printf("\n");
        printf("\nPress Return to Continue\n");
        getchar();
        //return 0;
    }

    //main menu choice 2 - List all Borrowed Books
    if(strcmp( ans, "2") == 0) {
        system("clear");

        printf("\nYour Borrowed Books:\n");
        for(int i = 0; i < totborr; i++)
        {
            printf("%d ", i + 1);
            printf("%s", borrowedarr[i]);
        }

        printf("\n");
        printf("\nPress Return to Continue\n");
        getchar();

    }

    //main menu choice 3 - Add a Book
    if(strcmp( ans, "3") == 0) {
        system("clear");
        printf("\n");

        string newbook = get_string("Enter title of the book: ");
        string newbookauthor = get_string("Enter author of the book: ");
        strcat(newbook, " by ");
        strcat(newbook, newbookauthor);
        strcat(newbook, "\n");
        strncpy(booksarr[totbooks], newbook, strlen(newbook)+1);
        totbooks++;


        printf("\n");
        printf("\nPress Return to Continue\n");
        getchar();
    }

    //main menu choice 4 - Check Out a Book
    if(strcmp(ans, "4") == 0) {
        system("clear");
        printf("\n");

        printf("\nYour %d Books:\n\n", totbooks);
        for(int i = 0; i < totbooks; i++)
        {
            printf("%d ", i+1);
            printf("%s", booksarr[i]);
        }

        int checkout = get_int("\nEnter number of book you would like to check out: ");

        string checkoutbook = booksarr[checkout-1];

        if (!check_borrowed (checkoutbook, totborr, borrowedarr))
        {
        strncpy(borrowedarr[totborr], checkoutbook, strlen(checkoutbook)+1);
        totborr++;
        printf("\nYou want to check out book: %s\n", booksarr[checkout-1]);
        } else
        {
        printf("\nThat Book is already borrowed!\n");
        }

        printf("\nPress Return to Continue\n");
        getchar();
    }

    //main menu choice 5 - Return a Book
    if(strcmp( ans, "5") == 0) {
        char newborrowedarr[RSIZ][LSIZ];
        system("clear");
        printf("\n");

        printf("\nYour Borrowed Books:\n");
        for(int i = 0; i < totborr; i++)
        {
            printf("%d ", i + 1);
            printf("%s", borrowedarr[i]);
        }

        int checkin = get_int("\nEnter number of book you would like to return: ");
        int z = 0;
        printf("\nYou want to return: %s\n", borrowedarr[checkin-1]);

        for(int i=0; i < totborr; i++)
        {
            if(i != checkin - 1) {

                strncpy(newborrowedarr[z], borrowedarr[i], strlen(borrowedarr[i]));
                z++;
            }
        }

        for(int i=0; i < totborr-1; i++)
        {
                strncpy(borrowedarr[i], newborrowedarr[i], strlen(newborrowedarr[i]));
        }

        totborr--;



        printf("\nPress Return to Continue\n");
        getchar();
    }



//  main menu choice 6 - Save Changes
    if(strcmp( ans, "6") == 0) {
        system("clear");

        if (!save_changes(borrowedarr, totborr, "borrowed.txt"))
        {
            printf("Error writing to borrowed.txt");
        }
        if (!save_changes(booksarr, totbooks, "library.txt"))
        {
            printf("Error writing to library.txt");
        }

        printf("\n");
        printf("\nChanges Saved!\n");
        printf("\n");
        printf("\nPress Return to Continue\n");
        getchar();

    }

    //main menu choice 7 - Exit the Library
    if(strcmp( ans, "7") == 0) {
        system("clear");
        printf("\n");
        system("clear");
        printf("Thank you for using my Library!\n");
        endprogram = 0;
    }


    } //end of while loop main menu


} //end main

bool save_changes(char list[RSIZ][LSIZ], int listcnt, string filename)
{
    int err = 0;

        FILE *wptr = fopen(filename, "w");
        for(int i = 0; i < listcnt; i++)
        {
            err = fprintf(wptr, "%s", list[i]);
        }
        fclose(wptr);

    if (err < 0) {
        return false;
    } else
    {
        return true;
    }


} // end save_changes

bool check_borrowed(string bookname, int borrcnt, char list[RSIZ][LSIZ] )
{
        for(int i = 0; i < borrcnt; i++)
        {
            if (strcmp(bookname, list[i]) == 0)
            {
                return 1;
            }
        }
    return 0;
} // end check_borrowed
