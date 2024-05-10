#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(name, candidates[i].name) == 0)
        {
            // If yes, store the index of the candidate who is the jth ranked preference for the ith
            // voter
            preferences[voter][rank] = i;
            return true;
        }
    }
    // If no match, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int rank = 0;
        int br = 0;
        while (true)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                // If the jth candidate of the rankth rank has been eliminated, move to the next
                // rank
                if (preferences[i][rank] == j && candidates[j].eliminated == true)
                {
                    rank++;
                    break;
                }
                // If the jth candidate of the rankth rank hasn't been eliminated, add one vote to
                // him/her
                else if (preferences[i][rank] == j && candidates[j].eliminated == false)
                {
                    candidates[j].votes++;
                    br = 1;
                    break;
                }
            }
            if (br == 1)
                break;
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int max_votes = 0;
    int winner_index = 0;
    // Find the maximum number of votes per candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (max_votes < candidates[i].votes)
        {
            max_votes = candidates[i].votes;
            winner_index = i;
        }
    }
    // If any candidate has more than half of the vote, print their name
    if (max_votes > voter_count / 2)
    {
        printf("%s\n", candidates[winner_index].name);
        return true;
    }
    // If nobody has won the election yet, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && min_votes > candidates[i].votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If a candidate remaining in the election has more than the min number of votes, return
        // false
        if (candidates[i].eliminated == false && candidates[i].votes > min)
        {
            return false;
        }
    }
    // If every candidate remaining in the election has the same number of votes, return true
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Eliminate the candidate (or candidates) who have min number of votes
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
