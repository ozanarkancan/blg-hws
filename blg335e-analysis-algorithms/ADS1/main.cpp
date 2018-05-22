#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "Location.h"
#include <deque>
#include <time.h>
#include "AlgorithmExecuter.h"

using namespace std;

int main(int argc, char* argv[]){
  string line;
  int index = 0;
  int N = atoi(argv[1]);
  unsigned k = atoi(argv[2]);
  char algorithmType = argv[3][0];
  clock_t startTime, endTime;

  ifstream myfile("location.txt");

  vector<Location> locations = vector<Location>();
  vector<Location> result = vector<Location>();

  //istanbul 41.0186	28.9647
  Location target = Location("", atof(argv[4]), atof(argv[5]));

  if(myfile.is_open())
  {
	  while (getline(myfile, line) && index < N)
	  {
	      index++;
		  unsigned pos = line.find("\t");
		  string city = line.substr(0,pos);
		  line = line.substr(pos+1);
		  pos = line.find("\t");
		  float latitude = atof(line.substr(0,pos).c_str());
		  line = line.substr(pos+1);
		  float longitude = atof(line.substr(0,pos).c_str());
		  Location location = Location(city, latitude, longitude);
		  locations.push_back(location);
	  }
	  myfile.close();

	  AlgorithmExecuter ae = AlgorithmExecuter(target);

      //SECTION FOR EVALUATING AVERAGE RUNNING TIME
      /*startTime = clock();
      for(unsigned i = 0; i < 1; i++)
      {
          vector<Location> copyOfLocations = vector<Location>(locations);
          result = ae.executeAlgorithm(locations, k, algorithmType);
      }
      endTime = clock();
      cout << "Running time: " << (float)(endTime - startTime) * 1000000 / CLOCKS_PER_SEC << " us" << endl << endl;*/

      startTime = clock();
      result = ae.executeAlgorithm(locations, k, algorithmType);
      endTime = clock();
      cout << "Running time: " << (float)(endTime - startTime) / CLOCKS_PER_SEC << " us" << endl << endl;

      ofstream out("output.txt");

      if(out.is_open())
      {
          for(unsigned i = 0; i < result.size(); i++)
            out << result[i].getCity() << "\t" << result[i].getLatitude() << "\t" << result[i].getLongitude() << endl;

          out.close();
      }
      else
        cout << "Output file could not be opened." << endl;
  }
  else
	  cout << "File could not be opened." << endl;
  return 0;
}
