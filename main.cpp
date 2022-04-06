#include "Solver.hpp"
#include <iostream>
#include <time.h>
#include <chrono>

using namespace GameSolver::Connect4;

/*
 * Main function.
 * Reads Connect 4 positions, line by line, from standard input 
 * and writes one line per position to standard output containing:
 *  - score of the position
 *  - number of nodes explored
 *  - time spent in microsecond to solve the position.
 *
 *  Any invalid position (invalid sequence of move, or already won game) 
 *  will generate an error message to standard error and an empty line to standard output.
 */

int main(int argc, char** argv) {

  Solver solver;

  bool weak = false;	
  bool analyze = true;

  std::string opening_book = "7x6.book";

  //not needed actually
  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-') {
      if(argv[i][1] == 'w') weak = true; // parameter -w: use weak solver
      else if(argv[i][1] == 'b') { // paramater -b: define an alternative opening book
        if(++i < argc) opening_book = std::string(argv[i]);
      }
      else if(argv[i][1] == 'a') { // paramater -a: make an analysis of all possible moves
        analyze = true;
      }
    }
  }
  solver.loadBook(opening_book);
  

  std::string line;
  
  for(int l = 1; std::getline(std::cin, line); l++) {
    Position P;
    if(P.play(line) != line.size()) {
      std::cerr << "Line " << l << ": Invalid move " << (P.nbMoves()+1) << " \"" << line << "\"" << std::endl;
    } 
    // else {
    //   solver.reset();
    //   auto start = std::chrono::high_resolution_clock::now();
    //   std::cout << "start solver \n";
    //   int score = solver.solve(P, weak);
    //   std::cout << "end solver \n";
    //   auto end = std::chrono::high_resolution_clock::now();
    //   double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    //   time_taken *= 1e-9; 
    //   std::cout << line << " score:" << score << " solver.getNodeCount:" << solver.getNodeCount() << " time_taken:" << time_taken ;
    // }
    // std::cout << std::endl;
    else {
      std::cout << line;
      if(analyze) {
        std::vector<int> scores = solver.analyze(P, weak);
        for(int i = 0; i < Position::WIDTH; i++) std::cout << " " << scores[i];
        // int score = solver.solve(P, weak);
        // std::cout << " and score:" << score;
      }
      else {
        int score = solver.solve(P, weak);
        std::cout << " " << score;
      }
      std::cout << std::endl;
    }
  }
}