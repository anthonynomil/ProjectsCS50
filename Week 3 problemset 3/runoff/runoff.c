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
}
candidate;

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
    // TODO
    for (int i = 0; i < candidate_count; ++i)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
        else if (name == NULL)
        {
            return false;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for(int i = 0; i < voter_count; ++i)
    {
        int k = 0;
        while (k != 4)
        {
            int cmp = preferences[i][k];
            if (candidates[cmp].eliminated == true)
            {
                ++k;
            }
            else
            {
                candidates[cmp].votes++;
                k = 4;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // For each candidate check if the candidates vote is the majority (by / 2 the number of voters )
    for (int i = 0; i < candidate_count; ++i)
    {
        if (candidates[i].votes > (voter_count / 2) && candidates[i].eliminated == false)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int vote_count;

    // For each candidate check if the candidate has been eliminated, if he isn't copy his votes to the variable vote_count and break the for to avoid unecessary looping we just needed one value from a candidate still in the race
    for (int i = 0; i < candidate_count; ++i)
    {
        if (candidates[i].eliminated == false)
        {
            vote_count = candidates[i].votes;
            break;
        }

    }
    // For each candidate check if the vote_count of the previous candidate is bigger and if the current candidate is still in the race if they're both true change vote_count to the one of the current candidate since he's inferior
    for (int i = 0; i < candidate_count; ++i)
    {
        if (vote_count > candidates[i].votes && candidates[i].eliminated == false)
        {
            vote_count = candidates[i].votes;
        }
    }
    return vote_count;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    /* For each candidate, check if their amount of votes are the same as the lowest amount of votes if true add one to the number of ties, check if the candidate is still in the race
       if true add one to the number of candidates in the race if the number of ties are the same as the number of candidates in the race return true that there is a tie */
    int tie = 0;
    int inrace = 0;
    for(int i = 0; i < candidate_count; ++i)
    {
        if(candidates[i].votes == min)
        {
            ++tie;

        }
        if(candidates[i].eliminated == false)
        {
            ++inrace;
        }
    }
    if (tie == inrace)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO --- DONE
    // For each candidate, check if a candidate number of votes is equal to the lowest amount of votes and if the candidate is still in the race, if it's true eliminate the candidate
    for (int i = 0; i < candidate_count; ++i)
    {
        if (min == candidates[i].votes && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}