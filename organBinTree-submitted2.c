#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE 20 // max length of organT.name string
#define BLOODTYPESIZE 4 // max length of organT.bloodtype string
#define DATESIZE 11 // max length of date in mm/dd/yyyy format
#define TIMESIZE 6 // max length of time in hh:mm format

typedef struct {
    int month;
    int day;
    int year;
} dateT;

typedef struct {
    int hour;
    int minute;
} timeT;

typedef struct {
    char name[SIZE];
    char organname[SIZE];
    char bloodtype[BLOODTYPESIZE];
    dateT dateAdded;
    timeT timeAdded;
    int received;
} organT;

dateT parseDate(char* date);
timeT parseTime(char* time);
void findMatch(organT* people, int numPeople, char* organ, char* blood);
int compareDates(organT other, organT best);
int compareTimes(organT other, organT best);

int main()
{
    int numPeople = 0, numOrgans = 0, i = 0;
    char date[DATESIZE];
    char time[TIMESIZE];

    scanf("%d", &numPeople);
    // Dynamically allocate an array of structs for all of the people that we have on the
	// waitlist.
	organT* people = (organT*)malloc(numPeople * sizeof(organT));

	// Read in the information for everyone.
    for (i=0; i < numPeople; i++)
    {
         scanf("%s", people[i].name);
         scanf("%s", people[i].organname);
         scanf("%s", people[i].bloodtype);
         scanf("%s", date);
         people[i].dateAdded = parseDate(date);
         scanf("%s", time);
         people[i].timeAdded = parseTime(time);

		 // Initialize the received flag.
		 people[i].received = 0;
    }

	// Read the number of organs.
    scanf("%d", &numOrgans);

	// Read each organ. For each organ, try to find a match in the array of people.
    char organ[SIZE];
    char blood[BLOODTYPESIZE];
    for (i=0; i < numOrgans; i++)
    {
        scanf("%s", organ);
        scanf("%s", blood);
        findMatch(people, numPeople, organ, blood);
    }

	// When we've attempted to find all of the matches, we clean up.
    free(people);

    return 0;
}

// We know that when we read the date we will tokenize (split) it into three pieces and
// store them into their respective fields in the dateT struct, so we make three explicit
// calls to strtok (which splits our string into multiple parts called tokens).
dateT parseDate(char* date)
{
      dateT ret;

      date = strtok(date, "/");
      ret.month = atoi(date);

      date = strtok(NULL, "/");
      ret.day = atoi(date);

      date = strtok(NULL, "/");
      ret.year = atoi(date);

      return ret;
}

// Similar to above, but two tokens.
timeT parseTime(char* time)
{
      timeT ret;

      time = strtok(time, ":");
      ret.hour = atoi(time);

      time = strtok(NULL, "/");
      ret.minute = atoi(time);

      return ret;
}

void findMatch(organT* people, int numPeople, char* organ, char* blood)
{
     int i = 0;

	 // This flag keeps track of whether or not we have found a match so far.
	 int matchFlag = 0;

     // We want to store the index of the best match so far.
     int matchIdx = -1;

	 // Loop through everyone to see if they are a match.
     for (i = 0; i < numPeople; i++)
     {
		// This statement is what determines if someone is a match to an organ.
         if (people[i].received == 0 && strcmp(people[i].bloodtype,blood) == 0
			&& strcmp(people[i].organname,organ) == 0)
		{
			// If we've previously found a match
			if (matchFlag)
			{
				// Then we see if this match is higher up in the waiting list
				if (compareDates(people[i], people[matchIdx]) < 0)
				{
					// If it is then we store it as the best match found so far.
					matchIdx = i;
				}
			}
			// If this is the first match
			else
			{
				// Then save it as the best match found so far and change the flag.
				matchIdx = i;
				matchFlag = 1;
			}
		}
     }

	 // We've found a match, so we set received = 1 for that person, so that they don't get
	 // matched to another organ when they already have one.
	 if (matchFlag == 1)
	 {
		 people[matchIdx].received = 1;
		 printf("%s %s\n", people[matchIdx].name, organ);
	 }
	 else
	 {
		printf("No match found\n");
	 }
}

int compareDates(organT other, organT best)
{
    if (other.dateAdded.year < best.dateAdded.year)
       return -1;
    else if (other.dateAdded.year > best.dateAdded.year)
         return 1;
    else
    {
		if (other.dateAdded.month < best.dateAdded.month)
		   return -1;
		else if (other.dateAdded.month > best.dateAdded.month)
			 return 1;
		else
		{
		   if (other.dateAdded.day < best.dateAdded.day)
			   return -1;
			else if (other.dateAdded.day > best.dateAdded.day)
				 return 1;
			else
			{
				return compareTimes(other, best);
			}
		}
    }
}

int compareTimes(organT other, organT best)
{
	if (other.timeAdded.hour < best.timeAdded.hour)
	   return -1;
	else if (other.timeAdded.hour > best.timeAdded.hour)
		 return 1;
	else
	{
		if (other.timeAdded.minute < best.timeAdded.minute)
		   return -1;
		else if (other.timeAdded.minute > best.timeAdded.minute)
			 return 1;
		else
			return 0;
	}
}
