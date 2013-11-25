/**
*   Donald Richards
*   Assignment COP3502-P5
*   11/25/2013 - Submitted
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.1415926535
#define DEGREES 360

// STRUCTS for Cop & ROBBERS
typedef struct {
  float x, y; 
  float speed;
  double time;
}Cop;

typedef struct {
  float x, y; 
  float speed, direction;
}Robber;


// FUNCTIONS DECLARATION 
void runApp();
double minimalTime(Cop copTemp,Robber robTemp);
Robber initalizeRobber(int x, int y, int speed, int direction);
void RobberLocation(Robber ** robTemp, int numberOfRobbers);
int * permutation(const int n, int i);
int factorial(int n);


// MAIN APP CALLS runApp()
int main(){
  runApp();
}

// Calculate factorials when n! is over 1 or possibly negative  
int factorial(int n){
  if( n == 0 || n == 1){
    return 1;
  }
  else{
    return n*factorial(n-1); //RECURSIVE CALL TO FACTORIAL 
  }
}// END OF factorial 


// Permutation through the board
int * permutation(int n, int i){
  int j, k = 0;
  int *factTemp = (int *)calloc(n, sizeof(int));
  int *permutationTemp = (int *)calloc(n, sizeof(int));

  factTemp[k] = 1;
  
  while(++k < n)
    factTemp[k] = factTemp[k - 1] * k;

  for(k = 0; k < n; ++k){
      permutationTemp[k] = i / factTemp[n - 1 - k];
      i = i % factTemp[n - 1 - k];
  }//END OF FOR k<n 

  // Reverse lookup to check values are lower 
  for(k = n - 1; k > 0; --k)
    for(j = k - 1; j >= 0; --j)
      if(permutationTemp[j] <= permutationTemp[k])
        permutationTemp[k]++;

  free(factTemp);
  return permutationTemp;
}// END OF permutation

// Calculates minimum time to robbers by distance and time  
double minimalTime(Cop copTemp, Robber robTemp){
  double distChase = 10;
  double time = 0.0;
  double incriments = 10; 
  while( !0 ){
    while( copTemp.speed*(time) < distChase){
      time+=incriments;
      distChase = pow((pow((robTemp.x+robTemp.speed*(copTemp.time+time)*cos((robTemp.direction*2*PI)/DEGREES)-copTemp.x), 2)+pow((robTemp.y+robTemp.speed*(copTemp.time+time)*sin((robTemp.direction*2*PI)/DEGREES)-copTemp.y), 2) ), 0.5);
    }// FOUND THIS EQUIVALENT EQUATION ONLINE FOR FASTEST CHASE

    if(copTemp.speed*time-distChase < 0.0001) 
      break; // COP CAUGHT ROBBER 
    
    incriments/=2;

    while( copTemp.speed*(time) > distChase ){
      time-=incriments;
      distChase = pow((pow((robTemp.x+robTemp.speed*(copTemp.time+time)*cos((robTemp.direction*2*PI)/DEGREES)-copTemp.x), 2)+pow((robTemp.y+robTemp.speed*(copTemp.time+time)*sin((robTemp.direction*2*PI)/DEGREES)-copTemp.y), 2)), 0.5);
    }// FOUND THIS EQUIVALENT EQUATION ONLINE FOR FASTEST CHASE 
    
    if( distChase-copTemp.speed*time< 0.0001) 
      break; // Cop CAUGHT Robber 

    incriments/=2;
  }//END OF WHILE !0
  return time;
}//END OF minimalTime


// Initialize a Robber function with the passed inputs 
Robber initalizeRobber(int x, int y, int speed, int direction){
  Robber robber;
  robber.x = (float)x;
  robber.y = (float)y;
  robber.speed = (float)speed;
  robber.direction = (float)direction;
  return robber;
}//END OF INITALIZE ROBBER


//Robber's Location stored as an array 
void RobberLocation(Robber ** robTemp, int numberOfRobbers){
  *robTemp = (Robber *) calloc((numberOfRobbers+1), sizeof(Robber));
  int i, x, y, speedTemp , dir;
  for( i = 0; i < numberOfRobbers; i++ ){
    scanf("%d %d %d %d", &x, &y, &dir, &speedTemp);
    *(*robTemp+i) = initalizeRobber(x, y, speedTemp, dir);
  }
}// END OF ROBBER LOCATION


// FUNCTION THAT INITIALIZES THE PROGRAM AND FUNCTIONS
void runApp(){
  while(!0){
    int numberOfRobbers, speedTemp;
    double time, minTime;
    int * Permutation;

    //INPUT Number of Robers and Speed 
    scanf("%d %d", &numberOfRobbers, &speedTemp);

    // IF NO ROBBERS OR THEY AREN'T MOVING GAME OVER
    if(numberOfRobbers == 0 && speedTemp == 0) 
      break;

    Cop copTemp;
    copTemp.x = copTemp.y = copTemp.time = 0.0;
    copTemp.speed = speedTemp;

    Robber * robTemp;
    RobberLocation(&robTemp, numberOfRobbers);

    int j , k , factTemp = factorial(numberOfRobbers);

    // Running Permuntations through the permuntation array  
    for( j = 0; j < factTemp; j++ ){

      Permutation = permutation(numberOfRobbers,j);
      copTemp.x = copTemp.y = copTemp.time = 0.0;

      for( k = 0; k < numberOfRobbers; k++){
        copTemp.time+=minimalTime(copTemp,robTemp[Permutation[k]]);
        copTemp.x = robTemp[Permutation[k]].x+robTemp[Permutation[k]].speed*(copTemp.time)*cos((robTemp[Permutation[k]].direction*2*PI)/DEGREES);
        copTemp.y = robTemp[Permutation[k]].y+robTemp[Permutation[k]].speed*(copTemp.time)*sin((robTemp[Permutation[k]].direction*2*PI)/DEGREES);
      }

      if( j == 0 ) 
        minTime = copTemp.time;
      else{
        if ( copTemp.time < minTime) minTime = copTemp.time;
      }
      free(Permutation); 
    }
    printf("%0.02f\n", minTime); 
    free(robTemp); 
  }//END OF WHILE NOT 0 
}//END OF RUN APP
