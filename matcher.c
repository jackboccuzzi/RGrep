/**
 * You can modify this file.
 */

#include "matcher.h"

/**
 * Your helper functions can go below this line
 */

// check if char is the '.' operator
int isDotOperator(char op) {
  if (op == '.') {
      return 1;
  }
  return 0;
}

// check if char is the + operator
int isPlusOperator(char op) {
  if (op == '+') {
      return 1;
  }
  return 0;
}

// check if char is the ? operator
int isQuestionOperator(char op) {
  if (op == '?') {
      return 1;
  }
  return 0;
}

// check if the char is the \ operator
int isBackSlashOperator(char op) {
  if (op == '\\') {
    return 1;
  }
  return 0;
}

/**
 * Your helper functions can go above this line
 */


/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // if we hit end of pattern, its a match
  if (*pattern == '\0') {
    return 1;
  }
  // if pattern contains '\' operator
  else if (isBackSlashOperator(*pattern) == 1) {
    if (*partial_line == *(pattern + 1)) {
      return matches_leading(partial_line + 1, pattern + 2);
    }
    else {
      return 0;
    }
  }
  // if pattern contains '?' operator
  else if (isQuestionOperator(*(pattern + 1)) == 1) {
    if (*partial_line == *pattern) {
      return matches_leading(partial_line + 1, pattern + 2);
    }
    else {
      return matches_leading(partial_line, pattern + 2);
    }
  }
  // if pattern contains '+' operator
  else if (isPlusOperator(*(pattern + 1)) == 1) {
    char current_char = *partial_line;
    // move the pointer to the point in memory where the last repeated char is
    while (*partial_line == current_char) {
      partial_line++;
    }
    return matches_leading(partial_line, pattern + 2);
  }

  // if we hit end of partial line, its not a match
  if (*partial_line == '\0') {
    return 0;
  }

  // if the current char in pattern is a '.' or the chars match
  if (isDotOperator(*pattern) == 1 || *partial_line == *pattern) {
    return matches_leading(partial_line + 1, pattern + 1);
  }
  // if the chars dont match, return false
  else {
    return 0;
  }
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {
  // . -> matches any character
  // + -> preceding chars can be repeated one or more times
  // ? -> preceding chars may appear zero or one times
  // \ -> escape the next character (nullifying its meaning)
  
  if (*line == '\0') {
    return 0;
  }
  if (matches_leading(line, pattern) == 1) {
    return 1;
  }
  else {
    return rgrep_matches(line + 1, pattern);
  }
  return 0;
}
