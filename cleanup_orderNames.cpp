// Program for reordering names of genes, using the TSP solution.
// This program creates a list of gene names for each cluster.  For a
// rearrangement of matrix values, use order1.  For this rearrangement
// clusters identified, use order2.
//
// Sharlee Climer, 2004
//
// cleaned up by Alberto Maiocco in 2019

#include "conv.h"

int main(int argc, char * argv[])
{
  FILE *tourFile;
  FILE *input;
  FILE *output;

  if (argc != 6) {
    std::cerr << "Usage: orderNames tour.sol data.txt outputFile.txt numClusters numObjects" << std::endl;
    fatal("Check command line arguments");
  }

  if ((tourFile = fopen(argv[1], "r")) == NULL)
    fatal("File could not be opened.\n");

  if (((input = fopen(argv[2], "r")) == NULL) ||
      ((output = fopen(argv[3], "w")) == NULL))
    fatal("File could not be opened.\n");

  int K = atoi(argv[4]);
  int n = atoi(argv[5]);     // number of items
  std::cout << "n = " << n << ", startCity = " << startCity << std::endl;

  char string[30];
  int num;
  int * tour;
  char ** names;
  int dummy = -1;
  int *partition;
  float *gVals;
  int dummyPtr = 0;
  int rowPtr = 0;
  //int colPtr = 0;

  if (((partition = new int[K-1]) == NULL) ||
      ((gVals = new float[K-1]) == NULL))
    fatal("Memory not allocated");

  if (((tour = new int[n+K]) == NULL) ||
      ((names = new char* [n]) == NULL))
    fatal("Memory not allocated");

  for (int i = 0; i < n; i++)
    if ((names[i] = new char[30]) == NULL)
      fatal("Memory not allocated");

  fscanf(tourFile, "%s", string);   // throw away number of cities
  num = atoi(string);
  if (num != n+K)
    fatal("Number of cities does not match");

  for (int i = 0; i < n+K; i++) {
    fscanf(tourFile, "%s", string);
    tour[i] = atoi(string);
    if (startCity)
      tour[i]--;     // subtract if city numbers 1 to n
    if ((tour[i] < 0) || (tour[i] >= n+K))
      fatal("Check startCity in convert.h");
    if ((tour[i] >= n) && (dummy == -1))   // find first dummy city
      dummy = i;
  }
  fclose(tourFile);
  /*
  int number = 1;
  for (int i = 0; i < n+K; i++)
    if (tour[i] >= n) {
      std::cout << "i = " << i << ", tour[i] = " << tour[i] << ", number = " << number << std::endl;
      number++;
    }
  */
  for (int i = 0; i < n; i++) {      // read in gene names
      fscanf(input, "%s", string);
      sprintf (names[i], "%s", string);
      //std::cout << i << ": " << names[i] << std::endl;
    }
  fclose(input);

  int clustNum = 1;
  fprintf(output, "k = %d\n", K);
  fprintf(output, "%d ******* \n ", clustNum++);

  for (int i = dummy+1; i < n+K; i++) {
    //std::cout << "i = " << i << std::endl;
    if (tour[i] >= n) {
      //partition[dummyPtr++] = rowPtr - 1;  // mark other dummy nodes
      //std::cout << "clustNum = " << clustNum << ", i = " << i << ", tour[i] = " << tour[i] << std::endl;
      fprintf(output, "%d *******  ", clustNum++);
      fprintf(output, "\n");
      continue;                  // don't include dummy nodes in arrangement
    }
    //std::cout << "tour[i] = " << tour[i] << std::endl;
    if (tour[i] < 10)  fprintf(output, " ");
    //fprintf(output, "%d: ", tour[i]);
    //std::cout << names[tour[i]] << std::endl;
    fprintf(output, "%s \n", names[tour[i]]);
    //colPtr = 0;
    //rowPtr++;
  }
  //std::cout << "here3" << std::endl;
  //std::cout << "dummy = " << dummy << std::endl;
  //for (int i = 0; i < K-1; i++)
  //std::cout << partition[i] << std::endl;

  for (int i = 0; i < dummy; i++) {
    if (tour[i] < 10)  fprintf(output, " ");
    //fprintf(output, "%d: ", tour[i]);
    fprintf(output, "%s \n", names[tour[i]]);
    //colPtr = 0;
    //rowPtr++;
  }
  /*
  for (int i = 0; i < K-1; i++)
    std::cout << partition[i] << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      std::cout << newData[i][j] << " ";
    std::cout << std::endl;
  }
  */

  fclose(output);

  /*
  double Sscore = 0;
  double Gscore = 0;
  float Snorm = 0;
  float Gnorm = 0;
  //float stotal = 0;
  dummyPtr = 0;
  */
  /*
  float maxNeg = 0.0;
  int intData[n][numConditions];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < numConditions; j++) {
      if (newData[i][j] >= 1000)     // missing data
	fatal("missing data values");
      if (newData[i][j] < maxNeg)
	maxNeg = newData[i][j];
    }

  if (maxNeg < 0.0)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < numConditions; j++)
	newData[i][j] -= maxNeg;     // no negative vals

  for (int i = 0; i < n; i++)
    for (int j = 0; j < numConditions; j++) {
      intData[i][j] = (int)(newData[i][j] * 100);  // change to integers
      if (newData[i][j] - (float)intData[i][j] >= 0.5)
	intData[i][j]++;
    }
  */
  /*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < numConditions; j++)
      std::cout << intData[i][j] << " " ;
    std::cout << std::endl;
  }
  */
  /*
  for (int x = 0; x < n-1; x++) {
    double num = 0;
    for (int j = 0; j < numConditions; j++)
      num += intData[x][j] * intData[x+1][j];

    if ((x == partition[dummyPtr]) && (K > 1)) {
      Gscore += num;       // this is a break between clusters
      //Gnorm += (num + 1) / 2;  // normalize to range [0,1]
      gVals[dummyPtr++] = num;
      //dummyPtr++;
      std::cout << "x: " << x << ", Gscore = " << Gscore << ", num "
         << num << std::endl;
      //Sscore += stotal / (float)clusterSize;
      //stotal = 0;
      //clusterSize = 0;
    }

    else {
      Sscore += num;
      //Snorm += (num + 1) / 2;  // normalize to range [0,1]
      std::cout << "Sscore = " << Sscore << ", num " << num << std::endl;
      //stotal += num;
      //clusterSize++;
    }
  }

  //Sscore /= (float)K;
  //Gscore /= (float)K;
  //if (K == 1)
  //Sscore /= (float)n;
  Sscore /= 10000;
  Gscore /= 10000;
  std::cout << "Sscore = " << Sscore << ", Gscore = " << Gscore << std::endl;

  FILE * results;
  if ((results = fopen(argv[5], "a")) == NULL)
    fatal("File could not be opened.\n");
  //fprintf(results, "K    Sscore    Gscore  Savg-Gavg  medG    avgG    95upG    95downG    minG   maxG\n");
  fprintf(results, "%d   %0.3f   %0.3f   %0.3f   %0.3f", K, Sscore, Gscore,
	  (Sscore/(float)(n-K-1)) - (Gscore/(float)K),
	  (Sscore/(float)(n-K-1)) / (Gscore/(float)K));
  fclose(results);

  printStatistics(gVals, K-1, argv[5]);

  if ((results = fopen(argv[5], "a")) == NULL)
    fatal("File could not be opened.\n");
  fprintf(results, "  %0.3f  %0.3f\n", gVals[0], gVals[K-2]);
  fclose(results);
  */

  delete [] tour;
  for (int i = 0; i < n; i++)
    delete [] names[i];

  delete [] names;

  //delete [] partition;
  return 1;
}
