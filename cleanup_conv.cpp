// Program for converting data matrix into a TSP using the Pearson
// correlation coefficient.
//
// Sharlee Climer, 2004
//
// Missing values should be replaced by '1000'.  It is assumed that
// the input data is real values (negative values are OK) that are
// less than 1000.
//
//cleaned up by Alberto Maiocco in 2019

#include "conv.h"

int main(int argc, char * argv[])
{
  // args coming in are: data matrix, output name, clusters, objects, features
  if (argc != 6) {
    //error fatal
    std::cerr << "Usage: conv data.txt outputFile.tsp numClusters numObjects numFeatures" << std::endl;
    fatal("Check command line arguments");
    return 0;
  }

  FILE *input;
  FILE *output;

  //file handling
  if (((input = fopen(argv[1], "r")) == NULL) || ((output = fopen(argv[2], "w")) == NULL))
    fatal("File could not be opened.\n");

  int K = atoi(argv[3]);     // number of clusters
  int n = atoi(argv[4]);     // number of items (defined in convert.h)
  int numConditions = atoi(argv[5]);  // number of conditions(defined in convert.h)

  char string[50];
  std::cout << "n = " << n << ", numConditions = " << numConditions << std::endl;

  fprintf(output, "NAME: %s\nTYPE: TSP\n", argv[2]);
  fprintf(output, "DIMENSION: %d\n", n+K);
  fprintf(output, "EDGE_WEIGHT_TYPE: EXPLICIT \nEDGE_WEIGHT_FORMAT: UPPER_ROW \nEDGE_WEIGHT_SECTION \n");

  float ** data;

  if ((data = new float* [n]) == NULL) fatal("Memory not allocated");

  for (int i = 0; i < n; i++) {
    if ((data[i] = new float[numConditions]) == NULL) fatal("Memory not allocated");
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < numConditions; j++) {      // read in gene data
      fscanf(input, "%s", string);
      data[i][j] = atof(string);
    }
  }

  //figure out maximum values, try not to use 1000 for arbitrarily large number
  //this for missing values

  //weighted hamming distance

  //prep TSP??

  //implementing pearson correlation coefficient(?)
  for (int x = 0; x < n-1; x++) {
    for (int y = x+1; y < n; y++) {
      float sumX = 0;
      float sumY = 0;
      float sumXY = 0;
      float sumX2 = 0;
      float sumY2 = 0;
      float N = 0;

      for (int i = 0; i < numConditions; i++) {
	       if ((data[x][i] < 1000) && (data[y][i] < 1000)) {
	          N++;
	          sumX += data[x][i];
	          sumY += data[y][i];
	          sumXY += data[x][i] * data[y][i];
	          sumX2 += data[x][i] * data[x][i];
	          sumY2 += data[y][i] * data[y][i];
	       }
       }

      float num = sumXY;

      if (N > 0) num -= sumX * sumY / N;
      if ((num < 0.00001) && (num > -0.00001)) num = 0;
      else {
	       float den = sqrt((sumX2 - (sumX*sumX/N)) * (sumY2 - (sumY*sumY/N)));
	       if ((den < 0.000001) && (den > -0.000001)) fatal("den is very small");
	       num /= den;

      }



      if (N == 0)   num = 0;  // not enough data - assume uncorrelated
      if (num < -1) num = -1; // take care of round-off error
      if (num > 1)  num = 1;

      num = 5000 - (5000 * num);  // invert and scale up values

      int newnum = (int)num;
      if (num - (float)newnum >= 0.5)	newnum++;
      if (newnum < 0) {
        std::cout << "num = " << num << ", newnum = " << newnum << std::endl;
       std::cout << x << ", " << y << ": " << std::endl;
	    fatal("negative distance value");
      }
      fprintf(output, "%d ", newnum);

    }

    for (int i = 0; i < K; i++) fprintf(output, "0 ");   // add dummy nodes

    fprintf(output, "\n");
  }

  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K-i; j++)
      fprintf(output, "0 ");   // distance between dummy cities
    fprintf(output, "\n");
  }

  for (int i = 0; i < n; i++) {
      delete [] data[i];
  }

  delete [] data;

  fclose(input);
  fclose(output);

  return 1;
}
