/**
 * @file    mash_map.cpp
 * @ingroup src
 * @author  Chirag Jain <cjain7@gatech.edu>
 */

#include <iostream>
#include <ctime>
#include <chrono>
#include <functional>

//Own includes
#include "map/include/map_parameters.hpp"
#include "map/include/base_types.hpp"
#include "map/include/parseCmdArgs.hpp"
#include "map/include/winSketch.hpp"
#include "map/include/computeMap.hpp"

//External includes
#include "common/argvparser.hpp"

int main(int argc, char** argv)
{
  /*
   * Make sure env variable MALLOC_ARENA_MAX is unset 
   * for efficient multi-thread execution
   */
  unsetenv((char *)"MALLOC_ARENA_MAX");

  CommandLineProcessing::ArgvParser cmd;

  //Setup command line options
  skch::initCmdParser(cmd);

  //Parse command line arguments
  skch::Parameters parameters;        //sketching and mapping parameters

  skch::parseandSave(argc, argv, cmd, parameters);   

  auto t0 = skch::Time::now();

  //Build the sketch for reference
  skch::Sketch referSketch(parameters);

  std::chrono::duration<double> timeRefSketch = skch::Time::now() - t0;
  std::cerr << "INFO, skch::main, Time spent computing the reference index: " << timeRefSketch.count() << " sec" << std::endl;

  //Map the sequences in query file
  t0 = skch::Time::now();

  skch::Map mapper = skch::Map(parameters, referSketch);

  std::chrono::duration<double> timeMapQuery = skch::Time::now() - t0;
  std::cerr << "INFO, skch::main, Time spent mapping the query : " << timeMapQuery.count() << " sec" << std::endl;

  std::cerr << "INFO, skch::main, mapping results saved in : " << parameters.outFileName << std::endl;

}
