
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

void failedVarTypeCheck(int &variable, string prompt) // function for checking invalid inputs. Takes 2 variables in the parameter, a pointer integer for modyfing a global integer and the string for the prompt
{
    while (true) // loops the function until the input is valid
    {
        cout << prompt; // Message prompt here. There used to be more than one use case for this function so I made the prompt dynamic. I left it as it is for possible future appication
        int check;
        cin >> check;                // temporarily stores the value to be checked
        if (cin.fail() || check < 0) // checks for failed cin, due to invalid value type or if < 0
        {
            cout << "\n\n==================================";
            cout << "\nERROR: INVALID INPUT: TRY AGAIN";
            cout << "\n==================================\n";

            cin.clear();             // clears the error flag
            cin.ignore(10000, '\n'); // ignores the invalid input
        }
        else
        {
            variable = check; // stores the temporarily stored value into a pointer integer which modifies the global integer
            break;            // breaks the loop once the input is found to be valid
        }
    }
}

void faileStringInputCheck(string &op) // function for checking input for the operation/type of relation
{
    while (true) // loops the function until the input is valid
    {
        cout << "\n\nChoose the Type of Relation \n[<], [>], [=], [=], [<=], [>=]: ";
        string checkOp;
        cin >> checkOp; // temporarily stores the value to be checked

        if (checkOp != "=" && checkOp != "<" && checkOp != ">" && checkOp != "<=" && checkOp != ">=")
        {
            cout << "\n\n==========================";
            cout << "\nERROR: INVALID INPUT";
            cout << "\n==========================\n";
        }
        else
        {
            op = checkOp; // stors the temporarily stored value into a pointer integer
            break;        // breaks the loop once the input is found to be valid
        }
    }
}

void printSet(int countElement, int set[]) // function to print the set. Pwedeng wala na to pero twice kasi nagamit sa code kaya ginawa ko nalang na function
{
    cout << "\nSet A = {";
    for (int i = 0; i < countElement; i++) // for loop for printing an array
    {
        cout << set[i] << ", "; // prints the array with the index value of i, starting from 0 to the total number of elements
    }
    cout << "}\n";
}

void reflexiveCheck(int count, vector<vector<int>> &matrix)
{
    bool diagonalCheck = true; // sets the diagonal check flag as true and remains true if all the diagonal are 1
    for (int i = 0; i < count; i++)
    {
        if (matrix[i][i] != 1) // checks diagonal by assigning an equal index value to the 2d vector's row and column. It checks if they are equal to 1
        {
            diagonalCheck = false;
            break; // breaks the loop if a row and column with the same index value has a 0 integer
        }
    }

    if (diagonalCheck)
    {
        cout << "\nThe Relation is Reflexive\n";
    }
    else if (!diagonalCheck)
    {
        cout << "\nThe Relation is Irreflexive\n";
    }
    else
    {
        cout << "\nThe Relation is neither Reflexive nor Irreflexive\n";
    }
}

void symmetricCheck(int count, vector<vector<int>> &matrix)
{
    bool symmetric = true;          // sets the flag as true. Same as the reflexive funciton
    for (int i = 1; i < count; i++) // using nested for loop because we are using different index values for checking unlike the reflexive function
    {
        for (int j = 0; j < i; j++) // for every iteration of the outer loop, the index value i gets compared for every index value j in the inner loop, until every i is checked
        {
            if (matrix[i][j] != matrix[j][i]) // checks in the 2d vector if the row and column and it's adjacent is not equal. it follows the rule, for every [i][j] should be an equal [j][i]
            {
                symmetric = false; // updates the flag as false once an unequal row and column with the opposite index value is found
                break;
            }
        }
        if (!symmetric)
        {
            break;
        }
    }

    if (symmetric)
    {
        cout << "The Relation is Symmetri\n";
    }
    else
    {
        cout << "The Relation is not Symmetric\n";
    }
    /*
    Note: Tinanggal ko yung option na more than one set ang gagamitin. Isa nalang ang gagamitin so predictable na lahat ng result ng relation..
    At dahil dun useless tong function na to kasi yung in-example ni sir na operations/relations na gagamitin is "<,>,=,<=,>=". No symmetric relation will result from these operation so not symmetric lahat ng results.
    Same for the reflexiveCheck function since pwede naman na diretsio na ma determine if reflexive kung yung operator na ginamit ay =,<=,>= since lagi namang may equal lahat ng element in those cases.
    Nonetheless, linagay ko na muna.
    */
}

void printSymmetric(int count, int set[])
{
    vector<vector<int>> matrix(count, vector<int>(count));

    /*cout << "\n\n\n\nSymmetric Relation for the provided set might be: "; //Still trying to fix this part
    cout << "R = {";

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (matrix[i][j] == 1 && matrix[j][i] == 1)
            {
                cout << "(" << set[i] << ", " << set[j] << ")";
            }
        }
    }
    cout << "}";
    */

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (set[i] == set[j])
            {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }

    cout << "\n\nMatrix:\n     ";
    for (int j = 0; j < count; j++)
    {
        cout << set[j] << "    ";
    }
    cout << "\n";
    for (int i = 0; i < count; i++)
    {
        cout << set[i] << "  ";
        for (int j = 0; j < count; j++)
        {
            if (i != j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
            cout << "| " << matrix[i][j] << " |";
        }
        cout << "\n";
    }
    cout << "\nDigraph: \n";
    for (int i = 0; i < count; i++)
    {
        cout << set[i] << "-->";
        for (int j = 0; j < count; j++)
        {
            if (matrix[i][j] == 1)
            {
                cout << " " << set[j];
            }
        }
        cout << "\n";
    }
}
void operation(string op, int count, int set[]) // Function for the operations
{
    int matrix[count][count] = {}; // initializes the 2d array row and column to 0
    if (op == "<")
    {
        cout << "\n\nThe Relation is <\nR = {";
        for (int i = 0; i < count; i++) // nested for loop for 2 index values
        {
            for (int j = 0; j < count; j++)
            {
                if (set[i] < set[j]) // starts with the very first index i, and checks every index j that is less than i
                {
                    cout << "(" << set[i] << ", " << set[j] << ") "; // prints the elements found
                }
            }
        }
        cout << "}\n\nMatrix:\n\n   ";
        for (int j = 0; j < count; j++)
        {
            cout << set[j] << "  "; // prints element in the column
        }
        cout << "\n";

        for (int i = 0; i < count; i++)
        {
            cout << set[i] << "  "; // first prints the element of the row every iteration
            for (int j = 0; j < count; j++)
            {
                if (set[i] < set[j]) // after it prints the row element, it checks which elements have the "less than" relation
                {
                    matrix[i][j] = 1; // recall the previously initialized 2d array or matrix to 0. For every element that is found to have the less than relation, it assigns the value to those elements' coordinates to 1.
                }
                cout << "| " << matrix[i][j] << " |"; // prints the matrix
            }
            cout << "\n";
        }
    }
    else if (op == ">") // same process as the first operation
    {
        cout << "\n\nThe Relation is >\nR = {";
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (set[i] > set[j]) // the operation used here is the only difference
                {
                    cout << "(" << set[i] << ", " << set[j] << ") ";
                }
            }
        }
        cout << "}\n\nMatrix:\n     ";
        for (int j = 0; j < count; j++)
        {
            cout << set[j] << "    ";
        }
        cout << "\n";

        for (int i = 0; i < count; i++)
        {
            cout << set[i] << "  ";
            for (int j = 0; j < count; j++)
            {
                if (set[i] > set[j]) // also here
                {
                    matrix[i][j] = 1;
                }
                cout << "| " << matrix[i][j] << " |";
            }
            cout << "\n";
        }
    }

    else if (op == "=") // same process as the first operation
    {
        cout << "\n\nThe Relation is =\nR = {";
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (set[i] == set[j]) // the operation used here is the only difference
                {
                    cout << "(" << set[i] << ", " << set[j] << ") ";
                }
            }
        }
        cout << "}\n\nMatrix:\n     ";
        for (int j = 0; j < count; j++)
        {
            cout << set[j] << "    ";
        }
        cout << "\n";

        for (int i = 0; i < count; i++)
        {
            cout << set[i] << "  ";
            for (int j = 0; j < count; j++)
            {
                if (set[i] == set[j]) // also here
                {
                    matrix[i][j] = 1;
                }
                cout << "| " << matrix[i][j] << " |";
            }
            cout << "\n";
        }
    }
    else if (op == "<=") // same process as the first operation
    {
        cout << "\n\nThe Relation is <=\nR = {";
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (set[i] <= set[j]) // also here
                {
                    cout << "(" << set[i] << ", " << set[j] << ") ";
                }
            }
        }
        cout << "}\n\nMatrix:\n     ";
        for (int j = 0; j < count; j++)
        {
            cout << set[j] << "    ";
        }
        cout << "\n";

        for (int i = 0; i < count; i++)
        {
            cout << set[i] << "  ";
            for (int j = 0; j < count; j++)
            {
                if (set[i] <= set[j]) // also here
                {
                    matrix[i][j] = 1;
                }
                cout << "| " << matrix[i][j] << " |";
            }
            cout << "\n";
        }
    }
    else if (op == ">=") // same process as the first operation
    {
        cout << "\n\nThe Relation is >=\nR = {";
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (set[i] >= set[j]) // also here
                {
                    cout << "(" << set[i] << ", " << set[j] << ") ";
                }
            }
        }
        cout << "}\n\nMatrix:\n     ";
        for (int j = 0; j < count; j++)
        {
            cout << set[j] << "    ";
        }
        cout << "\n";

        for (int i = 0; i < count; i++)
        {
            cout << set[i] << "  ";
            for (int j = 0; j < count; j++)
            {
                if (set[i] >= set[j]) // also here
                {
                    matrix[i][j] = 1;
                }
                cout << "| " << matrix[i][j] << " |";
            }
            cout << "\n";
        }
    }

    vector<vector<int>> vectorMatrix(count, vector<int>(count)); // converts the 2d array to a 2d vector to be passed to the parameter of the functions
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            vectorMatrix[i][j] = matrix[i][j];
        }
    }

    reflexiveCheck(count, vectorMatrix); // calls the function to check reflexive...takes the variables count and the previously converted 2d vector as parameters
    symmetricCheck(count, vectorMatrix); // calls the function to check symmetric

    cout << "\nDigraph: \n";
    for (int i = 0; i < count; i++)
    {
        cout << set[i] << "-->"; // prints the first node in the first row
        for (int j = 0; j < count; j++)
        {
            if (matrix[i][j] == 1) // for every index i, it checks every index j if they are equal to 1
            {
                cout << " " << set[j]; // if it is equal to 1, it prints the element from the array with the index value of j
            }
        }
        cout << "\n";
    }

    cout << "\n\nTo see the possible SYMMETRIC RELATION: \n";
    system("pause");
    system("CLS");
    cout << "Systemmatic Relation of:\n";

    printSet(count, set); //prints set
    printSymmetric(count, set);
    /*
    calls the function that prints the possible symmetric relation of a given set including its matrix and digraph
    because as I've mentioned, there's now way of showing a symmetric relation using "<,>,<=,>=,="
    */
}

int main()
{
    int setOne[100], countElementOne, i, j, check, restart = 1;
    string relation, groupMembers[10] = {"Brylle Nyel Z. Mamuad", "Jensent M. Ortega", "Abigaile Cyrene Ramos", "Arjhay Malana", "Cedrick Novillero", "Dufnie Agas Perez", "Jezreal Quilang", "John Luis Calimag Pedoc", "Rizza Mendozza Pabon", "Tristan John Castro Mora"};

    while (restart == 1) // Loop for restarting the program if the user wishes to at the end
    {
        cout << "DISCRETE STRUCTURES PRELIM PROJECT\n";
        cout << "Group 4: SET RELATION GENERATOR with MATRIX and DIGRAPH\n";

        cout << "\n\nINPUT SET: \n";

        failedVarTypeCheck(countElementOne, "Enter Number of Elements for the Set: "); // calls the function to check for failed inputs

    setOne:
        cout << "\n\nEnter " << countElementOne << " numbers for the Set: \n\n";
        for (i = 0; i < countElementOne; i++)
        {
            cout << "Element Number " << i + 1 << ": ";
            cin >> check;
            if (cin.fail())
            {
                cout << "\n\n==========================";
                cout << "\nERROR: Invalid input: " << check;
                cout << "\n==========================\n";
                cin.clear();
                cin.ignore(10000, '\n');
                goto setOne;
            }
            else
            {
                setOne[i] = check;
                for (j = 0; j < i; j++)
                {
                    if (setOne[i] == setOne[j])
                    {
                        cout << "\n\n====================================";
                        cout << "\nERROR DUPLICATE NUMBER DETECTED: " << setOne[i];
                        cout << "\n====================================\n";
                        goto setOne;
                    }
                }
            }
        }

        printSet(countElementOne, setOne);

        faileStringInputCheck(relation); // calls the function to check for failed inputs

        system("CLS"); // Deletes all the previous text after before proceeding

        printSet(countElementOne, setOne); // calls the function to print the set

        operation(relation, countElementOne, setOne); // calls

        failedVarTypeCheck(restart, "\n\nDo you wish to restart the program? 1 for Yes. Anything other than 1 for No: "); // promts user asking if they wish to loop/restart the program
        if (restart == 1)
        {
            system("CLS");
        }
        else
        {
            system("CLS");

            cout << "BSCS 1A-BA\n";
            cout << "Group 4 Members: \n";

            for (i = 0; i < 10; i++)
            {
                cout << groupMembers[i] << "\n\n";
            }

            cout << "\n\n";

            while (true)
            {
                sleep(1);
                cout << "THANK " << flush;
                sleep(1);
                cout << "YOU " << flush;
                sleep(1);
                cout << "FOR " << flush;
                sleep(1);
                cout << "USING" << flush;
                sleep(1);
                for (int i = 0; i < 19; i++)
                {
                    cout << "\b \b" << flush;
                }
            }
        }
    }
}

/*overall, this could be further simplified starting from scratch. 
I started writing the code implementing more than one set but ultimately settling for one, so I only modified my previous code, making it more complicated than it needs to be.*/
