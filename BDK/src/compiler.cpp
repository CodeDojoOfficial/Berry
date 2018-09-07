#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#ifndef __BERRY_COMPILER_INITIALIZED__
#define __BERRY_COMPILER_INITIALIZED__ true

// Runtime error codes
#define ERR_UNKNOWN 1
#define ERR_LOOP    2

// Compiler error codes
#define CMPLERR_UNKNOWN 128
#define CMPLERR_OPTION  129
#define CMPLERR_FILE    130
#define CMPLERR_LOOP    131

// Primitive constants
#define PRIM_ADD   '+'
#define PRIM_SUB   '-'
#define PRIM_LEFT  '<'
#define PRIM_RIGHT '>'
#define PRIM_PRINT '.'
#define PRIM_INPUT ','
#define PRIM_LOOP0 '['
#define PRIM_LOOP1 ']'

#endif // __BERRY_COMPILER_INITIALIZED__

namespace berrySecrets {

class StackTraceElement {
public:
  StackTraceElement(std::string filename, int line, int column) : filename_(filename), line_(line), column_(column) {}

  std::string filename() { return filename_; }
  int         line    () { return line_    ; }
  int         column  () { return column_  ; }
private:
  const std::string filename_;
  const int line_;
  const int column_;
};

class ErrorMessage {
public:
  ErrorMessage(std::string type, std::string message) : type_(type), message_(message) {}

  std::string type   () { return type_   ; }
  std::string message() { return message_; }
private:
  const std::string type_;
  const std::string message_;
};

bool c_str_equality(char* c_str, std::string comparator) {
  std::string converted(c_str);

  return (converted == comparator);
}

void throwError(StackTraceElement stackTrace, ErrorMessage message) {
  std::cout << "\033[31m" << message.type() << ":\033[0m " << message.message() << std::endl;
  std::cout << "\tat " << stackTrace.filename() << ":" << stackTrace.line() << ":" << stackTrace.column() << std::endl;
}

}

int main(int argc, char** argv) {
  using namespace berrySecrets;

  // Command line options
  bool verbose = false;                  // Triggered by: -v --verbose
  
  bool output_set = false;
  std::string output_filename = "berry"; // Triggered by: -o --output
  
  bool input_set = false;
  std::string input_filename = "";

  // RECOGNIZE COMPILER COMMAND LINE ARGUMENTS
  for(int i = 1; i < argc; ++i) { // Skip script name agrument
    if(c_str_equality(argv[i], "-v") || c_str_equality(argv[i], "--verbose")) {
      if(verbose) {
        std::cerr << "Duplicate option: " << argv[i] << std::endl;
        return CMPLERR_OPTION;
      }

      verbose = true;
    } else if(c_str_equality(argv[i], "-o") || c_str_equality(argv[i], "--output")) {
      if(output_set) {
        std::cerr << "Duplicate option: " << argv[i] << std::endl;
        return CMPLERR_OPTION;
      }
      
      if(i + 1 > argc - 1) {
        std::cerr << "Expected an identifier after option: " << argv[i] << std::endl;
        return CMPLERR_OPTION;
      }

      output_filename = std::string(argv[++i]); // Skip the next input
    } else if(argv[i][0] == '-') {
      std::cerr << "Unknown option: " << argv[i] << std::endl;
      return CMPLERR_OPTION;
    } else {
      if(input_set) {
        std::cerr << "Input file already specified: " << input_filename << std::endl;
        return CMPLERR_FILE;
      }
      
      input_set = true;
      input_filename = argv[i];
    }
  }

  // COMPILATION PREPERATION
  char* stack; 
  int stackPointer = 0;
  int stackLength;
  
  if(!input_set) {
    std::cerr << "No input file given." << std::endl;
    return CMPLERR_FILE;
  }

  std::ifstream input(input_filename);
  if(!input.good()) {
    std::cerr << "No such file: " << input_filename << std::endl;
    return CMPLERR_FILE;
  }

  if(true) { // Intentionally create new scope.
    input.seekg(0, std::ios::end);
    stackLength = input.tellg();
    stack = (char*) malloc(stackLength);
    input.seekg(0, std::ios::beg);
    input.read(stack, stackLength);
    input.close();
  }

  // C++ FILE GENERATION
  if(verbose) {
    std::cout << "Genrating resource: " << output_filename << ".cpp ... ";
  }
  
  if(std::ifstream(output_filename + ".cpp").good()) {
    system(std::string(std::string("chmod 644 ") + output_filename + ".cpp").c_str()); // allow write access to generated file.
  }

  std::ofstream output_(output_filename + ".cpp", std::ofstream::out | std::ofstream::trunc);

  output_ << "/* WARNING: THIS FILE IS MACHINE GENERATED." << std::endl;
  output_ << " * DO NOT EDIT." << std::endl;
  output_ << " */" << std::endl << std::endl;

  output_ << "// Generated by Berry Compiler v1.0.0_0." << std::endl << std::endl;
  
  output_ << "/* Copyright (c) 2018 by CodeDojo and/or its individual developers. All rights reserved." << std::endl
          << " * " << std::endl
          << " * JUST BECAUSE THIS FILE IS ON YOUR COMPUTER/DISK/HARD DRIVE DOES NOT MEAN IT IS FREE" << std::endl
          << " * TO EDIT. DO NOT EDIT OR POST THIS FILE ANYWHERE ON THE INTERNET." << std::endl
          << " */" << std::endl;
  
  output_ << "#include <iostream>" << std::endl << std::endl;

  output_ << "int main(int argc, char** argv) {" << std::endl;
  
  output_ << "  char memory[8] = {\'\\0\', \'\\0\', \'\\0\', \'\\0\', \'\\0\', \'\\0\', \'\\0\', \'\\n\'};" << std::endl;
  output_ << "  int memoryPointer = 0;" << std::endl;
  output_ << "  " << std::endl;
  
  int line = 1;
  int clmn = 0;

  int openLoops = 0; // LoopError thrown if openLoops is 0, and the lexer discovers a ']'.

  std::string tabs = ""; // Used when an indent occurs, such as a loop

  // LEXING AND CODE INSERTION
  for(int i = 0; i < stackLength; ++i) {
    char token = stack[i];
    switch(token) {
    case PRIM_ADD: // '+'
      clmn++;
      output_ << tabs << "  memory[memoryPointer]++;" << std::endl;
      break;
    case PRIM_SUB: // '-'
      clmn++;
      output_ << tabs << "  memory[memoryPointer]--;" << std::endl;
      break;
    case PRIM_RIGHT: // '>'
      clmn++;
      output_ << tabs << "  memoryPointer++; memoryPointer %= 8;" << std::endl; // Loop around if overflow or negative occurs.
      break;
    case PRIM_LEFT: // '<'
      clmn++;
      output_ << tabs << "  memoryPointer--; memoryPointer %= 8;" << std::endl; // Loop around if overflow or negative occurs.
      break;
    case PRIM_PRINT: // '.'
      clmn++;
      output_ << tabs << "  std::cout << memory[memoryPointer];" << std::endl;
      break;
    case PRIM_INPUT: // ','
      clmn++;
      output_ << tabs << "  std::cin >> memory[memoryPointer];" << std::endl;
      break;
    case PRIM_LOOP0: // '['
    case PRIM_LOOP1: // ']'
      clmn++;
      if(token == PRIM_LOOP0) { // '['
        output_ << tabs << "  " << std::endl;
        output_ << tabs << "  while(memory[memoryPointer] != 0) {" << std::endl;
        
        openLoops++;

        tabs += "  ";
        output_ << tabs << "  " << std::endl;
      } else { // ']'
        if(openLoops == 0) {
          throwError(StackTraceElement(input_filename, line, clmn), ErrorMessage("LoopError", "Found an ending bracket, but there was no open loops"));
          return CMPLERR_LOOP;
        } else {
          output_ << tabs << "  " << std::endl;
          
          std::string temp = "";
          for(int i = 1; i < openLoops; ++i) {
            temp += "  ";
          }
          tabs = temp;

          output_ << tabs << "  }" << std::endl;

          openLoops--;

          output_ << tabs << "  " << std::endl;
        }
      }
      break;
    default:
      if(token == '\n') {
        line++;
        clmn = 0;
      } else {
        clmn++;
      } // Otherwise, comment
      break;
    }
  }
  
  if(openLoops != 0) {
    throwError(StackTraceElement(input_filename, line, clmn), ErrorMessage("LoopError", "Found EOF before all loops were closed"));
    return CMPLERR_LOOP;
  }

  output_ << "  " << std::endl;
  output_ << "  return 0;" << std::endl;
  output_ << "}" << std::endl;

  output_.close();

  if(verbose) {
    std::cout << "done." << std::endl;
    std::cout << "Compiling resource... ";
  }

  system(std::string(std::string("g++ -o ") + std::string(output_filename) + std::string(" ") + std::string(output_filename) + std::string(".cpp 2>/dev/null")).c_str());

  if(verbose) {
    std::cout << "done." << std::endl;
  }

  system(std::string(std::string("chmod 444 ") + std::string(output_filename) + std::string(".cpp")).c_str()); // read-only on all levels

  return EXIT_SUCCESS;
}
