// Program for reordering rows of matrix, using the TSP solution.
// This program creates a listing of objective features, with each
// cluster identified.  For a rearrangement of gene names, use orderNames.
// For a rearangement of the data without clusters marked, use order1.
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

  if (argc != 7) {
    std::cerr << "Usage: order2 tour.sol data.txt outputFile.txt numClusters numObjects numFeatures" << std::endl;
    fatal("Check command line arguments");
  }

  if ((tourFile = fopen(argv[1], "r")) == NULL)
    fatal("File could not be opened.\n");

  if (((input = fopen(argv[2], "r")) == NULL) ||
      ((output = fopen(argv[3], "w")) == NULL))
    fatal("File could not be opened.\n");

  int K = atoi(argv[4]);
  int n = atoi(argv[5]);     // number of items
  int numConditions = atoi(argv[6]);  // number of conditions
  std::cout << "n = " << n << ", numConditions = " << numConditions << ", startCity = " << startCity << std::endl;

  char string[50];
  int num;
  int * tour;
  float ** data;
  float ** newData;
  int dummy = -1;
  int *partition;
  float *gVals;
  int dummyPtr = 0;
  int rowPtr = 0;
  int colPtr = 0;

  if (((partition = new int[K-1]) == NULL) ||
      ((gVals = new float[K-1]) == NULL))
    fatal("Memory not allocated");

  if (((tour = new int[n+K]) == NULL) ||
      ((data = new float* [n]) == NULL))
    fatal("Memory not allocated");

  for (int i = 0; i < n; i++)
    if ((data[i] = new float[numConditions]) == NULL)
      fatal("Memory not allocated");

  if ((newData = new float* [n]) == NULL)
    fatal("Memory not allocated");

  for (int i = 0; i < n; i++)
    if ((newData[i] = new float[numConditions]) == NULL)
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

  for (int i = 0; i < n; i++)
    for (int j = 0; j < numConditions; j++) {      // read in gene data
      fscanf(input, "%s", string);
      data[i][j] = atof(string);
    }

  int clustNum = 1;
  fprintf(output, "k = %d\n", K);
  fprintf(output, "%d ******\n", clustNum++);

  for (int i = dummy+1; i < n+K; i++) {
    if (tour[i] >= n) {          // mark other dummy nodes
      partition[dummyPtr++] = rowPtr - 1;
      fprintf(output, "%d ******\n", clustNum++);
      continue;                  // don't include dummy nodes in arrangement
    }
    if (tour[i] < 10)  fprintf(output, " ");
    fprintf(output, "%d: ", tour[i]);
    for (int j = 0; j < numConditions; j++) {
      newData[rowPtr][colPtr++] = data[tour[i]][j];
      fprintf(output, "%.2f\t", data[tour[i]][j]);
    }
    colPtr = 0;
    rowPtr++;
    fprintf(output, "\n");
  }

  for (int i = 0; i < dummy; i++) {
    if (tour[i] < 10)  fprintf(output, " ");
    fprintf(output, "%d: ", tour[i]);
    for (int j = 0; j < numConditions; j++) {
      newData[rowPtr][colPtr++] = data[tour[i]][j];
      fprintf(output, "%.2f\t", data[tour[i]][j]);
    }
    colPtr = 0;
    rowPtr++;
    fprintf(output, "\n");
  }

  fclose(output);
  fclose(input);

  delete [] tour;
  for (int i = 0; i < n; i++) {
    delete [] data[i];
    delete [] newData[i];
  }
  delete [] data;
  delete [] newData;

  return 1;
}
