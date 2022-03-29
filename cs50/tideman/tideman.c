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
}
pair;

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
    int i = 0;
    while (i < candidate_count - 1 && strcmp(name, candidates[i]) != 0)
    {
        i++;
    }
    if (strcmp(name, candidates[i]) == 0)
    {
        ranks[rank] = i;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int n = 0;
    int i;
    int j;
    int k;
    while (n < candidate_count)
    {
        i = ranks[n];
        k = n + 1;
        while (k <= candidate_count)
        {
            j = ranks[k];
            preferences[i][j] = preferences[i][j] + 1;
            k++;
        }
        n++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int i = 0;
    int j;
    while (i < candidate_count)
    {
        j = i + 1;
        while (j < candidate_count)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            j++;
        }
        i++;
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int n;
    int i;
    int j;
    int k;
    int l;
    int m = 0;
    while (m < pair_count - 1)
    {
        n = m + 1;
        i = pairs[m].winner;
        j = pairs[m].loser;
        while (n < pair_count - 1 - m)
        {
            k = pairs[n].winner;
            l = pairs[n].loser;
            if (preferences[k][l] > preferences[i][j])
            {
                pairs[n].winner = i;
                pairs[n].loser = j;
                pairs[m].winner = k;
                pairs[m].loser = l;
            }
            n++;
        }
        m++;
    }
    return;
}

bool cycle(int end, int cycle_start)
{
    if (end == cycle_start)
    {
        return true;
    }
    int i = 0;
    while (i < candidate_count)
    {
        if (locked[end][i] == true)
        {
            if (cycle(i, cycle_start) == true)
            {
                return true;
            }
        }
        i++;
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (k < pair_count)
    {
        i = pairs[k].winner;
        j = pairs[k].loser;
        if (cycle(j, i) == false)
        {
            locked[i][j] = true;
        }
        k++;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < candidate_count)
    {
        j = 0;
        count = 0;
        while (j < candidate_count)
        {
            if (locked[j][i] == false)
            {
                count++;
                if (count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
            j++;
        }
        i++;
    }
    return;
}