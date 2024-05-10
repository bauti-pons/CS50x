#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool creates_cycle(int, int);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(name, candidates[i]) == 0)
        {
            // If yes, update the ranks array to indicate that the voter has the candidate as their
            // rank preference
            ranks[rank] = i;
            return true;
        }
    }
    // If no match, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Add one vote at the number of voters who prefer candidate i over candidate j
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
                preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                // Add pair (i,j)
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                // Add pair (j,i)
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength[pair_count];
    int winner_points;
    int loser_points;
    // Get the difference of points (strength) of each pair by index (in order)
    for (int i = 0; i < pair_count; i++)
    {
        winner_points = preferences[pairs[i].winner][pairs[i].loser];
        loser_points = preferences[pairs[i].loser][pairs[i].winner];
        strength[i] = winner_points - loser_points;
    }

    int max;
    int index;
    int count = pair_count;
    pair sorted_pairs[pair_count];
    int j = 0;

    while (count > 0)
    {
        max = 0;
        // Get the index of the max strength
        for (int i = 0; i < pair_count; i++)
        {
            if (max < strength[i])
            {
                max = strength[i];
                index = i;
            }
        }
        // Add the pair of that index to the sorted list
        sorted_pairs[j] = pairs[index];
        j++;
        strength[index] = 0;
        count--;
    }

    // Convert the pairs array into the sorted_pairs
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = sorted_pairs[i];
    }

    return;
}

//  Check if adding a specific edge creates a cycle in the graph
bool creates_cycle(int winner, int loser)
{
    // If loser can reach winner, a cycle is created
    if (loser == winner)
    {
        return true;
    }

    // Recurse through all candidates to see if there is a path from loser to winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (creates_cycle(winner, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate over each candidate to check if they have any incoming edges
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming_edges = false;

        // Check all other candidates to see if they have an edge pointing to candidate i
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_incoming_edges = true;
                break; // If any incoming edge is found, break the loop
            }
        }

        // If no incoming edges are found, print the candidate as the winner
        if (!has_incoming_edges)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
